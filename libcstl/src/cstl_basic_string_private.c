/*
 *  The implementation of basic_string private functions.
 *  Copyright (C)  2008 - 2012  Wangbo
 *
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU Lesser General Public
 *  License as published by the Free Software Foundation; either
 *  version 2.1 of the License, or (at your option) any later version.
 *
 *  This library is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *  Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public
 *  License along with this library; if not, write to the Free Software
 *  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 *
 *  Author e-mail: activesys.wb@gmail.com
 *                 activesys@sina.com.cn
 */

/** include section **/
#include <cstl/cstl_def.h>
#include <cstl/cstl_alloc.h>
#include <cstl/cstl_types.h>
#include <cstl/citerator.h>
#include <cstl/cvector.h>

#include <cstl/cstl_basic_string_iterator.h>
#include <cstl/cstl_basic_string_private.h>
#include <cstl/cstl_basic_string.h>

#include "cstl_basic_string_aux.h"

/** local constant declaration and local macro section **/

/** local data type declaration and local struct, union, enum section **/

/** local function prototype section **/

/** exported global variable definition section **/

/** local global variable definition section **/

/** exported function implementation section **/
/**
 * Create basic_string container.
 */
basic_string_t* _create_basic_string(const char* s_typename)
{
    basic_string_t* pt_basic_string = NULL;

    assert(s_typename != NULL);

    if ((pt_basic_string = (basic_string_t*)malloc(sizeof(basic_string_t))) == NULL) {
        return NULL;
    }

    if (!_create_basic_string_auxiliary(pt_basic_string, s_typename)) {
        free(pt_basic_string);
        return NULL;
    }

    return pt_basic_string;
}

/**
 * Create basic_string container auxiliary function.
 */
bool_t _create_basic_string_auxiliary(basic_string_t* pt_basic_string, const char* s_typename)
{
    assert(pt_basic_string != NULL);
    assert(s_typename != NULL);

    return _create_vector_auxiliary(&pt_basic_string->_vec_base, s_typename);
}

/**
 * Destroy basic_string container auxiliary function.
 */
void _basic_string_destroy_auxiliary(basic_string_t* pt_basic_string)
{
    assert(pt_basic_string != NULL);

    _vector_destroy_auxiliary(&pt_basic_string->_vec_base);
}

/**
 * Initialize basic_string with specified element.
 */
void _basic_string_init_elem(basic_string_t* pt_basic_string, size_t t_count, ...)
{
    va_list val_elemlist;

    assert(pt_basic_string != NULL);

    va_start(val_elemlist, t_count);
    _basic_string_init_elem_varg(pt_basic_string, t_count, val_elemlist);
    va_end(val_elemlist);
}

/**
 * Initialize basic_string with variable argument list of specified element.
 */
void _basic_string_init_elem_varg(basic_string_t* pt_basic_string, size_t t_count, va_list val_elemlist)
{
    assert(pt_basic_string != NULL);

    _vector_init_elem_varg(&pt_basic_string->_vec_base, t_count, val_elemlist);
}

/**
 * Appends specificed element to basic string.
 */
void _basic_string_connect_elem(basic_string_t* pt_basic_string, ...)
{
    va_list val_elemlist;

    va_start(val_elemlist, pt_basic_string);
    _basic_string_connect_elem_varg(pt_basic_string, val_elemlist);
    va_end(val_elemlist);
}

/**
 * Appends specificed element to basic string.
 */
void _basic_string_connect_elem_varg(basic_string_t* pt_basic_string, va_list val_elemlist)
{
    assert(pt_basic_string != NULL);

    _vector_push_back_varg(&pt_basic_string->_vec_base, val_elemlist);
}

/**
 * Find a first occurrence of a substring
 */
size_t _basic_string_find_elem(const basic_string_t* cpt_basic_string, size_t t_pos, ...)
{
    va_list val_elemlist;

    assert(cpt_basic_string != NULL);

    va_start(val_elemlist, t_pos);
    t_pos = _basic_string_find_elem_varg(cpt_basic_string, t_pos, val_elemlist);
    va_end(val_elemlist);

    return t_pos;
}

