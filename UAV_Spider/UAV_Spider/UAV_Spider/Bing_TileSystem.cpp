#include "StdAfx.h"
#include "BING_TILESYSTEM.h"
#include <io.h>
using namespace cv;
BING_TILESYSTEM::BING_TILESYSTEM(void)
{
	pFILE_SATMAPLOG = fopen("LOG_SATMAP.txt", "a+");
}


BING_TILESYSTEM::~BING_TILESYSTEM(void)
{
}


        /// <summary>
        /// Clips a number to the specified minimum and maximum values.
        /// </summary>
        /// <param name="n">The number to clip.</param>
        /// <param name="minValue">Minimum allowable value.</param>
        /// <param name="maxValue">Maximum allowable value.</param>
        /// <returns>The clipped value.</returns>
double BING_TILESYSTEM::Clip(double n, double minValue, double maxValue)
{
	return min(max(n, minValue), maxValue);
}



        /// <summary>
        /// Determines the map width and height (in pixels) at a specified level
        /// of detail.
        /// </summary>
        /// <param name="levelOfDetail">Level of detail, from 1 (lowest detail)
        /// to 23 (highest detail).</param>
        /// <returns>The map width and height in pixels.</returns>
unsigned int  BING_TILESYSTEM::MapSize(int levelOfDetail)
{
	return (unsigned int)256 << levelOfDetail;
}



        /// <summary>
        /// Determines the ground resolution (in meters per pixel) at a specified
        /// latitude and level of detail.
        /// </summary>
        /// <param name="latitude">Latitude (in degrees) at which to measure the
        /// ground resolution.</param>
        /// <param name="levelOfDetail">Level of detail, from 1 (lowest detail)
        /// to 23 (highest detail).</param>
        /// <returns>The ground resolution, in meters per pixel.</returns>
double BING_TILESYSTEM::GroundResolution(double latitude, int levelOfDetail)
{
	latitude = Clip(latitude, MinLatitude, MaxLatitude);
	return cos(latitude * PI / 180) * 2 * PI * EarthRadius / MapSize(levelOfDetail);
}



        /// <summary>
        /// Determines the map scale at a specified latitude, level of detail,
        /// and screen resolution.
        /// </summary>
        /// <param name="latitude">Latitude (in degrees) at which to measure the
        /// map scale.</param>
        /// <param name="levelOfDetail">Level of detail, from 1 (lowest detail)
        /// to 23 (highest detail).</param>
        /// <param name="screenDpi">Resolution of the screen, in dots per inch.</param>
        /// <returns>The map scale, expressed as the denominator N of the ratio 1 : N.</returns>
double BING_TILESYSTEM::MapScale(double latitude, int levelOfDetail, int screenDpi)
{
	return GroundResolution(latitude, levelOfDetail) * screenDpi / 0.0254;
}



        /// <summary>
        /// Converts a point from latitude/longitude WGS-84 coordinates (in degrees)
        /// into pixel XY coordinates at a specified level of detail.
        /// </summary>
        /// <param name="latitude">Latitude of the point, in degrees.</param>
        /// <param name="longitude">Longitude of the point, in degrees.</param>
        /// <param name="levelOfDetail">Level of detail, from 1 (lowest detail)
        /// to 23 (highest detail).</param>
        /// <param name="pixelX">Output parameter receiving the X coordinate in pixels.</param>
        /// <param name="pixelY">Output parameter receiving the Y coordinate in pixels.</param>
void BING_TILESYSTEM::LatLongToPixelXY(double latitude, double longitude, int levelOfDetail, int *pixelX,  int *pixelY)
//void LatLongToPixelXY(double latitude, double longitude, int levelOfDetail, out int pixelX, out int pixelY)
{
	latitude = Clip(latitude, MinLatitude, MaxLatitude);
	longitude = Clip(longitude, MinLongitude, MaxLongitude);
	
	double x = (longitude + 180) / 360;
	double sinLatitude = sin(latitude * PI / 180);
	double y = 0.5 - log((1 + sinLatitude) / (1 - sinLatitude)) / (4 * PI);

	unsigned int mapSize = MapSize(levelOfDetail);
	*pixelX = (int)Clip(x * mapSize + 0.5, 0, mapSize - 1);
	*pixelY = (int)Clip(y * mapSize + 0.5, 0, mapSize - 1);
}



        /// <summary>
        /// Converts a pixel from pixel XY coordinates at a specified level of detail
        /// into latitude/longitude WGS-84 coordinates (in degrees).
        /// </summary>
        /// <param name="pixelX">X coordinate of the point, in pixels.</param>
        /// <param name="pixelY">Y coordinates of the point, in pixels.</param>
        /// <param name="levelOfDetail">Level of detail, from 1 (lowest detail)
        /// to 23 (highest detail).</param>
        /// <param name="latitude">Output parameter receiving the latitude in degrees.</param>
        /// <param name="longitude">Output parameter receiving the longitude in degrees.</param>
