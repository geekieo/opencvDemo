#pragma
#include "highgui.h"
using namespace cv;
class colorReduce
{
public:
	colorReduce();
	~colorReduce();

	void cr_at(Mat& image, int div);//Mat���ṩ��һ��at�ķ�������ȡ��ͼ���ϵĵ㡣imageΪ����ͼ��divΪ��ɫɫ��
	void cr_point(const Mat& image, Mat& outImage, int div);//��ָ��������ͼ��
	void cr_isContinuous(const Mat& image, Mat& outImage, int div);//Mat�ṩ��һ�����ͼ���Ƿ������ĺ���isContinuous()����ͼ����ͨʱ�����ǾͿ��԰�ͼ����ȫչ����������һ��
	void cr_iterator(const Mat& image, Mat& outImage, int div);//�õ�����������
};

