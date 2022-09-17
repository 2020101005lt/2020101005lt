// UAV_SpiderDoc.cpp : implementation of the CUAV_SpiderDoc class
//

#include "stdafx.h"
#include "UAV_Spider.h"

#include "UAV_SpiderDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CUAV_SpiderDoc

IMPLEMENT_DYNCREATE(CUAV_SpiderDoc, CDocument)

BEGIN_MESSAGE_MAP(CUAV_SpiderDoc, CDocument)
END_MESSAGE_MAP()


// CUAV_SpiderDoc construction/destruction

CUAV_SpiderDoc::CUAV_SpiderDoc()
{
	// TODO: add one-time construction code here

}

CUAV_SpiderDoc::~CUAV_SpiderDoc()
{
}

BOOL CUAV_SpiderDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}




// CUAV_SpiderDoc serialization

void CUAV_SpiderDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}


// CUAV_SpiderDoc diagnostics

#ifdef _DEBUG
void CUAV_SpiderDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CUAV_SpiderDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CUAV_SpiderDoc commands
