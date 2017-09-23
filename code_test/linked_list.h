#include "stdafx.h"


typedef struct _node{
	int value;		//数据域，类型暂定为 int
	_node* next;	//链域，指向 Node 结构体实例的指针
} Node,* pNode;


int createList(pNode pHead);
void print(pNode pHead);
pNode merge(pNode p, pNode q);//顺序表合并
pNode deleteDuplicates(pNode pHead);//顺序表去重