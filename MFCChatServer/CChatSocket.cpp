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
	char szRecvBuf[200] = {0};

	// �������ݵ�buf
	Receive(szRecvBuf, 200, 0);
	TRACE("####Server szRecvBuf = %s", szRecvBuf);

	CString strRecvMsg;
	USES_CONVERSION;
	strRecvMsg = A2W(szRecvBuf);
	// ��ʾ���б��
	CString strShow = _T("�ͻ���: ");
	CString strTime;
	dlg->m_time = CTime::GetCurrentTime();
	strTime = dlg->m_time.Format("%X ");
	strShow = strTime + strShow;
	strShow += strRecvMsg;
	dlg->m_list.AddString(strShow);
	dlg->m_list.UpdateData(FALSE);

	CAsyncSocket::OnReceive(nErrorCode);

}

