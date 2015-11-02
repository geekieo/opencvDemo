// Graph CutDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Graph Cut.h"
#include "Graph CutDlg.h"
#include "CGlobal.h"
#include "graph.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////////
#define Infine 9999999

CGlobal GlFt;

extern void kmeans(const CvMat* samples, CvTermCriteria termcrit, CvMat* centers, CvMat* labels);


//////////////////////////////////////////////////////////////////////////


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CGraphCutDlg dialog




CGraphCutDlg::CGraphCutDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CGraphCutDlg::IDD, pParent)
	, TheImage(NULL)
	, RefPoint(0)
	, EndPoint(0)
	, ClickTimes(0)
	, img_stroked(NULL)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	

}

void CGraphCutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CGraphCutDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_InputImage, &CGraphCutDlg::OnBnClickedInputimage)
	//ON_STN_CLICKED(IDC_ShowImg, &CGraphCutDlg::OnStnClickedShowimg)
	ON_BN_CLICKED(IDC_BACKGROUND, &CGraphCutDlg::OnBnClickedBackground)
	ON_BN_CLICKED(IDC_FORGROUND, &CGraphCutDlg::OnBnClickedForground)
	ON_BN_CLICKED(IDC_GraphCut, &CGraphCutDlg::OnBnClickedGraphcut)
	ON_BN_CLICKED(IDOK, &CGraphCutDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CGraphCutDlg message handlers

BOOL CGraphCutDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here

	//////////////////////////////////////////////////////////////////////////
	CvSize ImageSize;
	
	ImageSize.height=IMAGE_HEIGHT;
	ImageSize.width=IMAGE_WIDTH;

	TheImage=cvCreateImage(ImageSize,IPL_DEPTH_8U,IMAGE_CHANNELS);

	//////////////////////////////////////////////////////////////////////////

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CGraphCutDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CGraphCutDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();

		//CDialog::UpdateWindow();

		//ShowImage(TheImage,IDC_ShowImg);
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CGraphCutDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CGraphCutDlg::OnBnClickedInputimage()
{
	// TODO: Add your control notification handler code here

	//////////////////////////////////////////////////////////////////////////

	reset_dg();
	
	//cvReleaseImage(&TheImage);

	CFileDialog dlg(TRUE,_T("*.bmp"),NULL,OFN_FILEMUSTEXIST|OFN_PATHMUSTEXIST|OFN_HIDEREADONLY,_T("image file(*.bmp;*.jpg)|*.bmp;*.jpg|ALL Files (*.*) | *.*||"),NULL);

	dlg.m_ofn.lpstrTitle=_T("Open Image");

	if (dlg.DoModal()!=IDOK)
	{
		return;
	}

	CString mpath=dlg.GetPathName();

	TheImage=cvLoadImage(mpath,1);

	GlFt.img_org=cvCloneImage(TheImage);

	//GlFt.pan_mask=cvCloneImage(TheImage);

	GlFt.pan_mask=cvCreateImage(cvSize(TheImage->width,TheImage->height),IPL_DEPTH_8U,1);

	cvZero(GlFt.pan_mask);

	if (!TheImage)
	{
		return;
	}

	//ResizeImage(ipl);


	ShowImage(TheImage);//,IDC_ShowImg);//IDC_ShowImg

	//////////////////////////////////////////////////////////////////////////
}

void on_mouse_fb(int event,int x,int y,int flags,void*pos)
{
	CvPoint pt=cvPoint(x,y);

	if (event==CV_EVENT_LBUTTONUP)//|| !(flags & CV_EVENT_FLAG_LBUTTON))
	{
		GlFt.prev_pt_temp=cvPoint(-1,-1);
	}
	else
	{
		if (event==CV_EVENT_LBUTTONDOWN)
		{
			GlFt.prev_pt_temp=cvPoint(x,y);

			cvLine(GlFt.TheImage_temp,pt,pt,CV_RGB(GlFt.color_R,GlFt.color_B,0),3,8,0);//prev_pt_temp
            
			if (GlFt.color_R)
			{
				((unsigned char*)(GlFt.pan_mask->imageData+y*GlFt.pan_mask->widthStep))[x]=Forground+1;
			}
			else
			{
				((unsigned char*)(GlFt.pan_mask->imageData+y*GlFt.pan_mask->widthStep))[x]=BackGround+1;
			}


			if (GlFt.color_R&&GlFt.FgSdNb<GlFt.MaxSdNb)
			{
				GlFt.SdPt[Forground][GlFt.FgSdNb]=cvPoint(x,y);
				GlFt.FgSdNb++;
			}
			else
			{
				if (GlFt.BgSdNb<GlFt.MaxSdNb)
				{
					GlFt.SdPt[BackGround][GlFt.BgSdNb]=cvPoint(x,y);
					GlFt.BgSdNb++;
				}			
			}


			cvShowImage("InputImage",GlFt.TheImage_temp);
		}
		else
		{
			if (event==CV_EVENT_MOUSEMOVE&& (flags & CV_EVENT_FLAG_LBUTTON))
			{
				if (GlFt.prev_pt_temp.x<0||GlFt.prev_pt_temp.y<0)
				{
					GlFt.prev_pt_temp=pt;
				}

				cvLine(GlFt.TheImage_temp,pt,pt,CV_RGB(GlFt.color_R,GlFt.color_B,0),3,8,0);

				if (GlFt.color_R)
				{
					((unsigned char*)(GlFt.pan_mask->imageData+y*GlFt.pan_mask->widthStep))[x]=Forground+1;
				}
				else 
				{
					((unsigned char*)(GlFt.pan_mask->imageData+y*GlFt.pan_mask->widthStep))[x]=BackGround+1;
				}

				if (GlFt.color_R&&GlFt.FgSdNb<GlFt.MaxSdNb)
				{
					GlFt.SdPt[Forground][GlFt.FgSdNb]=cvPoint(x,y);
					GlFt.FgSdNb++;
				}
				else
				{
					if (GlFt.BgSdNb<GlFt.MaxSdNb)
					{
						GlFt.SdPt[BackGround][GlFt.BgSdNb]=cvPoint(x,y);
						GlFt.BgSdNb++;
					}			
				}

				cvShowImage("InputImage",GlFt.TheImage_temp);
			}
			else
			{
				if (event==CV_EVENT_RBUTTONDOWN&&(flags&&CV_EVENT_FLAG_RBUTTON))
				{
					cvDestroyWindow("InputImage");

					exit(1);
				}
			}
		}
	}
}

void on_mouse_ploy(int event,int x,int y,int flags,void*pos)
{
	CvPoint pt=cvPoint(x,y);

	if (event==CV_EVENT_LBUTTONUP)//|| !(flags & CV_EVENT_FLAG_LBUTTON))
	{
		//prev_pt_temp=cvPoint(x,y);
	}

	else
	{
		if (event==CV_EVENT_LBUTTONDOWN)
		{
			//prev_pt_temp=cvPoint(x,y);

			//cvLine(TheImage_temp,pt,pt,CV_RGB(color_R,color_B,0),3,8,0);//prev_pt_temp

			//cvShowImage("InputImage",TheImage_temp);
		}
		else
		{
			if (event==CV_EVENT_MOUSEMOVE&& (flags & CV_EVENT_FLAG_LBUTTON))
			{
				if (GlFt.prev_pt_temp.x<0||GlFt.prev_pt_temp.y<0)
				{
					GlFt.prev_pt_temp=pt;
				}

				GlFt.pts[0][1]=pt;

				cvPolyLine(GlFt.TheImage_temp,GlFt.pts,GlFt.npts,GlFt.contours,1,CV_RGB(255,0,0),2,8,0);


			//	cvLine(TheImage_temp,pt,pt,CV_RGB(color_R,color_B,0),3,8,0);//prev_pt_temp

				cvShowImage("Poly",GlFt.TheImage_temp);
			}
			else
			{

				if (event==CV_EVENT_RBUTTONDOWN&&(flags&&CV_EVENT_FLAG_RBUTTON))
				{
					//cvDestroyWindow("InputImage");

					exit(1);
				}

			}
		}
	}


}
void CGraphCutDlg::ShowImage(IplImage*img)//,UINT ID)
{
	cvNamedWindow("InputImage");

	cvShowImage("InputImage",img);

	if (GlFt.TheImage_temp)
	{
		cvReleaseImage(&GlFt.TheImage_temp);
	}

	GlFt.TheImage_temp=cvCloneImage(img);

	cvSetMouseCallback("InputImage",on_mouse_fb,0);


	for (;;)
	{
		//int key;

		key=cvWaitKey(0);

		if (key=='c')//(char)
		{
			break;
		}
	}

	key=0;
/*
	img_stroked=cvCloneImage(GlFt.TheImage_temp);

	cvReleaseImage(&GlFt.TheImage_temp);

	cvShowImage("InputImage",img_stroked);
*/

	//////////////////////////////////////////////////////////////////////////
/*
	cvNamedWindow("Ploygon");

	//IplImage*img_ploy;

	GlFt.TheImage_temp=cvCloneImage(img);


	GlFt.pts=(CvPoint**)new (CvPoint*);

	GlFt.pts[0]=(CvPoint*)new CvPoint[4];

	GlFt.pts[0][0]=cvPoint(100,100);
	GlFt.pts[0][1]=cvPoint(200,100);
	GlFt.pts[0][2]=cvPoint(200,200);
	GlFt.pts[0][3]=cvPoint(100,200);


	(*GlFt.npts)=4;


	cvPolyLine(GlFt.TheImage_temp,GlFt.pts,GlFt.npts,GlFt.contours,1,CV_RGB(255,0,0),2,8,0);

	cvShowImage("Ploygon",GlFt.TheImage_temp);


	cvSetMouseCallback("Ploygon",on_mouse_ploy,0);

	int key;

    for(;;)
	{
		key=cvWaitKey(0);

		if ((char)key=='c')
		{
			exit(1);
		}
	}
*/



	//////////////////////////////////////////////////////////////////////////

}
void CGraphCutDlg::ResizeImage(IplImage*img)
{
	int w=img->width;
	int h=img->height;

	int max=(w>h)?w:h;

	float scale=(float)((float)max/256.0f);

	int nw=(int)(w/scale);
	int nh=(int)(h/scale);

	int tlx=(nw>nh)?0:(int)((256-nw)/2);
	int tly=(nw>nh)?(int)((256-nh)/2):0;

	cvSetImageROI(TheImage,cvRect(tlx,tly,nw,nh));

	cvResize(img,TheImage);

	cvResetImageROI(TheImage);
}

void CGraphCutDlg::OnBnClickedBackground()
{
	// TODO: Add your control notification handler code here

	GlFt.color_R=0;
	GlFt.color_B=255;
}

void CGraphCutDlg::OnBnClickedForground()
{
	// TODO: Add your control notification handler code here
	GlFt.color_R=255;
	GlFt.color_B=0;
}


void CGraphCutDlg::OnBnClickedGraphcut()
{
	// TODO: Add your control notification handler code here

	GlFt.get_cvKMeans_data(Forground);

	//int i;

	//i=cvKMeans2(GlFt.Pts_k,GlFt.clusters_k,GlFt.labelsF_k,cvTermCriteria(CV_TERMCRIT_EPS+CV_TERMCRIT_ITER,GlFt.iteration_k,GlFt.epsilon_k),1,0,0,GlFt.CentersF_k,0);

	kmeans(GlFt.Pts_k,cvTermCriteria(CV_TERMCRIT_EPS+CV_TERMCRIT_ITER,GlFt.iteration_k,GlFt.epsilon_k),GlFt.CentersF_k,GlFt.labelsF_k);//CV_TERMCRIT_EPS+

	GlFt.get_cvKMeans_data(BackGround);
    
	//cvKMeans2(GlFt.Pts_k,GlFt.clusters_k,GlFt.labelsB_k,cvTermCriteria(CV_TERMCRIT_EPS+CV_TERMCRIT_ITER,GlFt.iteration_k,GlFt.epsilon_k),1,0,0,GlFt.CentersB_k,0);

	kmeans(GlFt.Pts_k,cvTermCriteria(CV_TERMCRIT_EPS+CV_TERMCRIT_ITER,GlFt.iteration_k,GlFt.epsilon_k),GlFt.CentersB_k,GlFt.labelsB_k);//CV_TERMCRIT_EPS+


	if (GlFt.Pts_k)
	{
		cvReleaseMat(&GlFt.Pts_k);
	}
	if (GlFt.labelsF_k)
	{
		cvReleaseMat(&GlFt.labelsF_k);
	}
	if (GlFt.labelsB_k)
	{
		cvReleaseMat(&GlFt.labelsB_k);
	}

	cut();
}

void CGraphCutDlg::cut()
{
	int w,h;
	
	w=TheImage->width;
	h=TheImage->height;

	int nodes=w*h;
	int edges=w*h*4-3*(h-1)-3*(w-2)-3-4;

	double R,G,B,Rj,Gj,Bj;

	typedef Graph<double,double,double> GraphType;

	GraphType *g=new GraphType(nodes,edges);

	g->add_node(nodes);

	int i,j;
	int row,col;
	double dstcF,dstcB,dstcS,dstcAj;
	int adj[4];
	int adjN;
	double wF,wB;

	//Forground Source, Background Sink

	for (i=0;i<nodes;i++)
	{
		row=i/w;
		col=i%w;

		if (GlFt.pan_mask->imageData[row*GlFt.pan_mask->widthStep+col]==0)
		{
			R=(double)(((unsigned char*)(GlFt.img_org->imageData+row*GlFt.img_org->widthStep))[col*3+2]);
			G=(double)(((unsigned char*)(GlFt.img_org->imageData+row*GlFt.img_org->widthStep))[col*3+1]);
			B=(double)(((unsigned char*)(GlFt.img_org->imageData+row*GlFt.img_org->widthStep))[col*3+0]);
			get_distance_F(R,G,B,&dstcF);
			get_distance_B(R,G,B,&dstcB);

			dstcS=dstcB+dstcF;

			dstcF/=dstcS;

			dstcB/=dstcS;

			wF=dstcB;
			wB=dstcF;


			g->add_tweights(i,wF,wB);//(int)

			get_Adj(i,&adjN,&adj[0]);

			for(j=0;j<adjN;j++)
			{
				row=adj[j]/w;
				col=adj[j]%w;

				Rj=(double)(((unsigned char*)(GlFt.img_org->imageData+row*GlFt.img_org->widthStep))[col*3+2]);
				Gj=(double)(((unsigned char*)(GlFt.img_org->imageData+row*GlFt.img_org->widthStep))[col*3+1]);
				Bj=(double)(((unsigned char*)(GlFt.img_org->imageData+row*GlFt.img_org->widthStep))[col*3+0]);

				get_distance_adj(R,G,B,Rj,Gj,Bj,&dstcAj);

				g->add_edge(i,adj[j],dstcAj,dstcAj);//(int)

			}
		}
		else
		{
			if (GlFt.pan_mask->imageData[row*GlFt.pan_mask->widthStep+col]==Forground+1)
			{
				R=(double)(((unsigned char*)(GlFt.img_org->imageData+row*GlFt.img_org->widthStep))[col*3+2]);
				G=(double)(((unsigned char*)(GlFt.img_org->imageData+row*GlFt.img_org->widthStep))[col*3+1]);
				B=(double)(((unsigned char*)(GlFt.img_org->imageData+row*GlFt.img_org->widthStep))[col*3+0]);
				//get_distance_F(R,G,B,&dstcF);
				//get_distance_B(R,G,B,&dstcB);
// 				dstcF=0;
// 				dstcB=Infine;

				//dstcS=dstcB+dstcF;

				//dstcF/=dstcS;

				//dstcB/=dstcS;

				wF=Infine;
				wB=0;

				g->add_tweights(i,wF,wB);//(int)

				get_Adj(i,&adjN,&adj[0]);

				for(j=0;j<adjN;j++)
				{
					row=adj[j]/w;
					col=adj[j]%w;

					Rj=(double)(((unsigned char*)(GlFt.img_org->imageData+row*GlFt.img_org->widthStep))[col*3+2]);
					Gj=(double)(((unsigned char*)(GlFt.img_org->imageData+row*GlFt.img_org->widthStep))[col*3+1]);
					Bj=(double)(((unsigned char*)(GlFt.img_org->imageData+row*GlFt.img_org->widthStep))[col*3+0]);

					get_distance_adj(R,G,B,Rj,Gj,Bj,&dstcAj);

					g->add_edge(i,adj[j],dstcAj,dstcAj);//(int)

				}
			}
			else
			{
				R=(double)(((unsigned char*)(GlFt.img_org->imageData+row*GlFt.img_org->widthStep))[col*3+2]);
				G=(double)(((unsigned char*)(GlFt.img_org->imageData+row*GlFt.img_org->widthStep))[col*3+1]);
				B=(double)(((unsigned char*)(GlFt.img_org->imageData+row*GlFt.img_org->widthStep))[col*3+0]);


				//get_distance_F(R,G,B,&dstcF);
				//get_distance_B(R,G,B,&dstcB);
// 				dstcF=Infine;
// 				dstcB=0;

				//dstcS=dstcB+dstcF;

				//dstcF/=dstcS;

				//dstcB/=dstcS;

				wF=0;
				wB=Infine;

				g->add_tweights(i,wF,wB);//(int)

				get_Adj(i,&adjN,&adj[0]);

				for(j=0;j<adjN;j++)
				{
					row=adj[j]/w;
					col=adj[j]%w;

					Rj=(double)(((unsigned char*)(GlFt.img_org->imageData+row*GlFt.img_org->widthStep))[col*3+2]);
					Gj=(double)(((unsigned char*)(GlFt.img_org->imageData+row*GlFt.img_org->widthStep))[col*3+1]);
					Bj=(double)(((unsigned char*)(GlFt.img_org->imageData+row*GlFt.img_org->widthStep))[col*3+0]);


					get_distance_adj(R,G,B,Rj,Gj,Bj,&dstcAj);

					g->add_edge(i,adj[j],dstcAj,dstcAj);//(int)
     

					//g->add_edge(i,adj[j],0,0);

				}
			}
		}
	}

	double flow=g->maxflow();

	for (i=0;i<nodes;i++)
	{
		row=i/w;
		col=i%w;

		if (g->what_segment(i,g->SINK)==1)
		{
			((unsigned char*)(TheImage->imageData+row*GlFt.img_org->widthStep))[col*3+2]=0;//GlFt.TheImage_temp
			((unsigned char*)(TheImage->imageData+row*GlFt.img_org->widthStep))[col*3+1]=0;
			((unsigned char*)(TheImage->imageData+row*GlFt.img_org->widthStep))[col*3+0]=255;
		}
		else
		{
			if (g->what_segment(i,g->SINK)==0)
			{
				((unsigned char*)(TheImage->imageData+row*GlFt.img_org->widthStep))[col*3+2]=255;//GlFt.TheImage_temp
				((unsigned char*)(TheImage->imageData+row*GlFt.img_org->widthStep))[col*3+1]=0;
				((unsigned char*)(TheImage->imageData+row*GlFt.img_org->widthStep))[col*3+0]=0;
			}
			else
			{
				((unsigned char*)(TheImage->imageData+row*GlFt.img_org->widthStep))[col*3+2]=0;//GlFt.TheImage_temp
				((unsigned char*)(TheImage->imageData+row*GlFt.img_org->widthStep))[col*3+1]=255;
				((unsigned char*)(TheImage->imageData+row*GlFt.img_org->widthStep))[col*3+0]=0;

			}
		}

	}

	delete g;

	cvNamedWindow("Segment Result");

	//cvWaitKey(2000);

	for (;;)
	{
		if (TheImage)
		{
			cvShowImage("Segment Result",TheImage);
		}

		cvWaitKey(key);

		if (key=='c')
		{
			break;
		}
	}

	key=0;

	//cvDestroyAllWindows();


}
void CGraphCutDlg::get_distance_F(double R,double G,double B,double* dstc)
{
	int i;

	double dp=Infine,dc=0;

	double cR,cG,cB;

	//CvScalar s;  

	for (i=0;i<GlFt.clusters_k;i++)        
	{
 		cR=cvmGet(GlFt.CentersF_k,i,0);
 		cG=cvmGet(GlFt.CentersF_k,i,1);
 		cB=cvmGet(GlFt.CentersF_k,i,2);

// 		s=cvGet2D(GlFt.CentersF_k,i,0);
// 
// 		cR=s.val[2];
// 		cG=s.val[1];
// 		cB=s.val[0];

		

		dc=sqrt((R-cR)*(R-cR)+(G-cG)*(G-cG)+(B-cB)*(B-cB));

		if (dc<dp)
		{
			dp=dc;
		}
	}

	(*dstc)=dp;
}
void CGraphCutDlg::get_distance_B(double R,double G,double B,double* dstc)
{
	int i;

	double dp=Infine,dc=0;

	double cR,cG,cB;

	//CvScalar s;

	for (i=0;i<GlFt.clusters_k;i++)
	{
 		cR=cvmGet(GlFt.CentersB_k,i,0);
 		cG=cvmGet(GlFt.CentersB_k,i,1);
 		cB=cvmGet(GlFt.CentersB_k,i,2);

// 		s=cvGet2D(GlFt.CentersF_k,i,0);
// 
// 		cR=s.val[2];
// 		cG=s.val[1];
// 		cB=s.val[0];

		dc=sqrt((R-cR)*(R-cR)+(G-cG)*(G-cG)+(B-cB)*(B-cB));

		if (dc<dp)
		{
			dp=dc;
		}
	}

	(*dstc)=dp;
}
void CGraphCutDlg::get_distance_adj(double aR,double aG,double aB,double bR,double bG,double bB,double *DstcAj)
{
	double d;

	d=((aR-bR)*(aR-bR)+(aG-bG)*(aG-bG)+(aB-bB)*(aB-bB));//sqrt

	(*DstcAj)=1/(1+d);

}
void CGraphCutDlg:: get_Adj(int i,int *num,int*adj)
{
	int w=TheImage->width;
	int h=TheImage->height;

	int row=i/w;
	int col=i%w;

	if (col==0&&row!=h-1)
	{
		*num=3;

		adj[0]=i+1;
		adj[1]=i+1+w;
		adj[2]=i+w;
		adj[3]=-1;
	}
	else
	{
		if (row==h-1&&col!=w-1)
		{
			*num=1;

			adj[0]=i+1;
		}
		else
		{
			if (row=h-1&&col==w-1)
			{
				*num=0;
			}
			else
			{
				if (col==w-1)
				{
					*num=2;

					adj[0]=i+w;
					adj[1]=i+w-1;
				}
				else
				{
					*num=4;

					adj[0]=i+1;
					adj[1]=i+1+w;
					adj[2]=i+w;
					adj[3]=i+w-1;
				}
			}
		}

	}


}
void CGraphCutDlg::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	OnOK();

	if (TheImage)
	{
		cvReleaseImage(&TheImage);
	}

	cvDestroyAllWindows();

	exit(0);
}
void CGraphCutDlg::reset_dg()
{
	if (TheImage)
	{
		cvReleaseImage(&TheImage);
	}
    
	if (img_stroked)
	{
		cvReleaseImage(&img_stroked);
	}

	GlFt.reset_glft();

	cvDestroyAllWindows();

}