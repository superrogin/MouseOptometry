#pragma once
#include "afxcmn.h"
#include "afxwin.h"


// CDialogCamera 대화 상자입니다.

class CDialogCamera : public CDialogEx
{
	DECLARE_DYNAMIC(CDialogCamera)

public:
	CDialogCamera(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CDialogCamera();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_TAB_CAMERA };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	CSliderCtrl m_ctrMagnification;
	CSplitButton m_ctrFrameRate;
	virtual BOOL OnInitDialog();
	void setValue(int enumValue, int sliderValue);
	int m_magnification;
	int m_frameRate;
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnFrMax();
	afx_msg void OnFr2();
	afx_msg void OnFr3();
	afx_msg void OnFr4();
	afx_msg void OnFr5();
	afx_msg void OnFr6();
	afx_msg void OnBnClickedButtonCameraOpen();
	afx_msg void OnBnClickedSplitFrameRate();
	CSliderCtrl m_ctrFootholdDiameter;
	CSliderCtrl m_ctrVirtualDiameter;
	CSliderCtrl m_ctrCenterX;
	CSliderCtrl m_ctrCenterY;
};
