/*********************************************************************
功能: 	定义新的button控件类，基类为CBitmapButton，可以设置button控件
在四种状态（常态、鼠标单击、鼠标选中、禁止）下的不同位图显示。
*********************************************************************/
#pragma once 
class CMyBtn : public CBitmapButton 
{ 
	DECLARE_DYNAMIC(CMyBtn) 
public: 
	CMyBtn(); 
	// 给button控件装载多幅位图
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


