
// WinSocketʾ��1�ͻ���.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CWinSocketʾ��1�ͻ���App: 
// �йش����ʵ�֣������ WinSocketʾ��1�ͻ���.cpp
//

class CWinSocketʾ��1�ͻ���App : public CWinApp
{
public:
	CWinSocketʾ��1�ͻ���App();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CWinSocketʾ��1�ͻ���App theApp;