#include "stdafx.h"

typedef struct _node{
	int data; //�����ݶ�Ϊ int
	_node *next;	//ָ�򱾽ṹ�����͵�ָ��
} Node,*pNode  ;

int add(int a, int b);