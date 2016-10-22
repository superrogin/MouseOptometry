// DialogTestConfigure.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "MouseOptometry.h"
#include "DialogTestConfigure.h"
#include "afxdialogex.h"
#include "OptometryDlg.h"

#define VALUE_SPATIAL_FREQEUNCY 0
#define VALUE_CONTRAST 1
#define VALUE_DRIFT_SPEED 2

// CDialogTestConfigure 대화 상자입니다.

IMPLEMENT_DYNAMIC(CDialogTestConfigure, CDialogEx)

CDialogTestConfigure::CDialogTestConfigure(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG_TEST_CONFIGURATION, pParent)
{

}

CDialogTestConfigure::~CDialogTestConfigure()
{
}

void CDialogTestConfigure::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_TOTAL_PRESET, m_ctrCmbTotalPreset);
	DDX_Control(pDX, IDC_COMBO_SPATIAL_FREQUENCY, m_ctrCmbSpatialFrequency);
	DDX_Control(pDX, IDC_COMBO_CONTRAST, m_ctrCmbContrast);
	DDX_Control(pDX, IDC_COMBO_DRIFT_SPEED, m_ctrCmbDriftSpeed);
	DDX_Control(pDX, IDC_SLIDER_SPATIAL_FREQUENCY, m_ctrSpatialFrequency);
	DDX_Control(pDX, IDC_SLIDER_CONTRAST, m_ctrContrast);
	DDX_Control(pDX, IDC_SLIDER_DRIFT_SPEED, m_ctrDriftSpeed);
}


BEGIN_MESSAGE_MAP(CDialogTestConfigure, CDialogEx)
	ON_WM_HSCROLL()
	ON_CBN_SELCHANGE(IDC_COMBO_SPATIAL_FREQUENCY, &CDialogTestConfigure::OnCbnSelchangeComboSpatialFrequency)
	ON_CBN_SELCHANGE(IDC_COMBO_CONTRAST, &CDialogTestConfigure::OnCbnSelchangeComboContrast)
	ON_CBN_SELCHANGE(IDC_COMBO_DRIFT_SPEED, &CDialogTestConfigure::OnCbnSelchangeComboDriftSpeed)
END_MESSAGE_MAP()


// CDialogTestConfigure 메시지 처리기입니다.


