
// StockApp.h : PROJECT_NAME ���ε{�����D�n���Y��
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�� PCH �]�t���ɮ׫e���]�t 'stdafx.h'"
#endif

#include "resource.h"		// �D�n�Ÿ�


// CStockAppApp:
// �аѾ\��@�����O�� StockApp.cpp
//

class CStockAppApp : public CWinApp
{
public:
	CStockAppApp();

// �мg
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// �{���X��@

	DECLARE_MESSAGE_MAP()
};

extern CStockAppApp theApp;