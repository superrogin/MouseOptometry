#pragma once
#include "afxcmn.h"
#include "afxwin.h"
#include "afxcolorbutton.h"


// CDialogStimulus 대화 상자입니다.

class CDialogStimulus : public CDialogEx
{
	DECLARE_DYNAMIC(CDialogStimulus)

public:
	CDialogStimulus(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CDialogStimulus();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_TAB_STIMULUS };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CSliderCtrl m_ctrSpatialFrequency;
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	int m_spatialFrequency;
	int m_contrast;
	int m_driftSpeed;
	CSliderCtrl m_ctrContrast;
	CSliderCtrl m_ctrDriftSpeed;
	int m_temporalFrequency;
	void setValue(int enumValue, int sliderValue);
	CComboBox m_ctrCmbSpatFreq;
	CComboBox m_ctrCmbContrast;
	CComboBox m_ctrCmbDriftSpeed;
	afx_msg void OnCbnSelchangeComboSpatialFrequency();
	afx_msg void OnCbnSelchangeComboContrast();
	afx_msg void OnCbnSelchangeComboDriftSpeed();
	CSliderCtrl m_ctrTransparency;
	int m_transparency;
	CMFCColorButton m_ctrMarkerColor;
	afx_msg void OnBnClickedMarkerColor();
	COLORREF m_markerColor;
	afx_msg void OnCbnSelchangeComboNumberMode();
	CComboBox m_ctrCmbNumberMode;
	CSliderCtrl m_ctrMarkerRadius;
	CSliderCtrl m_ctrMarkerQuality;
	CSliderCtrl m_ctrNumberMode;
	int m_numberMode;
	int m_markerRadius;
	int m_markerQuality;
};
