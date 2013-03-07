/* Copyright (c) 2013, Diego Souza                                                 */
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

#ifndef __LIFT_HASHMAP__
#define __LIFT_HASHMAP__

#include "lift/type.h"

EXTERN_C_OPEN

typedef struct hashmap_entry_t hashmap_entry_t;
typedef struct hashmap_t hashmap_t;

struct hashmap_t
{
  type_t k_type;
  type_t v_type;

  /* querying */
  hashmap_entry_t *(*lookup)         (const hashmap_t *, const void *);
  hashmap_entry_t *(*head)           (const hashmap_t *);
  int          (*size)               (const hashmap_t *);
  const void  *(*key)                (const hashmap_t *, const hashmap_entry_t *);
  const void  *(*val)                (const hashmap_t *, const hashmap_entry_t *);

  /* iterator */
  hashmap_entry_t *(*next)           (const hashmap_t *, const hashmap_entry_t *);

  /* memory management */
  hashmap_entry_t *(*entry_init)     (const hashmap_t *, const void *, const void *);
  void             (*entry_free)     (const hashmap_t *, hashmap_entry_t *);
  void             (*hashmap_free)   (hashmap_t *);

  /* updates */
  bool             (*insert)         (hashmap_t *, hashmap_entry_t *);

  /* implementation specifics */
  void *impl;
};

/*! Performs the lookup of a given key.
 *
 * \param k The key you are looking for;
 * \return The entry found or NULL;
 */
const hashmap_entry_t *hashmap_lookup(hashmap_t *, const void *k);

/*! Inserts a new key into the hash.
 *
 * \param key The key to register this value with;
 * \return The value associated with this key;
 * \return true=success false=failure
 */
bool *hashmap_insert(hashmap_t *, const void *k, const void *v);

/*! Returns the first element on this map, useful to start
 *  iterating. Notice that in some implementations the order may be
 *  undefined.
 *
 *  \return The first element or NULL.
 */
const hashmap_entry_t *hashmap_head(const hashmap_t *);

/*! Returns the next element.
 *
 * \return The next element or NULL.
 */
const hashmap_entry_t *hashmap_next(const hashmap_t *, const hashmap_entry_t *);

/*! Returns a pair (key, val)
 */
tuple_t hashmap_entry_pair(const hashmap_t *, const hashmap_entry_t *);

/*! Returns the value.
 */
void *hashmap_entry_value(const hashmap_t *, const hashmap_entry_t *);

/*! Returns the key.
 */
void *hashmap_entry_key(const hashmap_t *, const hashmap_entry_t *);

/*! Computes the hashcode of this entry.
 */
size_t *hashmap_hashcode(const hashmap_t *, const hashmap_entry_t *);

/*! Releases all memory associated with this hashmap.
 */
void hashmap_destroy(hashmap_t *);

EXTERN_C_CLOSE

#endif
