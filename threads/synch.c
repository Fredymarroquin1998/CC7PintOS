/* This file is derived from source code for the Nachos
   instructional operating system.  The Nachos copyright notice
   is reproduced in full below. */

/* Copyright (c) 1992-1996 The Regents of the University of California.
   All rights reserved.

   Permission to use, copy, modify, and distribute this software
   and its documentation for any purpose, without fee, and
   without written agreement is hereby granted, provided that the
   above copyright notice and the following two paragraphs appear
   in all copies of this software.

   IN NO EVENT SHALL THE UNIVERSITY OF CALIFORNIA BE LIABLE TO
   ANY PARTY FOR DIRECT, INDIRECT, SPECIAL, INCIDENTAL, OR
   CONSEQUENTIAL DAMAGES ARISING OUT OF THE USE OF THIS SOFTWARE
   AND ITS DOCUMENTATION, EVEN IF THE UNIVERSITY OF CALIFORNIA
   HAS BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

   THE UNIVERSITY OF CALIFORNIA SPECIFICALLY DISCLAIMS ANY
   WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
   WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
   PURPOSE.  THE SOFTWARE PROVIDED HEREUNDER IS ON AN "AS IS"
   BASIS, AND THE UNIVERSITY OF CALIFORNIA HAS NO OBLIGATION TO
   PROVIDE MAINTENANCE, SUPPORT, UPDATES, ENHANCEMENTS, OR
   MODIFICATIONS.
*/

#include "threads/synch.h"
#include <stdio.h>
#include <string.h>
#include "threads/interrupt.h"
#include "threads/thread.h"

/* Initializes semaphore SEMA to VALUE.  A semaphore is a
   nonnegative integer along with two atomic operators for
   manipulating it:

   - down or "P": wait for the value to become positive, then
     decrement it.

   - up or "V": increment the value (and wake up one waiting
     thread, if any). */
void
sema_init (struct semaphore *sema, unsigned value) 
{
  ASSERT (sema != NULL);

  sema->value = value;
  list_init (&sema->waiters);
}


bool ordenar_prioridad(struct list_elem *a,struct list_elem *b){
  struct thread *a_elem;
  struct thread *b_elem;

  a_elem=list_entry(a,struct thread,elem);
  b_elem=list_entry(b,struct thread,elem);
  return (a_elem->priority) > (b_elem->priority);
}

bool prioridad_baja(struct list_elem *a,struct list_elem *b){
  struct thread *a_elem;
  struct thread *b_elem;

  a_elem=list_entry(a,struct thread,elem);
  b_elem=list_entry(b,struct thread,elem);
  return (a_elem->priority) <= (b_elem->priority);
}

/* Down or "P" operation on a semaphore.  Waits for SEMA's value
   to become positive and then atomically decrements it.

   This function may sleep, so it must not be called within an
   interrupt handler.  This function may be called with
   interrupts disabled, but if it sleeps then the next scheduled
   thread will probably turn interrupts back on. */
void
sema_down (struct semaphore *sema) 
{
  enum intr_level old_level;

  ASSERT (sema != NULL);
  ASSERT (!intr_context ());

  old_level = intr_disable ();
  while (sema->value == 0) 
  {

    if (!thread_mlfqs){
      //donar prioridad
      int aux = 0;
      struct thread *t=thread_current();
      struct lock *l=t -> esta_en_lock;

      while (l && aux < 8) {  //mientras se este en lock
        aux++;
        if (l -> holder != NULL && (l -> holder -> priority) < t -> priority) { //si existe holder y la prioridad del holder es menor a la prioridad del thread actual
          l -> holder -> priority = t -> priority;  //asignamos prioridad thread_actual->holder
          l = t -> esta_en_lock;  //mantenemos el lock
        }
      }
    }

    list_insert_ordered(&sema -> waiters, &thread_current() -> elem,(list_less_func*) &ordenar_prioridad, NULL);//insertar ordenada el semaforo

    thread_block(); 
  }
  sema->value--;
  intr_set_level (old_level);
}

/* Down or "P" operation on a semaphore, but only if the
   semaphore is not already 0.  Returns true if the semaphore is
   decremented, false otherwise.

   This function may be called from an interrupt handler. */
bool
sema_try_down (struct semaphore *sema) 
{
  enum intr_level old_level;
  bool success;

  ASSERT (sema != NULL);

  old_level = intr_disable ();
  if (sema->value > 0) 
    {
      sema->value--;
      success = true; 
    }
  else
    success = false;
  intr_set_level (old_level);

  return success;
}

/* Up or "V" operation on a semaphore.  Increments SEMA's value
   and wakes up one thread of those waiting for SEMA, if any.

   This function may be called from an interrupt handler. */
void
sema_up (struct semaphore *sema) 
{
  enum intr_level old_level;

  ASSERT (sema != NULL);

  old_level = intr_disable ();
  if (!list_empty (&sema->waiters)){  //si la lista no esta vacia
    list_sort(&sema->waiters, (list_less_func*)ordenar_prioridad, NULL); //ordenamos de forma descendente por prioridad
    thread_unblock (list_entry (list_pop_front (&sema->waiters),struct thread, elem));  //desbloqueamos el primer thread en la lista
  }
  sema->value++;

  if(!intr_context()){
    sema_upVer();
  }

  intr_set_level (old_level);
}

