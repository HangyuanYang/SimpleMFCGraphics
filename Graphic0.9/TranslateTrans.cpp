// TranslateTrans.cpp : implementation file
//

#include "stdafx.h"
#include "Graphic.h"
#include "TranslateTrans.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTranslateTrans dialog


CTranslateTrans::CTranslateTrans(CWnd* pParent /*=NULL*/)
	: CDialog(CTranslateTrans::IDD, pParent)
{
	//{{AFX_DATA_INIT(CTranslateTrans)
	m_TranslateLevel = 100;
	m_TranslateVertical = 100;
	//}}AFX_DATA_INIT
}


void CTranslateTrans::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTranslateTrans)
	DDX_Text(pDX, IDC_TRANSLATELEVEL, m_TranslateLevel);
	DDV_MinMaxInt(pDX, m_TranslateLevel, -1000, 1000);
	DDX_Text(pDX, IDC_TRANSLATEVERTICAL, m_TranslateVertical);
	DDV_MinMaxInt(pDX, m_TranslateVertical, -1000, 1000);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CTranslateTrans, CDialog)
	//{{AFX_MSG_MAP(CTranslateTrans)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTranslateTrans message handlers
