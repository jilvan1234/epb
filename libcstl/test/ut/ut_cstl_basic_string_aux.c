#include <stddef.h>
#include <stdarg.h>
#include <setjmp.h>
#include <google/cmockery.h>

#include "cstl/cstl_def.h"
#include "cstl/citerator.h"
#include "cstl/clist.h"
#include "cstl/cvector.h"
#include "cstl/cstl_basic_string_iterator.h"
#include "cstl/cstl_basic_string_private.h"
#include "cstl/cstl_basic_string.h"
#include "cstl_basic_string_aux.h"

#include "ut_def.h"
#include "ut_cstl_basic_string_aux.h"

UT_SUIT_DEFINATION(cstl_basic_string_aux, _basic_string_same_type)

/*
 * test _basic_string_same_type
 */
UT_CASE_DEFINATION(_basic_string_same_type)
void test__basic_string_same_type__null_first(void** state)
{
    basic_string_t* pt_basic_string = create_basic_string(int);
    basic_string_init(pt_basic_string);

    expect_assert_failure(_basic_string_same_type(NULL, pt_basic_string));

    basic_string_destroy(pt_basic_string);
}

void test__basic_string_same_type__null_second(void** state)
{
    basic_string_t* pt_basic_string = create_basic_string(int);
    basic_string_init(pt_basic_string);

    expect_assert_failure(_basic_string_same_type(pt_basic_string, NULL));

    basic_string_destroy(pt_basic_string);
}

void test__basic_string_same_type__non_created_first(void** state)
{
    basic_string_t bstring;
    basic_string_t* pt_basic_string = create_basic_string(int);
    basic_string_init(pt_basic_string);

    bstring._vec_base._t_typeinfo._t_style = 100;
    expect_assert_failure(_basic_string_same_type(&bstring, pt_basic_string));

    basic_string_destroy(pt_basic_string);
}

void test__basic_string_same_type__non_created_second(void** state)
{
    basic_string_t bstring;
    basic_string_t* pt_basic_string = create_basic_string(int);
    basic_string_init(pt_basic_string);

    bstring._vec_base._t_typeinfo._t_style = 100;
    expect_assert_failure(_basic_string_same_type(pt_basic_string, &bstring));

    basic_string_destroy(pt_basic_string);
}

void test__basic_string_same_type__not_same_type_name(void** state)
{
    basic_string_t* pt_first = create_basic_string(int);
    basic_string_t* pt_second = create_basic_string(double);
    basic_string_init(pt_first);
    basic_string_init(pt_second);

    assert_false(_basic_string_same_type(pt_first, pt_second));

    basic_string_destroy(pt_first);
    basic_string_destroy(pt_second);
}

void test__basic_string_same_type__not_same_type_pointer(void** state)
{
    basic_string_t* pt_first = create_basic_string(int);
    basic_string_t* pt_second = create_basic_string(double);
    basic_string_init(pt_first);
    basic_string_init(pt_second);

    assert_false(_basic_string_same_type(pt_first, pt_second));

    basic_string_destroy(pt_first);
    basic_string_destroy(pt_second);
}

void test__basic_string_same_type__not_same_type_style(void** state)
{
    basic_string_t* pt_first = create_basic_string(int);
    basic_string_t* pt_second = create_basic_string(list_t<int>);
    basic_string_init(pt_first);
    basic_string_init(pt_second);

    assert_false(_basic_string_same_type(pt_first, pt_second));

    basic_string_destroy(pt_first);
    basic_string_destroy(pt_second);
}

void test__basic_string_same_type__not_same_type_style_ex1(void** state)
{
    basic_string_t* pt_first = create_basic_string(iterator_t);
    basic_string_t* pt_second = create_basic_string(list_t<int>);
    basic_string_init(pt_first);
    basic_string_init(pt_second);

    assert_false(_basic_string_same_type(pt_first, pt_second));

    basic_string_destroy(pt_first);
    basic_string_destroy(pt_second);
}

void test__basic_string_same_type__not_same_type_style_ex2(void** state)
{
    basic_string_t* pt_first = create_basic_string(list_t<double>);
    basic_string_t* pt_second = create_basic_string(list_t<int>);
    basic_string_init(pt_first);
    basic_string_init(pt_second);

    assert_false(_basic_string_same_type(pt_first, pt_second));

    basic_string_destroy(pt_first);
    basic_string_destroy(pt_second);
}


