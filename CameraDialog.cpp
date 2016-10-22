// CameraDialog.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "MouseOptometry.h"
#include "CameraDialog.h"
#include "afxdialogex.h"
#include "OptometryDlg.h"

#define d_pParent ((COptometryDlg*)AfxGetMainWnd())

// CCameraDialog 대화 상자입니다.

IMPLEMENT_DYNAMIC(CCameraDialog, CDialogEx)

CCameraDialog::CCameraDialog(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG_CAMERA, pParent)
{
	m_headingAngle = 0.0;
	m_headX = 0;
	m_headY = 0;
	m_zoom = 1.0;
	m_isVideo = TRUE;
}

CCameraDialog::~CCameraDialog()
{
}

void CCameraDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CCameraDialog, CDialogEx)
	ON_WM_TIMER()
	ON_WM_DESTROY()
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()


// CCameraDialog 메시지 처리기입니다.


void CCameraDialog::displayImage(Mat* image, CDC* pDC)
{
	RECT rect;
	pDC->GetWindow()->GetClientRect(&rect);
	Size winSize(rect.right, rect.bottom);

	Mat matTmp;

	int padding = 0;
	if (image->type() != CV_8UC4) padding = 4 - (image->cols % 4);
	if (padding == 4) padding = 0;
	if (padding > 0 || image->isContinuous() == false)	cv::copyMakeBorder(*image, matTmp, 0, 0, 0, padding, cv::BORDER_CONSTANT, 0);
	else matTmp = image->clone();

	BITMAPINFO bitmapInfo;
	memset(&bitmapInfo, 0, sizeof(bitmapInfo));
	bitmapInfo.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	bitmapInfo.bmiHeader.biPlanes = 1;
	bitmapInfo.bmiHeader.biCompression = BI_RGB;
	bitmapInfo.bmiHeader.biWidth = matTmp.cols;
	bitmapInfo.bmiHeader.biHeight = -matTmp.rows;
	IplImage *dspImage = cvCloneImage(&IplImage(matTmp));

	bitmapInfo.bmiHeader.biBitCount = dspImage->depth * dspImage->nChannels;

	pDC->SetStretchBltMode(COLORONCOLOR);
	::StretchDIBits(pDC->GetSafeHdc(), rect.left, rect.top,
		rect.right, rect.bottom,
		0, 0, dspImage->width, dspImage->height,
		dspImage->imageData, &bitmapInfo, DIB_RGB_COLORS, SRCCOPY);

	ReleaseDC(pDC);
	matTmp.release();
	cvReleaseImage(&dspImage);
}

void CCameraDialog::openCamera()
{
	if (m_isVideo)
	{
		KillTimer(1394);
		m_capture.release();
		m_capture = VideoCapture(0);
		if (m_capture.isOpened()) setCameraFPS(1);
		else AfxMessageBox(_T("Camera open failed"));
		m_isVideo = FALSE;
	}
}


void CCameraDialog::openVideoFile()
{
	CFileDialog dlg(TRUE, NULL, NULL, OFN_HIDEREADONLY, _T("Video Files(*.avi, *.mp4, ...) | *.avi;*.mp4;*.mov;*.wmv | All Files(*.*)|*.*||"));
	if (IDOK == dlg.DoModal()) {
		m_isVideo = TRUE;
		KillTimer(1394);
		m_capture.release();
		m_strPath = CT2CA(dlg.GetPathName().GetString());
		m_capture = VideoCapture(m_strPath);
		if (m_capture.isOpened()) setCameraFPS(1);
		else AfxMessageBox(_T("File open failed"));
	}
}


