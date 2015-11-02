// Graph CutDlg.h : header file
//

#pragma once
#include "atltypes.h"
#include "opencv.h"



// CGraphCutDlg dialog
class CGraphCutDlg : public CDialog
{
// Construction
public:
	CGraphCutDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_GRAPHCUT_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	IplImage* TheImage;
	afx_msg void OnBnClickedInputimage();
	void ShowImage(IplImage*img);//,UINT ID);
	void ResizeImage(IplImage*img);
	CPoint RefPoint;
	CPoint EndPoint;
	CRect Range;
	int ClickTimes;
	//virtual BOOL PreTranslateMessage(MSG* pMsg);
	
	afx_msg void OnBnClickedBackground();
	afx_msg void OnBnClickedForground();
	//int key;
	IplImage* img_stroked;

	afx_msg void OnBnClickedGraphcut();

	void cut();
	void get_distance_F(double R,double G,double B,double *dstc);
	void get_distance_B(double R,double G,double B,double* dstc);
    void get_distance_adj(double aR,double aG,double aB,double bR,double bG,double bB,double *DstcAj);
	void get_Adj(int i,int *num,int*adj);

	char key;
	afx_msg void OnBnClickedOk();

	void reset_dg();
};
