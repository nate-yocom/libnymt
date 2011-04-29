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

/* 
  libnymt.h -> Public Header for the Multi Threading Library

  This libraries intent|goals:
    - Provide an extremely 'thin' (i.e. 1:1) wrapper for threading concepts
    - Be platform and architecture independant

  Currently, the library supports the following concepts:
    - Thread creation, attributes and joining
    - Thread cancellation
    - Mutex
    - Condition Variables

  We support the following platforms (with the noted underlying implementation):
    - *nix/Mac OS - via pthreads
    - Windows - via Win32 API (All flavors of windows)
*/

#ifndef __NYMT_INCLUDE_H__
#define __NYMT_INCLUDE_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

#define NYMT_VERSION_MAJOR 1
#define NYMT_VERSION_MINOR 0
#define NYMT_VERSION_BUILD 0
#define NYMT_VERSION_PATCH 0

/* Version is a 32 bit integer, 8 bits each for Major, Minor, Build, Patch */
#define NYMT_VERSION (NYMT_VERSION_MAJOR << 24 | \
                      NYMT_VERSION_MINOR << 16 | \
                      NYMT_VERSION_BUILD << 8  | \
                      NYMT_VERSION_PATCH << 0)

#define NYMT_SUCCESS  0 /* All other int return codes are errors */

uint32_t  nymt_version_number();
uint32_t  nymt_version_major();
uint32_t  nymt_version_minor();
uint32_t  nymt_version_build();
uint32_t  nymt_version_patch();

/* Opaque handle definitions */
typedef struct nymt_thread_handle nymt_thread_handle;
typedef struct nymt_mutex_handle nymt_mutex_handle;
typedef void * (*nymt_thread_start)(void *);

/* Handle factories */
nymt_thread_handle *      nymt_get_thread_handle(void);
nymt_mutex_handle *       nymt_get_mutex_handle(void);

/* Handle destruction */
void  nymt_free_thread_handle(nymt_thread_handle *);
void  nymt_free_mutex_handle(nymt_mutex_handle *);

/* Threads */
int   nymt_thread_create(nymt_thread_handle *, nymt_thread_start, void *);
int   nymt_thread_detach(nymt_thread_handle *);
int   nymt_thread_join(nymt_thread_handle *, void **);
void  nymt_thread_exit(void *);

/* Mutexes */
int   nymt_mutex_lock(nymt_mutex_handle *);
int   nymt_mutex_unlock(nymt_mutex_handle *);

#ifdef __cplusplus
}
#endif

#endif /* __NYMT_INCLUDE_H__ */