void CCameraDialog::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	switch (nIDEvent)
	{
	case 1394:
		CDC *pDC = GetDlgItem(IDC_MAIN_PIC)->GetDC();
		Mat grab;
		m_capture >> grab;
		if (grab.empty()) {
			KillTimer(1394);
			AfxMessageBox(_T("Video End!"));
			KillTimer(1394);
		}
		else {

			if (d_pParent->m_testMode)
			{
				if (!m_isExperimentStarted)
				{
					m_prevMc.x = 0;
					m_prevMc.y = 0;
					m_prevPntNose.x = 1;
					m_prevPntNose.y = 1;
				}
				bool isRecognized = FALSE;
				Scalar tempVal = mean(grab);
				int vals = (tempVal.val[0] + tempVal.val[1] + tempVal.val[2]) / 3;
				if (vals < 90) grab = 2 * grab;

				Mat grabGray;
				cvtColor(grab, grabGray, COLOR_BGR2GRAY);
				vector<Point2f> corners;

				inRange(grabGray, 0, 40, grabGray);

				blur(grabGray, grabGray, cv::Size(40.0, 40.0));
				inRange(grabGray, 128, 255, grabGray);

				//erode(grabGray, grabGray, Mat(), Point(-1, -1), 5, 1);
				//dilate(grabGray, grabGray, Mat(), Point(-1, -1), 8, 1);

				Mat tmpDisp = grabGray.clone();

				RNG rng(12345);

				std::vector< std::vector<cv::Point> > contours;
				vector<Vec4i> hierarchy;
				Mat tmp = grabGray.clone();
				findContours(tmp, contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE); // edited to change from CV_CHAIN_APPROX_SIMPLE

				int cmin = 100;  // 최소 외곽선 길이
				int cmax = 1000; // 최대 외곽선 길이
				std::vector<std::vector<cv::Point>>::const_iterator itc = contours.begin();
				while (itc != contours.end()) {
					if (itc->size() < cmin || itc->size() > cmax)
						itc = contours.erase(itc);
					else
						++itc;
				}


				Point2f mc,pntNose;

				//Recognition
				if (contours.size())
				{
					RotatedRect e;
					e = cv::fitEllipse(contours[0]);
					Scalar color = Scalar(255, 0, 0);
					//drawContours(grab, contours, 0, color, 2, 8, hierarchy, 0, Point());

					//ellipse(grab, e, cv::Scalar(0, 255, 0), 3);
					std::vector<cv::Point> pts;

					std::vector< std::vector<cv::Point> > cntrs;
					int i = 0;
					while (true)
					{
						Mat tmpCntrs = tmpDisp.clone();
						ellipse2Poly(e.center, Size(e.size.width / 2 + i, e.size.height / 2 + i), e.angle, 0, 360, 16, pts);
						fillConvexPoly(tmpCntrs, pts, Scalar(0, 0, 0), 8);
						findContours(tmpCntrs, cntrs, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE);
						if (cntrs.size() == 1 || cntrs.size() == 0) {
							tmpDisp = tmpCntrs.clone();
							break;
						}
						else i++;
					}
					if (cntrs.size())
					{
						if (contourArea(cntrs[0]))
						{
							Moments mu = moments(cntrs[0]);
							pntNose = Point2f(mu.m10 / mu.m00, mu.m01 / mu.m00);

							Mat msk = Mat::zeros(Size(tmpDisp.cols, tmpDisp.rows), CV_8UC1);
							circle(msk, pntNose, max(e.size.height, e.size.width) / 3, Scalar(255, 255, 255), -1);
							Mat tmpMsk;
							grabGray.copyTo(tmpMsk, msk);
							Mat tmpCntrs = tmpMsk.clone();
							findContours(tmpCntrs, cntrs, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE);

							if (contourArea(cntrs[0]))
							{
								isRecognized = TRUE;
								mu = moments(cntrs[0]);
								mc = Point2f(mu.m10 / mu.m00, mu.m01 / mu.m00);
							}
						}
					}
					else {
						Mat tmpCntrs = tmpDisp.clone();
						ellipse2Poly(e.center, Size(e.size.width / 2 + i - 1, e.size.height / 2 + i - 1), e.angle, 0, 360, 16, pts);
					}

					Point2f vertices[4];
					e.points(vertices);
					//line(grab, (vertices[0]+ vertices[1])/2, (vertices[2] + vertices[3]) / 2, Scalar(0, 0, 255),5);
					//line(grab, (vertices[0] + vertices[1]) - (vertices[2] + vertices[3]) / 2, (vertices[2] + vertices[3]) - (vertices[0] + vertices[1]) / 2, Scalar(0, 0, 255), 5);	
				}

				//
				if (!isRecognized)
				{
					mc = m_prevMc;
					pntNose = m_prevPntNose;
				}
				circle(grab, mc, 5, Scalar(0, 0, 255), -1);
				line(grab, mc, pntNose, Scalar(0, 0, 255), 2.5);

				if (d_pParent->m_tab3_testing.m_ctrTracking.GetCheck())
				{
					d_pParent->m_stimulusX = mc.x - grab.cols / 2;
					d_pParent->m_stimulusY = mc.y - grab.rows / 2;
				}
				double angVal = atan2(pntNose.y - mc.y, pntNose.x - mc.x) * 180 / M_PI;
			}
			else m_isExperimentStarted = FALSE;
			//imshow("gray", tmpDisp);

			// Calibration marker
			CButton* pCheck;
			pCheck = (CButton*)GetDlgItem(IDC_CHECK_CALIBRATION);
			if (pCheck->GetCheck())
			{
				double centerX = grab.cols / 2.0*d_pParent->m_calX / 1000.0;
				double centerY = grab.rows / 2.0*d_pParent->m_calY / 1000.0;
				Point2f markerCenter(centerX, centerY);
				circle(grab, markerCenter, d_pParent->m_calDiameter / 2.0, Scalar(0, 0, 255), 2);
				line(grab, Point(centerX, 0), Point(centerX, grab.rows), Scalar(0, 0, 255), 2.5);
				line(grab, Point(0, centerY), Point(grab.cols, centerY), Scalar(0, 0, 255), 2.5);
			}
			// Stimulus Marker
			pCheck = (CButton*)GetDlgItem(IDC_CHECK_STIMULUS);
			if (pCheck->GetCheck())
			{
				// Draw Marker
				int rValue = GetRValue(d_pParent->m_tab1_stimulus.m_markerColor);
				int gValue = GetGValue(d_pParent->m_tab1_stimulus.m_markerColor);
				int bValue = GetBValue(d_pParent->m_tab1_stimulus.m_markerColor);

				Mat stimMarker(grab.rows, grab.cols, CV_8UC3); //Stimulation Marker

				double centerX = d_pParent->m_stimulusX + 0.5*grab.cols;
				double centerY = d_pParent->m_stimulusY + 0.5*grab.rows;
				Point2f markerCenter(centerX, centerY);

				//circle(stimMarker, Point(, ), 25, Scalar(bValue, gValue, rValue), -1);
				int numCircle = (d_pParent->m_tab1_stimulus.m_markerQuality);
				int markerRadius = d_pParent->m_tab1_stimulus.m_markerRadius;

				double driftedTime = d_pParent->m_tab1_stimulus.m_driftSpeed * GetTickCount() * 0.0001;
				double spaFreq = d_pParent->m_tab1_stimulus.m_ctrCmbNumberMode.GetCurSel() == 0?d_pParent->m_tab1_stimulus.m_spatialFrequency:d_pParent->m_tab1_stimulus.m_numberMode;
				double pixelRatio = d_pParent->m_footholdDiameter / d_pParent->m_calDiameter;
				double finalX = pixelRatio*(-(d_pParent->m_calX - 1000) / 2000.0*d_pParent->m_dlgCamera.m_capture.get(CAP_PROP_FRAME_WIDTH) + d_pParent->m_stimulusX);
				double finalY = pixelRatio*((d_pParent->m_calY - 1000) / 2000.0*d_pParent->m_dlgCamera.m_capture.get(CAP_PROP_FRAME_HEIGHT) - d_pParent->m_stimulusY);
				for (int i = 0; i < numCircle; i++)
				{
					double partColor = 0.5*(sin(spaFreq * (2*M_PI*i/numCircle + driftedTime * M_PI / 180.0)) + 1);
					partColor = partColor < 0.05 ? 0.05 : partColor;
					ellipse(stimMarker, markerCenter, Size(markerRadius, markerRadius), 0, i * 360 / numCircle, (i + 1) * 360 / numCircle, partColor * Scalar(bValue, gValue, rValue), -1);
				}

				circle(stimMarker, markerCenter, 75, Scalar(0, 0, 0), -1);
				circle(stimMarker, markerCenter, 10, Scalar(bValue, gValue, rValue), -1);

				// Merge
				double alpha = 1 - d_pParent->m_tab1_stimulus.m_transparency/100.0;
				double beta = 1 - alpha;
				for (int j = 0; j < grab.rows; j++) {
					for (int i = 0; i < grab.cols; i++) {
						int pos = j * grab.cols * 3 + i * 3;
						if (stimMarker.data[pos] != 0 || stimMarker.data[pos + 1] != 0 || stimMarker.data[pos + 2] != 0)
						{
							double brightness = (stimMarker.data[pos] + stimMarker.data[pos + 1] + stimMarker.data[pos + 1])/3.0/256;
							
							for (int k = 0; k < 3; k++)
							{
								grab.data[pos + k] = beta*grab.data[pos + k] + alpha*stimMarker.data[pos + k];
							}
						}
					}
				}

			}
			// Magnification
			double roiX = (0.5 - 0.5 / m_zoom + (d_pParent->m_calX - 1000) / 2000.0)*grab.cols;
			double roiY = (0.5 - 0.5 / m_zoom + (d_pParent->m_calY - 1000) / 2000.0)*grab.rows;
			roiX = roiX > 0 ? roiX : 0;
			roiY = roiY > 0 ? roiY : 0;
			roiX = roiX + grab.cols / m_zoom < grab.cols ? roiX : grab.cols*(1.0 - 1.0 / m_zoom);
			roiY = roiY + grab.rows / m_zoom < grab.rows ? roiY : grab.rows*(1.0 - 1.0 / m_zoom);
			Rect zoomROI(roiX, roiY, grab.cols / m_zoom, grab.rows / m_zoom);
			grab = grab(zoomROI);
			displayImage(&grab, pDC);
		}
		break;
	}

	CDialogEx::OnTimer(nIDEvent);
}

