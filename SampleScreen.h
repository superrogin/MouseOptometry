#pragma once
#include "afxwin.h"
#include "afxcmn.h"


// CSampleScreen ��ȭ �����Դϴ�.

class CSampleScreen : public CDialogEx
{
	DECLARE_DYNAMIC(CSampleScreen)

public:
	CSampleScreen(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CSampleScreen();

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_SAMPLE };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

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
