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
* 功能 : 将 cv::Mat 数据写入到 .txt 文件
*----------------------------
* 函数 : WriteData
* 访问 : public
* 返回 : -1：打开文件失败；0：写入数据成功；1：矩阵为空
*
* 参数 : fileName	[in]	文件名
* 参数 : matData	[in]	矩阵数据
*/
int WriteData(string fileName, cv::Mat& matData)
{
	int retVal = 0;

	// 检查矩阵是否为空
	if (matData.empty())
	{
		cout << "矩阵为空" << endl;
		retVal = 1;
		return (retVal);
	}

	// 打开文件
	ofstream outFile(fileName.c_str(), ios_base::out);	//按新建或覆盖方式写入
	if (!outFile.is_open())
	{
		cout << "打开文件失败" << endl;
		retVal = -1;
		return (retVal);
	}

	// 写入数据
	for (int r = 0; r < matData.rows; r++)
	{
		for (int c = 0; c < matData.cols; c++)
		{
			//int data = matData.at<uchar>(r, c);	//读取数据，at<type> - type 是矩阵元素的具体数据格式
			int data = matData.at<float>(r, c);	//读取数据，at<type> - type 是矩阵元素的具体数据格式
			outFile << data << "\t";	//每列数据用 tab 隔开
		}
		outFile << endl;	//换行
	}

	return (retVal);
}


/*----------------------------
* 功能 : 从 .txt 文件中读入数据，保存到 cv::Mat 矩阵
*		- 默认按 float 格式读入数据，
*		- 如果没有指定矩阵的行、列和通道数，则输出的矩阵是单通道、N 行 1 列的
*----------------------------
* 函数 : LoadData
* 访问 : public
* 返回 : -1：打开文件失败；0：按设定的矩阵参数读取数据成功；1：按默认的矩阵参数读取数据
*
* 参数 : fileName	[in]	文件名
* 参数 : matData	[out]	矩阵数据
* 参数 : matRows	[in]	矩阵行数，默认为 0
* 参数 : matCols	[in]	矩阵列数，默认为 0
* 参数 : matChns	[in]	矩阵通道数，默认为 0
*/
int LoadData(string fileName, cv::Mat& matData, int matRows = 0, int matCols = 0, int matChns = 0)
{
	int retVal = 0;

	// 打开文件
	ifstream inFile(fileName.c_str(), ios_base::in);
	if (!inFile.is_open())
	{
		cout << "读取文件失败" << endl;
		retVal = -1;
		return (retVal);
	}

	// 载入数据
	istream_iterator<float> begin(inFile);	//按 float 格式取文件数据流的起始指针
	istream_iterator<float> end;			//取文件流的终止位置
	vector<float> inData(begin, end);		//将文件数据保存至 std::vector 中
	cv::Mat tmpMat = cv::Mat(inData);		//将数据由 std::vector 转换为 cv::Mat

	// 输出到命令行窗口
	//copy(vec.begin(),vec.end(),ostream_iterator<double>(cout,"\t")); 

	// 检查设定的矩阵尺寸和通道数
	size_t dataLength = inData.size();
	//1.通道数
	if (matChns == 0)
	{
		matChns = 1;
	}
	//2.行列数
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
	//3.数据总长度
	if (dataLength != (matRows * matCols * matChns))
	{
		cout << "读入的数据长度 不满足 设定的矩阵尺寸与通道数要求，将按默认方式输出矩阵！" << endl;
		retVal = 1;
		matChns = 1;
		matRows = dataLength;
	}

	// 将文件数据保存至输出矩阵
	matData = tmpMat.reshape(matChns, matRows).clone();

	return (retVal);
}

void main()
{
	//可视化数据
	int width = 21, height = 21;
	Mat image = Mat::zeros(height, width, CV_8UC3);

	//设置训练数据
	string filename = "testSet.txt";
	cv::Mat matData;
	LoadData(filename,matData,100,3,1);//txt数据读入Mat，第三列是正负标签。

	cv::Mat labelsMat=matData.col(2);//提取第2列为标签
	string filename_out = "testSet_label.txt";
	WriteData(filename_out, labelsMat);//保存txt
	Mat trainingDataMat = matData(Range::all(), Range(0, 2));//提取第0,1列为训练数据

	//设置支持向量机的参数
	CvSVMParams params;
	params.svm_type = CvSVM::C_SVC;//SVM类型：使用C支持向量机
	params.kernel_type = CvSVM::LINEAR;//核函数类型：线性
	params.term_crit = cvTermCriteria(CV_TERMCRIT_ITER, 100, 1e-6);//终止准则函数：当迭代次数达到最大值时终止

	//训练SVM
	//建立一个SVM类的实例
	CvSVM SVM;
	//训练模型，参数为：输入数据、响应、XX、XX、参数（前面设置过）
	SVM.train(trainingDataMat, labelsMat, Mat(), Mat(), params);

	Vec3b green(0, 255, 0), red(0, 0, 255);
	//显示判决域
	for (int i = 0; i < image.rows; ++i)
		for (int j = 0; j < image.cols; ++j)
		{
		Mat sampleMat = (Mat_<float>(1, 2) << i, j);
		//predict是用来预测的，参数为：样本、返回值类型（如果值为ture而且是一个2类问题则返回判决函数值，否则返回类标签）、
		float response = SVM.predict(sampleMat);

		if (response == 1)
			image.at<Vec3b>(j, i) = green;
		else if (response == -1)
			image.at<Vec3b>(j, i) = red;
		}
	//画出训练数据
	int thickness = -1;
	int lineType = 8;
	circle(image, Point(501, 10), 5, Scalar(0, 0, 0), thickness, lineType);//画圆
	circle(image, Point(255, 10), 5, Scalar(255, 255, 255), thickness, lineType);
	circle(image, Point(501, 255), 5, Scalar(255, 255, 255), thickness, lineType);
	circle(image, Point(10, 501), 5, Scalar(255, 255, 255), thickness, lineType);
	circle(image, Point(501, 128), 5, Scalar(0, 0, 0), thickness, lineType);
	//显示支持向量
	thickness = 2;
	lineType = 8;
	//获取支持向量的个数
	int c = SVM.get_support_vector_count();

	for (int i = 0; i < c; ++i)
	{
		//获取第i个支持向量
		const float* v = SVM.get_support_vector(i);
		//支持向量用到的样本点，用灰色进行标注
		circle(image, Point((int)v[0], (int)v[1]), 6, Scalar(128, 128, 128), thickness, lineType);
	}

	imwrite("result.png", image);        // save the image 

	imshow("SVM Simple Example", image); // show it to the user
	waitKey(0);
}