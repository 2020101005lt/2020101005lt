// MyBtn.cpp : 实现文件
//

#include "stdafx.h"
#include "UAV_Spider.h"
#include "MyBtn.h"
IMPLEMENT_DYNAMIC(CMyBtn, CBitmapButton) 
	CMyBtn::CMyBtn() 
	:m_bTracked(FALSE) 
{     
} 
// 为控件装载位图，nBitmapContainCount代表位图数量
BOOL CMyBtn::LoadListBitmap( UINT nIDBitmapResource, UINT nBitmapContainCount ) 
{ 
	m_bitmap.DeleteObject(); 
	m_bitmapSel.DeleteObject(); 
	m_bitmapFocus.DeleteObject(); 
	m_bitmapDisabled.DeleteObject(); 
	CBitmap bmpSrc; 
	bmpSrc.LoadBitmap(nIDBitmapResource); 
	BITMAP bmpInfo; 
	bmpSrc.GetBitmap(&bmpInfo); 
	CClientDC dc(this); 
	CDC dcSrc, dcDest; 
	dcSrc.CreateCompatibleDC(&dc); 
	CBitmap *pOldBmpSrc = dcSrc.SelectObject(&bmpSrc); 
	int nWidth = bmpInfo.bmWidth / nBitmapContainCount; 
	int nHeight = bmpInfo.bmHeight; 
	dcDest.CreateCompatibleDC(&dc); 
	m_bitmap.CreateCompatibleBitmap(&dcSrc, nWidth, nHeight); 
	CBitmap *pOldBmpDest = dcDest.SelectObject(&m_bitmap); 
	dcDest.BitBlt(0, 0, nWidth, nHeight, &dcSrc, 0, 0, SRCCOPY); 
	dcDest.SelectObject(pOldBmpDest); 

	if (nBitmapContainCount > 1) 
	{ 
		m_bitmapSel.CreateCompatibleBitmap(&dcSrc, nWidth, nHeight); 
		pOldBmpDest = dcDest.SelectObject(&m_bitmapSel); 
		dcDest.BitBlt(0, 0, nWidth, nHeight, &dcSrc, nWidth, 0, SRCCOPY); 
		dcDest.SelectObject(pOldBmpDest); 
	} 
	if (nBitmapContainCount > 2) 
	{ 
		m_bitmapFocus.CreateCompatibleBitmap(&dcSrc, nWidth, nHeight); 
		pOldBmpDest = dcDest.SelectObject(&m_bitmapFocus); 
		dcDest.BitBlt(0, 0, nWidth, nHeight, &dcSrc, nWidth * 2, 0, SRCCOPY); 
		dcDest.SelectObject(pOldBmpDest); 
	} 
	if (nBitmapContainCount > 3) 
	{ 
		m_bitmapDisabled.CreateCompatibleBitmap(&dcSrc, nWidth, nHeight); 
		pOldBmpDest = dcDest.SelectObject(&m_bitmapDisabled); 
		dcDest.BitBlt(0, 0, nWidth, nHeight, &dcSrc, nWidth * 3, 0, SRCCOPY); 
		dcDest.SelectObject(pOldBmpDest); 
	} 
	dcSrc.SelectObject(pOldBmpSrc); 
	return TRUE; 
} 

BEGIN_MESSAGE_MAP(CMyBtn, CBitmapButton) 
	ON_WM_MOUSEMOVE() 
	ON_WM_MOUSELEAVE() 
END_MESSAGE_MAP() 
// 绘制控件函数
void CMyBtn::DrawItem( LPDRAWITEMSTRUCT lpDIS ) 
{ 
	ASSERT(lpDIS != NULL); 
	// 确保至少第一幅位图被装载 
	ASSERT(m_bitmap.m_hObject != NULL);     

	// 采用第1幅位图作为按键的常态显示,第2幅位图作为按键被点击的状态显示 
	CBitmap* pBitmap = &m_bitmap; 
	UINT state = lpDIS->itemState; 
	if ((state & ODS_SELECTED) && m_bitmapSel.m_hObject != NULL) 
		pBitmap = &m_bitmapSel; 
	else if ((state & ODS_DISABLED) && m_bitmapDisabled.m_hObject != NULL) 
		pBitmap = &m_bitmapDisabled;   // 第4幅位图作为按键被禁用的状态显示 
	else if (m_bTracked && m_bitmapFocus.m_hObject != NULL)     
		pBitmap = &m_bitmapFocus;   // 第3幅位图作为鼠标焦点在按键上的状态显示

	// 绘制控件 
	CDC* pDC = CDC::FromHandle(lpDIS->hDC); 
	CDC memDC; 
	memDC.CreateCompatibleDC(pDC); 
	CBitmap* pOld = memDC.SelectObject(pBitmap); 
	if (pOld == NULL) 
		return;     // destructors will clean up 

	CRect rect; 
	rect.CopyRect(&lpDIS->rcItem); 
	pDC->BitBlt(rect.left, rect.top, rect.Width(), rect.Height(), 
		&memDC, 0, 0, SRCCOPY); 
	memDC.SelectObject(pOld); 
} 
// 控件响应鼠标移动事件的函数，point代表鼠标坐标
void CMyBtn::OnMouseMove(UINT nFlags, CPoint point) 
{ 
	if (!m_bTracked) 
	{ 
		TRACKMOUSEEVENT tme; 
		tme.cbSize = sizeof(tme); 
		tme.dwFlags = TME_LEAVE; 
		tme.dwHoverTime = 0; 
		tme.hwndTrack = m_hWnd; 
		TrackMouseEvent(&tme); 
		m_bTracked = TRUE; 
		Invalidate(FALSE); 
	}     
	CBitmapButton::OnMouseMove(nFlags, point); 
} 
// 控件响应鼠标离开button事件的函数
void CMyBtn::OnMouseLeave() 
{ 
	m_bTracked = FALSE; 
	Invalidate(FALSE); 

	CBitmapButton::OnMouseLeave(); 
} 
// 修改控件属性为用户自绘
void CMyBtn::PreSubclassWindow() 
{ 
	CBitmapButton::PreSubclassWindow(); 
	ModifyStyle(0, BS_OWNERDRAW); 
}
