#pragma once
#include <afxwin.h>
class test :
    public CView
{
    virtual void OnDraw(CDC* /*pDC*/);
public:
    DECLARE_MESSAGE_MAP()
//        afx_msg void OnAfxIdPreviewClose();
};

