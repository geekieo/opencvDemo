#include "stdafx.h"
#include "link_list.h"

#include <iostream>
#include <stdio.h>
using namespace std;

/*
name:����/�ӳ�����
param: pHead �����ڵ��ͷ���
return:�����ڵ����
method:
�� pHead Ϊβ�ڵ㣬���ݼ������֣��½�/�ӳ�����
�ӳ�������pHead ����һλ��Ϊ�����ڵ��ͷ�ڵ�
*/
int createList(pNode pHead){
	pNode pEnd, pNew;	//pEndָ��β�ڵ㣬pNewָ���½ڵ�
	pEnd = pHead;
	int iCount = 0;	//�洢����
	char c;
	while (c = getchar(), c != '\n'){
		if (c >= '0' && c <= '9'){//���ֶ�����
			pNew = new Node();
			ungetc(c, stdin);//��c�ͻ����뻺����
			cin >> pNew->value;//�ڻ�����ʹ��cin��ȡ�����
			pEnd->next = pNew;//��������β��
			pEnd = pNew;//pEnd ָ�� pNew
			iCount++;
		}
	}
	//pHead ָ���ַ���ܱ䣬����һλ����ֵ��ʹ��Ϊ��ֵͷ�ڵ�
	pHead->value = pHead->next->value;
	pHead->next = pHead->next->next;
	return iCount;
}

/*
��ӡ����
*/
void print(pNode pHead){
	pNode node = pHead;
	//������ӡ�ڵ�����
	while (node != NULL){
		cout << node->value<<" ";
		node = node->next;
	}
	cout << endl;
}

/*
����˳������˳��ϲ������ظ�Ԫ��
���غϲ��������ͷ�ڵ�
*/
pNode merge(pNode p, pNode q){
	pNode mHead, mNode;
	mHead = mNode = new Node();
	while (p != NULL && q != NULL){
		if (p->value <= q->value){
			mNode ->next = p;
			mNode = mNode->next;
			p = p->next;
		}
		else{
			mNode->next = q;
			q = mNode = mNode->next;
			q = q->next; 
		}
	}
	// ����δ�ȽϵĽڵ�
	if (p != NULL){
		mNode->next = p;
	}
	else{
		mNode->next = q;
	}
	//mHead �ڵ����һλ��ʹ��Ϊ��ֵͷ�ڵ�
	mHead->value = mHead->next->value;
	mHead->next =  mHead->next->next;
	return mHead;
}

/*
˳���ȥ��
Given 1->2->2->3, return 1->2->3
*/
pNode deleteDuplicates(pNode pHead){
	pNode sHead = pHead;
	pNode sNode = pHead;
	while(pHead->next != NULL){
		pHead = pHead->next;
		while (pHead->value == sNode->value)
			pHead = pHead->next;
		sNode->next = new Node();//���ı�����ڴ棬�������ڴ棬�濽��
		sNode = sNode->next;
		sNode->value =	pHead ->value;
	}
	return sHead;
}