#pragma once


// CScreen ��ȭ �����Դϴ�.

class CScreen : public CDialogEx
{
	DECLARE_DYNAMIC(CScreen)

public:
	CScreen(int i, CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CScreen();

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_SCREEN };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

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
