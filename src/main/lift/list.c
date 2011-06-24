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

#include <lift/list.h>

inline
bool list_append(list_t *l, void *data, free_f f)
{
  return(list_insert_after(l, list_last(l), data, f));
}

inline
bool list_prepend(list_t *l, void *data, free_f f)
{
  return(list_insert_before(l, list_head(l), data, f));
}

inline
bool list_insert_after(list_t *l, list_node_t *e, void *data, free_f f)
{
  list_node_t *elem = l->node_init(l, data, f);
  if (elem != NULL)
    l->insert_after(l, e, elem);
  return(elem != NULL);
}

inline
bool list_insert_before(list_t *l, list_node_t *e, void *data, free_f f)
{
  list_node_t *elem = l->node_init(l, data, f);
  if (elem != NULL)
    l->insert_before(l, e, elem);
  return(elem != NULL);
}

inline
list_node_t *list_head(const list_t *l)
{
  return(l->head(l));
}

inline
list_node_t *list_last(const list_t *l)
{
  return(l->last(l));
}

inline
list_node_t *list_at(const list_t *l, int o_)
{
  int s = list_size(l);
  int o = (s==0 ? 0 : (o_%s+s)%s);
  return(l->at(l, o));
}

inline
void *list_get_data(const list_t *l, const list_node_t *e)
{
  return(l->get(l, e));
}

inline
int list_size(const list_t *l)
{
  return(l->size(l));
}

inline
bool list_empty(const list_t *l)
{
  return(list_size(l) == 0);
}

inline
void list_remove(list_t *l, list_node_t *e)
{
  l->remove(l, e);
  l->node_free(l, e);
}

void list_remove_range(list_t *l, list_node_t *s, list_node_t *e)
{
  list_remove(l, s);
  if (s != e)
    list_remove_range(l, list_next(l, s), e);
}

inline
void list_clear(list_t *l)
{
  if (!list_empty(l))
    list_remove_range(l, list_head(l), list_last(l));
}

inline
void list_pop(list_t *l)
{
  list_node_t *head = list_head(l);
  if (head != NULL)
    list_remove(l, head);
}

inline
void list_rpop(list_t *l)
{
  list_node_t *last = list_last(l);
  if (last != NULL)
    list_remove(l, last);
}

inline
list_node_t *list_next(const list_t *l, const list_node_t *e)
{
  return(l->next(l, e));
}

inline
list_node_t *list_prev(const list_t *l, const list_node_t *e)
{
  return(l->prev(l, e));
}


