
#pragma once

typedef struct Node {
    DataType data;
    struct Node * prior;
    struct Node * next;
} DListNode, * DLinkList;

/// 双向循环链表

/**
 * 初始化
 */
int InitDList(DLinkList * head)
{
    *head = (DListNode*)malloc(sizeof(DListNode));
    if (*head == NULL) {
        return -1;
    }
    
    // 使前驱指针和后继指针都指向自己
    (*head)->next = *head;
    (*head)->prior = *head;
    
    return 1;
}
/**
 * 插入操作
 */
int InsertDList(DLinkList head, int i, DataType e)
{
	DListNode * p, * s;
	int j;
	
	// 定位第一个有效节点
	p = head->next;
	j = 1;
	
	while (p != NULL && j < i) {
		p = p->next;
		j++;
	}
	if (p == head || j > i)
		return -1;
	
	s = (DListNode*)malloc(sizeof(DListNode));
	if (! s) {
		return -1;
	}
	
	s->data = e;
	s->prior = p->prior;
	s->next = p;
	p->prior->next = s;
	p->prior = s;
	
	return 1;
}
/**
 * 删除节点
 */
