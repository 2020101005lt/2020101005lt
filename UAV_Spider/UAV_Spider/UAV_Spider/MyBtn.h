/*********************************************************************
����: 	�����µ�button�ؼ��࣬����ΪCBitmapButton����������button�ؼ�
������״̬����̬����굥�������ѡ�С���ֹ���µĲ�ͬλͼ��ʾ��
*********************************************************************/
#pragma once 
class CMyBtn : public CBitmapButton 
{ 
	DECLARE_DYNAMIC(CMyBtn) 
public: 
	CMyBtn(); 
	// ��button�ؼ�װ�ض��λͼ
	BOOL LoadListBitmap(UINT nIDBitmapResource, UINT nBitmapContainCount); 
protected: 
	BOOL m_bTracked; 
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDIS); 
	virtual void PreSubclassWindow(); 
	DECLARE_MESSAGE_MAP() 
public: 
	afx_msg void OnMouseMove(UINT nFlags, CPoint point); 
	afx_msg void OnMouseLeave(); 
}; 


