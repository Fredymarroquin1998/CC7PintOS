#include "userprog/syscall.h"
#include <stdio.h>
#include <syscall-nr.h>
#include "threads/interrupt.h"
#include "threads/thread.h"
#include "threads/vaddr.h"
#include "list.h"
#include "process.h"

static void syscall_handler (struct intr_frame *);
void* validar(const void*);
void halt(void);
void exit(int status);
int read(int fd,void *buffer,unsigned size);
int write(int fd,const void *buffer,unsigned size);
bool create(const char *file,unsigned initial_size);
bool remove(const char *file);
int open(const char *file);
int filesize(int fd);
void seek(int fd,unsigned position);
unsigned tell(int fd);
void close(struct list* files,int fd);
static int get_user (const uint8_t *uaddr);

struct file_description {
  struct file* ptr;
  int fd;
  struct list_elem elem;
};

void
syscall_init (void) 
{
  intr_register_int (0x30, 3, INTR_ON, syscall_handler, "syscall");
}

static void
syscall_handler (struct intr_frame *f UNUSED) 
{
  int *args[3];
  uint8_t* check_byteptr=(uint8_t *)(int*)f->esp;
  args[0]=*((int*)f->esp + 1);//nombre del archivo
  args[1]=*((int*)f->esp + 2);//todos los argumentos que tiene el archivo - bufer
  args[2]=*((int*)f->esp + 3);//longitud del archivo
  
  if (!is_user_vaddr((int*)f->esp)||!pagedir_get_page(thread_current()->pagedir, (int*)f->esp)){
    exit(-1);
    return 0;
  }
  for (int i=0;i<=3;i++){
    if(get_user(check_byteptr+i)==-1){
      exit(-1);
      return 0;
    }
  }
  
  uint32_t syscall_code = *(int*)f->esp;

  switch (syscall_code){
    case SYS_HALT:  //listo
      halt();
      break;

    case SYS_EXIT://LISTO
      if (!is_user_vaddr((int*)f->esp + 1)||!pagedir_get_page(thread_current()->pagedir, (int*)f->esp + 1)){
        exit(-1);
      }else{
        exit(*((int*)f->esp + 1));
      }
      break;

    case SYS_EXEC:
      validar((int*)f->esp + 1);
      validar(*((int*)f->esp + 1));
      char *file_name = *((int*)f->esp + 1);
      char *file_name_copy = malloc (strlen(file_name) + 1);
      strlcpy(file_name_copy, file_name, strlen(file_name) + 1);
      char *save_ptr;
      file_name_copy = strtok_r(file_name_copy, " ", &save_ptr);
      struct file *file=filesys_open(file_name_copy);
      if(file==NULL){
        f->eax = -1;
        break;
      }
      file_close(file);
      f->eax = process_execute(file_name);
      break;

    case SYS_WAIT:  //listo
      f->eax=process_wait(*((int*)f->esp + 1));
      break;
    
    case SYS_CREATE:  //listo
      if (!is_user_vaddr(*((int*)f->esp + 1))||!pagedir_get_page(thread_current()->pagedir, *((int*)f->esp + 1))){
        exit(-1);
        return 0;
      }
      uint8_t* check_byteptr = (uint8_t *)*((int*)f->esp + 1);
      for (int i=0;i<=3;i++){
        if(get_user(check_byteptr+i)==-1){
          exit(-1);
          return 0;
        }
      }
      pagedir_get_page(thread_current()->pagedir, *((int*)f->esp + 1));
      f->eax = create((const char*)*((int*)f->esp + 1), (unsigned)*((int*)f->esp + 2));
      break;

    case SYS_REMOVE:  //listo
      f->eax=remove((const char*)*((int*)f->esp + 1));
      break;

    case SYS_OPEN:  //listo
      validar((int*)f->esp + 1);
      validar(*((int*)f->esp + 1));
      f->eax=open((const char*)*((int*)f->esp + 1));
      break;
    
    case SYS_FILESIZE:  //listo
      f->eax=filesize(*((int*)f->esp + 1));
      break;

    case SYS_READ://lisgo
      validar(*((int*)f->esp + 2));
      f->eax=read(*((int*)f->esp + 1),(void*)*((int*)f->esp + 2),(unsigned)*((int*)f->esp + 3));
      break;

    case SYS_WRITE: //listo
      validar(*((int*)f->esp + 2));
      f->eax = write(*((int*)f->esp + 1), *((int*)f->esp + 2), *((int*)f->esp + 3));
      break;

    case SYS_SEEK://listo
      seek(*((int*)f->esp + 1), *((int*)f->esp + 2));
      break;

    case SYS_TELL://listo
      f->eax = file_tell(tell(*((int*)f->esp + 1)));
      break;

    case SYS_CLOSE://listo
      close(&thread_current()->listado_archivos,*((int*)f->esp + 1));
      break;
  }
}

