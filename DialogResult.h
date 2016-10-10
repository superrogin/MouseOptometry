#pragma once
#include "afxwin.h"


// CDialogResult 대화 상자입니다.

class CDialogResult : public CDialogEx
{
	DECLARE_DYNAMIC(CDialogResult)

public:
	CDialogResult(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CDialogResult();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_TAB_RESULT };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	CEdit m_ctrResult;
	afx_msg void OnBnClickedButtonClear();
};
