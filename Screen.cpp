// Screen.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "MouseOptometry.h"
#include "Screen.h"
#include "afxdialogex.h"
#include "OptometryDlg.h"

#define M_PI 3.14159265358979323846
#define d_pParent ((COptometryDlg*)AfxGetMainWnd())

// CScreen ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(CScreen, CDialogEx)

CScreen::CScreen(int i, CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG_SCREEN, pParent)
{
	monNum = i;
	screenWidth = 1600;
	screenHeight = 1200;
}

CScreen::~CScreen()
{
}

void CScreen::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CScreen, CDialogEx)
END_MESSAGE_MAP()

// CScreen �޽��� ó�����Դϴ�.

BOOL CScreen::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.

	HMONITOR hMonitor;
	MONITORINFO mi;

	RECT rct, rect;
	int tol = 50;
	rct.left = GetSystemMetrics(SM_CXSCREEN) * monNum + tol;
	rct.top = tol;
	rct.right = GetSystemMetrics(SM_CXSCREEN) * (monNum + 1) - tol;
	rct.bottom = GetSystemMetrics(SM_CYSCREEN) - tol;

	hMonitor = MonitorFromRect(&rct, MONITOR_DEFAULTTONEAREST);

	mi.cbSize = sizeof(mi);

	GetMonitorInfo(hMonitor, &mi);
	rect = mi.rcMonitor;

	screenWidth = rect.right - rect.left;
	screenHeight = rect.bottom - rect.top;

	SetWindowPos(&wndTopMost, rect.left, rect.top, screenWidth, screenHeight, SWP_SHOWWINDOW);
	ShowWindow(SW_MAXIMIZE);
	//ShowWindow(SW_SHOW);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
}


void CScreen::bufferedDraw(double driftedTime, int drawWidth, double centerX, double centerY, double spaFreq, double contrast, double monSize, double monPos)
{
 	CDC* thisDC = GetDC();
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
		mx += -monSize/2.0;
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
			drawSlit(pRgb, i, mx, my, driftedTime, drawWidth,  spaFreq, contrast);
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


void CScreen::drawSlit(RGBQUAD* pRgb, int i, double mx, double my, double driftedTime, int drawWidth, double spaFreq, double contrast)
{
	int penColor = contrast * (sin(spaFreq * (atan2(my, mx) + driftedTime * M_PI / 180.0)) + 1);
	penColor = penColor > 255 ? 255 : penColor < 0 ? 0 : penColor;
	pRgb[i].rgbRed = penColor;
	pRgb[i].rgbGreen = penColor;
	pRgb[i].rgbBlue = penColor;
}


void CScreen::OnCancel()
{
	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.

	CDialogEx::OnCancel();
}
