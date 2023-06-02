// SphereView.cpp : implementation of the CSphereView class

#include "stdafx.h"
#include <math.h>

#include "Sphere.h"
#include "SphereDoc.h"
#include "SphereView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSphereView

IMPLEMENT_DYNCREATE(CSphereView, COpenGLView)

BEGIN_MESSAGE_MAP(CSphereView, COpenGLView)
	//{{AFX_MSG_MAP(CSphereView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
	ON_WM_KEYDOWN()
	ON_WM_SYSKEYDOWN()
	ON_WM_MOUSEWHEEL()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_CREATE()
	ON_WM_MOUSEHWHEEL()
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSphereView construction/destruction
CSphereView::CSphereView()
{
	// TODO: add construction code here
	m_xTranslation = 0.0f;
	m_yTranslation = 0.0f;
	m_zTranslation = 0.0f;

	m_xScaling = 1.0f;
	m_yScaling = 1.0f;
	m_zScaling = 1.0f;

	m_LeftButtonDown = FALSE;
	m_xRotation = 0.0f;
	m_yRotation = 0.0f;
}

CSphereView::~CSphereView()
{
}

/////////////////////////////////////////////////////////////////////////////
// CSphereView printing

BOOL CSphereView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CSphereView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CSphereView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CSphereView diagnostics

#ifdef _DEBUG
void CSphereView::AssertValid() const
{
	CView::AssertValid();
}

void CSphereView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CSphereDoc* CSphereView::GetDocument() // non-debug version is inline   在视图类中访问相应的文档类
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CSphereDoc)));
	return (CSphereDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CSphereView message handlers
void CSphereView::Display()
{
	// clear background
	glClearColor(m_ClearColorRed, m_ClearColorGreen, m_ClearColorBlue, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	// scale / translation / rotation
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
	glScalef(m_xScaling, m_yScaling, m_zScaling);
	glTranslatef(m_xTranslation, m_yTranslation, m_zTranslation);
	glRotatef(m_xRotation, 1.0f, 0.0f, 0.0f);
	glRotatef(m_yRotation, 0.0f, 1.0f, 0.0f);
	GLfloat	ambientProperties[] = { m_La_r, m_La_g, m_La_b, 1.0f };
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambientProperties);
	CSphereDoc* pDoc = GetDocument();
	if (NULL == pDoc) return;
	if (pDoc->m_pModel != NULL)
		glmDraw(pDoc->m_pModel, GLM_SMOOTH | GLM_COLOR);
	glPopMatrix();
}                                                                                                                                                                                                                                                                                                                                                                                       


void CSphereView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)      //方向键控制图像向相应方向移动
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值 
	if(nChar==VK_LEFT)
	{
		m_xTranslation-=0.01f; 
		InvalidateRect(NULL,FALSE);
	}
	else if(nChar==VK_RIGHT)
	{
		m_xTranslation+=0.01f; 
		InvalidateRect(NULL,FALSE);
	}
	else if(nChar==VK_UP)
	{
		m_yTranslation+=0.01f; 
		InvalidateRect(NULL,FALSE);
	}
	else if(nChar==VK_DOWN)
	{
		m_yTranslation-=0.01f; 
		InvalidateRect(NULL,FALSE);
	}

	COpenGLView::OnKeyDown(nChar, nRepCnt, nFlags);
}


void CSphereView::OnSysKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)       //按下alt键的同时按下方向键
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if(nChar==VK_LEFT)
	{
		m_xTranslation-=0.05f; 
		InvalidateRect(NULL,FALSE);
	}
	else if(nChar==VK_RIGHT)
	{
		m_xTranslation+=0.05f; 
		InvalidateRect(NULL,FALSE);
	}
	else if(nChar==VK_UP)
	{
		m_yTranslation+=0.05f; 
		InvalidateRect(NULL,FALSE);
	}
	else if(nChar==VK_DOWN)
	{
		m_yTranslation-=0.05f; 
		InvalidateRect(NULL,FALSE);
	}
	COpenGLView::OnSysKeyDown(nChar, nRepCnt, nFlags);
}

void CSphereView::OnLButtonDown(UINT nFlags, CPoint point)                   //鼠标左键按下
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值                    
	m_LeftButtonDown = TRUE;
	m_LeftDownPos = point;

	COpenGLView::OnLButtonDown(nFlags, point);
}


void CSphereView::OnLButtonUp(UINT nFlags, CPoint point)                   //鼠标左键抬起
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	m_LeftButtonDown = FALSE;
	COpenGLView::OnLButtonUp(nFlags, point);
}


void CSphereView::OnMouseMove(UINT nFlags, CPoint point)                   //鼠标移动
{                    
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if(m_LeftButtonDown)
	{
		m_xRotation += (float)(point.y - m_LeftDownPos.y) / 3.0f;
		m_yRotation += (float)(point.x - m_LeftDownPos.x) / 3.0f;
		m_LeftDownPos = point;
		InvalidateRect(NULL,FALSE);
	}
	COpenGLView::OnMouseMove(nFlags, point);
}

int CSphereView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (COpenGLView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// Default mode
	glPolygonMode(GL_FRONT, GL_LINE);
	glPolygonMode(GL_BACK, GL_LINE);
	glShadeModel(GL_FLAT);
	glEnable(GL_NORMALIZE);

	// Lights, material properties
	GLfloat	ambientProperties[] = { 0.5f, 0.5f, 0.5f, 1.0f };
	GLfloat	diffuseProperties[] = { 0.8f, 0.8f, 0.8f, 1.0f };
	GLfloat	specularProperties[] = { 0.0f, 0.8f, 0.2f, 1.0f };

	glClearDepth(1.0f);

	m_ClearColorRed = 1.0f;
	m_ClearColorGreen = 1.0f;
	m_ClearColorBlue = 1.0f;

	glLightfv(GL_LIGHT0, GL_AMBIENT, ambientProperties);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseProperties);
	glLightfv(GL_LIGHT0, GL_SPECULAR, specularProperties);
	glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_FALSE);

	// Default : lighting
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHTING);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(m_ClearColorRed, m_ClearColorGreen, m_ClearColorBlue, 1.0f);
	return 0;
}


void CSphereView::OnMouseHWheel(UINT nFlags, short zDelta, CPoint pt)
{
	// 此功能要求 Windows Vista 或更高版本。
	// _WIN32_WINNT 符号必须 >= 0x0600。
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	COpenGLView::OnMouseHWheel(nFlags, zDelta, pt);
}
