// DialogTesting.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "MouseOptometry.h"
#include "DialogTesting.h"
#include "afxdialogex.h"
#include "OptometryDlg.h"

#define d_pParent ((COptometryDlg*)AfxGetMainWnd())

// CDialogTesting 대화 상자입니다.

IMPLEMENT_DYNAMIC(CDialogTesting, CDialogEx)

CDialogTesting::CDialogTesting(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_TAB_TESTING, pParent)
{
	m_startSpatialFrequency = 0;
	m_startContrast = 0;
	m_startDriftSpeed = 0;
}

CDialogTesting::~CDialogTesting()
{
}

void CDialogTesting::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_MODE_SELECT, m_ctrCmbModeSelect);
	DDX_Control(pDX, IDC_CHECK_AUTO_GENERATE, m_ctrAutoGenerate);
	DDX_Control(pDX, IDC_CHECK_AUTO_INDEX, m_ctrAutoIndex);
	DDX_Control(pDX, IDC_CHECK_DATE, m_ctrDate);
	DDX_Control(pDX, IDC_CHECK_TIME, m_ctrTime);
	DDX_Control(pDX, IDC_EDIT_SAVE_NAME, m_ctrSaveFileName);
	DDX_Control(pDX, IDC_EDIT_BASE_NAME, m_ctrBaseFileName);
	DDX_Control(pDX, IDC_COMBO_TESTING_EYES, m_ctrCmbTestingEyes);
	DDX_Control(pDX, IDC_COMBO_SEARCHING_ALGORITHMS, m_ctrCmbSearchingAlgorithms);
	DDX_Control(pDX, IDC_BUTTON_YES, m_ctrYes);
	DDX_Control(pDX, IDC_BUTTON_NO, m_ctrNo);
	DDX_Control(pDX, IDC_BUTTON_RESET, m_ctrReset);
	DDX_Control(pDX, IDC_BUTTON_DONE, m_ctrDone);
	DDX_Control(pDX, IDC_BUTTON_START, m_ctrExperimentStart);
	DDX_Control(pDX, IDC_CHECK_TRACKING, m_ctrTracking);
}


BEGIN_MESSAGE_MAP(CDialogTesting, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_BROWSE, &CDialogTesting::OnBnClickedButtonBrowse)
	ON_BN_CLICKED(IDC_CHECK_AUTO_GENERATE, &CDialogTesting::OnBnClickedCheckAutoGenerate)
	ON_BN_CLICKED(IDC_CHECK_AUTO_INDEX, &CDialogTesting::OnBnClickedCheckAutoIndex)
	ON_BN_CLICKED(IDC_CHECK_DATE, &CDialogTesting::OnBnClickedCheckDate)
	ON_BN_CLICKED(IDC_CHECK_TIME, &CDialogTesting::OnBnClickedCheckTime)
	ON_EN_CHANGE(IDC_EDIT_BASE_NAME, &CDialogTesting::OnEnChangeEditBaseName)
	ON_BN_CLICKED(IDC_BUTTON_START, &CDialogTesting::OnBnClickedButtonStart)
	ON_BN_CLICKED(IDC_BUTTON_CONFIGURATION, &CDialogTesting::OnBnClickedButtonConfiguration)
	ON_BN_CLICKED(IDC_BUTTON_YES, &CDialogTesting::OnBnClickedButtonYes)
	ON_BN_CLICKED(IDC_BUTTON_NO, &CDialogTesting::OnBnClickedButtonNo)
	ON_BN_CLICKED(IDC_BUTTON_RESET, &CDialogTesting::OnBnClickedButtonReset)
	ON_BN_CLICKED(IDC_BUTTON_DONE, &CDialogTesting::OnBnClickedButtonDone)
END_MESSAGE_MAP()


// CDialogTesting 메시지 처리기입니다.


