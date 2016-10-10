#pragma once
#include "afxcmn.h"
#include "afxwin.h"


// CDialogCamera ��ȭ �����Դϴ�.

class CDialogCamera : public CDialogEx
{
	DECLARE_DYNAMIC(CDialogCamera)

public:
	CDialogCamera(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CDialogCamera();

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_TAB_CAMERA };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

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
