#include <iostream>
#include <fstream>
#include <iterator>
#include <vector>
#include "cv.h"
#include "highgui.h"
#include <ml.h>
using namespace std;
using namespace cv;
/*----------------------------
* ���� : �� cv::Mat ����д�뵽 .txt �ļ�
*----------------------------
* ���� : WriteData
* ���� : public
* ���� : -1�����ļ�ʧ�ܣ�0��д�����ݳɹ���1������Ϊ��
*
* ���� : fileName	[in]	�ļ���
* ���� : matData	[in]	��������
*/
int WriteData(string fileName, cv::Mat& matData)
{
	int retVal = 0;

	// �������Ƿ�Ϊ��
	if (matData.empty())
	{
		cout << "����Ϊ��" << endl;
		retVal = 1;
		return (retVal);
	}

	// ���ļ�
	ofstream outFile(fileName.c_str(), ios_base::out);	//���½��򸲸Ƿ�ʽд��
	if (!outFile.is_open())
	{
		cout << "���ļ�ʧ��" << endl;
		retVal = -1;
		return (retVal);
	}

	// д������
	for (int r = 0; r < matData.rows; r++)
	{
		for (int c = 0; c < matData.cols; c++)
		{
			//int data = matData.at<uchar>(r, c);	//��ȡ���ݣ�at<type> - type �Ǿ���Ԫ�صľ������ݸ�ʽ
			int data = matData.at<float>(r, c);	//��ȡ���ݣ�at<type> - type �Ǿ���Ԫ�صľ������ݸ�ʽ
			outFile << data << "\t";	//ÿ�������� tab ����
		}
		outFile << endl;	//����
	}

	return (retVal);
}


/*----------------------------
* ���� : �� .txt �ļ��ж������ݣ����浽 cv::Mat ����
*		- Ĭ�ϰ� float ��ʽ�������ݣ�
*		- ���û��ָ��������С��к�ͨ������������ľ����ǵ�ͨ����N �� 1 �е�
*----------------------------
* ���� : LoadData
* ���� : public
* ���� : -1�����ļ�ʧ�ܣ�0�����趨�ľ��������ȡ���ݳɹ���1����Ĭ�ϵľ��������ȡ����
*
* ���� : fileName	[in]	�ļ���
* ���� : matData	[out]	��������
* ���� : matRows	[in]	����������Ĭ��Ϊ 0
* ���� : matCols	[in]	����������Ĭ��Ϊ 0
* ���� : matChns	[in]	����ͨ������Ĭ��Ϊ 0
*/
int LoadData(string fileName, cv::Mat& matData, int matRows = 0, int matCols = 0, int matChns = 0)
{
	int retVal = 0;

	// ���ļ�
	ifstream inFile(fileName.c_str(), ios_base::in);
	if (!inFile.is_open())
	{
		cout << "��ȡ�ļ�ʧ��" << endl;
		retVal = -1;
		return (retVal);
	}

	// ��������
	istream_iterator<float> begin(inFile);	//�� float ��ʽȡ�ļ�����������ʼָ��
	istream_iterator<float> end;			//ȡ�ļ�������ֹλ��
	vector<float> inData(begin, end);		//���ļ����ݱ����� std::vector ��
	cv::Mat tmpMat = cv::Mat(inData);		//�������� std::vector ת��Ϊ cv::Mat

	// ����������д���
	//copy(vec.begin(),vec.end(),ostream_iterator<double>(cout,"\t")); 

	// ����趨�ľ���ߴ��ͨ����
	size_t dataLength = inData.size();
	//1.ͨ����
	if (matChns == 0)
	{
		matChns = 1;
	}
	//2.������
	if (matRows != 0 && matCols == 0)
	{
		matCols = dataLength / matChns / matRows;
	}
	else if (matCols != 0 && matRows == 0)
	{
		matRows = dataLength / matChns / matCols;
	}
	else if (matCols == 0 && matRows == 0)
	{
		matRows = dataLength / matChns;
		matCols = 1;
	}
	//3.�����ܳ���
	if (dataLength != (matRows * matCols * matChns))
	{
		cout << "��������ݳ��� ������ �趨�ľ���ߴ���ͨ����Ҫ�󣬽���Ĭ�Ϸ�ʽ�������" << endl;
		retVal = 1;
		matChns = 1;
		matRows = dataLength;
	}

	// ���ļ����ݱ������������
	matData = tmpMat.reshape(matChns, matRows).clone();

	return (retVal);
}

void main()
{
	//���ӻ�����
	int width = 21, height = 21;
	Mat image = Mat::zeros(height, width, CV_8UC3);

	//����ѵ������
	string filename = "testSet.txt";
	cv::Mat matData;
	LoadData(filename,matData,100,3,1);//txt���ݶ���Mat����������������ǩ��

	cv::Mat labelsMat=matData.col(2);//��ȡ��2��Ϊ��ǩ
	string filename_out = "testSet_label.txt";
	WriteData(filename_out, labelsMat);//����txt
	Mat trainingDataMat = matData(Range::all(), Range(0, 2));//��ȡ��0,1��Ϊѵ������

	//����֧���������Ĳ���
	CvSVMParams params;
	params.svm_type = CvSVM::C_SVC;//SVM���ͣ�ʹ��C֧��������
	params.kernel_type = CvSVM::LINEAR;//�˺������ͣ�����
	params.term_crit = cvTermCriteria(CV_TERMCRIT_ITER, 100, 1e-6);//��ֹ׼�����������������ﵽ���ֵʱ��ֹ

	//ѵ��SVM
	//����һ��SVM���ʵ��
	CvSVM SVM;
	//ѵ��ģ�ͣ�����Ϊ���������ݡ���Ӧ��XX��XX��������ǰ�����ù���
	SVM.train(trainingDataMat, labelsMat, Mat(), Mat(), params);

	Vec3b green(0, 255, 0), red(0, 0, 255);
	//��ʾ�о���
	for (int i = 0; i < image.rows; ++i)
		for (int j = 0; j < image.cols; ++j)
		{
		Mat sampleMat = (Mat_<float>(1, 2) << i, j);
		//predict������Ԥ��ģ�����Ϊ������������ֵ���ͣ����ֵΪture������һ��2�������򷵻��о�����ֵ�����򷵻����ǩ����
		float response = SVM.predict(sampleMat);

		if (response == 1)
			image.at<Vec3b>(j, i) = green;
		else if (response == -1)
			image.at<Vec3b>(j, i) = red;
		}
	//����ѵ������
	int thickness = -1;
	int lineType = 8;
	circle(image, Point(501, 10), 5, Scalar(0, 0, 0), thickness, lineType);//��Բ
	circle(image, Point(255, 10), 5, Scalar(255, 255, 255), thickness, lineType);
	circle(image, Point(501, 255), 5, Scalar(255, 255, 255), thickness, lineType);
	circle(image, Point(10, 501), 5, Scalar(255, 255, 255), thickness, lineType);
	circle(image, Point(501, 128), 5, Scalar(0, 0, 0), thickness, lineType);
	//��ʾ֧������
	thickness = 2;
	lineType = 8;
	//��ȡ֧�������ĸ���
	int c = SVM.get_support_vector_count();

	for (int i = 0; i < c; ++i)
	{
		//��ȡ��i��֧������
		const float* v = SVM.get_support_vector(i);
		//֧�������õ��������㣬�û�ɫ���б�ע
		circle(image, Point((int)v[0], (int)v[1]), 6, Scalar(128, 128, 128), thickness, lineType);
	}

	imwrite("result.png", image);        // save the image 

	imshow("SVM Simple Example", image); // show it to the user
	waitKey(0);
}