
// MFCChatServerDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "MFCChatServer.h"
#include "MFCChatServerDlg.h"
#include "afxdialogex.h"
#include "CServerSocket.h"

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


// CMFCChatServerDlg 对话框



CMFCChatServerDlg::CMFCChatServerDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCCHATSERVER_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCChatServerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_MSG_LIST, m_list);
	DDX_Control(pDX, IDC_COLOUR_COMBO, m_FontColorCombo);
}

BEGIN_MESSAGE_MAP(CMFCChatServerDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_CBN_SELCHANGE(IDC_COLOUR_COMBO, &CMFCChatServerDlg::OnCbnSelchangeColourCombo)
	ON_BN_CLICKED(IDC_CAL_BTN, &CMFCChatServerDlg::OnClickedCalBtn)
	ON_BN_CLICKED(IDC_MAIL_BTN, &CMFCChatServerDlg::OnClickedMailBtn)
	ON_BN_CLICKED(IDC_QQ_BTN, &CMFCChatServerDlg::OnClickedQqBtn)
	ON_BN_CLICKED(IDC_SEND_BTN, &CMFCChatServerDlg::OnClickedSendBtn)
	ON_BN_CLICKED(IDC_START_BTN, &CMFCChatServerDlg::OnClickedStartBtn)
	ON_BN_CLICKED(IDC_STOP_BTN, &CMFCChatServerDlg::OnClickedStopBtn)
	ON_BN_CLICKED(IDC_CLEAR_BUT, &CMFCChatServerDlg::OnClickedClearBut)
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// CMFCChatServerDlg 消息处理程序

BOOL CMFCChatServerDlg::OnInitDialog()
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
	GetDlgItem(IDC_START_BTN)->EnableWindow(TRUE);
	GetDlgItem(IDC_STOP_BTN)->EnableWindow(FALSE);
	GetDlgItem(IDC_SEND_BTN)->EnableWindow(FALSE);
	GetDlgItem(IDC_CAL_BTN)->EnableWindow(TRUE);
	GetDlgItem(IDC_MAIL_BTN)->EnableWindow(TRUE);
	GetDlgItem(IDC_QQ_BTN)->EnableWindow(TRUE);

	GetDlgItem(IDC_PORT_EDIT)->SetWindowText(_T("5000"));

	m_FontColorCombo.AddString(_T("黑色"));
	m_FontColorCombo.AddString(_T("红色"));
	m_FontColorCombo.AddString(_T("蓝色"));
	m_FontColorCombo.AddString(_T("绿色"));
	m_FontColorCombo.AddString(_T("紫色"));
	m_FontColorCombo.SetCurSel(0);
	SetDlgItemText(IDC_COLOUR_COMBO, _T("黑色"));


	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CMFCChatServerDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CMFCChatServerDlg::OnPaint()
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
HCURSOR CMFCChatServerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMFCChatServerDlg::OnCbnSelchangeColourCombo()
{
	// TODO: 在此添加控件通知处理程序代码
}


void CMFCChatServerDlg::OnClickedCalBtn()
{
	// TODO: 在此添加控件通知处理程序代码
}


void CMFCChatServerDlg::OnClickedMailBtn()
{
	// TODO: 在此添加控件通知处理程序代码
}


void CMFCChatServerDlg::OnClickedQqBtn()
{
	// TODO: 在此添加控件通知处理程序代码
}


void CMFCChatServerDlg::OnClickedSendBtn()
{
	// TODO: 在此添加控件通知处理程序代码
	TRACE("####Server OnClickedSendBtn");
	// 获取编辑框内容
	CString strMsg;
	GetDlgItem(IDC_SENDMSG_EDIT)->GetWindowText(strMsg);

	USES_CONVERSION;
	char* szSendBuf = T2A(strMsg);

	// 发送给客户端
	m_chat->Send(szSendBuf, SEND_MAX_BUF, 0);

	// 显示到列表框
	CString strShow;
	CString strInfo = _T("服务端: ");
	strShow = CatShowString(strInfo, strMsg);


	m_list.AddString(strShow);
	m_list.UpdateData(FALSE);

	// 清空编辑框
	GetDlgItem(IDC_SENDMSG_EDIT)->SetWindowTextW(_T(""));
}


void CMFCChatServerDlg::OnClickedStartBtn()
{
	// TODO: 在此添加控件通知处理程序代码
	TRACE("####[ChatServer]OnClickedStartBtn");
	GetDlgItem(IDC_START_BTN)->EnableWindow(FALSE);
	GetDlgItem(IDC_STOP_BTN)->EnableWindow(TRUE);
	GetDlgItem(IDC_SEND_BTN)->EnableWindow(TRUE);

	CString strPort;

	// 从控件中获取内容
	GetDlgItem(IDC_PORT_EDIT)->GetWindowTextW(strPort);

	// CString转char *
	USES_CONVERSION;
	LPCSTR szPort = (LPCSTR)T2A(strPort);
	TRACE("####[ChatClient]szPort = %s", szPort);

	int iPort = _ttoi(strPort);

	// 创建服务器Socket对象
	m_server = new CServerSocket;

	// 创建socket
	if (!m_server->Create(iPort))
	{
		TRACE("m_server Create error %d", GetLastError());
		return;
	} 
	else
	{
		TRACE("m_server Create success");
	}

	// 监听
	if (!m_server->Listen())
	{
		TRACE("m_server Listen error %d", GetLastError());
		return;
	}
	
	CString strShow;
	CString strInfo;
	CString strMsg = _T("建立服务");
	strShow = CatShowString(strInfo, strMsg);

	m_list.AddString(strShow);
	UpdateData(FALSE);


	
}


void CMFCChatServerDlg::OnClickedStopBtn()
{
	// TODO: 在此添加控件通知处理程序代码
	TRACE("OnClickedStopBtn");
	// 1.控制控件
	GetDlgItem(IDC_START_BTN)->EnableWindow(TRUE);
	GetDlgItem(IDC_STOP_BTN)->EnableWindow(FALSE);
	GetDlgItem(IDC_SEND_BTN)->EnableWindow(FALSE);

	// 2.回收资源
	m_server->Close();
	if (m_server != NULL)
	{
		delete m_server;
		m_server = NULL;
	}
	if (m_chat != NULL)
	{
		delete m_chat;
		m_chat = NULL;
	}
	// 3.显示到列表框
	CString strShow;
	CString strInfo = _T("");
	CString strMsg = _T("服务器停止");
	strShow = CatShowString(strInfo, strMsg);
	m_list.AddString(FALSE);
	m_list.UpdateData(FALSE);
}

CString CMFCChatServerDlg::CatShowString(CString strInfo, CString strMsg)
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


void CMFCChatServerDlg::OnClickedClearBut()
{
	// TODO: 在此添加控件通知处理程序代码
	m_list.ResetContent();
}


HBRUSH CMFCChatServerDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
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
