
// IMClient2View.h : interface of the CIMClient2View class
//

#pragma once


class CIMClient2View : public CView
{
protected: // create from serialization only
	CIMClient2View() noexcept;
	DECLARE_DYNCREATE(CIMClient2View)

// Attributes
public:
	CIMClient2Doc* GetDocument() const;

// Operations
public:

// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// Implementation
public:
	virtual ~CIMClient2View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in IMClient2View.cpp
inline CIMClient2Doc* CIMClient2View::GetDocument() const
   { return reinterpret_cast<CIMClient2Doc*>(m_pDocument); }
#endif

