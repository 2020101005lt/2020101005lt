// UAV_SpiderView.cpp : implementation of the CUAV_SpiderView class
//

#include "stdafx.h"
#include "UAV_Spider.h"

#include "UAV_SpiderDoc.h"
#include "UAV_SpiderView.h"

#include <io.h>
#include <opencv2/opencv.hpp>
#include "resource.h"
using namespace cv; // all the new API is put into "cv" namespace. Export its content
using namespace std;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

bool Func_VectorSort_ShpShowConfig_Type(MAPWINGIS_LAYERSHOWINFO curNode, MAPWINGIS_LAYERSHOWINFO nextNode)
{
	return (curNode.layerType < nextNode.layerType);		//����layerType����
}
// CUAV_SpiderView

IMPLEMENT_DYNCREATE(CUAV_SpiderView, CView)

BEGIN_MESSAGE_MAP(CUAV_SpiderView, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_SIZE()
	//ON_BN_CLICKED(IDC_BTN_ZOOMIN, &CUAV_SpiderView::OnBnClickedBtnZoomin)
	//ON_BN_CLICKED(IDC_BTN_ZOOMOUT, &CUAV_SpiderView::OnBnClickedBtnZoomout)
	//ON_BN_CLICKED(IDC_BTN_PAN, &CUAV_SpiderView::OnBnClickedBtnPan)
	//ON_WM_MOUSEWHEEL()
	//ON_WM_CREATE()
	ON_WM_CREATE()
	ON_WM_CLOSE()
//	ON_WM_MOUSEHWHEEL()
ON_WM_MOUSEWHEEL()
ON_WM_LBUTTONDOWN()
ON_WM_LBUTTONUP()
END_MESSAGE_MAP()

BEGIN_EVENTSINK_MAP(CUAV_SpiderView, CView)
	ON_EVENT(CUAV_SpiderView, IDC_MAP_MapWinGis, 1, CUAV_SpiderView::MouseDownMapMapwingis, VTS_I2 VTS_I2 VTS_I4 VTS_I4)
	ON_EVENT(CUAV_SpiderView, IDC_MAP_MapWinGis, 2, CUAV_SpiderView::MouseUpMapMapwingis, VTS_I2 VTS_I2 VTS_I4 VTS_I4)
END_EVENTSINK_MAP()

// CUAV_SpiderView construction/destruction

CUAV_SpiderView::CUAV_SpiderView()
{
	// TODO: add construction code here
	// TODO: add construction code here
	myMap_SatelliteShapeFilePtr = NULL;
	myMap_ImageMapLayerHandle = -1;
	myMap_SatelliteImgPtr = NULL;
	myMap_SatellitePointPtr = NULL;
	myMap_SatelliteShapePtr = NULL;

	Update_Bing_TileImage_Busy = 0;
	Update_Bing_TileImage_TimeD = 0;
	Update_Bing_TileImage_Cmd = 0;
	//m_nRadiusIn = 500;
	//m_nRadiusOut = 1000;
}

CUAV_SpiderView::~CUAV_SpiderView()
{
	m_btnInDlg.DestroyWindow();
	m_btnOutDlg.DestroyWindow();
	m_btnPanDlg.DestroyWindow();
	myMap_SatelliteShapeFilePtr	= NULL;
	myMap_ImageMapLayerHandle = -1;
	myMap_SatelliteImgPtr = NULL;
	myMap_SatellitePointPtr = NULL;
	myMap_SatelliteShapePtr = NULL;
	myTileMerge.matMerged.release();
}

BOOL CUAV_SpiderView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CUAV_SpiderView drawing

void CUAV_SpiderView::OnDraw(CDC* /*pDC*/)
{
	CUAV_SpiderDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: add draw code for native data here
}


// CUAV_SpiderView printing

BOOL CUAV_SpiderView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CUAV_SpiderView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CUAV_SpiderView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}


// CUAV_SpiderView diagnostics

#ifdef _DEBUG
void CUAV_SpiderView::AssertValid() const
{
	CView::AssertValid();
}

void CUAV_SpiderView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CUAV_SpiderDoc* CUAV_SpiderView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CUAV_SpiderDoc)));
	return (CUAV_SpiderDoc*)m_pDocument;
}
#endif //_DEBUG


// CUAV_SpiderView message handlers


void CUAV_SpiderView::DoDataExchange(CDataExchange* pDX)
{
	// TODO: �ڴ����ר�ô����/����û���
	DDX_Control(pDX, IDC_MAP_MapWinGis, myMAP_MapWinGis);
	CView::DoDataExchange(pDX);
}


int CUAV_SpiderView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  �ڴ������ר�õĴ�������
	CRect rcmap;
	GetClientRect(rcmap);
	myMAP_MapWinGis.Create(NULL,WS_CHILD|WS_VISIBLE|WS_BORDER,rcmap,this,IDC_MAP_MapWinGis);

	//--V6--��ͼ��ʼ��
	//���������ģ��
	CWnd* mw_Wnd;
	IUnknown*  mw_iUnknown;
	mw_Wnd = GetDlgItem(IDC_MAP_MapWinGis);
	mw_iUnknown = mw_Wnd->GetControlUnknown();
	mw_iUnknown->QueryInterface(__uuidof(::_DMap),(LPVOID*)&map_CtrInterface);
	myMapWinGis_PANING = 0;
	myMap_ImageMapLayeVisble = 0;

	if ( m_btnInDlg.m_hWnd == NULL )
	{
		m_btnInDlg.m_strKind = "IN";
		m_btnInDlg.Create(IDD_DIALOG_BTN,this);
		m_btnInDlg.m_pParentView = this;
	}
	m_btnInDlg.MoveWindow(m_rctView.right - 120,m_rctView.bottom-40,32,32);
	m_btnInDlg.ShowWindow(SW_SHOW);
	if ( m_btnOutDlg.m_hWnd == NULL )
	{
		m_btnOutDlg.m_strKind = "OUT";
		m_btnOutDlg.Create(IDD_DIALOG_BTN,this);
		m_btnOutDlg.m_pParentView = this;
	}
	m_btnOutDlg.MoveWindow(m_rctView.right - 80,m_rctView.bottom-40,32,32);
	m_btnOutDlg.ShowWindow(SW_SHOW);
	if ( m_btnPanDlg.m_hWnd == NULL )
	{
		m_btnPanDlg.m_strKind = "PAN";
		m_btnPanDlg.Create(IDD_DIALOG_BTN,this);
		m_btnPanDlg.m_pParentView = this;
	}
	m_btnPanDlg.MoveWindow(m_rctView.right - 40,m_rctView.bottom-40,32,32);
	m_btnPanDlg.ShowWindow(SW_SHOW);
	return 0;
}


void CUAV_SpiderView::OnClose()
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	map_CtrInterface->RemoveAllLayers();
	//map_CtrInterface->Release();
	CView::OnClose();
}


