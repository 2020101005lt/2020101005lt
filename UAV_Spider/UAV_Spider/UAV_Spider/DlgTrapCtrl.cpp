// DlgTrapCtrl.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "UAV_Spider.h"
#include "DlgTrapCtrl.h"
#include "afxdialogex.h"
#include "MainFrm.h"

// CDlgTrapCtrl �Ի���

IMPLEMENT_DYNAMIC(CDlgTrapCtrl, CDialogEx)

CDlgTrapCtrl::CDlgTrapCtrl(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgTrapCtrl::IDD, pParent)
{

}

CDlgTrapCtrl::~CDlgTrapCtrl()
{
}

void CDlgTrapCtrl::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDlgTrapCtrl, CDialogEx)
	ON_BN_CLICKED(IDC_BTN_SEND_TIME, &CDlgTrapCtrl::OnBnClickedBtnSendTime)
	ON_BN_CLICKED(IDC_RADIO_TRAP_ON, &CDlgTrapCtrl::OnBnClickedRadioTrapOn)
	ON_BN_CLICKED(IDC_RADIO_TRAP_OFF, &CDlgTrapCtrl::OnBnClickedRadioTrapOff)
	ON_BN_CLICKED(IDC_RADIO_LD_ON, &CDlgTrapCtrl::OnBnClickedRadioLdOn)
	ON_BN_CLICKED(IDC_RADIO_LD_OFF, &CDlgTrapCtrl::OnBnClickedRadioLdOff)
	ON_BN_CLICKED(IDC_BUTTON_SENDCOM, &CDlgTrapCtrl::OnBnClickedButtonSendcom)
END_MESSAGE_MAP()

// CDlgTrapCtrl ��Ϣ�������
void CDlgTrapCtrl::OnBnClickedBtnSendTime()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	int a = 0;
	int b = 1;
}


void CDlgTrapCtrl::OnBnClickedRadioTrapOn()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}


void CDlgTrapCtrl::OnBnClickedRadioTrapOff()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}


void CDlgTrapCtrl::OnBnClickedRadioLdOn()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}


void CDlgTrapCtrl::OnBnClickedRadioLdOff()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}

void CDlgTrapCtrl::OnBnClickedButtonSendcom()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString m_UDPSend;

	GetDlgItemText(IDC_EDIT1, m_UDPSend);


	//��CStringת��Ϊint
	int m_iUDPSend = _ttoi(m_UDPSend);

	char m_sendBuf[4] = "0";
	sprintf_s(m_sendBuf,4,"%d",m_iUDPSend);

	//��ȡ�ĵ�CMainFrame��ָ��

	CMainFrame *pFrame=(CMainFrame*)AfxGetMainWnd();

	/***********************************************��������****************************************************************/
	int len = sizeof(SOCKADDR);

	//sendto(pFrame->m_UDPclientTrap.s_UDPSockSrv,m_sendBuf,strlen(m_sendBuf)+1,0,(SOCKADDR*)&pFrame->m_UDPclientTrap.s_UDPAddrClient,len); 
	TRACE("+----------------------------�ѷ���%d----------------------------+\n",m_iUDPSend );
}
