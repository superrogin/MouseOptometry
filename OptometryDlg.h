// OptometryDlg.h : 헤더 파일
//

#pragma once
#include "afxwin.h"
#include "afxcmn.h"
#include "DialogCalibration.h"
#include "DialogCamera.h"
#include "DialogResult.h"
#include "DialogStimulus.h"
#include "DialogTesting.h"
#include "Screen.h"
#include "SampleScreen.h"
#include "CameraDialog.h"

// COptometryDlg 대화 상자
class COptometryDlg : public CDialogEx
{
// 생성입니다.
public:
	COptometryDlg(CWnd* pParent = NULL);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_MAIN };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnFileExit();
	CListBox m_mainList;
	CTabCtrl m_mainTab;
	CDialogStimulus m_tab1_stimulus;
	CDialogCamera m_tab2_camera;
	CDialogTesting m_tab3_testing;
	CDialogResult m_tab4_result;
	CDialogCalibration m_tab5_calibration;
	CCameraDialog m_dlgCamera;
	CWnd* m_mainTabNow;
	afx_msg void OnLbnSelchangeList1();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	bool m_threadStop;
	static UINT threadFunc1(LPVOID pParam);
	static UINT threadFunc2(LPVOID pParam);
	static UINT threadFunc3(LPVOID pParam);
	static UINT threadFunc4(LPVOID pParam);
	static UINT sampleThreadFunc(LPVOID pParam);
	CScreen* m_slitScreen[4];
	CWinThread* m_pThread[4];
	CSampleScreen* m_sampleScreen;
	CWinThread* m_sampleThread;
	afx_msg void OnViewShowvideo();
	afx_msg void OnFileOpencamera();
	afx_msg void OnFileOpenvideofile();
	void onThread(COptometryDlg* pDlg, int idx);
	void onSampleThread(COptometryDlg* pDlg);
	virtual void OnCancel();
	afx_msg void OnViewShowscreen();
	afx_msg void OnViewShowsamplescreen();
	byte m_isScreenOn;
	byte m_isSampleOn;
	byte m_isCameraOn;
	int m_testMode;
	int m_calX;
	int m_calY;
	int m_calDiameter;
	double m_footholdDiameter;
	double m_stimulusX;
	double m_stimulusY;
	double m_monitorSize;
	double m_monitorPosition;
	afx_msg void OnPress1();
	afx_msg void OnPress2();
	afx_msg void OnPress3();
	afx_msg void OnPress4();
	HACCEL m_hAccelTable;
	int m_valueScreenMode;
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
};
