
// HuXinView.cpp: CHuXinView 类的实现
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "HuXin.h"
#endif

#include "HuXinDoc.h"
#include "HuXinView.h"
#include "InputDataDLG.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CHuXinView

IMPLEMENT_DYNCREATE(CHuXinView, CView)

BEGIN_MESSAGE_MAP(CHuXinView, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_CREATE()
	ON_WM_DESTROY()
	ON_WM_SIZE()
	ON_WM_ERASEBKGND()
	ON_COMMAND(ID_Open_dlg, &CHuXinView::OnOpenDlg)
END_MESSAGE_MAP()

// CHuXinView 构造/析构

CHuXinView::CHuXinView() noexcept
{
	// TODO: 在此处添加构造代码
	this->m_GLPixelIndex = 0;
	this->m_hGLContext = NULL;

	//赋值
	control_point[0][0] = 0;
	control_point[0][1] = 0;
	control_point[1][0] = 1;
	control_point[1][1] = 3;
	control_point[2][0] = 2;
	control_point[2][1] = 1;
	control_point[3][0] = 3;
	control_point[3][1] = 3;

}

CHuXinView::~CHuXinView()
{
}

BOOL CHuXinView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	cs.style |= (WS_CLIPCHILDREN | WS_CLIPSIBLINGS);    //窗口风格


	return CView::PreCreateWindow(cs);
}

// CHuXinView 绘图

void CHuXinView::DrawScene(void)
{
	/*
	
	*/



	

	//循环
	float temp_point[4][2];
	glColor3f(1, 0, 0);
	glLineWidth(3);
	glBegin(GL_LINE_STRIP);
	for (int loop = 0; loop <= 50; loop++)
	{
		for (int i = 0; i <= 3; i++)
		{
			temp_point[i][0] = control_point[i][0];
			temp_point[i][1] = control_point[i][1];
		}
		//////////////////////////////////////////
		for (int s = 1; s <= 3; s++)
		{
			for (int i = 0; i <= 3 - s; i++)
			{
				temp_point[i][0] = (1 - loop / 50.0) * temp_point[i][0] + (loop / 50.0) * temp_point[i + 1][0];
				temp_point[i][1] = (1 - loop / 50.0) * temp_point[i][1] + (loop / 50.0) * temp_point[i + 1][1];
			}
		}
		glVertex2f(temp_point[0][0], temp_point[0][1]);
	}
	glEnd();

}

void CHuXinView::OnDraw(CDC* pDC)
{
	CHuXinDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 在此处为本机数据添加绘制代码
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();


	DrawScene();
	SwapBuffers(pDC->m_hDC);
}


// CHuXinView 打印

BOOL CHuXinView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CHuXinView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CHuXinView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
}

BOOL CHuXinView::SetWindowPixelFormat(HDC hDC)
{
	PIXELFORMATDESCRIPTOR  pixelDesc = { sizeof(PIXELFORMATDESCRIPTOR), 1,
																			   PFD_DRAW_TO_WINDOW |
																			   PFD_SUPPORT_OPENGL |
																			   PFD_DOUBLEBUFFER,
																			   PFD_TYPE_RGBA,   24,  0,0,0,0,0,0,  0,  0,  0,
																			   0,0,0,0,  32,   0,  0, 0,  0,  0,0,0 };
	m_GLPixelIndex = ChoosePixelFormat(hDC, &pixelDesc);

	if (m_GLPixelIndex == 0)
	{
		return FALSE;
	}

	if (SetPixelFormat(hDC, m_GLPixelIndex, &pixelDesc) == FALSE)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CHuXinView::CreateViewGLContext(HDC hDC)
{
	m_hGLContext = wglCreateContext(hDC);
	if (m_hGLContext == NULL) //创建失败
	{
		return FALSE;
	}

	if (wglMakeCurrent(hDC, m_hGLContext) == FALSE)
	{//选为当前RC失败
		return FALSE;
	}
	return TRUE;
}


// CHuXinView 诊断

#ifdef _DEBUG
void CHuXinView::AssertValid() const
{
	CView::AssertValid();
}

void CHuXinView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CHuXinDoc* CHuXinView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CHuXinDoc)));
	return (CHuXinDoc*)m_pDocument;
}
#endif //_DEBUG


// CHuXinView 消息处理程序

int CHuXinView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  在此添加您专用的创建代码
	HWND hWnd = this->GetSafeHwnd();
	HDC hDC = ::GetDC(hWnd);

	if (this->SetWindowPixelFormat(hDC) == FALSE)
	{
		return 0;
	}

	if (this->CreateViewGLContext(hDC) == FALSE)
	{
		return 0;
	}


	//////////////
	glewInit();
	glDrawBuffer(GL_BACK);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClearDepth(1.0);

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	/////////////

	return 0;
}

void CHuXinView::OnDestroy()
{
	CView::OnDestroy();

	// TODO: 在此处添加消息处理程序代码
	if (wglGetCurrentContext() != NULL)
	{
		wglMakeCurrent(NULL, NULL);
	}

	if (this->m_hGLContext != NULL)
	{
		wglDeleteContext(this->m_hGLContext);
		this->m_hGLContext = NULL;
	}

}

void CHuXinView::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType, cx, cy);

	// TODO: 在此处添加消息处理程序代码
	glViewport(0, 0, cx, cy);
	GLdouble aspect;
	if (cy == 0)
	{
		aspect = (GLdouble)cx;
	}
	else
	{
		aspect = (GLdouble)cx / (GLdouble)cy;
	}

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-5.0 * aspect, 5.0 * aspect, -5.0, 5.0, -13.0, 13.0);
	Invalidate();

}

BOOL CHuXinView::OnEraseBkgnd(CDC* pDC)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	//return CView::OnEraseBkgnd(pDC);

	return TRUE;
}

void CHuXinView::OnOpenDlg()
{
	// TODO: 在此添加命令处理程序代码
	InputDataDLG m_dlg;
	if (m_dlg.DoModal() == IDOK)
	{
		control_point[0][0] = m_dlg.point1_x;
		control_point[0][1] = m_dlg.point1_y;
		control_point[1][0] = m_dlg.point2_x;
		control_point[1][1] = m_dlg.point2_y;
		control_point[2][0] = m_dlg.point3_x;
		control_point[2][1] = m_dlg.point3_y;
		control_point[3][0] = m_dlg.point4_x;
		control_point[3][1] = m_dlg.point4_y;
	}
	Invalidate();
}
