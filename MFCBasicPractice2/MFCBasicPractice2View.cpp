
// MFCBasicPractice2View.cpp: CMFCBasicPractice2View 类的实现
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "MFCBasicPractice2.h"
#endif

#include "MFCBasicPractice2Doc.h"
#include "MFCBasicPractice2View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define TIMER_TEXT 9527

// CMFCBasicPractice2View

IMPLEMENT_DYNCREATE(CMFCBasicPractice2View, CView)

BEGIN_MESSAGE_MAP(CMFCBasicPractice2View, CView)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_CREATE()
	ON_WM_TIMER()
END_MESSAGE_MAP()

// CMFCBasicPractice2View 构造/析构

CMFCBasicPractice2View::CMFCBasicPractice2View() noexcept
{
	// TODO: 在此处添加构造代码

	m_nWidth = 0;
}

CMFCBasicPractice2View::~CMFCBasicPractice2View()
{
}

BOOL CMFCBasicPractice2View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CMFCBasicPractice2View 绘图

void CMFCBasicPractice2View::OnDraw(CDC* /*pDC*/)
{
	CMFCBasicPractice2Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 在此处为本机数据添加绘制代码
}

void CMFCBasicPractice2View::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CMFCBasicPractice2View::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CMFCBasicPractice2View 诊断

#ifdef _DEBUG
void CMFCBasicPractice2View::AssertValid() const
{
	CView::AssertValid();
}

void CMFCBasicPractice2View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMFCBasicPractice2Doc* CMFCBasicPractice2View::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMFCBasicPractice2Doc)));
	return (CMFCBasicPractice2Doc*)m_pDocument;
}
#endif //_DEBUG


// CMFCBasicPractice2View 消息处理程序


void CMFCBasicPractice2View::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	CClientDC dc(this);

	CFont font;
	font.CreatePointFont(200, _T("华文行楷"));
	CFont* pOldFont = dc.SelectObject(&font);

	CString str(_T("你好我好大家好"));
	// 设置文字颜色
	dc.SetTextColor(RGB(120, 0, 125));

	// 输出字符串
	//dc.TextOut(point.x, point.y, str, str.GetLength());

	// 获取文字在屏幕上的空间大小,长度和宽度
	CSize cz = dc.GetTextExtent(str);
	// 在指定矩形区域内绘制文字
	dc.DrawText(str, CRect(point.x, point.y, point.x + cz.cx / 2, point.y + cz.cy), DT_LEFT);
	dc.SelectObject(pOldFont);

	CView::OnLButtonDown(nFlags, point);
}


void CMFCBasicPractice2View::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	CView::OnLButtonUp(nFlags, point);
}


int CMFCBasicPractice2View::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  在此添加您专用的创建代码
	SetTimer(TIMER_TEXT, 200, NULL);

	return 0;
}


void CMFCBasicPractice2View::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	CClientDC dc(this);
	CFont font;
	font.CreatePointFont(200, _T("华文行楷"));
	CFont* pOldFont = dc.SelectObject(&font);
	CString str(_T("你好我好大家好"));
	dc.SetTextColor(RGB(120, 0, 125));
	CSize cz = dc.GetTextExtent(str);
	CRect rect;
	switch (nIDEvent)
	{
	case TIMER_TEXT:
		m_nWidth += 10;
		// 获取文字在屏幕的空间大小,长度和宽度
		rect.left = 200;
		rect.top = 100;
		rect.bottom = rect.top + cz.cy;
		rect.right = rect.left + m_nWidth;

		// 在指定矩形区域内绘制文字
		dc.DrawText(str, rect, DT_LEFT);

		if (m_nWidth > cz.cx)
		{
			m_nWidth = 0;
			// 擦除屏幕上内容
			Invalidate();
		}
		dc.SelectObject(pOldFont);
		
		break;
	default:
		break;
	}
	CView::OnTimer(nIDEvent);
}
