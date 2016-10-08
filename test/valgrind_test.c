#include "LIST/list.h"
#include "stdlib.h"

typedef struct dummy
{
    int a;
    char b;
    float c;
} dummy;
int dummycmp(void *a, void *b)
{
    return 0;
}

int main(int argc, char** argv)
{
    dummy *dumb;
    List* mylist = List_create(dummycmp);

    for(size_t i = 0; i < 8; i++)
    {
        dumb = malloc(sizeof(dummy));
        dumb->a = i;
        dumb->b = i+65;
        dumb->c =((float)i) + 0.1;
        List_add(mylist, dumb);

        free(List_at(mylist , i));
    }

    List_delete(mylist);
    return 0;
}
