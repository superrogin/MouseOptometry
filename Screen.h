#pragma once


// CScreen 대화 상자입니다.

class CScreen : public CDialogEx
{
	DECLARE_DYNAMIC(CScreen)

public:
	CScreen(int i, CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CScreen();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_SCREEN };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	int monNum;
	void bufferedDraw(double driftedTime, int drawWidth, double centerX, double centerY, double spaFreq, double contrast, double monSize, double monPos);
	int screenWidth;
	int screenHeight;
	void drawSlit(RGBQUAD* pRgb, int i, double mx, double my, double driftedTime, double spaFreq, double contrast);
	virtual void OnCancel();
	void constantDraw(unsigned char brightness);
	afx_msg void OnPress1();
	afx_msg void OnPress2();
	afx_msg void OnPress3();
	afx_msg void OnPress4();
	HACCEL m_hAccelTable;
	virtual BOOL PreTranslateMessage(MSG* pMsg);
};