/**
 * Find a first occurrence of a substring
 */
size_t _basic_string_find_elem_varg(const basic_string_t* cpt_basic_string, size_t t_pos, va_list val_elemlist)
{
    size_t   t_typesize = 0;
    size_t   t_findpos = 0;
    size_t   t_length = 0;
    void*    pv_varg = NULL;
    _byte_t* pby_string = NULL;
    bool_t   b_less = false;
    bool_t   b_greater = false;

    assert(cpt_basic_string != NULL);

    if (t_pos >= basic_string_size(cpt_basic_string)) {
        return NPOS;
    }

    /* get element */
    t_typesize = _GET_BASIC_STRING_TYPE_SIZE(cpt_basic_string);
    pv_varg = _alloc_allocate(&((basic_string_t*)cpt_basic_string)->_vec_base._t_allocator, t_typesize, 1);
    assert(pv_varg != NULL);
    _basic_string_get_varg_value_auxiliary((basic_string_t*)cpt_basic_string, val_elemlist, pv_varg);

    /* find elemen */
    t_length = basic_string_length(cpt_basic_string);
    pby_string = _BASIC_STRING_ITERATOR_COREPOS(basic_string_begin(cpt_basic_string));
    t_findpos = t_pos;
    while (t_findpos != t_length) {
        b_less = b_greater = t_typesize;
        _GET_BASIC_STRING_TYPE_LESS_FUNCTION(cpt_basic_string)(pby_string + t_findpos * t_typesize, pv_varg, &b_less);
        _GET_BASIC_STRING_TYPE_LESS_FUNCTION(cpt_basic_string)(pv_varg, pby_string + t_findpos * t_typesize, &b_greater);
        if (!b_less && !b_greater) {
            break;
        } else {
            t_findpos++;
        }
    }
    if (t_findpos == t_length) {
        t_findpos = NPOS;
    }

    _basic_string_destroy_varg_value_auxiliary((basic_string_t*)cpt_basic_string, pv_varg);
    _alloc_deallocate(&((basic_string_t*)cpt_basic_string)->_vec_base._t_allocator, pv_varg, t_typesize, 1);

    return t_findpos;
}

/**
 * Find a last occurrence of a substring
 */
size_t _basic_string_rfind_elem(const basic_string_t* cpt_basic_string, size_t t_pos, ...)
{
    va_list val_elemlist;

    va_start(val_elemlist, t_pos);
    t_pos = _basic_string_rfind_elem_varg(cpt_basic_string, t_pos, val_elemlist);
    va_end(val_elemlist);

    return t_pos;
}

/**
 * Find a last occurrence of a substring
 */
