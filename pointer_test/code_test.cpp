// code_test.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"

#include <iostream>		//sortTest
#include <algorithm>	//sortTest
#include <vector>		//sortTest

bool myfunction(int i, int j) { return (i<j); }

struct SortTestClass {
	bool operator() (int i, int j) { return (i<j); }
} myobject;

int sortTest() {
	int myints[] = { 32, 71, 12, 45, 26, 80, 53, 33 };
	std::vector<int> myvector(myints, myints + 8);               // 32 71 12 45 26 80 53 33
	std::vector<int>::iterator it;

	// using default comparison (operator <):
	sort(myvector.begin(), myvector.begin() + 4);           //(12 32 45 71)26 80 53 33

	// using function as comp
	sort(myvector.begin() + 4, myvector.end(), myfunction); // 12 32 45 71(26 33 53 80)

	// using object as comp
	sort(myvector.begin(), myvector.end(), myobject);     //(12 26 32 33 45 53 71 80)

	// print out content:
	std::cout << "myvector contains:";
	for (it = myvector.begin(); it != myvector.end(); ++it)
		std::cout << " " << *it;

	std::cout << std::endl;

	return 0;
}

void pointTest(){
	int p1[] = { 1, 3, 5, 7, 9 };
	int *p = p1;
	printf("*p = %d\n\n", *p);
	printf("p = p1 = %d\n", p);

	printf("*p1++ = %d, p1 =%d\n", *p++, p);//���Ϊ3 ��++���ȼ���*�ߣ���p++��pָ���ʱָ��p1[1]=3������*Pȡֵ��������3ȡ��
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
}

// "try" test class
class A{
public:
	A(): a(0){
		std::cout << "A Ĭ�Ϲ��캯��" << std::endl;
	}
	A(const A& rsh){
		std::cout << "A ���ƹ��캯��" << std::endl;
	}
	~A(){
		std::cout << "A ��������" << std::endl;
	}
private:
	int a;
};

int tryTest(){
	try{
		A a;
		throw a;
	}
	catch (A a){
		;
	}
	return 0;
}


int _tmain(int argc, _TCHAR* argv[])
{
	tryTest();
}

