# Copyright (c) 2013, Diego Souza
# All rights reserved.
#
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions
# are met:
#
# Redistributions of source code must retain the above copyright
# notice, this list of conditions and the following disclaimer.
#
# Redistributions in binary form must reproduce the above copyright
# notice, this list of conditions and the following disclaimer in the
# documentation and/or other materials provided with the
# distribution.
#
# Neither the name of the Diego Souza nor the names of its
# contributors may be used to endorse or promote products derived
# from this software without specific prior written permission.
#
# THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
# "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
# LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
# FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
# COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT,
# INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
# (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
# SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
# HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
# STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
# ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED
# OF THE POSSIBILITY OF SUCH DAMAGE.

project       = lift
srcroot       = $(CURDIR)

bin_find      = find
bin_unzip     = unzip

CFLAGS        = -Wall -Werror -pedantic -g
CXXFLAGS      = -Wall -g
_CFLAGS       = -std=c99 -I$(srcroot)/src
_CXXFLAGS     = -I$(srcroot)/src -I$(srcroot)/try -I$(srcroot)/tmp/UnitTest++/src

SRCFILES      = $(shell $(bin_find) $(srcroot)/src/lift -name \*.c -type f)
TRYFILES      = $(shell $(bin_find) $(srcroot)/try/lift_test -name \*.cc -type f)
S_OBJFILES    = $(subst .c,.o,$(SRCFILES))
T_OBJFILES    = $(subst .cc,.o,$(TRYFILES))

.bootstrap:
	if [ ! -f $(srcroot)/tmp/UnitTest++/libUnitTest++.a ];                        \
        then                                                                          \
          rm -r -f $(srcroot)/tmp;                                                    \
          mkdir $(srcroot)/tmp;                                                       \
          cd $(srcroot)/tmp && $(bin_unzip) -q $(srcroot)/lib/unittest-cpp-1.4.zip;   \
          $(MAKE) -C $(srcroot)/tmp/UnitTest++ libUnitTest++.a;                       \
        fi

test: compile
test: compile-test
test: try/run_tests
test:
	$(srcroot)/try/run_tests

compile: override CFLAGS  += $(_CFLAGS)
compile: $(S_OBJFILES)

compile-test: override CXXFLAGS += $(_CXXFLAGS)
compile-test: $(T_OBJFILES)

clean:
	$(bin_find) $(srcroot)/src -name \*.o -type f -exec rm -f \{\} \;
	$(bin_find) $(srcroot)/try -name \*.o -type f -exec rm -f \{\} \;
	rm -r -f tmp
	rm -f $(srcroot)/try/run_tests

try/run_tests: override CXXFLAGS += $(_CXXFLAGS)
try/run_tests: override LDFLAGS  += -L$(srcroot)/tmp/UnitTest++
try/run_tests: override LDLIBS   += -lUnitTest++
try/run_tests: $(S_OBJFILES) $(T_OBJFILES)
