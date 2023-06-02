#include "stdafx.h"
#include "Sphere.h"
#include "MainFrm.h"
#include "FORMCOMMAND1.h"
#include "SphereDoc.h"
#include "SphereView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFormCommandView

IMPLEMENT_DYNCREATE(FORMCOMMAND1, CFormView)

FORMCOMMAND1::FORMCOMMAND1()
	: CFormView(FORMCOMMAND1::IDD)
{
	//{{AFX_DATA_INIT(CFormCommandView)

	BackColor = RGB(255, 255, 255);
	AmbientColor = RGB(128, 128, 128);

	m_Lighting = TRUE;
	m_Smooth = FALSE;
	m_Antialias = FALSE;
	m_VRotate = FALSE;
	m_LinkScale = FALSE;
	//}}AFX_DATA_INIT
}

FORMCOMMAND1::~FORMCOMMAND1()
{
}

void FORMCOMMAND1::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CFormCommandView)
	DDX_Control(pDX, IDC_FRAME_COLOR_LIGHT_AMBIENT3, m_ControlColorLightSpecular);
	DDX_Control(pDX, IDC_FRAME_COLOR_LIGHT_AMBIENT2, m_ControlColorLightDiffuse);
	DDX_Control(pDX, IDC_FRAME_COLOR_LIGHT_AMBIENT, m_ControlColorLightAmbient);
	DDX_Control(pDX, IDC_SLIDER_Z, m_SliderScaleZ);
	DDX_Control(pDX, IDC_SLIDER_Y, m_SliderScaleY);
	DDX_Control(pDX, IDC_SLIDER_X, m_SliderScaleX);
	DDX_Control(pDX, IDC_FRAME_COLOR_BACK, m_ControlBackColor);
	DDX_Control(pDX, IDC_RADIO_MODEL0, m_ControlModel0);
	DDX_Control(pDX, IDC_RADIO_MODEL1, m_ControlModel1);
	DDX_Control(pDX, IDC_RADIO_MODEL2, m_ControlModel2);
	DDX_Check(pDX, IDC_CHECK_LIGHTING, m_Lighting);
	DDX_Check(pDX, IDC_CHECK_SMOOTH, m_Smooth);
	DDX_Check(pDX, IDC_CHECK_ANTIALIAS, m_Antialias);
	DDX_Check(pDX, IDC_CHECK_VROTATION, m_VRotate);
	DDX_Control(pDX, IDC_EDIT2, m_La[0]);
	DDX_Control(pDX, IDC_EDIT3, m_La[1]);
	DDX_Control(pDX, IDC_EDIT4, m_La[2]);
	DDX_Control(pDX, IDC_EDIT5, m_Ld[0]);
	DDX_Control(pDX, IDC_EDIT6, m_Ld[1]);
	DDX_Control(pDX, IDC_EDIT7, m_Ld[2]);
	DDX_Control(pDX, IDC_EDIT8, m_Ls[0]);
	DDX_Control(pDX, IDC_EDIT9, m_Ls[1]);
	DDX_Control(pDX, IDC_EDIT10, m_Ls[2]);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(FORMCOMMAND1, CFormView)
	//{{AFX_MSG_MAP(CFormCommandView)
	ON_WM_PAINT()
	ON_WM_LBUTTONUP()
	ON_BN_CLICKED(IDC_RADIO_MODEL0, OnRadioModel0)
	ON_BN_CLICKED(IDC_RADIO_MODEL1, OnRadioModel1)
	ON_BN_CLICKED(IDC_RADIO_MODEL2, OnRadioModel2)
	ON_BN_CLICKED(IDC_CHECK_LIGHTING, OnCheckLighting)
	ON_BN_CLICKED(IDC_CHECK_SMOOTH, OnCheckSmooth)
	ON_BN_CLICKED(IDC_CHECK_VROTATION, OnCheckVrotation)
	ON_WM_HSCROLL()
	ON_BN_CLICKED(IDC_CHECK_LINK_SCALE, OnCheckLinkScale)
	ON_BN_CLICKED(IDC_CHECK_ANTIALIAS, OnCheckAntialias)
	//}}AFX_MSG_MAP
	ON_EN_CHANGE(IDC_EDIT2, &FORMCOMMAND1::OnEnChangeEditParam)
	ON_EN_CHANGE(IDC_EDIT3, &FORMCOMMAND1::OnEnChangeEditParam)
	ON_EN_CHANGE(IDC_EDIT4, &FORMCOMMAND1::OnEnChangeEditParam)
	ON_EN_CHANGE(IDC_EDIT5, &FORMCOMMAND1::OnEnChangeEditParam)
	ON_EN_CHANGE(IDC_EDIT6, &FORMCOMMAND1::OnEnChangeEditParam)
	ON_EN_CHANGE(IDC_EDIT7, &FORMCOMMAND1::OnEnChangeEditParam)
	ON_EN_CHANGE(IDC_EDIT8, &FORMCOMMAND1::OnEnChangeEditParam)
	ON_EN_CHANGE(IDC_EDIT9, &FORMCOMMAND1::OnEnChangeEditParam)
	ON_EN_CHANGE(IDC_EDIT10, &FORMCOMMAND1::OnEnChangeEditParam)

	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER_Z, &FORMCOMMAND1::OnNMCustomdrawSliderZ)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFormCommandView diagnostics

