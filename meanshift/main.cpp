#include "cv.h"
#include "highgui.h"
#include <stdio.h>
#include <ctype.h>

IplImage *image = 0, *hsv = 0, *hue = 0, *mask = 0, *backproject = 0, *histimg = 0;//用HSV中的Hue分量进行跟踪
CvHistogram *hist = 0;//直方图类

int backproject_mode = 0;
int select_object = 0;
int track_object = 0;
int show_hist = 1;
CvPoint origin;
CvRect selection;
CvRect track_window;
CvBox2D track_box; // Meanshift跟踪算法返回的Box类
CvConnectedComp track_comp;
int hdims = 30; // 划分直方图bins的个数，越多越精确

float hranges_arr[] = {0,180};//像素值的范围
float* hranges = hranges_arr;//用于初始化CvHistogram类
int vmin = 10, vmax = 256, smin = 30;

void on_mouse( int event, int x, int y, int flags,void *NotUsed)//该函数用于选择跟踪目标
{
	if( !image )
		return;

	if( image->origin )
		y = image->height - y;

	if( select_object )//如果处于选择跟踪物体阶段，则对selection用当前的鼠标位置进行设置
	{
		selection.x = MIN(x,origin.x);
		selection.y = MIN(y,origin.y);
		selection.width = selection.x + CV_IABS(x - origin.x);
		selection.height = selection.y + CV_IABS(y - origin.y);

		selection.x = MAX( selection.x, 0 );
		selection.y = MAX( selection.y, 0 );
		selection.width = MIN( selection.width, image->width );
		selection.height = MIN( selection.height, image->height );
		selection.width -= selection.x;
		selection.height -= selection.y;

	}

	switch( event )
	{
	case CV_EVENT_LBUTTONDOWN://开始点击选择跟踪物体
		origin = cvPoint(x,y);
		selection = cvRect(x,y,0,0);//坐标
		select_object = 1;//表明开始进行选取
		break;
	case CV_EVENT_LBUTTONUP:
		select_object = 0;//选取完成
		if( selection.width > 0 && selection.height > 0 )
			track_object = -1;//如果选择物体有效，则打开跟踪功能

		break;
	}
}


CvScalar hsv2rgb( float hue )//用于将Hue量转换成RGB量
{
	int rgb[3], p, sector;
	static const int sector_data[][3]={{0,2,1}, {1,2,0}, {1,0,2}, {2,0,1}, {2,1,0}, {0,1,2}};
	hue *= 0.033333333333333333333333333333333f;
	sector = cvFloor(hue);
	p = cvRound(255*(hue - sector));
	p ^= sector & 1 ? 255 : 0;

	rgb[sector_data[sector][0]] = 255;
	rgb[sector_data[sector][1]] = 0;
	rgb[sector_data[sector][2]] = p;

	return cvScalar(rgb[2], rgb[1], rgb[0],0);//返回对应的颜色值
}

