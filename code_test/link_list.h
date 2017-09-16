#include "stdafx.h"


typedef struct _node{
	int data; //类型暂定为 int
	_node* next;	//指向 Node 结构体对象的指针
} Node,* pNode;
 
void createList(pNode pHead);