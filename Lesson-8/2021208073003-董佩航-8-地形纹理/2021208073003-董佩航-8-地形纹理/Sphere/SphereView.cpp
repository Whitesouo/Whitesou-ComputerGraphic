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
	CSphereDoc* pDoc = GetDocument();
	if (NULL == pDoc) return;
	if (pDoc->m_pModel != NULL)
		glmDraw(pDoc->m_pModel, GLM_SMOOTH | GLM_COLOR);
	glPopMatrix();
}


void CSphereView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)      //方向键控制图像向相应方向移动
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值 
	if (nChar == VK_LEFT)
	{
		m_xTranslation -= 0.01f;
		InvalidateRect(NULL, FALSE);
	}
	else if (nChar == VK_RIGHT)
	{
		m_xTranslation += 0.01f;
		InvalidateRect(NULL, FALSE);
	}
	else if (nChar == VK_UP)
	{
		m_yTranslation += 0.01f;
		InvalidateRect(NULL, FALSE);
	}
	else if (nChar == VK_DOWN)
	{
		m_yTranslation -= 0.01f;
		InvalidateRect(NULL, FALSE);
	}

	COpenGLView::OnKeyDown(nChar, nRepCnt, nFlags);
}


void CSphereView::OnSysKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)       //按下alt键的同时按下方向键
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if (nChar == VK_LEFT)
	{
		m_xTranslation -= 0.05f;
		InvalidateRect(NULL, FALSE);
	}
	else if (nChar == VK_RIGHT)
	{
		m_xTranslation += 0.05f;
		InvalidateRect(NULL, FALSE);
	}
	else if (nChar == VK_UP)
	{
		m_yTranslation += 0.05f;
		InvalidateRect(NULL, FALSE);
	}
	else if (nChar == VK_DOWN)
	{
		m_yTranslation -= 0.05f;
		InvalidateRect(NULL, FALSE);
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
	if (m_LeftButtonDown)
	{
		m_xRotation += (float)(point.y - m_LeftDownPos.y) / 3.0f;
		m_yRotation += (float)(point.x - m_LeftDownPos.x) / 3.0f;
		m_LeftDownPos = point;
		InvalidateRect(NULL, FALSE);
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

void CSphereView::Show()
{
	// 生成顶点数据和纹理坐标数据
	for (int y = 0; y < 64; y++)
	{
		for (int x = 0; x < 64; x++)
		{
			int index = y * 64 + x;

			// 设置顶点坐标
			vertices[index].x = x * planeSize / 63.0f - planeSize / 2.0f;
			vertices[index].y = y * planeSize / 63.0f - planeSize / 2.0f;
			vertices[index].z = 0.0f;

			// 设置纹理坐标
			texCoords[index].s = x * textureScale / 63.0f;
			texCoords[index].t = y * textureScale / 63.0f;
		}
	}

	// 生成索引数据
	int index = 0;
	for (int y = 0; y < 63; y++)
	{
		for (int x = 0; x < 63; x++)
		{
			int topLeft = y * 64 + x;
			int topRight = topLeft + 1;
			int bottomLeft = (y + 1) * 64 + x;
			int bottomRight = bottomLeft + 1;

			// 第一个三角形
			indices[index++] = topLeft;
			indices[index++] = bottomLeft;
			indices[index++] = topRight;

			// 第二个三角形
			indices[index++] = topRight;
			indices[index++] = bottomLeft;
			indices[index++] = bottomRight;
		}
	}
}


void  CSphereView::DrawPlane()
{
	for (int i = 0; i < planeSize - 1;)
	{
		glBegin(GL_TRIANGLE_STRIP);
		{
			// 设置顶点位置和纹理
			glColor3f(0, 0, 0);
			GLubyte* pixels = new GLubyte[height_width * height_height * 3]; // 假设纹理大小为width x height，并且每个像素有3个字节（RGB格式）

			
			glTexImage2D(GL_TEXTURE_2D, 0, 3, height_height,
				height_width, 0, GL_RGB, GL_UNSIGNED_BYTE,pixels);
			glGetTexImage(GL_TEXTURE_2D, 0, GL_RGB, GL_UNSIGNED_BYTE, pixels);
			GLubyte red = pixels[(int)(vertices[indices[i]].s* 64/height_width +
				vertices[indices[i]].t* 64/height_height) *3];
			glVertex3f(vertices[indices[i]].x, vertices[indices[i]].y, red);
			i++;
			red=pixels[(int)(vertices[indices[i]].s * 64 / height_width +
				vertices[indices[i]].t * 64 / height_height) * 3];
			glVertex3f(vertices[indices[i]].x, vertices[indices[i]].y,red);
			i++;
			red=pixels[(int)(vertices[indices[i]].s * 64 / height_width +
				vertices[indices[i]].t * 64 / height_height) * 3];
			glVertex3f(vertices[indices[i]].x, vertices[indices[i]].y, red);
			i++;
		}
		glEnd();

	}
}