void CUAV_SpiderView::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType, cx, cy);
	if(myMAP_MapWinGis.m_hWnd == NULL)
		return;
	if(IsWindow(myMAP_MapWinGis.m_hWnd))
	{
		CRect rect;
		GetClientRect(&rect);
		myMAP_MapWinGis.MoveWindow(rect,FALSE);
		myMAP_MapWinGis.ZoomToPrev();
	}
		
	this->GetWindowRect(&m_rctView);
	if ( cx * cy != 0 )
	{
		if ( m_btnInDlg.m_hWnd == NULL )
		{
			m_btnInDlg.m_strKind = "IN";
			m_btnInDlg.Create(IDD_DIALOG_BTN,this);
			m_btnInDlg.m_pParentView = this;
		}
		m_btnInDlg.MoveWindow(m_rctView.right - 120,m_rctView.bottom-40,32,32);
		m_btnInDlg.ShowWindow(SW_SHOW);
		if ( m_btnOutDlg.m_hWnd == NULL )
		{
			m_btnOutDlg.m_strKind = "OUT";
			m_btnOutDlg.Create(IDD_DIALOG_BTN,this);
			m_btnOutDlg.m_pParentView = this;
		}
		m_btnOutDlg.MoveWindow(m_rctView.right - 80,m_rctView.bottom-40,32,32);
		m_btnOutDlg.ShowWindow(SW_SHOW);
		if ( m_btnPanDlg.m_hWnd == NULL )
		{
			m_btnPanDlg.m_strKind = "PAN";
			m_btnPanDlg.Create(IDD_DIALOG_BTN,this);
			m_btnPanDlg.m_pParentView = this;
		}
		m_btnPanDlg.MoveWindow(m_rctView.right - 40,m_rctView.bottom-40,32,32);
		m_btnPanDlg.ShowWindow(SW_SHOW);
	}	
}

//������--�ڵ�ͼ������--�����ʾ��վ������Ϣ���Ҽ���ʾ��վ����״̬��
void CUAV_SpiderView::MouseDownMapMapwingis(short Button, short Shift, long x, long y)
{
	if (Button == 1)	//������
	{
		if(m_mapParams.UsingSatelliteMap > 0) //--->>>���ǵ�ͼ������Ϊ���θ���
		{
			m_MouseStartXY[0] = x;
			m_MouseStartXY[1] = y;
		}
		//long index = -1;
		//GetSelectedShapeIndex(myMap_TowerLayerHandle,x,y,&index);
	}
}

//--���ݵ�ͼZoom������̬������ǩ�ɼ���
void CUAV_SpiderView::DealLabelsVisibleWhileZoomIn_Out() 
{
	//��������ʱ���ر�ǩ
	//TRACE("Line3907 scale_X\n");
	IExtentsPtr map_Ext;
	//IDispatch map_Ext;
	map_Ext = map_CtrInterface->GetExtents();
	//tdoaMapRectBLH[0] = map_Ext->yMax;
	//tdoaMapRectBLH[1] = map_Ext->xMin;

	//tdoaMapRectBLH[2] = map_Ext->yMin;
	//tdoaMapRectBLH[3] = map_Ext->xMax;
	double scale_X = map_Ext->xMax - map_Ext->xMin;
}

//���̧��--�ڵ�ͼ�ϻ���
void CUAV_SpiderView::MouseUpMapMapwingis(short Button, short Shift, long x, long y)
{
	DealLabelsVisibleWhileZoomIn_Out();	//��̬������ǩ�ɼ�
	if (Button == 1)	//������
	{
		if(m_mapParams.UsingSatelliteMap > 0 && myMapWinGis_PANING == 0) //--->>>���ǵ�ͼ������Ϊ���θ���
		{
			myMapWinGis_PANING++;
			int dx = x - m_MouseStartXY[0];
			int dy = y - m_MouseStartXY[1];
			if(abs(dx) + abs(dy) > 3)
			{
				myTileMerge.showCenterXY[0] -= dx;
				myTileMerge.showCenterXY[1] -= dy;
				bingTileSystem.PixelXYToLatLong(myTileMerge.showCenterXY[0], myTileMerge.showCenterXY[1], myTileMerge.showLevelOfDetail, &myTileMerge.showCenterBL[0], &myTileMerge.showCenterBL[1]);
				Update_Bing_TileImage();
				muUpdata_TowerPosition = 909;
			}
			myMapWinGis_PANING = 0;
		}
	}
}

void CUAV_SpiderView::OnBnClickedBtnZoomin()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//--�������ǵ�ͼ��������MapWinGis�ں˽ӹ����Ż��ƣ����һ��ִ��һ�����ţ�
	if(m_mapParams.UsingSatelliteMap > 0 && myMapWinGis_PANING == 0)
	{
		myTileMerge.showLevelOfDetail = min(myTileMerge.showLevelOfDetail + 1, SATELLET_TILEMAP_ZOOMMAX);
		myMapWinGis_PANING++;
		Update_Bing_TileImage();
		myMapWinGis_PANING = 0;
		return;
	}
	CWnd*      mw_Wnd;
	IUnknown*  mw_iUnknown;
	CComPtr<MapWinGIS::_DMap> map_CtrInterface;
	mw_Wnd      = GetDlgItem(IDC_MAP_MapWinGis);
	mw_iUnknown = mw_Wnd->GetControlUnknown();
	mw_iUnknown->QueryInterface(__uuidof(MapWinGIS::_DMap),(LPVOID*)&map_CtrInterface);
	map_CtrInterface->MapCursor = crsrMapDefault;		//crsrSizeAll�ķ����ͷ��crsrAppStarting��������־�ļ�ͷ��
	map_CtrInterface->CursorMode = cmZoomIn;		
	if(myMap_ImageMapLayeVisble == 1 && m_mapParams.UsingSatelliteMap == 0)
	{
		map_CtrInterface->PutLayerVisible(myMap_ImageMapLayerHandle, 1);
		myMap_ImageMapLayeVisble = 0;
	}
}

void CUAV_SpiderView::OnBnClickedBtnZoomout()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if(m_mapParams.UsingSatelliteMap > 0 && myMapWinGis_PANING == 0)
	{
		myTileMerge.showLevelOfDetail = min(myTileMerge.showLevelOfDetail - 1, SATELLET_TILEMAP_ZOOMMAX);
		myMapWinGis_PANING++;
		Update_Bing_TileImage();
		myMapWinGis_PANING = 0;
		return;
	}
	CWnd*      mw_Wnd;
	IUnknown*  mw_iUnknown;
	CComPtr<MapWinGIS::_DMap> map_CtrInterface;
	mw_Wnd      = GetDlgItem(IDC_MAP_MapWinGis);
	mw_iUnknown = mw_Wnd->GetControlUnknown();
	mw_iUnknown->QueryInterface(__uuidof(MapWinGIS::_DMap),(LPVOID*)&map_CtrInterface);
	map_CtrInterface->MapCursor = crsrMapDefault;		//crsrSizeAll�ķ����ͷ��crsrAppStarting��������־�ļ�ͷ��
	map_CtrInterface->CursorMode = cmZoomOut;		
	if(myMap_ImageMapLayeVisble == 1)
	{
		map_CtrInterface->PutLayerVisible(myMap_ImageMapLayerHandle, 1);
		myMap_ImageMapLayeVisble = 0;
	}
}


void CUAV_SpiderView::OnBnClickedBtnPan()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//if(m_mapParams.UsingSatelliteMap > 0 && myMapWinGis_PANING == 0)
	//{
	//	myMapWinGis_PANING++;
	//Update_Bing_TileImage();
	//	myMapWinGis_PANING = 0;
	//	return;
	//}
	CWnd*      mw_Wnd;
	IUnknown*  mw_iUnknown;
	CComPtr<MapWinGIS::_DMap> map_CtrInterface;
	mw_Wnd      = GetDlgItem(IDC_MAP_MapWinGis);
	mw_iUnknown = mw_Wnd->GetControlUnknown();
	mw_iUnknown->QueryInterface(__uuidof(MapWinGIS::_DMap),(LPVOID*)&map_CtrInterface);
	map_CtrInterface->MapCursor = crsrMapDefault;		//crsrSizeAll�ķ����ͷ��crsrAppStarting��������־�ļ�ͷ��
	map_CtrInterface->CursorMode = cmPan;
	//m_DrawLine = FALSE;
	Update_Bing_TileImage();
}

