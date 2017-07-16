// name: graham algorithm 
// author: geekieo
// date: 2017-7-12
// email:geekieo@hotmail.com

#include "stdafx.h"
#include <iostream>
#include <algorithm>
#include <vector>
#include <fstream>
#include <string>

typedef struct{
	int x;
	int y;
} vertice; //��ά��ṹ��

int amount = 0;//���ݼ�����
std::vector<vertice> vertices; //�㼯��Դ����
std::vector<vertice> convexHull; //͹���㼯���ɱ䳤���������

/*
 *�ж�������(������)�Ƿ����
 */
bool operator==(const vertice &pt1, const vertice &pt2) {
	return (pt1.x == pt2.x && pt1.y == pt2.y);
}

/*
 * ��(p0,p1)��(p0,p2)�������
 * �ú�����͹��ɨ��ĺ��ģ�����
 * ������Ҫ֪�����������Ϊ������(p0,p1)��(p0,p2)Ϊ��ʱ�룬���������Ϊ˳ʱ�롣
 * ��const ����&�������Զ����������Ϊ��������߱���Ч��
 */
inline int cross(const vertice& p0, const vertice& p1, const vertice& p2)
{
	vertice u, v;
	u.x = p1.x - p0.x, u.y = p1.y - p0.y;
	v.x = p2.x - p0.x, v.y = p2.y - p0.y;

	return u.x * v.y - u.y * v.x;
}

/*
 * ���������ŷʽ���롣
 */
inline int distance(const vertice& p1, const vertice& p2){
	return (p2.x - p1.x)*(p2.x - p1.x) + (p2.y - p1.y)*(p2.y - p1.y);
}

/*
 * �Ƚ�����������˳��
 * ���������������Աȣ�return true ��ʾ������ p1>p2��ʹ����˳��Ϊ��ʱ��˳��
 * void* ָ�����ͱ�ʾָ��ָ��Ķ����ڴ泤�Ȳ�ȷ��
 * (vertice*)Ϊǿ������ת������ʾaΪָ��vertice���Ͷ����ָ��
 * * ǰ��û�����ͣ�Ϊ�����÷�����ʾȡָ��ָ���ֵ
 */
inline bool graham_compare(const vertice &p1, const vertice &p2){
	int result = cross(vertices[0], p1, p2);//�������㵽��ʼ�㹹�����������
	//std::cout << result << std::endl;
	if (result)
		//���<0��return true����ʱ������
		return result > 0;
	// ���==0��������һֱ���ϣ������볤������
	return distance(vertices[0], p1) > distance(vertices[0], p2);
}

/*
 * graham ͹��ɨ�衣
 * ��ɨ���ѹ��ջ����ջ��3����˳���������
 * ����ʱ�루���Ϊ����ɨ��㼯
 * �������Ϊ����������
 * �������Ϊ�������������� p0,p1,p2 �е�p1
 */
inline void graham_scan(){
	//ǰ����һ����͹����
	convexHull.push_back(vertices[0]);
	convexHull.push_back(vertices[1]);
	int amount = vertices.size();
	//std::cout << "����:" <<amount<<std::endl;
	for (int i = 2; i < amount; i++){
		//ע�⣺�˴��ͳ�ʼ����ʱ���������������
		//��ʼ��������ʼ�㵽�����㹹�ɵ��������˴���͹�����ڽ����㹹�ɵ�������
		while (cross(convexHull[convexHull.size() - 2], convexHull[convexHull.size() - 1], vertices[i]) <= 0)
			convexHull.pop_back();
		convexHull.push_back(vertices[i]);
	}
}

int _tmain(int argc, _TCHAR* argv[])
{
	//��ȡ����
	std::ifstream in("case_in.txt");
	std::string line;
	int index = 0; //��ʼ������
	if (!in.eof()){
		in >> amount;
		std::cout << "����:" << std::endl << amount << std::endl;
	}
	while (!in.eof()){
		vertice temp;
		in >> temp.x >> temp.y;
		vertices.push_back(temp);
	}


	// ȷ����ʼ��
	for (int i = 0; i < amount; i++){
		in >> vertices[i].x >> vertices[i].y;
		if (vertices[index].x > vertices[i].x || (vertices[index].x == vertices[i].x && vertices[index].y > vertices[i].y))
			index = i;
		//std::cout << vertices[i].x << " " << vertices[i].y << " " << index << std::endl;
	}
	//std::cout << std::endl;

	in.close();

	//��ʼ�㽻���� vertices[0]
	vertice temp;
	temp.x = vertices[0].x, temp.y = vertices[0].y;
	vertices[0].x = vertices[index].x, vertices[0].y = vertices[index].y;
	vertices[index].x = temp.x, vertices[index].y = temp.y;

	//for (int i = 0; i < amount; i++){
	//	std::cout << vertices[i].x << " " << vertices[i].y << std::endl;
	//}
	//std::cout << std::endl;

	//�㼯����ʱ������
	std::sort(vertices.begin() + 1, vertices.end(), graham_compare);

	std::cout << "��ʱ������Դ���ݼ�:" << std::endl;
	for (int i = 0; i < amount; i++){
		std::cout << vertices[i].x << " " << vertices[i].y << std::endl;
	}

	//��˳��͹��ɨ��
	graham_scan();

	//output
	std::cout << "͹���㼯:" << std::endl;
	for (unsigned int i = 0; i < convexHull.size(); i++)
		std::cout << convexHull[i].x << ' ' << convexHull[i].y << std::endl;

	return 0;
}

