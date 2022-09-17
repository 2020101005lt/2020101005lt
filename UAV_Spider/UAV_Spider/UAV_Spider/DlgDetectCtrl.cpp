// DlgDetectCtrl.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "UAV_Spider.h"
#include "DlgDetectCtrl.h"
#include "afxdialogex.h"


// CDlgDetectCtrl �Ի���

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


// CDlgDetectCtrl ��Ϣ�������


void CDlgDetectCtrl::OnBnClickedRadioDetectOn()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}


void CDlgDetectCtrl::OnBnClickedRadioDetectOff()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}


void CDlgDetectCtrl::OnBnClickedRadioFk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}


void CDlgDetectCtrl::OnBnClickedRadioTc()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}


void CDlgDetectCtrl::OnBnClickedRadioTrackOn()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}


void CDlgDetectCtrl::OnBnClickedRadioTrackOff()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}


void CDlgDetectCtrl::OnBnClickedRadioUploadOn()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}


void CDlgDetectCtrl::OnBnClickedRadioUploadOff()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}