//����������γ��֮��ľ��룬��������λ�ף�
double CUAV_SpiderView::Distance_Between_2_BLH(double B1, double L1, double B2, double L2)
{
	//�������������㹫ʽΪ        
	//d��111.12cos{1/[sin��Asin��Bʮ   cos��Acos��Bcos(��B����A)]}    
	//����A�㾭�ȣ�γ�ȷֱ�Ϊ��A�ͦ�A��B��ľ��ȡ�γ�ȷֱ�Ϊ��B�ͦ�B��dΪ���롣
	//Dist = 6378 * ACOS(COS(LatA) * COS(LatB) * COS(LngB - LngA) + SIN(LatA) * SIN(LatB))
	return 6371e3 * acos(sin(B1 * PI / 180) * sin(B2 * PI / 180) + cos(B1 * PI / 180) * cos(B2 * PI / 180) * cos((L2 - L1)  * PI / 180));
}

// �������ļ����ȡ·����䵽�����m_mapParams�ṹ����
int CUAV_SpiderView::ReadMapPathConfig()
{
	char myCurDir[256], myCurConfigDir[256], myCurSaveDir[256];//��ǰģ��·���������ļ�·�������ݼ�¼�ļ�·����
	char curModularPath[256];
	GetCurrentDirectory(255,curModularPath);	// ��ȡ��ǰ·��

	sprintf_s(myCurConfigDir, 255, "%s\\Config", curModularPath);

	int rtn,cnt;
	float f1,f2,f3;
	int   int1, int2, int3, int4;
	char cstr[255], cstr2[255], cstr3[255];

	char FilePath[255] = "";
	strncat(FilePath, myCurConfigDir,255);
	strncat(FilePath, "\\CenterStation.config",255);

	FILE *pFile = fopen(FilePath, "r");
	if(pFile == NULL)
	{
		AfxMessageBox(_T("�����Ҳ���CenterStation.config�ļ���\n�����˳���"));
		//mainDlg->OnBnClickedButtonMaindlgMaindlgQuit();
		return -998;
	}
	char buffer[255], *pChar;
	cnt = 0;
	while(fgets(buffer, 255, pFile) != NULL)
	{
		int NoteLine = 0;
		for(int i=0; i< strlen(buffer); i++)
		{
			if(buffer[i] == '!')
			{
				NoteLine = 1;	//����ע����
				break;
			}
			if(buffer[i] != ' ')
				break;
		}//for
		if(NoteLine)
			continue;//����ע����
		if(strstr(buffer, "ʹ�����ǵ�ͼ") != NULL)
		{
			pChar = strchr(buffer, '=');
			int rtn = sscanf(&pChar[1], "%d", &int1);		// ��ȡ��ʹ�����ǵ�ͼ=��֮�����ֵ����int1
			if(rtn != 1 || int1 < 0 || int1 > 2)			// rtn�ķ���ֵ����ֵ�ɹ��Ĳ�����������Ϊ�˴�ֻ��1���������ɹ�Ӧ��Ϊ1��int1ֻ��ȡֵΪ0����1���֣�����ʹ�û�ʹ�����ǵ�ͼ
			{
				AfxMessageBox(_T("CenterStation.config�ļ���ʽ����169\n�����˳���"));
				// mainDlg->OnBnClickedButtonMaindlgMaindlgQuit();   // �˳������һЩ��β��ɨ����
				return -998;
			}
			m_mapParams.UsingSatelliteMap = int1;			// ȷ���Ƿ�ʹ�����ǵ�ͼ
		}
		if(strstr(buffer, "���ǵ�ͼ�ļ���·��") != NULL)
		{
			pChar = strchr(buffer, '=');
			int rtn = sscanf(&pChar[1], "%s", cstr);
			if(rtn != 1)
			{
				AfxMessageBox(_T("CenterStation.config�ļ���ʽ����170\n�����˳���"));
				// mainDlg->OnBnClickedButtonMaindlgMaindlgQuit();  // �˳������һЩ��β��ɨ����
				return -998;
			}
			strncpy(m_mapParams.SatelliteFoldPath, cstr, 255);			// ȷ�����ǵ�ͼ·��SatelliteFoldPath
		}
		if(strstr(buffer, "SHP��ͼ�ļ���·��") != NULL)
		{
			pChar = strchr(buffer, '=');
			int rtn = sscanf(&pChar[1], "%s", cstr);
			if(rtn != 1)
			{
				AfxMessageBox(_T("CenterStation.config�ļ���ʽ����171\n�����˳���"));
				// mainDlg->OnBnClickedButtonMaindlgMaindlgQuit();   // �˳������һЩ��β��ɨ����
				return -998;
			}
			strncpy(m_mapParams.MapFileFoldPath, cstr, 255);			// ȷ��ʸ����ͼ·��MapFileFoldPath
		}
	}
	return 1;
}

//��ȡ \Config\ͼ����ʾ��.xls  �е�ͼ����ʾ��Ϣ����--->>>ͼ�����ݶ�ȡ��������
void CUAV_SpiderView::GetLayerShowConfigInfo(CString FilePath)
{
	FILE *pF = NULL;
	char buf[1024], buf2[1024], colstr[256];
	int rtn,cnt;
	float f1,f2,f3;
	int   int1, int2;
	char cstr[255], cstr2[255], cstr3[255];
	//-----------�޸Ķ�ȡxls���룬����:13.10.14---------
	CString sSql, str;
	CString sItem;
	CString sDsn;
	int uInt1, uInt2, uInt3;
	char errmsg[256];

	// �������д�ȡ���ַ���
	MAPWINGIS_LAYERSHOWINFO tempNode;
	myShpLayerShowInfoVec.clear();
	pF = fopen(FilePath, "r");
	if(pF == NULL)
	{
		sprintf(errmsg, "ERROR#3248\n\t��<ͼ����ʾ���ñ�.csv>�ļ�ʧ��, ErrorCode = %d", GetLastError());
		AfxMessageBox(errmsg);
		//OnBnClickedButtonMaindlgMaindlgQuit();
		return;
	}
#ifndef UUU_3241
	// ��ȡ��ѯ���			
	int counter = 0;  //��¼�������������ÿ����Ԫ��ֵ�Ƿ�Ҫ����2--5


	cnt = -1;
	while ( fgets(buf, 511, pF) )
	{
		if(cnt < 0)
		{
			cnt++;
			continue;
		}
		CString show;
		int k = 1; int colm = 1;
		strncpy(buf2, buf, 511);
		char *pStart = buf;
		char *pEnd = strchr(buf, ',');		//��ʼ����
		int curBytes = strlen(buf);
		int strPOS, endPos, rtn;
		char *pSTR;

		for(long i = 0; i < 10; ++i) //16��
		{
			if(i > 0)
			{
				pStart = &pEnd[1];
				pEnd = strchr(pStart, ','); if(pEnd == NULL) pEnd = &buf[curBytes]; 
			}
			endPos = (unsigned int)pEnd -  (unsigned int)buf;
			buf2[endPos] = '\0';
			strPOS = (unsigned int)pStart -  (unsigned int)buf;	//��ǰ�д�����ʼ�±�
			pSTR = &buf2[strPOS];	//��ǰ�д�
			colstr[0] = '\0';
			if(strlen(pSTR) > 0) rtn = sscanf(pSTR, "%s", colstr);	//��ȡ�д�								
			str= colstr;

			switch(i)
			{
			case 0:
				//��COL--01��== ���
				break;
			case 1:
				//��COL--02��== ͼ���ļ��� 
				strncpy(tempNode.LayerName,str, 63);	
				for(int kk=0; kk < 3; kk++)
				{
					if(strstr(tempNode.LayerName, MAPWINGIS_LAYERTYPE[kk]) != NULL)
					{
						tempNode.layerType = kk;			//����ͼ���ļ���ȷ��ͼ�����ͣ�3�����ͣ�0 == region��1 == polyline��2 == point
						break;
					}
				}//for kk
				break;
			case 2:
				//��COL--03��== ͼ����ʾ��־ 
				if(str.Find('A') >= 0)
					tempNode.IsLayerShow = 1;			//
				else
					tempNode.IsLayerShow = 0;	
				break;
			case 3:
				//��COL--04��== ��ǩ��ʾ��־ 
				if(str.Find('A') >= 0)
					tempNode.IsLabelShow = 1;
				else
					tempNode.IsLabelShow = 0;	
				break;
			case 4:
				//��COL--05��== ���ɫ
				uInt1 = 0; uInt2 = 0; uInt3 = 0;
				sscanf(str, "%d;%d;%d", &uInt1, &uInt2, &uInt3);
				tempNode.Color_Fill = uInt1 | (uInt2 << 8) | (uInt3 << 16);	//
				break;
			case 5:
				//��COL--06��== ����ɫ
				uInt1 = 0; uInt2 = 0; uInt3 = 0;
				sscanf(str, "%d;%d;%d", &uInt1, &uInt2, &uInt3);
				tempNode.Color_Line = uInt1 | (uInt2 << 8) | (uInt3 << 16);	//����ɫ
				break;
			case 6:
				//��COL--07��== ��ɫ
				uInt1 = 0; uInt2 = 0; uInt3 = 0;
				sscanf(str, "%d;%d;%d", &uInt1, &uInt2, &uInt3);
				tempNode.Color_Point = uInt1 | (uInt2 << 8) | (uInt3 << 16);	//���ɫ
				break;
			case 7:
				//��COL--08��== �߿�
				uInt1 = 0; uInt2 = 0; uInt3 = 0;
				sscanf(str, "%d", &uInt1);
				tempNode.LineWidth = max(uInt1, 1);	//�߿�
				break;
			case 8:					
				//��COL--09��== ��ߴ�
				uInt1 = 0; uInt2 = 0; uInt3 = 0;
				sscanf(str, "%d", &uInt1);
				tempNode.PointSize = max(uInt1, 1);	//���С
				break;
			case 9:
				//��COL--10��== ��ʾ����
				uInt1 = 0; uInt2 = 0; uInt3 = 0;
				sscanf(str, "%d", &uInt1);
				tempNode.ShowRank = max(uInt1, 0);	//��ʾ����
				break;
			}//switch

		}//for i

		cnt++;
		tempNode.layerHandle = -1;
		if(strlen(tempNode.LayerName) > 2)
			myShpLayerShowInfoVec.push_back(tempNode);
	}//while

#endif //LOAD_LAYER_SETUP
	fclose(pF);
	std::sort (myShpLayerShowInfoVec.begin(), myShpLayerShowInfoVec.end(), Func_VectorSort_ShpShowConfig_Type);		//����ͼ��������������

	return;
}

