 #include "stdafx.h"
#include "linked_list.h"

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
	//pHead ָ���ַ���ܱ䣬����һλ����ָ��,��ֵ��ֵ������ʹ��Ϊ��ֵͷ�ڵ�
	*pHead = *pHead->next;// ->���ȼ�����*
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
	pNode mHead, mEnd;//�ϲ��������ͷ�ڵ��β�ڵ�
	mHead = mEnd = new Node();
	while (p != NULL && q != NULL){
		pNode pTemp = new Node();
		mEnd->next = pTemp;
		if (p->value <= q->value){
			*pTemp = *p;//��ָ�룬ֵ����
			p = p->next;
		}
		else{
			*pTemp = *q;
			q = q->next; 
		}
		mEnd = mEnd->next;
	}
	// ���δ�ȽϵĽڵ�
	if (p != NULL){
		while (p != NULL){
			pNode pTemp = new Node();
			mEnd->next = pTemp;
			*pTemp = *p;
			p = p->next;
			mEnd = mEnd->next;
		}
	}
	else{
		while (q != NULL){
			pNode pTemp = new Node();
			mEnd->next = pTemp;
			*pTemp = *q;
			q = q->next;
			mEnd = mEnd->next;
		}
	}
	//mHead �ڵ����һλ��ʹ��Ϊ��ֵͷ�ڵ�
	*mHead = *(mHead->next);
	return mHead;
}

/*
˳���ȥ��
Given 1->2->2->3, return 1->2->3
*/
pNode deleteDuplicates(pNode pHead){
	pNode sHead, sEnd;//����ȥ�غ������ͷ�ڵ��β�ڵ�
	sHead = sEnd = new Node();
	while(pHead != NULL){
		while (pHead->value == sEnd->value)
			pHead = pHead->next;//�����ظ��ڵ㣬�������Ӳ��ظ��ڵ�
		sEnd->next = new Node();//���ı�����ڴ棬�������ڴ棬�濽��
		sEnd = sEnd->next;
		*sEnd = *pHead;
		pHead = pHead->next;//������pHeadΪ�������仯���ı��ⲿpHead
	}
	*sHead = *sHead->next;
	return sHead;
}