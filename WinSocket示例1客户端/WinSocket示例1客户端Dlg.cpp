
// WinSocketʾ��1�ͻ���Dlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "WinSocketʾ��1�ͻ���.h"
#include "WinSocketʾ��1�ͻ���Dlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CWinSocketʾ��1�ͻ���Dlg �Ի���



CWinSocketʾ��1�ͻ���Dlg::CWinSocketʾ��1�ͻ���Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CWinSocketʾ��1�ͻ���Dlg::IDD, pParent)
	, m_ServerIP(_T(""))
	, m_ClientIP(_T(""))
	, m_ServerPort(0)
	, m_ClientPort(0)
	, m_ReceiveData(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CWinSocketʾ��1�ͻ���Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_ServerIP);
	DDX_Text(pDX, IDC_EDIT3, m_ClientIP);
	DDX_Text(pDX, IDC_EDIT2, m_ServerPort);
	DDX_Text(pDX, IDC_EDIT4, m_ClientPort);
	DDX_Text(pDX, IDC_EDIT5, m_ReceiveData);
}

BEGIN_MESSAGE_MAP(CWinSocketʾ��1�ͻ���Dlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_RECEIVE, &CWinSocketʾ��1�ͻ���Dlg::OnBnClickedReceive)
	ON_BN_CLICKED(IDC_STOP, &CWinSocketʾ��1�ͻ���Dlg::OnBnClickedStop)
	ON_WM_TIMER()
END_MESSAGE_MAP()


// CWinSocketʾ��1�ͻ���Dlg ��Ϣ�������

BOOL CWinSocketʾ��1�ͻ���Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO:  �ڴ���Ӷ���ĳ�ʼ������

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CWinSocketʾ��1�ͻ���Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CWinSocketʾ��1�ͻ���Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CWinSocketʾ��1�ͻ���Dlg::OnBnClickedReceive()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	UpdateData(true);
	if (m_sockReceive.Create(m_ClientPort, SOCK_DGRAM, NULL))
	{
		m_ReceiveData = "����receive";
		UpdateData(false);
		m_sockReceive.Bind(m_ClientPort, m_ClientIP);
		SetTimer(1, 2000, NULL);
		GetDlgItem(IDC_RECEIVE)->EnableWindow(false);
		GetDlgItem(IDC_STOP)->EnableWindow(true);
	}
	else
	{
		AfxMessageBox(L"Socket����ʧ��!");
	}
}







void CWinSocketʾ��1�ͻ���Dlg::OnBnClickedStop()
{
	KillTimer(1);
	m_sockReceive.Close();
	m_ReceiveData = "ֹͣ��������!";
	UpdateData(false);
	GetDlgItem(IDC_RECEIVE)->EnableWindow(true);
	GetDlgItem(IDC_STOP)->EnableWindow(false);
}

void CWinSocketʾ��1�ͻ���Dlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
	char szRecv[20];
	int iRecv = m_sockReceive.ReceiveFrom(szRecv, 10, m_ServerIP, m_ServerPort, 0);
	if (iRecv == -1)
	{
		m_ReceiveData = "û���յ�����!";
	}
	else
	{
		szRecv[iRecv] = NULL;
		m_ReceiveData = szRecv;
	}
	UpdateData(false);
	
	CDialogEx::OnTimer(nIDEvent);
}


void CWinSocketʾ��1�ͻ���Dlg::myReceive()
{
	
}
