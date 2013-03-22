/*
 *  The implementation of base algorithm.
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
#include <cstl/cfunctional.h>
#include <cstl/cstring.h>

#include <cstl/cstl_algobase.h>
#include <cstl/cstl_algobase_private.h>

/** local constant declaration and local macro section **/

/** local data type declaration and local struct, union, enum section **/

/** local function prototype section **/

/** exported global variable definition section **/

/** local global variable definition section **/

/** exported function implementation section **/
bool_t algo_equal(
    input_iterator_t t_first1, input_iterator_t t_last1, input_iterator_t t_first2)
{
    return algo_equal_if(t_first1, t_last1, t_first2, _fun_get_binary(t_first1, _EQUAL_FUN));
}

bool_t algo_equal_if(
    input_iterator_t t_first1, input_iterator_t t_last1, input_iterator_t t_first2,
    binary_function_t t_binary_op)
{
    bool_t t_result = false;
    bool_t t_less = false;
    bool_t t_greater = false;

    assert(_iterator_valid_range(t_first1, t_last1, _INPUT_ITERATOR));
    assert(_iterator_limit_type(t_first2, _INPUT_ITERATOR));
    assert(_iterator_same_elem_type(t_first1, t_first2));

    if(t_binary_op == NULL)
    {
        t_binary_op = _fun_get_binary(t_first1, _EQUAL_FUN);
    }

    if(t_binary_op == fun_default_binary)
    {
        t_binary_op = _fun_get_binary(t_first1, _LESS_FUN);
        for(; !iterator_equal(t_first1, t_last1);
            t_first1 = iterator_next(t_first1), t_first2 = iterator_next(t_first2))
        {
            (*t_binary_op)(
                iterator_get_pointer(t_first1), iterator_get_pointer(t_first2), &t_less);
            if(t_less)
            {
                return false;
            }
            (*t_binary_op)(
                iterator_get_pointer(t_first2), iterator_get_pointer(t_first1), &t_greater);
            if(t_greater)
            {
                return false;
            }
        }
    }
    else
    {
        for(; !iterator_equal(t_first1, t_last1);
            t_first1 = iterator_next(t_first1), t_first2 = iterator_next(t_first2))
        {
            (*t_binary_op)(
                iterator_get_pointer(t_first1), iterator_get_pointer(t_first2), &t_result);
            if(!t_result)
            {
                return false;
            }
        }
    }

    return true;
}

void _algo_fill(
    forward_iterator_t t_first, forward_iterator_t t_last, ...)
{
    va_list val_elemlist;

    va_start(val_elemlist, t_last);
    _algo_fill_varg(t_first, t_last, val_elemlist);
    va_end(val_elemlist);
}

void _algo_fill_varg(
    forward_iterator_t t_first, forward_iterator_t t_last, va_list val_elemlist)
{
    void* pv_value = NULL;

    assert(_iterator_valid_range(t_first, t_last, _FORWARD_ITERATOR));

    pv_value = _iterator_allocate_init_elem(t_first);
    _type_get_varg_value(_iterator_get_typeinfo(t_first), val_elemlist, pv_value);

    if(strncmp(_iterator_get_typebasename(t_first), _C_STRING_TYPE, _TYPE_NAME_SIZE) == 0)
    {
        for(; !iterator_equal(t_first, t_last); t_first = iterator_next(t_first))
        {
            iterator_set_value(t_first, string_c_str((string_t*)pv_value));
        }
    }
    else
    {
        for(; !iterator_equal(t_first, t_last); t_first = iterator_next(t_first))
        {
            iterator_set_value(t_first, pv_value);
        }
    }

    _iterator_deallocate_destroy_elem(t_first, pv_value);
    pv_value = NULL;
}

output_iterator_t _algo_fill_n(
    output_iterator_t t_first, size_t t_fillsize, ...)
{
    output_iterator_t t_iter;
    va_list val_elemlist;

    va_start(val_elemlist, t_fillsize);
    t_iter = _algo_fill_n_varg(t_first, t_fillsize, val_elemlist);
    va_end(val_elemlist);

    return t_iter;
}

output_iterator_t _algo_fill_n_varg(
    output_iterator_t t_first, size_t t_fillsize, va_list val_elemlist)
{
    size_t t_index = 0;
    void*  pv_value = NULL;
 
    pv_value = _iterator_allocate_init_elem(t_first);
    _type_get_varg_value(_iterator_get_typeinfo(t_first), val_elemlist, pv_value);

    if(strncmp(_iterator_get_typebasename(t_first), _C_STRING_TYPE, _TYPE_NAME_SIZE) == 0)
    {
        for(t_index = 0; t_index < t_fillsize; ++t_index, t_first = iterator_next(t_first))
        {
            iterator_set_value(t_first, string_c_str((string_t*)pv_value));
        }
    }
    else
    {
        for(t_index = 0; t_index < t_fillsize; ++t_index, t_first = iterator_next(t_first))
        {
            iterator_set_value(t_first, pv_value);
        }
    }

    _iterator_deallocate_destroy_elem(t_first, pv_value);
    pv_value = NULL;

    return t_first;
}

