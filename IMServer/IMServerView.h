
// IMServerView.h : interface of the CIMServerView class
//

#pragma once


class CIMServerView : public CView
{
protected: // create from serialization only
	CIMServerView() noexcept;
	DECLARE_DYNCREATE(CIMServerView)

// Attributes
public:
	CIMServerDoc* GetDocument() const;

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
	virtual ~CIMServerView();
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

#ifndef _DEBUG  // debug version in IMServerView.cpp
inline CIMServerDoc* CIMServerView::GetDocument() const
   { return reinterpret_cast<CIMServerDoc*>(m_pDocument); }
#endif

