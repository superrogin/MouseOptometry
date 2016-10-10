// DialogCamera.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "MouseOptometry.h"
#include "DialogCamera.h"
#include "afxdialogex.h"
#include "OptometryDlg.h"

#define VALUE_MAGNIFICATION 0
#define VALUE_FRAME_RATE 1
#define VALUE_FOOTHOLD_DIAMETER 2
#define VALUE_VIRTUAL_DIAMETER 3
#define VALUE_CENTER_X 4
#define VALUE_CENTER_Y 5
#define d_pParent ((COptometryDlg*)AfxGetMainWnd())

// CDialogCamera ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(CDialogCamera, CDialogEx)

CDialogCamera::CDialogCamera(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_TAB_CAMERA, pParent)
{
	m_magnification = 0;
	m_frameRate = 0;
}

CDialogCamera::~CDialogCamera()
{
}

void CDialogCamera::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SLIDER_MAGNIFICATION, m_ctrMagnification);
	DDX_Control(pDX, IDC_SPLIT_FRAME_RATE, m_ctrFrameRate);
	DDX_Control(pDX, IDC_SLIDER_FOOTHOLD_DIAMETER, m_ctrFootholdDiameter);
	DDX_Control(pDX, IDC_SLIDER_VIRTUAL_DIAMETER, m_ctrVirtualDiameter);
	DDX_Control(pDX, IDC_SLIDER_CENTER_X, m_ctrCenterX);
	DDX_Control(pDX, IDC_SLIDER_CENTER_Y, m_ctrCenterY);
}


BEGIN_MESSAGE_MAP(CDialogCamera, CDialogEx)
	ON_WM_HSCROLL()
	ON_COMMAND(ID_FR_MAX, &CDialogCamera::OnFrMax)
	ON_COMMAND(ID_FR_2, &CDialogCamera::OnFr2)
	ON_COMMAND(ID_FR_3, &CDialogCamera::OnFr3)
	ON_COMMAND(ID_FR_4, &CDialogCamera::OnFr4)
	ON_COMMAND(ID_FR_5, &CDialogCamera::OnFr5)
	ON_COMMAND(ID_FR_6, &CDialogCamera::OnFr6)
	ON_BN_CLICKED(IDC_BUTTON_CAMERA_OPEN, &CDialogCamera::OnBnClickedButtonCameraOpen)
	ON_BN_CLICKED(IDC_SPLIT_FRAME_RATE, &CDialogCamera::OnBnClickedSplitFrameRate)
END_MESSAGE_MAP()

BOOL CDialogCamera::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
	m_ctrMagnification.SetRange(100, 500);
	m_ctrMagnification.SetPageSize(50);
	m_ctrMagnification.SetLineSize(1);
	m_ctrMagnification.SetTicFreq(50);

	m_ctrFootholdDiameter.SetRange(1, 200);
	m_ctrFootholdDiameter.SetPageSize(10);
	m_ctrFootholdDiameter.SetLineSize(1);
	m_ctrFootholdDiameter.SetTicFreq(10);

	m_ctrVirtualDiameter.SetRange(1, 1000);
	m_ctrVirtualDiameter.SetPageSize(100);
	m_ctrVirtualDiameter.SetLineSize(1);
	m_ctrVirtualDiameter.SetTicFreq(100);

	m_ctrCenterX.SetRange(0, 2000);
	m_ctrCenterX.SetPageSize(100);
	m_ctrCenterX.SetLineSize(1);
	m_ctrCenterX.SetTicFreq(100);

	m_ctrCenterY.SetRange(0, 2000);
	m_ctrCenterY.SetPageSize(100);
	m_ctrCenterY.SetLineSize(1);
	m_ctrCenterY.SetTicFreq(100);

	m_ctrFrameRate.SetDropDownMenu(IDR_MENU_FRAME_RATE, 0);

	setValue(VALUE_MAGNIFICATION, 100);
	m_frameRate = 1;
	setValue(VALUE_FOOTHOLD_DIAMETER, 50);
	m_ctrFootholdDiameter.SetPos(d_pParent->m_footholdDiameter * 10);
	setValue(VALUE_VIRTUAL_DIAMETER, 200);
	m_ctrVirtualDiameter.SetPos(d_pParent->m_calDiameter);
	setValue(VALUE_CENTER_X, 1000);
	m_ctrCenterX.SetPos(d_pParent->m_calX);
	setValue(VALUE_CENTER_Y, 1000);
	m_ctrCenterY.SetPos(d_pParent->m_calY);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
}