long CUAV_SpiderView::CreateShapefile(LPCTSTR sFilename, int IsLabelVisible)
{
	int layerHandle = 0;
	VARIANT_BOOL retVal = FALSE;
	CString bstrFilename = sFilename;
	CString bstrFieldName;
	HRESULT hr;
	IShapefilePtr pShapefile;
	pShapefile.CreateInstance(__uuidof(Shapefile));
	CheckShapefileError(pShapefile);
	long FieldIndex = 0;
	IFieldPtr pField;
	hr = pField.CreateInstance(__uuidof(MapWinGIS::Field));
	if (!bstrFilename)
		bstrFieldName = "InMemoryFile";
	else
		bstrFieldName = sFilename;
	hr = pField->put_Name((_bstr_t)bstrFieldName);
	VARIANT_BOOL vb;
	pShapefile->raw_Open((_bstr_t)bstrFieldName, NULL, &vb);
	//����ͼ��
	layerHandle = map_CtrInterface->AddLayer(pShapefile, TRUE);
	CString str = map_CtrInterface->GetErrorMsg(layerHandle);
	shpLayerNums++;		//ͼ�������� 1
	return layerHandle;
}

void CUAV_SpiderView::CheckShapefileError(::IShapefilePtr p)
{
	long ErrorCode = 0;
	BSTR bstrErrorMsg;
	CString sErrorMsg;
	HRESULT hr;
	hr = p->get_LastErrorCode(&ErrorCode);
	// - Note to reader - Test the return value of hr
	if (ErrorCode != 0)
	{
		hr = p->get_ErrorMsg(ErrorCode, &bstrErrorMsg);
		//- Note to reader - Test the return value of hr
		sErrorMsg.Format("Shapefile Error [%d]: %s", ErrorCode, bstrErrorMsg);
		AfxMessageBox(sErrorMsg);
	}
}

