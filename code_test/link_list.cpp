#include "stdafx.h"
#include "link_list.h"

#include <iostream>
#include <stdio.h>
using namespace std;

int iCount; //�ڵ����

/*
����/�ӳ�����
�� pHead Ϊβ�ڵ㣬���ݼ������֣��½�/�ӳ����� 
���������ڵ����
������½�����pHead->data Ϊ��
*/
int createList(pNode pHead){
	pNode pEnd, pNew;	//pEndָ��ԭ�ڵ㣬pNewָ���½ڵ�
	iCount = 0;	//��ʼ�������ȣ����ڵ���=0
	pEnd = pHead;

	int i = 0;	//�洢����
	int data;	//�洢����
	char c;
	while (c = getchar(), c != '\n'){
		if (c >= '0' && c <= '9'){//���ֶ�����
			pNew = new(Node);
			ungetc(c, stdin);//��c�ͻ����뻺����
			cin >> pNew->value;//�ڻ�����ʹ��cin��ȡ�����
			pEnd->next = pNew;//��������β��
			pEnd = pNew;//pEnd ָ�� pNew
			i++;
		}
	}
	return i;
}

/*
��ӡ����
*/
void print(pNode pHead){
	pNode node = pHead;
	//������ӡ�ڵ�����
	while (node->next != NULL){
		node = node->next;
		cout << node->value << endl;
	}
}

/*
����˳������ϲ��������ظ�Ԫ��
���磺���� p��1->1->2->3 �� q:1->2->2->3 �����Ϊ 1->2->3
���غϲ��������ͷ�ڵ�
*/
pNode merge(pNode p, pNode q){
	pNode mergedListHead;

	return mergedListHead;
}

/*
hash ����
hash��ʽ��key = value
�־û��ڵ����ݣ������ظ����� false
*/
bool uniqueHash(int value){
	
}