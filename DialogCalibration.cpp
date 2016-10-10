// DialogCalibration.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "MouseOptometry.h"
#include "DialogCalibration.h"
#include "afxdialogex.h"
#include "OptometryDlg.h"

#define d_pParent ((COptometryDlg*)AfxGetMainWnd())
#define VALUE_MONITOR_SIZE 0
#define VALUE_MONITOR_POSITION 1

// CDialogCalibration ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(CDialogCalibration, CDialogEx)

CDialogCalibration::CDialogCalibration(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_TAB_CALIBRATION, pParent)
{
}

CDialogCalibration::~CDialogCalibration()
{
}

void CDialogCalibration::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SLIDER_MONITOR_SIZE, m_ctrMonitorSize);
	DDX_Control(pDX, IDC_SLIDER_MONITOR_POSITION, m_ctrMonitorPosition);
}


BEGIN_MESSAGE_MAP(CDialogCalibration, CDialogEx)
	ON_WM_HSCROLL()
END_MESSAGE_MAP()


// CDialogCalibration �޽��� ó�����Դϴ�.


BOOL CDialogCalibration::PreTranslateMessage(MSG* pMsg)
{
	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.
	if (pMsg->wParam == VK_RETURN || pMsg->wParam == VK_ESCAPE)
		return TRUE;
	return CDialogEx::PreTranslateMessage(pMsg);
}

void CDialogCalibration::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	if (pScrollBar == (CScrollBar*)&m_ctrMonitorSize)
	{
		setValue(VALUE_MONITOR_SIZE, m_ctrMonitorSize.GetPos());
	}
	else if (pScrollBar == (CScrollBar*)&m_ctrMonitorPosition)
	{
		setValue(VALUE_MONITOR_POSITION, m_ctrMonitorPosition.GetPos());
	}
	CDialogEx::OnHScroll(nSBCode, nPos, pScrollBar);
}


BOOL CDialogCalibration::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.

	m_ctrMonitorSize.SetRange(1, 1000);
	m_ctrMonitorSize.SetPageSize(10);
	m_ctrMonitorSize.SetLineSize(1);
	m_ctrMonitorSize.SetTicFreq(100);

	m_ctrMonitorPosition.SetRange(1, 1000);
	m_ctrMonitorPosition.SetPageSize(10);
	m_ctrMonitorPosition.SetLineSize(1);
	m_ctrMonitorPosition.SetTicFreq(100);

	setValue(VALUE_MONITOR_SIZE, 410);
	m_ctrMonitorSize.SetPos(d_pParent->m_monitorSize*10.0);
	setValue(VALUE_MONITOR_POSITION, 235);
	m_ctrMonitorPosition.SetPos(d_pParent->m_monitorPosition*10.0);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
}


void CDialogCalibration::setValue(int enumValue, int sliderValue)
{
	CString value;
	switch (enumValue)
	{
	case VALUE_MONITOR_SIZE: 
		d_pParent->m_monitorSize = sliderValue/10.0;
		value.Format(_T("%.1f"), d_pParent->m_monitorSize);
		GetDlgItem(IDC_EDIT_MONITOR_SIZE)->SetWindowText(value);
		break;
	case VALUE_MONITOR_POSITION:
		d_pParent->m_monitorPosition = sliderValue / 10.0;
		value.Format(_T("%.1f"), d_pParent->m_monitorPosition);
		GetDlgItem(IDC_EDIT_MONITOR_POSITION)->SetWindowText(value);
		break;
	}
}
