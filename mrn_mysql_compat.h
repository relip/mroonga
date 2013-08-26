/* -*- c-basic-offset: 2 -*- */
/*
  Copyright(C) 2011 Kouhei Sutou <kou@clear-code.com>

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*/

#ifndef MRN_MYSQL_COMPAT_H_
#define MRN_MYSQL_COMPAT_H_

#include "mrn_mysql.h"

#if MYSQL_VERSION_ID >= 50500
#  define my_free(PTR, FLAG) my_free(PTR)
#endif

#if MYSQL_VERSION_ID < 50500
#  define mysql_mutex_lock(mutex) pthread_mutex_lock(mutex)
#  define mysql_mutex_unlock(mutex) pthread_mutex_unlock(mutex)
#endif

#if MYSQL_VERSION_ID >= 50604 && !defined(MRN_MARIADB_P)
#  define MRN_HAVE_MYSQL_TYPE_TIMESTAMP2
#  define MRN_HAVE_MYSQL_TYPE_DATETIME2
#  define MRN_HAVE_MYSQL_TYPE_TIME2
#endif

#if MYSQL_VERSION_ID < 50603
  typedef MYSQL_ERROR Sql_condition;
#endif

#if defined(MRN_MARIADB_P)
#  if MYSQL_VERSION_ID >= 50302 && MYSQL_VERSION_ID < 100000
     typedef COST_VECT Cost_estimate;
#  endif
#endif

#if MYSQL_VERSION_ID >= 50516
#  define MRN_PLUGIN_HAVE_FLAGS 1
#endif

// for MySQL < 5.5
#ifndef MY_ALL_CHARSETS_SIZE
#  define MY_ALL_CHARSETS_SIZE 256
#endif

#ifndef MRN_MARIADB_P
  typedef char *range_id_t;
#endif

#if MYSQL_VERSION_ID >= 50609
#  define MRN_KEY_HAS_USER_DEFINED_KEYPARTS
#endif

#ifdef MRN_KEY_HAS_USER_DEFINED_KEYPARTS
#  define KEY_N_KEY_PARTS(key) (key)->user_defined_key_parts
#else
#  define KEY_N_KEY_PARTS(key) (key)->key_parts
#endif

#if MYSQL_VERSION_ID < 100000 || !defined(MRN_MARIADB_P)
#  define init_alloc_root(PTR, SZ1, SZ2, FLAG) init_alloc_root(PTR, SZ1, SZ2)
#endif

#if MYSQL_VERSION_ID < 100002 || !defined(MRN_MARIADB_P)
#  define GTS_TABLE 0
#endif

/* For MySQL 5.1. MySQL 5.1 doesn't have FN_LIBCHAR2. */
#ifndef FN_LIBCHAR2
#  define FN_LIBCHAR2 FN_LIBCHAR
#endif

#if MYSQL_VERSION_ID >= 50607
#  define MRN_GET_ERROR_MESSAGE current_thd->get_stmt_da()->message()
#else
#  if MYSQL_VERSION_ID >= 50500
#    define MRN_GET_ERROR_MESSAGE current_thd->stmt_da->message()
#  else
#    define MRN_GET_ERROR_MESSAGE current_thd->main_da.message()
#  endif
#endif

#if MYSQL_VERSION_ID >= 50607 && !defined(MRN_MARIADB_P)
#  define MRN_ITEM_HAVE_ITEM_NAME
#endif

#endif /* MRN_MYSQL_COMPAT_H_ */
