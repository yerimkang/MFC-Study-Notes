
// ExamMFCDlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "ExamMFC.h"
#include "ExamMFCDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CExamMFCDlg 대화 상자



CExamMFCDlg::CExamMFCDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_EXAMMFC_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CExamMFCDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CExamMFCDlg, CDialogEx) //어려운거
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_LBUTTONDOWN() //추가
	ON_BN_CLICKED(IDC_BUTTON, &CExamMFCDlg::OnBnClickedButton)
END_MESSAGE_MAP()


// CExamMFCDlg 메시지 처리기

BOOL CExamMFCDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 애플리케이션의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CExamMFCDlg::OnPaint()
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
HCURSOR CExamMFCDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


/*
LRESULT CExamMFCDlg::WindowProc(UINT message, WPARAM wParam, LPARAM lParam)
{
	//왼쪽 마우스를 누르면 사각형을 만들고 싶다
	if (message == WM_LBUTTONDOWN) {
		CClientDC dc(this);  //클라이언트 영역

		int x = LOWORD(lParam); // 하위 16비트 값 분리
		int y = HIWORD(lParam); // 상위 16비트 값 분리


		//컨트롤키 누르고 우클릭 -> wParam / lparam이 더 어렵다.
		if (wParam & MK_CONTROL) dc.Ellipse(x - 30, y - 30, x + 30, y + 30);
		else dc.Rectangle(x - 30, y - 30, x + 30, y + 30);

		
		//Win32
		HDC h_dc = ::GetDC(m_hWnd);
		Rectangle(h_dc, 10, 10, 100, 100);
		::ReleaseDC(m_hWnd, h_dc);

		//MFC기본코드!
		//CDC *p_dc = GetDC();//CDC = MFC를 총괄하는 제일 상위단 클래스
		//p_dc->Rectangle(10, 10, 100, 100); //핸들이 안넘어간다.
		//ReleaseDC(p_dc);
	}

	return CDialogEx::WindowProc(message, wParam, lParam);
}
*/


void CExamMFCDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	//point.x, point.y
	CClientDC dc(this);  //클라이언트 영역
	
	//컨트롤키 누르고 우클릭 -> wParam / lparam이 더 어렵다.
	if (nFlags & MK_CONTROL) dc.Ellipse(point.x - 30, point.y - 30, point.x + 30, point.y + 30);
	else dc.Rectangle(point.x - 30, point.y - 30, point.x + 30, point.y + 30);
	
	CDialogEx::OnLButtonDown(nFlags, point);
}


void CExamMFCDlg::OnBnClickedButton()
{
	// 문자를 읽어와야함 -> wchar_t str[64]; / CString str; 을 사용하게 되면 숫자를 적지 않아도 된다.
	CString str, show_str;

	GetDlgItemText(IDC_INPUT_MSG_EDIT, str); //대화상자 : Dlg 
	show_str.Format(L"사용자가 입력한 문자열 : %s", str);
	//show_str = L"사용자가 입력한 문자열 : " + str;

	AfxMessageBox(show_str);
}
