#include "stdafx.h"


typedef struct _node{
	int data;		//�����������ݶ�Ϊ int
	_node* next;	//����ָ�� Node �ṹ��ʵ����ָ��
} Node,* pNode;
 
void createList(pNode pHead);