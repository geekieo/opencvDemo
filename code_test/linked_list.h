#include "stdafx.h"


typedef struct _node{
	int value;		//�����������ݶ�Ϊ int
	_node* next;	//����ָ�� Node �ṹ��ʵ����ָ��
} Node,* pNode;


int createList(pNode pHead);
void print(pNode pHead);
pNode merge(pNode p, pNode q);//˳���ϲ�
pNode deleteDuplicates(pNode pHead);//˳���ȥ��