void CCameraDialog::OnCancel()
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	//KillTimer(1394);
	//m_capture.release();

	ShowWindow(SW_HIDE);

	//CDialogEx::OnCancel();
}


void CCameraDialog::setCameraFPS(int frameRateMode)
{
	if (frameRateMode)
	{
		int fps = 30;
		SetTimer(1394, 1000.0 / fps * frameRateMode, NULL);
	}
}


BOOL CCameraDialog::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.

	CButton* pCheck;

	pCheck = (CButton*)GetDlgItem(IDC_CHECK_CALIBRATION);
	pCheck->SetBitmap(LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_BITMAP_CALIBRATION_MARKER)));
	pCheck->SetCheck(TRUE);

	pCheck = (CButton*)GetDlgItem(IDC_CHECK_STIMULUS);
	pCheck->SetBitmap(LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_BITMAP_STIMULUS_MARKER)));
	pCheck->SetCheck(TRUE);

	CRect mainRc, thisRc;
	AfxGetMainWnd()->GetWindowRect(&mainRc);
	GetWindowRect(&thisRc);
	SetWindowPos(NULL, mainRc.left - thisRc.right + thisRc.left, mainRc.top, 0, 0, SWP_NOSIZE);


	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


void CCameraDialog::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	CRect rt;
	((CStatic*)GetDlgItem(IDC_MAIN_PIC))->GetWindowRect(&rt);

	ScreenToClient(&rt);

	if (rt.PtInRect(point)) // 픽쳐 컨트롤의 사각형 영역에 마우스 클릭 좌표(point) 가 있으면...TRUE
	{
		d_pParent->m_stimulusX = ((point.x - rt.left) / (double)(rt.right - rt.left) - 0.5) * m_capture.get(CAP_PROP_FRAME_WIDTH);
		d_pParent->m_stimulusY = ((point.y - rt.top) / (double)(rt.bottom - rt.top) - 0.5) * m_capture.get(CAP_PROP_FRAME_HEIGHT);

	}

	CDialogEx::OnLButtonDown(nFlags, point);
}
