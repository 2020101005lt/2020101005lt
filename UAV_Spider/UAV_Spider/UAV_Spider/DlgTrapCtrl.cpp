// DlgTrapCtrl.cpp : 实现文件
//

#include "stdafx.h"
#include "UAV_Spider.h"
#include "DlgTrapCtrl.h"
#include "afxdialogex.h"
#include "MainFrm.h"

// CDlgTrapCtrl 对话框

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

// CDlgTrapCtrl 消息处理程序
void CDlgTrapCtrl::OnBnClickedBtnSendTime()
{
	// TODO: 在此添加控件通知处理程序代码
	int a = 0;
	int b = 1;
}


void CDlgTrapCtrl::OnBnClickedRadioTrapOn()
{
	// TODO: 在此添加控件通知处理程序代码
}


void CDlgTrapCtrl::OnBnClickedRadioTrapOff()
{
	// TODO: 在此添加控件通知处理程序代码
}


void CDlgTrapCtrl::OnBnClickedRadioLdOn()
{
	// TODO: 在此添加控件通知处理程序代码
}


void CDlgTrapCtrl::OnBnClickedRadioLdOff()
{
	// TODO: 在此添加控件通知处理程序代码
}

void CDlgTrapCtrl::OnBnClickedButtonSendcom()
{
	// TODO: 在此添加控件通知处理程序代码
	CString m_UDPSend;

	GetDlgItemText(IDC_EDIT1, m_UDPSend);


	//将CString转换为int
	int m_iUDPSend = _ttoi(m_UDPSend);

	char m_sendBuf[4] = "0";
	sprintf_s(m_sendBuf,4,"%d",m_iUDPSend);

	//获取文档CMainFrame的指针

	CMainFrame *pFrame=(CMainFrame*)AfxGetMainWnd();

	/***********************************************发送数据****************************************************************/
	int len = sizeof(SOCKADDR);

	//sendto(pFrame->m_UDPclientTrap.s_UDPSockSrv,m_sendBuf,strlen(m_sendBuf)+1,0,(SOCKADDR*)&pFrame->m_UDPclientTrap.s_UDPAddrClient,len); 
	TRACE("+----------------------------已发送%d----------------------------+\n",m_iUDPSend );
}
