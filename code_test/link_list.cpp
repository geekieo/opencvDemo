#include "stdafx.h"
#include "link_list.h"

#include <iostream>
#include <stdio.h>
using namespace std;

/*
创建/延长链表
以 pHead 为尾节点，根据键入数字，新建/延长链表 
返回新增节点个数
如果是新建链表，pHead->data 为空
*/
int createList(pNode pHead){
	pNode pEnd, pNew;	//pEnd指向头节点，pNew指向新节点
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
	return iCount;
}

/*
打印链表
*/
void print(pNode pHead){
	pNode node = pHead;
	//迭代打印节点数据
	while (node != NULL){
		cout << node->value << endl;
		node = node->next;
	}
}

/*
两个顺序链表顺序合并，含重复元素
返回合并后的链表头节点
*/
pNode merge(pNode p, pNode q){
	pNode mHead, mNode;
	mHead = mNode = new Node();
	mHead->next = mNode;
	while (p != NULL && q != NULL){
		if (p->value <= q->value){
			mNode = p;
			p = mNode = mNode -> next;
		}
		else{
			mNode = q;
			q = mNode = mNode->next;
		}
	}
	// 续上未比较的节点
	if (p != NULL){
		mNode->next = p;
	}
	else{
		mNode->next = q;
	}
	return mHead;
}

/*
顺序表去重
Given 1->2->2->3, return 1->2->3
*/
void deleteDuplicates(pNode pHead){

}