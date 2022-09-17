// DlgDetectCtrl.cpp : 实现文件
//

#include "stdafx.h"
#include "UAV_Spider.h"
#include "DlgDetectCtrl.h"
#include "afxdialogex.h"


// CDlgDetectCtrl 对话框

IMPLEMENT_DYNAMIC(CDlgDetectCtrl, CDialogEx)

CDlgDetectCtrl::CDlgDetectCtrl(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgDetectCtrl::IDD, pParent)
{

}

CDlgDetectCtrl::~CDlgDetectCtrl()
{
}

void CDlgDetectCtrl::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDlgDetectCtrl, CDialogEx)
	ON_BN_CLICKED(IDC_RADIO_DETECT_ON, &CDlgDetectCtrl::OnBnClickedRadioDetectOn)
	ON_BN_CLICKED(IDC_RADIO_DETECT_OFF, &CDlgDetectCtrl::OnBnClickedRadioDetectOff)
	ON_BN_CLICKED(IDC_RADIO_FK, &CDlgDetectCtrl::OnBnClickedRadioFk)
	ON_BN_CLICKED(IDC_RADIO_TC, &CDlgDetectCtrl::OnBnClickedRadioTc)
	ON_BN_CLICKED(IDC_RADIO_TRACK_ON, &CDlgDetectCtrl::OnBnClickedRadioTrackOn)
	ON_BN_CLICKED(IDC_RADIO_TRACK_OFF, &CDlgDetectCtrl::OnBnClickedRadioTrackOff)
	ON_BN_CLICKED(IDC_RADIO_UPLOAD_ON, &CDlgDetectCtrl::OnBnClickedRadioUploadOn)
	ON_BN_CLICKED(IDC_RADIO_UPLOAD_OFF, &CDlgDetectCtrl::OnBnClickedRadioUploadOff)
END_MESSAGE_MAP()


// CDlgDetectCtrl 消息处理程序


void CDlgDetectCtrl::OnBnClickedRadioDetectOn()
{
	// TODO: 在此添加控件通知处理程序代码
}


void CDlgDetectCtrl::OnBnClickedRadioDetectOff()
{
	// TODO: 在此添加控件通知处理程序代码
}


void CDlgDetectCtrl::OnBnClickedRadioFk()
{
	// TODO: 在此添加控件通知处理程序代码
}


void CDlgDetectCtrl::OnBnClickedRadioTc()
{
	// TODO: 在此添加控件通知处理程序代码
}


void CDlgDetectCtrl::OnBnClickedRadioTrackOn()
{
	// TODO: 在此添加控件通知处理程序代码
}


void CDlgDetectCtrl::OnBnClickedRadioTrackOff()
{
	// TODO: 在此添加控件通知处理程序代码
}


void CDlgDetectCtrl::OnBnClickedRadioUploadOn()
{
	// TODO: 在此添加控件通知处理程序代码
}


void CDlgDetectCtrl::OnBnClickedRadioUploadOff()
{
	// TODO: 在此添加控件通知处理程序代码
}