#ifdef _DEBUG
void FORMCOMMAND1::AssertValid() const
{
	CFormView::AssertValid();
}

void FORMCOMMAND1::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}

CSphereDoc* FORMCOMMAND1::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CSphereDoc)));
	return (CSphereDoc*)m_pDocument;
}

#endif //_DEBUG

//********************************************
// OnPaint
//********************************************
void FORMCOMMAND1::OnPaint()
{
	// Device context for painting
	CPaintDC dc(this);

	// Options are stored in Application
	CSphereApp* pApp = (CSphereApp*)AfxGetApp();
	CRect rect;

	// Color back
	m_ControlBackColor.GetWindowRect(&rect);
	ScreenToClient(&rect);
	CBrush BrushBack(BackColor);
	dc.FillRect(&rect, &BrushBack);

	// Color light ambient
	m_ControlColorLightAmbient.GetWindowRect(&rect);
	ScreenToClient(&rect);
	CBrush BrushLightAmbient(AmbientColor);
	dc.FillRect(&rect, &BrushLightAmbient);

	// Color light diffuse
	m_ControlColorLightDiffuse.GetWindowRect(&rect);
	ScreenToClient(&rect);
	CBrush BrushLightDiffuse(DiffuseColor);
	dc.FillRect(&rect, &BrushLightDiffuse);

	// Color light specular
	m_ControlColorLightSpecular.GetWindowRect(&rect);
	ScreenToClient(&rect);
	CBrush BrushLightSpecular(SpecularColor);
	dc.FillRect(&rect, &BrushLightSpecular);
}

//********************************************
// OnLButtonUp
//********************************************
void FORMCOMMAND1::OnLButtonUp(UINT nFlags, CPoint point)
{
	CRect rect;
	CSphereApp* pApp = (CSphereApp*)AfxGetApp();
	float r, g, b;

	// back color
	m_ControlBackColor.GetWindowRect(&rect);
	ScreenToClient(&rect);
	if (rect.PtInRect(point))
	{
		CColorDialog dlg(BackColor);
		if (dlg.DoModal() == IDOK)
		{
			BackColor = dlg.GetColor();
			CSphereView* pView = (CSphereView*)GetRenderView();
			r = (float)GetRValue(BackColor) / 255.0f;
			g = (float)GetGValue(BackColor) / 255.0f;
			b = (float)GetBValue(BackColor) / 255.0f;
			pView->m_ClearColorRed = r;
			pView->m_ClearColorGreen = g;
			pView->m_ClearColorBlue = b;
			glClearColor(r, g, b, 1.0f);
			this->InvalidateRect(&rect, FALSE);
			pView->InvalidateRect(NULL, FALSE);
		}
	}

	// ambient light color
	m_ControlColorLightAmbient.GetWindowRect(&rect);
	ScreenToClient(&rect);
	if (rect.PtInRect(point))
	{
		CColorDialog dlg(AmbientColor);
		if (dlg.DoModal() == IDOK)
		{
			AmbientColor = dlg.GetColor();
			CSphereView* pView = (CSphereView*)GetRenderView();
			// Refresh Light0
			r = (float)GetRValue(AmbientColor) / 255.0f;
			g = (float)GetGValue(AmbientColor) / 255.0f;
			b = (float)GetBValue(AmbientColor) / 255.0f;
			float	ambientProperties[] = { r,g,b,1.0f };
			glLightfv(GL_LIGHT0, GL_AMBIENT, ambientProperties);
			// Refresh views
			this->InvalidateRect(&rect, FALSE);
			pView->InvalidateRect(NULL, FALSE);
		}
	}

	// specular light color
	m_ControlColorLightSpecular.GetWindowRect(&rect);
	ScreenToClient(&rect);
	if (rect.PtInRect(point))
	{
		CColorDialog dlg(SpecularColor);
		if (dlg.DoModal() == IDOK)
		{
			SpecularColor = dlg.GetColor();
			CSphereView* pView = (CSphereView*)GetRenderView();
			// Refresh Light0
			float r = (float)GetRValue(SpecularColor) / 255.0f;
			float g = (float)GetGValue(SpecularColor) / 255.0f;
			float b = (float)GetBValue(SpecularColor) / 255.0f;
			float	specularProperties[] = { r,g,b,1.0f };
			glLightfv(GL_LIGHT0, GL_DIFFUSE, specularProperties);
			// Refresh views
			this->InvalidateRect(&rect, FALSE);
			pView->InvalidateRect(NULL, FALSE);
		}
	}

	// diffuse light color
	m_ControlColorLightDiffuse.GetWindowRect(&rect);
	ScreenToClient(&rect);
	if (rect.PtInRect(point))
	{
		CColorDialog dlg(DiffuseColor);
		if (dlg.DoModal() == IDOK)
		{
			DiffuseColor = dlg.GetColor();
			CSphereView* pView = (CSphereView*)GetRenderView();
			// Refresh Light0
			float r = (float)GetRValue(DiffuseColor) / 255.0f;
			float g = (float)GetGValue(DiffuseColor) / 255.0f;
			float b = (float)GetBValue(DiffuseColor) / 255.0f;
			float	diffuseProperties[] = { r,g,b,1.0f };
			glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseProperties);
			// Refresh views
			this->InvalidateRect(&rect, FALSE);
			pView->InvalidateRect(NULL, FALSE);
		}
	}
	CFormView::OnLButtonUp(nFlags, point);
}


