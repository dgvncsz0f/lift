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
#include <UnitTest++.h>

namespace lift_test
{

  // append

  TEST(list_append_on_an_empty_list_defines_both_head_and_last)
  {
    list_t *l = llist_init(type_int());
    list_append(l, NULL);
    CHECK(NULL != list_head(l));
    CHECK(list_head(l) == list_last(l));
    llist_destroy(l);
  }

  TEST(list_append_preserves_head)
  {
    list_t *l = llist_init(type_int());
    list_append(l, NULL);
    list_node_t *e = list_head(l);

    list_append(l, NULL);
    list_append(l, NULL);
    CHECK(e == list_head(l));

    llist_destroy(l);
  }

  // prepend

  TEST(list_prepend_on_an_empty_defines_both_head_and_last)
  {
    list_t *l = llist_init(type_int());
    list_prepend(l, NULL);
    CHECK(NULL != list_last(l));
    CHECK(list_last(l) == list_head(l));
    llist_destroy(l);
  }

  TEST(list_prepend_preserves_tail)
  {
    list_t *l = llist_init(type_int());
    list_prepend(l, NULL);
    list_node_t *e = list_last(l);

    list_prepend(l, NULL);
    list_prepend(l, NULL);
    CHECK(e == list_last(l));

    llist_destroy(l);
  }

  // head
  TEST(list_head_returns_NULL_when_the_list_is_empty)
  {
    list_t *l = llist_init(type_int());
    CHECK(NULL == list_head(l));
    llist_destroy(l);
  }

  // last
  TEST(list_last_returns_NULL_when_the_list_is_empty)
  {
    list_t *l = llist_init(type_int());
    CHECK(NULL == list_last(l));
    llist_destroy(l);
  }

  TEST(list_last_and_list_head_are_the_same_when_list_is_singleton)
  {
    list_t *l = llist_init(type_int());
    list_append(l, NULL);
    CHECK(list_head(l) == list_last(l));
    llist_destroy(l);
  }

  // at
  TEST(list_at_returns_NULL_if_list_is_empty)
  {
    list_t *l = llist_init(type_int());
    CHECK(NULL == list_at(l, 0));
    llist_destroy(l);
  }

  TEST(list_at_returns_the_element_at_a_given_index)
  {
    list_t *l = llist_init(type_int());
    list_append(l, NULL);
    list_append(l, NULL);
    CHECK(list_at(l, 0) == list_head(l));
    CHECK(list_at(l, 1) == list_last(l));
    llist_destroy(l);
  }

  TEST(list_at_works_with_numbers_that_exceeds_list_size)
  {
    list_t *l = llist_init(type_int());
    list_append(l, NULL);
    list_append(l, NULL);

    CHECK(list_at(l, 0) == list_at(l, 2));
    CHECK(list_at(l, 1) == list_at(l, 3));

    llist_destroy(l);
  }

  TEST(list_at_works_with_negative_numbers)
  {
    list_t *l = llist_init(type_int());
    list_append(l, NULL);
    list_append(l, NULL);

    CHECK(list_at(l, -1) == list_last(l));
    CHECK(list_at(l, -2) == list_head(l));

    llist_destroy(l);
  }

  TEST(list_at_works_with_negative_numbers_that_exceeds_list_size)
  {
    list_t *l = llist_init(type_int());
    list_append(l, NULL);
    list_append(l, NULL);

    CHECK(list_at(l, -1) == list_at(l, -3));
    CHECK(list_at(l, -2) == list_at(l, -4));

    llist_destroy(l);
  }

  // size
  TEST(list_size_returns_zero_when_list_is_empty)
  {
    list_t *l = llist_init(type_int());

    CHECK(0 == list_size(l));

    llist_destroy(l);
  }

  TEST(list_size_returns_the_correct_number_of_elements)
  {
    list_t *l = llist_init(type_int());
    list_append(l, NULL);
    list_append(l, NULL);

    CHECK(2 == list_size(l));
    
    llist_destroy(l);
  }

  // empty
  TEST(list_empty_returns_true_when_list_is_empty)
  {
    list_t *l = llist_init(type_int());

    CHECK(list_empty(l));

    llist_destroy(l);
  }