void BING_TILESYSTEM::PixelXYToLatLong(int pixelX, int pixelY, int levelOfDetail, double *latitude, double *longitude)
{
	double mapSize = MapSize(levelOfDetail);
	double x = (Clip(pixelX, 0, mapSize - 1) / mapSize) - 0.5;
	double y = 0.5 - (Clip(pixelY, 0, mapSize - 1) / mapSize);

	*latitude = 90 - 360 * atan(exp(-y * 2 * PI)) / PI;
	*longitude = 360 * x;
}



        /// <summary>
        /// Converts pixel XY coordinates into tile XY coordinates of the tile containing
        /// the specified pixel.
        /// </summary>
        /// <param name="pixelX">Pixel X coordinate.</param>
        /// <param name="pixelY">Pixel Y coordinate.</param>
        /// <param name="tileX">Output parameter receiving the tile X coordinate.</param>
        /// <param name="tileY">Output parameter receiving the tile Y coordinate.</param>
void BING_TILESYSTEM::PixelXYToTileXY(int pixelX, int pixelY,  int *tileX, int *tileY)
{
	*tileX = pixelX / 256;
	*tileY = pixelY / 256;
}



        /// <summary>
        /// Converts tile XY coordinates into pixel XY coordinates of the upper-left pixel
        /// of the specified tile.
        /// </summary>
        /// <param name="tileX">Tile X coordinate.</param>
        /// <param name="tileY">Tile Y coordinate.</param>
        /// <param name="pixelX">Output parameter receiving the pixel X coordinate.</param>
        /// <param name="pixelY">Output parameter receiving the pixel Y coordinate.</param>
void BING_TILESYSTEM::TileXYToPixelXY(int tileX, int tileY, int *pixelX, int *pixelY)
{
	*pixelX = tileX * 256;
	*pixelY = tileY * 256;
}



        /// <summary>
        /// Converts tile XY coordinates into a QuadKey at a specified level of detail.
        /// </summary>
        /// <param name="tileX">Tile X coordinate.</param>
        /// <param name="tileY">Tile Y coordinate.</param>
        /// <param name="levelOfDetail">Level of detail, from 1 (lowest detail)
        /// to 23 (highest detail).</param>
        /// <returns>A string containing the QuadKey.</returns>
string BING_TILESYSTEM::TileXYToQuadKey(int tileX, int tileY, int levelOfDetail)
{
	string quadKey = "";
	for (int i = levelOfDetail; i > 0; i--)
	{
		char digit[8] = "0";
		int mask = 1 << (i - 1);
		if ((tileX & mask) != 0)
		{
			digit[0]++;
		}
		if ((tileY & mask) != 0)
		{
			digit[0]++;
			digit[0]++;
		}
		quadKey.append(string(digit));
	}
	return quadKey;
}



        /// <summary>
        /// Converts a QuadKey into tile XY coordinates.
        /// </summary>
        /// <param name="quadKey">QuadKey of the tile.</param>
        /// <param name="tileX">Output parameter receiving the tile X coordinate.</param>
        /// <param name="tileY">Output parameter receiving the tile Y coordinate.</param>
        /// <param name="levelOfDetail">Output parameter receiving the level of detail.</param>
int BING_TILESYSTEM::QuadKeyToTileXY(string quadKey, int *tileX, int *tileY, int *levelOfDetail)
{
	tileX = tileY = 0;
	*levelOfDetail = quadKey.length();
	for (int i = *levelOfDetail; i > 0; i--)
	{
		int mask = 1 << (i - 1);
		char *pChar = (char *)quadKey.c_str();
		switch (pChar[*levelOfDetail - i])
		{
		case '0':
			break;

		case '1':
			*tileX |= mask;
			break;

		case '2':
			*tileY |= mask;
			break;

		case '3':
			*tileX |= mask;
			*tileY |= mask;
			break;

		default:
			return -1;
		}
	}
return 1;
}


