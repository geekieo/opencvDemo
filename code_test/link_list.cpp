#include "stdafx.h"
#include "link_list.h"

#include <iostream>
#include <stdlib.h>
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
	int inData;
	cin >> inData;
	while (inData!= 0){
		iCount += 1;
	}

	pHead = pNew;
}

void print(pNode list){

}