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

	// �������ݵ�buf
	Receive(szRecvBuf, SEND_MAX_BUF, 0);
	TRACE("####Server szRecvBuf = %s", szRecvBuf);

	CString strRecvMsg;
	USES_CONVERSION;
	strRecvMsg = A2W(szRecvBuf);

	// ��ʾ���б��
	CString strShow;
	CString strInfo = _T("�ͻ���: ");
	strShow = dlg->CatShowString(strInfo, strRecvMsg);

	dlg->m_list.AddString(strShow);
	dlg->m_list.UpdateData(FALSE);

	CAsyncSocket::OnReceive(nErrorCode);

}

