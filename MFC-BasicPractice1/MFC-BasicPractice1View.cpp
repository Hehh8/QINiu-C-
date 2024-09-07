
// MFC-BasicPractice1View.cpp: CMFCBasicPractice1View 类的实现
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "MFC-BasicPractice1.h"
#endif

#include "MFC-BasicPractice1Doc.h"
#include "MFC-BasicPractice1View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMFCBasicPractice1View

IMPLEMENT_DYNCREATE(CMFCBasicPractice1View, CView)

BEGIN_MESSAGE_MAP(CMFCBasicPractice1View, CView)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
END_MESSAGE_MAP()

// CMFCBasicPractice1View 构造/析构

CMFCBasicPractice1View::CMFCBasicPractice1View() noexcept
{
	// TODO: 在此处添加构造代码

}

CMFCBasicPractice1View::~CMFCBasicPractice1View()
{
}

BOOL CMFCBasicPractice1View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CMFCBasicPractice1View 绘图

void CMFCBasicPractice1View::OnDraw(CDC* /*pDC*/)
{
	CMFCBasicPractice1Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 在此处为本机数据添加绘制代码
}

void CMFCBasicPractice1View::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CMFCBasicPractice1View::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CMFCBasicPractice1View 诊断

#ifdef _DEBUG
void CMFCBasicPractice1View::AssertValid() const
{
	CView::AssertValid();
}

void CMFCBasicPractice1View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMFCBasicPractice1Doc* CMFCBasicPractice1View::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMFCBasicPractice1Doc)));
	return (CMFCBasicPractice1Doc*)m_pDocument;
}
#endif //_DEBUG


// CMFCBasicPractice1View 消息处理程序


void CMFCBasicPractice1View::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	m_pOrigin = point;

	CView::OnLButtonDown(nFlags, point);
}


void CMFCBasicPractice1View::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	// 获取设备上下文
	CDC* pDC = GetDC();

	CPen pen(PS_SOLID, 2, RGB(130, 244, 122));

	CPen* pOldPen = pDC->SelectObject(&pen);

	// 移动画笔到起点
	pDC->MoveTo(m_pOrigin);

	// 在起点和终点间绘制直线
	pDC->LineTo(point);

	// 设备上下文恢复原画笔
	pDC->SelectObject(pOldPen);

	// 释放设备上下文
	ReleaseDC(pDC);
	CView::OnLButtonUp(nFlags, point);
}
