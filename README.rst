::

   _ _  __ _   
  | (_)/ _| |_ 
  | | | |_| __|
  | | |  _| |_ 
  |_|_|_|  \__|

=====================================
A C-library of common data structures
=====================================

.. image:: https://travis-ci.org/dgvncsz0f/lift.png?branch=master
  :target: https://travis-ci.org/dgvncsz0f/lift

INTRODUCTION
============

This library aims to provide established data structures
implementation for C99.

The motivation is not really the lack of such libraries [there is at
least gnulib and glib that does exactly this] but rather to have a
reason to implement such algorithms/data structures and experiment
with generic programming in C.

That said, my goal is studying and not creating the most efficient
library.

Consider youself warned. :-)

DATA STRUCTURES
===============

Lists
-----

+--------------------+-----------+
| Operation          | llist.h   |
+--------------------+-----------+
| list_head          | O(1)      |
+--------------------+-----------+
| list_last          | O(1)      |
+--------------------+-----------+
| list_get_data      | --        |
+--------------------+-----------+
| list_at            | O(n)      |
+--------------------+-----------+
| list_size          | O(1)      |
+--------------------+-----------+
| list_empty         | O(1)      |
+--------------------+-----------+
| list_append        | O(1)      |
+--------------------+-----------+
| list_prepend       | O(1)      |
+--------------------+-----------+
| list_insert_after  | O(1)      |
+--------------------+-----------+
| list_insert_before | O(1)      |
+--------------------+-----------+
| list_remove        | O(1)      |
+--------------------+-----------+
| list_remove_range  | O(n)      |
+--------------------+-----------+
| list_clear         | O(n)      |
+--------------------+-----------+
| list_pop           | O(1)      |
+--------------------+-----------+
| list_rpop          | O(1)      |
+--------------------+-----------+
| list_next          | O(1)      |
+--------------------+-----------+
| list_prev          | O(1)      |
+--------------------+-----------+

TODO
====

* lists:

 * array list;
 * circular array list;
 * avl tree;
 * red black tree;

* associative arrays:

 * sets;
 * maps;
 * algorithms:
 * searching;
 * sorting;

DESIGN
======

There will be always a *public interface* and possibly many
implementations. For instance, the `list.h` header provides the
interface for *list* type whereas `llist.h` provides the
implementation of a *linked list*. This way you can choose the
implementation you want using the same interface.

The implementations are responsible for initializing the generic
structure. Thus you *must always use specific functions* to
instantiate, for instance, list types. These are the `init` functions
and there will be always their dual `destroy`.

To give an example, this should given you a linked list implementation::

  list_t *l = llist_init(type_int());

Whereas in the following you should get an array::

  list_t *l = alist_init(type_int());

The memory management will be the pair `malloc/free` by
default. However you may use a different one. This might be done be
using using the `init_with` functions. As a matter effect the `init`
functions use the `init_with` with `malloc` and `free` as arguments::

  list_t *llist_init(type_t t)
  {
    return(llist_init_with(t, malloc, free));
  }

All memory is guaranteed to be allocated and freed using these functions.

CHANGELOG
=========

::

  v0.0.1

* llist.h
