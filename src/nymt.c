#include <nymt.h>

uint32_t  nymt_version_number()
{
  return NYMT_VERSION;
}

uint32_t  nymt_version_major()
{
  return (NYMT_VERSION >> 24 & 0x000000FF);
}

uint32_t  nymt_version_minor()
{
  return (NYMT_VERSION >> 16 & 0x000000FF);
}

uint32_t  nymt_version_build()
{
  return (NYMT_VERSION >> 8 & 0x000000FF);
}

uint32_t  nymt_version_patch()
{
  return (NYMT_VERSION & 0x000000FF);
}
