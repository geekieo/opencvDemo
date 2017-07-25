// inverted_index.cpp : �������̨Ӧ�ó������ڵ㡣
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
	vector<vector<T>> docs; //�ĵ����ű���ά����src

public:
	// Key function�����������м���һ���ĵ�
	void add(vector<T> &doc){
		//�����ű����¼���ĵ�
		docs.push_back(doc);
		int curDocID = docs.size();//�ĵ���� == size������1��ʼ��¼

		//����doc������term
		for (int w = 0; w < (int)doc.size(); w++){
			map<T, list<int>>::iterator it;//���� map<T,list<int>> ���͵ĵ�����
			it = this->find(doc[w]);//find�̳���map�����ر�����Ԫ�ص�λ�ã�û���򷵻�end()

			//��������������ڣ��½�������
			if (it == this->end()){
				list<int> newList;
				(*this)[doc[w]] = newList;
				it = this->find(doc[w]);
			}
			//�ڵ�����ĩβ�����µ��ĵ�
			it->second.push_back(curDocID);//second Ϊ value
		}
	}

	//�������н���һ�β�ѯ
	void retrieve(vector<T> &query, set<int> &docIDs){
		int termNum = query.size();

		//�ϲ�����term�ĵ�����
		docIDs.clear();
		for (int t = 0; t < termNum; t++){
			map<T, list<int>>::iterator it;
			//��term������������
			if ((it = this->find(query[t])) != this->end());
			docIDs.insert(it->second.begin(), it->second.end());
		}
	}

};

//���ɲ�������
InvIndex<string>* loadTestData(){
	string D1_data[] = { "�ȸ�", "��ͼ", "֮��", "����", "Facebook" };
	int D1_size = sizeof(D1_data) / sizeof(string);
	vector<string> D1(D1_data, D1_data + D1_size);//β����� datasize

	string D2_tmp[] = { "�ȸ�", "��ͼ", "֮��", "����", "Facebook" };
	int D2_tmp_size = sizeof(D2_tmp) / sizeof(string);
	vector<string> D2(D2_tmp, D2_tmp + D2_tmp_size);

	string D3_tmp[] = { "�ȸ�", "��ͼ", "��ʼ��", "��˹", "�뿪", "�ȸ�", "����", "Facebook" };
	int D3_tmp_size = sizeof(D3_tmp) / sizeof(string);
	vector<string> D3(D3_tmp, D3_tmp + D3_tmp_size);

	string D4_tmp[] = { "�ȸ�", "��ͼ", "��ʼ��", "����", "Facebook", "��", "Wave", "��Ŀ", "ȡ��", "�й�" };
	int D4_tmp_size = sizeof(D4_tmp) / sizeof(string);
	vector<string> D4(D4_tmp, D4_tmp + D4_tmp_size);

	string D5_tmp[] = { "�ȸ�", "��ͼ", "��ʼ��", "��˹", "����", "�罻", "��վ", "Facebook" };
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
	string str_query[] = { "�ȸ�", "��ͼ", "֮��", "����", "Facebook", "��ʼ��", "����", "��˹", "�뿪", "�뿪", "��", "Wave", "��Ŀ", "ȡ��", "�й�", "�罻", "��վ" };
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