int CUAV_SpiderView::LoadMap()
{
	if (ReadMapPathConfig()==-998)
	{
		AfxMessageBox("���ص�ͼʧ�ܣ�");
		return 0;
	}

	myMAP_MapWinGis.SetBackColor(RGB(255, 255, 255));
	//��01��--ͼ������ʼ��	
	Map_ShowRank_Status = 0;
	shpLayerNums = 0;
	//myMap_lineLayerHandle											= -1;
	//myMap_TrackLayerHandle											= -1;
	//myMap_TdoaCurveLayerHandle									= -1;
	//mySpecialTask_MeaResLayerHandle		= -1;
	//mySpecialTask_FinalPlotBLH[0]	= 0;					//����ͼʱ��BLH��
	//mySpecialTask_FinalPlotBLH[1]	= 0;					//����ͼʱ��BLH��
	//mySpecialTask_FinalPlotTimeD		= 0;					//����ͼʱ��ʱ�䣻
	//mySpecialTask_MeaResLayerHandle_Newest = -1;
	//myMap_FieldIntensityMap	= -1;
	//m_DrawLine = FALSE;			//Ĭ��Ϊ�ǻ���ģʽ
	//myMap_TowerLayerHandle_BeingUsed = 0;//����ͼ�����ڱ�(TDOAģ��)ʹ��--��ʱ���ܸ������������

	//--[02]--��ȡͼ����ʾ������ϢExcel�ļ�
	char buf[256];
	GetCurrentDirectoryA(sizeof(buf),buf);
	CString relativeDir;
	relativeDir = buf;
	//��ȡ������	std::vector <MAPWINGIS_LAYERSHOWINFO>	myShpLayerShowInfoVec; --->>>�������������ˣ�
	GetLayerShowConfigInfo(relativeDir + "\\Config\\ͼ����ʾ���ñ�.csv");	
	//--[03]--���ص�ͼ�ļ�

	long layerHandle = -1;
	CString shpFilePath = ""; char fName[64];

	if(strlen(m_mapParams.MapFileFoldPath) > 4)
	{
		for(int i=0; i< myShpLayerShowInfoVec.size(); i++)
		{

			if(strlen(myShpLayerShowInfoVec.at(i).LayerName) < 4)
				break;
			if(myShpLayerShowInfoVec.at(i).IsLayerShow == 0)
				continue;
			shpFilePath.Format("%s\\%s", m_mapParams.MapFileFoldPath, myShpLayerShowInfoVec.at(i).LayerName);
			if (0 == _access(shpFilePath,0))			//�ļ��Ƿ����   ��Ҫͷ�ļ�<io.h>
			{
				layerHandle = CreateShapefile(shpFilePath,myShpLayerShowInfoVec.at(i).IsLabelShow);
				strncpy(fName, myShpLayerShowInfoVec.at(i).LayerName, 63);
				char *pChar = strstr(fName, ".shp");
				pChar[0] = '\0';
				if(1)
				{
					map_CtrInterface->PutShapeLayerLineWidth(layerHandle,(float)myShpLayerShowInfoVec.at(i).LineWidth);
					map_CtrInterface->PutShapeLayerLineColor(layerHandle,(OLE_COLOR)myShpLayerShowInfoVec.at(i).Color_Line);	//0x000000ff����ɫ
					map_CtrInterface->PutShapeLayerPointColor(layerHandle,(OLE_COLOR)myShpLayerShowInfoVec.at(i).Color_Point);	
					map_CtrInterface->PutShapeLayerPointSize(layerHandle,(float)myShpLayerShowInfoVec.at(i).PointSize);	
					map_CtrInterface->PutShapeLayerFillColor(layerHandle,(OLE_COLOR)myShpLayerShowInfoVec.at(i).Color_Fill);	
					map_CtrInterface->PutShapeLayerFillTransparency(layerHandle, 0);	//͸����
					if(0 && myShpLayerShowInfoVec.at(i).layerType == 0 && myShpLayerShowInfoVec.at(i).layerCityMargin >= 2)
					{
						map_CtrInterface->PutShapeLayerLineWidth(layerHandle,6);
						map_CtrInterface->PutShapeLayerLineColor(layerHandle,(OLE_COLOR)RGB(255, 0, 0));	//0x000000ff����ɫ
					}
				}
				myShpLayerShowInfoVec.at(i).layerHandle = layerHandle;//��סͼ���
				if(myShpLayerShowInfoVec.at(i).ShowRank > 0 && layerHandle >= 0)
				{
					//HRESULT rtn = map_CtrInterface->RemoveLayerWithoutClosing(layerHandle);	//��ʼ��ʱ����ʾ�͵ȼ�ͼ��
					//int kkk = 0;
					//map_CtrInterface->LayerVisible
				}
				//if(myShpLayerShowInfoVec.at(i).IsLabelShow)
				//{
				//	CString str = myShpLayerShowInfoVec.at(i).LayerName;
				//	ShowLabelsInShapefile(layerHandle,str, i);		//��ʾͼ���ǩ
				//}
				map_CtrInterface->PutLayerName(layerHandle,myShpLayerShowInfoVec.at(i).LayerName);
				//map_CtrInterface->GetShapeLayerStippleTransparent(layerHandle);
				myShpLayerShowInfoVec.at(i).layerPostion = map_CtrInterface->GetLayerPosition(layerHandle);
				if(m_mapParams.UsingSatelliteMap == 1)
					map_CtrInterface->PutShapeLayerFillTransparency(layerHandle, 0);	//͸����---region�����͸����
			}//if
			else
			{
					MessageBox(shpFilePath + "\r\n�ļ������ڣ�","��ʾ",MB_ICONWARNING);
					//return 0;
			}
		}//for
	}

	// 20191128-����--�ֶ������ĸ���+���ĵ����꣬������-��-�� = 1.8*2 Km����-��-�� = 1.2*2 Km
	// ���ĵ�-���ӿƴ���ˮ��У��103.937449,30.756088��
	// ����103.917942,30.767135������103.95604,30.766844������103.917853,30.745334������103.955716,30.745318
	myMapSensorField[0] = 30.745318;
	myMapSensorField[1] = 103.917853;
	myMapSensorField[2] = 30.767135;
	myMapSensorField[3] = 103.95604;

	//--[3]--��ͼ��ʼ״̬����
	//�������ű���
	map_CtrInterface->PutZoomPercent(0.3);
	//�������ģ�͵�
	map_CtrInterface->CursorMode = tkCursorMode::cmNone;
	map_CtrInterface->MapCursor = tkCursor::crsrArrow;
	//������Ϣ��Ӧ
	map_CtrInterface->PutSendMouseDown(VARIANT_TRUE);
	map_CtrInterface->PutSendMouseMove(VARIANT_TRUE);
	map_CtrInterface->PutSendMouseUp(VARIANT_TRUE);
	//���õ�ͼ��ʼ����ʾ����
	//��ȡ��ͼ����
	IExtentsPtr map_Ext;
	map_Ext = map_CtrInterface->Extents;
	//���þ�γ�ȷ�Χ
	map_Ext->SetBounds(myMapSensorField[1] - 0.03,
		myMapSensorField[0] - 0.03,
		0,
		myMapSensorField[3] + 0.03,
		myMapSensorField[2] + 0.03,
		0);

	//��λ�÷�Χ
	map_CtrInterface->PutExtents(map_Ext);
	map_CtrInterface->PutDoubleBuffer ( TRUE );


	//--[4]--���ǵ�ͼ��ʼ��������
	double	mapWidthMeter = Distance_Between_2_BLH(myMapSensorField[0], myMapSensorField[1], myMapSensorField[0], myMapSensorField[3]);
	CRect  mRect;
	GetDlgItem(IDC_MAP_MapWinGis)->GetClientRect(&mRect);
	double mapResolution = mapWidthMeter/(double)mRect.Width();
	myTileMerge.showLevelOfDetail = 8;
	/*if(strlen(m_mapParams.SatelliteRAMDISK) > 0 && 
	m_mapParams.SatelliteRAMDISK[ strlen(m_mapParams.SatelliteRAMDISK) - 1 ] != '\\')
	strcat_s(myCentRunStatus.SatelliteRAMDISK, "\\");
	strncpy(bingTileSystem.RAMDISK, myCentRunStatus.SatelliteRAMDISK, 255);*/
	for(int i=16; i >= 8; i--)
	{
		if(bingTileSystem.GroundResolution(25, i) >= mapResolution)
		{
			myTileMerge.showLevelOfDetail = i;
			break;
		}
	}//for i
	double mwgXmin, mwgYmin, mwgZmin, mwgXmax, mwgYmax, mwgZmax;
	map_Ext->GetBounds(&mwgXmin, &mwgYmin, &mwgZmin, &mwgXmax, &mwgYmax, &mwgZmax);		//MapWinGis����ʾ���ģ�
	myTileMerge.showCenterBL[0] = (mwgYmin + mwgYmax)/2;
	myTileMerge.showCenterBL[1] = (mwgXmin + mwgXmax)/2;
	bingTileSystem.LatLongToPixelXY(myTileMerge.showCenterBL[0], myTileMerge.showCenterBL[1], 
		myTileMerge.showLevelOfDetail, &myTileMerge.showCenterXY[0],  &myTileMerge.showCenterXY[1]);
	strncpy(myTileMerge.tilePATH, m_mapParams.SatelliteFoldPath, 255);
	myTileMerge.guiClientRect = mRect;

	Update_Bing_TileImage();
	long m_layerHandle = myMAP_MapWinGis.NewDrawing(1);
	//myMAP_MapWinGis.set_ShapeLayerDrawFill(m_layerHandle, true); 
	//myMAP_MapWinGis.SetBackColor(0xFF00FF);
	
	myMAP_MapWinGis.DrawCircleEx(m_layerHandle,myTileMerge.showCenterBL[1],myTileMerge.showCenterBL[0],200,0xFF00FF,0.6);
	//myMAP_MapWinGis.DrawCircle(myTileMerge.showCenterBL[1],myTileMerge.showCenterBL[0],200,0xFF00FF,0.6);
	//cv::ellipse(m_mat,myTileMerge.showCenterBL[1],myTileMerge.showCenterBL[0],(150,100),145,(255,255,0),-1);
	return 1;

}

void CUAV_SpiderView::SystemTimeToTime_t(SYSTEMTIME st, time_t *pt)
{
	FILETIME ft;
	SystemTimeToFileTime( &st, &ft );

	LONGLONG ll;

	ULARGE_INTEGER ui;
	ui.LowPart = ft.dwLowDateTime;
	ui.HighPart = ft.dwHighDateTime;

	ll = (ft.dwHighDateTime << 32) + ft.dwLowDateTime;

	*pt = (DWORD)((LONGLONG)(ui.QuadPart - 116444736000000000) / 10000000);
	return;
}

