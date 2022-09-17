// UAV_SpiderView.h : interface of the CUAV_SpiderView class
//


#pragma once
#include "map_mapwingis.h"
#include "ButtonDlg.h"
#include "Bing_TileSystem.h"
#include "UserDef.h"
#include "UAV_SpiderDoc.h"
using namespace MapWinGIS;
using namespace std;
#include <opencv2/contrib/contrib.hpp>
#ifdef _DEBUG
#pragma comment(lib, "opencv_contrib242d.lib") 
#pragma comment(lib, "opencv_core242d.lib") 
#pragma comment(lib, "opencv_imgproc242d.lib") //cvresize
#pragma comment(lib, "opencv_highgui242d.lib") //imread
//#pragma comment(lib, "Bing_TileSystem_Debug.lib") //imread


#else
#pragma comment(lib, "opencv_contrib242.lib") 
#pragma comment(lib, "opencv_core242.lib") 
#pragma comment(lib, "opencv_imgproc242.lib") //cvresize
#pragma comment(lib, "opencv_highgui242.lib") //imread
//#pragma comment(lib, "Bing_TileSystem_Realase.lib") //imread
#endif

class CUAV_SpiderView : public CView
{
protected: // create from serialization only
	CUAV_SpiderView();
	DECLARE_DYNCREATE(CUAV_SpiderView)

// Attributes
public:
	CUAV_SpiderDoc* GetDocument() const;
	CMap_mapwingis myMAP_MapWinGis;
//	CComPtr<::_DMap> map_CtrInterface;			
//	MAP_PATH_PARAMS m_mapParams;			// ��ͼ·������--���ڴ������ļ��ж�ȡʸ����ͼ�����ǵ�ͼ������·��
//	int ReadMapPathConfig();				// �������ļ����ȡ·����䵽�����m_mapParams�ṹ����
//	double	myMap_BLPerPixel;				//��ͼ��ÿ�����ش���ľ�γ��ȡֵ��
//	//����������γ��֮��ľ��룬��������λ�ף�
//	double Distance_Between_2_BLH(double B1, double L1, double B2, double L2);
//
//// Operations
//public:
//	double myMapSensorField[4];				//���������ڵĵ�ͼ����[minB, minL, maxB, maxL]--��ȡ�����������ļ�ʱ����--�������õ�ͼ��ʼλ�� + ��ֹ��ͼ�ܷ�����
//	// Operations
//public:
//	// ʸ����ͼ����--20191127����
//	std::vector <MAPWINGIS_LAYERSHOWINFO>	myShpLayerShowInfoVec;
//	int		Map_ShowRank_Status;		//ȱʡģʽ�Ǽ����������ť���Ϊ��ϸģʽ
//	int		shpLayerNums;			//ͼ�㣨Shapefile������    ��Ӧ��ͼ������Ϊ shpLayerNums - 1
//	// ��
//	void GetLayerShowConfigInfo(CString FilePath);
//
//	int LoadMap();
//
//	long CreateShapefile(LPCTSTR sFilename, int IsLabelVisible);
//	void CheckShapefileError(::IShapefilePtr p);
//
//	// ���ǵ�ͼ����--20191127����
//	//--��������--��Ƭ��ͼ��ʼ��-->>>����ʱ����-->>
//	int BingTileMap_ImageInit(void);
//	int Update_Bing_TileImage(void);
//	//��ȡ��ǰϵͳȫʵ����ʱ��
//	double GetLocalDoubleTimeSec(SYSTEMTIME curTimeSys);
//	void SystemTimeToTime_t(SYSTEMTIME st, time_t *pt);
//	//���ǵ�ͼ��ز���
//	std::vector <SATTELLITE_MAP_LABEL_NODE> mySatelliteLabels;			//���ǵ�ͼ��ǵ�����-->>>ʹ��Read_ShapFile_LabelsXY���򣬶�ȡ��shp�ļ�--->>>��ൽxls�ļ��У�
//	vector <MAP_IMAGE_FILE_CACHE> myImageCache;									//�ļ�����--�������ż����-->>��ȡJPG��ʽ���ݵ�����-->>����Ӳ�̶�ȡ����
//	MAP_TILE_MERGE		myTileMerge;																//�������ݽṹ
//	BING_TILESYSTEM		bingTileSystem;														//BING��Ƭ��ͼ������
//	double mySatelliteThdStartTimeD;								//�����̵߳Ŀ�ʼʱ��
//	int myStartUpdateStatelliteImage;							//����we����ͼƬ�ı�־
//	int myMapWinGis_PANING;									//ִ�������εı�־
//	int myMapWinGis_InitOk;										//ִ���˵�ͼ��ʼ���ı�־
//	long myShapefile_PointIndex;									//����ͼƬ�ĵ����
//	int muUpdata_TowerPosition;								//����ͼƬ�ƶ�����Ҫ������������
//	int Update_Bing_TileImage_Busy;
//	int Update_Bing_TileImage_Cmd;
//	double	Update_Bing_TileImage_TimeD;
//
//	CRect myMap_SmallClient;	//Сģʽ�µĵ�ͼ���ο�
//	CRect myMapBigClient;		//ȫ��ģʽ�µĵ�ͼ���ο�
//	int   myMapRectMode;		//��ͼ����ģʽ��0=Сģʽ����ʼ������1=��ģʽ
//	void TAB_DataField_ShowHide(int flag);//�ڵ�ͼ�ߴ����ʱ������TAB_DataField�Լ�ҳ��ɼ��Եĺ���
//	//--��ͼ�����ļ�������--��־ƽ
//	MAP_LONG myMap_lineLayerHandle;	//���߲��ͼ���Handle  [0 --  ...]
//	BOOL	m_DrawLine;				//�Ƿ�Ϊ  ������ģʽ��
//	double	m_StartPoint[2];		//������ģʽ��ʱ  �����
//	int		m_MouseStartXY[2];//�����µ�����
//	CPoint CurMousePoint;
//
//
//	long myMap_ImageMapLayerHandle;		//���ǵ�ͼ��Ӧ��Shapefile��Ӧ��Handle
//	IExtentsPtr	myMap_Ext;
//	double myMapBounds[6];							//�߳��л�ȡ��ͼ����
//	long imgSatelliteMapIndex;						//��ʾ�������ĸ�ͼƬ��Ӧ�� UDPointImageList �е��������ɱ��5��״̬������������7��״̬��
//	int myMap_ImageMapLayeVisble;			//���ǵ�ͼ--����ͼƬ�ɼ���־--��ʼ���ɼ�--ֻ�����ض�scale����ʾ��zoom�¼���ʹ�䲻�ɼ���
//	int myMap_ImageWidth;
//	//2018MARCH:
//	IShapefilePtr myMap_SatelliteShapeFilePtr;										//����ͼƬʹ��
//	IImagePtr myMap_SatelliteImgPtr;								//
//	IPointPtr myMap_SatellitePointPtr;
//	IShapePtr myMap_SatelliteShapePtr;
//	unsigned int myImgSatelliteMap_CNT;			//���´���
// Overrides
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// Implementation
public:
	virtual ~CUAV_SpiderView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
public:
	CComPtr<::_DMap> map_CtrInterface;			
	MAP_PATH_PARAMS m_mapParams;			// ��ͼ·������--���ڴ������ļ��ж�ȡʸ����ͼ�����ǵ�ͼ������·��

