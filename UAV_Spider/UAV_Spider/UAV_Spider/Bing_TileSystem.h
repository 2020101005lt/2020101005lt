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
#define			MAP_CACHE_NODES			128					//��������ڵ���--�ܵĽڵ�--���в��
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
		char		tilePATH[256];										//��Ƭͼ���·��

		int		showCenterXY[2];									//��ͼ���ĵ��ī��������--���ݳ�ʼBLHȷ��--->>>��������κ��޸�
		int		showLevelOfDetail;								//��ͼ����������

		cv::Mat		matMerged;										//�ϲ����ͼ�ľ���
		int		matLT_XY[2];											//�ϲ����ͼ��XY��������==���Ͻ�BING��������
		int		matCopy_DeltaXY[2];							//COPY��ͼʱ��ʹ�õ�ƫ���������Ͻǣ�--->>>���Ͻ����꣬ƫ����������--->>�����ͼ�����꣡
		int		matCenterXY[2];									//�ϲ����ͼ��XY��������==�м��BING��������
		int		matLevelOfDetail;									//�ϲ����ͼ�����ŵȼ�


		int		mouseDownPoint[2];							//��갴�µĵ�
		int		mouseUpPoint[2];									//���̧��ĵ�--->>>��������---ȡdeltaXY�������ε�����

		CRect	guiClientRect;										//��ʾ����ľ��ο�-->>������Ƭ�ϲ�֮ǰ��Ҫ���ã�
		}MAP_TILE_MERGE;

	typedef struct _MAP_IMAGE_FILE_CACHE
			{
			unsigned int		ImageFoldNo;		//�ļ��к���
			unsigned int		ImageTileNo;		//ֱ��ʹ����Ƭ��-->>>���jpg�ļ���-->>������
			unsigned int		HitTimeSec;			//����ʱ��
			//unsigned int		ImageCenterXY[2];//��ǰ��Ƭ�����ĵ�����-->>>�����޳� ���̾�����Զ����Ƭ
			IplImage			*ReadImg;				//��ȡ����ͼ���ļ�--ÿ������3*64K
			}MAP_IMAGE_FILE_CACHE;	//ÿ��ͼ���������cach32���ļ�-->>8 * 32 * 3 * 64 = 49MB--->>>�ǿ��Խ��ܵģ�
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

	char					RAMDISK[256];		//RAMDISK����·��������'\'����
};

