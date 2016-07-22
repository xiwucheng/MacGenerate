// MacGenerateDlg.cpp : implementation file
//

#include "stdafx.h"
#include "MacGenerate.h"
#include "MacGenerateDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMacGenerateDlg dialog




CMacGenerateDlg::CMacGenerateDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMacGenerateDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMacGenerateDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMacGenerateDlg, CDialog)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDOK, &CMacGenerateDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CMacGenerateDlg message handlers

BOOL CMacGenerateDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here

	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CMacGenerateDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CMacGenerateDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CMacGenerateDlg::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	CString str;
	GetDlgItemText(IDC_MAC,str);
	if (str.GetLength() != 12)
	{
		MessageBox("MAC地址位数错误，请输入12位十六进制数！","错误",MB_ICONERROR);
		return;
	}
	__int64 lMac = 0;
	sscanf(str,"%I64X",&lMac);
	CFile fp;
	fp.Open("mac.txt",CFile::modeCreate|CFile::modeWrite);
	int count = GetDlgItemInt(IDC_COUNT);
	for (int i=0;i<count;i++)
	{
		str.Format("%012I64X\r\n",lMac);
		fp.Write(str,str.GetLength());
		lMac++;
	}
	fp.Close();
	MessageBox("MAC地址已生成，请查看程序目录的文本文件！","MAC地址",MB_ICONINFORMATION);
	OnOK();
}

BOOL CMacGenerateDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: Add your specialized code here and/or call the base class
	CEdit* edit = (CEdit*)GetDlgItem(IDC_MAC);
	if (GetFocus() == edit && pMsg->message == WM_CHAR)
	{
		if ((pMsg->wParam <= '9' && pMsg->wParam >= '0') || 
			(pMsg->wParam <= 'F' && pMsg->wParam >= 'A') ||
			(pMsg->wParam <= 'f' && pMsg->wParam >= 'a') ||
			pMsg->wParam == VK_BACK)
		{
			return 0;
		}
		else
		{
			return 1;
		}
	}

	return CDialog::PreTranslateMessage(pMsg);
}
