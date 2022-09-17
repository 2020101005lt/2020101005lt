#pragma once
#include<opencv2/opencv.hpp>
using namespace cv; 
#define SATELLET_TILEMAP_ZOOMMAX 16
#define SATELLET_TILEMAP_ZOOMMIN 8			//卫星图层的级别区间
#define	MAP_LONG		long

enum TcpSrc{TCP_DETECT=0,TCP_TRAP};
// Detect Protocol
enum ECmdType
{
	eCmdTypeInvalid						= 0x00,	//无效命令
	eCmdTypeHeartbeat					= 0x01,	//心跳包
	eCmdTypeDeviceStatus				    = 0x02,	//获取设备状态 
	eCmdTypeIQData						= 0x03,	//获取原始IQ数据，未使用
	eCmdTypeGPSData						= 0x04,	//获取GPS数据
	eCmdTypeCompassData					= 0x05,	//获取电子罗盘数据，未使用
	eCmdTypeMonitorAlarm				= 0x06,	//返回监测告警结果

	eCmdTypeSpectrumParam				= 0x10,	//下发频谱监测参数
	eCmdTypeSpectrumData				= 0x11,	//返回频谱结果数据
	eCmdTypeSpectrumOn					= 0x12,	//频谱数据上传[开]
	eCmdTypeSpectrumOff					= 0x13,	//频谱数据上传[关]
	eCmdTypeScanMode                    = 0x14, //设置扫描模式
	eCmdTypeEnviMode                    = 0x15, //设置环境模式

	eCmdTypeTrackData					= 0x20,		//跟踪数据，未使用
	eCmdTypeTrackOn						= 0x21,		//跟踪[开]
	eCmdTypeTrackOff					    = 0x22,		//跟踪[关]

	eCmdTypeMonitorAirCtrl				= 0x30,      //设置监测模式[飞控]
	eCmdTypeMonitorImageTran			    = 0x31,		//设置监测模式[图传]
	eCmdTypeGain						= 0x32,		//设置增益控制，未使用
	eCmdTypeAtt                         = 0x33,      //设置衰减控制

	eCmdTypeDfOn						= 0x40,		//测向[开]，未使用
	eCmdTypeDfOff						= 0x41,		//测向[关]，信号发现重置，停止所有测向任务
	eCmdTypeDfData						= 0x42,		//返回测向结果数据
	eCmdTypeDfStop                      = 0x43,      //未使用
	eCmdTypeSignalDisappear             = 0x44,       //返回测向信号消失

	eCmdTypeDfSigFreq                   = 0x45,       //设置测向单频

	eCmdTypeStartWork                   = 0x50,      //开始工作，未使用
	eCmdTypeStopWork                    = 0x51,     //停止工作，未使用

	eCmdTypeInitState                     = 0x60,     //返回初始化状态
};

typedef struct _CENTER_STATION_RUNNING_PARAMS
{
	//【01】--从中心站读取的参数--与COMM无关的
	int			UsingSatelliteMap;			//使用卫星地图的开关：2==BEING地图；1==GOOGLE地图；0=不使用！
	char		SatelliteFoldPath[256];		//地图文件夹全路径--来自配置文件---卫星地图的文件夹路径
	char		MapFileFoldPath[256];		//地图文件夹全路径--来自配置文件
}MAP_PATH_PARAMS;

//【卫星地图所需要的标签点信息数据结构】-->>>使用Read_ShapFile_LabelsXY程序，读取自shp文件--->>>汇编到xls文件中；
typedef struct _SATTELLITE_MAP_LABEL_NODE
{
	char		labelName[64];
	double	labelBL[2];
}SATTELLITE_MAP_LABEL_NODE;
//--1--图层配置信息表--需要进一步完善
typedef struct MAPWINGIS_LAYERSHOWINFO
{
	char					LayerName[64];			//图层名称--全文件名
	int					IsLayerShow;				//是否显示该图层
	int					IsLabelShow;				//该图层是否显示标签
	unsigned int	Color_Point;				//点色彩
	unsigned int	Color_Line;					//线条色彩
	unsigned int	Color_Fill;					//填充色彩
	unsigned int	LineWidth;					//线宽
	unsigned int	PointSize;					//点大小
	unsigned int	ShowRank;					//显示级别：0为必须显示的；1为简练模式下要隐藏的
	long					layerHandle;				//图层句柄--需要记住，再显示时使用
	int					layerPostion;				//图层显示层次--->>>用于动态化的层次修正！
	int					layerType;					//图层类型：0 == region；1 == polyline；2 == point
	int					layerCityMargin;			//1==国界；2==省界；3==市界；4==县界；
}MAPWINGIS_LAYERSHOWINFO;

#define		MAPWINGIS_MAXSHPLAYERNUMS	64			//最大SHP层数
const char	MAPWINGIS_LAYERTYPE[3][16] = {
	"_region",
	"_polyline",
	"_point"
};
const char	MAPWINGIS_LAYERTYPE_ADMINMARGIN[4][16] = {
	"国界",
	"省界",
	"市界",
	"县界"
};
//--->>>卫星地图相关的数据结构
typedef struct _MAP_TILE_MERGE
{
	char		tilePATH[256];										//瓦片图像的路径，末尾不带'\'

	int		showCenterXY[2];									//地图中心点的墨卡托坐标--根据初始BLH确定--->>>随后在漫游后修改
	double		showCenterBL[2];									//地图中心点的墨卡托坐标--根据初始BLH确定--->>>随后在漫游后修改
	int		showLevelOfDetail;								//地图的缩放因子

	cv::Mat		matMerged;										//合并后地图的矩阵
	int		matLT_XY[2];											//合并后地图的XY像素坐标==左上角BING像素坐标
	int		matCopy_DeltaXY[2];							//COPY地图时所使用的偏移量（左上角）--->>>左上角坐标，偏移量，鼠标点--->>计算地图点坐标！
	int		matCenterXY[2];									//合并后地图的XY像素坐标==中间点BING像素坐标
	int		matLevelOfDetail;									//合并后地图的缩放等级


	CRect	guiClientRect;										//显示界面的矩形框-->>调用瓦片合并之前需要设置！
}MAP_TILE_MERGE;

typedef struct _MAP_IMAGE_FILE_CACHE
{
	unsigned int		ImageFoldNo;		//文件夹号码
	unsigned int		ImageTileNo;		//直接使用瓦片号-->>>替代jpg文件名-->>更方便
	unsigned int		HitTimeSec;			//击中时间
	//unsigned int		ImageCenterXY[2];//当前瓦片的中心点坐标-->>>优先剔除 棋盘距离最远的瓦片
	IplImage			*ReadImg;				//读取到的图像文件--每个大致3*64K
}MAP_IMAGE_FILE_CACHE;	//每个图层最多允许cach32个文件-->>8 * 32 * 3 * 64 = 49MB--->>>是可以接受的！