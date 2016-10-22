#pragma once
#include <opencv.hpp>

#define M_PI 3.14159265358979323846

using namespace std;
using namespace cv;


// CCameraDialog 대화 상자입니다.

class CCameraDialog : public CDialogEx
{
	DECLARE_DYNAMIC(CCameraDialog)

public:
	CCameraDialog(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CCameraDialog();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_CAMERA };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	void displayImage(Mat* image, CDC* pDC);
	void openCamera();
	double m_headingAngle;
	int m_headX;
	int m_headY;
	VideoCapture m_capture;
	string m_strPath;
	void openVideoFile();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	virtual void OnCancel();
	void setCameraFPS(int frameRateMode);
	virtual BOOL OnInitDialog();
	bool m_viewCalibration;
	double m_zoom;
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	bool m_isVideo;
	Point2f m_prevMc;
	Point2f m_prevPntNose;
	bool m_isExperimentStarted;
};
