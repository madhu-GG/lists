#include "LIST/List.h"
#include <stdlib.h>
#include <stdio.h>
#define NUM_ELEMS 10

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

void freefunc(void *a)
{
    free (a);
}

int main(int argc, char** argv)
{
    dummy *dumb;
    List* mylist = List_create(dummycmp, freefunc);

    for(size_t i = 0; i < NUM_ELEMS; i++)
    {
        dumb = malloc(sizeof(dummy));
        dumb->a = i;
        dumb->b = i+65;
        dumb->c =((float)i) + 0.1;
        List_add(mylist, dumb);
    }

    dumb = NULL;

    for (size_t i = 0; i < NUM_ELEMS; i++)
    {
	dumb = List_at (mylist, i);

	if (dumb != NULL)
	{
	    printf ("a: %d b: %c c: %f\n", dumb->a, dumb->b, dumb->c);
	}
    }

    List_delete(mylist);
    return 0;
}