static void sema_test_helper (void *sema_);

/* Self-test for semaphores that makes control "ping-pong"
   between a pair of threads.  Insert calls to printf() to see
   what's going on. */
void
sema_self_test (void) 
{
  struct semaphore sema[2];
  int i;

  printf ("Testing semaphores...");
  sema_init (&sema[0], 0);
  sema_init (&sema[1], 0);
  thread_create ("sema-test", PRI_DEFAULT, sema_test_helper, &sema);
  for (i = 0; i < 10; i++) 
    {
      sema_up (&sema[0]);
      sema_down (&sema[1]);
    }
  printf ("done.\n");
}

/* Thread function used by sema_self_test(). */
static void
sema_test_helper (void *sema_) 
{
  struct semaphore *sema = sema_;
  int i;

  for (i = 0; i < 10; i++) 
    {
      sema_down (&sema[0]);
      sema_up (&sema[1]);
    }
}

/* Initializes LOCK.  A lock can be held by at most a single
   thread at any given time.  Our locks are not "recursive", that
   is, it is an error for the thread currently holding a lock to
   try to acquire that lock.

   A lock is a specialization of a semaphore with an initial
   value of 1.  The difference between a lock and such a
   semaphore is twofold.  First, a semaphore can have a value
   greater than 1, but a lock can only be owned by a single
   thread at a time.  Second, a semaphore does not have an owner,
   meaning that one thread can "down" the semaphore and then
   another one "up" it, but with a lock the same thread must both
   acquire and release it.  When these restrictions prove
   onerous, it's a good sign that a semaphore should be used,
   instead of a lock. */
void
lock_init (struct lock *lock)
{
  ASSERT (lock != NULL);

  lock->holder = NULL;
  sema_init (&lock->semaphore, 1);  
}

/* Acquires LOCK, sleeping until it becomes available if
   necessary.  The lock must not already be held by the current
   thread.

   This function may sleep, so it must not be called within an
   interrupt handler.  This function may be called with
   interrupts disabled, but interrupts will be turned back on if
   we need to sleep. */




void
lock_acquire (struct lock *lock)
{
  ASSERT (lock != NULL);
  ASSERT (!intr_context ());
  ASSERT (!lock_held_by_current_thread (lock));

  enum intr_level old_level;
  old_level = intr_disable(); //desactivamos interrupciones

  //struct thread *t = thread_current ();
  if(!thread_mlfqs && lock->holder ){ //si no se usa mlfqs y esta bloqueado el holder
    thread_current ()->esta_en_lock = lock; //ahora obtenemos el lock
    list_insert_ordered(&lock->holder->cola_de_lock, &thread_current ()->elementos_de_lista_locks,(list_less_func *)&ordenar_prioridad,NULL); //agregamos de forma descendente
  }
  sema_down (&lock->semaphore);
  thread_current() -> esta_en_lock = NULL;  //se restaura el thread actual
  lock -> holder = thread_current();  //ahora el thread actual es el holder
  intr_set_level(old_level);  //restauramos el estado
}



/* Tries to acquires LOCK and returns true if successful or false
   on failure.  The lock must not already be held by the current
   thread.

   This function will not sleep, so it may be called within an
   interrupt handler. */
bool
lock_try_acquire (struct lock *lock)
{
  bool success;

  ASSERT (lock != NULL);
  ASSERT (!lock_held_by_current_thread (lock));

  enum intr_level old_level;
  old_level = intr_disable(); //desactivamos interrupciones

  success = sema_try_down (&lock->semaphore); 
  if (success) {  //fue exitoso?
    thread_current() -> esta_en_lock = NULL;  //restauramos el lock del thread
    lock->holder = thread_current (); //el holder es el thread actual
  }
  
  intr_set_level(old_level);  //restauramos el estado
  /* My Code Ends */
  
  return success;
}

/* Releases LOCK, which must be owned by the current thread.

   An interrupt handler cannot acquire a lock, so it does not
   make sense to try to release a lock within an interrupt
   handler. */
void
lock_release (struct lock *lock) 
{
  ASSERT (lock != NULL);
  ASSERT (lock_held_by_current_thread (lock));

  enum intr_level old_level;
  old_level = intr_disable(); //deshabilitamos interrupciones

  lock -> holder = NULL; //restauramos el holder
  if(!thread_mlfqs){  //si no se usa mlfqs
    lock_remove(lock); //removemos el lock
    //hacemos update de la prioridad 
    struct thread *t_actual = thread_current(); // thread actual
    struct thread *t_nuevo; //nuevo thread
    t_actual -> priority = t_actual -> init_priority; //la prioridad del thread actual es igual a la prioridad inicial
    if (!list_empty(&t_actual -> cola_de_lock)) {
      t_nuevo = list_entry(list_front(&t_actual -> cola_de_lock), struct thread, elementos_de_lista_locks);//thread nuevo es el primero de la lista
      if ((t_nuevo -> priority) > (t_actual -> priority)) //si el thread nuevo es mayor al actual
        t_actual -> priority = t_nuevo -> priority; //el thread actual toma la prioridad nueva
    }
  }
  
  sema_up(&lock -> semaphore);  //lo modificamos
  intr_set_level(old_level);  //restauramos el estado
}

