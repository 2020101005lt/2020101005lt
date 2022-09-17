// SockC.h : header file
#include "UserDef.h "
#include<iostream>
#include<winsock.h>
#include <time.h>
#pragma comment(lib,"ws2_32.lib")
using namespace std;
class CTCPSock : public CSocket
{
	// Attributes
public:

	// Operations
public:
	CTCPSock();
	virtual ~CTCPSock();
	TcpSrc m_DataSrc;
	CString m_strLocalIP;
	UINT m_uPort;
	// Overrides
public:
	
public:
	virtual void OnReceive(int nErrorCode);
	void SendCommand(ECmdType cmdType);
protected:
};
