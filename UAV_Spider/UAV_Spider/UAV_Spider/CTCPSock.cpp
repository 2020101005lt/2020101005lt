#include "stdafx.h"
#include "MainFrm.h"

///////////////// CSockC.cpp�ļ�  ///////////////////
using namespace std;
CTCPSock::CTCPSock()
{
}

CTCPSock::~CTCPSock()
{
}


// Do not edit the following lines, which are needed by ClassWizard.
#if 0
BEGIN_MESSAGE_MAP(CTCPSock, CSocket)
	//{{AFX_MSG_MAP(CSockC)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
#endif    // 0

/////////////////////////////////////////////////////////////////////////////
// CSockC member functions

void CTCPSock::OnReceive(int nErrorCode) 
{
	char s[2048] = {0};
	CString szIP;
	UINT nPort;
	//TCP������Ϣ����
	Receive(s,sizeof(s));
	//��ȡ��Ϣ��Դ��IP��ַ�Ͷ˿ں�
	GetPeerName(szIP, nPort);
	CMainFrame* pMainFrm = (CMainFrame*)AfxGetMainWnd();
	pMainFrm->RecvTCPData(s);

	CSocket::OnReceive(nErrorCode);
}

void CTCPSock::SendCommand(ECmdType cmdType)
{
	char s[2048] = {0};
	UINT Header = 0xAABBCCDD;
	ECmdType Type = cmdType;
	//public PacketHeader(ECmdType type, uint staID)
	//{
	//	this.Header 
	//		this.Type = type;
	//	this.StationID = staID;
	//	this.Time = STime.Now;
	//	this.Length = 0;
	//}
}