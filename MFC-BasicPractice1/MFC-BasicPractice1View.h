
// MFC-BasicPractice1View.h: CMFCBasicPractice1View 类的接口
//

#pragma once


class CMFCBasicPractice1View : public CView
{
protected: // 仅从序列化创建
	CMFCBasicPractice1View() noexcept;
	DECLARE_DYNCREATE(CMFCBasicPractice1View)

// 特性
public:
	CMFCBasicPractice1Doc* GetDocument() const;

// 操作
public:

// 重写
public:
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:

// 实现
public:
	virtual ~CMFCBasicPractice1View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
protected:
	CPoint m_pOrigin;
public:
//	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
protected:
	bool m_pPressed;
public:
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
};

#ifndef _DEBUG  // MFC-BasicPractice1View.cpp 中的调试版本
inline CMFCBasicPractice1Doc* CMFCBasicPractice1View::GetDocument() const
   { return reinterpret_cast<CMFCBasicPractice1Doc*>(m_pDocument); }
#endif