int main( int argc, char** argv )
{
	CvCapture* capture = 0;
	IplImage* frame = 0;

	if( argc == 1 || (argc == 2 && strlen(argv[1]) == 1 && isdigit(argv[1][0])))
		capture = cvCaptureFromCAM( argc == 2 ? argv[1][0] - '0' : 0 );//打开摄像头
	else if( argc == 2 )
		capture = cvCaptureFromAVI( argv[1] );//打开AVI文件

	if( !capture )
	{
		fprintf(stderr,"Could not initialize capturing.../n");//打开视频流失败处理
		return -1;
	}

	printf( "Hot keys: /n/tESC - quit the program/n/tc - stop the tracking/n/tb - switch to/from backprojection view/n/th - show/hide object histogram/nTo initialize tracking, select the object with mouse/n" );//打印出程序功能列表
	cvNamedWindow( "CamShiftDemo", 1 );//建立视频窗口
	cvSetMouseCallback( "CamShiftDemo", on_mouse ); // 设置鼠标回调函数

	cvCreateTrackbar( "Vmin", "CamShiftDemo", &vmin, 256, 0 );//建立滑动条
	cvCreateTrackbar( "Vmax", "CamShiftDemo", &vmax, 256, 0 );
	cvCreateTrackbar( "Smin", "CamShiftDemo", &smin, 256, 0 );

	for(;;)//进入视频帧处理主循环
	{
		int i, bin_w, c;
		frame = cvQueryFrame( capture );
		if( !frame )
			break;

		if( !image )//刚开始先建立一些缓冲区
		{

			image = cvCreateImage( cvGetSize(frame), 8, 3 );// 根据获取帧大小，给image分配8位，3通道
			image->origin = frame->origin;//获取顶点位置
			hsv = cvCreateImage( cvGetSize(frame), 8, 3 );//给hsv分配图像空间8位，3通道
			hue = cvCreateImage( cvGetSize(frame), 8, 1 );//给色度分量分配8位，单通道
			mask = cvCreateImage( cvGetSize(frame), 8, 1 );//分配掩膜图像空间8位，单通道
			backproject = cvCreateImage( cvGetSize(frame), 8, 1 );//分配反向投影图空间，大小一样，单通道
			//创建一个指定尺寸的直方图，并且返回创建的直方图的指针（1维，直方图数量的数组，多维密集数组，每个条块范围的数组，)
			hist = cvCreateHist( 1, &hdims, CV_HIST_ARRAY, &hranges, 1 ); 
			
			histimg = cvCreateImage( cvSize(320,200), 8, 3 );//分配用于画直方图的空间
			cvZero( histimg );//背景为黑色
		}

		cvCopy( frame, image, 0 );
		cvCvtColor( image, hsv, CV_BGR2HSV ); // 把图像从RGB表色系转为HSV表色系

		if( track_object )//   如果当前有需要跟踪的物体  
		{
			int _vmin = vmin, _vmax = vmax;

			cvInRangeS( hsv, cvScalar(0,smin,MIN(_vmin,_vmax),0),cvScalar(180,256,MAX(_vmin,_vmax),0), mask ); //制作掩膜板，只处理像素值为H：0~180，S：smin~256，V：vmin~vmax之间的部分
			
			cvSplit( hsv, hue, 0, 0, 0 ); // 取得H分量

			if( track_object < 0 )//如果需要跟踪的物体还没有进行属性提取，则进行选取框类的图像属性提取
			{
				float max_val = 0.f;
				cvSetImageROI( hue, selection ); // 设置原选择框
				cvSetImageROI( mask, selection ); // 设置Mask的选择框

				cvCalcHist( &hue, hist, 0, mask ); // 得到选择框内且满足掩膜板内的直方图

				cvGetMinMaxHistValue( hist, 0, &max_val, 0, 0 ); 
				cvConvertScale( hist->bins, hist->bins, max_val ? 255. / max_val : 0., 0 ); // 对直方图转为0~255
				cvResetImageROI( hue ); // remove ROI
				cvResetImageROI( mask );
				track_window = selection;
				track_object = 1;

				cvZero( histimg );
				bin_w = histimg->width / hdims;

				for( i = 0; i < hdims; i++ )
				{
					int val = cvRound( 
						cvGetReal1D(hist->bins,i)*histimg->height/255 );
					CvScalar color = hsv2rgb(i*180.f/hdims);
					cvRectangle( histimg, cvPoint(i*bin_w,histimg->height),
						cvPoint((i+1)*bin_w,histimg->height - val),color, -1, 8, 0 );//画直方图到图像空间
				}
			}

			cvCalcBackProject( &hue, backproject, hist ); // 得到hue的反向投影图

			cvAnd( backproject, mask, backproject, 0 );//得到反向投影图mask内的内容
				cvCamShift( backproject, track_window,cvTermCriteria( CV_TERMCRIT_EPS | CV_TERMCRIT_ITER, 10, 1 ),&track_comp, &track_box );//使用MeanShift算法对backproject中的内容进行搜索，返回跟踪结果
			track_window = track_comp.rect;//得到跟踪结果的矩形框

			if( backproject_mode )
				cvCvtColor( backproject, image, CV_GRAY2BGR ); // 显示模式
			if( image->origin )
				track_box.angle = -track_box.angle;
			cvEllipseBox( image, track_box, CV_RGB(255,0,0), 3, CV_AA, 0 );//画出跟踪结果的位置
		}

		if( select_object && selection.width > 0 && selection.height > 0 )//如果正处于物体选择，画出选择框
		{
			cvSetImageROI( image, selection );
			cvXorS( image, cvScalarAll(255), image, 0 );
			cvResetImageROI( image );
		}

		cvShowImage( "CamShiftDemo", image );//显示视频和直方图
		cvShowImage( "Histogram", histimg );


		c = cvWaitKey(10);
		if( c == 27 )
			break;

		switch( c )
		{
		case 'b':
			backproject_mode ^= 1;
			break;
		case 'c':
			track_object = 0;
			cvZero( histimg );
			break;
		case 'h':
			show_hist ^= 1;
			if( !show_hist )
				cvDestroyWindow( "Histogram" );
			else
				cvNamedWindow( "Histogram", 1 );
			break;
		default:
			;
		}
	}

	cvReleaseCapture( &capture );
	cvDestroyWindow("CamShiftDemo");

	return 0;
}