	// ʸ����ͼ����--20191127����
	std::vector <MAPWINGIS_LAYERSHOWINFO>	myShpLayerShowInfoVec;
	int	Map_ShowRank_Status;		//ȱʡģʽ�Ǽ����������ť���Ϊ��ϸģʽ
	int	shpLayerNums;			//ͼ�㣨Shapefile������    ��Ӧ��ͼ������Ϊ shpLayerNums - 1
	double	myMap_BLPerPixel;				//��ͼ��ÿ�����ش���ľ�γ��ȡֵ��
	double myMapSensorField[4];				//���������ڵĵ�ͼ����[minB, minL, maxB, maxL]--��ȡ�����������ļ�ʱ����--�������õ�ͼ��ʼλ�� + ��ֹ��ͼ�ܷ�����
	//���ǵ�ͼ��ز���
	std::vector <SATTELLITE_MAP_LABEL_NODE> mySatelliteLabels;			//���ǵ�ͼ��ǵ�����-->>>ʹ��Read_ShapFile_LabelsXY���򣬶�ȡ��shp�ļ�--->>>��ൽxls�ļ��У�
	vector <MAP_IMAGE_FILE_CACHE> myImageCache;									//�ļ�����--�������ż����-->>��ȡJPG��ʽ���ݵ�����-->>����Ӳ�̶�ȡ����
	MAP_TILE_MERGE		myTileMerge;																//�������ݽṹ
	BING_TILESYSTEM		bingTileSystem;														//BING��Ƭ��ͼ������
	double mySatelliteThdStartTimeD;								//�����̵߳Ŀ�ʼʱ��
	int myStartUpdateStatelliteImage;							//����we����ͼƬ�ı�־
	int myMapWinGis_PANING;									//ִ�������εı�־
	int myMapWinGis_InitOk;										//ִ���˵�ͼ��ʼ���ı�־
	long myShapefile_PointIndex;									//����ͼƬ�ĵ����
	int muUpdata_TowerPosition;								//����ͼƬ�ƶ�����Ҫ������������
	int Update_Bing_TileImage_Busy;
	int Update_Bing_TileImage_Cmd;
	double	Update_Bing_TileImage_TimeD;

