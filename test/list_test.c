#include "LIST/list.h"
#include "criterion/criterion.h"

int t_intCmp(void* a, void* b)
{
    int res = (*(int*)a) - (*(int*)b);
    return res;
}

Test(List_test, t_neg__List_create)
{
    
    cr_expect_eq(List_create(NULL), NULL, "Expected List_create() to fail on NULL compare");

    List* t_list = List_create(t_intCmp);
    cr_expect_neq(t_list, NULL, "List_create() failed to allocate list");

    List_delete(t_list);
}

Test(List_test, t_pos__List_create)
{
    List* t_list = List_create(t_intCmp);
    cr_assert_neq(t_list,  NULL, "List_create() failed!");
    List_delete(t_list);
}
