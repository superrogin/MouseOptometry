// DialogResult.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "MouseOptometry.h"
#include "DialogResult.h"
#include "afxdialogex.h"
#include "OptometryDlg.h"

#define d_pParent ((COptometryDlg*)AfxGetMainWnd())

// CDialogResult 대화 상자입니다.

IMPLEMENT_DYNAMIC(CDialogResult, CDialogEx)

CDialogResult::CDialogResult(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_TAB_RESULT, pParent)
{
}

CDialogResult::~CDialogResult()
{
}

void CDialogResult::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, m_ctrResult);
}


BEGIN_MESSAGE_MAP(CDialogResult, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_CLEAR, &CDialogResult::OnBnClickedButtonClear)
END_MESSAGE_MAP()


// CDialogResult 메시지 처리기입니다.


BOOL CDialogResult::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	if (pMsg->wParam == VK_RETURN || pMsg->wParam == VK_ESCAPE)
		return TRUE;

	return CDialogEx::PreTranslateMessage(pMsg);
}


void CDialogResult::OnBnClickedButtonClear()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	m_ctrResult.SetWindowText(_T(""));
}