void test__basic_string_same_type__same_type(void** state)
{
    basic_string_t* pt_first = create_basic_string(int);
    basic_string_t* pt_second = create_basic_string(int);
    basic_string_init(pt_first);
    basic_string_init(pt_second);

    assert_true(_basic_string_same_type(pt_first, pt_second));

    basic_string_destroy(pt_first);
    basic_string_destroy(pt_second);
}

void test__basic_string_same_type__same_type_duplicate_name(void** state)
{
    basic_string_t* pt_first = create_basic_string(int);
    basic_string_t* pt_second = create_basic_string(signed);
    basic_string_init(pt_first);
    basic_string_init(pt_second);

    assert_true(_basic_string_same_type(pt_first, pt_second));

    basic_string_destroy(pt_first);
    basic_string_destroy(pt_second);
}

void test__basic_string_same_type__same_container(void** state)
{
    basic_string_t* pt_basic_string = create_basic_string(int);
    basic_string_init(pt_basic_string);

    assert_true(_basic_string_same_type(pt_basic_string, pt_basic_string));

    basic_string_destroy(pt_basic_string);
}

/*
 * test _basic_string_get_value_string_length
 */
UT_CASE_DEFINATION(_basic_string_get_value_string_length)
void test__basic_string_get_value_string_length__null_basic_string(void** state)
{
    expect_assert_failure(_basic_string_get_value_string_length(NULL, (void*)0xcc));
}

void test__basic_string_get_value_string_length__null_value_string(void** state)
{
    basic_string_t* pt_basic_string = create_basic_string(int);

    basic_string_init(pt_basic_string);
    expect_assert_failure(_basic_string_get_value_string_length(pt_basic_string, NULL));

    basic_string_destroy(pt_basic_string);
}

void test__basic_string_get_value_string_length__c_builtin_empty(void** state)
{
    basic_string_t* pt_basic_string = create_basic_string(int);
    int vstring[10] = {0};

    basic_string_init(pt_basic_string);
    assert_true(_basic_string_get_value_string_length(pt_basic_string, vstring) == 0);

    basic_string_destroy(pt_basic_string);
}

void test__basic_string_get_value_string_length__c_builtin_non_empty(void** state)
{
    basic_string_t* pt_basic_string = create_basic_string(int);
    int vstring[10] = {1, 2, 3, 4, 5, 0, 7, 8, 9, -1};

    basic_string_init(pt_basic_string);
    assert_true(_basic_string_get_value_string_length(pt_basic_string, vstring) == 5);

    basic_string_destroy(pt_basic_string);
}

void test__basic_string_get_value_string_length__c_builtin_no_terminal(void** state)
{
    basic_string_t* pt_basic_string = create_basic_string(int);
    int vstring[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, -1};

    basic_string_init(pt_basic_string);
    /*assert_true(_basic_string_get_value_string_length(pt_basic_string, vstring) >= 10);*/

    basic_string_destroy(pt_basic_string);
}

void test__basic_string_get_value_string_length__char_empty(void** state)
{
    basic_string_t* pt_basic_string = create_basic_string(char);

    basic_string_init(pt_basic_string);
    assert_true(_basic_string_get_value_string_length(pt_basic_string, "") == 0);

    basic_string_destroy(pt_basic_string);
}

void test__basic_string_get_value_string_length__char_non_empty(void** state)
{
    basic_string_t* pt_basic_string = create_basic_string(char);

    basic_string_init(pt_basic_string);
    assert_true(_basic_string_get_value_string_length(pt_basic_string, "abc0ef") == 6);

    basic_string_destroy(pt_basic_string);
}

void test__basic_string_get_value_string_length__char_no_terminal(void** state)
{
    basic_string_t* pt_basic_string = create_basic_string(char);
    char elems[] = {'a', 'a', 'a'};

    basic_string_init(pt_basic_string);
    /*assert_true(_basic_string_get_value_string_length(pt_basic_string, elems) == 6);*/

    basic_string_destroy(pt_basic_string);
}

void test__basic_string_get_value_string_length__cstr_empty(void** state)
{
    basic_string_t* pt_basic_string = create_basic_string(char*);
    const char* elems[] = {NULL};

    basic_string_init(pt_basic_string);
    assert_true(_basic_string_get_value_string_length(pt_basic_string, elems) == 0);

    basic_string_destroy(pt_basic_string);
}

