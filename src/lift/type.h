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

#ifndef __LIFT_TYPE__
#define __LIFT_TYPE__

#include <stdbool.h>
#include <inttypes.h>
#include "lift/base.h"

EXTERN_C_OPEN

#define LIFT_V(t, a)          (* ((t) a))
#define LIFT_SIZEOF(t)        sizeof(t)
#define LIFT_EQ(t, a, b)      (LIFT_V(t, a) == LIFT_V(t, b))
#define LIFT_COMPARE(t, a, b) (LIFT_V(t, a) > LIFT_V(t, b) ? GT : (LIFT_V(t, a) < LIFT_V(t, b) ? LT : EQ))

#define TEMPLATE_TYPE_FUNCTION(t, sf, cf) type_t type;                       \
                                          type.size     = sf;                \
                                          type.compare  = cf;                \
                                          type.equals   = __generic_equals;  \
                                          type.hashcode = NULL;              \
                                          return(type);


typedef struct type_t type_t;

typedef enum
{
  EQ,         // Equals
  LT,         // Less than
  GT          // Greater than
} ord_e;

/*! Contains information about a generic type. Not all functions are
 *  required for most operations. For instance, the linked list
 *  interface are likely to require equal function but not compare.
 */
struct type_t
{
  // measure this value
  size_t   (*size)     (const type_t *, const void *);

  // comparable interface two values
  ord_e    (*compare)  (const type_t *, const void *, const void *);
  bool     (*equals)   (const type_t *, const void *, const void *);

  // hashable interface
  uint64_t (*hashcode) (const type_t *, const void *);
};

void *type_dup(const type_t *, const void *, init_f init);

type_t type_any();
type_t type_char();
type_t type_int();
type_t type_uint8();
type_t type_int8();
type_t type_uin16();
type_t type_int16();
type_t type_uint32();
type_t type_int32();
type_t type_uint64();
type_t type_int64();
type_t type_float();
type_t type_double();
type_t type_cstring();
type_t type_wstring();

EXTERN_C_CLOSE

#endif
