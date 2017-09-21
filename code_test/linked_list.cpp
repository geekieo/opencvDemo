#include "stdafx.h"
#include "link_list.h"

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
	//pHead 指针地址不能变，后移一位（赋值）使其为有值头节点
	pHead->value = pHead->next->value;
	pHead->next = pHead->next->next;
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
	pNode mHead, mNode;
	mHead = mNode = new Node();
	while (p != NULL && q != NULL){
		if (p->value <= q->value){
			mNode ->next = p;
			mNode = mNode->next;
			p = p->next;
		}
		else{
			mNode->next = q;
			q = mNode = mNode->next;
			q = q->next; 
		}
	}
	// 续上未比较的节点
	if (p != NULL){
		mNode->next = p;
	}
	else{
		mNode->next = q;
	}
	//mHead 节点后移一位，使其为有值头节点
	mHead->value = mHead->next->value;
	mHead->next =  mHead->next->next;
	return mHead;
}

/*
顺序表去重
Given 1->2->2->3, return 1->2->3
*/
pNode deleteDuplicates(pNode pHead){
	pNode sHead = pHead;
	pNode sNode = pHead;
	while(pHead->next != NULL){
		pHead = pHead->next;
		while (pHead->value == sNode->value)
			pHead = pHead->next;
		sNode->next = new Node();//不改变入参内存，开辟新内存，真拷贝
		sNode = sNode->next;
		sNode->value =	pHead ->value;
	}
	return sHead;
}