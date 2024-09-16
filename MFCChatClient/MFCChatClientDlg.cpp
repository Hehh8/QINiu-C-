﻿
// MFCChatClientDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "MFCChatClient.h"
#include "MFCChatClientDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CMFCChatClientDlg 对话框



CMFCChatClientDlg::CMFCChatClientDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCCHATCLIENT_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCChatClientDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_MSG_LIST, m_list);
	DDX_Control(pDX, IDC_SENDMSG_EDIT, m_input);
	DDX_Control(pDX, IDC_COLOUR_COMBO, m_FontColorCombo);
}

BEGIN_MESSAGE_MAP(CMFCChatClientDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_CONNECT_BTN, &CMFCChatClientDlg::OnClickedConnectBtn)
	ON_BN_CLICKED(IDC_CLEARMSG_BTN, &CMFCChatClientDlg::OnClickedClearmsgBtn)
	ON_BN_CLICKED(IDC_DISCONNECT_BTN, &CMFCChatClientDlg::OnClickedDisconnectBtn)
	ON_BN_CLICKED(IDC_SEND_BTN, &CMFCChatClientDlg::OnClickedSendBtn)
	ON_BN_CLICKED(IDC_SAVENAME_BTN, &CMFCChatClientDlg::OnClickedSavenameBtn)
	ON_BN_CLICKED(IDC_AUTOSEND_CHECK, &CMFCChatClientDlg::OnClickedAutosendCheck)
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// CMFCChatClientDlg 消息处理程序

BOOL CMFCChatClientDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	GetDlgItem(IDC_PORT_EDIT)->SetWindowText(_T("5000"));
	GetDlgItem(IDC_IPADDRESS)->SetWindowText(_T("127.0.0.1"));

	// 从配置文件获取昵称
	WCHAR wszName[MAX_PATH] = { 0 };
	WCHAR strPath[MAX_PATH] = { 0 };
	// 获取当前路径
	GetCurrentDirectory(MAX_PATH, strPath);
	TRACE("####strPath = %ls", strPath);
	CString strFilePath;
	strFilePath.Format(L"%ls//Test.ini", strPath);


	DWORD dwNum = GetPrivateProfileStringW(_T("CLIENT"), _T("NAME"), NULL, wszName, MAX_PATH, strFilePath);

	if (dwNum > 0)
	{
		TRACE("wszName = %ls", wszName);
		SetDlgItemText(IDC_NAME_EDIT, wszName);
		UpdateData(FALSE);
	}
	else
	{

		WritePrivateProfileStringW(_T("CLIENT"), _T("NAME"), L"客户端", strFilePath);
		SetDlgItemText(IDC_NAME_EDIT, L"客户端");
		UpdateData(FALSE);
	}
	GetDlgItem(IDC_DISCONNECT_BTN)->EnableWindow(FALSE);
	GetDlgItem(IDC_SEND_BTN)->EnableWindow(FALSE);
	GetDlgItem(IDC_CONNECT_BTN)->EnableWindow(TRUE);
	GetDlgItem(IDC_AUTOSEND_CHECK)->EnableWindow(FALSE);

	m_FontColorCombo.AddString(_T("黑色"));
	m_FontColorCombo.AddString(_T("红色"));
	m_FontColorCombo.AddString(_T("蓝色"));
	m_FontColorCombo.AddString(_T("绿色"));
	m_FontColorCombo.AddString(_T("紫色"));
	m_FontColorCombo.SetCurSel(0);
	SetDlgItemText(IDC_COLOUR_COMBO, _T("黑色"));

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CMFCChatClientDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CMFCChatClientDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CMFCChatClientDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMFCChatClientDlg::OnClickedConnectBtn()
{
	// TODO: 在此添加控件通知处理程序代码
	TRACE("####[ChatClient]Connent was clicked");
	GetDlgItem(IDC_CONNECT_BTN)->EnableWindow(FALSE);
	GetDlgItem(IDC_DISCONNECT_BTN)->EnableWindow(TRUE);
	GetDlgItem(IDC_SEND_BTN)->EnableWindow(TRUE);
	GetDlgItem(IDC_AUTOSEND_CHECK)->EnableWindow(TRUE);

	CString strPort, strIP;

	// 获取IP和端口
	GetDlgItem(IDC_PORT_EDIT)->GetWindowTextW(strPort);
	GetDlgItem(IDC_IPADDRESS)->GetWindowTextW(strIP);

	// CString转char *
	USES_CONVERSION;
	LPCSTR szPort = (LPCSTR)T2A(strPort);
	LPCSTR szIP = (LPCSTR)T2A(strIP);
	TRACE("####[ChatClient]szPort = %s, szIP = %s", szPort, szIP);

	// CString转int
	int iPort = _ttoi(strPort);

	// 创建一个socket对象
	m_client = new CMySocket;

	// 创建套接字
	if (!m_client->Create())
	{
		TRACE("m_client Create error %d", GetLastError());
		return;
	}
	else
	{
		TRACE("m_client Create success");
	}

	// 连接
	if (m_client->Connect(strIP, iPort) != SOCKET_ERROR)
	{
		TRACE("m_client Connect error %d", GetLastError());
		return;
	}
	
	

}


