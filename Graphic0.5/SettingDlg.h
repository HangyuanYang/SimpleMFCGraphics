#if !defined(AFX_SETTINGDLG_H__419EF7BB_9827_43BD_B595_B58ED7E3F9B6__INCLUDED_)
#define AFX_SETTINGDLG_H__419EF7BB_9827_43BD_B595_B58ED7E3F9B6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SettingDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// SettingDlg dialog

class SettingDlg : public CDialog
{
// Construction
public:
	SettingDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(SettingDlg)
	enum { IDD = IDD_DLG_SETTING };
	UINT	m_LineWidth;
	int		m_LineStyle;
	int		m_nFILLMODEL;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(SettingDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(SettingDlg)
	afx_msg void OnLineModel();
	afx_msg void OnFill();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SETTINGDLG_H__419EF7BB_9827_43BD_B595_B58ED7E3F9B6__INCLUDED_)
