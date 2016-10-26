#pragma once
#include "afxwin.h"
#include "DialogTestConfigure.h"


// CDialogTesting 대화 상자입니다.

class CDialogTesting : public CDialogEx
{
	DECLARE_DYNAMIC(CDialogTesting)

public:
	CDialogTesting(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CDialogTesting();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_TAB_TESTING };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	CComboBox m_ctrCmbModeSelect;
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButtonBrowse();
	CButton m_ctrAutoGenerate;
	CButton m_ctrAutoIndex;
	CButton m_ctrDate;
	CButton m_ctrTime;
	CEdit m_ctrSaveFileName;
	CEdit m_ctrBaseFileName;
	afx_msg void OnBnClickedCheckAutoGenerate();
	afx_msg void OnBnClickedCheckAutoIndex();
	afx_msg void OnBnClickedCheckDate();
	afx_msg void OnBnClickedCheckTime();
	void makeFileName();
	afx_msg void OnEnChangeEditBaseName();
	afx_msg void OnBnClickedButtonStart();
	CComboBox m_ctrCmbTestingEyes;
	CComboBox m_ctrCmbSearchingAlgorithms;
	afx_msg void OnBnClickedButtonConfiguration();
	int m_startSpatialFrequency;
	int m_startContrast;
	int m_startDriftSpeed;
	afx_msg void OnBnClickedButtonYes();
	afx_msg void OnBnClickedButtonNo();
	afx_msg void OnBnClickedButtonReset();
	afx_msg void OnBnClickedButtonDone();
	CButton m_ctrYes;
	CButton m_ctrNo;
	CButton m_ctrReset;
	CButton m_ctrDone;
	CButton m_ctrExperimentStart;
	CButton m_ctrTracking;
};