//********************************************
// GetRenderView
//********************************************
CView* FORMCOMMAND1::GetRenderView()
{
	CSphereApp* pApp = (CSphereApp*)AfxGetApp();
	CMainFrame* pFrame = (CMainFrame*)pApp->m_pMainWnd;
	CView* pView = (CView*)pFrame->m_wndSplitter.GetPane(0, 1);
	return pView;
}

//********************************************
// Model
//********************************************
void FORMCOMMAND1::OnRadioModel0()
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
	this->GetRenderView()->InvalidateRect(NULL, FALSE);
}

void FORMCOMMAND1::OnRadioModel1()
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	this->GetRenderView()->InvalidateRect(NULL, FALSE);
}

void FORMCOMMAND1::OnRadioModel2()
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	this->GetRenderView()->InvalidateRect(NULL, FALSE);
}

//********************************************
// OnCheckLighting
//********************************************
void FORMCOMMAND1::OnCheckLighting()
{
	m_Lighting = !m_Lighting;
	if (m_Lighting)
		glEnable(GL_LIGHTING);
	else
		glDisable(GL_LIGHTING);

	this->GetRenderView()->InvalidateRect(NULL, FALSE);
}

//********************************************
// OnCheckSmooth
//********************************************
void FORMCOMMAND1::OnCheckSmooth()
{
	m_Smooth = !m_Smooth;
	if (m_Smooth)
		glShadeModel(GL_SMOOTH);
	else
		glShadeModel(GL_FLAT);
	GetRenderView()->InvalidateRect(NULL, FALSE);

}

void FORMCOMMAND1::OnCheckVrotation()
{
	m_VRotate = !m_VRotate;
	CSphereView* pView = (CSphereView*)GetRenderView();
	if (m_VRotate)
		pView->SetTimer(1, 10, NULL);
	else
		pView->KillTimer(1);
}

//********************************************
// OnInitialUpdate
//********************************************
void FORMCOMMAND1::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	// Slider
	TRACE("Sliders : updating...\n");
	m_SliderScaleX.SetRange(1, 100, TRUE);
	m_SliderScaleY.SetRange(1, 100, TRUE);
	m_SliderScaleZ.SetRange(1, 100, TRUE);

	m_SliderScaleX.SetPos(50);
	m_SliderScaleY.SetPos(50);
	m_SliderScaleZ.SetPos(50);

	m_La[0].SetWindowTextA(_T("1"));
	m_La[1].SetWindowTextA(_T("1"));
	m_La[2].SetWindowTextA(_T("1"));
	m_Ld[0].SetWindowTextA(_T("1"));
	m_Ld[1].SetWindowTextA(_T("1"));
	m_Ld[2].SetWindowTextA(_T("1"));
	m_Ls[0].SetWindowTextA(_T("1"));
	m_Ls[1].SetWindowTextA(_T("1"));
	m_Ls[2].SetWindowTextA(_T("1"));

	m_ControlModel1.SetCheck(1);

}

//********************************************
// OnHScroll
//********************************************
void FORMCOMMAND1::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	UpdateScale();
	GetRenderView()->InvalidateRect(NULL, FALSE);
	CFormView::OnHScroll(nSBCode, nPos, pScrollBar);
}


