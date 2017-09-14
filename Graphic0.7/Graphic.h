// Graphic.h : main header file for the GRAPHIC application
//

#if !defined(AFX_GRAPHIC_H__258F2057_167A_49CF_94B9_6BE6179BA90E__INCLUDED_)
#define AFX_GRAPHIC_H__258F2057_167A_49CF_94B9_6BE6179BA90E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CGraphicApp:
// See Graphic.cpp for the implementation of this class
//

class CGraphicApp : public CWinApp
{
public:
	CGraphicApp();

//≈‰÷√GDI+
private:
	GdiplusStartupInput m_gdiplusStartupInput;
	ULONG_PTR m_pGdiToken;
	UINT m_nDrawType;
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGraphicApp)
	public:
	virtual BOOL InitInstance();
	virtual BOOL ExitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CGraphicApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GRAPHIC_H__258F2057_167A_49CF_94B9_6BE6179BA90E__INCLUDED_)
