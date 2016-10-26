// SampleScreen.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "MouseOptometry.h"
#include "SampleScreen.h"
#include "afxdialogex.h"
#include "OptometryDlg.h"

#define d_pParent ((COptometryDlg*)AfxGetMainWnd())

// CSampleScreen 대화 상자입니다.

IMPLEMENT_DYNAMIC(CSampleScreen, CDialogEx)

CSampleScreen::CSampleScreen(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG_SAMPLE, pParent)
{
	monNum = 1;
	screenWidth = 0;
	screenHeight = 0;
}

CSampleScreen::~CSampleScreen()
{
}

void CSampleScreen::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_SAMPLE_SCREEN, m_sampleComboBox);
	DDX_Control(pDX, IDC_PICTURE_SAMPLE, m_drawSample);
	DDX_Control(pDX, IDC_SLIDER_QUALITY, m_sliderQuality);
}


BEGIN_MESSAGE_MAP(CSampleScreen, CDialogEx)
	ON_CBN_SELCHANGE(IDC_COMBO_SAMPLE_SCREEN, &CSampleScreen::OnCbnSelchangeComboSampleScreen)
	ON_WM_SIZE()
	ON_WM_HSCROLL()
END_MESSAGE_MAP()


// CSampleScreen 메시지 처리기입니다.


void CSampleScreen::bufferedDraw(double driftedTime,  double centerX, double centerY, double spaFreq, double contrast, double monSize, double monPos)
{
	int drawWidth = m_sliderQuality.GetPos();
	CDC* thisDC = GetDlgItem(IDC_PICTURE_SAMPLE)->GetDC(); //GetDC();
	CDC memDC;
	memDC.CreateCompatibleDC(thisDC);
	CBitmap *pOldBitmap, bitmap;
	bitmap.CreateCompatibleBitmap(thisDC, drawWidth, 1);

	pOldBitmap = memDC.SelectObject(&bitmap);

	BITMAP bm;
	bitmap.GetObject(sizeof(BITMAP), (LPSTR)&bm);
	BYTE *pData = NULL;
	pData = (BYTE*)malloc(bm.bmWidthBytes * bm.bmHeight);
	memset(pData, 0x00, bm.bmWidthBytes * bm.bmHeight);
	bitmap.GetBitmapBits(bm.bmWidthBytes * bm.bmHeight, pData);
	RGBQUAD *pRgb = (RGBQUAD*)pData;

	double mx = -centerX, my = -centerY;
	switch (monNum)
	{
	case 1:
		mx += -monSize / 2.0;
		my += monPos;
		for (int i = 0; i < drawWidth; i++)
		{
			mx += monSize / drawWidth;
			drawSlit(pRgb, i, mx, my, driftedTime, drawWidth, spaFreq, contrast);
		}
		break;
	case 2:
		mx += monPos;
		my += monSize / 2.0;
		for (int i = 0; i < drawWidth; i++)
		{
			my -= monSize / drawWidth;
			drawSlit(pRgb, i, mx, my, driftedTime, drawWidth, spaFreq, contrast);
		}
		break;
	case 3:
		mx += monSize / 2.0;
		my += -monPos;
		for (int i = 0; i < drawWidth; i++)
		{
			mx -= monSize / drawWidth;
			drawSlit(pRgb, i, mx, my, driftedTime, drawWidth, spaFreq, contrast);
		}
		break;
	case 4:
		mx += -monPos;
		my += -monSize / 2.0;
		for (int i = 0; i < drawWidth; i++)
		{
			my += monSize / drawWidth;
			drawSlit(pRgb, i, mx, my, driftedTime, drawWidth, spaFreq, contrast);
		}
		break;
	}

	bitmap.SetBitmapBits(bm.bmWidthBytes * bm.bmHeight, pData);
	CDC tmpDC;
	thisDC->StretchBlt(0, 0, screenWidth, screenHeight, &memDC, 0, 0, drawWidth, 1, SRCCOPY);
	memDC.SelectObject(pOldBitmap);

	free(pData);
	pData = NULL;

	tmpDC.DeleteDC();
	memDC.DeleteDC();
	thisDC->DeleteDC();
	bitmap.DeleteObject();
}


