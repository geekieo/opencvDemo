// code_test.cpp : 定义控制台应用程序的入口点。
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

	printf("*p1++ = %d, p1 =%d\n", *p++, p);//结果为3 （++优先级比*高）先p++后p指针此时指向p1[1]=3出，再*P取值操作即把3取出
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
}

// "try" test class
class A{
public:
	A(): a(0){
		std::cout << "A 默认构造函数" << std::endl;
	}
	A(const A& rsh){
		std::cout << "A 复制构造函数" << std::endl;
	}
	~A(){
		std::cout << "A 析构函数" << std::endl;
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