//��ȡ��ǰϵͳȫʵ����ʱ��
double CUAV_SpiderView::GetLocalDoubleTimeSec(SYSTEMTIME curTimeSys)
{
	time_t timeT;
	SystemTimeToTime_t(curTimeSys, &timeT);
	double t = (double)timeT + 1e-3 * (double)curTimeSys.wMilliseconds;
	return t;
}


int CUAV_SpiderView::Update_Bing_TileImage(void)
{
	if(Update_Bing_TileImage_Busy)
		return 0;
	Update_Bing_TileImage_Busy = 1;		//�������룡
	CString str;
	time_t curTimeT;		
	time(&curTimeT);
	SYSTEMTIME curTimeLocal;	
	GetLocalTime(&curTimeLocal);
	double curTimeDouble = GetLocalDoubleTimeSec(curTimeLocal);
	if(curTimeDouble - Update_Bing_TileImage_TimeD < 0.20)	
	{
		Update_Bing_TileImage_Busy = 0;
		return 0;		//ʱ��������2�룻
	}
#ifdef DEBUG_BINGTILE_UPDATE
		TRACE("LINE12128: Start Time = %.3f\n", curTimeDouble);
#endif //DEBUG_BINGTILE_UPDATE
	Update_Bing_TileImage_TimeD = curTimeDouble;
	CRect mapRect;	
	double	mwgXmin, mwgYmin, mwgZmin, mwgXmax, mwgYmax, mwgZmax;
	double	MapWinGis_Cbl[2];				//MapWinGis�ؼ������ĵ�--�������
	int	MapWinGis_CpixlsXY[2];		//MapWinGis�ؼ������ĵ�--BING��������
	cv::Rect showRect;								// ָ��src �� ROI��ͼ������==��������
		//myMap_Ext = map_CtrInterface->Extents;
	if(myMap_Ext == NULL)
		myMap_Ext = map_CtrInterface->Extents;
	//MapWinGIS::IExtentsPtr pExtents = map_CtrInterface->GetExtents();		--->>>�߳����޷���������
	myStartUpdateStatelliteImage = 0;
		//===��ע�͡�===���θı����ĵ��������꣬���Ÿı�cv::MAT���ŵȼ�;
		//--��01��--׼���׶�---���ݡ�MapWinGis�����ĵ����꡿ + ����ǰlevelOfDetail��--->>>���ɺϲ�����ͼƬ
	double	duSatelliteAlignment_deltaXY[2] = {180, -180};		//����ͼ��ʸ��ͼ֮�����������ʸ��ͼ��׼ȷ�ģ�
			//dRX(0.01@34) = 921.84; dRX(0.01@35) = 910.84
			//dRY(0.01@103) = 1111.94
	double	duSatelliteAlignment_deltaBL[2] = {180 * 0.01/915,-180 * 0.01/1112};		//����ͼ��������
	GetDlgItem(IDC_MAP_MapWinGis)->GetClientRect(&mapRect);	//��ͼ�ؼ�CRECT
	int levelOfDetail = myTileMerge.showLevelOfDetail;						//��Ƭ��ͼ����ʾ����
	myMapBounds[0] = 0;
			//----�����������֮ǰ��--����MapWinGis�����ĵ�������BL
	bingTileSystem.LatLongToPixelXY(myTileMerge.showCenterBL[0], myTileMerge.showCenterBL[1],myTileMerge.showLevelOfDetail, &MapWinGis_CpixlsXY[0],&MapWinGis_CpixlsXY[1]);//MapWinGis�ؼ����ĵ�--��������
	myTileMerge.showCenterXY[0] = MapWinGis_CpixlsXY[0];
	myTileMerge.showCenterXY[1] = MapWinGis_CpixlsXY[1];
#ifdef DEBUG_BINGTILE_UPDATE
	TRACE("Line12745  MapWinGis  Cbl= %.4f %.4f  levelOfDetail = %d\n",	myTileMerge.showCenterBL[0], myTileMerge.showCenterBL[1], levelOfDetail);		//MAPWINGIS�ĸ�����Ĵ������
#endif //DEBUG_BINGTILE_UPDATE
	strncpy(myTileMerge.tilePATH, m_mapParams.SatelliteFoldPath, 255);
	myTileMerge.guiClientRect = mapRect;

	int rtn = bingTileSystem.DO_Map_Tiles_Montage_Cache(&myTileMerge, &myImageCache);		//--->>>ִ����Ƭͼ��ϲ�
	
//#ifdef TestMem


	if(rtn < 0)
				{
				Update_Bing_TileImage_Busy = 0;
				return -1;
				}
		//--��02��---->>>���ݺϲ�ͼƬ���ĸ�����BL����������MapWinGis�ؼ��ĵ�������
			int	MatShowRect_PixlsXY_LT[2], MatShowRect_PixlsXY_RB[2];		//�ϲ�����Ƭͼ�Ķ���--��������<<<----����MAT���Ͻ��������꣬�Լ�MapWinGis�ľ��ο����ĵ����������ã�
			int	dxy[2] = {0};
			dxy[0] = myTileMerge.showCenterXY[0] - myTileMerge.matCenterXY[0];
			dxy[1] = 1 * (myTileMerge.showCenterXY[1] - myTileMerge.matCenterXY[1]);		//cv::MAT�������ĵ���MapWinGis���ĵ��ƫ������
			int	cvmatCXY[2];			//	MapWinGis���ĵ��Ӧ��cv::MAT�еľ��ο�����--��Ҫע�⣺BING��������Y�����Ե���������?????
			cvmatCXY[0] = myTileMerge.matMerged.cols/2 +  dxy[0];
			cvmatCXY[1] = myTileMerge.matMerged.rows/2 + dxy[1];//����cv::MAT�е����ĵ����꣬����MapWinGis���ο�����ص�������չ�����ɻ���ĸ������λ��
			showRect.x = cvmatCXY[0] - mapRect.Width()/2;
			showRect.y = cvmatCXY[1] - mapRect.Height()/2;
			showRect.width = mapRect.Width();
			showRect.height = mapRect.Height();	//cvMAT��Ҫ��ʾ�ľ�������
			if(showRect.x < 0 || showRect.y < 0 || showRect.x + showRect.width>myTileMerge.matMerged.cols ||   showRect.y + showRect.height >myTileMerge.matMerged.rows)
				{
				AfxMessageBox("��ͼ�������#13017�������ǵ�ͼ�����㣡");
				//return -1;
				}
			//����Ҫ��ʾ������ + cvMAT���Ͻ��������꣬����cvMAT����������������
			bingTileSystem.PixelXYToLatLong(	myTileMerge.matLT_XY[0] + showRect.x, 
																			myTileMerge.matLT_XY[1] + showRect.y, 
																			myTileMerge.matLevelOfDetail, 
																			&mwgYmax, &mwgXmin);		//---��001��--���ϽǴ������
			bingTileSystem.PixelXYToLatLong(	myTileMerge.matLT_XY[0] + showRect.width  + showRect.x, 
																			myTileMerge.matLT_XY[1] + showRect.height + showRect.y, 
																			myTileMerge.matLevelOfDetail, 
																			&mwgYmin, &mwgXmax);		//---��002��--���½Ǵ������
			#ifdef DEBUG_BINGTILE_UPDATE
			TRACE("Line12262  MapWinGis PutExtents  C��%.3f, %.3f; %.3f, %.3f��\n",	mwgXmin, mwgYmin, mwgXmax, mwgYmax);		//MAPWINGIS�ĸ�����Ĵ������
			#endif //DEBUG_BINGTILE_UPDATE
			if(mwgXmin < 0)
				char msg[] = "BUG";
			myMap_Ext->SetBounds(mwgXmin, mwgYmin, 0, mwgXmax, mwgYmax, 0);		//����MapWinGis�ľ�����--->>>���ݴ����������	
			map_CtrInterface->PutExtents(myMap_Ext);
			//Sleep(30);
			MapWinGIS::IExtentsPtr pExtents = map_CtrInterface->GetExtents();
			//pExtents->SetBounds(mwgXmin, mwgYmin, 0, mwgXmax, mwgYmax, 0);	
			double Xmin = pExtents->GetxMin(); double Xmax = pExtents->GetxMax();
			double Ymin = pExtents->GetyMin(); double Ymax = pExtents->GetyMax();							//��ʱ��õ�һ�����������ò�ͬ��γ������--->>>ʹ�������γ������--->>>��������Ϊ׼ȷ��������
			myMap_BLPerPixel = (Ymax - Ymin)/(double)mapRect.Width();
			//HRESULT hRes8 = myMap_Ext->GetBounds(&mwgXmin, &mwgYmin, &mwgZmin, &mwgXmax, &mwgYmax, &mwgZmax);		//����MapWinGis�ľ�����--->>>���ݴ����������-->>>��׼ȷ������
			//mwgXmin = 118.52050781250000  mwgYmin = 24.901929811256295 mwgXmax = 118.56831550598145 mwgYmax = 24.924504534441326

	#ifndef USING_SATELLITE_MAP_LAYER_VERIFY
		#ifdef DEBUG_BINGTILE_UPDATE
		TRACE("Line12723 MapWinGis Rect��%d, %d, %d, %d��; GIS: X(%.4f->%.4f)   Y(%.4f->%.4f)  Cbl= %.4f %.4f\n",	mapRect.left, mapRect.top, mapRect.Width(), mapRect.Height(),
																																							mwgXmin, mwgXmax, mwgYmin, mwgYmax,
																																							(mwgXmin + mwgXmax)/2, (mwgYmin + mwgYmax)/2);		//MAPWINGIS�ĸ�����Ĵ������
		#endif //DEBUG_BINGTILE_UPDATE
		int pixleXY_LT[2], pixleXY_RB[2];	//MapWinGis�ؼ��Ľǵ���������
		bingTileSystem.LatLongToPixelXY(mwgYmax, mwgXmin, levelOfDetail, &pixleXY_LT[0],  &pixleXY_LT[1]);		//���Ͻ�
		bingTileSystem.LatLongToPixelXY(mwgYmin, mwgXmax, levelOfDetail, &pixleXY_RB[0],  &pixleXY_RB[1]);		//���½�
		#ifdef DEBUG_BINGTILE_UPDATE
		TRACE("Line12724 MapWinGis PIXLS: X(%d->%d)   Y(%d->%d)  ;C = %d, %d\n",	pixleXY_LT[0], pixleXY_RB[0], pixleXY_LT[1], pixleXY_RB[1], 
																																		(pixleXY_LT[0] +pixleXY_RB[0])/2, (pixleXY_LT[1] + pixleXY_RB[1])/2);		//MAPWINGIS�ĸ��������������

		TRACE("Line12725 ��߱ȣ���MapCtrl=%.4f    ;Image = %.4f\n",	(double)mapRect.Width()/(double)mapRect.Height(), 
																																		(mwgXmin - mwgXmax)/(mwgYmin - mwgYmax));		//MAPWINGIS�ĸ��������������
		#endif //DEBUG_BINGTILE_UPDATE

		//Line12725 ��߱ȣ���MapCtrl=1.7796    ;Image = 1.9621 == >>�����⡿���ڿؼ���߱ȣ���BING��Ƭ֮��Ŀ�߱��ǲ�ͬ�ģ����Ե������Ե����===>>>��ν�����
		//Ϊ�˽����߱Ȳ�ͬ�����⣬ʹ��cvResize, ��������������10%������ֱ��ͬ���ظ��ƣ�ÿ10��ȥ��һ�У�

	#endif //USING_SATELLITE_MAP_LAYER_VERIFY

	#ifndef USING_SATELLITE_MAP_LAYER
		//--�������ǵ�ͼ��ʾ������--�̶����������䣬ʹ�ð�ťȷ������ͼ���Ƿ�ɼ�������������ͼ��ɼ�������������Ϊ�̶����䣻�ı�scale������������ͼ�㲻�ɼ���
		//--ʹ��<100����==X��>���̻�����ͼ�����ʾ��
		if("UsingSattelliteMap")
			{
			#ifndef FIT_IMAGE2DLGRECT_WIDTHEIGHTRATIO
				int showRectHeight = showRect.height;
				showRect.y -= mapRect.Height()/20;						
				showRect.y = max(showRect.y, 0);
				showRect.height += mapRect.Height()/10;			
				showRect.height = min(showRect.height, myTileMerge.matMerged.rows);


			#endif //FIT_IMAGE2DLGRECT_WIDTHEIGHTRATIO
			#ifdef DEBUG_BINGTILE_UPDATE
				TRACE("Line16372--BUG showRect��x%d y%d w%d h%d��\n", showRect.x, showRect.y, showRect.width, showRect.height);
			#endif //DEBUG_BINGTILE_UPDATE
			if(myTileMerge.matMerged.rows < showRect.y +  showRect.height)
				{
				Update_Bing_TileImage_Busy = 0;
				return 0;
				}
			if(myTileMerge.matMerged.cols < showRect.x +  showRect.width)
				{
				Update_Bing_TileImage_Busy = 0;
				return 0;
				}
			//����ͼƬ--ƫ��У׼--�ο�ʸ��ͼ
			int uuDXY[2];
			switch(myTileMerge.showLevelOfDetail)
				{
				case 16:
					uuDXY[0] = 110;
					uuDXY[1] = 110;
					break;
				case 15:
					uuDXY[0] = 44 + 8;
					uuDXY[1] = 44 + 8;
					break;
				case 14:
					uuDXY[0] = 22 + 4;
					uuDXY[1] = 22 + 4;
					break;
				default:
					uuDXY[0] = 26/(15 - myTileMerge.showLevelOfDetail);
					uuDXY[1] = 26/(15 - myTileMerge.showLevelOfDetail);
				}//switch
			showRect.x += uuDXY[0];
			showRect.y += uuDXY[1];		//���ǵ�ͼ��ƫ�����ο�ʸ��ͼ

			if(myTileMerge.matMerged.empty())
				{
				Update_Bing_TileImage_Busy = 0;
				return 0;
				}
			if(showRect.x < 0 || showRect.x + showRect.width > myTileMerge.matMerged.cols ||
				showRect.y < 0 || showRect.y + showRect.height > myTileMerge.matMerged.rows)
				{
				Update_Bing_TileImage_Busy = 0;
				return 0;
				}
			#ifdef DEBUG_BINGTILE_UPDATE
				TRACE("Line16362--BUG showRect��x%d y%d w%d h%d��\n", showRect.x, showRect.y, showRect.width, showRect.height);
				TRACE("Line16363--BUGMAT w = %d; h= %d\n", myTileMerge.matMerged.cols, myTileMerge.matMerged.rows);
			#endif //DEBUG_BINGTILE_UPDATE
			cv::Mat showRoiMat;
			try	
				{
				showRoiMat = myTileMerge.matMerged(showRect); // �õ� dstָ��������ͼ�������
				}
			catch(cv::Exception& e) 
			{ 
			  AfxMessageBox(e.what()); 
			} 
			if(showRoiMat.rows <= 0 || showRoiMat.cols <= 0)
				{
				Update_Bing_TileImage_Busy = 0;
				return 0;
				}
			#ifndef FIT_IMAGE2DLGRECT_WIDTHEIGHTRATIO
		#ifdef DEBUG_BINGTILE_UPDATE
		TRACE("Line16372(1)--BUG showRectHeight=%d showRoiMat.cols = %d\n", showRectHeight, showRoiMat.cols);
		#endif //DEBUG_BINGTILE_UPDATE
				if(showRoiMat.empty())
					{
					Update_Bing_TileImage_Busy = 0;
					return 0;
					}
				cv::Mat showRoiMatB(showRectHeight, showRoiMat.cols, CV_8UC3);
				//cvResize(showRoiMat, showRoiMatB, CV_INTER_LINEAR );
				cv::Size dstSize;		dstSize.height = showRectHeight;		dstSize.width = showRoiMat.cols;
			if(dstSize.height <= 0 || dstSize.width <= 0)
				{
				Update_Bing_TileImage_Busy = 0;
				return 0;
				}
			cv::resize(showRoiMat, showRoiMatB, dstSize, 0,0, CV_INTER_LINEAR );
			if(showRoiMatB.rows <= 0 || showRoiMatB.cols <= 0)
				{
				Update_Bing_TileImage_Busy = 0;
				return 0;
				}
			#endif 
			/*****************************************************************************************************
			*														������MAP_ShapeFile��															*
			*****************************************************************************************************/
			#ifndef SAVE_showRoiMatB_to_FILE
			IplImage *saveImg = (IplImage *)&showRoiMatB.operator IplImage();			//MatתIplImage
			CRect gisRECT;		GetDlgItem(IDC_MAP_MapWinGis)->GetWindowRect(&gisRECT);
					//��ʱ��õ�һ�����������ò�ͬ��γ������--->>>ʹ�������γ������--->>>��������Ϊ׼ȷ��������
			#ifdef DEBUG_BINGTILE_UPDATE
			TRACE("Line16894 MapGisBL = L: %.4f~%.4f (pixlsW=%d); B: %.4f~%.4f (pixlsH=%d);  dlgW = %d/%d\n",
						Xmin, Xmax, saveImg->width, Ymin, Ymax, saveImg->height, gisRECT.Width(), gisRECT.Height());
			#endif //DEBUG_BINGTILE_UPDATE
			try
				{
					str.Format("%sssstemp.bmp", "");
					cvSaveImage(str, saveImg);
				//#ifdef DEBUG_BINGTILE_UPDATE
				//	TRACE("Line17004: Save Satellite Image2File: %s\n", str);
				//#endif //DEBUG_BINGTILE_UPDATE
				}
			catch(cv::Exception& e) 
			{ 
			  AfxMessageBox(e.what()); 
			} 
			showRoiMat.release();
			showRoiMatB.release();
			#endif //SAVE_showRoiMatB_to_FILE

			//����Image�㣬�������ص�λ������ͼ�����½����꣬����ͼ�����ݣ�
			#ifndef TEST_SEGMENT
				//��C01��--ͼ���ļ�·��
				#ifndef GET_IMAGE_PATH
				char buf[256];
				GetCurrentDirectoryA(sizeof(buf),buf);
				CString relativeDir = buf;
				char iamgeMapFileName[256];		// = "h:\\ssstemp.jpg";
				sprintf_s(iamgeMapFileName, 255, "%sssstemp.bmp","");
				CString imgMapFile = relativeDir  + iamgeMapFileName;
				#endif //GET_IMAGE_PATH

				HRESULT resH;	  int rtnM;

					if(myMap_SatelliteImgPtr == NULL)
						resH = myMap_SatelliteImgPtr.CreateInstance(__uuidof(Image));		//��Ӧ���ͷź���myMap_SatelliteImgPtr->Release();
					if(myMap_SatelliteImgPtr->GetWidth() > 0)
							myMap_SatelliteImgPtr->Close();
					rtnM = myMap_SatelliteImgPtr->Open((_bstr_t)iamgeMapFileName, MapWinGIS::ImageType::USE_FILE_EXTENSION, true, NULL);		//BITMAP_FILE
					int imageW = myMap_SatelliteImgPtr->GetWidth();
					int imageH = myMap_SatelliteImgPtr->GetHeight();
					double imageDX = (Xmax - Xmin)/imageW;
					double imageDY = (Ymax - Ymin)/imageH;
					myMap_SatelliteImgPtr->put_dX(imageDX);
					myMap_SatelliteImgPtr->put_dY(imageDY);
					myMap_SatelliteImgPtr->PutXllCenter(Xmin);
					myMap_SatelliteImgPtr->PutYllCenter(Ymin);
					if(myMap_ImageMapLayerHandle == -1 && myMap_SatelliteImgPtr != NULL)
						{
						myMap_ImageMapLayerHandle = map_CtrInterface->AddLayer(myMap_SatelliteImgPtr,TRUE);

						long layerPostion_ImageMap = map_CtrInterface->GetLayerPosition(myMap_ImageMapLayerHandle);
						rtnM = map_CtrInterface->MoveLayerBottom(layerPostion_ImageMap);
						}
				myImgSatelliteMap_CNT++;
			#endif //TEST_SEGMENT
			}//if("UsingSattelliteMap")
	#endif //USING_SATELLITE_MAP_LAYER

Update_Bing_TileImage_Busy = 0;
Update_Bing_TileImage_Cmd = 0;
//#endif
return 0;
}


