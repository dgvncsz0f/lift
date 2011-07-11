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

#ifndef __LIFT_ALGO_SEARCH__
#define __LIFT_ALGO_SEARCH__

#include <lift/base.h>
#include <lift/list.h>

EXTERN_C_OPEN

#define NOT_FOUND (-1)

/*! Executes a binary search on a given list.
 * N.B.: This requires the list to be sorted.
 *
 * \param xs The list to perform the search on;
 * \param x The element you are looking for;
 * \return The index at which the element is located or NOT_FOUND.
 */
int binary_search(const list_t *xs, const gvalue_t *x);

/*! Finds the least element
 * N.B: Obviously this assumes a non sorted list.
 *
 * \param start,end The range to perform the search on;
 * \param f The function that compare two eleemnts;
 * \return The index at which the least element was found. Returns NOT_FOUND when the list is empty
 */
list_node_t *least_elem(const list_t *l, list_node_t *start, list_node_t *end);

/*! Finds the greatest element.
 * N.B: Obviously this assumes a non sorted list.
 *
 * \param start,end The range to perform the search on;
 * \param f The function that compare two eleemnts;
 * \return The index at which the greatest element was found. Returns NOT_FOUND when the list is empty
 */
list_node_t *greatest_elem(const list_t *l, list_node_t *start, list_node_t *end);

EXTERN_C_CLOSE

#endif
