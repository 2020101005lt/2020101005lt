#pragma once
#include "afxsock.h"
//#include <Winsock2.h>
#include <stdio.h>
#include <iostream>
#include <string>
#include "./json/json.h"
using namespace std;
//#pragma comment(lib, "json_vc71_libmtd.lib")
#pragma comment(lib, "ws2_32.lib")
class UDPSock :
	public CSocket
{
public:
	UDPSock(void);
	~UDPSock(void);
	int UDPInit(void);
	int UDPRecv(void);
	void UDPSend(void);
	SOCKET s_UDPSockSrv;
	SOCKADDR_IN s_UDPAddrSrv;
	SOCKADDR_IN s_UDPAddrClient;
};