void algo_swap(forward_iterator_t t_first, forward_iterator_t t_second)
{
    algo_iter_swap(t_first, t_second);
}

void algo_iter_swap(forward_iterator_t t_first, forward_iterator_t t_second)
{
    void* pv_value = NULL;

    assert(_iterator_same_elem_type(t_first, t_second));

    if(!iterator_equal(t_first, t_second))
    {
        pv_value = _iterator_allocate_init_elem(t_first);

        /* c string */
        if(strncmp(_iterator_get_typebasename(t_first), _C_STRING_TYPE, _TYPE_NAME_SIZE) == 0)
        {
            string_assign_cstr((string_t*)pv_value, iterator_get_pointer(t_first));
            iterator_set_value(t_first, iterator_get_pointer(t_second));
            iterator_set_value(t_second, string_c_str((string_t*)pv_value));
        }
        else
        {
            iterator_get_value(t_first, pv_value);
            iterator_set_value(t_first, iterator_get_pointer(t_second));
            iterator_set_value(t_second, pv_value);
        }

        _iterator_deallocate_destroy_elem(t_first, pv_value);
        pv_value = NULL;
    }
}

bool_t algo_lexicographical_compare(
    input_iterator_t t_first1, input_iterator_t t_last1,
    input_iterator_t t_first2, input_iterator_t t_last2)
{
    return algo_lexicographical_compare_if(t_first1, t_last1, t_first2, t_last2,
        _fun_get_binary(t_first1, _LESS_FUN));
}

bool_t algo_lexicographical_compare_if(
    input_iterator_t t_first1, input_iterator_t t_last1,
    input_iterator_t t_first2, input_iterator_t t_last2,
    binary_function_t t_binary_op)
{
    bool_t t_result = false;

    assert(_iterator_valid_range(t_first1, t_last1, _INPUT_ITERATOR));
    assert(_iterator_valid_range(t_first2, t_last2, _INPUT_ITERATOR));
    assert(_iterator_same_elem_type(t_first1, t_first2));

    if(t_binary_op == NULL)
    {
        t_binary_op = _fun_get_binary(t_first1, _LESS_FUN);
    }
    for(;
        !iterator_equal(t_first1, t_last1) && !iterator_equal(t_first2, t_last2);
        t_first1 = iterator_next(t_first1), t_first2 = iterator_next(t_first2))
    {
        (*t_binary_op)(
            iterator_get_pointer(t_first1), iterator_get_pointer(t_first2), &t_result);
        if(t_result)
        {
            return true;
        }
        (*t_binary_op)(
            iterator_get_pointer(t_first2), iterator_get_pointer(t_first1), &t_result);
        if(t_result)
        {
            return false;
        }
    }

    if(iterator_equal(t_first1, t_last1) && !iterator_equal(t_first2, t_last2))
    {
        return true;
    }
    else
    {
        return false;
    }
}

int algo_lexicographical_compare_3way(
    input_iterator_t t_first1, input_iterator_t t_last1,
    input_iterator_t t_first2, input_iterator_t t_last2)
{
    return algo_lexicographical_compare_3way_if(t_first1, t_last1, t_first2, t_last2,
        _fun_get_binary(t_first1, _LESS_FUN));
}

int algo_lexicographical_compare_3way_if(
    input_iterator_t t_first1, input_iterator_t t_last1,
    input_iterator_t t_first2, input_iterator_t t_last2,
    binary_function_t t_binary_op)
{
    bool_t t_result = false;

    assert(_iterator_valid_range(t_first1, t_last1, _INPUT_ITERATOR));
    assert(_iterator_valid_range(t_first2, t_last2, _INPUT_ITERATOR));
    assert(_iterator_same_elem_type(t_first1, t_first2));

    if(t_binary_op == NULL)
    {
        t_binary_op = _fun_get_binary(t_first1, _LESS_FUN);
    }
    for(;
        !iterator_equal(t_first1, t_last1) && !iterator_equal(t_first2, t_last2);
        t_first1 = iterator_next(t_first1), t_first2 = iterator_next(t_first2))
    {
        (*t_binary_op)(
            iterator_get_pointer(t_first1), iterator_get_pointer(t_first2), &t_result);
        if(t_result)
        {
            return -1;
        }
        (*t_binary_op)(
            iterator_get_pointer(t_first2), iterator_get_pointer(t_first1), &t_result);
        if(t_result)
        {
            return 1;
        }
    }

    if(iterator_equal(t_first1, t_last1) && !iterator_equal(t_first2, t_last2))
    {
        return -1;
    }
    else if(iterator_equal(t_first1, t_last1) && iterator_equal(t_first2, t_last2))
    {
        return 0;
    }
    else
    {
        return 1;
    }
}

input_iterator_t algo_max(input_iterator_t t_first, input_iterator_t t_second)
{
    return algo_max_if(t_first, t_second, _fun_get_binary(t_first, _LESS_FUN));
}

