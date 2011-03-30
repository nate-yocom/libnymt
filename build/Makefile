CC = gcc
vpath %.c src

# First set CPU_ARCH, defaults to 32 bit
ifneq ($(ARCH),)
CPU_ARCH=$(ARCH)
else
CPU_ARCH=32
endif

# Now build CFLAGS, first is the stuff all flavors get:
BASE_CFLAGS=-c -Wall -I. -Iinclude/

# Now set CFLAGS as base + debug|release specifics
# Default is RELEASE x86
ifneq ($(DEBUG),)
CFLAGS = $(BASE_CFLAGS) -m$(CPU_ARCH) -g -O0 -DDEBUG
else
CFLAGS = $(BASE_CFLAGS) -m$(CPU_ARCH) -O2 -DRELEASE
endif

ifeq ($(CPU_ARCH),64)
ARCH_DIR=x64
else
ARCH_DIR=x86
endif

SOURCES=nymt.c
OBJECTS=$(SOURCES:.c=.o)
LIBDIR=lib/$(ARCH_DIR)
LIB=$(LIBDIR)/libnymt.a

all: dirs $(SOURCES) $(LIB)

dirs:
	mkdir -p $(LIBDIR)

$(LIB): $(OBJECTS)
	ar rcs $(LIB) $(OBJECTS) 	

.c.o:
	$(CC) $(CFLAGS) $< -o $@

.PHONY: clean dirs
clean:
	rm -f *.o
	rm -rf $(LIBDIR)
