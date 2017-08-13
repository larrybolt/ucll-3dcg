CC=g++
COMMONFLAGS=-I. -std=c++14 -pthread -DELPP_CUSTOM_OUT=std::cerr -DELPP_THREAD_SAFE
DEBUG_FLAGS=$(COMMONFLAGS) -g -ort-debug -Wall -Wextra

UNAME := $(shell uname -o)
ifeq ($(UNAME),Cygwin)
	DEBUG_FLAGS += -O1
else
	DEBUG_FLAGS += -O0
endif

RELEASE_FLAGS=$(COMMONFLAGS) -DNDEBUG -O3 -s -ort-release
TEST_FLAGS=$(DEBUG_FLAGS) -DTEST_BUILD -ort-test
NO_SCRIPTING_FLAGS=-DEXCLUDE_SCRIPTING

FILES=`find -type f -name "*.cpp"`

all: debug_build release_build test_build

debug_build:
	$(CC) $(DEBUG_FLAGS) $(FILES) -ldl

release_build:
	$(CC) $(RELEASE_FLAGS) $(FILES) -ldl

test_build:
	$(CC) $(TEST_FLAGS) $(FILES) -ldl

debug_no_scripting_build:
	$(CC) $(DEBUG_FLAGS) $(NO_SCRIPTING_FLAGS) $(FILES) -ldl

release_no_scripting_build:
	$(CC) $(RELEASE_FLAGS) $(NO_SCRIPTING_FLAGS) $(FILES) -ldl

test_no_scripting_build:
	$(CC) $(TEST_FLAGS) $(NO_SCRIPTING_FLAGS) $(FILES) -ldl

d: debug_build
r: release_build
t: test_build
dn: debug_no_scripting_build
rn: release_no_scripting_build
tn: test_no_scripting_build
