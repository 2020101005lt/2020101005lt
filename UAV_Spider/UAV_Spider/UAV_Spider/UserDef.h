#pragma once
#include<opencv2/opencv.hpp>
using namespace cv; 
#define SATELLET_TILEMAP_ZOOMMAX 16
#define SATELLET_TILEMAP_ZOOMMIN 8			//����ͼ��ļ�������
#define	MAP_LONG		long

enum TcpSrc{TCP_DETECT=0,TCP_TRAP};
// Detect Protocol
enum ECmdType
{
	eCmdTypeInvalid						= 0x00,	//��Ч����
	eCmdTypeHeartbeat					= 0x01,	//������
	eCmdTypeDeviceStatus				    = 0x02,	//��ȡ�豸״̬ 
	eCmdTypeIQData						= 0x03,	//��ȡԭʼIQ���ݣ�δʹ��
	eCmdTypeGPSData						= 0x04,	//��ȡGPS����
	eCmdTypeCompassData					= 0x05,	//��ȡ�����������ݣ�δʹ��
	eCmdTypeMonitorAlarm				= 0x06,	//���ؼ��澯���

	eCmdTypeSpectrumParam				= 0x10,	//�·�Ƶ�׼�����
	eCmdTypeSpectrumData				= 0x11,	//����Ƶ�׽������
	eCmdTypeSpectrumOn					= 0x12,	//Ƶ�������ϴ�[��]
	eCmdTypeSpectrumOff					= 0x13,	//Ƶ�������ϴ�[��]
	eCmdTypeScanMode                    = 0x14, //����ɨ��ģʽ
	eCmdTypeEnviMode                    = 0x15, //���û���ģʽ

	eCmdTypeTrackData					= 0x20,		//�������ݣ�δʹ��
	eCmdTypeTrackOn						= 0x21,		//����[��]
	eCmdTypeTrackOff					    = 0x22,		//����[��]

	eCmdTypeMonitorAirCtrl				= 0x30,      //���ü��ģʽ[�ɿ�]
	eCmdTypeMonitorImageTran			    = 0x31,		//���ü��ģʽ[ͼ��]
	eCmdTypeGain						= 0x32,		//����������ƣ�δʹ��
	eCmdTypeAtt                         = 0x33,      //����˥������

	eCmdTypeDfOn						= 0x40,		//����[��]��δʹ��
	eCmdTypeDfOff						= 0x41,		//����[��]���źŷ������ã�ֹͣ���в�������
	eCmdTypeDfData						= 0x42,		//���ز���������
	eCmdTypeDfStop                      = 0x43,      //δʹ��
	eCmdTypeSignalDisappear             = 0x44,       //���ز����ź���ʧ

	eCmdTypeDfSigFreq                   = 0x45,       //���ò���Ƶ

	eCmdTypeStartWork                   = 0x50,      //��ʼ������δʹ��
	eCmdTypeStopWork                    = 0x51,     //ֹͣ������δʹ��

	eCmdTypeInitState                     = 0x60,     //���س�ʼ��״̬
};

typedef struct _CENTER_STATION_RUNNING_PARAMS
{
	//��01��--������վ��ȡ�Ĳ���--��COMM�޹ص�
	int			UsingSatelliteMap;			//ʹ�����ǵ�ͼ�Ŀ��أ�2==BEING��ͼ��1==GOOGLE��ͼ��0=��ʹ�ã�
	char		SatelliteFoldPath[256];		//��ͼ�ļ���ȫ·��--���������ļ�---���ǵ�ͼ���ļ���·��
	char		MapFileFoldPath[256];		//��ͼ�ļ���ȫ·��--���������ļ�
}MAP_PATH_PARAMS;

//�����ǵ�ͼ����Ҫ�ı�ǩ����Ϣ���ݽṹ��-->>>ʹ��Read_ShapFile_LabelsXY���򣬶�ȡ��shp�ļ�--->>>��ൽxls�ļ��У�
typedef struct _SATTELLITE_MAP_LABEL_NODE
{
	char		labelName[64];
	double	labelBL[2];
}SATTELLITE_MAP_LABEL_NODE;
//--1--ͼ��������Ϣ��--��Ҫ��һ������
typedef struct MAPWINGIS_LAYERSHOWINFO
{
	char					LayerName[64];			//ͼ������--ȫ�ļ���
	int					IsLayerShow;				//�Ƿ���ʾ��ͼ��
	int					IsLabelShow;				//��ͼ���Ƿ���ʾ��ǩ
	unsigned int	Color_Point;				//��ɫ��
	unsigned int	Color_Line;					//����ɫ��
	unsigned int	Color_Fill;					//���ɫ��
	unsigned int	LineWidth;					//�߿�
	unsigned int	PointSize;					//���С
	unsigned int	ShowRank;					//��ʾ����0Ϊ������ʾ�ģ�1Ϊ����ģʽ��Ҫ���ص�
	long					layerHandle;				//ͼ����--��Ҫ��ס������ʾʱʹ��
	int					layerPostion;				//ͼ����ʾ���--->>>���ڶ�̬���Ĳ��������
	int					layerType;					//ͼ�����ͣ�0 == region��1 == polyline��2 == point
	int					layerCityMargin;			//1==���磻2==ʡ�磻3==�н磻4==�ؽ磻
}MAPWINGIS_LAYERSHOWINFO;

#define		MAPWINGIS_MAXSHPLAYERNUMS	64			//���SHP����
const char	MAPWINGIS_LAYERTYPE[3][16] = {
	"_region",
	"_polyline",
	"_point"
};
const char	MAPWINGIS_LAYERTYPE_ADMINMARGIN[4][16] = {
	"����",
	"ʡ��",
	"�н�",
	"�ؽ�"
};
//--->>>���ǵ�ͼ��ص����ݽṹ
typedef struct _MAP_TILE_MERGE
{
	char		tilePATH[256];										//��Ƭͼ���·����ĩβ����'\'

	int		showCenterXY[2];									//��ͼ���ĵ��ī��������--���ݳ�ʼBLHȷ��--->>>��������κ��޸�
	double		showCenterBL[2];									//��ͼ���ĵ��ī��������--���ݳ�ʼBLHȷ��--->>>��������κ��޸�
	int		showLevelOfDetail;								//��ͼ����������

	cv::Mat		matMerged;										//�ϲ����ͼ�ľ���
	int		matLT_XY[2];											//�ϲ����ͼ��XY��������==���Ͻ�BING��������
	int		matCopy_DeltaXY[2];							//COPY��ͼʱ��ʹ�õ�ƫ���������Ͻǣ�--->>>���Ͻ����꣬ƫ����������--->>�����ͼ�����꣡
	int		matCenterXY[2];									//�ϲ����ͼ��XY��������==�м��BING��������
	int		matLevelOfDetail;									//�ϲ����ͼ�����ŵȼ�


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