
// OptometryDlg.cpp : 구현 파일
//

#include "stdafx.h"
#include "MouseOptometry.h"
#include "OptometryDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif



// COptometryDlg 대화 상자

COptometryDlg::COptometryDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG_MAIN, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_calX = 1000;
	m_calY = 1000;
	m_calDiameter = 0;
	m_footholdDiameter = 0.0;
	m_stimulusX = 0.0;
	m_stimulusY = 0.0;
	m_monitorSize = 0.0;
	m_monitorPosition = 0.0;
}

void COptometryDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_MAIN, m_mainList);
	DDX_Control(pDX, IDC_TAB_MAIN, m_mainTab);
}

BEGIN_MESSAGE_MAP(COptometryDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_COMMAND(ID_FILE_EXIT, &COptometryDlg::OnFileExit)
	ON_LBN_SELCHANGE(IDC_LIST_MAIN, &COptometryDlg::OnLbnSelchangeList1)
	ON_WM_CTLCOLOR()
	ON_COMMAND(ID_VIEW_SHOWVIDEO, &COptometryDlg::OnViewShowvideo)
	ON_COMMAND(ID_FILE_OPENCAMERA, &COptometryDlg::OnFileOpencamera)
	ON_COMMAND(ID_FILE_OPENVIDEOFILE, &COptometryDlg::OnFileOpenvideofile)
	ON_COMMAND(ID_VIEW_SHOWSCREEN, &COptometryDlg::OnViewShowscreen)
	ON_COMMAND(ID_VIEW_SHOWSAMPLESCREEN, &COptometryDlg::OnViewShowsamplescreen)
END_MESSAGE_MAP()


// COptometryDlg 메시지 처리기

BOOL COptometryDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.

	/*CString tst;
	tst.Format(L"%5.5f", atan2(3.3,3.3));
	AfxMessageBox(tst);*/

	//변수초기화
	m_isScreenOn = 0;
	m_isSampleOn = 0;
	m_testMode = 0;			// 테스트 모드. 1이상이면 쥐 검출을 한다. 0:

	// Main List 폰트 크기 조절
	HFONT hNewFont;
	hNewFont = CreateFont(20, 0, 0, 0, 0, 0, 0, 0, HANGEUL_CHARSET, 3, 2, 1, VARIABLE_PITCH | FF_MODERN, _T("맑은 고딕"));
	m_mainList.SendMessage(WM_SETFONT, (WPARAM)hNewFont, (LPARAM)FALSE);

	// Main List 아이템 추가
	m_mainList.InsertString(0, _T("Stimulus"));
	m_mainList.InsertString(1, _T("Camera"));
	m_mainList.InsertString(2, _T("Experiment"));
	m_mainList.InsertString(3, _T("Result"));
	m_mainList.InsertString(4, _T("Calibration"));

	// Main List Item 선택
	m_mainList.SelectString(0, _T("Stimulus"));

	// Main 탭 다이얼로그 설정
	CRect rect;
	m_mainTab.GetClientRect(&rect);

	m_tab1_stimulus.Create(IDD_TAB_STIMULUS, &m_mainTab);
	m_tab1_stimulus.SetWindowPos(NULL, 0, 0, rect.Width(), rect.Height(), SWP_SHOWWINDOW | SWP_NOZORDER);
	m_tab2_camera.Create(IDD_TAB_CAMERA, &m_mainTab);
	m_tab2_camera.SetWindowPos(NULL, 0, 0, rect.Width(), rect.Height(), SWP_NOZORDER);
	m_tab3_testing.Create(IDD_TAB_TESTING, &m_mainTab);
	m_tab3_testing.SetWindowPos(NULL, 0, 0, rect.Width(), rect.Height(), SWP_NOZORDER);
	m_tab4_result.Create(IDD_TAB_RESULT, &m_mainTab);
	m_tab4_result.SetWindowPos(NULL, 0, 0, rect.Width(), rect.Height(), SWP_NOZORDER);
	m_tab5_calibration.Create(IDD_TAB_CALIBRATION, &m_mainTab);
	m_tab5_calibration.SetWindowPos(NULL, 0, 0, rect.Width(), rect.Height(), SWP_NOZORDER);

	this->m_mainTabNow = &this->m_tab1_stimulus;

	CButton* pCheck;
	pCheck = (CButton*)GetDlgItem(IDC_RADIO_SCREEN_MODE1);
	pCheck->SetBitmap(LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_BITMAP_SCREEN_MODE1)));
	pCheck = (CButton*)GetDlgItem(IDC_RADIO_SCREEN_MODE2);
	pCheck->SetBitmap(LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_BITMAP_SCREEN_MODE2)));
	pCheck = (CButton*)GetDlgItem(IDC_RADIO_SCREEN_MODE3);
	pCheck->SetBitmap(LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_BITMAP_SCREEN_MODE3)));
	pCheck = (CButton*)GetDlgItem(IDC_RADIO_SCREEN_MODE4);
	pCheck->SetBitmap(LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_BITMAP_SCREEN_MODE4)));
	pCheck->SetCheck(true);

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 응용 프로그램의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void COptometryDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR COptometryDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void COptometryDlg::OnFileExit()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CDialogEx::OnCancel();
}


void COptometryDlg::OnLbnSelchangeList1()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (this->m_mainTabNow != NULL)
	{
		this->m_mainTabNow->ShowWindow(SW_HIDE);
		this->m_mainTabNow = NULL;
	}

	int slctidx = m_mainList.GetCurSel();
	switch (slctidx) {
	case 0:
		this->m_tab1_stimulus.ShowWindow(SW_SHOW);
		this->m_mainTabNow = &this->m_tab1_stimulus;
		break;
	case 1:
		this->m_tab2_camera.ShowWindow(SW_SHOW);
		this->m_mainTabNow = &this->m_tab2_camera;
		break;
	case 2:
		this->m_tab3_testing.ShowWindow(SW_SHOW);
		this->m_mainTabNow = &this->m_tab3_testing;
		break;
	case 3:
		this->m_tab4_result.ShowWindow(SW_SHOW);
		this->m_mainTabNow = &this->m_tab4_result;
		break;
	case 4:
		this->m_tab5_calibration.ShowWindow(SW_SHOW);
		this->m_mainTabNow = &this->m_tab5_calibration;
		break;
	}
}


HBRUSH COptometryDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  여기서 DC의 특성을 변경합니다.

	if (nCtlColor == CTLCOLOR_LISTBOX)
	{
		if (pWnd->GetDlgCtrlID() == IDC_LIST_MAIN)
		{
			//pDC->SetTextColor(RGB(255, 0, 0));
			pDC->SetBkColor(RGB(240, 240, 240));
			HBRUSH m_brh = CreateSolidBrush(RGB(240, 240, 240));
			return m_brh;
		}
	}

	// TODO:  기본값이 적당하지 않으면 다른 브러시를 반환합니다.
	return hbr;
}


BOOL COptometryDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	 if(pMsg->wParam == VK_RETURN || pMsg->wParam == VK_ESCAPE)
          return TRUE;
	return CDialogEx::PreTranslateMessage(pMsg);
}


UINT COptometryDlg::threadFunc1(LPVOID pParam)
{
	COptometryDlg* pDlg = (COptometryDlg*) pParam;
	while (!(pDlg->m_threadStop))
	{
		pDlg->onThread(pDlg, 0);
	}
	return 0;
}
UINT COptometryDlg::threadFunc2(LPVOID pParam)
{
	COptometryDlg* pDlg = (COptometryDlg*)pParam;
	while (!(pDlg->m_threadStop))
	{
		pDlg->onThread(pDlg, 1);
	}
	return 0;
}
UINT COptometryDlg::threadFunc3(LPVOID pParam)
{
	COptometryDlg* pDlg = (COptometryDlg*)pParam;
	while (!(pDlg->m_threadStop))
	{
		pDlg->onThread(pDlg, 2);
	}
	return 0;
}
UINT COptometryDlg::threadFunc4(LPVOID pParam)
{
	COptometryDlg* pDlg = (COptometryDlg*)pParam;
	while (!(pDlg->m_threadStop))
	{
		pDlg->onThread(pDlg, 3);
	}
	return 0;
}
UINT COptometryDlg::sampleThreadFunc(LPVOID pParam)
{
	COptometryDlg* pDlg = (COptometryDlg*)pParam;
	while (!(pDlg->m_threadStop))
	{
		pDlg->onSampleThread(pDlg);
	}
	return 0;
}


void COptometryDlg::OnViewShowvideo()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	
	if (m_dlgCamera.GetSafeHwnd() == NULL)
			m_dlgCamera.Create(IDD_DIALOG_CAMERA);
	m_dlgCamera.ShowWindow(SW_SHOW);
}


void COptometryDlg::OnFileOpencamera()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	OnViewShowvideo();
	m_dlgCamera.openCamera();
}


void COptometryDlg::OnFileOpenvideofile()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	OnViewShowvideo();
	m_dlgCamera.openVideoFile();
}


