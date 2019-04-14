
// IMServerView.cpp : implementation of the CIMServerView class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "IMServer.h"
#endif

#include "IMServerDoc.h"
#include "IMServerView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CIMServerView

IMPLEMENT_DYNCREATE(CIMServerView, CView)

BEGIN_MESSAGE_MAP(CIMServerView, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CIMServerView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
END_MESSAGE_MAP()

// CIMServerView construction/destruction

CIMServerView::CIMServerView() noexcept
{
	// TODO: add construction code here

}

CIMServerView::~CIMServerView()
{
}

BOOL CIMServerView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CIMServerView drawing

void CIMServerView::OnDraw(CDC* /*pDC*/)
{
	CIMServerDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: add draw code for native data here
}


// CIMServerView printing


void CIMServerView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CIMServerView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CIMServerView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CIMServerView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

void CIMServerView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CIMServerView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CIMServerView diagnostics

#ifdef _DEBUG
void CIMServerView::AssertValid() const
{
	CView::AssertValid();
}

void CIMServerView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CIMServerDoc* CIMServerView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CIMServerDoc)));
	return (CIMServerDoc*)m_pDocument;
}
#endif //_DEBUG


// CIMServerView message handlers
