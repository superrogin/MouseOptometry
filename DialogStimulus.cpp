// DialogStimulus.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "MouseOptometry.h"
#include "DialogStimulus.h"
#include "afxdialogex.h"
#include "OptometryDlg.h"

#define VALUE_SPATIAL_FREQEUNCY 0
#define VALUE_CONTRAST 1
#define VALUE_DRIFT_SPEED 2
#define VALUE_TRANSPARENCY 3
#define VALUE_NUMBER_MODE 4
#define VALUE_MARKER_RADIUS 5
#define VALUE_MARKER_QUALITY 6

#define d_pParent ((COptometryDlg*)AfxGetMainWnd())

// CDialogStimulus 대화 상자입니다.

IMPLEMENT_DYNAMIC(CDialogStimulus, CDialogEx)

CDialogStimulus::CDialogStimulus(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_TAB_STIMULUS, pParent)
{
	m_spatialFrequency = 0;
	m_contrast = 0;
	m_driftSpeed = 0;
	m_temporalFrequency = 0;
	m_transparency = 0;
	m_numberMode = 0;
	m_markerRadius = 0;
	m_markerQuality = 0;
}

CDialogStimulus::~CDialogStimulus()
{
}

void CDialogStimulus::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SLIDER_SPATIAL_FREQUENCY, m_ctrSpatialFrequency);
	DDX_Control(pDX, IDC_SLIDER_CONTRAST, m_ctrContrast);
	DDX_Control(pDX, IDC_SLIDER_DRIFT_SPEED, m_ctrDriftSpeed);
	DDX_Control(pDX, IDC_COMBO_SPATIAL_FREQUENCY, m_ctrCmbSpatFreq);
	DDX_Control(pDX, IDC_COMBO_CONTRAST, m_ctrCmbContrast);
	DDX_Control(pDX, IDC_COMBO_DRIFT_SPEED, m_ctrCmbDriftSpeed);
	DDX_Control(pDX, IDC_SLIDER_TRANSPARENCY, m_ctrTransparency);
	DDX_Control(pDX, IDC_MARKER_COLOR, m_ctrMarkerColor);
	DDX_Control(pDX, IDC_COMBO_NUMBER_MODE, m_ctrCmbNumberMode);
	DDX_Control(pDX, IDC_SLIDER_MARKER_RADIUS, m_ctrMarkerRadius);
	DDX_Control(pDX, IDC_SLIDER_MARKER_QUALITY, m_ctrMarkerQuality);
	DDX_Control(pDX, IDC_SLIDER_MARKER_NUMBER, m_ctrNumberMode);
}


BEGIN_MESSAGE_MAP(CDialogStimulus, CDialogEx)
	ON_WM_VSCROLL()
	ON_WM_HSCROLL()
	ON_CBN_SELCHANGE(IDC_COMBO_SPATIAL_FREQUENCY, &CDialogStimulus::OnCbnSelchangeComboSpatialFrequency)
	ON_CBN_SELCHANGE(IDC_COMBO_CONTRAST, &CDialogStimulus::OnCbnSelchangeComboContrast)
	ON_CBN_SELCHANGE(IDC_COMBO_DRIFT_SPEED, &CDialogStimulus::OnCbnSelchangeComboDriftSpeed)
	ON_BN_CLICKED(IDC_MARKER_COLOR, &CDialogStimulus::OnBnClickedMarkerColor)
	ON_CBN_SELCHANGE(IDC_COMBO_NUMBER_MODE, &CDialogStimulus::OnCbnSelchangeComboNumberMode)
END_MESSAGE_MAP()


// CDialogStimulus 메시지 처리기입니다.


