// Protection.cpp : implementation file
//

#include "stdafx.h"
#include "Graphic.h"
#include "Protection.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CProtection dialog


CProtection::CProtection(CWnd* pParent /*=NULL*/)
	: CDialog(CProtection::IDD, pParent)
{
	//{{AFX_DATA_INIT(CProtection)
	m_Password = _T("");
	//}}AFX_DATA_INIT
}


void CProtection::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CProtection)
	DDX_Text(pDX, IDC_PASSWORD, m_Password);
	DDV_MaxChars(pDX, m_Password, 20);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CProtection, CDialog)
	//{{AFX_MSG_MAP(CProtection)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CProtection message handlers
