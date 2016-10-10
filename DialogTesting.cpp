// DialogTesting.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "MouseOptometry.h"
#include "DialogTesting.h"
#include "afxdialogex.h"
#include "OptometryDlg.h"

#define d_pParent ((COptometryDlg*)AfxGetMainWnd())

// CDialogTesting ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(CDialogTesting, CDialogEx)

CDialogTesting::CDialogTesting(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_TAB_TESTING, pParent)
{
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
	DDX_Control(pDX, IDC_EDIT_SAVE_NAME2, m_ctrBaseFileName);
}


BEGIN_MESSAGE_MAP(CDialogTesting, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_BROWSE, &CDialogTesting::OnBnClickedButtonBrowse)
	ON_BN_CLICKED(IDC_CHECK_AUTO_GENERATE, &CDialogTesting::OnBnClickedCheckAutoGenerate)
	ON_BN_CLICKED(IDC_CHECK_AUTO_INDEX, &CDialogTesting::OnBnClickedCheckAutoIndex)
	ON_BN_CLICKED(IDC_CHECK_DATE, &CDialogTesting::OnBnClickedCheckDate)
	ON_BN_CLICKED(IDC_CHECK_TIME, &CDialogTesting::OnBnClickedCheckTime)
	ON_EN_CHANGE(IDC_EDIT_BASE_NAME, &CDialogTesting::OnEnChangeEditBaseName)
END_MESSAGE_MAP()


// CDialogTesting �޽��� ó�����Դϴ�.


BOOL CDialogTesting::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.

	HFONT hNewFont;
	hNewFont = CreateFont(20, 0, 0, 0, 0, 0, 0, 0, HANGEUL_CHARSET, 3, 2, 1, VARIABLE_PITCH | FF_MODERN, _T("���� ���"));
	GetDlgItem(IDC_BUTTON_START)->SendMessage(WM_SETFONT, (WPARAM)hNewFont, (LPARAM)FALSE);
	GetDlgItem(IDC_COMBO_MODE_SELECT)->SendMessage(WM_SETFONT, (WPARAM)hNewFont, (LPARAM)FALSE);

	m_ctrCmbModeSelect.AddString(L"Auto");
	m_ctrCmbModeSelect.AddString(L"Auto+MANUAL");
	m_ctrCmbModeSelect.AddString(L"MANUAL");
	m_ctrCmbModeSelect.SelectString(-1, L"Auto");

	TCHAR initialPath[_MAX_PATH];
	GetModuleFileName(NULL, initialPath, sizeof initialPath);

	CString strPath = initialPath;
	int i = strPath.ReverseFind('\\');//���� ���� �̸��� ����� ���ؼ� ���ʿ� �ִ� '/'�� ã�´�.
	strPath = strPath.Left(i);

	GetDlgItem(IDC_EDIT_SAVE_PATH)->SetWindowText(strPath);

	m_ctrAutoGenerate.SetCheck(TRUE);
	m_ctrBaseFileName.SetWindowTextW(L"Experiment");
	m_ctrDate.SetCheck(TRUE);
	m_ctrAutoIndex.SetCheck(TRUE);
	makeFileName();

	return TRUE;  // return TRUE unless you set the focus to a control
				  // ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
}

int CALLBACK BrowseCallbackProc(HWND hwnd, UINT uMsg, LPARAM lParam, LPARAM lpData)
{
	switch (uMsg) {
		// �������� ���̾�α��� �ʱ�ȭ�� ���� ���
	case BFFM_INITIALIZED:
		SendMessage(hwnd, BFFM_SETSELECTION, TRUE, lpData);
		break;
	}
	return 0;
}

void CDialogTesting::OnBnClickedButtonBrowse()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.

	ITEMIDLIST  *pidlBrowse;
    WCHAR       pszPathname[MAX_PATH];
 
    BROWSEINFO  BrInfo;
    BrInfo.hwndOwner = GetSafeHwnd();
    BrInfo.pidlRoot = NULL;
 
    memset(&BrInfo, 0x00, sizeof(BrInfo));
    BrInfo.pszDisplayName = pszPathname;
    BrInfo.lpszTitle = _T("Select folder");
    BrInfo.ulFlags = BIF_RETURNONLYFSDIRS| BIF_USENEWUI;
 
    // �̺�Ʈ�� ���� ��������� �Լ�
    BrInfo.lpfn = BrowseCallbackProc;
 
    // ��������� �Լ��� �Ѱ��� ���ڷ� ����ڰ� �����ϰ��� �ϴ� ��θ� �����Ѵ�.
    // ������� �ʱ�������θ� C����̺�� �����ϴ� ���
	CString strInitPath;
	GetDlgItem(IDC_EDIT_SAVE_PATH)->GetWindowText(strInitPath);
    BrInfo.lParam = (LPARAM)strInitPath.GetBuffer();
 
    pidlBrowse = ::SHBrowseForFolder(&BrInfo);
    if(pidlBrowse != NULL)
    {
        // ���õ� ���� ��ξ���
        SHGetPathFromIDList(pidlBrowse, pszPathname);
         
        // ���(pszPathname)�� �̿��Ͽ� �����۾� �߰�
		GetDlgItem(IDC_EDIT_SAVE_PATH)->SetWindowText(pszPathname);
    }
}



void CDialogTesting::OnBnClickedCheckAutoGenerate()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
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
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	makeFileName();
}


void CDialogTesting::OnBnClickedCheckDate()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	makeFileName();
}


void CDialogTesting::OnBnClickedCheckTime()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	makeFileName();
}

void CDialogTesting::OnEnChangeEditBaseName()
{
	// TODO:  RICHEDIT ��Ʈ���� ���, �� ��Ʈ����
	// CDialogEx::OnInitDialog() �Լ��� ������ 
	//�ϰ� ����ũ�� OR �����Ͽ� ������ ENM_CHANGE �÷��׸� �����Ͽ� CRichEditCtrl().SetEventMask()�� ȣ������ ������
	// �� �˸� �޽����� ������ �ʽ��ϴ�.

	// TODO:  ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
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



