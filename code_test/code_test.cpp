// code_test.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

#include <iostream>		//sortTest
#include <algorithm>	//sortTest
#include <vector>		//sortTest

using namespace std;

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

// class for "tryTest"
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
	void f(){
		std::cout << "This is A's f() function" << std::endl;
	}
	virtual void virtual_f(){
		std::cout << "This is A's virtual_f() function" << std::endl;
	}
private:
	int a;
};

class B :public A{
public:
	B(){
		virtual_f();
	}
	~B();

	virtual void virtual_f(){
		std::cout << "This is B's virtual_f() function" << std::endl;
	}
private:

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

//class for "iteratorTest"
class _iterator{
private:
	char *p;
public:
	_iterator(char *str) :p(str){} //初始化私有变量 p 赋值
	char *&operator++(){
		p += 1;
		return p;
	}
};

int iteratorTest(){
	char *p = "This is C++ program";
	_iterator it(p);//it 为 p 的迭代器
	std::cout << "++之前：" << p << std::endl;// ++之前：This is C++ program
	char *p1 = ++it;//把地址向后加一个 char 型长度，此处为++it，不是++p
	std::cout << "++之后：" << p1 << std::endl;//"++之后：his is C++ program
	return 0;
}

//int* wrong_f(std::vector<int> v) {
//	int a[10000000];		// a[] 所有元素保存在栈内存上，a是个符号地址，没有存储空间
//	for (int i = 0; i < v.size(); ++i) { //warning C4018: “<”: 有符号/无符号不匹配
//		a[i] = v[i];
//	}
//	return a;	//warning C4172: 返回局部变量或临时变量的地址
//				//即警告返回了指向栈内存的指针，返回后栈内存都会被自动回收
//				//修改方法：将 int a[10000000]转为 static，存入常量区
//}

int* wrong_f(std::vector<int> v) {
	static int a[10000000];		//修改内容：添加 static
	for (size_t i = 0; i < v.size(); ++i) { //修改内容：int -> size_t
		a[i] = v[i];
	}
	return a;	
}

int pClassTest(){
	// Test1
	A *p = NULL;
	p->f(); //编译成功，直接调用A类内函数f(),因为f并不涉及类内变量，故未实例化也没报错
	//A *p2=NULL; p2->virtual_f();//编译出错，指向不明

	// Test2
	std::cout << sizeof(int) << std::endl; // int 为4个字节
	int *pa = new int[10];
	std::cout << pa << "; " << pa + 1 << std::endl; // +1 指针右移4个位置，一个位置1字节
	//delete (pa+1); //指针不存在，编译出错

	// Test3
	A ca; //会调用默认构造函数,return会调析构函数
	//B b; //编译出错，B构造函数中的 virtual_f() 指代不明
	
	//int shuzu[7] = { 1, 2, 3, 4, 5, 6, 7 };
	//std::vector<int> v(shuzu, shuzu + 7);
	std::vector<int> v = { 1, 2, 3, 4, 5, 6, 7 }; //C++11标准
	int* arr_wf = wrong_f(v);
	cout << arr_wf[0] << endl;

	return 0;
}

void inputToArrayTest(){
	//输入一行以空格为分隔的数字，存入数组，回车为结束符 
	int i = 0;	//存储计数
	int num[20];	//存储数组
	char c;
	while (c = getchar(), c != '\n'){
		if (c >= '0' && c <= '9'){//数字定义域
			ungetc(c, stdin);//把c送回输入缓冲区
			cin >> num[i++];//在缓冲区使用cin读取这个数
		}
	}
	for (int j = 0; j<i; j++)
	{
		cout << "a[" << j << "]:" << num[j] << endl;
	}
}

#include "linked_list.h"
int _tmain(int argc, _TCHAR* argv[])
{
	pNode list1 = new Node();
	pNode list2 = new Node();
	createList(list1);
	print(list1);
	createList(list2);
	print(list2);
	pNode mList = merge(list1, list2);
	print(mList);
	print(list1);
	print(list2);
	pNode mListSet = deleteDuplicates(mList);
	print(mListSet);
	print(mList);

}

  