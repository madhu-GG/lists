#include "LIST/List.h"
#include <stdlib.h>
#include <stdio.h>

#define LIST_SIZE_DEFAULT 8

bool List_upsize(List*);
void List_downsize(List*);

struct List
{
    void **arr;
    size_t num_vals;
    size_t size;
    List_cmpFunc cmp;
    List_freeFunc free_func;
};

size_t List_size(List* list)
{
    return (list == NULL)? 0 :  list->num_vals;
}

List *List_create(List_cmpFunc cmp_func, List_freeFunc free_func)
{
    size_t size;

    if(NULL == cmp_func || NULL == free_func)
        return NULL;

    size = LIST_SIZE_DEFAULT;

    List *list = malloc(sizeof(List));
    if(!list)
        return NULL;
    
    list->num_vals = 0;
    list->cmp = cmp_func;
    list->free_func = free_func;
    list->arr = malloc(size * sizeof(void*));
    if(list->arr)
    {
        list->size = size;
    }
    else
    {
        List_delete(list);
        return NULL;
    }
    return list;
}

void List_delete(List* list)
{
    size_t iter_ind;
    if(list)
    {
        if(list->arr && list->num_vals != 0)
	{
	    if (list->free_func != NULL)
	    {
	        for (iter_ind=0; iter_ind < list->size; iter_ind++)
	        {
		    list->free_func (list->arr[iter_ind]);
	        }
	    }
            free(list->arr);
	}
        free(list);
    }
}

bool List_add(List* list, void* val)
{
    if(!list)
        return false;

    if(!val)
        return false;

    /* no space in list, increase the storage capacity of the list */
    if(list->num_vals == list->size)
    {
        if(!List_upsize(list))
            return false;
    }
    
    list->arr[list->num_vals] = val;
    list->num_vals++;
    return true;
}

void* List_removeFrom(List* list, size_t pos, bool keepValuePtr)
{
    void *tmp;      /* holds the element that is removed, to be returned to the caller */
    void **new_arr;

    if(!list)
        return NULL;
    else if(list->num_vals == 0)
        return NULL;
    else if(pos >= list->num_vals)
        return NULL;

    /* move the last element of the list to the position of the element
     * that is removed.
     */
    tmp = list->arr[pos];
    
    if(list->num_vals > 1)
    {
        list->arr[pos] = list->arr[list->num_vals - 1];
    }

    list->arr[list->num_vals - 1] = tmp;

    if (keepValuePtr == false && list->free_func != NULL)
    {
	list->free_func (list->arr[list->num_vals - 1]);
    }

    list->arr[list->num_vals - 1] = NULL;
    list->num_vals--;

    /* release excessive free space after deletion */
    List_downsize(list);

    return tmp;
}

bool List_remove(List* list, void* val, bool keepValuePtr)
{
    void *pVal;
    size_t pos;
    
    if(!list)
        return false;
    else if(!val)
        return false;
    else if(list->num_vals == 0)
        return false;
    else if(!list->cmp)
        return false;

    /* find the first occurance of the element to be removed */
    for(size_t pos = 0; pos < list->num_vals; pos++)
    {
        /* found the element */
        if(0 == list->cmp(list->arr[pos], val))
            break;
    }

    /* not found */
    if(pos == list->num_vals)
        return false;

    /* swap the element to be removed with the last element */
    if(list->num_vals > 1)
    {
	pVal = list->arr[pos];
        list->arr[pos] = list->arr[list->num_vals - 1];
	list->arr[list->num_vals - 1] = pVal;
    }

    if (keepValuePtr == false && list->free_func != NULL)
    {
	list->free_func (list->arr[list->num_vals - 1]);
    }

    list->arr[list->num_vals - 1] = NULL;
    list->num_vals--;

    /* release excessive free space after deletion */
    List_downsize(list);
    return true;
}

size_t List_removeAll(List* list, void* val, bool keepValuePtr)
{
    void *tmp;
    size_t removed = 0;

    if(!list)
        return 0;
    else if(!val)
        return 0;
    else if(0 == list->num_vals)
        return 0;

    for(size_t pos = 0; pos < list->num_vals;)
    {
        if(0 == list->cmp(list->arr[pos], val))
        {
	    tmp = list->arr[pos];
            list->arr[pos] = list->arr[list->num_vals - 1];
	    list->arr[list->num_vals - 1] = tmp;

	    if (keepValuePtr == false && list->free_func != NULL)
	    {
		list->free_func (list->arr[list->num_vals - 1]);
	    }
            list->num_vals--;
            removed++;
        }
        else
            pos++;
    }

    return removed;
}

void List_clear(List* list, bool keepValuePtr)
{
    if(!list)
        return;
    else if(0 == list->num_vals)
        return;

    for(size_t pos = 0; pos < list->num_vals; pos++)
    {
	if (keepValuePtr == false && list->free_func != NULL)
	{
	    list->free_func (list->arr[pos]);
	}
        list->arr[pos] = NULL;
    }
}

bool List_upsize(List* list)
{
    void **new_arr;
    if(!list)
        return false;
    else if(list->size == 0)
        list->size = LIST_SIZE_DEFAULT;

    new_arr = (void**)realloc(list->arr, sizeof(void*) * list->size * 2);
    if(new_arr)
    {
        list->arr = new_arr;
        list->size *= 2;
        return true;
    }
    
    return false;
}

void List_downsize(List* list)
{
    void **new_arr;
    
    /* only downsize list if size is above the minimum threshold, to avoid frequent resizing
     * due to element additions.
     */
    if(list->size >= LIST_SIZE_DEFAULT * 2)
    {
        if(list->num_vals < (list->size / 2))
        {
            new_arr = (void**)realloc(list->arr, sizeof(void*) * (list->size / 2));
            if(new_arr)
            {
                list->arr = new_arr;
                list->size /= 2;
            }
        }
    }
}

void* List_at(List* list, size_t pos)
{
    if(list->num_vals == 0)
    {
        printf("numvals is 0");
        return NULL;
    }
    if(list->num_vals <= pos)
    {
        printf("pos is >= num_vals");
        return NULL;
    }

    return list->arr[pos];
}

int List_intCmp(void *a, void *b)
{
    int ia = *(int*)a;
    int ib = *(int*)b;

    return (ia < ib)? -1 : ((ia == ib)? 0 : 1);
}

