// pointer_test.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"


int _tmain(int argc, _TCHAR* argv[])
{
	int p1[] = { 1, 3, 5, 7, 9 };
	int *p = p1;
	printf("*p = %d\n\n", *p);
	printf("p = p1 = %d\n", p);

	printf("*p1++ = %d, p1 =%d\n", *p++,p);//���Ϊ3 ��++���ȼ���*�ߣ���p++��pָ���ʱָ��p1[1]=3������*Pȡֵ��������3ȡ��
	printf("p1 = %d\n\n", p);

	p = p1;
	printf("p1 = %d\n", p);
	*++p;
	printf("*p1++ = %d\n", *p);//���Ϊ3 ��++���ȼ���*�ߣ���p++��pָ���ʱָ��p1[1]=3������*Pȡֵ��������3ȡ��
	printf("p1 = %d\n\n", p);

	int p2[] = { 1, 3, 5, 7, 9 };
	p = p2;
	printf("p2 = %d\n", p);
	(*p)++;
	printf("(*p2)++ = %d\n", *p);//���Ϊ2 ��ȡֵ������ʱ*p=1 Ȼ����++������ִ��1+1=2 ��Ϊ�����
	printf("p2 = %d\n", p);

	return 0;
}

