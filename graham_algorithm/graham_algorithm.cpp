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
} vertice; //二维点结构体

int amount = 0;//数据集点数
std::vector<vertice> vertices; //点集，源数据
std::vector<vertice> convexHull; //凸包点集，可变长，结果数据

/*
 *判断两个点(或向量)是否相等
 */
bool operator==(const vertice &pt1, const vertice &pt2) {
	return (pt1.x == pt2.x && pt1.y == pt2.y);
}

/*
 * 求(p0,p1)×(p0,p2)的外积。
 * 该函数是凸包扫描的核心！！！
 * 我们需要知道正负。结果为正，则(p0,p1)→(p0,p2)为逆时针，结果负，则为顺时针。
 * “const 类型&”修饰自定义类型入参为常量，提高编译效率
 */
inline int cross(const vertice& p0, const vertice& p1, const vertice& p2)
{
	vertice u, v;
	u.x = p1.x - p0.x, u.y = p1.y - p0.y;
	v.x = p2.x - p0.x, v.y = p2.y - p0.y;

	return u.x * v.y - u.y * v.x;
}

/*
 * 计算两点的欧式距离。
 */
inline int distance(const vertice& p1, const vertice& p2){
	return (p2.x - p1.x)*(p2.x - p1.x) + (p2.y - p1.y)*(p2.y - p1.y);
}

/*
 * 比较两个向量的顺序。
 * 用于排序函数中做对比，return true 表示升序中 p1>p2，使遍历顺序为逆时针顺序。
 * void* 指针类型表示指针指向的对象内存长度不确定
 * (vertice*)为强制类型转换，表示a为指向vertice类型对象的指针
 * * 前面没有类型，为解引用符，表示取指针指向的值
 */
inline bool graham_compare(const vertice &p1, const vertice &p2){
	int result = cross(vertices[0], p1, p2);//计算两点到起始点构成向量的外积
	//std::cout << result << std::endl;
	if (result)
		//外积<0，return true，逆时针升序。
		return result > 0;
	// 外积==0，向量在一直线上，按距离长度升序。
	return distance(vertices[0], p1) > distance(vertices[0], p2);
}

/*
 * graham 凸包扫描。
 * 将扫描点压入栈，将栈顶3个点顺序组成向量
 * 按逆时针（外积为正）扫描点集
 * 保留外积为正的两个点
 * 弹出外积为负的向量，例如 p0,p1,p2 中的p1
 */
inline void graham_scan(){
	//前两个一定在凸包上
	convexHull.push_back(vertices[0]);
	convexHull.push_back(vertices[1]);
	int amount = vertices.size();
	//std::cout << "点数:" <<amount<<std::endl;
	for (int i = 2; i < amount; i++){
		//注意：此处和初始排序时外积计算对象的区别。
		//初始排序是起始点到其他点构成的向量，此处是凸包里邻近三点构成的向量。
		while (cross(convexHull[convexHull.size() - 2], convexHull[convexHull.size() - 1], vertices[i]) <= 0)
			convexHull.pop_back();
		convexHull.push_back(vertices[i]);
	}
}

int _tmain(int argc, _TCHAR* argv[])
{
	//读取数据
	std::ifstream in("case_in.txt");
	std::string line;
	int index = 0; //起始点索引
	if (!in.eof()){
		in >> amount;
		std::cout << "点数:" << std::endl << amount << std::endl;
	}
	while (!in.eof()){
		vertice temp;
		in >> temp.x >> temp.y;
		vertices.push_back(temp);
	}


	// 确定起始点
	for (int i = 0; i < amount; i++){
		in >> vertices[i].x >> vertices[i].y;
		if (vertices[index].x > vertices[i].x || (vertices[index].x == vertices[i].x && vertices[index].y > vertices[i].y))
			index = i;
		//std::cout << vertices[i].x << " " << vertices[i].y << " " << index << std::endl;
	}
	//std::cout << std::endl;

	in.close();

	//起始点交换到 vertices[0]
	vertice temp;
	temp.x = vertices[0].x, temp.y = vertices[0].y;
	vertices[0].x = vertices[index].x, vertices[0].y = vertices[index].y;
	vertices[index].x = temp.x, vertices[index].y = temp.y;

	//for (int i = 0; i < amount; i++){
	//	std::cout << vertices[i].x << " " << vertices[i].y << std::endl;
	//}
	//std::cout << std::endl;

	//点集按逆时针排序
	std::sort(vertices.begin() + 1, vertices.end(), graham_compare);

	std::cout << "逆时针排序源数据集:" << std::endl;
	for (int i = 0; i < amount; i++){
		std::cout << vertices[i].x << " " << vertices[i].y << std::endl;
	}

	//按顺序凸包扫描
	graham_scan();

	//output
	std::cout << "凸包点集:" << std::endl;
	for (unsigned int i = 0; i < convexHull.size(); i++)
		std::cout << convexHull[i].x << ' ' << convexHull[i].y << std::endl;

	return 0;
}

