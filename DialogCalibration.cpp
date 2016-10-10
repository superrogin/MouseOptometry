// DialogCalibration.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "MouseOptometry.h"
#include "DialogCalibration.h"
#include "afxdialogex.h"
#include "OptometryDlg.h"

#define d_pParent ((COptometryDlg*)AfxGetMainWnd())
#define VALUE_MONITOR_SIZE 0
#define VALUE_MONITOR_POSITION 1

// CDialogCalibration 대화 상자입니다.

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


// CDialogCalibration 메시지 처리기입니다.


BOOL CDialogCalibration::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	if (pMsg->wParam == VK_RETURN || pMsg->wParam == VK_ESCAPE)
		return TRUE;
	return CDialogEx::PreTranslateMessage(pMsg);
}

void CDialogCalibration::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
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

	// TODO:  여기에 추가 초기화 작업을 추가합니다.

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
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
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
