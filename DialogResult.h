#pragma once
#include "afxwin.h"


// CDialogResult ��ȭ �����Դϴ�.

class CDialogResult : public CDialogEx
{
	DECLARE_DYNAMIC(CDialogResult)

public:
	CDialogResult(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CDialogResult();

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_TAB_RESULT };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	CEdit m_ctrResult;
	afx_msg void OnBnClickedButtonClear();
};
