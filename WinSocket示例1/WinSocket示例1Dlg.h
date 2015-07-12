
// WinSocketʾ��1Dlg.h : ͷ�ļ�
//

#pragma once


// CWinSocketʾ��1Dlg �Ի���
class CWinSocketʾ��1Dlg : public CDialogEx
{
// ����
public:
	CWinSocketʾ��1Dlg(CWnd* pParent = NULL);	// ��׼���캯��

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
	int m_ServerPort;
	int m_ClientPort;

	CAsyncSocket m_sockSend;
	afx_msg void OnBnClickedSend();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnBnClickedStop();
	CString m_SendData;
};
