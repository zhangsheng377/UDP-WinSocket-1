
// WinSocketʾ��1Dlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "WinSocketʾ��1.h"
#include "WinSocketʾ��1Dlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CWinSocketʾ��1Dlg �Ի���



CWinSocketʾ��1Dlg::CWinSocketʾ��1Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CWinSocketʾ��1Dlg::IDD, pParent)
	, m_ServerIP(_T(""))
	, m_ClientIP(_T(""))
	, m_ServerPort(0)
	, m_ClientPort(0)
	, m_SendData(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CWinSocketʾ��1Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_ServerIP);
	DDX_Text(pDX, IDC_EDIT3, m_ClientIP);
	DDX_Text(pDX, IDC_EDIT2, m_ServerPort);
	DDX_Text(pDX, IDC_EDIT4, m_ClientPort);
	DDX_Text(pDX, IDC_EDIT5, m_SendData);
}

BEGIN_MESSAGE_MAP(CWinSocketʾ��1Dlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_SEND, &CWinSocketʾ��1Dlg::OnBnClickedSend)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_STOP, &CWinSocketʾ��1Dlg::OnBnClickedStop)
END_MESSAGE_MAP()


// CWinSocketʾ��1Dlg ��Ϣ�������

BOOL CWinSocketʾ��1Dlg::OnInitDialog()
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

void CWinSocketʾ��1Dlg::OnPaint()
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
HCURSOR CWinSocketʾ��1Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CWinSocketʾ��1Dlg::OnBnClickedSend()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	UpdateData(true);
	if (m_sockSend.Create(m_ServerPort, SOCK_DGRAM, NULL))			//�����׽���
	{
		m_SendData.Format(L"");
		UpdateData(false);
		m_sockSend.Bind(m_ServerPort, m_ServerIP);					//�󶨱����׽���
		SetTimer(1, 2000, NULL);									//����һ����ʱ��
		GetDlgItem(IDC_SEND)->EnableWindow(false);					//���Ͱ�ť��Ч
		GetDlgItem(IDC_STOP)->EnableWindow(true);					//ֹͣ��ť��Ч
	}
	else
	{
		AfxMessageBox(L"Socket����ʧ��!");
	}
}


void CWinSocketʾ��1Dlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
	static int iIndex = 0;														//��̬����,���ڼ���
	char szSend[20];
	sprintf_s(szSend, "%010d", iIndex++);											//���͵��������뻺����
	int iSend = m_sockSend.SendTo(szSend, 10, m_ClientPort, m_ClientIP, 0);		//����UDP����
	TRACE("������ %d ���ֽ�\n", iSend);
	m_SendData.Format(L"������ %d ���ֽ�, %d", iSend, iIndex - 1);
	UpdateData(false);
	
	CDialogEx::OnTimer(nIDEvent);
}


void CWinSocketʾ��1Dlg::OnBnClickedStop()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	KillTimer(1);												//�����ʱ��
	m_sockSend.Close();											//�ر��׽���
	GetDlgItem(IDC_SEND)->EnableWindow(true);					//���Ͱ�ť��Ч
	GetDlgItem(IDC_STOP)->EnableWindow(false);					//ֹͣ��ť��Ч
}
