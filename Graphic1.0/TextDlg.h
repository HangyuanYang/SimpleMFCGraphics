#if !defined(AFX_TEXTDLG_H__178A02C0_9F66_41F3_B5D7_EA2894884E67__INCLUDED_)
#define AFX_TEXTDLG_H__178A02C0_9F66_41F3_B5D7_EA2894884E67__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// TextDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CTextDlg dialog

class CTextDlg : public CDialog
{
// Construction
public:
	CTextDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CTextDlg)
	enum { IDD = IDD_DLG_TEXT };
	int		m_Textx;
	int		m_Texty;
	CString	m_Content;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTextDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTextDlg)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TEXTDLG_H__178A02C0_9F66_41F3_B5D7_EA2894884E67__INCLUDED_)