void test__basic_string_get_value_string_length__cstr_non_empty(void** state)
{
    basic_string_t* pt_basic_string = create_basic_string(char*);
    const char* elems[] = {"abc", "def", "hij", NULL, "aaaa"};

    basic_string_init(pt_basic_string);
    assert_true(_basic_string_get_value_string_length(pt_basic_string, elems) == 3);

    basic_string_destroy(pt_basic_string);
}

void test__basic_string_get_value_string_length__cstr_no_terminal(void** state)
{
    basic_string_t* pt_basic_string = create_basic_string(char*);
    const char* elems[] = {"abc", "def", "hij", "aaaa"};

    basic_string_init(pt_basic_string);
    /*assert_true(_basic_string_get_value_string_length(pt_basic_string, elems) == 3);*/

    basic_string_destroy(pt_basic_string);
}

void test__basic_string_get_value_string_length__libcstl_builtin_empty(void** state)
{
    basic_string_t* pt_basic_string = create_basic_string(list_t<int>);
    list_t* elems[] = {NULL};

    basic_string_init(pt_basic_string);
    assert_true(_basic_string_get_value_string_length(pt_basic_string, elems) == 0);

    basic_string_destroy(pt_basic_string);
}

void test__basic_string_get_value_string_length__libcstl_builtin_non_empty(void** state)
{
    basic_string_t* pt_basic_string = create_basic_string(list_t<int>);
    list_t* plist_1 = create_list(int);
    list_t* plist_2 = create_list(int);
    list_t* plist_3 = create_list(int);
    list_t* plist_4 = create_list(int);
    list_t* elems[5] = {NULL};

    list_init(plist_1);
    list_init(plist_2);
    list_init(plist_3);
    list_init(plist_4);
    basic_string_init(pt_basic_string);
    elems[0] = plist_1;
    elems[1] = plist_2;
    elems[2] = NULL;
    elems[3] = plist_3;
    elems[4] = plist_4;
    assert_true(_basic_string_get_value_string_length(pt_basic_string, elems) == 2);

    basic_string_destroy(pt_basic_string);
    list_destroy(plist_1);
    list_destroy(plist_2);
    list_destroy(plist_3);
    list_destroy(plist_4);
}

void test__basic_string_get_value_string_length__libcstl_builtin_no_terminal(void** state)
{
    basic_string_t* pt_basic_string = create_basic_string(list_t<int>);
    list_t* plist_1 = create_list(int);
    list_t* plist_2 = create_list(int);
    list_t* plist_3 = create_list(int);
    list_t* plist_4 = create_list(int);
    list_t* elems[5] = {NULL};

    list_init(plist_1);
    list_init(plist_2);
    list_init(plist_3);
    list_init(plist_4);
    basic_string_init(pt_basic_string);
    elems[0] = plist_1;
    elems[1] = plist_2;
    elems[2] = plist_2;
    elems[3] = plist_3;
    elems[4] = plist_4;
    /*assert_true(_basic_string_get_value_string_length(pt_basic_string, elems) == 2);*/

    basic_string_destroy(pt_basic_string);
    list_destroy(plist_1);
    list_destroy(plist_2);
    list_destroy(plist_3);
    list_destroy(plist_4);
}

typedef struct _tagtest__basic_string_get_value_string_length__user_define
{
    int n_first;
    double d_second;
}_test__basic_string_get_value_string_length__user_define;

void test__basic_string_get_value_string_length__user_define_empty(void** state)
{
    basic_string_t* pt_basic_string = NULL;
    _test__basic_string_get_value_string_length__user_define* elems[] = {NULL};

    type_register(_test__basic_string_get_value_string_length__user_define, NULL, NULL, NULL, NULL);

    pt_basic_string = create_basic_string(_test__basic_string_get_value_string_length__user_define);

    basic_string_init(pt_basic_string);
    assert_true(_basic_string_get_value_string_length(pt_basic_string, elems) == 0);

    basic_string_destroy(pt_basic_string);
}

