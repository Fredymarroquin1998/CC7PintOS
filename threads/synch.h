#ifndef THREADS_SYNCH_H
#define THREADS_SYNCH_H

#include <list.h>
#include <stdbool.h>

/* A counting semaphore. */
struct semaphore 
  {
    unsigned value;             /* Current value. */
    struct list waiters;        /* List of waiting threads. */
  };

void sema_init (struct semaphore *, unsigned value);
void sema_down (struct semaphore *);
bool sema_try_down (struct semaphore *);
void sema_up (struct semaphore *);
void sema_self_test (void);

/* Lock. */
struct lock 
  {
    struct thread *holder;      /* Thread holding lock (for debugging). */
    struct semaphore semaphore; /* Binary semaphore controlling access. */
  };

void donate_priority(void); //donar prioridad
bool ordenar_prioridad(struct list_elem *a,struct list_elem *b); //ordenar con forme a prioridad

void lock_init (struct lock *);
void lock_acquire (struct lock *); //lock acquire
bool lock_try_acquire (struct lock *);
void lock_release (struct lock *); //lock release
bool lock_held_by_current_thread (const struct lock *);

bool change_sem_priority (const struct list_elem *a, const struct list_elem *b, void *aux );
bool change_priority (const struct list_elem *a, const struct list_elem *b, void *aux );

/* Condition variable. */
struct condition 
  {
    struct list waiters;        /* List of waiting threads. */
  };

void cond_init (struct condition *);
void cond_wait (struct condition *, struct lock *);
void cond_signal (struct condition *, struct lock *);
void cond_broadcast (struct condition *, struct lock *);
void update_priority (void);
void lock_remove (struct lock *lock); //remover locks
/* Optimization barrier.

   The compiler will not reorder operations across an
   optimization barrier.  See "Optimization Barriers" in the
   reference guide for more information.*/


bool prioridad_baja(struct list_elem *a,struct list_elem *b);
#define barrier() asm volatile ("" : : : "memory")

#endif /* threads/synch.h */
