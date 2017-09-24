#if !defined(AFX_ZOOMDLG_H__7828793B_124F_42D7_BF72_DDC03DF8B459__INCLUDED_)
#define AFX_ZOOMDLG_H__7828793B_124F_42D7_BF72_DDC03DF8B459__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ZoomDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CZoomDlg dialog

class CZoomDlg : public CDialog
{
// Construction
public:
	CZoomDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CZoomDlg)
	enum { IDD = IDD_DLG_ZOOM };
	int		m_ZoomRow;
	int		m_ZoomColumn;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CZoomDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CZoomDlg)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ZOOMDLG_H__7828793B_124F_42D7_BF72_DDC03DF8B459__INCLUDED_)
