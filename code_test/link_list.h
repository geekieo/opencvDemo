#include "stdafx.h"


typedef struct _node{
	int data;		//数据域，类型暂定为 int
	_node* next;	//链域，指向 Node 结构体实例的指针
} Node,* pNode;
 
int createList(pNode pHead);
void print(pNode pHead);