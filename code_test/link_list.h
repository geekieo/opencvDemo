#include "stdafx.h"

typedef struct _node{
	int data; //类型暂定为 int
	_node *next;	//指向本结构体类型的指针
} Node,*pNode  ;

int add(int a, int b);