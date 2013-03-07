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

#ifndef __LIFT_BASE__
#define __LIFT_BASE__

#include <stdbool.h>
#include <stdlib.h>

#ifdef __cplusplus
#  define EXTERN_C_OPEN extern "C" {
#  define EXTERN_C_CLOSE }
#else
#  define EXTERN_C_OPEN
#  define EXTERN_C_CLOSE
#endif

EXTERN_C_OPEN

#define L_GOTOIF(p, j) if (p) { goto j; }

typedef struct
{
  const void *fst;
  const void *snd;
} tuple_t;

/*! The function responsible for allocating memory. Should provide
 *  same semantics as malloc.
 */
typedef void *(*init_f)(size_t);

/*! The function responsible for freeing memory. Should provide same
 *  semantics of free.
 */
typedef void (*free_f)(void *);

/*! Duplicates a given memory region. Should provide same semantics as
 *  same of init + memcpy.
 */
typedef void *(*dup_f)(void *, size_t);

EXTERN_C_CLOSE

#endif
