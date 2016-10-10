// DialogResult.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "MouseOptometry.h"
#include "DialogResult.h"
#include "afxdialogex.h"
#include "OptometryDlg.h"

#define d_pParent ((COptometryDlg*)AfxGetMainWnd())

// CDialogResult ��ȭ �����Դϴ�.

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


// CDialogResult �޽��� ó�����Դϴ�.


BOOL CDialogResult::PreTranslateMessage(MSG* pMsg)
{
	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.
	if (pMsg->wParam == VK_RETURN || pMsg->wParam == VK_ESCAPE)
		return TRUE;

	return CDialogEx::PreTranslateMessage(pMsg);
}


void CDialogResult::OnBnClickedButtonClear()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	m_ctrResult.SetWindowText(_T(""));
}
