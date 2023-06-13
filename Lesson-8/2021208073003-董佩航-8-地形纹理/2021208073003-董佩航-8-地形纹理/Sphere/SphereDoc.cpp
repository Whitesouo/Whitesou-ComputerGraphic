// SphereDoc.cpp : implementation of the CSphereDoc class

#include "stdafx.h"
#include "Sphere.h"

#include "SphereDoc.h"
#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSphereDoc

IMPLEMENT_DYNCREATE(CSphereDoc, CDocument)

BEGIN_MESSAGE_MAP(CSphereDoc, CDocument)
	//{{AFX_MSG_MAP(CSphereDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSphereDoc construction/destruction

CSphereDoc::CSphereDoc()
{
}

CSphereDoc::~CSphereDoc()
{
}

BOOL CSphereDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;
	m_pModel = NULL;
	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CSphereDoc serialization

void CSphereDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
	}
}

/////////////////////////////////////////////////////////////////////////////
// CSphereDoc diagnostics

#ifdef _DEBUG
void CSphereDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CSphereDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG



BOOL CSphereDoc::OnOpenDocument(LPCTSTR lpszPathName)
{
	if (m_pModel != NULL) glmDelete(m_pModel);
	m_pModel = glmReadOBJ((char *)lpszPathName);
	glmUnitize(m_pModel);
	glmFacetNormals(m_pModel);
	glmVertexNormals(m_pModel, 90);
	CSphereApp *pApp = (CSphereApp *)AfxGetApp();
	CMainFrame *pFrame = (CMainFrame *)pApp->m_pMainWnd;
	CView* pView = (CView*)pFrame->m_wndSplitter.GetPane(0, 1);
	pView->Invalidate(FALSE);
	return NULL;
}


void CSphereDoc::OnCloseDocument()
{
	// TODO: 在此添加专用代码和/或调用基类
	if (m_pModel != NULL) glmDelete(m_pModel);
	CDocument::OnCloseDocument();
}
