#include <stdio.h>
#include <stdlib.h>

#include <nymt.h>

int main(int argc, char ** argv)
{
  printf("libnymt version: 0x%08x = %d.%d.%d.%d\n", 
    nymt_version_number(), nymt_version_major(),
    nymt_version_minor(), nymt_version_build(),
    nymt_version_patch());
  return 0;
}