BOOL CDialogTesting::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.

	HFONT hNewFont;
	hNewFont = CreateFont(20, 0, 0, 0, 0, 0, 0, 0, HANGEUL_CHARSET, 3, 2, 1, VARIABLE_PITCH | FF_MODERN, _T("맑은 고딕"));
	GetDlgItem(IDC_BUTTON_START)->SendMessage(WM_SETFONT, (WPARAM)hNewFont, (LPARAM)FALSE);

	m_ctrCmbModeSelect.AddString(L"Auto");
	m_ctrCmbModeSelect.AddString(L"Auto+MANUAL");
	m_ctrCmbModeSelect.AddString(L"MANUAL");
	m_ctrCmbModeSelect.SelectString(-1, L"Auto");

	m_ctrCmbTestingEyes.AddString(L"Left(CCW)-Right(CW)");
	m_ctrCmbTestingEyes.AddString(L"Right(CW)-Left(CCW)");
	m_ctrCmbTestingEyes.AddString(L"Left(CCW)");
	m_ctrCmbTestingEyes.AddString(L"Right(CW)");
	m_ctrCmbTestingEyes.SelectString(-1, L"Left(CCW)-Right(CW)");

	m_ctrCmbSearchingAlgorithms.AddString(L"Binary Search");
	m_ctrCmbSearchingAlgorithms.AddString(L"Gradually Increase");
	m_ctrCmbSearchingAlgorithms.AddString(L"Gradually Decrease");
	m_ctrCmbSearchingAlgorithms.SelectString(-1, L"Binary Search");

	TCHAR initialPath[_MAX_PATH];
	GetModuleFileName(NULL, initialPath, sizeof initialPath);

	CString strPath = initialPath;
	int i = strPath.ReverseFind('\\');//실행 파일 이름을 지우기 위해서 왼쪽에 있는 '/'를 찾는다.
	strPath = strPath.Left(i);

	GetDlgItem(IDC_EDIT_SAVE_PATH)->SetWindowText(strPath);

	m_ctrAutoGenerate.SetCheck(TRUE);
	m_ctrBaseFileName.SetWindowTextW(L"Experiment");
	m_ctrDate.SetCheck(TRUE);
	m_ctrAutoIndex.SetCheck(TRUE);
	m_ctrTracking.SetCheck(TRUE);
	makeFileName();

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

int CALLBACK BrowseCallbackProc(HWND hwnd, UINT uMsg, LPARAM lParam, LPARAM lpData)
{
	switch (uMsg) {
		// 폴더선택 다이얼로그의 초기화가 끝난 경우
	case BFFM_INITIALIZED:
		SendMessage(hwnd, BFFM_SETSELECTION, TRUE, lpData);
		break;
	}
	return 0;
}

void CDialogTesting::OnBnClickedButtonBrowse()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	ITEMIDLIST  *pidlBrowse;
    WCHAR       pszPathname[MAX_PATH];
 
    BROWSEINFO  BrInfo;
    BrInfo.hwndOwner = GetSafeHwnd();
    BrInfo.pidlRoot = NULL;
 
    memset(&BrInfo, 0x00, sizeof(BrInfo));
    BrInfo.pszDisplayName = pszPathname;
    BrInfo.lpszTitle = _T("Select folder");
    BrInfo.ulFlags = BIF_RETURNONLYFSDIRS| BIF_USENEWUI;
 
    // 이벤트에 대한 사용자정의 함수
    BrInfo.lpfn = BrowseCallbackProc;
 
    // 사용자정의 함수에 넘겨질 인자로 사용자가 설정하고자 하는 경로를 설정한다.
    // 예를들어 초기폴더경로를 C드라이브로 설정하는 경우
	CString strInitPath;
	GetDlgItem(IDC_EDIT_SAVE_PATH)->GetWindowText(strInitPath);
    BrInfo.lParam = (LPARAM)strInitPath.GetBuffer();
 
    pidlBrowse = ::SHBrowseForFolder(&BrInfo);
    if(pidlBrowse != NULL)
    {
        // 선택된 폴더 경로얻음
        SHGetPathFromIDList(pidlBrowse, pszPathname);
         
        // 경로(pszPathname)를 이용하여 이후작업 추가
		GetDlgItem(IDC_EDIT_SAVE_PATH)->SetWindowText(pszPathname);
    }
}



