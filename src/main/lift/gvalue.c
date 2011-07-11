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

#include <string.h>
#include <lift/gvalue.h>

#define SEQ_F(t, a, b) ((*(t *)a) == (*(t *)b))

#define SCMP_F(t, r, a, b) if (SEQ_F(t, a, b))                 r = EQ; \
                           else if ((*(t *)a) < (*(t *)b))     r = LT; \
                           else /*if ((*(t *)a) > (*(t *)b))*/ r = GT;  \

#define GVALUE_INIT_FROM_SCALAR(t, v, f0, f1) { t *d = (t *) malloc(sizeof(t)); ensure(d!=NULL, "memory error"); \
                                                *d = v;\
                                                return(gvalue_init_with2(d, free, malloc, free, f0, f1)); \
                                              }

static inline
bool __eq_pointer(void *a, void *b)
{
  return(a == b);
}

static inline
bool __eq_string(void *a, void *b)
{
  return(strcmp((char *) a, (char *) b) == 0);
}

static inline
bool __eq_double(void *a, void *b)
{
  return(SEQ_F(double, a, b));
}

static inline
bool __eq_float(void *a, void *b)
{
  return(SEQ_F(float, a, b));
}

static inline
bool __eq_long(void *a, void *b)
{
  return(SEQ_F(long int, a, b));
}

static inline
bool __eq_ulong(void *a, void *b)
{
  return(SEQ_F(unsigned long int, a, b));
}

static inline
bool __eq_int(void *a, void *b)
{
  return(SEQ_F(int, a, b));
}

static inline
bool __eq_uint(void *a, void *b)
{
  return(SEQ_F(unsigned int, a, b));
}

static inline
bool __eq_short(void *a, void *b)
{
  return(SEQ_F(short, a, b));
}

static inline
bool __eq_ushort(void *a, void *b)
{
  return(SEQ_F(unsigned short, a, b));
}

static inline
bool __eq_char(void *a, void *b)
{
  return(SEQ_F(char, a, b));
}

static inline
bool __eq_uchar(void *a, void *b)
{
  return(SEQ_F(unsigned char, a, b));
}

static inline
ord_e __cmp_char(void *a, void *b)
{
  ord_e r;
  SCMP_F(char, r, a, b);
  return(r);
}

static inline
ord_e __cmp_uchar(void *a, void *b)
{
  ord_e r;
  SCMP_F(unsigned char, r, a, b);
  return(r);
}

static inline
ord_e __cmp_short(void *a, void *b)
{
  ord_e r;
  SCMP_F(short, r, a, b);
  return(r);
}

static inline
ord_e __cmp_ushort(void *a, void *b)
{
  ord_e r;
  SCMP_F(unsigned short, r, a, b);
  return(r);
}

static inline
ord_e __cmp_int(void *a, void *b)
{
  ord_e r;
  SCMP_F(int, r, a, b);
  return(r);
}

static inline
ord_e __cmp_uint(void *a, void *b)
{
  ord_e r;
  SCMP_F(unsigned int, r, a, b);
  return(r);
}

static inline
ord_e __cmp_long(void *a, void *b)
{
  ord_e r;
  SCMP_F(long int, r, a, b);
  return(r);
}

static inline
ord_e __cmp_ulong(void *a, void *b)
{
  ord_e r;
  SCMP_F(unsigned long int, r, a, b);
  return(r);
}

static inline
ord_e __cmp_double(void *a, void *b)
{
  ord_e r;
  SCMP_F(double, r, a, b);
  return(r);
}

static inline
ord_e __cmp_float(void *a, void *b)
{
  ord_e r;
  SCMP_F(float, r, a, b);
  return(r);
}

static inline
ord_e __cmp_string(void *a, void *b)
{
  int cmp = strcmp((char *) a, (char *) b);
  if (cmp == 0)
    return(EQ);
  else if (cmp < 0)
    return(LT);
  else /*if (cmp > 0)*/
    return(GT);
}

struct gvalue_t
{
  void *value;
  free_f vfree;
  free_f destroy;
  compare_f compare;
  equals_f equals;
};


void gvalue_destroy(gvalue_t *g)
{
  if (g->value!=NULL && g->vfree!=NULL)
    g->vfree(g->value);
  g->destroy(g);
}

inline
gvalue_t *gvalue_init(void *data, free_f f)
{
  return(gvalue_init_with(data, f, malloc, free));
}

inline
gvalue_t *gvalue_init_with(void *data, free_f vfree, init_f init, free_f destroy)
{
  return(gvalue_init_with2(data, vfree, init, destroy, __eq_pointer, NULL));
}

gvalue_t *gvalue_init_with2(void *data, free_f vfree, init_f init, free_f destroy, equals_f equals, compare_f compare)
{
  gvalue_t *gv = (gvalue_t *) init(sizeof(gvalue_t));
  gv->value   = data;
  gv->vfree   = vfree;
  gv->destroy = destroy;
  gv->compare = compare;
  gv->equals  = equals;
  return(gv);
}

gvalue_t *gvalue_init_from_char(char v)
{
  GVALUE_INIT_FROM_SCALAR(char, v, __eq_char, __cmp_char);
}

gvalue_t *gvalue_init_from_uchar(unsigned char v)
{
  GVALUE_INIT_FROM_SCALAR(unsigned char, v, __eq_uchar, __cmp_uchar);
}

gvalue_t *gvalue_init_from_short(short v)
{
  GVALUE_INIT_FROM_SCALAR(short, v, __eq_short, __cmp_short);
}

gvalue_t *gvalue_init_from_ushort(unsigned short v)
{
  GVALUE_INIT_FROM_SCALAR(unsigned short, v, __eq_ushort, __cmp_ushort);
}

gvalue_t *gvalue_init_from_int(int v)
{
  GVALUE_INIT_FROM_SCALAR(int, v, __eq_int, __cmp_int);
}

gvalue_t *gvalue_init_from_uint(unsigned int v)
{
  GVALUE_INIT_FROM_SCALAR(unsigned int, v, __eq_uint, __cmp_uint);
}

gvalue_t *gvalue_init_from_long(long int v)
{
  GVALUE_INIT_FROM_SCALAR(long int, v, __eq_long, __cmp_long);
}

gvalue_t *gvalue_init_from_ulong(unsigned long int v)
{
  GVALUE_INIT_FROM_SCALAR(unsigned long int, v, __eq_ulong, __cmp_ulong);
}

inline
void *gvalue_data(const gvalue_t *gv)
{
  return(gv->value);
}

inline
ord_e gvalue_compare(const gvalue_t *a, const gvalue_t *b)
{
  return(a->compare(a->value, b->value));
}

inline
ord_e gvalue_compare_data(const void *a, const gvalue_t *b)
{
  return(b->compare(a, b->value));
}

inline
bool gvalue_equals(const gvalue_t *a, const gvalue_t *b)
{
  return(a->equals(a->value, b->value));
}

inline
bool gvalue_equals_data(const void *a, const gvalue_t *b)
{
  return(b->equals(a, b->value));
}
