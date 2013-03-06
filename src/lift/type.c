// Copyright (c) 2013, Diego Souza
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions
// are met:
//
// Redistributions of source code must retain the above copyright
// notice, this list of conditions and the following disclaimer.
//
// Redistributions in binary form must reproduce the above copyright
// notice, this list of conditions and the following disclaimer in the
// documentation and/or other materials provided with the
// distribution.
//
// Neither the name of the Diego Souza nor the names of its
// contributors may be used to endorse or promote products derived
// from this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
// "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
// LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
// FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
// COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT,
// INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
// (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
// SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
// HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
// STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
// ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED
// OF THE POSSIBILITY OF SUCH DAMAGE.

#include <string.h>
#include "lift/type.h"

static
ord_e __compare_char(const type_t *t, const void *a, const void *b)
{ return(LIFT_COMPARE(char *, a, b)); }

static
size_t __sizeof_char(const type_t *t, const void *a)
{ return(LIFT_SIZEOF(char)); }

static
ord_e __compare_int(const type_t *t, const void *a, const void *b)
{ return(LIFT_COMPARE(int *, a, b)); }

static
size_t __sizeof_int(const type_t *t, const void *a)
{ return(LIFT_SIZEOF(int)); }

static
ord_e __compare_uint8(const type_t *t, const void *a, const void *b)
{ return(LIFT_COMPARE(uint8_t *, a, b)); }

static
size_t __sizeof_uint8(const type_t *t, const void *a)
{ return(LIFT_SIZEOF(uint8_t)); }

static
ord_e __compare_uint16(const type_t *t, const void *a, const void *b)
{ return(LIFT_COMPARE(uint16_t *, a, b)); }

static
size_t __sizeof_uint16(const type_t *t, const void *a)
{ return(LIFT_SIZEOF(uint16_t)); }

static
ord_e __compare_uint32(const type_t *t, const void *a, const void *b)
{ return(LIFT_COMPARE(uint32_t *, a, b)); }

static
size_t __sizeof_uint32(const type_t *t, const void *a)
{ return(LIFT_SIZEOF(uint32_t)); }

static
ord_e __compare_uint64(const type_t *t, const void *a, const void *b)
{ return(LIFT_COMPARE(uint64_t *, a, b)); }

static
size_t __sizeof_uint64(const type_t *t, const void *a)
{ return(LIFT_SIZEOF(uint64_t)); }

static
ord_e __compare_int8(const type_t *t, const void *a, const void *b)
{ return(LIFT_COMPARE(int8_t *, a, b)); }

static
size_t __sizeof_int8(const type_t *t, const void *a)
{ return(LIFT_SIZEOF(int8_t)); }

static
ord_e __compare_int16(const type_t *t, const void *a, const void *b)
{ return(LIFT_COMPARE(int16_t *, a, b)); }

static
size_t __sizeof_int16(const type_t *t, const void *a)
{ return(LIFT_SIZEOF(int16_t)); }

static
ord_e __compare_int32(const type_t *t, const void *a, const void *b)
{ return(LIFT_COMPARE(int32_t *, a, b)); }

static
size_t __sizeof_int32(const type_t *t, const void *a)
{ return(LIFT_SIZEOF(int32_t)); }

static
ord_e __compare_int64(const type_t *t, const void *a, const void *b)
{ return(LIFT_COMPARE(int64_t *, a, b)); }

static
size_t __sizeof_int64(const type_t *t, const void *a)
{ return(LIFT_SIZEOF(int64_t)); }

static
ord_e __compare_float(const type_t *t, const void *a, const void *b)
{ return(LIFT_COMPARE(float *, a, b)); }

static
size_t __sizeof_float(const type_t *t, const void *a)
{ return(LIFT_SIZEOF(float)); }

static
ord_e __compare_double(const type_t *t, const void *a, const void *b)
{ return(LIFT_COMPARE(double *, a, b)); }

static
size_t __sizeof_double(const type_t *t, const void *a)
{ return(LIFT_SIZEOF(double)); }

static
ord_e __compare_cstring(const type_t *t, const void *a, const void *b)
{
  int x = strcmp((const char *) a, (const char *) b);
  if (x == 0)
  { return(EQ); }
  else if (x > 0)
  { return(GT); }
  else // if (x < 0)
  { return(LT); }
}

static
size_t __sizeof_cstring(const type_t *t, const void *a)
{ return(strlen((const char *) a)); }

static
bool __generic_equals(const type_t *t, const void *a, const void *b)
{ return(t->compare(t, a, b) == EQ); }

void *type_dup(const type_t *t, const void *data, init_f alloc)
{
  if (data == NULL)
  { return(NULL); }
  size_t size = t->size(t, data);
  void *ddata = alloc(size);
  if (ddata != NULL)
  { memcpy(ddata, data, size); }
  return(ddata);
}

type_t type_int()
{ TEMPLATE_TYPE_FUNCTION(int, __sizeof_int, __compare_int); }

type_t type_char()
{ TEMPLATE_TYPE_FUNCTION(char, __sizeof_char, __compare_char); }

type_t type_uint8()
{ TEMPLATE_TYPE_FUNCTION(uint8_t, __sizeof_uint8, __compare_uint8); }

type_t type_uint16()
{ TEMPLATE_TYPE_FUNCTION(uint16_t, __sizeof_uint16, __compare_uint16); }

type_t type_uint32()
{ TEMPLATE_TYPE_FUNCTION(uint32_t, __sizeof_uint32, __compare_uint32); }

type_t type_uint64()
{ TEMPLATE_TYPE_FUNCTION(uint64_t, __sizeof_uint64, __compare_uint64); }

type_t type_int8()
{ TEMPLATE_TYPE_FUNCTION(int8_t, __sizeof_int8, __compare_int8); }

type_t type_int16()
{ TEMPLATE_TYPE_FUNCTION(int16_t, __sizeof_int16, __compare_int16); }

type_t type_int32()
{ TEMPLATE_TYPE_FUNCTION(int32_t, __sizeof_int32, __compare_int32); }

type_t type_int64()
{ TEMPLATE_TYPE_FUNCTION(int64_t, __sizeof_int64, __compare_int64); }

type_t type_float()
{ TEMPLATE_TYPE_FUNCTION(float, __sizeof_float, __compare_float); }

type_t type_double()
{ TEMPLATE_TYPE_FUNCTION(double, __sizeof_double, __compare_double); }

type_t type_cstring()
{ TEMPLATE_TYPE_FUNCTION(char *, __sizeof_cstring, __compare_cstring); }
