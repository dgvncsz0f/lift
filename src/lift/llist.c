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

#include <lift/llist.h>

typedef struct llist_t
{
  type_t type;
  list_node_t *head;
  list_node_t *last;
  int size;
  init_f mem_init;
  free_f mem_free;
} llist_t;

struct list_node_t
{
  void *data;
  free_f mem_free;
  list_node_t *next;
  list_node_t *prev;
};

static inline
const void *__get_f(const list_t *l, const list_node_t *e)
{ return(e->data); }

static inline
int __size_f(const list_t *l)
{
  llist_t *ll = (llist_t *) l->impl;
  return(ll->size);
}

static inline
list_node_t *__head_f(const list_t *l)
{
  llist_t *ll = (llist_t *) l->impl;
  return(ll->head);
}

static inline
list_node_t *__last_f(const list_t *l)
{
  llist_t *ll = (llist_t *) l->impl;
  return(ll->last);
}

static
list_node_t *__at_f(const list_t *l, int k)
{
  llist_t *ll = (llist_t *) l->impl;
  list_node_t *it = ll->head;

  while (it!=NULL && k>0)
  {
    it = it->next;
    k -= 1;
  }

  return(it);
}

static inline
list_node_t *__next_f(const list_t *l, const list_node_t *e)
{
  llist_t *ll = (llist_t *) l->impl;
  if (e == ll->last)
    return(NULL);
  return(e->next);
}

static inline
list_node_t *__prev_f(const list_t *l, const list_node_t *e)
{
  llist_t *ll = (llist_t *) l->impl;
  if (e == ll->head)
    return(NULL);
  return(e->prev);
}

static
list_node_t *__node_init_f(const list_t *l, const void *data)
{
  llist_t *ll    = (llist_t *) l->impl;
  list_node_t *e = (list_node_t *) ll->mem_init(sizeof(list_node_t));

  if (e != NULL)
  {
    e->data = type_dup(&l->type, data, ll->mem_init);
    e->next = NULL;
    e->prev = NULL;
  }

  return(e);
}

static
void __node_free_f(const list_t *l, list_node_t *e)
{
  llist_t *ll = (llist_t *) l->impl;
  if (e->data!=NULL)
  { ll->mem_free(e->data); }
  ll->mem_free(e);
}

static
void __remove_f(const list_t *l, list_node_t *e)
{
  llist_t *ll = (llist_t *) l->impl;
  list_node_t *prev = e->prev;
  list_node_t *next = e->next;
  if (prev != NULL)
  { prev->next = next; }
  if (next != NULL)
  { next->prev = prev; }

  if (e == ll->head)
  { ll->head = next; }
  if (e == ll->last)
  { ll->last = prev; }

  ll->size -= 1;
}

static
void __insert_after_f(list_t *l, list_node_t *p, list_node_t *e)
{
  llist_t *ll = (llist_t *) l->impl;

  e->prev = p;
  if (p != NULL)
  {
    e->next = p->next;
    if (p->next != NULL)
    { p->next->prev = e; }
    p->next = e;
  }
  else if (ll->size == 0)
  {
    ll->head = e;
    ll->last = e;
  }

  if (p == ll->last)
  { ll->last = e; }

  ll->size += 1;
}

static
void __insert_before_f(list_t *l, list_node_t *p, list_node_t *e)
{
  llist_t *ll = (llist_t *) l->impl;

  e->next = p;
  if (p != NULL)
  {
    e->prev = p->prev;
    if (p->prev != NULL)
    {  p->prev->next = e; }
    p->prev = e;
  }
  else if (ll->size == 0)
  {
    ll->head = e;
    ll->last = e;
  }

  if (p == ll->head)
  { ll->head = e; }

  ll->size += 1;
}

inline
list_t *llist_init(type_t type)
{ return(llist_init_with(type, malloc, free)); }

list_t *llist_init_with(type_t type, init_f myinit, free_f myfree)
{
  list_t *l   = (list_t *) myinit(sizeof(list_t));
  llist_t *ll = (llist_t *) myinit(sizeof(llist_t));
  L_GOTOIF(l == NULL, exit_failure);
  L_GOTOIF(ll == NULL, exit_failure);
  
  ll->head     = NULL;
  ll->last     = NULL;
  ll->size     = 0;
  ll->mem_init = myinit;
  ll->mem_free = myfree;

  l->type          = type;
  l->head          = __head_f;
  l->last          = __last_f;
  l->at            = __at_f;
  l->size          = __size_f;
  l->get           = __get_f;
  l->next          = __next_f;
  l->prev          = __prev_f;
  l->node_init     = __node_init_f;
  l->node_free     = __node_free_f;
  l->remove        = __remove_f;
  l->insert_after  = __insert_after_f;
  l->insert_before = __insert_before_f;
  l->impl          = ll;

  return(l);

exit_failure:
  if (ll != NULL)
  { myfree(ll); }
  if (l != NULL)
  { myfree(l); }
  return(NULL);
}

void llist_destroy(list_t *l)
{
  llist_t *ll = (llist_t *) l->impl;
  list_clear(l);
  ll->mem_free(l);
  ll->mem_free(ll);
}