void test__basic_string_get_value_string_length__user_define_non_empty(void** state)
{
    basic_string_t* pt_basic_string = create_basic_string(_test__basic_string_get_value_string_length__user_define);
    _test__basic_string_get_value_string_length__user_define t_user;
    _test__basic_string_get_value_string_length__user_define* elems[5] = {&t_user, &t_user, &t_user, NULL, &t_user};

    basic_string_init(pt_basic_string);
    assert_true(_basic_string_get_value_string_length(pt_basic_string, elems) == 3);

    basic_string_destroy(pt_basic_string);
}

void test__basic_string_get_value_string_length__user_define_no_terminal(void** state)
{
    basic_string_t* pt_basic_string = create_basic_string(_test__basic_string_get_value_string_length__user_define);
    _test__basic_string_get_value_string_length__user_define t_user;
    _test__basic_string_get_value_string_length__user_define* elems[5] = {&t_user, &t_user, &t_user, &t_user, &t_user};

    basic_string_init(pt_basic_string);
    /*assert_true(_basic_string_get_value_string_length(pt_basic_string, &vstr) >= 5);*/

    basic_string_destroy(pt_basic_string);
}

/*
 * test _basic_string_get_varg_value_auxiliary
 */
UT_CASE_DEFINATION(_basic_string_get_varg_value_auxiliary)

static void _wrapper_basic_string_get_varg_value_auxiliary(basic_string_t* pt_basic_string, void* pv_varg, ...)
{
    va_list val_elemlist;
    va_start(val_elemlist, pv_varg);
    _basic_string_get_varg_value_auxiliary(pt_basic_string, val_elemlist, pv_varg);
    va_end(val_elemlist);
}

void test__basic_string_get_varg_value_auxiliary__null_basic_string_container(void** state)
{
    int varg = 0;
    expect_assert_failure(_wrapper_basic_string_get_varg_value_auxiliary(NULL, &varg, 100));
}

void test__basic_string_get_varg_value_auxiliary__null_varg(void** state)
{
    basic_string_t* pt_basic_string = create_basic_string(int);
    basic_string_init(pt_basic_string);
    expect_assert_failure(_wrapper_basic_string_get_varg_value_auxiliary(pt_basic_string, NULL, 100));
    basic_string_destroy(pt_basic_string);
}

void test__basic_string_get_varg_value_auxiliary__non_created(void** state)
{
    int varg = 0;
    /*basic_string_t bstr;*/
    /*bstr._vec_base._t_typeinfo._t_style = 100;*/
    /*expect_assert_failure(_wrapper_basic_string_get_varg_value_auxiliary(&bstr, &varg, 100));*/
    assert_true(true);
}

void test__basic_string_get_varg_value_auxiliary__successfully(void** state)
{
    int varg = 0;
    basic_string_t* pt_basic_string = create_basic_string(int);
    basic_string_init(pt_basic_string);
    _wrapper_basic_string_get_varg_value_auxiliary(pt_basic_string, &varg, 100);
    assert_int_equal(varg, 100);
    basic_string_destroy(pt_basic_string);
}

/*
 * test _basic_string_destroy_varg_value_auxiliary
 */
UT_CASE_DEFINATION(_basic_string_destroy_varg_value_auxiliary)
void test__basic_string_destroy_varg_value_auxiliary__null_basic_string_container(void** state)
{
    int varg = 0;
    expect_assert_failure(_basic_string_destroy_varg_value_auxiliary(NULL, &varg));
}

void test__basic_string_destroy_varg_value_auxiliary__null_varg(void** state)
{
    basic_string_t* pt_basic_string = create_basic_string(int);
    basic_string_init(pt_basic_string);
    expect_assert_failure(_basic_string_destroy_varg_value_auxiliary(pt_basic_string, NULL));
    basic_string_destroy(pt_basic_string);
}

void test__basic_string_destroy_varg_value_auxiliary__non_created(void** state)
{
    int varg = 0;
    /*basic_string_t bstr;*/
    /*bstr._vec_base._t_typeinfo._t_style = 100;*/
    /*expect_assert_failure(_basic_string_destroy_varg_value_auxiliary(&bstr, &varg));*/
    assert_true(true);
}

void test__basic_string_destroy_varg_value_auxiliary__successfully(void** state)
{
    int varg = 100;
    basic_string_t* pt_basic_string = create_basic_string(int);
    basic_string_init(pt_basic_string);
    _basic_string_destroy_varg_value_auxiliary(pt_basic_string, &varg);
    basic_string_destroy(pt_basic_string);
}

