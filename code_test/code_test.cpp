// code_test.cpp : �������̨Ӧ�ó������ڵ㡣
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

// class for "tryTest"
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
	_iterator(char *str) :p(str){} //��ʼ��˽�б��� p ��ֵ
	char *&operator++(){
		p += 1;
		return p;
	}
};

int iteratorTest(){
	char *p = "This is C++ program";
	_iterator it(p);//it Ϊ p �ĵ�����
	std::cout << "++֮ǰ��" << p << std::endl;// ++֮ǰ��This is C++ program
	char *p1 = ++it;//�ѵ�ַ����һ�� char �ͳ��ȣ��˴�Ϊ++it������++p
	std::cout << "++֮��" << p1 << std::endl;//"++֮��his is C++ program
	return 0;
}

//int* wrong_f(std::vector<int> v) {
//	int a[10000000];		// a[] ����Ԫ�ر�����ջ�ڴ��ϣ�a�Ǹ����ŵ�ַ��û�д洢�ռ�
//	for (int i = 0; i < v.size(); ++i) { //warning C4018: ��<��: �з���/�޷��Ų�ƥ��
//		a[i] = v[i];
//	}
//	return a;	//warning C4172: ���ؾֲ���������ʱ�����ĵ�ַ
//				//�����淵����ָ��ջ�ڴ��ָ�룬���غ�ջ�ڴ涼�ᱻ�Զ�����
//				//�޸ķ������� int a[10000000]תΪ static�����볣����
//}

int* wrong_f(std::vector<int> v) {
	static int a[10000000];		//�޸����ݣ���� static
	for (size_t i = 0; i < v.size(); ++i) { //�޸����ݣ�int -> size_t
		a[i] = v[i];
	}
	return a;	
}

int pClassTest(){
	// Test1
	A *p = NULL;
	p->f(); //����ɹ���ֱ�ӵ���A���ں���f(),��Ϊf�����漰���ڱ�������δʵ����Ҳû����
	//A *p2=NULL; p2->virtual_f();//�������ָ����

	// Test2
	std::cout << sizeof(int) << std::endl; // int Ϊ4���ֽ�
	int *pa = new int[10];
	std::cout << pa << "; " << pa + 1 << std::endl; // +1 ָ������4��λ�ã�һ��λ��1�ֽ�
	//delete (pa+1); //ָ�벻���ڣ��������

	// Test3
	A ca; //�����Ĭ�Ϲ��캯��,return�����������
	//B b; //�������B���캯���е� virtual_f() ָ������
	
	//int shuzu[7] = { 1, 2, 3, 4, 5, 6, 7 };
	//std::vector<int> v(shuzu, shuzu + 7);
	std::vector<int> v = { 1, 2, 3, 4, 5, 6, 7 }; //C++11��׼
	int* arr_wf = wrong_f(v);
	cout << arr_wf[0] << endl;

	return 0;
}

void inputToArrayTest(){
	//����һ���Կո�Ϊ�ָ������֣��������飬�س�Ϊ������ 
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

  