
// MFC-BasicPractice1.h: MFC-BasicPractice1 应用程序的主头文件
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"       // 主符号


// CMFCBasicPractice1App:
// 有关此类的实现，请参阅 MFC-BasicPractice1.cpp
//

class CMFCBasicPractice1App : public CWinAppEx
{
public:
	CMFCBasicPractice1App() noexcept;


// 重写
public:
	virtual BOOL InitInstance();

// 实现
	UINT  m_nAppLook;
	BOOL  m_bHiColorIcons;

	virtual void PreLoadState();
	virtual void LoadCustomState();
	virtual void SaveCustomState();

	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CMFCBasicPractice1App theApp;
