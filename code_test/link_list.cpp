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
			cin >> pNew->data;//�ڻ�����ʹ��cin��ȡ�����
			pEnd->next = pNew;//��������β��
			pEnd = pNew;//pEnd ָ�� pNew
			i++;
		}
	}
	return i;

}

void print(pNode pHead){
	pNode node = pHead;
	//������ӡ
	while (node->next != NULL){
		node = node->next;
		cout << node->data << endl;
	}
}