size_t _basic_string_rfind_elem_varg(const basic_string_t* cpt_basic_string, size_t t_pos, va_list val_elemlist)
{
    size_t   t_typesize = 0;
    size_t   t_length = 0;
    void*    pv_varg = NULL;
    _byte_t* pby_string = NULL;
    size_t   t_findpos = 0;
    bool_t   b_less = false;
    bool_t   b_greater = false;

    assert(cpt_basic_string != NULL);

    if (basic_string_empty(cpt_basic_string)) {
        return NPOS;
    }

    /* get element */
    t_typesize = _GET_BASIC_STRING_TYPE_SIZE(cpt_basic_string);
    pv_varg = _alloc_allocate(&((basic_string_t*)cpt_basic_string)->_vec_base._t_allocator, t_typesize, 1);
    assert(pv_varg != NULL);
    _basic_string_get_varg_value_auxiliary((basic_string_t*)cpt_basic_string, val_elemlist, pv_varg);

    /* find elemen */
    t_length = basic_string_length(cpt_basic_string);
    pby_string = _BASIC_STRING_ITERATOR_COREPOS(basic_string_begin(cpt_basic_string));
    if (t_pos > t_length) {
        t_pos = t_length;
    }
    t_findpos = (t_pos == t_length ? t_pos - 1 : t_pos);
    for (;;) {
        b_less = b_greater = t_typesize;
        _GET_BASIC_STRING_TYPE_LESS_FUNCTION(cpt_basic_string)(pby_string + t_findpos * t_typesize, pv_varg, &b_less);
        _GET_BASIC_STRING_TYPE_LESS_FUNCTION(cpt_basic_string)(pv_varg, pby_string + t_findpos * t_typesize, &b_greater);
        if (!b_less && !b_greater) {
            break;
        } else {
            if (t_findpos > 0) {
                t_findpos--;
            } else {
                t_findpos = NPOS;
                break;
            }
        }
    }

    _basic_string_destroy_varg_value_auxiliary((basic_string_t*)cpt_basic_string, pv_varg);
    _alloc_deallocate(&((basic_string_t*)cpt_basic_string)->_vec_base._t_allocator, pv_varg, t_typesize, 1);

    return t_findpos;
}

/**
 * Find a first occurrence of a character that is not equal to specificed element.
 */
size_t _basic_string_find_first_not_of_elem(const basic_string_t* cpt_basic_string, size_t t_pos, ...)
{
    va_list val_elemlist;

    va_start(val_elemlist, t_pos);
    t_pos = _basic_string_find_first_not_of_elem_varg(cpt_basic_string, t_pos, val_elemlist);
    va_end(val_elemlist);

    return t_pos;
}

/**
 * Find a first occurrence of a character that is not equal to specificed element.
 */
size_t _basic_string_find_first_not_of_elem_varg(const basic_string_t* cpt_basic_string, size_t t_pos, va_list val_elemlist)
{
    size_t   t_typesize = 0;
    size_t   t_findpos = 0;
    size_t   t_length = 0;
    void*    pv_varg = NULL;
    _byte_t* pby_string = NULL;
    bool_t   b_less = false;
    bool_t   b_greater = false;

    assert(cpt_basic_string != NULL);

    if (t_pos >= basic_string_size(cpt_basic_string)) {
        return NPOS;
    }

    /* get element */
    t_typesize = _GET_BASIC_STRING_TYPE_SIZE(cpt_basic_string);
    pv_varg = _alloc_allocate(&((basic_string_t*)cpt_basic_string)->_vec_base._t_allocator, t_typesize, 1);
    assert(pv_varg != NULL);
    _basic_string_get_varg_value_auxiliary((basic_string_t*)cpt_basic_string, val_elemlist, pv_varg);

    /* find elemen */
    t_length = basic_string_length(cpt_basic_string);
    pby_string = _BASIC_STRING_ITERATOR_COREPOS(basic_string_begin(cpt_basic_string));
    t_findpos = t_pos;
    while (t_findpos != t_length) {
        b_less = b_greater = t_typesize;
        _GET_BASIC_STRING_TYPE_LESS_FUNCTION(cpt_basic_string)(pby_string + t_findpos * t_typesize, pv_varg, &b_less);
        _GET_BASIC_STRING_TYPE_LESS_FUNCTION(cpt_basic_string)(pv_varg, pby_string + t_findpos * t_typesize, &b_greater);
        if (b_less || b_greater) {
            break;
        } else {
            t_findpos++;
        }
    }

    if (t_findpos == t_length) {
        t_findpos = NPOS;
    }

    _basic_string_destroy_varg_value_auxiliary((basic_string_t*)cpt_basic_string, pv_varg);
    _alloc_deallocate(&((basic_string_t*)cpt_basic_string)->_vec_base._t_allocator, pv_varg, t_typesize, 1);

    return t_findpos;
}

/**
 * Find a last occurrence of a character that is not equal to specificed element.
 */
