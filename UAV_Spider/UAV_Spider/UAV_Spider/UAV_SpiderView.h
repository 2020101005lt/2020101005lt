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
//	MAP_PATH_PARAMS m_mapParams;			// 地图路径参数--用于从配置文件中读取矢量地图和卫星地图的完整路径
//	int ReadMapPathConfig();				// 从配置文件里读取路径填充到上面的m_mapParams结构体中
//	double	myMap_BLPerPixel;				//地图上每个像素代表的经纬度取值；
//	//计算两个经纬度之间的距离，输出结果单位米；
//	double Distance_Between_2_BLH(double B1, double L1, double B2, double L2);
//
//// Operations
//public:
//	double myMapSensorField[4];				//传感器所在的地图区域[minB, minL, maxB, maxL]--读取传感器配置文件时设置--用于设置地图初始位置 + 防止地图跑飞设置
//	// Operations
//public:
//	// 矢量地图操作--20191127张敏
//	std::vector <MAPWINGIS_LAYERSHOWINFO>	myShpLayerShowInfoVec;
//	int		Map_ShowRank_Status;		//缺省模式是简练，点击按钮后成为精细模式
//	int		shpLayerNums;			//图层（Shapefile）数量    对应的图层索引为 shpLayerNums - 1
//	// 从
//	void GetLayerShowConfigInfo(CString FilePath);
//
//	int LoadMap();
//
//	long CreateShapefile(LPCTSTR sFilename, int IsLabelVisible);
//	void CheckShapefileError(::IShapefilePtr p);
//
//	// 卫星地图操作--20191127张敏
//	//--【函数】--瓦片地图初始化-->>>启动时调用-->>
//	int BingTileMap_ImageInit(void);
//	int Update_Bing_TileImage(void);
//	//获取当前系统全实数秒时间
//	double GetLocalDoubleTimeSec(SYSTEMTIME curTimeSys);
//	void SystemTimeToTime_t(SYSTEMTIME st, time_t *pt);
//	//卫星地图相关参数
//	std::vector <SATTELLITE_MAP_LABEL_NODE> mySatelliteLabels;			//卫星地图标记点向量-->>>使用Read_ShapFile_LabelsXY程序，读取自shp文件--->>>汇编到xls文件中；
//	vector <MAP_IMAGE_FILE_CACHE> myImageCache;									//文件缓冲--基于缩放级别的-->>读取JPG格式数据到阵列-->>减少硬盘读取次数
//	MAP_TILE_MERGE		myTileMerge;																//核心数据结构
//	BING_TILESYSTEM		bingTileSystem;														//BING瓦片地图操作类
//	double mySatelliteThdStartTimeD;								//卫星线程的开始时间
//	int myStartUpdateStatelliteImage;							//更新we诶行图片的标志
//	int myMapWinGis_PANING;									//执行了漫游的标志
//	int myMapWinGis_InitOk;										//执行了地图初始化的标志
//	long myShapefile_PointIndex;									//卫星图片的点序号
//	int muUpdata_TowerPosition;								//卫星图片移动后，需要更新铁塔坐标
//	int Update_Bing_TileImage_Busy;
//	int Update_Bing_TileImage_Cmd;
//	double	Update_Bing_TileImage_TimeD;
//
//	CRect myMap_SmallClient;	//小模式下的地图矩形框
//	CRect myMapBigClient;		//全屏模式下的地图矩形框
//	int   myMapRectMode;		//地图矩形模式：0=小模式（初始化）；1=大模式
//	void TAB_DataField_ShowHide(int flag);//在地图尺寸调整时，设置TAB_DataField以及页面可见性的函数
//	//--地图操作的几个参数--温志平
//	MAP_LONG myMap_lineLayerHandle;	//画线测距图层的Handle  [0 --  ...]
//	BOOL	m_DrawLine;				//是否为  “画线模式”
//	double	m_StartPoint[2];		//“画线模式”时  的起点
//	int		m_MouseStartXY[2];//鼠标点下的坐标
//	CPoint CurMousePoint;
//
//
//	long myMap_ImageMapLayerHandle;		//卫星地图对应的Shapefile对应的Handle
//	IExtentsPtr	myMap_Ext;
//	double myMapBounds[6];							//线程中获取地图区域
//	long imgSatelliteMapIndex;						//表示铁塔的四个图片对应的 UDPointImageList 中的索引：可表达5个状态，但是现在有7个状态！
//	int myMap_ImageMapLayeVisble;			//卫星地图--卫星图片可见标志--初始不可见--只能在特定scale上显示，zoom事件将使其不可见！
//	int myMap_ImageWidth;
//	//2018MARCH:
//	IShapefilePtr myMap_SatelliteShapeFilePtr;										//卫星图片使用
//	IImagePtr myMap_SatelliteImgPtr;								//
//	IPointPtr myMap_SatellitePointPtr;
//	IShapePtr myMap_SatelliteShapePtr;
//	unsigned int myImgSatelliteMap_CNT;			//更新次数
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
	MAP_PATH_PARAMS m_mapParams;			// 地图路径参数--用于从配置文件中读取矢量地图和卫星地图的完整路径

	// 矢量地图操作--20191127张敏
	std::vector <MAPWINGIS_LAYERSHOWINFO>	myShpLayerShowInfoVec;
	int	Map_ShowRank_Status;		//缺省模式是简练，点击按钮后成为精细模式
	int	shpLayerNums;			//图层（Shapefile）数量    对应的图层索引为 shpLayerNums - 1
	double	myMap_BLPerPixel;				//地图上每个像素代表的经纬度取值；
	double myMapSensorField[4];				//传感器所在的地图区域[minB, minL, maxB, maxL]--读取传感器配置文件时设置--用于设置地图初始位置 + 防止地图跑飞设置
	//卫星地图相关参数
	std::vector <SATTELLITE_MAP_LABEL_NODE> mySatelliteLabels;			//卫星地图标记点向量-->>>使用Read_ShapFile_LabelsXY程序，读取自shp文件--->>>汇编到xls文件中；
	vector <MAP_IMAGE_FILE_CACHE> myImageCache;									//文件缓冲--基于缩放级别的-->>读取JPG格式数据到阵列-->>减少硬盘读取次数
	MAP_TILE_MERGE		myTileMerge;																//核心数据结构
	BING_TILESYSTEM		bingTileSystem;														//BING瓦片地图操作类
	double mySatelliteThdStartTimeD;								//卫星线程的开始时间
	int myStartUpdateStatelliteImage;							//更新we诶行图片的标志
	int myMapWinGis_PANING;									//执行了漫游的标志
	int myMapWinGis_InitOk;										//执行了地图初始化的标志
	long myShapefile_PointIndex;									//卫星图片的点序号
	int muUpdata_TowerPosition;								//卫星图片移动后，需要更新铁塔坐标
	int Update_Bing_TileImage_Busy;
	int Update_Bing_TileImage_Cmd;
	double	Update_Bing_TileImage_TimeD;

	long myMap_ImageMapLayerHandle;		//卫星地图对应的Shapefile对应的Handle
	IExtentsPtr	myMap_Ext;
	double myMapBounds[6];							//线程中获取地图区域
	long imgSatelliteMapIndex;						//表示铁塔的四个图片对应的 UDPointImageList 中的索引：可表达5个状态，但是现在有7个状态！
	int myMap_ImageMapLayeVisble;			//卫星地图--卫星图片可见标志--初始不可见--只能在特定scale上显示，zoom事件将使其不可见！
	int myMap_ImageWidth;
	//2018MARCH:
	IShapefilePtr myMap_SatelliteShapeFilePtr;										//卫星图片使用
	IImagePtr myMap_SatelliteImgPtr;								//
	IPointPtr myMap_SatellitePointPtr;
	IShapePtr myMap_SatelliteShapePtr;
	unsigned int myImgSatelliteMap_CNT;			//更新次数
	int m_MouseStartXY[2];//鼠标点下的坐标

