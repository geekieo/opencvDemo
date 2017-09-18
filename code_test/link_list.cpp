#include "stdafx.h"
#include "link_list.h"

#include <iostream>
#include <stdio.h>
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
	
	int i = 0;	//存储计数
	int num[20];	//存储数组
	char c;
	while (c = getchar(), c != '\n'){
		if (c >= '0' && c <= '9'){//数字定义域
			ungetc(c, stdin);//把c送回输入缓冲区
			cin >> num[i++];//在缓冲区使用cin读取这个数
		}
			
	}
	for (int j = 0; j<i; j++)
	{
		cout << "a[" << j << "]:" << num[j] << endl;
	}

	

}

void print(pNode list){

}