
#include "stdafx.h"

#include "CGlobal.h"

CGlobal::CGlobal()
{
	TheImage_temp=NULL;
	img_org=NULL;
	prev_pt_temp=cvPoint(-1,-1);
    color_R=255;
	color_B=0;
	//CvPoint **pts;
	//npts=new int;
	npts=NULL;
    contours=1;
	FgSdNb=0;
	BgSdNb=0;
	MaxSdNb=5000;
	clusters_k=5;
	iteration_k=50;
	epsilon_k=1;
}
CGlobal::~CGlobal()
{
	//free(npts);
}


void CGlobal::get_kmeans_data(int side)
{
	int i;//j;
    int SdNb;
	int row,col;
	CvScalar s;

	if (side==Forground)
	{
		SdNb=FgSdNb;
	}
	else
	{
		SdNb=BgSdNb;
	}

	for (i=0;i<SdNb;i++)
	{
		row=SdPt[side][i].x;
		col=SdPt[side][i].y;

		s=cvGet2D(img_org,row,col);

		k_mean_data[0][i]=(char)s.val[2];
		k_mean_data[1][i]=(char)s.val[1];
		k_mean_data[2][i]=(char)s.val[0];
	}
}

// CvMat*Pts_k;
// CvMat*labels_k;
// CvMat*Centers_k;
// int clusters_k;

void CGlobal::get_cvKMeans_data(int side)
{
	int i;
	int SdNb;
	int row,col;
	CvScalar s;


	if (side==Forground)
	{
		SdNb=FgSdNb;
	}
	else
	{
		SdNb=BgSdNb;
	}

	if (Pts_k)
	{
		cvReleaseMat(&Pts_k);
	}
    
	Pts_k=cvCreateMat(SdNb,3,CV_32FC1);

	if (side==Forground)
	{
		if (labelsF_k)
		{
			cvReleaseMat(&labelsF_k);
		}

		labelsF_k=cvCreateMat(SdNb,1,CV_32SC1);
	}
	if (side==BackGround)
	{
		if (labelsB_k)
		{
			cvReleaseMat(&labelsB_k);
		}

		labelsB_k=cvCreateMat(SdNb,1,CV_32SC1);
	}
	if (side==Forground)
	{
		if (CentersF_k)
		{
			cvReleaseMat(&CentersF_k);
		}

		CentersF_k=cvCreateMat(clusters_k,3,CV_64FC1);

		cvmSet(CentersF_k,0,0,0);
	}
	if (side==BackGround)
	{
		if (CentersB_k)
		{
			cvReleaseMat(&CentersB_k);
		}

		CentersB_k=cvCreateMat(clusters_k,3,CV_64FC1);
	}

/*
	IplImage*tt;

	tt=cvCloneImage(img_org);

	cvNamedWindow("TT");
*/
	for (i=0;i<SdNb;i++)
	{
		row=SdPt[side][i].y;
		col=SdPt[side][i].x;

		s=cvGet2D(img_org,row,col);

		//(float*)(Pts_k->data.ptr+i*Pts_k->step)

// 		int j;
// 
// 		j=sizeof(float);

		cvmSet(Pts_k,i,0,s.val[2]);

		cvmSet(Pts_k,i,1,s.val[1]);

		cvmSet(Pts_k,i,2,s.val[0]);

		//cvSet2D(Pts_k,i,0,s);


/*
		CvPoint pt;

		pt=cvPoint(row,col);

		cvLine(tt,pt,pt,CV_RGB(255,0,0),3,8,0);
*/
	}


// 	float t;
// 
// 	t=(float)cvmGet(Pts_k,SdNb-1,0);

/*

	cvShowImage("TT",tt);

	cvWaitKey(2000);
*/
}

void CGlobal::reset_glft()
{
	if (TheImage_temp)
	{
		cvReleaseImage(&TheImage_temp);
	}
	if (img_org)
	{
		cvReleaseImage(&img_org);
	}
	if (pan_mask)
	{
		cvReleaseImage(&pan_mask);
	}
	if (pts)
	{
		free(pts);
	}
	if (npts)
	{
		free(npts);
	}

	FgSdNb=0;
	BgSdNb=0;

	if (Pts_k)
	{
		cvReleaseMat(&Pts_k);
	}
	if (labelsF_k)
	{
		cvReleaseMat(&labelsF_k);
	}
	if (labelsB_k)
	{
		cvReleaseMat(&labelsB_k);
	}
	if (CentersF_k)
	{
		cvReleaseMat(&CentersF_k);
	}
	if (CentersB_k)
	{
		cvReleaseMat(&CentersB_k);
	}
}