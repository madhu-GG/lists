#include "LIST/List.h"
#include "criterion/criterion.h"
#include "criterion/logging.h"
#include <signal.h>

int t_intCmp(void* a, void* b)
{
    int res = (*(int*)a) - (*(int*)b);
    return res;
}

void t_intDel(void *pVal)
{
    free (pVal);
}

Test(List_test, t_neg__List_create)
{
    List *first, *second;
    cr_log_info ("before List_create");

    first = List_create (NULL, t_intDel);
    second = List_create (t_intCmp, NULL);

    cr_log_info ("after List_create");
    cr_expect_eq(first, NULL, "Expected List_create() to fail on NULL compare");
    cr_expect_eq(second, NULL, "Expected List_create() to fail on NULL free_func");

    List* t_list = List_create(t_intCmp, t_intDel);
    cr_expect_neq(t_list, NULL, "List_create() failed to allocate list");

    List_delete(t_list);
}

Test(List_test, t_pos__List_create)
{
    cr_log_info ("before List_create");
    List* t_list = List_create(t_intCmp, t_intDel);
    cr_log_info ("after List_create");
    cr_assert_neq(t_list,  NULL, "List_create() failed!");
    List_delete(t_list);
}
