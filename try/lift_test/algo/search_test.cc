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

#include <cstdlib>
#include <lift/list.h>
#include <lift/llist.h>
#include <lift/algo/search.h>
#include <UnitTest++.h>

namespace lift_test
{

  namespace algo_test
  {

    TEST(binary_search_should_return_the_index_of_the_element_when_such_exists)
    {
      int elem    = 1,
          tmp;
      list_t *ll  = llist_init(type_int());

      tmp = 0; list_append(ll, &tmp);
      tmp = 1; list_append(ll, &tmp);
      tmp = 2; list_append(ll, &tmp);
      tmp = 3; list_append(ll, &tmp);
      tmp = 4; list_append(ll, &tmp);

      CHECK(1 == binary_search(ll, &elem));
      llist_destroy(ll);
    }

    TEST(binary_search_should_return_NOT_FOUND_if_the_element_is_not_on_the_list)
    {
      int elem    = 4,
          tmp;
      list_t *ll  = llist_init(type_int());

      tmp = 0; list_append(ll, &tmp);
      tmp = 1; list_append(ll, &tmp);
      tmp = 2; list_append(ll, &tmp);
      tmp = 3; list_append(ll, &tmp);

      CHECK(NOT_FOUND == binary_search(ll, &elem));
      llist_destroy(ll);
    }

    TEST(binary_search_should_return_NOT_FOUND_when_the_list_is_empty)
    {
      int elem    = 0;
      list_t *ll  = llist_init(type_int());

      CHECK(NOT_FOUND == binary_search(ll, &elem));
      llist_destroy(ll);
    }

    TEST(least_elem_on_the_entire_list_returns_the_minimum)
    {
      int tmp;
      list_t *ll  = llist_init(type_int());

      tmp = 0; list_append(ll, &tmp);
      tmp = 1; list_append(ll, &tmp);
      tmp = 2; list_append(ll, &tmp);
      tmp = 3; list_append(ll, &tmp);
      tmp = 4; list_append(ll, &tmp);

      CHECK(list_head(ll) == least_elem(ll, list_head(ll), list_last(ll)));
      llist_destroy(ll);
    }

    TEST(least_elem_on_the_empty_list_returns_NULL)
    {
      list_t *ll  = llist_init(type_int());

      CHECK(NULL == least_elem(ll, list_head(ll), list_last(ll)));
      llist_destroy(ll);
    }

    TEST(least_elem_on_unordered_list_also_returns_the_minimum)
    {
      int tmp;
      list_t *ll = llist_init(type_int());

      tmp = 3; list_append(ll, &tmp);
      tmp = 4; list_append(ll, &tmp);
      tmp = 1; list_append(ll, &tmp);
      tmp = 0; list_append(ll, &tmp);
      tmp = 2; list_append(ll, &tmp);

      CHECK(list_prev(ll, list_last(ll)) == least_elem(ll, list_head(ll), list_last(ll)));
      llist_destroy(ll);
    }

    TEST(greatest_elem_on_the_entire_list_returns_the_maximum)
    {
      int tmp;
      list_t *ll = llist_init(type_int());

      tmp = 0; list_append(ll, &tmp);
      tmp = 1; list_append(ll, &tmp);
      tmp = 2; list_append(ll, &tmp);
      tmp = 3; list_append(ll, &tmp);
      tmp = 4; list_append(ll, &tmp);

      CHECK(list_last(ll) == greatest_elem(ll, list_head(ll), list_last(ll)));
      llist_destroy(ll);
    }

    TEST(greatest_elem_on_unordered_list_also_returns_the_maximum)
    {
      int tmp;
      list_t *ll = llist_init(type_int());

      tmp = 3; list_append(ll, &tmp);
      tmp = 4; list_append(ll, &tmp);
      tmp = 1; list_append(ll, &tmp);
      tmp = 0; list_append(ll, &tmp);
      tmp = 2; list_append(ll, &tmp);

      CHECK(list_next(ll, list_head(ll)) == greatest_elem(ll, list_head(ll), list_last(ll)));
      llist_destroy(ll);
    }

    TEST(greatest_elem_on_the_empty_list_returns_NULL)
    {
      list_t *ll = llist_init(type_int());

      CHECK(NULL == greatest_elem(ll, list_head(ll), list_last(ll)));
      llist_destroy(ll);
    }
  }

}
