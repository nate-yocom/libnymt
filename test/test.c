#include <stdio.h>
#include <stdlib.h>

#include <nymt.h>

void * print_test_message(void * arg)
{
  printf("Hello(%p)\n", arg);
  nymt_thread_exit(arg);
  return 0;  /* Unreachable code, compiler doesn't know that */
}

int main(int argc, char ** argv)
{
  nymt_thread_handle * thread_handle = 0;
  nymt_thread_attributes * thread_attr_handle = 0;
  void * thread_result = 0;

  printf("libnymt version: 0x%08x = %d.%d.%d.%d\n", 
    nymt_version_number(), nymt_version_major(),
    nymt_version_minor(), nymt_version_build(),
    nymt_version_patch());

  thread_handle = nymt_get_thread_handle();
  int ret = nymt_thread_create(thread_handle, thread_attr_handle, print_test_message, 0x42);
  ret = nymt_thread_join(thread_handle, &thread_result);
  printf("thread result: %p\n", thread_result);

  return 0;
}
