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

#ifndef __LIFT_LIST__
#define __LIFT_LIST__

#include <stdlib.h>
#include <stdbool.h>
#include <lift/base.h>
#include <lift/type.h>

EXTERN_C_OPEN

typedef struct list_t list_t;
typedef struct list_node_t list_node_t;

struct list_t
{
  type_t type;

  /* Querying */
  list_node_t *(*head)          (const list_t *);
  list_node_t *(*last)          (const list_t *);
  list_node_t *(*at)            (const list_t *, int);
  int          (*size)          (const list_t *);
  const void  *(*get)           (const list_t *, const list_node_t *);

  /* iterator */
  list_node_t *(*next)          (const list_t *, const list_node_t *);
  list_node_t *(*prev)          (const list_t *, const list_node_t *);

  /* memory management */
  list_node_t *(*node_init)     (const list_t *, const void *data);
  void         (*node_free)     (const list_t *, list_node_t *);

  /* updates */
  void         (*remove)        (const list_t *, list_node_t *);         
  void         (*insert_after)  (list_t *, list_node_t *, list_node_t *);
  void         (*insert_before) (list_t *, list_node_t *, list_node_t *);

  /* implementation specifics */
  void *impl;
};

/*! Returns the first element of this list.
 *
 * \param l The list to get the first element of;
 * \return The first element or NULL.
 */
list_node_t *list_head(const list_t *l);

/*! Returns the last element of this list.
 *
 * \param l The list to get the last element of;
 * \return The last element or NULL.
 */
list_node_t *list_last(const list_t *l);

/*! Retrieves the value held by a given node.
 *
 * \param l The list that owns this node;
 * \param e The node to get the value from;
 * \return The data.
 */
const void *list_get_data(const list_t *l, const list_node_t *e);

/*! Returns the element at a given position.
 *
 * \param l The list to get an element of;
 * \param o The index to get the element. You may use negative numbers.
 */
list_node_t *list_at(const list_t *l, int o);

/*! Computes the number of elements in this list;
 *
 * \param l The list to get the size of;
 * \return The number of elements.
 */
int list_size(const list_t *l);

/*! Returns true if the list is empty.
 *
 * \param l The list;
 * \return true=empty, false=not empty.
 */
bool list_empty(const list_t *l);

/*! Inserts a new element at the tail. This is the same as
 * list_insert_after(l, list_last(l), data, f);
 *
 * \param l The linked list;
 * \param data The data to insert;
 * \return true=success, false=failure.
 */
bool list_append(list_t *l, const void *data);

/*! Inserts a new element after at the head. This is the same as
 * list_insert_before(l, list_head(l), data, f);
 *
 * \param l The linked list;
 * \param p The position to insert element after.
 * \param data The data to insert;
 * \return true=success, false=failure.
 */
bool list_prepend(list_t *l, const void *data);

/*! Inserts a new element after a given position.
 *
 * \param l The list container. 
 * \param e The element that will be the predecessor of the new one.
 * \param data The data to insert;
 * \return true=success, false=failure.
 */
bool list_insert_after(list_t *l, list_node_t *e, const void *data);

/*! Inserts a new element before a given position.
 *
 * \param l The list container. 
 * \param e The element that will be the successor of the new one.
 * \param data The data to insert;
 * \return true=success, false=failure.
 */
bool list_insert_before(list_t *l, list_node_t *e, const void *data);

/*! Removes an element from the list.
 *
 * \param l The list to remove the element from;
 * \param e The element to remove;
 */
void list_remove(list_t *l, list_node_t *e);

/* Removes the elements in a given range (inclusive).
 *
 * \param l The list to remove elements from;
 * \param s The start element.
 * \param e The end element.
 */
void list_remove_range(list_t *l, list_node_t *s, list_node_t *e);

/*! Removes all elements from this list. This is the same as
 *  list_remove_range(l, list_head(l), list_last(l));
 * 
 * \param l The list to remove all elements of.
 */
void list_clear(list_t *l);

/*! Removes the first element. This is the same as 
 * list_remove(l, list_head(l));
 *
 * \param l The list to remove the element from;
 */
void list_pop(list_t *l);

/*! Removes the last element. This is the same as
 * list_remove(l, list_last(l));
 *
 * \param l The list to remove the element from;
 */
void list_rpop(list_t *l);

/*! Returns the next element. Might be NULL if this is last one.
 *
 * \param l The list type; 
 * \param e The element to get the next of;
 * \return The next element of NULL;
 */
list_node_t *list_next(const list_t *l, const list_node_t *e);

/*! Returns the previous element. Might be NULL if this is the head one.
 *
 * \param l The list type; 
 * \param e The element to get the previous of;
 * \return The previous element of NULL;
 */
list_node_t *list_prev(const list_t *l, const list_node_t *e);

EXTERN_C_CLOSE

#endif