  TEST(list_insert_after_with_head_does_not_change_head_nor_last)
  {
    list_t *l = llist_init(type_int());
    list_append(l, NULL);
    list_append(l, NULL);

    list_node_t *head = list_head(l);
    list_node_t *last = list_last(l);
    list_insert_after(l, head, NULL);

    CHECK(head == list_head(l));
    CHECK(last == list_last(l));
    CHECK(3 == list_size(l));

    llist_destroy(l);
  }

  TEST(list_insert_after_with_the_last_element_changes_the_tail)
  {
    list_t *l = llist_init(type_int());
    list_append(l, NULL);
    list_append(l, NULL);

    list_node_t *head = list_head(l);
    list_node_t *last = list_last(l);
    list_insert_after(l, last, NULL);
    
    CHECK(head == list_head(l));
    CHECK(last != list_last(l));
    CHECK(3    == list_size(l));

    llist_destroy(l);
  }

  // list_insert_before
  TEST(list_insert_before_with_head_changes_the_head)
  {
    list_t *l = llist_init(type_int());
    list_append(l, NULL);
    list_append(l, NULL);

    list_node_t *head = list_head(l);
    list_node_t *last = list_last(l);
    list_insert_before(l, head, NULL);

    CHECK(head != list_head(l));
    CHECK(last == list_last(l));
    CHECK(3 == list_size(l));

    llist_destroy(l);
  }

  TEST(list_insert_before_with_tail_preserves_both_head_and_tail)
  {
    list_t *l = llist_init(type_int());
    list_append(l, NULL);
    list_append(l, NULL);

    list_node_t *head = list_head(l);
    list_node_t *last = list_last(l);
    list_insert_before(l, last, NULL);

    CHECK(head == list_head(l));
    CHECK(last == list_last(l));
    CHECK(3 == list_size(l));

    llist_destroy(l);
  }

  // list_remove

  TEST(list_remove_reduces_list_length)
  {
    list_t *l = llist_init(type_int());
    list_append(l, NULL);

    list_remove(l, list_head(l));
    CHECK(0 == list_size(l));

    llist_destroy(l);
  }

  TEST(list_remove_changes_head_when_this_is_removed)
  {
    list_t *l = llist_init(type_int());
    list_append(l, NULL);
    list_append(l, NULL);

    list_node_t *head = list_head(l);
    list_node_t *last = list_last(l);
    CHECK(head != last);

    list_remove(l, head);
    CHECK(last == list_head(l));

    llist_destroy(l);
  }

  TEST(list_remove_changes_last_when_this_is_removed)
  {
    list_t *l = llist_init(type_int());
    list_append(l, NULL);
    list_append(l, NULL);

    list_node_t *head = list_head(l);
    list_node_t *last = list_last(l);
    CHECK(head != last);

    list_remove(l, last);
    CHECK(head == list_last(l));

    llist_destroy(l);
  }

  TEST(list_remove_preserves_both_head_and_last_if_element_is_in_the_middle)
  {
    list_t *l = llist_init(type_int());
    list_append(l, NULL);
    list_append(l, NULL);
    list_append(l, NULL);

    list_node_t *head = list_head(l);
    list_node_t *last = list_last(l);
    list_node_t *middle = list_at(l, 1);
    CHECK(head != last);
    CHECK(last != middle);
    
    list_remove(l, middle);
    CHECK(head == list_head(l));
    CHECK(last == list_last(l));

    llist_destroy(l);
  }

  // get

  TEST(list_get_data_returns_it_without_modifications)
  {
    int tmp = 10;
    list_t *l = llist_init(type_int());

    list_append(l, &tmp);
    const int *v = (const int *) list_get_data(l, list_head(l));

    CHECK(10 == *v);

    llist_destroy(l);
  }

  // clear

  TEST(list_clear_works_on_empty_lists)
  {
    list_t *l = llist_init(type_int());

    list_clear(l);
    CHECK(0 == list_size(l));

    llist_destroy(l);
  }

  TEST(list_clear_erases_all_elements)
  {
    list_t *l = llist_init(type_int());
    list_append(l, NULL);
    list_append(l, NULL);
    list_append(l, NULL);

    list_clear(l);
    CHECK(0 == list_size(l));
    CHECK(NULL == list_head(l));
    CHECK(NULL == list_last(l));

    llist_destroy(l);
  }

  // remove_range
  