BOOL CDialogStimulus::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	// Slider 설정
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

	m_ctrTransparency.SetRange(1, 100);
	m_ctrTransparency.SetPageSize(10);
	m_ctrTransparency.SetLineSize(1);
	m_ctrTransparency.SetTicFreq(10);

	m_ctrNumberMode.SetRange(1, 30);
	m_ctrNumberMode.SetPageSize(5);
	m_ctrNumberMode.SetLineSize(1);
	m_ctrNumberMode.SetTicFreq(5);

	m_ctrMarkerRadius.SetRange(10, 1000);
	m_ctrMarkerRadius.SetPageSize(50);
	m_ctrMarkerRadius.SetLineSize(1);
	m_ctrMarkerRadius.SetTicFreq(50);

	m_ctrMarkerQuality.SetRange(1, 810);
	m_ctrMarkerQuality.SetPageSize(30);
	m_ctrMarkerQuality.SetLineSize(1);
	m_ctrMarkerQuality.SetTicFreq(90);

	// Slider 초기값 설정
	setValue(VALUE_SPATIAL_FREQEUNCY, 15);
	m_ctrSpatialFrequency.SetPos(m_spatialFrequency);
	setValue(VALUE_CONTRAST, 1000);
	m_ctrContrast.SetPos(m_contrast);
	setValue(VALUE_DRIFT_SPEED, 120);
	m_ctrDriftSpeed.SetPos(m_driftSpeed);
	setValue(VALUE_TRANSPARENCY, 50);
	m_ctrTransparency.SetPos(m_transparency);
	setValue(VALUE_NUMBER_MODE, 5);
	m_ctrNumberMode.SetPos(m_numberMode);
	setValue(VALUE_MARKER_RADIUS, 200);
	m_ctrMarkerRadius.SetPos(m_markerRadius);
	setValue(VALUE_MARKER_QUALITY, 150);
	m_ctrMarkerQuality.SetPos(m_markerQuality);


	m_ctrCmbSpatFreq.AddString(L"0.042 c/d"); // 15
	m_ctrCmbSpatFreq.AddString(L"0.058 c/d"); // 21
	m_ctrCmbSpatFreq.AddString(L"0.083 c/d"); // 30
	m_ctrCmbSpatFreq.AddString(L"0.119 c/d"); // 43
	m_ctrCmbSpatFreq.AddString(L"0.172 c/d"); // 62
	m_ctrCmbSpatFreq.AddString(L"0.244 c/d"); // 88
	m_ctrCmbSpatFreq.AddString(L"0.347 c/d"); // 125

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

	m_ctrCmbNumberMode.AddString(L"Auto");
	m_ctrCmbNumberMode.AddString(L"Manual");
	m_ctrCmbNumberMode.SelectString(0, L"Auto");

	GetDlgItem(IDC_EDIT_MARKER_NUMBER)->EnableWindow(FALSE);
	GetDlgItem(IDC_SLIDER_MARKER_NUMBER)->EnableWindow(FALSE);

	m_markerColor = RGB(50, 150, 250);
	m_ctrMarkerColor.SetColor(m_markerColor);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}



void CDialogStimulus::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
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
	else if (pScrollBar == (CScrollBar*)&m_ctrTransparency)
	{
		setValue(VALUE_TRANSPARENCY, m_ctrTransparency.GetPos());
	}
	else if (pScrollBar == (CScrollBar*)&m_ctrNumberMode)
	{
		setValue(VALUE_NUMBER_MODE, m_ctrNumberMode.GetPos());
	}
	else if (pScrollBar == (CScrollBar*)&m_ctrMarkerRadius)
	{
		setValue(VALUE_MARKER_RADIUS, m_ctrMarkerRadius.GetPos());
	}
	else if (pScrollBar == (CScrollBar*)&m_ctrMarkerQuality)
	{
		setValue(VALUE_MARKER_QUALITY, m_ctrMarkerQuality.GetPos());
	}
	CDialogEx::OnHScroll(nSBCode, nPos, pScrollBar);
}


BOOL CDialogStimulus::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	if (pMsg->wParam == VK_RETURN || pMsg->wParam == VK_ESCAPE)
		return TRUE;
	return CDialogEx::PreTranslateMessage(pMsg);
}


void CDialogStimulus::setValue(int enumValue, int sliderValue)
{
	CString value;
	switch (enumValue)
	{
	case VALUE_SPATIAL_FREQEUNCY:
		m_spatialFrequency = sliderValue;
		value.Format(_T("%.3f"), m_spatialFrequency / 360.0);
		GetDlgItem(IDC_EDIT_SPATIAL_FREQUENCY)->SetWindowText(value);
		break;
	case VALUE_CONTRAST:
		m_contrast = sliderValue;
		value.Format(_T("%.1f"), m_contrast / 10.0);
		GetDlgItem(IDC_EDIT_CONTRAST)->SetWindowText(value);
		break;
	case VALUE_DRIFT_SPEED:
		m_driftSpeed = sliderValue;
		value.Format(_T("%.1f"), m_driftSpeed / 10.0);
		GetDlgItem(IDC_EDIT_DRIFT_SPEED)->SetWindowText(value);
		break;
	case VALUE_TRANSPARENCY:
		m_transparency = sliderValue;
		value.Format(_T("%d"), m_transparency);
		GetDlgItem(IDC_EDIT_TRANSPARENCY)->SetWindowText(value);
		break;
	case VALUE_NUMBER_MODE:
		m_numberMode = sliderValue;
		value.Format(_T("%d"), m_numberMode);
		GetDlgItem(IDC_EDIT_MARKER_NUMBER)->SetWindowText(value);
		break;
	case VALUE_MARKER_RADIUS:
		m_markerRadius = sliderValue;
		value.Format(_T("%d"), m_markerRadius);
		GetDlgItem(IDC_EDIT_MARKER_RADIUS)->SetWindowText(value);
		break;
	case VALUE_MARKER_QUALITY:
		m_markerQuality = sliderValue;
		value.Format(_T("%d"), m_markerQuality);
		GetDlgItem(IDC_EDIT_MARKER_QUALITY)->SetWindowText(value);
		break;
	}
	if (enumValue != 1)
	{
		m_temporalFrequency = m_spatialFrequency*m_driftSpeed;
		value.Format(_T("Temporal Frequency %4.2fHz"), m_temporalFrequency / 3600.0);
		GetDlgItem(IDC_STATIC_TEMPORAL_FREQUENCY)->SetWindowText(value);
	}
}


