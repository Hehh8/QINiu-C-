
// MFCBasicPractice2View.h: CMFCBasicPractice2View 类的接口
//

#pragma once


class CMFCBasicPractice2View : public CView
{
protected: // 仅从序列化创建
	CMFCBasicPractice2View() noexcept;
	DECLARE_DYNCREATE(CMFCBasicPractice2View)

// 特性
public:
	CMFCBasicPractice2Doc* GetDocument() const;

// 操作
public:

// 重写
public:
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:

// 实现
public:
	virtual ~CMFCBasicPractice2View();
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
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
protected:
	int m_nWidth;
};

#ifndef _DEBUG  // MFCBasicPractice2View.cpp 中的调试版本
inline CMFCBasicPractice2Doc* CMFCBasicPractice2View::GetDocument() const
   { return reinterpret_cast<CMFCBasicPractice2Doc*>(m_pDocument); }
#endif

