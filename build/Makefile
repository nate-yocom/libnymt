# *nix and Mac Makefile - builds libnymt with underlying pthread
# implementation.  Set the following env variables to change build
# settings:
#   ARCH=32|64
#   DEBUG=1 (omit for release build)

CC = gcc
vpath %.c src:test

# First set CPU_ARCH, defaults to 32 bit
ifneq ($(ARCH),)
CPU_ARCH=$(ARCH)
else
CPU_ARCH=32
endif

# Now build CFLAGS, first is the stuff all flavors get:
BASE_CFLAGS=-DPTHREAD_IMPL -c -Wall -I. -Iinclude/

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

BUILD_DIR=build/$(ARCH_DIR)

LIB_SOURCES=nymt.c pthreads_impl.c
LIB_OBJECTS=$(LIB_SOURCES:.c=.o)
LIB_DIR=lib/$(ARCH_DIR)
LIB_NAME=libnymt.a
LIB=$(LIB_DIR)/$(LIB_NAME)

BIN_DIR=bin/$(ARCH_DIR)
TEST_SOURCES=test.c
TEST_OBJECTS=$(TEST_SOURCES:.c=.o)
TEST_NAME=test
TEST_APP=$(BIN_DIR)/$(TEST_NAME)

# Note that we -L. and link the libnymt.a in the build dir
LDFLAGS=-L. -lnymt -m$(CPU_ARCH) -lpthread

.PHONY: clean dirs 

all: dirs $(LIB_SOURCES) $(LIB) $(TEST_SOURCES) $(TEST_APP)

dirs:
	mkdir -p $(LIB_DIR)
	mkdir -p $(BIN_DIR)
	mkdir -p build/$(ARCH_DIR)

$(LIB): $(LIB_OBJECTS)
	cd $(BUILD_DIR) && ar rcs $(LIB_NAME) $(LIB_OBJECTS)
	cp -f $(BUILD_DIR)/$(LIB_NAME) $(LIB)

$(TEST_APP): $(TEST_OBJECTS)
	cd $(BUILD_DIR) && $(CC) $(LDFLAGS) $(TEST_OBJECTS) -o $(TEST_NAME)
	cp -f $(BUILD_DIR)/$(TEST_NAME) $(TEST_APP)

.c.o:
	$(CC) $(CFLAGS) $< -o build/$(ARCH_DIR)/$@

clean:
	rm -rf lib/
	rm -rf bin/
	rm -rf build/x86
	rm -rf build/x64

