#include "colorReduce.h"
#include "highgui.h"

colorReduce::colorReduce()
{
}


colorReduce::~colorReduce()
{
}

void colorReduce::cr_at(Mat& image, int div)
{
	for (int i = 0; i < image.rows; i++)
	{
		for (int j = 0; j < image.cols; j++)
		{
			image.at<Vec3b>(i, j)[0] = image.at<Vec3b>(i, j)[0] / div*div + div / 2;//image.at<uchar>(i,j)：取出灰度图像中i行j列的点。mage.at<Vec3b>(i,j)[k]：取出彩色图像中i行j列第k通道的颜色点。
			image.at<Vec3b>(i, j)[1] = image.at<Vec3b>(i, j)[1] / div*div + div / 2;
			image.at<Vec3b>(i, j)[2] = image.at<Vec3b>(i, j)[2] / div*div + div / 2;
		}
	}
}

void colorReduce::cr_point(const Mat& image, Mat& outImage, int div)
{
	// 创建与原图像等尺寸的图像
	outImage.create(image.size(), image.type());
	int nr = image.rows;
	// 将3通道转换为1通道
	int nl = image.cols*image.channels();
	for (int k = 0; k<nr; k++)
	{
		// 每一行图像的指针
		const uchar* inData = image.ptr<uchar>(k);
		uchar* outData = outImage.ptr<uchar>(k);
		for (int i = 0; i<nl; i++)
		{
			outData[i] = inData[i] / div*div + div / 2;
		}
	}
}

void colorReduce::cr_isContinuous(const Mat& image, Mat& outImage, int div)
{
	int nr = image.rows;
	int nc = image.cols;
	outImage.create(image.size(), image.type());
	if (image.isContinuous() && outImage.isContinuous())
	{
		nr = 1;
		nc = nc*image.rows*image.channels();
	}
	for (int i = 0; i<nr; i++)
	{
		const uchar* inData = image.ptr<uchar>(i);
		uchar* outData = outImage.ptr<uchar>(i);
		for (int j = 0; j<nc; j++)
		{
			*outData++ = *inData++ / div*div + div / 2;
		}
	}
}

void colorReduce::cr_iterator(const Mat& image, Mat& outImage, int div)
{
	outImage.create(image.size(), image.type());
	MatConstIterator_<Vec3b> it_in = image.begin<Vec3b>();
	MatConstIterator_<Vec3b> itend_in = image.end<Vec3b>();
	MatIterator_<Vec3b> it_out = outImage.begin<Vec3b>();
	MatIterator_<Vec3b> itend_out = outImage.end<Vec3b>();
	while (it_in != itend_in)
	{
		(*it_out)[0] = (*it_in)[0] / div*div + div / 2;
		(*it_out)[1] = (*it_in)[1] / div*div + div / 2;
		(*it_out)[2] = (*it_in)[2] / div*div + div / 2;
		it_in++;
		it_out++;
	}
}