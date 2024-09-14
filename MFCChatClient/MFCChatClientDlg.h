﻿
// MFCChatClientDlg.h: 头文件
//

#pragma once
#include "CMySocket.h"

// CMFCChatClientDlg 对话框
class CMFCChatClientDlg : public CDialogEx
{
// 构造
public:
	CMFCChatClientDlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCCHATCLIENT_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnClickedConnectBtn();
	afx_msg void OnClickedClearmsgBtn();
	afx_msg void OnClickedDisconnectBtn();

	CMySocket* m_client;
	CListBox m_list;
	CTime m_time;  // 实时时间

	CEdit m_input;
	afx_msg void OnClickedSendBtn();
};
