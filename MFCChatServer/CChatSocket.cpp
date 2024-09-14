#include "pch.h"
#include "CChatSocket.h"
#include "MFCChatServerDlg.h"


CChatSocket::CChatSocket()
{
}

CChatSocket::~CChatSocket()
{
}

void CChatSocket::OnReceive(int nErrorCode)
{
	TRACE("####Server onReceive");
	CMFCChatServerDlg* dlg = (CMFCChatServerDlg*)AfxGetApp()->GetMainWnd();
	char szRecvBuf[SEND_MAX_BUF] = {0};

	// 接收数据到buf
	Receive(szRecvBuf, SEND_MAX_BUF, 0);
	TRACE("####Server szRecvBuf = %s", szRecvBuf);

	CString strRecvMsg;
	USES_CONVERSION;
	strRecvMsg = A2W(szRecvBuf);

	// 显示到列表框
	CString strShow;
	CString strInfo = _T("客户端: ");
	strShow = dlg->CatShowString(strInfo, strRecvMsg);

	dlg->m_list.AddString(strShow);
	dlg->m_list.UpdateData(FALSE);

	CAsyncSocket::OnReceive(nErrorCode);

}