  TEST(remove_range_removes_inclusive_the_start_and_end_elements)
  {
    list_t *l = llist_init(type_int());
    list_append(l, NULL);
    list_append(l, NULL);

    list_remove_range(l, list_head(l), list_last(l));
    CHECK(0 == list_size(l));
    CHECK(NULL == list_head(l));
    CHECK(NULL == list_last(l));

    llist_destroy(l);
  }

  TEST(remove_range_should_clear_singleton_lists)
  {
    list_t *l = llist_init(type_int());
    list_append(l, NULL);
    
    list_remove_range(l, list_head(l), list_last(l));
    CHECK(0 == list_size(l));

    llist_destroy(l);
  }

  TEST(remove_range_should_not_touch_the_head_nor_last_if_the_range_does_not_include_them)
  {
    list_t *l = llist_init(type_int());
    list_append(l, NULL);
    list_append(l, NULL);
    list_append(l, NULL);
    list_append(l, NULL);

    list_node_t *head = list_head(l);
    list_node_t *last = list_last(l);
    list_remove_range(l, list_next(l, list_head(l)), list_prev(l, list_last(l)));
    CHECK(2 == list_size(l));
    CHECK(head == list_head(l));
    CHECK(last == list_last(l));

    llist_destroy(l);
  }

  // pop

  TEST(list_pop_works_on_empty_lists)
  {
    list_t *l = llist_init(type_int());

    list_pop(l);
    CHECK(0 == list_size(l));

    llist_destroy(l);
  }

  TEST(list_pop_changes_head_for_non_empty_lists)
  {
    list_t *l = llist_init(type_int());
    list_append(l, NULL);
    list_append(l, NULL);

    list_node_t *last = list_last(l);
    list_pop(l);

    CHECK(last == list_head(l));

    llist_destroy(l);
  }

  TEST(list_pop_reduces_list_length)
  {
    list_t *l = llist_init(type_int());
    list_append(l, NULL);

    list_pop(l);
    CHECK(0 == list_size(l));

    llist_destroy(l);
  }

  // rpop

  TEST(list_rpop_works_on_empty_lists)
  {
    list_t *l = llist_init(type_int());

    list_rpop(l);
    CHECK(0 == list_size(l));

    llist_destroy(l);
  }

  TEST(list_rpop_changes_last_for_non_empty_lists)
  {
    list_t *l = llist_init(type_int());
    list_append(l, NULL);
    list_append(l, NULL);

    list_node_t *head = list_head(l);
    list_rpop(l);

    CHECK(head == list_last(l));

    llist_destroy(l);
  }

  TEST(list_rpop_reduces_list_length)
  {
    list_t *l = llist_init(type_int());
    list_append(l, NULL);

    list_rpop(l);
    CHECK(0 == list_size(l));

    llist_destroy(l);
  }

  // next

  TEST(list_next_returns_NULL_on_last_even_if_the_list_is_empty)
  {
    list_t *l = llist_init(type_int());

    CHECK(NULL == list_next(l, list_last(l)));

    llist_destroy(l);
  }

  TEST(list_next_returns_NULL_on_last)
  {
    list_t *l = llist_init(type_int());
    list_append(l, NULL);

    CHECK(NULL == list_next(l, list_last(l)));

    llist_destroy(l);
  }

  TEST(list_next_returns_elements_in_insertion_order)
  {
    list_t *l = llist_init(type_int());
    list_append(l, NULL);
    list_append(l, NULL);

    CHECK(list_last(l) == list_next(l, list_head(l)));

    llist_destroy(l);
  }

  // prev

  TEST(list_prev_returns_NULL_on_last_even_if_the_list_is_empty)
  {
    list_t *l = llist_init(type_int());

    CHECK(NULL == list_prev(l, list_head(l)));

    llist_destroy(l);
  }

  TEST(list_head_returns_NULL_on_head)
  {
    list_t *l = llist_init(type_int());
    list_append(l, NULL);

    CHECK(NULL == list_prev(l, list_head(l)));

    llist_destroy(l);
  }

  TEST(list_head_returns_elements_in_insertion_order)
  {
    list_t *l = llist_init(type_int());
    list_append(l, NULL);
    list_append(l, NULL);

    CHECK(list_head(l) == list_prev(l, list_last(l)));

    llist_destroy(l);
  }
}
