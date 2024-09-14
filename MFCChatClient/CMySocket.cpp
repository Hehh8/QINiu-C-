#include "pch.h"
#include "CMySocket.h"
#include "MFCChatClient.h"
#include "MFCChatClientDlg.h"

CMySocket::CMySocket()
{
}

CMySocket::~CMySocket()
{
}

void CMySocket::OnConnect(int nErrorCode)
{
	TRACE("####[ChatClient]OnConnect");
	CMFCChatClientDlg* dlg = (CMFCChatClientDlg*)AfxGetApp()->GetMainWnd();

	CString str;
	dlg->m_time = CTime::GetCurrentTime();
	str = dlg->m_time.Format("%X ");
	str += _T("与服务器连接成功");
	dlg->m_list.AddString(str);

	CAsyncSocket::OnConnect(nErrorCode);
}

void CMySocket::OnReceive(int nErrorCode)
{
	TRACE("####[ChatClient]OnReceive");
	CMFCChatClientDlg* dlg = (CMFCChatClientDlg*)AfxGetApp()->GetMainWnd();
	char szRecvBuf[200] = { 0 };

	// 接收数据到buf
	Receive(szRecvBuf, 200, 0);
	TRACE("####Server szRecvBuf = %s", szRecvBuf);

	CString strRecvMsg;
	USES_CONVERSION;
	strRecvMsg = A2W(szRecvBuf);

	// 显示到列表框
	CString strShow = _T("服务端: ");
	CString strTime;
	dlg->m_time = CTime::GetCurrentTime();
	strTime = dlg->m_time.Format("%X ");
	strShow = strTime + strShow;
	strShow += strRecvMsg;
	dlg->m_list.AddString(strShow);
	dlg->m_list.UpdateData(FALSE);


	CAsyncSocket::OnReceive(nErrorCode);
}