size_t _basic_string_find_last_not_of_elem(const basic_string_t* cpt_basic_string, size_t t_pos, ...)
{
    va_list val_elemlist;

    va_start(val_elemlist, t_pos);
    t_pos = _basic_string_find_last_not_of_elem_varg(cpt_basic_string, t_pos, val_elemlist);
    va_end(val_elemlist);

    return t_pos;
}

/**
 * Find a last occurrence of a character that is not equal to specificed element.
 */
size_t _basic_string_find_last_not_of_elem_varg(const basic_string_t* cpt_basic_string, size_t t_pos, va_list val_elemlist)
{
    size_t   t_typesize = 0;
    size_t   t_length = 0;
    void*    pv_varg = NULL;
    _byte_t* pby_string = NULL;
    size_t   t_findpos = 0;
    bool_t   b_less = false;
    bool_t   b_greater = false;

    assert(cpt_basic_string != NULL);

    if (basic_string_empty(cpt_basic_string)) {
        return NPOS;
    }

    /* get element */
    t_typesize = _GET_BASIC_STRING_TYPE_SIZE(cpt_basic_string);
    pv_varg = _alloc_allocate(&((basic_string_t*)cpt_basic_string)->_vec_base._t_allocator, t_typesize, 1);
    assert(pv_varg != NULL);
    _basic_string_get_varg_value_auxiliary((basic_string_t*)cpt_basic_string, val_elemlist, pv_varg);

    /* find elemen */
    t_length = basic_string_length(cpt_basic_string);
    pby_string = _BASIC_STRING_ITERATOR_COREPOS(basic_string_begin(cpt_basic_string));
    if (t_pos > t_length) {
        t_pos = t_length;
    }
    t_findpos = (t_pos == t_length ? t_pos - 1 : t_pos);
    for (;;) {
        b_less = b_greater = t_typesize;
        _GET_BASIC_STRING_TYPE_LESS_FUNCTION(cpt_basic_string)(pby_string + t_findpos * t_typesize, pv_varg, &b_less);
        _GET_BASIC_STRING_TYPE_LESS_FUNCTION(cpt_basic_string)(pv_varg, pby_string + t_findpos * t_typesize, &b_greater);
        if (b_less || b_greater) {
            break;
        } else {
            if (t_findpos > 0) {
                t_findpos--;
            } else {
                t_findpos = NPOS;
                break;
            }
        }
    }

    _basic_string_destroy_varg_value_auxiliary((basic_string_t*)cpt_basic_string, pv_varg);
    _alloc_deallocate(&((basic_string_t*)cpt_basic_string)->_vec_base._t_allocator, pv_varg, t_typesize, 1);

    return t_findpos;
}

/**
 * Reset the size of basic_string elements.
 */
void _basic_string_resize(basic_string_t* pt_basic_string, size_t t_resize, ...)
{
    va_list val_elemlist;

    va_start(val_elemlist, t_resize);
    _basic_string_resize_varg(pt_basic_string, t_resize, val_elemlist);
    va_end(val_elemlist);
}

/**
 * Reset the size of basic_string elements, and filled element is from variable argument list.
 */
void _basic_string_resize_varg(basic_string_t* pt_basic_string, size_t t_resize, va_list val_elemlist)
{
    assert(pt_basic_string != NULL);

    _vector_resize_elem_varg(&pt_basic_string->_vec_base, t_resize, val_elemlist);
}

/**
 * Erase the last element.
 */
void _basic_string_pop_back(basic_string_t* pt_basic_string)
{
    assert(pt_basic_string != NULL);

    vector_pop_back(&pt_basic_string->_vec_base);
}

/**
 * Adds an element to basic string.
 */
void _basic_string_push_back(basic_string_t* pt_basic_string, ...)
{
    va_list val_elemlist;

    va_start(val_elemlist, pt_basic_string);
    _basic_string_push_back_varg(pt_basic_string, val_elemlist);
    va_end(val_elemlist);
}

/**
 * Adds an element to basic string.
 */