BOOL CDialogTestConfigure::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.

	m_ctrSpatialFrequency.SetRange(1, 270);
	m_ctrSpatialFrequency.SetPageSize(10);
	m_ctrSpatialFrequency.SetLineSize(1);
	m_ctrSpatialFrequency.SetTicFreq(30);

	m_ctrContrast.SetRange(1, 1000);
	m_ctrContrast.SetPageSize(100);
	m_ctrContrast.SetLineSize(1);
	m_ctrContrast.SetTicFreq(100);

	m_ctrDriftSpeed.SetRange(1, 500);
	m_ctrDriftSpeed.SetPageSize(50);
	m_ctrDriftSpeed.SetLineSize(1);
	m_ctrDriftSpeed.SetTicFreq(50);


	m_ctrCmbSpatialFrequency.AddString(L"0.042 c/d"); // 15
	m_ctrCmbSpatialFrequency.AddString(L"0.058 c/d"); // 21
	m_ctrCmbSpatialFrequency.AddString(L"0.083 c/d"); // 30
	m_ctrCmbSpatialFrequency.AddString(L"0.119 c/d"); // 43
	m_ctrCmbSpatialFrequency.AddString(L"0.172 c/d"); // 62
	m_ctrCmbSpatialFrequency.AddString(L"0.244 c/d"); // 88
	m_ctrCmbSpatialFrequency.AddString(L"0.347 c/d"); // 125

	m_ctrCmbContrast.AddString(L"100%");
	m_ctrCmbContrast.AddString(L" 80%");
	m_ctrCmbContrast.AddString(L" 60%");
	m_ctrCmbContrast.AddString(L" 40%");
	m_ctrCmbContrast.AddString(L" 20%");
	m_ctrCmbContrast.AddString(L"  0%");

	m_ctrCmbDriftSpeed.AddString(L" 6d/s");
	m_ctrCmbDriftSpeed.AddString(L"12d/s");
	m_ctrCmbDriftSpeed.AddString(L"18d/s");
	m_ctrCmbDriftSpeed.AddString(L"24d/s");
	m_ctrCmbDriftSpeed.AddString(L"30d/s");
	m_ctrCmbDriftSpeed.AddString(L"36d/s");

	m_ctrCmbTotalPreset.AddString(L"Preset #1");
	m_ctrCmbTotalPreset.AddString(L"Preset #2");
	m_ctrCmbTotalPreset.AddString(L"Preset #3");
	m_ctrCmbTotalPreset.AddString(L"Preset #4");
	m_ctrCmbTotalPreset.AddString(L"Preset #5");
	m_ctrCmbTotalPreset.AddString(L"Preset #6");
	m_ctrCmbTotalPreset.AddString(L"Preset #7");
	m_ctrCmbTotalPreset.AddString(L"Preset #8");
	m_ctrCmbTotalPreset.AddString(L"Preset #9");
	m_ctrCmbTotalPreset.AddString(L"Preset #10");

	setValue(VALUE_SPATIAL_FREQEUNCY, 15);
	m_ctrSpatialFrequency.SetPos(d_pParent->m_tab3_testing.m_startSpatialFrequency);
	setValue(VALUE_CONTRAST, 1000);
	m_ctrContrast.SetPos(d_pParent->m_tab3_testing.m_startContrast);
	setValue(VALUE_DRIFT_SPEED, 120);
	m_ctrDriftSpeed.SetPos(d_pParent->m_tab3_testing.m_startDriftSpeed);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


void CDialogTestConfigure::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	if (pScrollBar == (CScrollBar*)&m_ctrSpatialFrequency)
	{
		setValue(VALUE_SPATIAL_FREQEUNCY, m_ctrSpatialFrequency.GetPos());
	}
	else if (pScrollBar == (CScrollBar*)&m_ctrContrast)
	{
		setValue(VALUE_CONTRAST, m_ctrContrast.GetPos());
	}
	else if (pScrollBar == (CScrollBar*)&m_ctrDriftSpeed)
	{
		setValue(VALUE_DRIFT_SPEED, m_ctrDriftSpeed.GetPos());
	}

	CDialogEx::OnHScroll(nSBCode, nPos, pScrollBar);
}


void CDialogTestConfigure::setValue(int enumValue, int sliderValue)
{
	CString value;
	switch (enumValue)
	{
	case VALUE_SPATIAL_FREQEUNCY:
		d_pParent->m_tab3_testing.m_startSpatialFrequency = sliderValue;
		value.Format(_T("%.3f"), d_pParent->m_tab3_testing.m_startSpatialFrequency / 360.0);
		GetDlgItem(IDC_EDIT_SPATIAL_FREQUENCY)->SetWindowText(value);
		break;
	case VALUE_CONTRAST:
		d_pParent->m_tab3_testing.m_startContrast = sliderValue;
		value.Format(_T("%.1f"), d_pParent->m_tab3_testing.m_startSpatialFrequency / 10.0);
		GetDlgItem(IDC_EDIT_CONTRAST)->SetWindowText(value);
		break;
	case VALUE_DRIFT_SPEED:
		d_pParent->m_tab3_testing.m_startDriftSpeed = sliderValue;
		value.Format(_T("%.1f"), d_pParent->m_tab3_testing.m_startSpatialFrequency / 10.0);
		GetDlgItem(IDC_EDIT_DRIFT_SPEED)->SetWindowText(value);
		break;
	}
	if (enumValue != 1)
	{
		int temporalFrequency = d_pParent->m_tab3_testing.m_startSpatialFrequency*d_pParent->m_tab3_testing.m_startDriftSpeed;
		value.Format(_T("Temporal Frequency %4.2fHz"), temporalFrequency / 3600.0);
		GetDlgItem(IDC_STATIC_TEMPORAL_FREQUENCY)->SetWindowText(value);
	}
}


