
// WinSocketʾ��1�ͻ���Dlg.h : ͷ�ļ�
//

#pragma once


// CWinSocketʾ��1�ͻ���Dlg �Ի���
class CWinSocketʾ��1�ͻ���Dlg : public CDialogEx
{
// ����
public:
	CWinSocketʾ��1�ͻ���Dlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_WINSOCKET1_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CString m_ServerIP;
	CString m_ClientIP;
	UINT m_ServerPort;
	int m_ClientPort;

	CAsyncSocket m_sockReceive;
	afx_msg void OnBnClickedReceive();
	
	CString m_ReceiveData;
	afx_msg void OnBnClickedStop();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	void myReceive();
};
