
// WinSocketʾ��1.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CWinSocketʾ��1App: 
// �йش����ʵ�֣������ WinSocketʾ��1.cpp
//

class CWinSocketʾ��1App : public CWinApp
{
public:
	CWinSocketʾ��1App();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CWinSocketʾ��1App theApp;