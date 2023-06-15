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
