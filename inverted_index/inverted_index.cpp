// inverted_index.cpp : 定义控制台应用程序的入口点。
//

#include <iostream>
#include <map>
#include <list>
#include <vector>
#include <string>
#include <set>

using namespace std;

template <class T>
class InvIndex :public map < T, list<int> > {
public:
	vector<vector<T>> docs; //文档正排表，二维链表，src

public:
	// Key function！向倒排索引中加入一个文档
	void add(vector<T> &doc){
		//在正排表里记录该文档
		docs.push_back(doc);
		int curDocID = docs.size();//文档编号 == size，即从1开始记录

		//遍历doc里所有term
		for (int w = 0; w < (int)doc.size(); w++){
			map<T, list<int>>::iterator it;//声明 map<T,list<int>> 类型的迭代器
			it = this->find(doc[w]);//find继承自map，返回被查找元素的位置，没有则返回end()

			//如果倒排链不存在，新建倒排链
			if (it == this->end()){
				list<int> newList;
				(*this)[doc[w]] = newList;
				it = this->find(doc[w]);
			}
			//在倒排链末尾插入新的文档
			it->second.push_back(curDocID);//second 为 value
		}
	}

	//在索引中进行一次查询
	void retrieve(vector<T> &query, set<int> &docIDs){
		int termNum = query.size();

		//合并所有term的倒排链
		docIDs.clear();
		for (int t = 0; t < termNum; t++){
			map<T, list<int>>::iterator it;
			//该term倒排链不存在
			if ((it = this->find(query[t])) != this->end());
			docIDs.insert(it->second.begin(), it->second.end());
		}
	}

};

//生成测试数据
InvIndex<string>* loadTestData(){
	string D1_data[] = { "谷歌", "地图", "之父", "跳槽", "Facebook" };
	int D1_size = sizeof(D1_data) / sizeof(string);
	vector<string> D1(D1_data, D1_data + D1_size);//尾部存放 datasize

	string D2_tmp[] = { "谷歌", "地图", "之父", "加盟", "Facebook" };
	int D2_tmp_size = sizeof(D2_tmp) / sizeof(string);
	vector<string> D2(D2_tmp, D2_tmp + D2_tmp_size);

	string D3_tmp[] = { "谷歌", "地图", "创始人", "拉斯", "离开", "谷歌", "加盟", "Facebook" };
	int D3_tmp_size = sizeof(D3_tmp) / sizeof(string);
	vector<string> D3(D3_tmp, D3_tmp + D3_tmp_size);

	string D4_tmp[] = { "谷歌", "地图", "创始人", "跳槽", "Facebook", "与", "Wave", "项目", "取消", "有关" };
	int D4_tmp_size = sizeof(D4_tmp) / sizeof(string);
	vector<string> D4(D4_tmp, D4_tmp + D4_tmp_size);

	string D5_tmp[] = { "谷歌", "地图", "创始人", "拉斯", "加盟", "社交", "网站", "Facebook" };
	int D5_tmp_size = sizeof(D5_tmp) / sizeof(string);
	vector<string> D5(D5_tmp, D5_tmp + D5_tmp_size);

	InvIndex<string>* inverted_index = new InvIndex<string>();
	inverted_index->add(D1);
	inverted_index->add(D2);
	inverted_index->add(D3);
	inverted_index->add(D4);
	inverted_index->add(D5);

	return inverted_index;
}

int queryTest(InvIndex<string>* inverted_index){
	string str_query[] = { "谷歌", "地图", "之父", "跳槽", "Facebook", "创始人", "加盟", "拉斯", "离开", "离开", "与", "Wave", "项目", "取消", "有关", "社交", "网站" };
	for (int i = 0; i < sizeof(str_query) / sizeof(string); i++){
		vector<string> query;
		query.push_back(str_query[i]);

		cout << str_query[i] << " ";

		set<int> docSet;

		inverted_index->retrieve(query, docSet);

		set<int>::iterator it;
		for (it = docSet.begin(); it != docSet.end(); it++){
			cout << "D" << *it << " ";
		}
		cout << endl;
	}
	return 0;
}

int main(){
	queryTest(loadTestData());
	
	return 0;
}

