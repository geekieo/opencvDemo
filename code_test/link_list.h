#include "stdafx.h"


typedef struct _node{
	int value;		//�����������ݶ�Ϊ int
	_node* next;	//����ָ�� Node �ṹ��ʵ����ָ��
} Node,* pNode;

typedef struct _linearHash{
	int key;
	bool hasValue = false;
} linearHash;

int createList(pNode pHead);
void print(pNode pHead);