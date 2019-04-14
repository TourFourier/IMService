
// IMClientView.cpp : implementation of the CIMClientView class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "IMClient.h"
#endif

#include "IMClientDoc.h"
#include "IMClientView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CIMClientView

IMPLEMENT_DYNCREATE(CIMClientView, CView)

BEGIN_MESSAGE_MAP(CIMClientView, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CIMClientView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
END_MESSAGE_MAP()

// CIMClientView construction/destruction

CIMClientView::CIMClientView() noexcept
{
	// TODO: add construction code here

}

CIMClientView::~CIMClientView()
{
}

BOOL CIMClientView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CIMClientView drawing

void CIMClientView::OnDraw(CDC* /*pDC*/)
{
	CIMClientDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: add draw code for native data here
}


// CIMClientView printing


void CIMClientView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CIMClientView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CIMClientView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CIMClientView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

void CIMClientView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CIMClientView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CIMClientView diagnostics

#ifdef _DEBUG
void CIMClientView::AssertValid() const
{
	CView::AssertValid();
}

void CIMClientView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CIMClientDoc* CIMClientView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CIMClientDoc)));
	return (CIMClientDoc*)m_pDocument;
}
#endif //_DEBUG


// CIMClientView message handlers
