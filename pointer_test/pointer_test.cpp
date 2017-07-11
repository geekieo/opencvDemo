// pointer_test.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"


int _tmain(int argc, _TCHAR* argv[])
{
	int p1[] = { 1, 3, 5, 7, 9 };
	int *p = p1;
	printf("*p = %d\n\n", *p);
	printf("p = p1 = %d\n", p);

	printf("*p1++ = %d, p1 =%d\n", *p++,p);//结果为3 （++优先级比*高）先p++后p指针此时指向p1[1]=3出，再*P取值操作即把3取出
	printf("p1 = %d\n\n", p);

	p = p1;
	printf("p1 = %d\n", p);
	*++p;
	printf("*p1++ = %d\n", *p);//结果为3 （++优先级比*高）先p++后p指针此时指向p1[1]=3出，再*P取值操作即把3取出
	printf("p1 = %d\n\n", p);

	int p2[] = { 1, 3, 5, 7, 9 };
	p = p2;
	printf("p2 = %d\n", p);
	(*p)++;
	printf("(*p2)++ = %d\n", *p);//结果为2 先取值操作此时*p=1 然后再++操作即执行1+1=2 即为最后结果
	printf("p2 = %d\n", p);

	return 0;
}

