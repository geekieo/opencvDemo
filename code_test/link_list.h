#include "stdafx.h"


typedef struct _node{
	int data;		//�����������ݶ�Ϊ int
	_node* next;	//����ָ�� Node �ṹ��ʵ����ָ��
} Node,* pNode;
 
int createList(pNode pHead);
void print(pNode pHead);