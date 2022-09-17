// UAV_SpiderDoc.h : interface of the CUAV_SpiderDoc class
//


#pragma once


class CUAV_SpiderDoc : public CDocument
{
protected: // create from serialization only
	CUAV_SpiderDoc();
	DECLARE_DYNCREATE(CUAV_SpiderDoc)

// Attributes
public:

// Operations
public:

// Overrides
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);

// Implementation
public:
	virtual ~CUAV_SpiderDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
};