void CDialogCamera::setValue(int enumValue, int sliderValue)
{
	CString value;
	switch (enumValue)
	{
	case VALUE_MAGNIFICATION:
		m_magnification = sliderValue;
		value.Format(_T("%d"), m_magnification);
		GetDlgItem(IDC_EDIT_MAGNIFICATION)->SetWindowText(value);
		((COptometryDlg*)AfxGetMainWnd())->m_dlgCamera.m_zoom = m_magnification / 100.0;
		break;
	case VALUE_FRAME_RATE:
		m_frameRate = sliderValue;
		break;
	case VALUE_FOOTHOLD_DIAMETER:
		d_pParent->m_footholdDiameter = sliderValue / 10.0;
		value.Format(_T("%.1f"), d_pParent->m_footholdDiameter);
		GetDlgItem(IDC_EDIT_FOOTHOLD_DIAMETER)->SetWindowText(value);
		break;
	case VALUE_VIRTUAL_DIAMETER:
		d_pParent->m_calDiameter = sliderValue;
		value.Format(_T("%.1f"), d_pParent->m_calDiameter / 10.0);
		GetDlgItem(IDC_EDIT_VIRTUAL_DIAMETER)->SetWindowText(value);
		break;
	case VALUE_CENTER_X:
		d_pParent->m_calX = sliderValue;
		value.Format(_T("%.1f"), (d_pParent->m_calX - 1000.0) / 10.0);
		GetDlgItem(IDC_EDIT_CENTER_X)->SetWindowText(value);
		break;
	case VALUE_CENTER_Y:
		d_pParent->m_calY = sliderValue;
		value.Format(_T("%.1f"), (d_pParent->m_calY - 1000.0) / 10.0);
		GetDlgItem(IDC_EDIT_CENTER_Y)->SetWindowText(value);
		break;
	}
}


void CDialogCamera::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	if (pScrollBar == (CScrollBar*)&m_ctrMagnification)
	{
		if (d_pParent->m_dlgCamera.GetSafeHwnd() != NULL)
			setValue(VALUE_MAGNIFICATION, m_ctrMagnification.GetPos());
		else {
			m_ctrMagnification.SetPos(100);
			AfxMessageBox(L"Please open camera first");
		}
	}
	else if (pScrollBar == (CScrollBar*)&m_ctrFootholdDiameter)
	{
		setValue(VALUE_FOOTHOLD_DIAMETER, m_ctrFootholdDiameter.GetPos());
	}
	else if (pScrollBar == (CScrollBar*)&m_ctrVirtualDiameter)
	{
		setValue(VALUE_VIRTUAL_DIAMETER, m_ctrVirtualDiameter.GetPos());
	}
	else if (pScrollBar == (CScrollBar*)&m_ctrCenterX)
	{
		setValue(VALUE_CENTER_X, m_ctrCenterX.GetPos());
	}
	else if (pScrollBar == (CScrollBar*)&m_ctrCenterY)
	{
		setValue(VALUE_CENTER_Y, m_ctrCenterY.GetPos());
	}
	CDialogEx::OnHScroll(nSBCode, nPos, pScrollBar);
}

void CDialogCamera::OnFrMax()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	if (d_pParent->m_dlgCamera.GetSafeHwnd() != NULL)
	{
		m_ctrFrameRate.SetWindowText(_T("30"));
		m_frameRate = 1;
		d_pParent->m_dlgCamera.setCameraFPS(m_frameRate);
	}
	else  AfxMessageBox(L"Please open camera first");
}


void CDialogCamera::OnFr2()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	if (d_pParent->m_dlgCamera.GetSafeHwnd() != NULL)
	{
		m_ctrFrameRate.SetWindowText(_T("15"));
		m_frameRate = 2;
		((COptometryDlg*)AfxGetMainWnd())->m_dlgCamera.setCameraFPS(m_frameRate);
	}
	else  AfxMessageBox(L"Please open camera first");
}

void CDialogCamera::OnFr3()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	if (d_pParent->m_dlgCamera.GetSafeHwnd() != NULL)
	{
		m_ctrFrameRate.SetWindowText(_T("10"));
		m_frameRate = 3;
		((COptometryDlg*)AfxGetMainWnd())->m_dlgCamera.setCameraFPS(m_frameRate);
	}
	else  AfxMessageBox(L"Please open camera first");
}

void CDialogCamera::OnFr4()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	if (d_pParent->m_dlgCamera.GetSafeHwnd() != NULL)
	{
		m_ctrFrameRate.SetWindowText(_T("7.5"));
		m_frameRate = 4;
		((COptometryDlg*)AfxGetMainWnd())->m_dlgCamera.setCameraFPS(m_frameRate);
	}
	else  AfxMessageBox(L"Please open camera first");
}

void CDialogCamera::OnFr5()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	if (d_pParent->m_dlgCamera.GetSafeHwnd() != NULL)
	{
		m_ctrFrameRate.SetWindowText(_T("6"));
		m_frameRate = 5;
		((COptometryDlg*)AfxGetMainWnd())->m_dlgCamera.setCameraFPS(m_frameRate);
	}
	else  AfxMessageBox(L"Please open camera first");
}

void CDialogCamera::OnFr6()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	if (d_pParent->m_dlgCamera.GetSafeHwnd() != NULL)
	{
		m_ctrFrameRate.SetWindowText(_T("5"));
		m_frameRate = 6;
		((COptometryDlg*)AfxGetMainWnd())->m_dlgCamera.setCameraFPS(m_frameRate);
	}
	else  AfxMessageBox(L"Please open camera first");
}


void CDialogCamera::OnBnClickedButtonCameraOpen()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	((COptometryDlg*)AfxGetMainWnd())->OnFileOpencamera();
}


void CDialogCamera::OnBnClickedSplitFrameRate()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	if (d_pParent->m_dlgCamera.GetSafeHwnd() == NULL) AfxMessageBox(L"Please open camera first");
}