void CDialogTestConfigure::OnCbnSelchangeComboSpatialFrequency()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	int spatialFrequency = d_pParent->m_tab3_testing.m_startSpatialFrequency;

	switch (m_ctrCmbSpatialFrequency.GetCurSel()) {
	case 0:
		setValue(VALUE_SPATIAL_FREQEUNCY, 15);
		m_ctrSpatialFrequency.SetPos(spatialFrequency);
		break;
	case 1:
		setValue(VALUE_SPATIAL_FREQEUNCY, 21);
		m_ctrSpatialFrequency.SetPos(spatialFrequency);
		break;
	case 2:
		setValue(VALUE_SPATIAL_FREQEUNCY, 30);
		m_ctrSpatialFrequency.SetPos(spatialFrequency);
		break;
	case 3:
		setValue(VALUE_SPATIAL_FREQEUNCY, 43);
		m_ctrSpatialFrequency.SetPos(spatialFrequency);
		break;
	case 4:
		setValue(VALUE_SPATIAL_FREQEUNCY, 62);
		m_ctrSpatialFrequency.SetPos(spatialFrequency);
		break;
	case 5:
		setValue(VALUE_SPATIAL_FREQEUNCY, 88);
		m_ctrSpatialFrequency.SetPos(spatialFrequency);
		break;
	case 6:
		setValue(VALUE_SPATIAL_FREQEUNCY, 125);
		m_ctrSpatialFrequency.SetPos(spatialFrequency);
		break;
	}
}


void CDialogTestConfigure::OnCbnSelchangeComboContrast()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	int contrast = d_pParent->m_tab3_testing.m_startContrast;
	switch (m_ctrCmbContrast.GetCurSel()) {
	case 0:
		setValue(VALUE_CONTRAST, 1000);
		m_ctrContrast.SetPos(contrast);
		break;
	case 1:
		setValue(VALUE_CONTRAST, 800);
		m_ctrContrast.SetPos(contrast);
		break;
	case 2:
		setValue(VALUE_CONTRAST, 600);
		m_ctrContrast.SetPos(contrast);
		break;
	case 3:
		setValue(VALUE_CONTRAST, 400);
		m_ctrContrast.SetPos(contrast);
		break;
	case 4:
		setValue(VALUE_CONTRAST, 200);
		m_ctrContrast.SetPos(contrast);
		break;
	case 5:
		setValue(VALUE_CONTRAST, 0);
		m_ctrContrast.SetPos(contrast);
		break;
	}
}


void CDialogTestConfigure::OnCbnSelchangeComboDriftSpeed()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	int driftSpeed = d_pParent->m_tab3_testing.m_startDriftSpeed;
	switch (m_ctrCmbDriftSpeed.GetCurSel()) {
	case 0:
		setValue(VALUE_DRIFT_SPEED, 60);
		m_ctrDriftSpeed.SetPos(driftSpeed);
		break;
	case 1:
		setValue(VALUE_DRIFT_SPEED, 120);
		m_ctrDriftSpeed.SetPos(driftSpeed);
		break;
	case 2:
		setValue(VALUE_DRIFT_SPEED, 180);
		m_ctrDriftSpeed.SetPos(driftSpeed);
		break;
	case 3:
		setValue(VALUE_DRIFT_SPEED, 240);
		m_ctrDriftSpeed.SetPos(driftSpeed);
		break;
	case 4:
		setValue(VALUE_DRIFT_SPEED, 300);
		m_ctrDriftSpeed.SetPos(driftSpeed);
		break;
	case 5:
		setValue(VALUE_DRIFT_SPEED, 360);
		m_ctrDriftSpeed.SetPos(driftSpeed);
		break;
	}
}
