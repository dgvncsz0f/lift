/* Copyright (c) 2011, Diego Souza                                                 */
/* All rights reserved.                                                            */
                                                                                   
/* Redistribution and use in source and binary forms, with or without              */
/* modification, are permitted provided that the following conditions are met:     */
                                                                                   
/*   * Redistributions of source code must retain the above copyright notice,      */
/*     this list of conditions and the following disclaimer.                       */
/*   * Redistributions in binary form must reproduce the above copyright notice,   */
/*     this list of conditions and the following disclaimer in the documentation   */
/*     and/or other materials provided with the distribution.                      */
/*   * Neither the name of the <ORGANIZATION> nor the names of its contributors    */
/*     may be used to endorse or promote products derived from this software       */
/*     without specific prior written permission.                                  */

/* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND */
/* ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED   */
/* WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE          */
/* DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE    */
/* FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL      */
/* DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR      */
/* SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER      */
/* CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,   */
/* OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE   */
/* OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.            */

#ifndef __LIFT_GVALUE__
#define __LIFT_GVALUE__

#include <lift/base.h>

EXTERN_C_OPEN

typedef enum ord_e
{
  LT,
  EQ,
  GT
} ord_e;

typedef struct gvalue_t gvalue_t;
typedef ord_e (*compare_f)(void *a, void *b);
typedef bool  (*equals_f)(void *a, void *b);

gvalue_t *gvalue_init(void *v, free_f vfree);
gvalue_t *gvalue_init_with(void *v, free_f vfree, init_f init, free_f destroy);
gvalue_t *gvalue_init_with2(void *v, free_f vfree, init_f init, free_f destroy, equals_f equals, compare_f compare);

gvalue_t *gvalue_init_from_char(char data);
gvalue_t *gvalue_init_from_uchar(unsigned char data);

gvalue_t *gvalue_init_from_short(short data);
gvalue_t *gvalue_init_from_ushort(unsigned short data);

gvalue_t *gvalue_init_from_int(int data);
gvalue_t *gvalue_init_from_uint(unsigned int data);

gvalue_t *gvalue_init_from_long(long int data);
gvalue_t *gvalue_init_from_ulong(unsigned long int data);

gvalue_t *gvalue_init_from_double(double data);

gvalue_t *gvalue_init_from_float(float data);

gvalue_t *gvalue_init_from_string(const char *data);

void *gvalue_data(const gvalue_t *gv);

ord_e gvalue_compare(const gvalue_t *a, const gvalue_t *b);

ord_e gvalue_compare_data(const void *a, const gvalue_t *b);

bool gvalue_equals(const gvalue_t *a, const gvalue_t *b);

bool gvalue_equals_data(const void *a, const gvalue_t *b);

/*! Free memory used by the value member using the suplied free_f function.
 */
void gvalue_destroy(gvalue_t *g);

EXTERN_C_CLOSE

#endif
