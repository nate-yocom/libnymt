#include <stdint.h>
#include <stdlib.h>         /* malloc */

#include <nymt.h>           /* Public nymt header */
#include "pthreads_impl.h"  /* Internal pthread specific header */

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
  return pthread_create(&handle->thread_handle, 0, start, args);
}

int nymt_thread_detach(nymt_thread_handle * handle)
{
  return pthread_detach(handle->thread_handle);
}
                       
int nymt_thread_join(nymt_thread_handle *handle, void ** ret)
{
  /* TBD: Map return values somehow... */
  return pthread_join(handle->thread_handle, ret);
}

void nymt_thread_exit(void * ret)
{
  pthread_exit(ret);
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


