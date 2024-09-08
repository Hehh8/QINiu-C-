
// MFCBasicPractice2.h: MFCBasicPractice2 应用程序的主头文件
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"       // 主符号


// CMFCBasicPractice2App:
// 有关此类的实现，请参阅 MFCBasicPractice2.cpp
//

class CMFCBasicPractice2App : public CWinAppEx
{
public:
	CMFCBasicPractice2App() noexcept;


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

extern CMFCBasicPractice2App theApp;
