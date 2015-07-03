/*
 * INTEL CONFIDENTIAL
 * Copyright (c) 2002, 2003 Intel Corporation.  All rights reserved.
 */
#ifndef __ILIBLINKED_LIST_H
#define __ILIBLINKED_LIST_H


/* Stack Methods */
void ILibCreateStack(void **TheStack);
void ILibPushStack(void **TheStack, void *data);
void *ILibPopStack(void **TheStack);
void *ILibPeekStack(void **TheStack);
void ILibClearStack(void **TheStack);

/* Queue Methods */
void *ILibQueue_Create(void);
void ILibQueue_Destroy(void *q);
int ILibQueue_IsEmpty(void *q);
void ILibQueue_EnQueue(void *q, void *data);
void *ILibQueue_DeQueue(void *q);
void *ILibQueue_PeekQueue(void *q);
void ILibQueue_Lock(void *q);
void ILibQueue_UnLock(void *q);

/* Bothway linked list */
void* XLinkedList_Create();
void* XLinkedList_ShallowCopy(void *LinkedList);
void* XLinkedList_GetNode_Head(void *LinkedList);
void* XLinkedList_GetNode_Tail(void *LinkedList);
void* XLinkedList_GetNextNode(void *LinkedList_Node);
void* XLinkedList_GetPreviousNode(void *LinkedList_Node);
void* XLinkedList_GetDataFromNode(void *LinkedList_Node);
void XLinkedList_InsertBefore(void *LinkedList_Node, void *data);
void XLinkedList_InsertAfter(void *LinkedList_Node, void *data);
void XLinkedList_Remove(void *LinkedList_Node);
void XLinkedList_Remove_ByData(void *LinkedList, void *data);
void XLinkedList_AddHead(void *LinkedList, void *data);
void XLinkedList_AddTail(void *LinkedList, void *data);
void XLinkedList_Lock(void *LinkedList);
void XLinkedList_UnLock(void *LinkedList);
void XLinkedList_Destroy(void *LinkedList);
long XLinkedList_GetCount(void *LinkedList);

#endif