void halt(void){
  shutdown_power_off();
}

unsigned tell(int fd){
  struct list_elem *e;
  for (e=list_begin(&thread_current()->listado_archivos); e!=list_end(&thread_current()->listado_archivos); e=list_next(e)){
    struct file_description *f=list_entry(e, struct file_description, elem);
    if(f->fd == fd)
      return file_tell(f->ptr);
  }
  return -1;
}

bool create(const char *file,unsigned initial_size){
  return filesys_create(file,initial_size);
}

bool remove(const char *file){
  return filesys_remove(file);
}

int write (int fd, const void *buffer, unsigned length){
  if (fd == 1){
    putbuf(buffer,length);
    return length;
  }
  struct file_description* frame_ptr = NULL;
  struct list_elem *e;
  for (e = list_begin (&thread_current()->listado_archivos); e != list_end (&thread_current()->listado_archivos); e = list_next (e)){
    struct file_description *f = list_entry (e, struct file_description, elem);
    if(f->fd == fd)
      frame_ptr=f;
  }
  if(frame_ptr == NULL)
    return -1;
  int ret = file_write(frame_ptr->ptr,buffer,length);
  return ret;
}

void seek(int fd,unsigned position){
  struct list_elem *e;
  for (e=list_begin(&thread_current()->listado_archivos); e!=list_end(&thread_current()->listado_archivos); e=list_next(e)){
    struct file_description *f=list_entry(e, struct file_description, elem);
    if(f->fd == fd)
      return file_seek(f->ptr,position);
  }
  return -1;
}

int open(const char *file){
  acquire_filesys_lock();
  struct file *file_open=filesys_open(file);
  release_filesys_lock();
  if(file_open==NULL){
    return -1;
  }
  struct file_description *f = malloc(sizeof(*f));
  f->ptr = file_open;
  f->fd = thread_current()->cantidad_archivos;
  thread_current()->cantidad_archivos++;
  list_push_back (&thread_current()->listado_archivos, &f->elem);
  return f->fd;
}

int filesize(int fd){
  struct list_elem *e;
  for (e=list_begin(&thread_current()->listado_archivos); e!=list_end(&thread_current()->listado_archivos); e=list_next(e)){
    struct file_description *f=list_entry(e, struct file_description, elem);
    if(f->fd == fd)
      return file_length(f->ptr);
  }
  return -1;
}

int read(int fd,void *buffer,unsigned size){
  if(fd == 0){
    uint8_t *buf=buffer;
    for(int i=0; i<size; i++){
      buf[i]=input_getc();
    }
    return size;
  }  
  struct list_elem *e;
  for (e=list_begin(&thread_current()->listado_archivos); e!=list_end(&thread_current()->listado_archivos); e=list_next(e)){
    struct file_description *f=list_entry(e, struct file_description, elem);
    if(f->fd == fd)
      return file_read(f->ptr, buffer, size);
  }
  return-1;
}

void close(struct list* files, int fd){
  struct list_elem *element;
  struct file_description *f;
  for (element = list_begin (files); element != list_end (files); element = list_next (element)){
    f = list_entry (element, struct file_description, elem);
    if(f->fd == fd){
      file_close(f->ptr);
      list_remove(element);
    }
  }
  free(f);
}

void exit(int status){
  struct list_elem *e;
  for (e=list_begin(&thread_current()->padre->listado_hijos); e!=list_end(&thread_current()->padre->listado_hijos); e=list_next(e)){
    struct hijo *f=list_entry(e, struct hijo, elem);
    if(f->tid==thread_current()->tid){
      f->en_uso=1;
      f->status_proc = status;
    }
  }
  thread_current()->status_proc=status;
  if(thread_current()->padre->esperando==thread_current()->tid){
    sema_up(&thread_current()->padre->lock_hijos);
  }
  thread_exit();
}

void* validar(const void *vaddr){
  if (!is_user_vaddr(vaddr)||!pagedir_get_page(thread_current()->pagedir, vaddr)){
    exit(-1);
    return 0;
  }
  uint8_t* check_byteptr = (uint8_t *)vaddr;
  for (int i=0;i<=3;i++){
    if(get_user(check_byteptr+i)==-1){
      exit(-1);
      return 0;
    }
  }
  return pagedir_get_page(thread_current()->pagedir, vaddr);
}

static int get_user (const uint8_t *uaddr){
 int result;
 asm ("movl $1f, %0; movzbl %1, %0; 1:"
      : "=&a" (result) : "m" (*uaddr));
 return result;
}