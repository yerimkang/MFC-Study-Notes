
// ExamEditDlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "ExamEdit.h"
#include "ExamEditDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CExamEditDlg 대화 상자



CExamEditDlg::CExamEditDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_EXAMEDIT_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CExamEditDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CExamEditDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_READ_BTN, &CExamEditDlg::OnBnClickedReadBtn)
	ON_BN_CLICKED(IDC_WRITE_BTN, &CExamEditDlg::OnBnClickedWriteBtn)
END_MESSAGE_MAP()


// CExamEditDlg 메시지 처리기

BOOL CExamEditDlg::OnInitDialog()
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

void CExamEditDlg::OnPaint()
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
HCURSOR CExamEditDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CExamEditDlg::OnBnClickedReadBtn()
{
	wchar_t strA[24];

	CString str;
	//int len = GetDlgItemText(IDC_EDIT1, str); //str에 저장, len에 크기 저장 GetDlgItemInt => 정수가능
	GetDlgItemText(IDC_EDIT1, strA, 24);

	CWnd* p = GetDlgItem(IDC_EDIT1);
	int len = p->SendMessage(WM_GETTEXTLENGTH);

	//int len = GetDlgItem(IDC_EDIT1)->GetWindowTextLengthW();
	//GetWindowTextLength() = 큰범위 / SendMessage() = 작은범위

	if (len > 3) {
		AfxMessageBox(L"너무 길게 입력했습니다!");
	}
	else {
		wchar_t str[4];
		GetDlgItemText(IDC_EDIT1, str, 4);
		AfxMessageBox(str);
	}
	//CEdit* p_edit = (CEdit *)p;

	//CEdit* p_edit = (CEdit *)GetDlgItem(IDC_EDIT1); //읽기전용 등등
}


void CExamEditDlg::OnBnClickedWriteBtn()
{
	SetDlgItemText(IDC_EDIT1, L"tipsware"); //굉장히 효율적이고 간단하게 사용 가능
}

