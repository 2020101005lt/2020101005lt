#include "StdAfx.h"
#include "UDPSock.h"


UDPSock::UDPSock(void)
{
}


UDPSock::~UDPSock(void)
{
}


int UDPSock::UDPInit(void)
{
	WORD wVersionRequested;
	WSADATA wsaData;
	int err;

	wVersionRequested = MAKEWORD(1,1);

	err = WSAStartup(wVersionRequested, &wsaData);//错误会返回WSASYSNOTREADY
	if(err != 0)
	{
		return 1;
	}

	if(LOBYTE(wsaData.wVersion) != 1 ||     //低字节为主版本
		HIBYTE(wsaData.wVersion) != 1)      //高字节为副版本
	{
		WSACleanup();
		return 1;
	}
	TRACE("server is operating!\n\n");

	//创建用于监听的套接字
	this->s_UDPSockSrv = socket(AF_INET,SOCK_DGRAM,0);//失败会返回 INVALID_SOCKET
	//printf("Failed. Error Code : %d",WSAGetLastError())//显示错误信息

	//定义sockSrv发送和接收数据包的地址
	this->s_UDPAddrSrv.sin_addr.S_un.S_addr = htonl(INADDR_ANY);
	this->s_UDPAddrSrv.sin_family = AF_INET;
	this->s_UDPAddrSrv.sin_port = htons(4003);

	//绑定套接字, 绑定到端口
	bind(this->s_UDPSockSrv,(SOCKADDR*)&this->s_UDPAddrSrv,sizeof(SOCKADDR));//会返回一个SOCKET_ERROR
	//将套接字设为监听模式， 准备接收客户请求


	return 0;
}


