// SphereView.h : interface of the CSphereView class

#ifndef ___SPHERE_VIEW_H___
#define ___SPHERE_VIEW_H___

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "OpenGLView.h"
#include "SphereDoc.h"

class CSphereView : public COpenGLView
{
protected: // create from serialization only
	CSphereView();
	DECLARE_DYNCREATE(CSphereView)

// Attributes
public:
	CSphereDoc* GetDocument();

// Operations
public:
	// 定义顶点数据结构
	struct Vertex
	{
		float x, y, z;     // 顶点坐标
		float s, t;        // 纹理坐标
	};

	// 定义纹理坐标结构
	struct TexCoord
	{
		float s, t;        // 纹理坐标
	};
	static const int numVertices = 64 * 64;
	static const int numIndices = 6 * (64 - 1) * (64 - 1); // 每个最小正方形有两个三角形，每个三角形有3个顶点

	Vertex vertices[numVertices];
	TexCoord texCoords[numVertices];
	unsigned int indices[numIndices];
	const float planeSize = 1.0f; // 平面大小
	const float textureScale = 1.0f; // 纹理缩放比例
	const float height_height = 640;
	const float height_width = 640;


	float m_xTranslation;
	float m_yTranslation;
	float m_zTranslation;

	float m_xScaling;
	float m_yScaling;
	float m_zScaling;

	CPoint m_LeftDownPos;
	BOOL m_LeftButtonDown;

	float m_xRotation;
	float m_yRotation;
	// Colors
	float m_ClearColorRed;
	float m_ClearColorGreen;
	float m_ClearColorBlue;
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSphereView)
	public:
	protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	//void Init();
	void Display();
//	void DrawTriangle(float *v1, float *v2, float *v3);
//	void Subdivide(float *v1, float *v2, float *v3, long depth);
//	void NormCrossProd(float v1[3], float v2[3], float out[3]);
//	void Normalize(float v[3]);
	virtual ~CSphereView();
	void Show();
	void GeneratePlane();
	void DrawPlane();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CSphereView)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
//	virtual HRESULT accDoDefaultAction(VARIANT varChild);
//	void DrawNormSphere(void);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnSysKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnMouseHWheel(UINT nFlags, short zDelta, CPoint pt);
};

#ifndef _DEBUG  // debug version in MyTestOpenGLView.cpp
inline CSphereDoc* CSphereView::GetDocument()
   { return (CSphereDoc*)m_pDocument; }
#endif

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif
