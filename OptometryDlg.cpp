
// OptometryDlg.cpp : ���� ����
//

#include "stdafx.h"
#include "MouseOptometry.h"
#include "OptometryDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif



// COptometryDlg ��ȭ ����

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


// COptometryDlg �޽��� ó����

BOOL COptometryDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// �� ��ȭ ������ �������� �����մϴ�.  ���� ���α׷��� �� â�� ��ȭ ���ڰ� �ƴ� ��쿡��
	//  �����ӿ�ũ�� �� �۾��� �ڵ����� �����մϴ�.
	SetIcon(m_hIcon, TRUE);			// ū �������� �����մϴ�.
	SetIcon(m_hIcon, FALSE);		// ���� �������� �����մϴ�.

	// TODO: ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.

	/*CString tst;
	tst.Format(L"%5.5f", atan2(3.3,3.3));
	AfxMessageBox(tst);*/

	//�����ʱ�ȭ
	m_isScreenOn = 0;
	m_isSampleOn = 0;
	m_testMode = 0;			// �׽�Ʈ ���. 1�̻��̸� �� ������ �Ѵ�. 0:

	// Main List ��Ʈ ũ�� ����
	HFONT hNewFont;
	hNewFont = CreateFont(20, 0, 0, 0, 0, 0, 0, 0, HANGEUL_CHARSET, 3, 2, 1, VARIABLE_PITCH | FF_MODERN, _T("���� ���"));
	m_mainList.SendMessage(WM_SETFONT, (WPARAM)hNewFont, (LPARAM)FALSE);

	// Main List ������ �߰�
	m_mainList.InsertString(0, _T("Stimulus"));
	m_mainList.InsertString(1, _T("Camera"));
	m_mainList.InsertString(2, _T("Experiment"));
	m_mainList.InsertString(3, _T("Result"));
	m_mainList.InsertString(4, _T("Calibration"));

	// Main List Item ����
	m_mainList.SelectString(0, _T("Stimulus"));

	// Main �� ���̾�α� ����
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

	return TRUE;  // ��Ŀ���� ��Ʈ�ѿ� �������� ������ TRUE�� ��ȯ�մϴ�.
}

// ��ȭ ���ڿ� �ּ�ȭ ���߸� �߰��� ��� �������� �׸�����
//  �Ʒ� �ڵ尡 �ʿ��մϴ�.  ����/�� ���� ����ϴ� MFC ���� ���α׷��� ��쿡��
//  �����ӿ�ũ���� �� �۾��� �ڵ����� �����մϴ�.

void COptometryDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // �׸��⸦ ���� ����̽� ���ؽ�Ʈ�Դϴ�.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Ŭ���̾�Ʈ �簢������ �������� ����� ����ϴ�.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// �������� �׸��ϴ�.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// ����ڰ� �ּ�ȭ�� â�� ���� ���ȿ� Ŀ���� ǥ�õǵ��� �ý��ۿ���
//  �� �Լ��� ȣ���մϴ�.
HCURSOR COptometryDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void COptometryDlg::OnFileExit()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	CDialogEx::OnCancel();
}


void COptometryDlg::OnLbnSelchangeList1()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
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

	// TODO:  ���⼭ DC�� Ư���� �����մϴ�.

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

	// TODO:  �⺻���� �������� ������ �ٸ� �귯�ø� ��ȯ�մϴ�.
	return hbr;
}


BOOL COptometryDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.
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
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	
	if (m_dlgCamera.GetSafeHwnd() == NULL)
			m_dlgCamera.Create(IDD_DIALOG_CAMERA);
	m_dlgCamera.ShowWindow(SW_SHOW);
}


void COptometryDlg::OnFileOpencamera()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	OnViewShowvideo();
	m_dlgCamera.openCamera();
}


void COptometryDlg::OnFileOpenvideofile()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
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
	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.
	m_threadStop = true;
	CDialogEx::OnCancel();
}


void COptometryDlg::OnViewShowscreen()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	// Slit�� �׸� ��ũ���� �غ�
	if (m_isScreenOn == 0)
	{
		for (int idx = 1; idx < 5; idx++)
		{
			m_slitScreen[idx - 1] = new CScreen(idx);
			m_slitScreen[idx - 1]->Create(IDD_DIALOG_SCREEN, this);
		}

		// Slit�� �׸��� Thread ����

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

	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
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
