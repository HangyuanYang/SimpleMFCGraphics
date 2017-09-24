#if !defined(AFX_PROTECTION_H__4E6602EC_BDAE_440E_ADDC_B102810B5613__INCLUDED_)
#define AFX_PROTECTION_H__4E6602EC_BDAE_440E_ADDC_B102810B5613__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Protection.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CProtection dialog

class CProtection : public CDialog
{
// Construction
public:
	CProtection(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CProtection)
	enum { IDD = IDD_FakeProtection };
	CString	m_Password;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CProtection)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CProtection)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PROTECTION_H__4E6602EC_BDAE_440E_ADDC_B102810B5613__INCLUDED_)
