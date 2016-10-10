#pragma once
#include "afxcmn.h"


// CDialogCalibration 대화 상자입니다.

class CDialogCalibration : public CDialogEx
{
	DECLARE_DYNAMIC(CDialogCalibration)

public:
	CDialogCalibration(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CDialogCalibration();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_TAB_CALIBRATION };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	virtual BOOL OnInitDialog();
	void setValue(int enumValue, int sliderValue);
	CSliderCtrl m_ctrMonitorSize;
	CSliderCtrl m_ctrMonitorPosition;
};