	long myMap_ImageMapLayerHandle;		//���ǵ�ͼ��Ӧ��Shapefile��Ӧ��Handle
	IExtentsPtr	myMap_Ext;
	double myMapBounds[6];							//�߳��л�ȡ��ͼ����
	long imgSatelliteMapIndex;						//��ʾ�������ĸ�ͼƬ��Ӧ�� UDPointImageList �е��������ɱ��5��״̬������������7��״̬��
	int myMap_ImageMapLayeVisble;			//���ǵ�ͼ--����ͼƬ�ɼ���־--��ʼ���ɼ�--ֻ�����ض�scale����ʾ��zoom�¼���ʹ�䲻�ɼ���
	int myMap_ImageWidth;
	//2018MARCH:
	IShapefilePtr myMap_SatelliteShapeFilePtr;										//����ͼƬʹ��
	IImagePtr myMap_SatelliteImgPtr;								//
	IPointPtr myMap_SatellitePointPtr;
	IShapePtr myMap_SatelliteShapePtr;
	unsigned int myImgSatelliteMap_CNT;			//���´���
	int m_MouseStartXY[2];//�����µ�����

public:
	afx_msg void OnSize(UINT nType, int cx, int cy);
	//��ȡ \Config\ͼ����ʾ��.xls  �е�ͼ����ʾ��Ϣ����--->>>ͼ�����ݶ�ȡ��������
	void GetLayerShowConfigInfo(CString FilePath);	
	// �������ļ����ȡ·����䵽�����m_mapParams�ṹ����
	int ReadMapPathConfig();
	// ���ص�ͼ
	int LoadMap();

	long CreateShapefile(LPCTSTR sFilename, int IsLabelVisible);
	void CheckShapefileError(::IShapefilePtr p);
	//����������γ��֮��ľ��룬��������λ�ף�
	double Distance_Between_2_BLH(double B1, double L1, double B2, double L2);
	int Update_Bing_TileImage(void);
	//��ȡ��ǰϵͳȫʵ����ʱ��
	double GetLocalDoubleTimeSec(SYSTEMTIME curTimeSys);
	void SystemTimeToTime_t(SYSTEMTIME st, time_t *pt);
//	afx_msg void OnBnClickedBtnZoomin();
//	afx_msg void OnBnClickedBtnZoomout();
//	afx_msg void OnBnClickedBtnPan();
//	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
//	// ��ͼ�Ŵ󰴼�
//	CBitmapButton m_btnZoomIn;
//	// ��ͼ��С����
//	CBitmapButton m_btnZoomOut;
//	// ��ͼ���ΰ���
//	CBitmapButton m_btnPan;
//	DECLARE_EVENTSINK_MAP()
//	void DealLabelsVisibleWhileZoomIn_Out();
//	void MouseDownMapMapwingis(short Button, short Shift, long x, long y);
//	void MouseUpMapMapwingis(short Button, short Shift, long x, long y);
//	void GetSelectedShapeIndex(long layerHandle,long x,long y,long *reVal);
//	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
public:
	CButtonDlg m_btnInDlg;
	CButtonDlg m_btnOutDlg;
	CButtonDlg m_btnPanDlg;
//	double m_dbLonCenter;	// ���ĵ�ľ��ȡ���̽���豸��λ��
//	double m_dbLatCenter;	// ���ĵ��γ�ȡ���̽���豸��λ��
//	int m_nRadiusIn;		// ��Բ�뾶
//	int m_nRadiusOut;		// ��Բ�뾶
	CRect m_rctView;
	cv::Mat	m_mat;
	virtual void DoDataExchange(CDataExchange* pDX);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnClose();
	void OnBnClickedBtnZoomin();
	void OnBnClickedBtnZoomout();
	void OnBnClickedBtnPan();
	void DealLabelsVisibleWhileZoomIn_Out();
	void MouseDownMapMapwingis(short Button, short Shift, long x, long y);
	void MouseUpMapMapwingis(short Button, short Shift, long x, long y);
//	afx_msg void OnMouseHWheel(UINT nFlags, short zDelta, CPoint pt);
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	DECLARE_EVENTSINK_MAP()
};

#ifndef _DEBUG  // debug version in UAV_SpiderView.cpp
inline CUAV_SpiderDoc* CUAV_SpiderView::GetDocument() const
   { return reinterpret_cast<CUAV_SpiderDoc*>(m_pDocument); }
#endif