int UDPSock::UDPRecv(void)
{
	
char c_recvBuf[200] = "0";    //收
	char c_recvTemp[200] = "0"; //备份

	char c_tempBuf[300]= "0";    //存储中间信息数据

	char c_HeadPart[10]= "0";
	char c_LenPart[10]= "0";
	char c_NumPart[10]= "0";
	char c_JsonPart[180]= "0";
	int m_AddrLen = sizeof(SOCKADDR);

	//等待并数据
		recvfrom(this->s_UDPSockSrv,c_recvBuf,200,0,(SOCKADDR*)&this->s_UDPAddrClient,&m_AddrLen);
		if('q' == 	c_recvBuf[0])
		{
			sendto(this->s_UDPSockSrv,"q",strlen("q")+1,0,(SOCKADDR*)&this->s_UDPAddrClient,m_AddrLen);
			TRACE("Chat end!\n");
			return 1;
		}
		sprintf_s(c_tempBuf,220,"%s say : %s",inet_ntoa(this->s_UDPAddrClient.sin_addr),c_recvBuf);      //将备份的内容打印出来
		TRACE("%s\n",c_tempBuf);

		if(c_tempBuf[0]=='F')          //首字母是F才进行拆分工作
		{
		char seg[] = "_";          //分隔符
		int Counti =0;
		char *substr= strtok(c_recvBuf, seg);           /*利用现成的分割函数,substr为分割出来的子字符串*/
		while (substr != NULL) {  		
			if(Counti == 0)
			{
					strcpy(c_HeadPart,substr);	
			}
			else if(Counti ==1)
			{
					strcpy(c_NumPart,substr);
			}
			else if(Counti == 2)
			{
					strcpy(c_LenPart,substr);	
			}
			else if (Counti == 3)
			{
					strcpy(c_JsonPart,substr);	
			}
			
			Counti++;               
             
			substr = strtok(NULL,seg);/*在第一次调用时，strtok()必需给予参数str字符串，				
									  往后的调用则将参数str设置成NULL。每次调用成功则返回被分割出片段的指针。*/      
		} 

	TRACE("%s\n",c_HeadPart);
	TRACE("%s\n",c_NumPart);
		TRACE("%s\n", c_LenPart);
	TRACE("%s\n", c_JsonPart);

	int m_NumPart = atoi(c_NumPart);
	Json::Value Va;
	Json::Reader Re;
	if(Re.parse(c_JsonPart, Va)) 
		{
	if(m_NumPart == 600)
	{
		
	int m_iSysSta =Va["iSysSta"].asInt();                                       //1		系统工作状态         
	std::string m_sTime =Va["sTime"].asString();                         //2		时间
	int m_iSysRunTime = Va["iSysRunTime"].asInt();                    //3		系统运行时长
	double m_fEnvTemp = Va["fEnvTemp"].asDouble();              //4        环境温度
	std::string m_sTsSyncSta = Va["sTsSyncSta"].asString();         //5		授时同步状态字
	double m_dbFixLon = Va["dbFixLon"].asDouble();					//6		当前定位位置经度
	double m_dbFixLat = Va["dbFixLat"].asDouble();					//7		当前定位位置纬度
	double m_dbFixAlt= Va["dbFixAlt"].asDouble();						//8		当前定位位置高度
	int m_iOcxoSta = Va["iOcxoSta"].asInt();								//9		晶振状态
	std::string m_sWorkStaGPS = Va["sWorkStaGPS"].asString();//10		GPS工作状态字
	std::string m_sWorkStaBDS = Va["sWorkStaBDS"].asString();//11		BDS工作状态字
	std::string m_sWorkStaGLO= Va["sWorkStaGLO"].asString();//12		GLONASS工作状态字
	int m_iSatNumGPS =Va["iSatNumGPS"].asInt();						//13		GPS转发卫星颗数
	int m_iSatNumBDS =Va["iSatNumBDS"].asInt();						//14		BDS转发卫星颗数
	int m_iSatNumGLO =Va["iSatNumGLO"].asInt();					//15		GLONASS转发卫星颗数
	int m_iSwitchGPS =Va["iSwitchGPS"].asInt();							//16		GPS发射开关
	int m_iSwitchBDS =Va["iSwitchBDS"].asInt();							//17		BDS发射开关
	int m_iSwitchGLO =Va["iSwitchGLO"].asInt();							//18		GLONASS发射开关
	int m_iPASwitch =Va["iPASwitch"].asInt();								//19		功放开关
	double m_dbSimuLon = Va["dbSimuLon"].asDouble();			//20		当前诱骗位置经度
	double m_dbSimuLat = Va["dbSimuLat"].asDouble();			//21		当前诱骗位置高度
	double m_dbSimuAlt = Va["dbSimuAlt"].asDouble();				//22		当前诱骗位置高度
	double m_fAttenGPS = Va["fAttenGPS"].asDouble();				//23		GPS功率衰减值
	double m_fAttenBDS = Va["fAttenBDS"].asDouble();				//24		BDS功率衰减值
	double m_fAttenGLO = Va["fAttenGLO"].asDouble();			//25		GLONASS功率衰减值
	double m_fDelayGPS = Va["fDelayGPS"].asDouble();				//26		GPS通道时延
	double m_fDelayBDS= Va["fDelayBDS"].asDouble();				//27		BDS通道时延
	double m_DelayGLO = Va["fDelayGLO"].asDouble();				//28		GLONASS通道时延

	}
	else if(m_NumPart == 601)
	{
		double m_dbLon = Va["dbLon"].asDouble();				//1		经度
		double m_dbLat= Va["dbLat"].asDouble();				//2		纬度
		double m_dbAlt = Va["dbAlt"].asDouble();				//3		高度
	}
	else if(m_NumPart == 602)
	{
			int m_iSwitch =Va["iSwitch"].asInt();							//1	开关
	}
	else if(m_NumPart == 603)
	{
		double m_fAttenGPS = Va["fAttenGPS"].asDouble();				//1		GPS功率衰减值
		double m_fAttenBDS= Va["fAttenBDS"].asDouble();				//2		BDS功率衰减值
		double m_fAttenGLO = Va["fAttenGLO"].asDouble();				//3		GLONASS功率衰减值
	}
	else if(m_NumPart == 604)
	{
		double m_fDelayGPS = Va["fDelayGPS"].asDouble();				//1		GPS通道时延
		double m_fDelayBDS= Va["fDelayBDS"].asDouble();				//2		BDS通道时延
		double m_DelayGLO = Va["fDelayGLO"].asDouble();				//3		GLONASS通道时延
	}
	else if(m_NumPart == 651)
	{
			int m_iState =Va["iState"].asInt();							//1	命令反馈
			int m_iSwitch =Va["iSwitch"].asInt();							//2	发射开关状态
			TRACE("%d--------------%d\n",m_iState,m_iSwitch);
	}
	else if(m_NumPart == 652)
	{
		int m_iState =Va["iState"].asInt();							//1	命令反馈
	}
	else if(m_NumPart == 653)
	{
		int m_iState =Va["iState"].asInt();							//1	命令反馈
		double m_fAttenGPS = Va["fAttenGPS"].asDouble();				//2		GPS功率衰减值
		double m_fAttenBDS = Va["fAttenBDS"].asDouble();				//3		BDS功率衰减值
		double m_fAttenGLO = Va["fAttenGLO"].asDouble();			//4		GLONASS功率衰减值
	}
	else if(m_NumPart == 654)
	{
			int m_iState =Va["iState"].asInt();							//1	命令反馈
			double m_fDelayGPS = Va["fDelayGPS"].asDouble();				//26		GPS通道时延
			double m_fDelayBDS= Va["fDelayBDS"].asDouble();				//27		BDS通道时延
			double m_DelayGLO = Va["fDelayGLO"].asDouble();				//28		GLONASS通道时延
			}
		}
	}
	else{	TRACE("%s\n",c_tempBuf);}
			return 0;
}


void UDPSock::UDPSend(void)
{
	char c_sendBuf[200]= "0";    //发
	Json::Value root;
	root["keystring"] = Json::Value("123456789");     // 新建一个 Key（名为：key_string），赋予字符串值："value_string"。
	root["keynumber"] = Json::Value(1);             // 新建一个 Key（名为：key_number），赋予数值：12345。
	root["keyboolean"] = Json::Value(true);             // 新建一个 Key（名为：key_boolean），赋予bool值：false。
	root["keydouble"] = Json::Value(12.345);             // 新建一个 Key（名为：key_double），赋予 double 值：12.345。
	Json::FastWriter styled_writer;
	std::string s=styled_writer.write(root);
	strcpy(c_sendBuf, s.c_str());                                        //帧体，json字符串
	//gets(sendBuf);
		int m_AddrLen = sizeof(SOCKADDR);
	int num = 660;
	char Head[220];
	sprintf_s( Head,220,"FF_%d_%d_",strlen(c_sendBuf),num);              //帧头
	char Tail[] = "_";                                                     //帧尾
	strcat(Head, c_sendBuf);                                             //帧头与帧体连接
	strcat(Head, Tail);                                                  //主体与帧尾相连
	sendto(this->s_UDPSockSrv,Head,strlen(Head)+1,0,(SOCKADDR*)&this->s_UDPAddrSrv,m_AddrLen);  //发送帧
	TRACE("已发送%s\n",Head);

}
