﻿
// MFCChatServerDlg.h: 头文件
//

#pragma once
#include "CServerSocket.h"
#include "CChatSocket.h"

#define SEND_MAX_BUF 200


// CMFCChatServerDlg 对话框
class CMFCChatServerDlg : public CDialogEx
{
// 构造
public:
	CMFCChatServerDlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCCHATSERVER_DIALOG };
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
	afx_msg void OnCbnSelchangeColourCombo();
	afx_msg void OnClickedCalBtn();
	afx_msg void OnClickedMailBtn();
	afx_msg void OnClickedQqBtn();
	afx_msg void OnClickedSendBtn();
	afx_msg void OnClickedStartBtn();
	afx_msg void OnClickedStopBtn();
	CListBox m_list;
	CServerSocket* m_server;
	CChatSocket* m_chat;
	CString CatShowString(CString strInfo, CString strMsg);
	afx_msg void OnClickedClearBut();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	CComboBox m_FontColorCombo;
};