input_iterator_t algo_max_if(
    input_iterator_t t_first, input_iterator_t t_second, binary_function_t t_binary_op)
{
    bool_t t_result = false;

    assert(_iterator_limit_type(t_first, _INPUT_ITERATOR));
    assert(_iterator_limit_type(t_second, _INPUT_ITERATOR));
    assert(_iterator_same_elem_type(t_first, t_second));

    if(t_binary_op == NULL)
    {
        t_binary_op = _fun_get_binary(t_first, _LESS_FUN);
    }

    (*t_binary_op)(
        iterator_get_pointer(t_first), iterator_get_pointer(t_second), &t_result);
    if(!t_result)
    {
        return t_first;
    }
    else
    {
        return t_second;
    }
}

input_iterator_t algo_min(input_iterator_t t_first, input_iterator_t t_second)
{
    return algo_min_if(t_first, t_second, _fun_get_binary(t_first, _LESS_FUN));
}

input_iterator_t algo_min_if(
    input_iterator_t t_first, input_iterator_t t_second, binary_function_t t_binary_op)
{
    bool_t t_result = false;

    assert(_iterator_limit_type(t_first, _INPUT_ITERATOR));
    assert(_iterator_limit_type(t_second, _INPUT_ITERATOR));
    assert(_iterator_same_elem_type(t_first, t_second));

    if(t_binary_op == NULL)
    {
        t_binary_op = _fun_get_binary(t_first, _LESS_FUN);
    }

    (*t_binary_op)(
        iterator_get_pointer(t_first), iterator_get_pointer(t_second), &t_result);
    if(t_result)
    {
        return t_first;
    }
    else
    {
        return t_second;
    }
}

range_t algo_mismatch(input_iterator_t t_first1,
    input_iterator_t t_last1, input_iterator_t t_first2)
{
    return algo_mismatch_if(t_first1, t_last1, t_first2,
        _fun_get_binary(t_first1, _EQUAL_FUN));
}

range_t algo_mismatch_if(
    input_iterator_t t_first1, input_iterator_t t_last1, input_iterator_t t_first2,
    binary_function_t t_binary_op)
{
    bool_t  t_result = false;
    bool_t  t_less = false;
    bool_t  t_greater = false;
    range_t t_range;

    assert(_iterator_valid_range(t_first1, t_last1, _INPUT_ITERATOR));
    assert(_iterator_limit_type(t_first2, _INPUT_ITERATOR));
    assert(_iterator_same_elem_type(t_first1, t_first1));

    if(t_binary_op == NULL)
    {
        t_binary_op = _fun_get_binary(t_first1, _EQUAL_FUN);
    }

    if(t_binary_op == fun_default_binary)
    {
        t_binary_op = _fun_get_binary(t_first1, _LESS_FUN);
        for(; !iterator_equal(t_first1, t_last1);
            t_first1 = iterator_next(t_first1), t_first2 = iterator_next(t_first2))
        {
            (*t_binary_op)(
                iterator_get_pointer(t_first1), iterator_get_pointer(t_first2), &t_less);
            if(t_less)
            {
                break;
            }
            (*t_binary_op)(
                iterator_get_pointer(t_first2), iterator_get_pointer(t_first1), &t_greater);
            if(t_greater)
            {
                break;
            }
        }
    }
    else
    {
        for(; !iterator_equal(t_first1, t_last1);
            t_first1 = iterator_next(t_first1), t_first2 = iterator_next(t_first2))
        {
            (*t_binary_op)(
                iterator_get_pointer(t_first1), iterator_get_pointer(t_first2), &t_result);
            if(!t_result)
            {
                break;
            }
        }
    }

    t_range.it_begin = t_first1;
    t_range.it_end = t_first2;
    return t_range;
}

output_iterator_t algo_copy(
    input_iterator_t t_first, input_iterator_t t_last, output_iterator_t t_result)
{
    assert(_iterator_valid_range(t_first, t_last, _INPUT_ITERATOR));
    assert(_iterator_limit_type(t_result, _OUTPUT_ITERATOR));
    assert(_iterator_same_elem_type(t_first, t_result));

    for(;
        !iterator_equal(t_first, t_last);
        t_first = iterator_next(t_first), t_result = iterator_next(t_result))
    {
        iterator_set_value(t_result, iterator_get_pointer(t_first));
    }

    return t_result;
}

output_iterator_t algo_copy_n(
    input_iterator_t t_first, size_t t_count, output_iterator_t t_result)
{
    input_iterator_t t_last = t_first;
    t_last = iterator_advance(t_last, t_count);

    return algo_copy(t_first, t_last, t_result);
}

bidirectional_iterator_t algo_copy_backward(
    bidirectional_iterator_t t_first, bidirectional_iterator_t t_last,
    bidirectional_iterator_t t_result)
{
    assert(_iterator_valid_range(t_first, t_last, _BIDIRECTIONAL_ITERATOR));
    assert(_iterator_limit_type(t_result, _BIDIRECTIONAL_ITERATOR));
    assert(_iterator_same_elem_type(t_first, t_result));

    while(!iterator_equal(t_first, t_last))
    {
        t_last = iterator_prev(t_last);
        t_result = iterator_prev(t_result);
        iterator_set_value(t_result, iterator_get_pointer(t_last));
    }

    return t_result;
}

/** local function implementation section **/

/** eof **/

