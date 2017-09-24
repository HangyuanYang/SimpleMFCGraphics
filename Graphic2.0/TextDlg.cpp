// TextDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Graphic.h"
#include "TextDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTextDlg dialog


CTextDlg::CTextDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CTextDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CTextDlg)
	m_Textx = 0;
	m_Texty = 0;
	m_Content = _T("nayifu");
	//}}AFX_DATA_INIT
}


void CTextDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTextDlg)
	DDX_Text(pDX, IDC_EDITX, m_Textx);
	DDX_Text(pDX, IDC_EDITY, m_Texty);
	DDX_Text(pDX, IDC_EDITCONTENT, m_Content);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CTextDlg, CDialog)
	//{{AFX_MSG_MAP(CTextDlg)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTextDlg message handlers
