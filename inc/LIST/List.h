#ifndef LIST_H
#define LIST_H

#include <stddef.h>
#include <stdbool.h>

/* forward declaration of struct List and List typedef
 * 
 * List should provide List->cmp function type in it's implementation.
 */
typedef struct List List;

/* comparator function type for List->cmp.
 * the comparator return value is similar to the C string library
 * function 'strcmp()' from string.h (cstring).
 */
typedef int (*List_cmpFunc)(void*, void*);

/* function to free the allocated memory for value objects stored
 * in the list.
 */
typedef void (*List_freeFunc)(void*);

/* List API functions are below.
 */

/*
 * List creation function.
 */
List *List_create(List_cmpFunc, List_freeFunc);

/*
 * free the memory allocated to the given list. do nothing if NULL.
 */
void List_delete(List*);

/*
 * add the given value to the given list.
 * return: TRUE if value is added
 *         FALSE if value, list is NULL or some other error.
 */
bool List_add(List*, void*);

/*
 * remove the element at given position of list.
 * return: removed element or,
 *         NULL if List is NULL, position is out of bounds.
 */
void* List_removeFrom(List*,size_t,bool);

/*
 * remove the first occurance of the given value.
 * return: TRUE if the given value was removed.
 *         FALSE if List,value is NULL or value does not exist.
 */
bool List_remove(List*, void*,bool);

/*
 * remove all occurances of the given value.
 * return: number of elements removed.
 */
size_t List_removeAll(List*, void*,bool);

/*
 * remove all the elements of the given list. do nothing if NULL.
 */
void List_clear(List*,bool);

/*
 * check if the given list contains the given value.
 * return: TRUE if the list contains the given value.
 *         FALSE if the value is not found.
 */
bool List_contains(List*, void*);

/*
 * return the value at the given position in the list.
 * NULL if the position is out of bounds or List is NULL.
 */
void* List_at(List*, size_t);

/*
 * return the number of elements in the list.
 */
size_t List_size(List*);

#endif /* LIST_H */
