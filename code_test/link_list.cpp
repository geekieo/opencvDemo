#include "stdafx.h"
#include "link_list.h"

#include <iostream>
#include <stdio.h>
using namespace std;

int iCount; //节点个数

/*
创建/延长链表
以 pHead 为尾节点，根据键入数字，新建/延长链表 
返回新增节点个数
如果是新建链表，pHead->data 为空
*/
int createList(pNode pHead){
	pNode pEnd, pNew;	//pEnd指向原节点，pNew指向新节点
	iCount = 0;	//初始化链表长度，即节点数=0
	pEnd = pHead;

	int i = 0;	//存储计数
	int data;	//存储数组
	char c;
	while (c = getchar(), c != '\n'){
		if (c >= '0' && c <= '9'){//数字定义域
			pNew = new(Node);
			ungetc(c, stdin);//把c送回输入缓冲区
			cin >> pNew->data;//在缓冲区使用cin读取这个数
			pEnd->next = pNew;//接入链表尾部
			pEnd = pNew;//pEnd 指向 pNew
			i++;
		}
	}
	return i;

}

void print(pNode pHead){
	pNode node = pHead;
	//迭代打印
	while (node->next != NULL){
		node = node->next;
		cout << node->data << endl;
	}
}