void _basic_string_push_back_varg(basic_string_t* pt_basic_string, va_list val_elemlist)
{
    assert(pt_basic_string != NULL);

    _vector_push_back_varg(&pt_basic_string->_vec_base, val_elemlist);
}

/**
 * Assign new element to basic_string.
 */
void _basic_string_assign_elem(basic_string_t* pt_basic_string, size_t t_count, ...)
{
    va_list val_elemlist;

    va_start(val_elemlist, t_count);
    _basic_string_assign_elem_varg(pt_basic_string, t_count, val_elemlist);
    va_end(val_elemlist);
}

/**
 * Assign new element to basic_string.
 */
void _basic_string_assign_elem_varg(basic_string_t* pt_basic_string, size_t t_count, va_list val_elemlist)
{
    assert(pt_basic_string != NULL);

    _vector_assign_elem_varg(&pt_basic_string->_vec_base, t_count, val_elemlist);
}


/**
 * Appends characters to the end of basic string.
 */
void _basic_string_append_elem(basic_string_t* pt_basic_string, size_t t_count, ...)
{
    va_list val_elemlist;

    va_start(val_elemlist, t_count);
    _basic_string_append_elem_varg(pt_basic_string, t_count, val_elemlist);
    va_end(val_elemlist);
}

/**
 * Appends characters to the end of basic string.
 */
void _basic_string_append_elem_varg(basic_string_t* pt_basic_string, size_t t_count, va_list val_elemlist)
{
    _basic_string_resize_varg(pt_basic_string, basic_string_size(pt_basic_string) + t_count, val_elemlist);
}

/**
 * Insert one copy of element befor specificed position.
 */
basic_string_iterator_t _basic_string_insert(basic_string_t* pt_basic_string, basic_string_iterator_t it_pos, ...)
{
    basic_string_iterator_t it_iter;
    va_list val_elemlist;

    va_start(val_elemlist, it_pos);
    it_iter = _basic_string_insert_n_varg(pt_basic_string, it_pos, 1, val_elemlist);
    va_end(val_elemlist);

    return it_iter;
}

/**
 * Insert multiple copys of element befor specificed position.
 */
basic_string_iterator_t _basic_string_insert_n(
    basic_string_t* pt_basic_string, basic_string_iterator_t it_pos, size_t t_count, ...)
{
    basic_string_iterator_t it_iter;
    va_list val_elemlist;

    va_start(val_elemlist, t_count);
    it_iter = _basic_string_insert_n_varg(pt_basic_string, it_pos, t_count, val_elemlist);
    va_end(val_elemlist);

    return it_iter;
}

/**
 * Insert multiple copys of element befor specificed position, the element is from variable argument list.
 */
basic_string_iterator_t _basic_string_insert_n_varg(
    basic_string_t* pt_basic_string, basic_string_iterator_t it_pos, size_t t_count, va_list val_elemlist)
{
    basic_string_iterator_t it_iter;
    assert(pt_basic_string != NULL);

    _BASIC_STRING_ITERATOR_CONTAINER_TYPE(it_pos) = _VECTOR_CONTAINER;
    it_iter = _vector_insert_n_varg(&pt_basic_string->_vec_base, it_pos, t_count, val_elemlist);
    _BASIC_STRING_ITERATOR_CONTAINER_TYPE(it_iter) = _BASIC_STRING_CONTAINER;

    return it_iter;
}

/**
 * Insert multiple copys of element befor specificed position.
 */
void _basic_string_insert_elem(basic_string_t* pt_basic_string, size_t t_pos, size_t t_count, ...)
{
    va_list val_elemlist;

    va_start(val_elemlist, t_count);
    _basic_string_insert_elem_varg(pt_basic_string, t_pos, t_count, val_elemlist);
    va_end(val_elemlist);
}

/**
 * Insert multiple copys of element befor specificed position, the element is from variable argument list.
 */