BOOL FORMCOMMAND1::UpdateScale()
{
	CSphereView* pView = (CSphereView*)GetRenderView();
	pView->m_xScaling = (float)m_SliderScaleX.GetPos() / 50.0f;
	pView->m_yScaling = (float)m_SliderScaleY.GetPos() / 50.0f;
	pView->m_zScaling = (float)m_SliderScaleZ.GetPos() / 50.0f;

	if (m_LinkScale)
	{
		m_SliderScaleY.SetPos(m_SliderScaleX.GetPos());
		m_SliderScaleZ.SetPos(m_SliderScaleX.GetPos());
		pView->m_yScaling = pView->m_zScaling = pView->m_xScaling;
	}

	return TRUE;
}

void FORMCOMMAND1::OnCheckLinkScale()
{
	m_LinkScale = !m_LinkScale;

	if (m_LinkScale)
	{
		CSphereView* pView = (CSphereView*)GetRenderView();
		m_SliderScaleY.SetPos(m_SliderScaleX.GetPos());
		m_SliderScaleZ.SetPos(m_SliderScaleX.GetPos());
		pView->m_yScaling = pView->m_zScaling = pView->m_xScaling;
	}

	m_SliderScaleY.EnableWindow(!m_LinkScale);
	m_SliderScaleZ.EnableWindow(!m_LinkScale);
	GetRenderView()->InvalidateRect(NULL, FALSE);

}

//********************************************
// OnCheckAntialias
// Toggle antialiased lines
//********************************************
void FORMCOMMAND1::OnCheckAntialias()
{
	m_Antialias = !m_Antialias;

	if (m_Antialias)
	{
		glEnable(GL_LINE_SMOOTH);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
		glLineWidth(1.5f);
	}
	else
	{
		glDisable(GL_LINE_SMOOTH);
		glDisable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
		glLineWidth(1.0f);
	}
	GetRenderView()->InvalidateRect(NULL, FALSE);
}


void FORMCOMMAND1::OnEnChangeEdit1()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CFormView::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}


void FORMCOMMAND1::OnCbnSelchangeCombo1()
{
	// TODO: 在此添加控件通知处理程序代码
}


void FORMCOMMAND1::OnEnChangeEdit2()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CFormView::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}


void FORMCOMMAND1::OnEnChangeEdit6()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CFormView::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}
void FORMCOMMAND1::OnEnChangeEditParam()
{
	float La[3], Ld[3], Ls[3];
	CString S_La[3], S_Ld[3], S_Ls[3];
	m_La[0].GetWindowTextA(S_La[0]);
	m_La[1].GetWindowTextA(S_La[1]);
	m_La[2].GetWindowTextA(S_La[2]);
	m_Ld[0].GetWindowTextA(S_Ld[0]);
	m_Ld[1].GetWindowTextA(S_Ld[1]);
	m_Ld[2].GetWindowTextA(S_Ld[2]);
	m_Ls[0].GetWindowTextA(S_Ls[0]);
	m_Ls[1].GetWindowTextA(S_Ls[1]);
	m_Ls[2].GetWindowTextA(S_Ls[2]);
	////La[0] = static_cast<float>(std::atof(S_La[0]));
	////La[1] = static_cast<float>(std::atof(S_La[1]));
	////La[2] = static_cast<float>(std::atof(S_La[2]));
	////Ld[0] = static_cast<float>(std::atof(S_Ld[0]));
	////Ld[1] = static_cast<float>(std::atof(S_Ld[1]));
	////Ld[2] = static_cast<float>(std::atof(S_Ld[2]));
	////Ls[0] = static_cast<float>(std::atof(S_Ls[0]));
	////Ls[1] = static_cast<float>(std::atof(S_Ls[1]));
	////Ls[2] = static_cast<float>(std::atof(S_Ls[2]));
	////// 将float值映射到[0, 1]区间
	////for(int i = 0; i < 3; i++)
	////{
	////	La[i]=(La[i] < 0.0f) ? 0.0f : La[i];
	////	La[i] = (La[i] > 1.0f) ? 1.0f : La[i];
	////	Ld[i] = (Ld[i] < 0.0f) ? 0.0f : Ld[i];
	////	Ld[i] = (Ld[i] > 1.0f) ? 1.0f : Ld[i];
	////	Ls[i] = (Ls[i] < 0.0f) ? 0.0f : Ls[i];
	////	Ls[i] = (Ls[i] > 1.0f) ? 1.0f : Ls[i];

	////}

	CSphereView* pView = (CSphereView*)GetRenderView();
	pView->m_La_r = La[0];
	pView->m_La_g = La[1];
	pView->m_La_b = La[2];

	//// 获取Edit Control的值并保存到成员变量
	GetRenderView()->InvalidateRect(NULL, FALSE);

}

void FORMCOMMAND1::OnNMCustomdrawSliderZ(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;
}
