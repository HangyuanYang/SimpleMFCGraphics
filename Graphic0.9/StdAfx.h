// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//

#if !defined(AFX_STDAFX_H__DF0099FB_B603_49B4_929E_D3F1CC87346E__INCLUDED_)
#define AFX_STDAFX_H__DF0099FB_B603_49B4_929E_D3F1CC87346E__INCLUDED_

#if _MSC_VER > 1000
#pragma once


#endif // _MSC_VER > 1000

#define VC_EXTRALEAN		// Exclude rarely-used stuff from Windows headers


//配置GDI+
#define ULONG_PTR ULONG 

// MFC support for Internet Explorer 4 Common Controls	//此处必须添加，否则出错
#include <afxdtctl.h>

#include <atlbase.h>  //CString转WCHAR*

#include <gdiplus.h>
using namespace Gdiplus;
#pragma comment(lib, "gdiplus.lib")


#include <afxext.h>         // MFC extensions
#include <afxdisp.h>        // MFC Automation classes
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>			// MFC support for Windows Common Controls
#include <afxwin.h>         // MFC core and standard components
#endif // _AFX_NO_AFXCMN_SUPPORT


//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__DF0099FB_B603_49B4_929E_D3F1CC87346E__INCLUDED_)
