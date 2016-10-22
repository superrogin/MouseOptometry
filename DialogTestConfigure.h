#pragma once
#include "afxwin.h"
#include "afxcmn.h"

#define d_pParent ((COptometryDlg*)AfxGetMainWnd())

// CDialogTestConfigure ��ȭ �����Դϴ�.

class CDialogTestConfigure : public CDialogEx
{
	DECLARE_DYNAMIC(CDialogTestConfigure)

public:
	CDialogTestConfigure(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CDialogTestConfigure();

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_TEST_CONFIGURATION };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	CComboBox m_ctrCmbTotalPreset;
	CComboBox m_ctrCmbSpatialFrequency;
	CComboBox m_ctrCmbContrast;
	CComboBox m_ctrCmbDriftSpeed;
	CSliderCtrl m_ctrSpatialFrequency;
	CSliderCtrl m_ctrContrast;
	CSliderCtrl m_ctrDriftSpeed;
	virtual BOOL OnInitDialog();
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	void setValue(int enumValue, int sliderValue);
	afx_msg void OnCbnSelchangeComboSpatialFrequency();
	afx_msg void OnCbnSelchangeComboContrast();
	afx_msg void OnCbnSelchangeComboDriftSpeed();
};
