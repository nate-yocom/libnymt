#include <stdio.h>
#include <stdlib.h>

#include <nymt.h>

int main(int argc, char ** argv)
{
  printf("libnymt version: %d:0x%08x\n", nymt_version_number(), nymt_version_number());
  return 0;
}
