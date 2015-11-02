#pragma once
#include"cv.h"
#include"highgui.h"
using namespace cv;

class CColorDetect
{
public:
	CColorDetect();
	~CColorDetect();

public:
	void SetMinDistance(int dist);
	void SetTargetColor(uchar red, uchar green, uchar blue);
	void SetTargetColor(Vec3b color); //set the target color
	void on_change(int position);//��trackbarλ�ñ��ı��ʱ��ϵͳ���������ص���������������pos����Ϊ��ʾtrackbarλ�õ���ֵ��
	void on_mouse(int event, int x, int y, int flags, void*);//�����Ӧ setMouseCalback �Ļص�����
	Mat process(const Mat& image); //main process;���������
private:
	Mat srcImage;
	Mat tempImage;
	int minDist=50; //minium acceptable distance,�����޶�������ɫ֮��ľ��룬�൱��PhotoShop��ħ�������ߵ���ֵ
	Vec3b target;//target color;Ŀ����ɫ���൱��������ɫ,ͨ��˳��ΪBGR
	Mat result; //the result;�洢����õ��Ľ��ͼ��
};

