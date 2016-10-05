#include "API/list.h"
#include "criterion/criterion.h"

int t_intCmp(void* a, void* b)
{
    int res = (*(int*)a) - (*(int*)b);
    return res;
}

Test(List_test, t_neg__List_new)
{
    
    cr_expect_eq(List_new(NULL), NULL, "Expected List_new() to fail on NULL compare");

    List* t_list = List_new(t_intCmp);
    cr_expect_neq(t_list, NULL, "List_new() failed to allocate list");

    List_delete(t_list);
}

Test(List_test, t_pos__List_new)
{
    List* t_list = List_new(t_intCmp);
    cr_assert_neq(t_list,  NULL, "List_new() failed!");
    List_delete(t_list);
}
