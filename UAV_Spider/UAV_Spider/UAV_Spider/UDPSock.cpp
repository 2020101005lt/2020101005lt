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

	err = WSAStartup(wVersionRequested, &wsaData);//����᷵��WSASYSNOTREADY
	if(err != 0)
	{
		return 1;
	}

	if(LOBYTE(wsaData.wVersion) != 1 ||     //���ֽ�Ϊ���汾
		HIBYTE(wsaData.wVersion) != 1)      //���ֽ�Ϊ���汾
	{
		WSACleanup();
		return 1;
	}
	TRACE("server is operating!\n\n");

	//�������ڼ������׽���
	this->s_UDPSockSrv = socket(AF_INET,SOCK_DGRAM,0);//ʧ�ܻ᷵�� INVALID_SOCKET
	//printf("Failed. Error Code : %d",WSAGetLastError())//��ʾ������Ϣ

	//����sockSrv���ͺͽ������ݰ��ĵ�ַ
	this->s_UDPAddrSrv.sin_addr.S_un.S_addr = htonl(INADDR_ANY);
	this->s_UDPAddrSrv.sin_family = AF_INET;
	this->s_UDPAddrSrv.sin_port = htons(4003);

	//���׽���, �󶨵��˿�
	bind(this->s_UDPSockSrv,(SOCKADDR*)&this->s_UDPAddrSrv,sizeof(SOCKADDR));//�᷵��һ��SOCKET_ERROR
	//���׽�����Ϊ����ģʽ�� ׼�����տͻ�����


	return 0;
}


