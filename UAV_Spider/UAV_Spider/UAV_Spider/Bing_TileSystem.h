#pragma once
#include <math.h>
#include <iostream>
#include <string>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "opencv2/stitching/stitcher.hpp"
#include "UserDef.h"
#include "CvvImage.h"
//#include "cuit_usrp_include/NetGrid_Const.h"
//#include "cuit_usrp_include/NetGrid.h"
//#include "cuit_usrp_include/CUIT_GUI_STRUCT_VSHEEP.h"
using namespace cv;
using namespace std;
#define			MAP_CACHE_NODES			128					//缓存的最大节点数--总的节点--所有层次
#ifndef PI
	#define		PI		3.1415926536
#endif
	const double	EarthRadius = 6378137;
	const double	MinLatitude = -85.05112878;
	const double	MaxLatitude = 85.05112878;
	const double	MinLongitude = -180;
	const double	MaxLongitude = 180;
#ifdef _MAP_TILE_MERGE_DECLARE
#define _MAP_TILE_MERGE_DECLARE
	typedef struct _MAP_TILE_MERGE
		{
		char		tilePATH[256];										//瓦片图像的路径

		int		showCenterXY[2];									//地图中心点的墨卡托坐标--根据初始BLH确定--->>>随后在漫游后修改
		int		showLevelOfDetail;								//地图的缩放因子

		cv::Mat		matMerged;										//合并后地图的矩阵
		int		matLT_XY[2];											//合并后地图的XY像素坐标==左上角BING像素坐标
		int		matCopy_DeltaXY[2];							//COPY地图时所使用的偏移量（左上角）--->>>左上角坐标，偏移量，鼠标点--->>计算地图点坐标！
		int		matCenterXY[2];									//合并后地图的XY像素坐标==中间点BING像素坐标
		int		matLevelOfDetail;									//合并后地图的缩放等级


		int		mouseDownPoint[2];							//鼠标按下的点
		int		mouseUpPoint[2];									//鼠标抬起的点--->>>漫游依据---取deltaXY就是漫游的区间

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
#endif //MAP_TILE_MERGE_DECLARE

class BING_TILESYSTEM
{
public:
	BING_TILESYSTEM(void);
	~BING_TILESYSTEM(void);


	double				Clip(double n, double minValue, double maxValue);
	unsigned int		MapSize(int levelOfDetail);
	double				GroundResolution(double latitude, int levelOfDetail);
	double				MapScale(double latitude, int levelOfDetail, int screenDpi);
	void						LatLongToPixelXY(double latitude, double longitude, int levelOfDetail, int *pixelX,  int *pixelY);	//USING
	void						PixelXYToLatLong(int pixelX, int pixelY, int levelOfDetail, double *latitude, double *longitude);		//USING
	void						PixelXYToTileXY(int pixelX, int pixelY,  int *tileX, int *tileY);
	void						TileXYToPixelXY(int tileX, int tileY, int *pixelX, int *pixelY);
	string					TileXYToQuadKey(int tileX, int tileY, int levelOfDetail);
	int						QuadKeyToTileXY(string quadKey, int *tileX, int *tileY, int *levelOfDetail);
	int						DO_Map_Tiles_Montage_Cache(MAP_TILE_MERGE	*pTileMerge, vector <MAP_IMAGE_FILE_CACHE> *pImageCache);//USING
	FILE					*pFILE_SATMAPLOG;

	char					RAMDISK[256];		//RAMDISK磁盘路径：不带'\'符号
};

