#include "stdafx.h"
#include "link_list.h"

#include <iostream>
#include <stdio.h>
using namespace std;

int iCount; //�ڵ����

/*
��������
pHead ��ͷ
*/
void createList(pNode pHead){
	pNode pEnd, pNew;	//pEndָ��ԭ�ڵ㣬pNewָ���½ڵ�
	iCount = 0;	//��ʼ�������ȣ����ڵ���=0
	pEnd = pNew = new(Node);
	
	int i = 0;	//�洢����
	int num[20];	//�洢����
	char c;
	while (c = getchar(), c != '\n'){
		if (c >= '0' && c <= '9'){//���ֶ�����
			ungetc(c, stdin);//��c�ͻ����뻺����
			cin >> num[i++];//�ڻ�����ʹ��cin��ȡ�����
		}
			
	}
	for (int j = 0; j<i; j++)
	{
		cout << "a[" << j << "]:" << num[j] << endl;
	}

	

}

void print(pNode list){

}