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

namespace
{
  int __myint_cmp(const void *pa, const void *pb)
  {
    int a = *((const int*) pa);
    int b = *((const int*) pb);
    return(a - b);
  }
}

namespace lift_test
{

  namespace algo_test
  {

    TEST(binary_search_should_return_the_index_of_the_element_when_such_exists)
    {
      int a=0, b=1, c=2, d=3, e=4;
      // not efficient but any list will do it
      list_t *ll = llist_init();

      list_append(ll, &a, NULL);
      list_append(ll, &b, NULL);
      list_append(ll, &c, NULL);
      list_append(ll, &d, NULL);
      list_append(ll, &e, NULL);

      CHECK(1 == binary_search(ll, &b, __myint_cmp));
    }

    TEST(binary_search_should_return_NOT_FOUND_if_the_element_is_not_on_the_list)
    {
      int a=0, b=1, c=2, d=3, e=4;
      // not efficient but any list will do it
      list_t *ll = llist_init();

      list_append(ll, &a, NULL);
      list_append(ll, &b, NULL);
      list_append(ll, &c, NULL);
      list_append(ll, &d, NULL);

      CHECK(NOT_FOUND == binary_search(ll, &e, __myint_cmp));
    }

    TEST(binary_search_should_return_NOT_FOUND_when_the_list_is_empty)
    {
      int a=0;
      // not efficient but any list will do it
      list_t *ll = llist_init();

      CHECK(NOT_FOUND == binary_search(ll, &a, __myint_cmp));
    }

  }

}
