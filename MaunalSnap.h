
// MaunalSnap.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CMaunalSnapApp: 
// �йش����ʵ�֣������ MaunalSnap.cpp
//

class CMaunalSnapApp : public CWinApp
{
public:
	CMaunalSnapApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CMaunalSnapApp theApp;