//void CUAV_SpiderView::OnMouseHWheel(UINT nFlags, short zDelta, CPoint pt)
//{
//	// �˹���Ҫ�� Windows Vista ����߰汾��
//	// _WIN32_WINNT ���ű��� >= 0x0600��
//	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
//
//	CView::OnMouseHWheel(nFlags, zDelta, pt);
//}


BOOL CUAV_SpiderView::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	if(m_mapParams.UsingSatelliteMap > 0 && myMapWinGis_PANING == 0)
	{
		if(zDelta > 0)
		{
			myTileMerge.showLevelOfDetail = min(myTileMerge.showLevelOfDetail + 1, SATELLET_TILEMAP_ZOOMMAX);
			myMapWinGis_PANING++;
			Update_Bing_TileImage();
		}
		else if(zDelta < 0)
		{
			myTileMerge.showLevelOfDetail = max(myTileMerge.showLevelOfDetail - 1, SATELLET_TILEMAP_ZOOMMIN);
			myMapWinGis_PANING++;
			Update_Bing_TileImage();
		}
		myMapWinGis_PANING = 0;
		return CView::OnMouseWheel(nFlags, zDelta, pt);
	}
	double curMapZomm = map_CtrInterface->GetZoomPercent();
	if(zDelta > 0)
	{
		map_CtrInterface->ZoomIn(0.1);
	}
	if(zDelta < 0)
	{
		map_CtrInterface->ZoomOut(0.1);
	}
	double curMapZommB = map_CtrInterface->GetZoomPercent();
	TRACE("Line10158:  zDelta = %d nFlags = %d ZoomA = %.2f ZoomB = %.2f\n", zDelta, nFlags, curMapZomm, curMapZommB);		//�Ϲ���ʱzDelta �� 0���¹���ʱ�� zDelta  0;
	if(myMap_ImageMapLayeVisble == 1)
	{
		map_CtrInterface->PutLayerVisible(myMap_ImageMapLayerHandle, 1);
		myMap_ImageMapLayeVisble = 0;
	}
	return CView::OnMouseWheel(nFlags, zDelta, pt);
}


void CUAV_SpiderView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

	CView::OnLButtonDown(nFlags, point);
}


void CUAV_SpiderView::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

	CView::OnLButtonUp(nFlags, point);
}
