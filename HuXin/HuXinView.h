
// HuXinView.h: CHuXinView 类的接口
//

#pragma once


class CHuXinView : public CView
{
protected: // 仅从序列化创建
	CHuXinView() noexcept;
	DECLARE_DYNCREATE(CHuXinView)

	int m_GLPixelIndex;
	HGLRC m_hGLContext;



// 特性
public:
	CHuXinDoc* GetDocument() const;

// 操作
public:
	void DrawScene(void);
	float control_point[4][2];

// 重写
public:
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

	BOOL SetWindowPixelFormat(HDC hDC);
	BOOL CreateViewGLContext(HDC hDC);


// 实现
public:
	virtual ~CHuXinView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnOpenDlg();
};

#ifndef _DEBUG  // HuXinView.cpp 中的调试版本
inline CHuXinDoc* CHuXinView::GetDocument() const
   { return reinterpret_cast<CHuXinDoc*>(m_pDocument); }
#endif