public:
	afx_msg void OnSize(UINT nType, int cx, int cy);
	//读取 \Config\图层显示表.xls  中的图层显示信息内容--->>>图层内容读取到向量中
	void GetLayerShowConfigInfo(CString FilePath);	
	// 从配置文件里读取路径填充到上面的m_mapParams结构体中
	int ReadMapPathConfig();
	// 加载地图
	int LoadMap();

	long CreateShapefile(LPCTSTR sFilename, int IsLabelVisible);
	void CheckShapefileError(::IShapefilePtr p);
	//计算两个经纬度之间的距离，输出结果单位米；
	double Distance_Between_2_BLH(double B1, double L1, double B2, double L2);
	int Update_Bing_TileImage(void);
	//获取当前系统全实数秒时间
	double GetLocalDoubleTimeSec(SYSTEMTIME curTimeSys);
	void SystemTimeToTime_t(SYSTEMTIME st, time_t *pt);
//	afx_msg void OnBnClickedBtnZoomin();
//	afx_msg void OnBnClickedBtnZoomout();
//	afx_msg void OnBnClickedBtnPan();
//	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
//	// 地图放大按键
//	CBitmapButton m_btnZoomIn;
//	// 地图缩小按键
//	CBitmapButton m_btnZoomOut;
//	// 地图漫游按键
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
//	double m_dbLonCenter;	// 中心点的经度——探测设备的位置
//	double m_dbLatCenter;	// 中心点的纬度——探测设备的位置
//	int m_nRadiusIn;		// 内圆半径
//	int m_nRadiusOut;		// 外圆半径
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
