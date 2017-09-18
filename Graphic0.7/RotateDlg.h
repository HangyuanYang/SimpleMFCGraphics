#if !defined(AFX_ROTATEDLG_H__E7217A5A_A159_4886_BC1C_5FD1BAF4BD44__INCLUDED_)
#define AFX_ROTATEDLG_H__E7217A5A_A159_4886_BC1C_5FD1BAF4BD44__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// RotateDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CRotateDlg dialog

class CRotateDlg : public CDialog
{
// Construction
public:
	CRotateDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CRotateDlg)
	enum { IDD = IDD_DLG_ROTATE };
	int		m_nAngle;
	int		m_nRotateModel;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRotateDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CRotateDlg)
	afx_msg void OnRotatemodel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ROTATEDLG_H__E7217A5A_A159_4886_BC1C_5FD1BAF4BD44__INCLUDED_)