void CDialogTesting::OnBnClickedCheckAutoGenerate()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (m_ctrAutoGenerate.GetCheck())
	{
		m_ctrSaveFileName.SetReadOnly(TRUE);
		m_ctrBaseFileName.EnableWindow(TRUE);
		m_ctrDate.EnableWindow(TRUE);
		m_ctrTime.EnableWindow(TRUE);
		makeFileName();
	}
	else
	{
		m_ctrSaveFileName.SetReadOnly(FALSE);
		m_ctrBaseFileName.EnableWindow(FALSE);
		m_ctrDate.EnableWindow(FALSE);
		m_ctrTime.EnableWindow(FALSE);
	}

}


void CDialogTesting::OnBnClickedCheckAutoIndex()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	makeFileName();
}


void CDialogTesting::OnBnClickedCheckDate()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	makeFileName();
}


void CDialogTesting::OnBnClickedCheckTime()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	makeFileName();
}

void CDialogTesting::OnEnChangeEditBaseName()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CDialogEx::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
	makeFileName();
}

void CDialogTesting::makeFileName()
{
	if (m_ctrAutoGenerate.GetCheck())
	{
		CString strBase;
		m_ctrBaseFileName.GetWindowText(strBase);

		if (m_ctrTime.GetCheck()) strBase = CTime::GetCurrentTime().Format("%H:%M_") + strBase;
		if (m_ctrDate.GetCheck()) strBase = CTime::GetCurrentTime().Format("%Y%m%d_") + strBase;
		if (m_ctrAutoIndex.GetCheck())
		{
			strBase = strBase + L"_";
			int num = 1;
			CFileStatus fs;
			CString strNumbered;
			while (TRUE) {				
				strNumbered.Format(strBase + L"%03d", num);
				CString strTemp;
				GetDlgItem(IDC_EDIT_SAVE_PATH)->GetWindowText(strTemp);
				strTemp += L"\\" + strNumbered + L".log";
				if (CFile::GetStatus(strTemp, fs)) num++;
				else break;
			}
			strBase = strNumbered;
		}
		m_ctrSaveFileName.SetWindowTextW(strBase);
	}
}





void CDialogTesting::OnBnClickedButtonStart()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	if (d_pParent->m_testMode) // 강제종료
	{
		m_ctrCmbModeSelect.EnableWindow(TRUE);
		m_ctrCmbSearchingAlgorithms.EnableWindow(TRUE);
		m_ctrCmbTestingEyes.EnableWindow(TRUE);
		m_ctrDone.EnableWindow(FALSE);
		m_ctrReset.EnableWindow(FALSE);
		m_ctrYes.EnableWindow(FALSE);
		m_ctrNo.EnableWindow(FALSE);

		m_ctrExperimentStart.SetWindowText(L"Experiment Start");

		d_pParent->m_testMode = FALSE;
	}
	else // 실험 시작
	{
		m_ctrCmbModeSelect.EnableWindow(FALSE);
		m_ctrCmbSearchingAlgorithms.EnableWindow(FALSE);
		m_ctrCmbTestingEyes.EnableWindow(FALSE);
		m_ctrDone.EnableWindow(TRUE);
		m_ctrReset.EnableWindow(TRUE);

		m_ctrExperimentStart.SetWindowText(L"Force Stop (Cancel)");

		d_pParent->m_testMode = TRUE;

		if (m_ctrCmbModeSelect.GetCurSel()==2)
		{
			m_ctrYes.EnableWindow(TRUE);
			m_ctrNo.EnableWindow(TRUE);
		}

		/*
		while (true)
		{

		}*/
	}
	
}


void CDialogTesting::OnBnClickedButtonConfiguration()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CDialogTestConfigure cfgDlg;
	cfgDlg.DoModal();
}


void CDialogTesting::OnBnClickedButtonYes()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void CDialogTesting::OnBnClickedButtonNo()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void CDialogTesting::OnBnClickedButtonReset()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void CDialogTesting::OnBnClickedButtonDone()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}
