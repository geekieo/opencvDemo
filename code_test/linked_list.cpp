 #include "stdafx.h"
#include "linked_list.h"

#include <iostream>
#include <stdio.h>
using namespace std;

/*
name:创建/延长链表
param: pHead 新增节点的头结点
return:新增节点个数
method:
以 pHead 为尾节点，根据键入数字，新建/延长链表
延长结束后，pHead 后移一位，为新增节点的头节点
*/
int createList(pNode pHead){
	pNode pEnd, pNew;	//pEnd指向尾节点，pNew指向新节点
	pEnd = pHead;
	int iCount = 0;	//存储计数
	char c;
	while (c = getchar(), c != '\n'){
		if (c >= '0' && c <= '9'){//数字定义域
			pNew = new Node();
			ungetc(c, stdin);//把c送回输入缓冲区
			cin >> pNew->value;//在缓冲区使用cin读取这个数
			pEnd->next = pNew;//接入链表尾部
			pEnd = pNew;//pEnd 指向 pNew
			iCount++;
		}
	}
	//pHead 指针地址不能变，后移一位（解指针,赋值，值拷贝）使其为有值头节点
	*pHead = *pHead->next;// ->优先级高于*
	return iCount;
}

/*
打印链表
*/
void print(pNode pHead){
	pNode node = pHead;
	//迭代打印节点数据
	while (node != NULL){
		cout << node->value<<" ";
		node = node->next;
	}
	cout << endl;
}

/*
两个顺序链表顺序合并，含重复元素
返回合并后的链表头节点
*/
pNode merge(pNode p, pNode q){
	pNode mHead, mEnd;//合并后的链表头节点和尾节点
	mHead = mEnd = new Node();
	while (p != NULL && q != NULL){
		pNode pTemp = new Node();
		mEnd->next = pTemp;
		if (p->value <= q->value){
			*pTemp = *p;//解指针，值拷贝
			p = p->next;
		}
		else{
			*pTemp = *q;
			q = q->next; 
		}
		mEnd = mEnd->next;
	}
	// 添加未比较的节点
	if (p != NULL){
		while (p != NULL){
			pNode pTemp = new Node();
			mEnd->next = pTemp;
			*pTemp = *p;
			p = p->next;
			mEnd = mEnd->next;
		}
	}
	else{
		while (q != NULL){
			pNode pTemp = new Node();
			mEnd->next = pTemp;
			*pTemp = *q;
			q = q->next;
			mEnd = mEnd->next;
		}
	}
	//mHead 节点后移一位，使其为有值头节点
	*mHead = *(mHead->next);
	return mHead;
}

/*
顺序表去重
Given 1->2->2->3, return 1->2->3
*/
pNode deleteDuplicates(pNode pHead){
	pNode sHead, sEnd;//开辟去重后的链表头节点和尾节点
	sHead = sEnd = new Node();
	while(pHead != NULL){
		while (pHead->value == sEnd->value)
			pHead = pHead->next;//跳过重复节点，仅仅链接不重复节点
		sEnd->next = new Node();//不改变入参内存，开辟新内存，真拷贝
		sEnd = sEnd->next;
		*sEnd = *pHead;
		pHead = pHead->next;//函数内pHead为拷贝，变化不改变外部pHead
	}
	*sHead = *sHead->next;
	return sHead;
}