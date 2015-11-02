#pragma
#include "highgui.h"
using namespace cv;
class colorReduce
{
public:
	colorReduce();
	~colorReduce();

	void cr_at(Mat& image, int div);//Mat类提供了一个at的方法用于取得图像上的点。image为输入图像，div为颜色色段
	void cr_point(const Mat& image, Mat& outImage, int div);//用指针来遍历图像
	void cr_isContinuous(const Mat& image, Mat& outImage, int div);//Mat提供了一个检测图像是否连续的函数isContinuous()。当图像连通时，我们就可以把图像完全展开，看成是一行
	void cr_iterator(const Mat& image, Mat& outImage, int div);//用迭代器来遍历
};

