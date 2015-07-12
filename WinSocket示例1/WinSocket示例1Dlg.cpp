
// WinSocket示例1Dlg.cpp : 实现文件
//

#include "stdafx.h"
#include "WinSocket示例1.h"
#include "WinSocket示例1Dlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CWinSocket示例1Dlg 对话框



CWinSocket示例1Dlg::CWinSocket示例1Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CWinSocket示例1Dlg::IDD, pParent)
	, m_ServerIP(_T(""))
	, m_ClientIP(_T(""))
	, m_ServerPort(0)
	, m_ClientPort(0)
	, m_SendData(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CWinSocket示例1Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_ServerIP);
	DDX_Text(pDX, IDC_EDIT3, m_ClientIP);
	DDX_Text(pDX, IDC_EDIT2, m_ServerPort);
	DDX_Text(pDX, IDC_EDIT4, m_ClientPort);
	DDX_Text(pDX, IDC_EDIT5, m_SendData);
}

BEGIN_MESSAGE_MAP(CWinSocket示例1Dlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_SEND, &CWinSocket示例1Dlg::OnBnClickedSend)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_STOP, &CWinSocket示例1Dlg::OnBnClickedStop)
END_MESSAGE_MAP()


// CWinSocket示例1Dlg 消息处理程序

BOOL CWinSocket示例1Dlg::OnInitDialog()
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

void CWinSocket示例1Dlg::OnPaint()
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
HCURSOR CWinSocket示例1Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CWinSocket示例1Dlg::OnBnClickedSend()
{
	// TODO:  在此添加控件通知处理程序代码
	UpdateData(true);
	if (m_sockSend.Create(m_ServerPort, SOCK_DGRAM, NULL))			//创建套接字
	{
		m_SendData.Format(L"");
		UpdateData(false);
		m_sockSend.Bind(m_ServerPort, m_ServerIP);					//绑定本地套接字
		SetTimer(1, 2000, NULL);									//创建一个定时器
		GetDlgItem(IDC_SEND)->EnableWindow(false);					//发送按钮无效
		GetDlgItem(IDC_STOP)->EnableWindow(true);					//停止按钮生效
	}
	else
	{
		AfxMessageBox(L"Socket创建失败!");
	}
}


void CWinSocket示例1Dlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值
	static int iIndex = 0;														//静态变量,用于计数
	char szSend[20];
	sprintf_s(szSend, "%010d", iIndex++);											//发送的数据置入缓冲区
	int iSend = m_sockSend.SendTo(szSend, 10, m_ClientPort, m_ClientIP, 0);		//发送UDP数据
	TRACE("发送了 %d 个字节\n", iSend);
	m_SendData.Format(L"发送了 %d 个字节, %d", iSend, iIndex - 1);
	UpdateData(false);
	
	CDialogEx::OnTimer(nIDEvent);
}


void CWinSocket示例1Dlg::OnBnClickedStop()
{
	// TODO:  在此添加控件通知处理程序代码
	KillTimer(1);												//清除定时器
	m_sockSend.Close();											//关闭套接字
	GetDlgItem(IDC_SEND)->EnableWindow(true);					//发送按钮生效
	GetDlgItem(IDC_STOP)->EnableWindow(false);					//停止按钮无效
}
