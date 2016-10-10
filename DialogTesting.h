#pragma once
#include "afxwin.h"


// CDialogTesting ��ȭ �����Դϴ�.

class CDialogTesting : public CDialogEx
{
	DECLARE_DYNAMIC(CDialogTesting)

public:
	CDialogTesting(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CDialogTesting();

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_TAB_TESTING };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

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
};