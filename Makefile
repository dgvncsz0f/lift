# Copyright (c) 2011, Diego Souza
# All rights reserved.
#
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions are met:
#
#   * Redistributions of source code must retain the above copyright notice,
#     this list of conditions and the following disclaimer.
#   * Redistributions in binary form must reproduce the above copyright notice,
#     this list of conditions and the following disclaimer in the documentation
#     and/or other materials provided with the distribution.
#   * Neither the name of the <ORGANIZATION> nor the names of its contributors
#     may be used to endorse or promote products derived from this software
#     without specific prior written permission.
#
# THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
# ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
# WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
# DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
# FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
# DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
# SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
# CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
# OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
# OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH Copyright.

include Makefile.vars

INC_FILES = $(wildcard src/main/lift/*.h) $(wildcard src/main/lift/algo/*.h) 
SRC_FILES = $(wildcard src/main/lift/*.c) $(wildcard src/main/lift/algo/*.c)
OBJ_FILES = $(addsuffix .o, $(basename $(SRC_FILES)))

INC_FILES_TEST = $(wildcard src/test/lift_test/*.hh) $(wildcard src/test/lift_test/algo/*.hh)
SRC_FILES_TEST = $(wildcard src/test/lift_test/*.cc) $(wildcard src/test/lift_test/algo/*.cc)
OBJ_FILES_TEST = $(addsuffix .o, $(basename $(SRC_FILES_TEST)))

PRG_TESTS = run_tests
DLIB_LIFT = liblift.so
SLIB_LIFT = liblift.a

DIST = $(CURDIR)/dist

override CXXFLAGS += -W -Wall -pedantic -Isrc/main -Isrc/test
override CFLAGS   += -W -Wall -pedantic -Isrc/main -fPIC
override LDFLAGS  += 

compile: $(OBJ_FILES)

ctags: 

build: build-dynamic build-static

build-dynamic:
	$(MAKE) __build_dynamic

build-static:
	$(MAKE) __build_static

tests:
	$(MAKE) __build_test
	/usr/bin/env MALLOC_CHECK_=3 $(DIST)/bin/$(PRG_TESTS)

ifneq (($BIN_VALGRIND),)
tests-valgrind:
	$(MAKE) "CXXFLAGS=$(CXXFLAGS) -g" __build_test
	$(BIN_VALGRIND) $(VALGRINDFLAGS) $(DIST)/bin/$(PRG_TESTS)
endif

ifeq ($(BIN_FIND),)
clean:
	rm -f $(OBJ_FILES) $(OBJ_FILES_TEST)
	rm -rf $(DIST)
else
clean:
	$(BIN_FIND) . -name \*.o -exec rm -f \{\} \;
	$(BIN_FIND) . -name \*.gcno -exec rm -f \{\} \;
	$(BIN_FIND) . -name \*.gcda -exec rm -f \{\} \;
	rm -rf $(DIST)
endif

%/$(PRG_TESTS): src/test/run_tests.cc $(OBJ_FILES_TEST)
	$(BIN_TEST) -d $(dir $(@)) || mkdir -p $(dir $(@))
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -o $(@) $(^) $(LDFLAGS)

%/$(DLIB_LIFT): $(OBJ_FILES)
	$(BIN_TEST) -d $(dir $(@)) || mkdir -p $(dir $(@))
	$(CC) -o $(@) $(^) $(LDFLAGS)

%/$(SLIB_LIFT): $(OBJ_FILES)
	$(BIN_TEST) -d $(dir $(@)) || mkdir -p $(dir $(@))
	$(MAKE) "$(@)($(OBJ_FILES))"

%.cc: %.hh
	$(BIN_TOUCH) $(@)

%.c: %.h
	$(BIN_TOUCH) $(@)

__build_dynamic: override LDFLAGS += -Wl,-soname,$(DLIB_LIFT) -shared
__build_dynamic: $(DIST)/lib/$(DLIB_LIFT)

__build_static: $(DIST)/lib/$(SLIB_LIFT)

__build_test: CPPFLAGS += -I/usr/include/unittest++
__build_test: LDFLAGS  += -L$(DIST)/lib -llift -lUnitTest++ -Wl,-rpath,$(DIST)/lib
__build_test: build $(DIST)/bin/$(PRG_TESTS)