void _basic_string_insert_elem_varg(basic_string_t* pt_basic_string, size_t t_pos, size_t t_count, va_list val_elemlist)
{
    basic_string_iterator_t it_pos;

    assert(pt_basic_string != NULL);
    assert(t_pos <= basic_string_size(pt_basic_string));

    it_pos = iterator_next_n(basic_string_begin(pt_basic_string), t_pos);
    _VECTOR_ITERATOR_CONTAINER_TYPE(it_pos) = _VECTOR_CONTAINER;
    _vector_insert_n_varg(&pt_basic_string->_vec_base, it_pos, t_count, val_elemlist);
}


/**
 * Replace elements at specificed posititon.
 */
void _basic_string_replace_elem(basic_string_t* pt_basic_string, size_t t_pos, size_t t_len, size_t t_count, ...)
{
    va_list val_elemlist;

    va_start(val_elemlist, t_count);
    _basic_string_replace_elem_varg(pt_basic_string, t_pos, t_len, t_count, val_elemlist);
    va_end(val_elemlist);
}

/**
 * Replace elements at specificed posititon.
 */
void _basic_string_replace_elem_varg(
    basic_string_t* pt_basic_string, size_t t_pos, size_t t_len, size_t t_count, va_list val_elemlist)
{
    basic_string_iterator_t it_begin;
    basic_string_iterator_t it_end;

    assert(t_pos <= basic_string_size(pt_basic_string));

    it_begin = iterator_next_n(basic_string_begin(pt_basic_string), t_pos);
    if (t_len == NPOS || t_pos + t_len >= basic_string_size(pt_basic_string)) {
        it_end = basic_string_end(pt_basic_string);
    } else {
        it_end = iterator_next_n(basic_string_begin(pt_basic_string), t_pos + t_len);
    }
    _basic_string_range_replace_elem_varg(pt_basic_string, it_begin, it_end, t_count, val_elemlist);
}

/**
 * Replace elements at specificed posititon.
 */
void _basic_string_range_replace_elem(
    basic_string_t* pt_basic_string, basic_string_iterator_t it_begin, basic_string_iterator_t it_end, size_t t_count, ...)
{
    va_list val_elemlist;

    va_start(val_elemlist, t_count);
    _basic_string_range_replace_elem_varg(pt_basic_string, it_begin, it_end, t_count, val_elemlist);
    va_end(val_elemlist);
}

/**
 * Replace elements at specificed posititon.
 */
void _basic_string_range_replace_elem_varg(
    basic_string_t* pt_basic_string, basic_string_iterator_t it_begin, basic_string_iterator_t it_end,
    size_t t_count, va_list val_elemlist)
{
    basic_string_iterator_t it_pos = basic_string_erase_range(pt_basic_string, it_begin, it_end);
    _basic_string_insert_n_varg(pt_basic_string, it_pos, t_count, val_elemlist);
}

/**
 * Initialize element with basic_string element type auxiliary function.
 */
void _basic_string_init_elem_auxiliary(basic_string_t* pt_basic_string, void* pv_elem)
{
    assert(pt_basic_string != NULL);
    assert(pv_elem != NULL);

    /* initialize new elements */
    if (_GET_BASIC_STRING_TYPE_STYLE(pt_basic_string) == _TYPE_CSTL_BUILTIN) {
        /* get element type name */
        char s_elemtypename[_TYPE_NAME_SIZE + 1];
        _type_get_elem_typename(_GET_BASIC_STRING_TYPE_NAME(pt_basic_string), s_elemtypename);

        _GET_BASIC_STRING_TYPE_INIT_FUNCTION(pt_basic_string)(pv_elem, s_elemtypename);
    } else {
        bool_t b_result = _GET_BASIC_STRING_TYPE_SIZE(pt_basic_string);
        _GET_BASIC_STRING_TYPE_INIT_FUNCTION(pt_basic_string)(pv_elem, &b_result);
        assert(b_result);
    }
}

/** local function implementation section **/

/** eof **/