void lock_remove (struct lock *lock)  
{
  struct list_elem *e;
  struct thread *t;
  for(e=list_begin(&thread_current()->cola_de_lock);e!=list_end(&thread_current()->cola_de_lock);e=list_next(e)){ 
    t = list_entry(e, struct thread, elementos_de_lista_locks);    
    if (t -> esta_en_lock == lock){
      list_remove(e);
    }
  }
}


/* Returns true if the current thread holds LOCK, false
   otherwise.  (Note that testing whether some other thread holds
   a lock would be racy.) */
bool
lock_held_by_current_thread (const struct lock *lock) 
{
  ASSERT (lock != NULL);

  return lock->holder == thread_current ();
}

/* One semaphore in a list. */
struct semaphore_elem 
  {
    struct list_elem elem;              /* List element. */
    struct semaphore semaphore;         /* This semaphore. */
  };

/* Initializes condition variable COND.  A condition variable
   allows one piece of code to signal a condition and cooperating
   code to receive the signal and act upon it. */
void
cond_init (struct condition *cond)
{
  ASSERT (cond != NULL);

  list_init (&cond->waiters);
}

/* Atomically releases LOCK and waits for COND to be signaled by
   some other piece of code.  After COND is signaled, LOCK is
   reacquired before returning.  LOCK must be held before calling
   this function.

   The monitor implemented by this function is "Mesa" style, not
   "Hoare" style, that is, sending and receiving a signal are not
   an atomic operation.  Thus, typically the caller must recheck
   the condition after the wait completes and, if necessary, wait
   again.

   A given condition variable is associated with only a single
   lock, but one lock may be associated with any number of
   condition variables.  That is, there is a one-to-many mapping
   from locks to condition variables.

   This function may sleep, so it must not be called within an
   interrupt handler.  This function may be called with
   interrupts disabled, but interrupts will be turned back on if
   we need to sleep. */

bool change_sem_priority (const struct list_elem *a, const struct list_elem *b, void *aux UNUSED) 
{
  struct semaphore_elem *sa = list_entry(a, struct semaphore_elem, elem);
  struct semaphore_elem *sb = list_entry(b, struct semaphore_elem, elem);

  if (list_empty(&sb -> semaphore.waiters))
    return true;
  if (list_empty(&sa -> semaphore.waiters))
    return false;
  //ordenamos las listas de forma descendente
  list_sort(&sa -> semaphore.waiters,(list_less_func*) ordenar_prioridad, NULL);
  list_sort(&sb -> semaphore.waiters,(list_less_func*) ordenar_prioridad, NULL);
  //agregamos el thread de mayor prioridad a cada lista
  struct thread *ta = list_entry(list_front(&sa -> semaphore.waiters), struct thread, elem);
  struct thread *tb = list_entry(list_front(&sb -> semaphore.waiters), struct thread, elem);

  return((ta -> priority) > (tb -> priority));
}

void
cond_wait (struct condition *cond, struct lock *lock) 
{
  struct semaphore_elem waiter;

  ASSERT (cond != NULL);
  ASSERT (lock != NULL);
  ASSERT (!intr_context ());
  ASSERT (lock_held_by_current_thread (lock));
  
  sema_init (&waiter.semaphore, 0);
  //list_push_back (&cond->waiters, &waiter.elem);
  list_insert_ordered(&cond->waiters, &waiter.elem, change_sem_priority, NULL);
  lock_release (lock);
  sema_down (&waiter.semaphore);
  lock_acquire (lock);
}

/* If any threads are waiting on COND (protected by LOCK), then
   this function signals one of them to wake up from its wait.
   LOCK must be held before calling this function.

   An interrupt handler cannot acquire a lock, so it does not
   make sense to try to signal a condition variable within an
   interrupt handler. */
void
cond_signal (struct condition *cond, struct lock *lock UNUSED) 
{
  ASSERT (cond != NULL);
  ASSERT (lock != NULL);
  ASSERT (!intr_context ());
  ASSERT (lock_held_by_current_thread (lock));

  if (list_empty (&cond->waiters)) {
    return;
  }else{
    list_sort(&cond -> waiters,change_sem_priority, NULL); //ordenamos de forma descendente
    sema_up (&list_entry (list_pop_front (&cond->waiters),struct semaphore_elem, elem)->semaphore);//levantmos el semaforo
  }
}



/* Wakes up all threads, if any, waiting on COND (protected by
   LOCK).  LOCK must be held before calling this function.

   An interrupt handler cannot acquire a lock, so it does not
   make sense to try to signal a condition variable within an
   interrupt handler. */
void
cond_broadcast (struct condition *cond, struct lock *lock) 
{
  ASSERT (cond != NULL);
  ASSERT (lock != NULL);

  while (!list_empty (&cond->waiters))
    cond_signal (cond, lock);
}
