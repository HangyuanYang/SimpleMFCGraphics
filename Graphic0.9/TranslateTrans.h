#if !defined(AFX_TRANSLATETRANS_H__3B5CC69B_BEF3_4511_8946_AD5510167A27__INCLUDED_)
#define AFX_TRANSLATETRANS_H__3B5CC69B_BEF3_4511_8946_AD5510167A27__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// TranslateTrans.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CTranslateTrans dialog

class CTranslateTrans : public CDialog
{
// Construction
public:
	CTranslateTrans(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CTranslateTrans)
	enum { IDD = IDD_Dlg_TranslateTrans };
	int		m_TranslateLevel;
	int		m_TranslateVertical;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTranslateTrans)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTranslateTrans)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TRANSLATETRANS_H__3B5CC69B_BEF3_4511_8946_AD5510167A27__INCLUDED_)