void CDialogStimulus::OnCbnSelchangeComboSpatialFrequency()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	switch (m_ctrCmbSpatFreq.GetCurSel()) {
	case 0:
		setValue(VALUE_SPATIAL_FREQEUNCY, 15);
		m_ctrSpatialFrequency.SetPos(m_spatialFrequency);
		break;
	case 1:
		setValue(VALUE_SPATIAL_FREQEUNCY, 21);
		m_ctrSpatialFrequency.SetPos(m_spatialFrequency);
		break;
	case 2:
		setValue(VALUE_SPATIAL_FREQEUNCY, 30);
		m_ctrSpatialFrequency.SetPos(m_spatialFrequency);
		break;
	case 3:
		setValue(VALUE_SPATIAL_FREQEUNCY, 43);
		m_ctrSpatialFrequency.SetPos(m_spatialFrequency);
		break;
	case 4:
		setValue(VALUE_SPATIAL_FREQEUNCY, 62);
		m_ctrSpatialFrequency.SetPos(m_spatialFrequency);
		break;
	case 5:
		setValue(VALUE_SPATIAL_FREQEUNCY, 88);
		m_ctrSpatialFrequency.SetPos(m_spatialFrequency);
		break;
	case 6:
		setValue(VALUE_SPATIAL_FREQEUNCY, 125);
		m_ctrSpatialFrequency.SetPos(m_spatialFrequency);
		break;
	}
}


void CDialogStimulus::OnCbnSelchangeComboContrast()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	switch (m_ctrCmbContrast.GetCurSel()) {
	case 0:
		setValue(VALUE_CONTRAST, 1000);
		m_ctrContrast.SetPos(m_contrast);
		break;
	case 1:
		setValue(VALUE_CONTRAST, 800);
		m_ctrContrast.SetPos(m_contrast);
		break;
	case 2:
		setValue(VALUE_CONTRAST, 600);
		m_ctrContrast.SetPos(m_contrast);
		break;
	case 3:
		setValue(VALUE_CONTRAST, 400);
		m_ctrContrast.SetPos(m_contrast);
		break;
	case 4:
		setValue(VALUE_CONTRAST, 200);
		m_ctrContrast.SetPos(m_contrast);
		break;
	case 5:
		setValue(VALUE_CONTRAST, 0);
		m_ctrContrast.SetPos(m_contrast);
		break;
	}
}


void CDialogStimulus::OnCbnSelchangeComboDriftSpeed()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	switch (m_ctrCmbDriftSpeed.GetCurSel()) {
	case 0:
		setValue(VALUE_DRIFT_SPEED, 60);
		m_ctrDriftSpeed.SetPos(m_driftSpeed);
		break;
	case 1:
		setValue(VALUE_DRIFT_SPEED, 120);
		m_ctrDriftSpeed.SetPos(m_driftSpeed);
		break;
	case 2:
		setValue(VALUE_DRIFT_SPEED, 180);
		m_ctrDriftSpeed.SetPos(m_driftSpeed);
		break;
	case 3:
		setValue(VALUE_DRIFT_SPEED, 240);
		m_ctrDriftSpeed.SetPos(m_driftSpeed);
		break;
	case 4:
		setValue(VALUE_DRIFT_SPEED, 300);
		m_ctrDriftSpeed.SetPos(m_driftSpeed);
		break;
	case 5:
		setValue(VALUE_DRIFT_SPEED, 360);
		m_ctrDriftSpeed.SetPos(m_driftSpeed);
		break;
	}

}


void CDialogStimulus::OnBnClickedMarkerColor()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	m_markerColor = m_ctrMarkerColor.GetColor();
}


void CDialogStimulus::OnCbnSelchangeComboNumberMode()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	switch (m_ctrCmbNumberMode.GetCurSel()) {
	case 0:
		GetDlgItem(IDC_EDIT_MARKER_NUMBER)->EnableWindow(FALSE);
		GetDlgItem(IDC_SLIDER_MARKER_NUMBER)->EnableWindow(FALSE);
		break;
	case 1:
		GetDlgItem(IDC_EDIT_MARKER_NUMBER)->EnableWindow(TRUE);
		GetDlgItem(IDC_SLIDER_MARKER_NUMBER)->EnableWindow(TRUE);
		break;
	}
}
