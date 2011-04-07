#include <stdint.h>
#include <stdlib.h>         /* malloc */

#include <nymt.h>           /* Public nymt header */
#include "pthreads_impl.h"  /* Internal pthread specific header */

nymt_thread_handle *      nymt_get_thread_handle(void)
{
  /* TBD: Basic array of free handles? use malloc? use passed allocator? */
  return (nymt_thread_handle *) malloc(sizeof(nymt_thread_handle));
}

nymt_thread_attributes *  nymt_get_thread_attributes(void)
{
  /* TBD: Basic array of free handles? use malloc? use passed allocator? */
  return (nymt_thread_attributes *) malloc(sizeof(nymt_thread_attributes));
}

void  nymt_free_thread_handle(nymt_thread_handle *handle)
{
  /* TBD: 'Free' up array etc.. */
  free(handle);
}

void  nymt_free_thread_attributes_handle(nymt_thread_attributes *attr)
{
  /* TBD: 'Free' up array entry etc.. */
  free(attr);
}

int nymt_thread_create(nymt_thread_handle * handle, nymt_thread_attributes * attr,
                       nymt_thread_start start, void * args)
{
  /* TBD: Map return value(s) somehow... */
  return pthread_create(NYMT_P_TO_PTHREAD_TP(handle), NYMT_P_TO_PTHREAD_ATTR_TP(attr), start, args);
}

int nymt_thread_detach(nymt_thread_handle * handle)
{
  return pthread_detach(NYMT_P_TO_PTHREAD_T(handle));
}
                       
int nymt_thread_join(nymt_thread_handle *handle, void ** ret)
{
  /* TBD: Map return values somehow... */
  return pthread_join(NYMT_P_TO_PTHREAD_T(handle), ret);
}

void nymt_thread_exit(void * ret)
{
  pthread_exit(ret);
}



