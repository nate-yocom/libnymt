#include <stdint.h>
#include <stdlib.h>         /* malloc */

#include <nymt.h>           /* Public nymt header */
#include "pthreads_impl.h"  /* Internal pthread specific header */

static void * _nymt_pthread_proc(void * args)
{
  nymt_thread_handle * handle = (nymt_thread_handle *) args;
  handle->thread_start(handle->thread_args);
  return 0;
}

nymt_thread_handle * nymt_get_thread_handle(void)
{
  /* TBD: Basic array of free handles? use malloc? use passed allocator? */
  return (nymt_thread_handle *) malloc(sizeof(nymt_thread_handle));
}

void nymt_free_thread_handle(nymt_thread_handle *handle)
{
  free(handle);
}

int nymt_thread_create(nymt_thread_handle * handle, 
                       nymt_thread_start start, void * args)
{
  /* TBD: Map return value(s) somehow... */
  handle->thread_start = start;
  handle->thread_args = args;
  return pthread_create(&handle->thread_handle, 0, _nymt_pthread_proc, handle);
}

int nymt_thread_detach(nymt_thread_handle * handle)
{
  return pthread_detach(handle->thread_handle);
}
                       
int nymt_thread_join(nymt_thread_handle *handle)
{
  /* TBD: Map return values somehow... */
  return pthread_join(handle->thread_handle, NULL);
}

void nymt_thread_exit()
{
  pthread_exit(0);
}

nymt_mutex_handle * nymt_get_mutex_handle(void)
{
  /* TBD: Array/centralized/agnostic handout... */
  nymt_mutex_handle * handle = (nymt_mutex_handle *) malloc(sizeof(nymt_mutex_handle));
  pthread_mutex_init(&handle->mutex_handle, NULL);
  return handle;
}

void nymt_free_mutex_handle(nymt_mutex_handle *handle)
{
  pthread_mutex_destroy(&handle->mutex_handle);
  free(handle);
}

int nymt_mutex_lock(nymt_mutex_handle *handle)
{
  return pthread_mutex_lock(&handle->mutex_handle);
}

int nymt_mutex_unlock(nymt_mutex_handle *handle)
{
  return pthread_mutex_unlock(&handle->mutex_handle);
}


