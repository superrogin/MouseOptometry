#pragma once
#include "afxwin.h"
#include "afxcmn.h"


// CSampleScreen 대화 상자입니다.

class CSampleScreen : public CDialogEx
{
	DECLARE_DYNAMIC(CSampleScreen)

public:
	CSampleScreen(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CSampleScreen();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_SAMPLE };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	int monNum;
	int screenWidth;
	int screenHeight;
	void bufferedDraw(double driftedTime, double centerX, double centerY, double spaFreq, double contrast, double monSize, double monPos);
	void drawSlit(RGBQUAD* pRgb, int i, double mx, double my, double driftedTime, int drawWidth, double spaFreq, double contrast);
	virtual BOOL OnInitDialog();
	virtual void OnCancel();
	CComboBox m_sampleComboBox;
	afx_msg void OnCbnSelchangeComboSampleScreen();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	CStatic m_drawSample;
	CSliderCtrl m_sliderQuality;
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
};
