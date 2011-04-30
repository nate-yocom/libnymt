#include <nymt.h>        /* Public nymt header */
#include "win32_impl.h"  /* Internal win32 specific header */

static DWORD WINAPI _nymt_win32_thread_proc(LPVOID lpParameter)
{
  nymt_thread_handle * handle = (nymt_thread_handle *) lpParameter;
  handle->thread_proc(handle->thread_args);
  return 0;
}

nymt_thread_handle * nymt_get_thread_handle(void)
{
  /* TBD: Basic array of free handles? use malloc? use passed allocator? */
  return (nymt_thread_handle *) malloc(sizeof(nymt_thread_handle));
}

void nymt_free_thread_handle(nymt_thread_handle *handle)
{
  CloseHandle(handle->thread_handle);
  free(handle);
}

int nymt_thread_create(nymt_thread_handle * handle, 
                       nymt_thread_start start, void * args)
{
  /* TBD: Map return value(s) somehow... */
  handle->thread_proc = start;
  handle->thread_args = args;
  handle->thread_handle = CreateThread(NULL, 0, _nymt_win32_thread_proc, handle, 0, 0);
  /* TBD: Check for failure! CreateThread returns null... */
  return NYMT_SUCCESS;
}

int nymt_thread_detach(nymt_thread_handle * handle)
{
  if(CloseHandle(handle->thread_handle))
    return NYMT_SUCCESS;
  else
    return -1;  /* TBD: Work out error codes... */
}
                       
int nymt_thread_join(nymt_thread_handle *handle)
{
  /* TBD: Map return values somehow... */
  return WaitForSingleObject(handle->thread_handle, INFINITE);
}

void nymt_thread_exit()
{
  ExitThread(0);
}

nymt_mutex_handle * nymt_get_mutex_handle(void)
{
  /* TBD: Array/centralized/agnostic handout... */
  nymt_mutex_handle * handle = (nymt_mutex_handle *) malloc(sizeof(nymt_mutex_handle));
  handle->mutex_handle = CreateMutex(NULL, FALSE, NULL);
  return handle;
}

void nymt_free_mutex_handle(nymt_mutex_handle *handle)
{
  CloseHandle(handle->mutex_handle);
  free(handle);
}

int nymt_mutex_lock(nymt_mutex_handle *handle)
{
  DWORD res = WaitForSingleObject(handle->mutex_handle, INFINITE);
  if(res == WAIT_OBJECT_0 || res == WAIT_ABANDONED)
    return NYMT_SUCCESS;
  
  return res;
}

int nymt_mutex_unlock(nymt_mutex_handle *handle)
{
  if(ReleaseMutex(handle->mutex_handle))
    return NYMT_SUCCESS;

  return -1;
}


