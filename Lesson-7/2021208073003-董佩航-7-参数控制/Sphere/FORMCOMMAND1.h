
#ifndef __FORMCOMMAND1_H__
#define __FORMCOMMAND1_H__

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

/////////////////////////////////////////////////////////////////////////////
// CFormCommandView form view

#ifndef __AFXEXT_H__
#include <afxext.h>
#endif
#include <afxcmn.h>

class CSphereDoc;

class FORMCOMMAND1 : public CFormView
{
protected:
	FORMCOMMAND1();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(FORMCOMMAND1)

		// Form Data
public:
	//{{AFX_DATA(CFormCommandView)
	enum { IDD = IDD_FORM_COMMAND1 };
	CStatic	m_ControlColorLightSpecular;
	CStatic	m_ControlColorLightDiffuse;
	CSliderCtrl	m_SliderScaleZ;
	CSliderCtrl	m_SliderScaleY;
	CSliderCtrl	m_SliderScaleX;
	CStatic	m_ControlColorLightAmbient;
	CStatic	m_ControlBackColor;
	CButton  m_ControlModel0;
	CButton  m_ControlModel1;
	CButton  m_ControlModel2;
	COLORREF BackColor;
	COLORREF AmbientColor;
	COLORREF DiffuseColor;
	COLORREF SpecularColor;
	BOOL	m_Lighting;
	BOOL	m_Smooth;
	BOOL	m_Antialias;
	BOOL	m_VRotate;
	BOOL	m_LinkScale;
	CEdit m_La[3];
	CEdit m_Ld[3];
	CEdit m_Ls[3];
	//}}AFX_DATA

// Attributes
public:
	CSphereDoc* GetDocument();
	CView* GetRenderView();
	BOOL UpdateScale();
	float CastStringToFloat(CString input);

	// Operations
public:

	// Overrides
		// ClassWizard generated virtual function overrides
		//{{AFX_VIRTUAL(CFormCommandView)
public:
	virtual void OnInitialUpdate();
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~FORMCOMMAND1();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
	//{{AFX_MSG(CFormCommandView)
	afx_msg void OnPaint();
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnRadioModel0();
	afx_msg void OnRadioModel1();
	afx_msg void OnRadioModel2();
	afx_msg void OnCheckLighting();
	afx_msg void OnCheckSmooth();
	afx_msg void OnCheckVrotation();
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnCheckLinkScale();
	afx_msg void OnCheckAntialias();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnEnChangeEdit1();
	afx_msg void OnCbnSelchangeCombo1();
	afx_msg void OnEnChangeEdit2();
	afx_msg void OnEnChangeEdit6();
	afx_msg void OnEnChangeEditParam();
	afx_msg void OnNMCustomdrawSliderZ(NMHDR* pNMHDR, LRESULT* pResult);
};

#ifndef _DEBUG  // debug version in RenderView.cpp
inline CToolDoc* CFormCommandView::GetDocument()
{
	return (CToolDoc*)m_pDocument;
}
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FORMCOMMANDVIEW_H__A4283CC1_72E6_11D1_A6C2_00A0242C0A32__INCLUDED_)



