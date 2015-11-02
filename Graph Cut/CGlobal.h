
#include "OpenCV.h"

#define Forground 0
#define BackGround 1

class CGlobal
{
public:
	CGlobal();
	~CGlobal();

public:
	IplImage*TheImage_temp;
	IplImage*img_org;
	IplImage*pan_mask;
	CvPoint prev_pt_temp;

	int color_R,color_B;

	CvPoint **pts;
	int*npts;
	int contours;

	int MaxSdNb;
	CvPoint SdPt[2][500];
	int FgSdNb;
	int BgSdNb;
	char k_mean_data[3][500]; 
	int kmm;

	CvMat*Pts_k;
	CvMat*labelsF_k;
	CvMat*labelsB_k;
	CvMat*CentersF_k;
	CvMat*CentersB_k;

	int clusters_k;
	int iteration_k;
	double epsilon_k;


public:
	void get_kmeans_data(int side);
	void get_cvKMeans_data(int side);
	//void k_means();
	//kmeans()
	//cvKMeans()
	//cvKMeans2()

	void reset_glft();
	
};