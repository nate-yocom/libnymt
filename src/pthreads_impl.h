/*
  libnymt - Multi Threading Library
 
  Copyright (c) 2011, Nathan Yocom (nate@yocom.org)
  All rights reserved.

  Redistribution and use in source and binary forms, with or without modification, 
  are permitted provided that the following conditions are met:

    - Redistributions of source code must retain the above copyright notice, this 
      list of conditions and the following disclaimer.
    - Redistributions in binary form must reproduce the above copyright notice, 
      this list of conditions and the following disclaimer in the documentation 
      and/or other materials provided with the distribution.

  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY 
  EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES 
  OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT 
  SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, 
  INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED 
  TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR 
  BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN 
  CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN 
  ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH 
  DAMAGE.
*/

/* pthread implementation header */

#ifndef __NYMT_PTHREADS_IMPL_H__
#define __NYMT_PTHREADS_IMPL_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <pthread.h>

/* Impl must define nymt_thread_handle and nymt_thread_attributes */
struct nymt_thread_handle
{
  pthread_t thread_handle;
  nymt_thread_start thread_start;
  void * thread_args;
};

struct nymt_mutex_handle
{
  pthread_mutex_t mutex_handle;
};

#ifdef __cplusplus
}
#endif
#endif /* __NYMT_PTHREADS_IMPL_H__ */
