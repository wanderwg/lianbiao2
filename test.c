#include <stdio.h>
#include "Slist.h"
#include <assert.h>
#include <stdlib.h>
#include <stddef.h>

void SListInit(SList*s) {
	assert(s);
	s->_pHead = NULL;
}

PNode BuySListNode(SDataType data) {
	PNode pNewNode = (PNode)malloc(sizeof(Node));
	if (pNewNode == NULL) {
		assert(0);
		return NULL;
	}
	pNewNode->_data = data;
	pNewNode->_PNext = NULL;
	return pNewNode;
}

void SListPushBack(SList* s, SDataType data) {
	//找链表最后一个节点
	assert(s);
	PNode pNewNode = BuySListNode(data);
	if (s->_pHead == NULL) {//链表没有节点的情况
		s->_pHead = pNewNode;
	}
	else {
		PNode pCur = s->_pHead;
		while (pCur->_PNext) {
			pCur = pCur->_PNext;
		}
		//让最后一个节点指向新节点
		pCur->_PNext = pNewNode;
	}
}

void SListPopBack(SList* s) {
	assert(s);
	if (s->_pHead == NULL) {//链表中没有节点
		return;
	}
	else if (s->_pHead->_PNext == NULL) {//只有一个节点
		free(s->_pHead);
		s->_pHead = NULL;
	}
	else {                           //多个节点
		PNode pCur = s->_pHead;
		PNode pPre = NULL;
		while (pCur->_PNext) {
			pPre = pCur;
			pCur = pCur->_PNext;
		}
		free(pCur);
		pPre->_PNext = NULL;
	}
}

void SListPushFront(SList* s, SDataType data) {
	assert(s);
	PNode pNewNode = BuySListNode(data);
	if (s->_pHead == NULL) {//链表为空
		s->_pHead = pNewNode;
	}
	else {
		pNewNode->_PNext = s->_pHead;
		s->_pHead = pNewNode;
	}
}

void SListPopFront(SList* s) {
	assert(s);
	if (s->_pHead == NULL) {//链表为空
		return;
	}
	else if (s->_pHead->_PNext == NULL) {//只有一个节点
		free(s->_pHead);
		s->_pHead = NULL;
	}
	else {
		PNode pCur = s->_pHead;
		s->_pHead = pCur->_PNext;
		free(pCur);
	}
}

void SListInsert(PNode pos, SDataType data) {
	if (pos == NULL) {
		return;
	}
	PNode pNewNode = BuySListNode(data);
	pNewNode = pos->_PNext;
	pos->_PNext = pNewNode;
}

void SListErase(SList* s, PNode pos) {
	assert(s);
	if (pos == NULL || s->_pHead == NULL) {
		return;
	}
	if (pos== s->_pHead) {
		s->_pHead = pos->_PNext;
	}
	else {
		PNode pPrePos = s->_pHead;
		while (pPrePos&&pPrePos->_PNext != pos) {
			pPrePos = pPrePos->_PNext;
		}
		pPrePos->_PNext = pos->_PNext;
	}
	free(pos);
}

PNode SListFind(SList* s, SDataType data) {
	assert(s);
	PNode pCur = s->_pHead;
	while (pCur) {
		if (pCur->_data == data) {
			return pCur;
		}
		pCur = pCur->_PNext;
	}
	return NULL;
}

size_t SListSize(SList* s) {
	assert(s);
	size_t count = 0;
	PNode pCur = s->_pHead;
	while (pCur) {
		count++;
		pCur = pCur->_PNext;
	}
	return count;
}

int SListEmpty(SList* s) {
	assert(s);
	if (s->_pHead == NULL) {
		return -1;
	}
	return 0;
}

void SListClear(SList* s) {
	assert(s);
	if (s->_pHead == NULL) {
		return;
	}
	PNode pCur = s->_pHead;
	while (pCur->_PNext) {    //循环清空链表中的节点
		PNode Tmp = pCur->_PNext;
		free(pCur);
		pCur = Tmp;
	}
	if (pCur) {      //清空最后一个节点
		free(pCur);
		pCur = NULL;
	}
}

void SListDestroy(SList* s) {
	assert(s);
	if (s->_pHead == NULL) {
		free(s->_pHead);
		return;
	}
	PNode pCur = s->_pHead;
	while (pCur->_PNext) {    //循环清空链表中的节点
		PNode Tmp = pCur->_PNext;
		free(pCur);
		pCur = Tmp;
	}
	if (pCur) {      //清空最后一个节点
		free(pCur);
	}
}

void SListPrint(SList* s) {
	assert(s);
	PNode pCur = s->_pHead;
	while (pCur) {
		printf("%d--->", pCur->_data);
		pCur = pCur->_PNext;
	}
	printf("\n");
}
void main() {
	SList s;
	SListInit(&s);
	SListPushBack(&s, 1);
	SListPushBack(&s, 2);
	SListPushBack(&s, 3);
	printf("size=%d\n", SListSize(&s));
	SListPrint(&s);
	SListPopFront(&s);
	SListPrint(&s);
	SListClear(&s);
	printf("%d\n",SListEmpty(&s));

	system("pause");
	return;
}