void CSampleScreen::drawSlit(RGBQUAD* pRgb, int i, double mx, double my, double driftedTime, int drawWidth, double spaFreq, double contrast)
{
	int penColor = contrast * (sin(spaFreq * (atan2(my, mx) + driftedTime * M_PI/180.0)) + 1);
	penColor = penColor > 255 ? 255 : penColor < 0 ? 0 : penColor;
	pRgb[i].rgbRed = penColor;
	pRgb[i].rgbGreen = penColor;
	pRgb[i].rgbBlue = penColor;
}


BOOL CSampleScreen::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	ShowWindow(SW_SHOW);
	CRect rect; 
	GetClientRect(rect);
	screenWidth = rect.right - rect.left;
	screenHeight = rect.bottom - rect.top;

	m_sampleComboBox.AddString(_T("North  (1)"));
	m_sampleComboBox.AddString(_T("East   (2)"));
	m_sampleComboBox.AddString(_T("South (3)"));
	m_sampleComboBox.AddString(_T("West  (4)"));
	m_sampleComboBox.SelectString(0, _T("North  (1)"));

	m_sliderQuality.SetRange(10, 800);
	m_sliderQuality.SetPos(200);
	((CWnd*)GetDlgItem(IDC_TEXT_QUALITY))->SetWindowText(_T("Quality : 200"));

	CRect mainRc;
	AfxGetMainWnd()->GetWindowRect(&mainRc);
	SetWindowPos(NULL, mainRc.right, mainRc.top, 0, 0, SWP_NOSIZE);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


void CSampleScreen::OnCancel()
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	d_pParent->OnViewShowsamplescreen();

	//CDialogEx::OnCancel();
}


void CSampleScreen::OnCbnSelchangeComboSampleScreen()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	monNum = m_sampleComboBox.GetCurSel() + 1;
}


void CSampleScreen::OnSize(UINT nType, int cx, int cy)
{
	if (cx > 399 && cy > 299)
	{
		CDialogEx::OnSize(nType, cx, cy);

		// TODO: 여기에 메시지 처리기 코드를 추가합니다.

		CRect r;
		GetClientRect(r);

		int margin = 28;
		screenWidth = r.right - r.left;
		screenHeight = r.bottom - r.top - margin;
		m_drawSample.MoveWindow(r.left, r.top + margin, screenWidth, screenHeight);
	}
	
}


void CSampleScreen::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	if (pScrollBar == (CScrollBar*)&m_sliderQuality)
	{
		CString strQuality = _T("");
		strQuality.Format(_T("Quality : %d"), m_sliderQuality.GetPos());
		SetDlgItemText(IDC_TEXT_QUALITY,strQuality);
	}

	CDialogEx::OnHScroll(nSBCode, nPos, pScrollBar);
}


void CSampleScreen::constantDraw(unsigned char brightness)
{

	CDC* thisDC = GetDlgItem(IDC_PICTURE_SAMPLE)->GetDC(); //GetDC();
	CDC memDC;
	memDC.CreateCompatibleDC(thisDC);
	CBitmap *pOldBitmap, bitmap;
	bitmap.CreateCompatibleBitmap(thisDC, 1, 1);

	pOldBitmap = memDC.SelectObject(&bitmap);

	BITMAP bm;
	bitmap.GetObject(sizeof(BITMAP), (LPSTR)&bm);
	BYTE *pData = NULL;
	pData = (BYTE*)malloc(bm.bmWidthBytes * bm.bmHeight);
	memset(pData, 0x00, bm.bmWidthBytes * bm.bmHeight);
	bitmap.GetBitmapBits(bm.bmWidthBytes * bm.bmHeight, pData);
	RGBQUAD *pRgb = (RGBQUAD*)pData;

	unsigned char penColor = brightness;
	pRgb[0].rgbRed = penColor;
	pRgb[0].rgbGreen = penColor;
	pRgb[0].rgbBlue = penColor;

	bitmap.SetBitmapBits(bm.bmWidthBytes * bm.bmHeight, pData);
	CDC tmpDC;
	thisDC->StretchBlt(0, 0, screenWidth, screenHeight, &memDC, 0, 0, 1, 1, SRCCOPY);
	memDC.SelectObject(pOldBitmap);

	free(pData);
	pData = NULL;

	tmpDC.DeleteDC();
	memDC.DeleteDC();
	thisDC->DeleteDC();
	bitmap.DeleteObject();
}
