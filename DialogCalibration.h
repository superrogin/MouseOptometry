#pragma once
#include "afxcmn.h"


// CDialogCalibration ��ȭ �����Դϴ�.

class CDialogCalibration : public CDialogEx
{
	DECLARE_DYNAMIC(CDialogCalibration)

public:
	CDialogCalibration(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CDialogCalibration();

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_TAB_CALIBRATION };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	virtual BOOL OnInitDialog();
	void setValue(int enumValue, int sliderValue);
	CSliderCtrl m_ctrMonitorSize;
	CSliderCtrl m_ctrMonitorPosition;
};