int UDPSock::UDPRecv(void)
{
	
char c_recvBuf[200] = "0";    //��
	char c_recvTemp[200] = "0"; //����

	char c_tempBuf[300]= "0";    //�洢�м���Ϣ����

	char c_HeadPart[10]= "0";
	char c_LenPart[10]= "0";
	char c_NumPart[10]= "0";
	char c_JsonPart[180]= "0";
	int m_AddrLen = sizeof(SOCKADDR);

	//�ȴ�������
		recvfrom(this->s_UDPSockSrv,c_recvBuf,200,0,(SOCKADDR*)&this->s_UDPAddrClient,&m_AddrLen);
		if('q' == 	c_recvBuf[0])
		{
			sendto(this->s_UDPSockSrv,"q",strlen("q")+1,0,(SOCKADDR*)&this->s_UDPAddrClient,m_AddrLen);
			TRACE("Chat end!\n");
			return 1;
		}
		sprintf_s(c_tempBuf,220,"%s say : %s",inet_ntoa(this->s_UDPAddrClient.sin_addr),c_recvBuf);      //�����ݵ����ݴ�ӡ����
		TRACE("%s\n",c_tempBuf);

		if(c_tempBuf[0]=='F')          //����ĸ��F�Ž��в�ֹ���
		{
		char seg[] = "_";          //�ָ���
		int Counti =0;
		char *substr= strtok(c_recvBuf, seg);           /*�����ֳɵķָ��,substrΪ�ָ���������ַ���*/
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
             
			substr = strtok(NULL,seg);/*�ڵ�һ�ε���ʱ��strtok()����������str�ַ�����				
									  ����ĵ����򽫲���str���ó�NULL��ÿ�ε��óɹ��򷵻ر��ָ��Ƭ�ε�ָ�롣*/      
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
		
	int m_iSysSta =Va["iSysSta"].asInt();                                       //1		ϵͳ����״̬         
	std::string m_sTime =Va["sTime"].asString();                         //2		ʱ��
	int m_iSysRunTime = Va["iSysRunTime"].asInt();                    //3		ϵͳ����ʱ��
	double m_fEnvTemp = Va["fEnvTemp"].asDouble();              //4        �����¶�
	std::string m_sTsSyncSta = Va["sTsSyncSta"].asString();         //5		��ʱͬ��״̬��
	double m_dbFixLon = Va["dbFixLon"].asDouble();					//6		��ǰ��λλ�þ���
	double m_dbFixLat = Va["dbFixLat"].asDouble();					//7		��ǰ��λλ��γ��
	double m_dbFixAlt= Va["dbFixAlt"].asDouble();						//8		��ǰ��λλ�ø߶�
	int m_iOcxoSta = Va["iOcxoSta"].asInt();								//9		����״̬
	std::string m_sWorkStaGPS = Va["sWorkStaGPS"].asString();//10		GPS����״̬��
	std::string m_sWorkStaBDS = Va["sWorkStaBDS"].asString();//11		BDS����״̬��
	std::string m_sWorkStaGLO= Va["sWorkStaGLO"].asString();//12		GLONASS����״̬��
	int m_iSatNumGPS =Va["iSatNumGPS"].asInt();						//13		GPSת�����ǿ���
	int m_iSatNumBDS =Va["iSatNumBDS"].asInt();						//14		BDSת�����ǿ���
	int m_iSatNumGLO =Va["iSatNumGLO"].asInt();					//15		GLONASSת�����ǿ���
	int m_iSwitchGPS =Va["iSwitchGPS"].asInt();							//16		GPS���俪��
	int m_iSwitchBDS =Va["iSwitchBDS"].asInt();							//17		BDS���俪��
	int m_iSwitchGLO =Va["iSwitchGLO"].asInt();							//18		GLONASS���俪��
	int m_iPASwitch =Va["iPASwitch"].asInt();								//19		���ſ���
	double m_dbSimuLon = Va["dbSimuLon"].asDouble();			//20		��ǰ��ƭλ�þ���
	double m_dbSimuLat = Va["dbSimuLat"].asDouble();			//21		��ǰ��ƭλ�ø߶�
	double m_dbSimuAlt = Va["dbSimuAlt"].asDouble();				//22		��ǰ��ƭλ�ø߶�
	double m_fAttenGPS = Va["fAttenGPS"].asDouble();				//23		GPS����˥��ֵ
	double m_fAttenBDS = Va["fAttenBDS"].asDouble();				//24		BDS����˥��ֵ
	double m_fAttenGLO = Va["fAttenGLO"].asDouble();			//25		GLONASS����˥��ֵ
	double m_fDelayGPS = Va["fDelayGPS"].asDouble();				//26		GPSͨ��ʱ��
	double m_fDelayBDS= Va["fDelayBDS"].asDouble();				//27		BDSͨ��ʱ��
	double m_DelayGLO = Va["fDelayGLO"].asDouble();				//28		GLONASSͨ��ʱ��

	}
	else if(m_NumPart == 601)
	{
		double m_dbLon = Va["dbLon"].asDouble();				//1		����
		double m_dbLat= Va["dbLat"].asDouble();				//2		γ��
		double m_dbAlt = Va["dbAlt"].asDouble();				//3		�߶�
	}
	else if(m_NumPart == 602)
	{
			int m_iSwitch =Va["iSwitch"].asInt();							//1	����
	}
	else if(m_NumPart == 603)
	{
		double m_fAttenGPS = Va["fAttenGPS"].asDouble();				//1		GPS����˥��ֵ
		double m_fAttenBDS= Va["fAttenBDS"].asDouble();				//2		BDS����˥��ֵ
		double m_fAttenGLO = Va["fAttenGLO"].asDouble();				//3		GLONASS����˥��ֵ
	}
	else if(m_NumPart == 604)
	{
		double m_fDelayGPS = Va["fDelayGPS"].asDouble();				//1		GPSͨ��ʱ��
		double m_fDelayBDS= Va["fDelayBDS"].asDouble();				//2		BDSͨ��ʱ��
		double m_DelayGLO = Va["fDelayGLO"].asDouble();				//3		GLONASSͨ��ʱ��
	}
	else if(m_NumPart == 651)
	{
			int m_iState =Va["iState"].asInt();							//1	�����
			int m_iSwitch =Va["iSwitch"].asInt();							//2	���俪��״̬
			TRACE("%d--------------%d\n",m_iState,m_iSwitch);
	}
	else if(m_NumPart == 652)
	{
		int m_iState =Va["iState"].asInt();							//1	�����
	}
	else if(m_NumPart == 653)
	{
		int m_iState =Va["iState"].asInt();							//1	�����
		double m_fAttenGPS = Va["fAttenGPS"].asDouble();				//2		GPS����˥��ֵ
		double m_fAttenBDS = Va["fAttenBDS"].asDouble();				//3		BDS����˥��ֵ
		double m_fAttenGLO = Va["fAttenGLO"].asDouble();			//4		GLONASS����˥��ֵ
	}
	else if(m_NumPart == 654)
	{
			int m_iState =Va["iState"].asInt();							//1	�����
			double m_fDelayGPS = Va["fDelayGPS"].asDouble();				//26		GPSͨ��ʱ��
			double m_fDelayBDS= Va["fDelayBDS"].asDouble();				//27		BDSͨ��ʱ��
			double m_DelayGLO = Va["fDelayGLO"].asDouble();				//28		GLONASSͨ��ʱ��
			}
		}
	}
	else{	TRACE("%s\n",c_tempBuf);}
			return 0;
}


void UDPSock::UDPSend(void)
{
	char c_sendBuf[200]= "0";    //��
	Json::Value root;
	root["keystring"] = Json::Value("123456789");     // �½�һ�� Key����Ϊ��key_string���������ַ���ֵ��"value_string"��
	root["keynumber"] = Json::Value(1);             // �½�һ�� Key����Ϊ��key_number����������ֵ��12345��
	root["keyboolean"] = Json::Value(true);             // �½�һ�� Key����Ϊ��key_boolean��������boolֵ��false��
	root["keydouble"] = Json::Value(12.345);             // �½�һ�� Key����Ϊ��key_double�������� double ֵ��12.345��
	Json::FastWriter styled_writer;
	std::string s=styled_writer.write(root);
	strcpy(c_sendBuf, s.c_str());                                        //֡�壬json�ַ���
	//gets(sendBuf);
		int m_AddrLen = sizeof(SOCKADDR);
	int num = 660;
	char Head[220];
	sprintf_s( Head,220,"FF_%d_%d_",strlen(c_sendBuf),num);              //֡ͷ
	char Tail[] = "_";                                                     //֡β
	strcat(Head, c_sendBuf);                                             //֡ͷ��֡������
	strcat(Head, Tail);                                                  //������֡β����
	sendto(this->s_UDPSockSrv,Head,strlen(Head)+1,0,(SOCKADDR*)&this->s_UDPAddrSrv,m_AddrLen);  //����֡
	TRACE("�ѷ���%s\n",Head);

}
