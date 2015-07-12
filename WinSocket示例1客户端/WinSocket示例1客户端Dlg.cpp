
// WinSocket示例1客户端Dlg.cpp : 实现文件
//

#include "stdafx.h"
#include "WinSocket示例1客户端.h"
#include "WinSocket示例1客户端Dlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CWinSocket示例1客户端Dlg 对话框



CWinSocket示例1客户端Dlg::CWinSocket示例1客户端Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CWinSocket示例1客户端Dlg::IDD, pParent)
	, m_ServerIP(_T(""))
	, m_ClientIP(_T(""))
	, m_ServerPort(0)
	, m_ClientPort(0)
	, m_ReceiveData(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CWinSocket示例1客户端Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_ServerIP);
	DDX_Text(pDX, IDC_EDIT3, m_ClientIP);
	DDX_Text(pDX, IDC_EDIT2, m_ServerPort);
	DDX_Text(pDX, IDC_EDIT4, m_ClientPort);
	DDX_Text(pDX, IDC_EDIT5, m_ReceiveData);
}

BEGIN_MESSAGE_MAP(CWinSocket示例1客户端Dlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_RECEIVE, &CWinSocket示例1客户端Dlg::OnBnClickedReceive)
	ON_BN_CLICKED(IDC_STOP, &CWinSocket示例1客户端Dlg::OnBnClickedStop)
	ON_WM_TIMER()
END_MESSAGE_MAP()


// CWinSocket示例1客户端Dlg 消息处理程序

BOOL CWinSocket示例1客户端Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO:  在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CWinSocket示例1客户端Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CWinSocket示例1客户端Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CWinSocket示例1客户端Dlg::OnBnClickedReceive()
{
	// TODO:  在此添加控件通知处理程序代码
	UpdateData(true);
	if (m_sockReceive.Create(m_ClientPort, SOCK_DGRAM, NULL))
	{
		m_ReceiveData = "进入receive";
		UpdateData(false);
		m_sockReceive.Bind(m_ClientPort, m_ClientIP);
		SetTimer(1, 2000, NULL);
		GetDlgItem(IDC_RECEIVE)->EnableWindow(false);
		GetDlgItem(IDC_STOP)->EnableWindow(true);
	}
	else
	{
		AfxMessageBox(L"Socket创建失败!");
	}
}







void CWinSocket示例1客户端Dlg::OnBnClickedStop()
{
	KillTimer(1);
	m_sockReceive.Close();
	m_ReceiveData = "停止接收数据!";
	UpdateData(false);
	GetDlgItem(IDC_RECEIVE)->EnableWindow(true);
	GetDlgItem(IDC_STOP)->EnableWindow(false);
}

void CWinSocket示例1客户端Dlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值
	char szRecv[20];
	int iRecv = m_sockReceive.ReceiveFrom(szRecv, 10, m_ServerIP, m_ServerPort, 0);
	if (iRecv == -1)
	{
		m_ReceiveData = "没有收到数据!";
	}
	else
	{
		szRecv[iRecv] = NULL;
		m_ReceiveData = szRecv;
	}
	UpdateData(false);
	
	CDialogEx::OnTimer(nIDEvent);
}


void CWinSocket示例1客户端Dlg::myReceive()
{
	
}
