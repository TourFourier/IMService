
// IMClient2View.cpp : implementation of the CIMClient2View class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "IMClient2.h"
#endif

#include "IMClient2Doc.h"
#include "IMClient2View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CIMClient2View

IMPLEMENT_DYNCREATE(CIMClient2View, CView)

BEGIN_MESSAGE_MAP(CIMClient2View, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CIMClient2View::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
END_MESSAGE_MAP()

// CIMClient2View construction/destruction

CIMClient2View::CIMClient2View() noexcept
{
	// TODO: add construction code here

}

CIMClient2View::~CIMClient2View()
{
}

BOOL CIMClient2View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CIMClient2View drawing

void CIMClient2View::OnDraw(CDC* /*pDC*/)
{
	CIMClient2Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: add draw code for native data here
}


// CIMClient2View printing


void CIMClient2View::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CIMClient2View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CIMClient2View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CIMClient2View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

void CIMClient2View::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CIMClient2View::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CIMClient2View diagnostics

#ifdef _DEBUG
void CIMClient2View::AssertValid() const
{
	CView::AssertValid();
}

void CIMClient2View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CIMClient2Doc* CIMClient2View::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CIMClient2Doc)));
	return (CIMClient2Doc*)m_pDocument;
}
#endif //_DEBUG


// CIMClient2View message handlers