void COptometryDlg::onThread(COptometryDlg* pDlg, int idx)
{
	double driftedTime = pDlg->m_tab1_stimulus.m_driftSpeed * GetTickCount() * 0.0001;
	int drawWidth = 800;
	double spaFreq = pDlg->m_tab1_stimulus.m_spatialFrequency;
	double contrast = pDlg->m_tab1_stimulus.m_contrast;
	double pixelRatio = m_footholdDiameter / m_calDiameter;
	double finalX = pixelRatio*(-(m_calX - 1000) / 2000.0*m_dlgCamera.m_capture.get(CAP_PROP_FRAME_WIDTH) + m_stimulusX);
	double finalY = pixelRatio*((m_calY - 1000) / 2000.0*m_dlgCamera.m_capture.get(CAP_PROP_FRAME_HEIGHT) - m_stimulusY);
	pDlg->m_slitScreen[idx]->bufferedDraw(driftedTime, drawWidth, finalX, finalY, spaFreq, 0.128*contrast, m_monitorSize, m_monitorPosition);
}

void COptometryDlg::onSampleThread(COptometryDlg* pDlg)
{
	double driftedTime = pDlg->m_tab1_stimulus.m_driftSpeed * GetTickCount() * 0.0001;
	double spaFreq = pDlg->m_tab1_stimulus.m_spatialFrequency;
	double contrast = pDlg->m_tab1_stimulus.m_contrast;
	double pixelRatio = m_footholdDiameter / m_calDiameter;
	double finalX = pixelRatio*(-(m_calX-1000) / 2000.0*m_dlgCamera.m_capture.get(CAP_PROP_FRAME_WIDTH) + m_stimulusX);
	double finalY = pixelRatio*((m_calY-1000) / 2000.0*m_dlgCamera.m_capture.get(CAP_PROP_FRAME_HEIGHT) - m_stimulusY);
	pDlg->m_sampleScreen->bufferedDraw(driftedTime, finalX, finalY, spaFreq, 0.128*contrast, m_monitorSize, m_monitorPosition);
}


void COptometryDlg::OnCancel()
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	m_threadStop = true;
	CDialogEx::OnCancel();
}


void COptometryDlg::OnViewShowscreen()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	// Slit을 그릴 스크린을 준비
	if (m_isScreenOn == 0)
	{
		for (int idx = 1; idx < 5; idx++)
		{
			m_slitScreen[idx - 1] = new CScreen(idx);
			m_slitScreen[idx - 1]->Create(IDD_DIALOG_SCREEN, this);
		}

		// Slit을 그리는 Thread 시작

		m_threadStop = FALSE;

		m_pThread[0] = AfxBeginThread(threadFunc1, this);
		m_pThread[1] = AfxBeginThread(threadFunc2, this);
		m_pThread[2] = AfxBeginThread(threadFunc3, this);
		m_pThread[3] = AfxBeginThread(threadFunc4, this);

		m_isScreenOn = 1;
	}
	else if (m_isScreenOn == 1)
	{
		for (int idx = 0; idx < 4; idx++)
		{
			m_slitScreen[idx]->ShowWindow(SW_HIDE);
			m_pThread[idx]->SuspendThread();
		}
		m_isScreenOn = 2;
	}
	else if (m_isScreenOn == 2)
	{
		for (int idx = 0; idx < 4; idx++)
		{
			m_slitScreen[idx]->ShowWindow(SW_SHOW);
			m_pThread[idx]->ResumeThread();
		}
		m_isScreenOn = 1;
	}
}


void COptometryDlg::OnViewShowsamplescreen()
{
	CMenu *pMenu = GetMenu();
	CMenu *pTemp = pMenu->GetSubMenu(0);

	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	if (m_isSampleOn == 0)
	{
		m_sampleScreen = new CSampleScreen();
		m_sampleScreen->Create(IDD_DIALOG_SAMPLE, this);

		m_threadStop = FALSE;

		m_sampleThread = AfxBeginThread(sampleThreadFunc, this);

		pMenu->ModifyMenu(ID_VIEW_SHOWSAMPLESCREEN, MF_BYCOMMAND, ID_VIEW_SHOWSAMPLESCREEN, _T("Hide Sample Screen"));

		m_isSampleOn = 1;
	}
	else if (m_isSampleOn == 1)
	{
		m_sampleScreen->ShowWindow(SW_HIDE);
		m_sampleThread->SuspendThread();

		pMenu->ModifyMenu(ID_VIEW_SHOWSAMPLESCREEN, MF_BYCOMMAND, ID_VIEW_SHOWSAMPLESCREEN, _T("Show Sample Screen"));

		m_isSampleOn = 2;
	}
	else if (m_isSampleOn == 2)
	{
		m_sampleScreen->ShowWindow(SW_SHOW);
		m_sampleThread->ResumeThread();

		pMenu->ModifyMenu(ID_VIEW_SHOWSAMPLESCREEN, MF_BYCOMMAND, ID_VIEW_SHOWSAMPLESCREEN, _T("Hide Sample Screen"));

		m_isSampleOn = 1;
	}
}
