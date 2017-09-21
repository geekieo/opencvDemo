#include "stdafx.h"
#include "link_list.h"

#include <iostream>
#include <stdio.h>
using namespace std;

/*
����/�ӳ�����
�� pHead Ϊβ�ڵ㣬���ݼ������֣��½�/�ӳ����� 
���������ڵ����
������½�����pHead->data Ϊ��
*/
int createList(pNode pHead){
	pNode pEnd, pNew;	//pEndָ��ͷ�ڵ㣬pNewָ���½ڵ�
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
	return iCount;
}

/*
��ӡ����
*/
void print(pNode pHead){
	pNode node = pHead;
	//������ӡ�ڵ�����
	while (node != NULL){
		cout << node->value << endl;
		node = node->next;
	}
}

/*
����˳������˳��ϲ������ظ�Ԫ��
���غϲ��������ͷ�ڵ�
*/
pNode merge(pNode p, pNode q){
	pNode mHead, mNode;
	mHead = mNode = new Node();
	mHead->next = mNode;
	while (p != NULL && q != NULL){
		if (p->value <= q->value){
			mNode = p;
			p = mNode = mNode -> next;
		}
		else{
			mNode = q;
			q = mNode = mNode->next;
		}
	}
	// ����δ�ȽϵĽڵ�
	if (p != NULL){
		mNode->next = p;
	}
	else{
		mNode->next = q;
	}
	return mHead;
}

/*
˳���ȥ��
Given 1->2->2->3, return 1->2->3
*/
void deleteDuplicates(pNode pHead){

}