void CMFCChatClientDlg::OnClickedClearmsgBtn()
{
	// TODO: 在此添加控件通知处理程序代码
	m_list.ResetContent();
}


void CMFCChatClientDlg::OnClickedDisconnectBtn()
{
	// TODO: 在此添加控件通知处理程序代码

	// 1.控制控件
	TRACE("####[ChatClient]OnClickedDisconnectBtn");
	GetDlgItem(IDC_CONNECT_BTN)->EnableWindow(TRUE);
	GetDlgItem(IDC_DISCONNECT_BTN)->EnableWindow(FALSE);
	GetDlgItem(IDC_SEND_BTN)->EnableWindow(FALSE);
	GetDlgItem(IDC_AUTOSEND_CHECK)->EnableWindow(FALSE);

	// 2.回收资源
	m_client->Close();
	if (m_client != NULL)
	{
		delete m_client;
		m_client = NULL;
	}

	// 3.显示到列表框
	CString strShow;
	CString strInfo = _T("");
	CString strMsg = _T("断开与服务器的连接");
	strShow = CatShowString(strInfo, strMsg);
	m_list.AddString(FALSE);
	m_list.UpdateData(FALSE);
}


void CMFCChatClientDlg::OnClickedSendBtn()
{
	// TODO: 在此添加控件通知处理程序代码
	// 获取编辑框内容
	CString strMsg = _T("");
	GetDlgItem(IDC_SENDMSG_EDIT)->GetWindowText(strMsg);

	CString strName;
	GetDlgItem(IDC_NAME_EDIT)->GetWindowTextW(strName);

	strMsg = strName + _T(":") + strMsg;

	USES_CONVERSION;
	char* szSendBuf = T2A(strMsg);

	// 发送给服务端
	m_client->Send(szSendBuf, SEND_MAX_BUF, 0);

	// 显示到列表框
	CString strShow;
	CString strInfo = _T("");
	

	strShow = CatShowString(strInfo, strMsg);
	
	m_list.AddString(strShow);
	m_list.UpdateData(FALSE);

	// 清空编辑框
	GetDlgItem(IDC_SENDMSG_EDIT)->SetWindowTextW(_T(""));
}

CString CMFCChatClientDlg::CatShowString(CString strInfo, CString strMsg)
{
	// 时间 + 昵称 + 消息
	CString strTime;
	CTime timeNow;
	timeNow = CTime::GetCurrentTime();
	strTime = timeNow.Format("%X ");

	CString strShow;
	strShow = strTime + strShow;
	strShow += strInfo;
	strShow += strMsg;

	return strShow;
}


void CMFCChatClientDlg::OnClickedSavenameBtn()
{
	// TODO: 在此添加控件通知处理程序代码
	CString strName;
	GetDlgItemText(IDC_NAME_EDIT, strName);
	if (strName.GetLength() <= 0)
	{
		MessageBox(L"昵称不能为空");
		return;
	}
	if (IDOK == AfxMessageBox(_T("真的要修改昵称吗?"), MB_OKCANCEL))
	{
		WCHAR strPath[MAX_PATH] = { 0 };
		// 获取当前路径
		GetCurrentDirectory(MAX_PATH, strPath);
		TRACE("####strPath = %ls", strPath);

		CString strFilePath;
		strFilePath.Format(L"%ls//Test.ini", strPath);

		WritePrivateProfileStringW(_T("CLIENT"), _T("NAME"), strName, strFilePath);
	}
	
		
}


void CMFCChatClientDlg::OnClickedAutosendCheck()
{
	// TODO: 在此添加控件通知处理程序代码
	if (((CButton*)GetDlgItem(IDC_AUTOSEND_CHECK))->GetCheck())
	{
		TRACE("选中");
		((CButton*)GetDlgItem(IDC_AUTOSEND_CHECK))->SetCheck(FALSE);
	}
	else
	{
		TRACE("不选中");
		((CButton*)GetDlgItem(IDC_AUTOSEND_CHECK))->SetCheck(TRUE);
	}
}


HBRUSH CMFCChatClientDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	CString strColor;
	m_FontColorCombo.GetWindowTextW(strColor);

	if (IDC_MSG_LIST == pWnd->GetDlgCtrlID() || IDC_SENDMSG_EDIT == pWnd->GetDlgCtrlID())
	{
		if (strColor == L"黑色")
		{
			pDC->SetTextColor(RGB(0, 0, 0));
		}
		else if (strColor == L"红色")
		{
			pDC->SetTextColor(RGB(255, 0, 0));
		}
		else if (strColor == L"蓝色")
		{
			pDC->SetTextColor(RGB(0, 0, 255));
		}
		else if (strColor == L"绿色")
		{
			pDC->SetTextColor(RGB(0, 255, 0));
		}
	}
	

	// TODO:  在此更改 DC 的任何特性

	// TODO:  如果默认的不是所需画笔，则返回另一个画笔
	return hbr;
}
