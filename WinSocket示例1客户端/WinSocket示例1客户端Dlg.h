
// WinSocket示例1客户端Dlg.h : 头文件
//

#pragma once


// CWinSocket示例1客户端Dlg 对话框
class CWinSocket示例1客户端Dlg : public CDialogEx
{
// 构造
public:
	CWinSocket示例1客户端Dlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_WINSOCKET1_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
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