int BING_TILESYSTEM::DO_Map_Tiles_Montage_Cache(MAP_TILE_MERGE	*pTileMerge, vector <MAP_IMAGE_FILE_CACHE> *pImageCache)
{
//---��01��---���ݽ���ͻ����Լ��ϲ���ͼ���䣬�ж��Ƿ���Ҫ���ºϲ�
	//_CrtSetBreakAlloc(4218);
	CRect guiClientRect, wndMapRect, showMapRect;		//����ͻ�������ǰ�ϳɵ�ͼ�ľ��ο����䣬��Ҫ��ʾ�ĵ�ͼ��������
	wndMapRect.left = pTileMerge->matCenterXY[0] - pTileMerge->matMerged.cols/2;
	wndMapRect.right = pTileMerge->matCenterXY[0] + pTileMerge->matMerged.cols/2;
	wndMapRect.top = pTileMerge->matCenterXY[1] - pTileMerge->matMerged.rows/2;
	wndMapRect.bottom= pTileMerge->matCenterXY[1] + pTileMerge->matMerged.rows/2;			//��ǰ��ͼ���������---��������
	guiClientRect = pTileMerge->guiClientRect;
	showMapRect.left = pTileMerge->showCenterXY[0]	-  guiClientRect.Width()/2;
	showMapRect.right = pTileMerge->showCenterXY[0]	+ guiClientRect.Width()/2;
	showMapRect.top = pTileMerge->showCenterXY[1]	-  guiClientRect.Height()/2;
	showMapRect.bottom = pTileMerge->showCenterXY[1]	+ guiClientRect.Height()/2;					//��ǰ�����ͼ����---��������

	int ReMerging_MapTile = 0;		//��Ҫ���ºϲ���ͼ�ı�־

	if(pTileMerge->matMerged.rows < 1 || pTileMerge->matMerged.cols < 1)		
		ReMerging_MapTile++;	//����û�г�ʼ��-->>�������
	if(pTileMerge->showLevelOfDetail != pTileMerge->matLevelOfDetail)				
		ReMerging_MapTile++;	//���ż���ı���-->>�������

	if(	showMapRect.left < wndMapRect.left || showMapRect.right > wndMapRect.right || showMapRect.top < wndMapRect.top || showMapRect.bottom > wndMapRect.bottom)											
		ReMerging_MapTile++;	//�������䲻�ܸ�����ʾ����-->>�������

	if(ReMerging_MapTile == 0)
		return 0;	//---->>>����Ҫ���£���·
//---��02��---������Ҫ�ϲ���ͼƬ����������-->>������ʾ������������Ӧ����Ƭ��
	int ShowRectEX = 255;		//��ʾ�������չ����
	int TileSeq_LT[2] = {-1, -1};		//��ʾ�������Ͻǵ���Ƭ��
	PixelXYToTileXY( showMapRect.left, showMapRect.top, &TileSeq_LT[0], &TileSeq_LT[1]);
	int TileSeq_RT[2] =  {-1, -1};		//���Ͻǵ���Ƭ��
	PixelXYToTileXY( showMapRect.right + ShowRectEX, showMapRect.top, &TileSeq_RT[0], &TileSeq_RT[1]);
	int TileSeq_LB[2] =  {-1, -1};		//���½ǵ���Ƭ��
	PixelXYToTileXY( showMapRect.left, showMapRect.bottom + ShowRectEX, &TileSeq_LB[0], &TileSeq_LB[1]);
	int TileSeq_RB[2] =  {-1, -1};		//���½ǵ���Ƭ��
	PixelXYToTileXY( showMapRect.right + ShowRectEX, showMapRect.bottom + ShowRectEX, &TileSeq_RB[0], &TileSeq_RB[1]);

	//��ʱ����һ���ļ�����TileSeq_LT[0]��			���һ���ļ�����TileSeq_RB[0];			---->>>>����������ÿ���ļ����У���Ƭͼ�����������ͬ�ģ�����
	//			��һ����Ƭ�ļ������TileSeq_LT[1]�����һ����Ƭ�ļ������TileSeq_RB[1]---->>>>��������������ͼƬ��ƴ����ͬһ��
	//����ϲ���ͼƬ�Ĵ�С

	int newMat_Rows =  (TileSeq_RB[1] - TileSeq_LT[1] + 1) * 256;
	int newMat_Cols	=	(TileSeq_RB[0] - TileSeq_LT[0] + 1) * 256;
	//pTileMerge->matMerged.rows = newMat_Rows;
	//pTileMerge->matMerged.cols  = newMat_Cols;
	//pTileMerge->matMerged.zeros();

	pTileMerge->matMerged.release();

	pTileMerge->matMerged = cv::Mat::zeros(newMat_Rows, newMat_Cols, CV_8UC3);

//--��03��--ͼ��ƴ��-->>>
	CString filePathStr, fileNameStr;
	CvRect rioRect;
	//CvvImage pSrcImg;
	int cnt_cvLoad = 0;
	int cnt_cvRelease = 0;
	//IplImage ipl_img = cvCloneImage(&(IplImage)pTileMerge->matMerged);;
	IplImage ipl_img = pTileMerge->matMerged.operator IplImage();			//������ݽṹ����û��ͼ�����ݵģ�������һ������ͷ
	int	MatX_min = 0x7fffffff;	
	int	MatX_max = 0; 
	int	MatY_min = 0x7fffffff;	
	int	MatY_max = 0;	//��������������������--���ڼ��������м������

	for(int i=TileSeq_LT[0]; i<= TileSeq_RB[0]; i++)				//��������-->>>��Ӧ���ļ�������
		{
		//�ļ���·������-->>
		for(int k=TileSeq_LT[1]; k<= TileSeq_RB[1]; k++)		//��������-->>>��Ӧ���ļ�����
			{
			//�ļ������ڣ���ʹ��Ĭ��������ͼ��
				rioRect.x = ( i - TileSeq_LT[0] ) * 256;
				rioRect.y = ( k - TileSeq_LT[1] ) * 256;
				rioRect.width = 256;
				rioRect.height= 256;
				int pixelX; 
				int pixelY;
				TileXYToPixelXY( i, k, &pixelX, &pixelY);//��Ƭ���Ͻ���������
				MatX_min = min(MatX_min, pixelX);
				MatX_max = max(MatX_max, pixelX + 256);
				MatY_min = min(MatY_min, pixelY);
				MatY_max = max(MatY_max, pixelY + 256);		//������Ƭ���Ľ�����
				if(rioRect.x + rioRect.width > ipl_img.width)
					continue;
				if(rioRect.y + rioRect.height  > ipl_img.height)
					continue;
				cvSetImageROI(&ipl_img, rioRect);	//ÿ�����ò�ͬ����Ȥ����
				TRACE("��Ln318��StartX = %d,StartY = %d,Height = %d, Width = %d\n",rioRect.x,rioRect.y,ipl_img.width,ipl_img.height);
				filePathStr.Format ("%s\\%d\\%d\\%d.jpg", pTileMerge->tilePATH, pTileMerge->showLevelOfDetail, i, k);	
				//�Զ���ӦͼƬ��ʽ--�����ڵ�ͼƬʹ�û�ɫͼƬ���
				if( (_access(filePathStr, 0 )) == -1 )
					{
					filePathStr.Format ("%s\\%d\\%d\\%d.png", pTileMerge->tilePATH, pTileMerge->showLevelOfDetail, i, k);	
					if( (_access(filePathStr, 0 )) == -1)
						{
						if(pFILE_SATMAPLOG != NULL)
							fprintf_s(pFILE_SATMAPLOG, "���ǵ�ͼ����#330��δ���ҵ�ͼ��ʹ�ÿ�ͼ�������%s\n", filePathStr);
						filePathStr = "Map0000.png";
						}

					}

				string filePathstring =(char *)(LPCTSTR)filePathStr;
//#ifdef Mem_Test
				/******************����Ƭ����Ͷ�ȡ����Ρ�******************/
					time_t curTimeSec; 
					time(&curTimeSec);
					CvSize tileSize;	
					tileSize.width = 256; 
					tileSize.height = 256;
					IplImage* readImg = NULL;	//�������Ƭ�ļ�
					int showLevelOfDetail = pTileMerge->showLevelOfDetail;		//��ǰ���ż���
					//--��01��-->>>���������������Ƿ���ڵ�ǰ��Ƭ--������Ƭ��k
					//for(int n=0; n < pImageCache->size(); n++)
					//	{
					//	if(pImageCache->at(n).ImageTileNo == k && pImageCache->at(n).ImageFoldNo == i)
					//		{
					//		try
					//			{
					//			readImg = cvCreateImage(tileSize, pImageCache->at(n).ReadImg->depth, pImageCache->at(n).ReadImg->nChannels);
					//			cvCopy(pImageCache->at(n).ReadImg, readImg);
					//			}
					//		catch(cv::Exception& e) 
					//			{ 
					//			 //AfxMessageBox(e.what()); 
					//			if(pFILE_SATMAPLOG != NULL)
					//				fprintf_s(pFILE_SATMAPLOG, "���ǵ�ͼ����#357��%s\n", e.what());
					//			} 
					//		pImageCache->at(n).HitTimeSec = (unsigned int)curTimeSec;
					//		break;
					//		}
					//	}//for n
					//--��02��-->>>������û�л�����-->>��ȡ�ļ�����ִ�л���洢
					if(readImg == NULL)	
						{
							//pSrcImg.Load(filePathstring.c_str());                                //strΪCstring���͵�ͼ���ļ���
							//readImg = pSrcImg.GetImage();   //������pSrcImg��ͼ�����ݡ�
							readImg = cvLoadImage(filePathstring.c_str(), CV_LOAD_IMAGE_COLOR );
							cnt_cvLoad++;
							TRACE("��Ln378��%d times cvLoad,\t readImg = %X\n",cnt_cvLoad,readImg);
						//--��02.2��-->>>�ڵ����Ѿ�����--�޳�һ���ڵ㣺���ϵ�ʱ���Ȼ��ǰ��
						if(pImageCache->size() >= MAP_CACHE_NODES && readImg != NULL)	
							{
							unsigned int oldestHitTimeSec = 0x7fffffff;	int oldNodeIndex = 0;
							for(int n=0; n < pImageCache->size(); n++)
								{
								if(pImageCache->at(n).HitTimeSec < oldestHitTimeSec )
									{
									oldestHitTimeSec = pImageCache->at(n).HitTimeSec;
									oldNodeIndex = n;
									}
								}//for n
							cvReleaseImage(&pImageCache->at(oldNodeIndex).ReadImg);	//�����ͷ�ͼƬ
							pImageCache->erase(pImageCache->begin() + oldNodeIndex);	//�ͷ����Ͻڵ�
							}
						//--��02.1��-->>>�ڵ���û�г���--ֱ�Ӳ�������
						//if(pImageCache->size() < MAP_CACHE_NODES && readImg != NULL)	
						//	{
						//	MAP_IMAGE_FILE_CACHE *pNewNode = new MAP_IMAGE_FILE_CACHE;
						//	memset(pNewNode, 0, sizeof(MAP_IMAGE_FILE_CACHE));
						//	pNewNode->HitTimeSec = (unsigned int)curTimeSec;
						//	pNewNode->ImageFoldNo = i;
						//	pNewNode->ImageTileNo = k;
						//	pNewNode->ReadImg = cvCreateImage(tileSize, readImg->depth, readImg->nChannels);
						//	cvCopy(readImg, pNewNode->ReadImg);
						//	pImageCache->push_back(*pNewNode);		//2018FEB
						//	}
						}
				if(readImg != NULL)
					{
					cvCopy(readImg,  &ipl_img);
					TRACE("��Ln445��%d times ��before�� cvRelease,\t readImg = %X, Src.Width = %d, Src.Height = %d, Dst.Width = %d, Dst.Height = %d\n",cnt_cvRelease,readImg,readImg->width,readImg->height,ipl_img.width,ipl_img.height);
					cvReleaseImage(&readImg);
					cnt_cvRelease++;
					TRACE("��Ln448��%d times ��after�� cvRelease,\t readImg = %X\n",cnt_cvRelease,readImg);
					cvResetImageROI(&ipl_img);  
					}
				
//#endif
			}//for k
		}//for i
	pTileMerge->matLevelOfDetail = pTileMerge->showLevelOfDetail;
	pTileMerge->matLT_XY[0] = MatX_min;		
	pTileMerge->matLT_XY[1] = MatY_min;
	//cvSaveImage("MergedImage_ipl.jpg", &ipl_img);	
	pTileMerge->matCenterXY[0] = (MatX_min + MatX_max)/2;		//MatX_min = 357120		MatX_max = 358912
	pTileMerge->matCenterXY[1] = (MatY_min + MatY_max)/2;		//MatY_min = 223232		MatY_max = 224256			//pixelX_LT = 356608  pixelY_LT = 222464

	for (int i = 0;i<pImageCache->size();i++)
	{
		cvReleaseImage(&pImageCache->at(i).ReadImg);
	}
	vector<MAP_IMAGE_FILE_CACHE>().swap(*pImageCache);     //�����������С��������
	int capacity = pImageCache->capacity();   //0
	int size = pImageCache->size();           //0
//#endif
	return 0;
}
