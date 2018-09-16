#include "LIST/List.h"
#include <stdlib.h>

typedef struct ListNode {
	struct ListNode *pNext;
	void *pData;
} tListNode;

struct List {
	tListNode *pHead;
	size_t len;
	List_cmpFunc cmp;
	List_freeFunc free;
};

/*
 * Allocate memory for a list with no nodes initially
 * */
List *List_create(List_cmpFunc argCmp, List_freeFunc argFree)
{
	List *pList = NULL;
	
	pList = malloc (sizeof (List));
	
	if (pList != NULL)
	{
		pList->pHead = NULL;
		pList->len = 0;
		pList->cmp = argCmp;
		pList->free = argFree;
	}
	
	return pList;
}

/*
 * Delete all entries in the list and then delete the list.
 * */
void List_delete(List* pList)
{
    tListNode *pNode = NULL, *pNextNode = NULL;
    if(pList != NULL && pList->len > 0)
    {
		pNode = pList->pHead;
		while (pNode != NULL)
		{
			pNextNode = pNode->pNext;
			pList->free (pNode->pData);
			free (pNode);
			pNode = NULL;
			pList->len--;
			pNode = pNextNode;
		}
		
        free(pList);
        pList = NULL;
    }
}

/*
 * List_add for linked list adds entry in proper order according to cmp function
 * given by the user.
 * */

bool List_add (List* pList, void* pVal)
{
	if (pList == NULL || pVal == NULL)
	{
		return false;
	}
	
	tListNode *pNode = pList->pHead;
	tListNode *pNewNode = NULL, *pPrevNode;

	pNewNode = malloc (sizeof(tListNode));
	
	if (pNewNode == NULL)
	{
		return false;
	}
	
	pNewNode->pNext = NULL;
	pNewNode->pData = pVal;
	
	if (pNode == NULL)
	{
		pList->pHead = pNewNode;
	}
	else
	{
		/* loop until value to be inserted is in correct place in list */
		while (pNode != NULL && pList->cmp (pNode->pData, pVal) <= 0)
		{
			pPrevNode = pNode;
			pNode = pNode->pNext;
		}
		
		if (pNode == NULL)
		{
			pPrevNode->pNext = pNewNode;
		}
		else
		{
			pNewNode->pNext = pPrevNode->pNext;
			pPrevNode->pNext = pNewNode;
		}
	}
	
	pList->len++;
	return true;
}
