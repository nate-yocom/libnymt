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
  This is a simple test app 
 */

#include <stdio.h>
#include <stdlib.h>

#include <nymt.h>

void * print_test_message(void * arg)
{
  printf("Hello(%p)\n", arg);
  nymt_thread_exit(arg);
  return 0;  /* Unreachable code, compiler doesn't know that */
}

int global_num = 0;

void * sync_test_message(void * arg)
{
  int x = 0;
  nymt_mutex_handle * mutex = (nymt_mutex_handle *) arg;

  for(x = 0; x < 25; x++)
  {
    nymt_mutex_lock(mutex);
    printf("Hello: %d\n", global_num++);
    nymt_mutex_unlock(mutex);
  }
}

int main(int argc, char ** argv)
{
  nymt_thread_handle * thread_handle = 0;
  nymt_thread_handle * thread_handle2 = 0;
  nymt_mutex_handle * mutex_handle = 0;
  void * thread_result = 0;

  printf("libnymt version: 0x%08x = %d.%d.%d.%d\n", 
    nymt_version_number(), nymt_version_major(),
    nymt_version_minor(), nymt_version_build(),
    nymt_version_patch());

  thread_handle = nymt_get_thread_handle();
  int ret = nymt_thread_create(thread_handle, print_test_message, (void *) 0x42);
  printf("nymt_thread_create: %d\n", ret);
  ret = nymt_thread_join(thread_handle, &thread_result);
  printf("nymt_thread_join: %d\n", ret);
  printf("thread result: %p\n", thread_result);
  nymt_free_thread_handle(thread_handle);

  printf("Counting to 50 with 2 threads!\n");
  mutex_handle = nymt_get_mutex_handle();
  thread_handle = nymt_get_thread_handle();
  thread_handle2 = nymt_get_thread_handle();
  nymt_thread_create(thread_handle, sync_test_message, (void *) mutex_handle);
  nymt_thread_create(thread_handle2, sync_test_message, (void *) mutex_handle);
  nymt_thread_join(thread_handle, 0);
  nymt_thread_join(thread_handle2, 0);
  nymt_free_thread_handle(thread_handle);
  nymt_free_thread_handle(thread_handle2);
  nymt_free_mutex_handle(mutex_handle);

  
  return 0;
}
