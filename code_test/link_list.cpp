#include "stdafx.h"
#include "link_list.h"

#include <iostream>
#include <stdlib.h>
using namespace std;

int iCount; //节点个数

/*
创建链表
pHead 表头
*/
void createList(pNode pHead){
	pNode pEnd, pNew;	//pEnd指向原节点，pNew指向新节点
	iCount = 0;	//初始化链表长度，即节点数=0
	pEnd = pNew = new(Node);
	int inData;
	cin >> inData;
	while (inData!= 0){
		iCount += 1;
	}

	pHead = pNew;
}

void print(pNode list){

}