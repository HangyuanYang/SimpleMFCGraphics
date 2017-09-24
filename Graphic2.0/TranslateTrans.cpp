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
	m_TranslateLevel = 0;
	m_TranslateVertical = 0;
	m_signal1 = 0;
	m_signal2 = 0;
	//}}AFX_DATA_INIT
}


void CTranslateTrans::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTranslateTrans)
	DDX_Text(pDX, IDC_TRANSLATELEVEL, m_TranslateLevel);
	DDV_MinMaxInt(pDX, m_TranslateLevel, 0, 1000);
	DDX_Text(pDX, IDC_TRANSLATEVERTICAL, m_TranslateVertical);
	DDV_MinMaxInt(pDX, m_TranslateVertical, 0, 1000);
	DDX_Radio(pDX, IDC_plus1, m_signal1);
	DDX_Radio(pDX, IDC_plus2, m_signal2);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CTranslateTrans, CDialog)
	//{{AFX_MSG_MAP(CTranslateTrans)
	ON_BN_CLICKED(IDC_plus1, OnSignal1)
	ON_BN_CLICKED(IDC_minus1, OnSignal1)
	ON_BN_CLICKED(IDC_plus2, OnSignal2)
	ON_BN_CLICKED(IDC_minus2, OnSignal2)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTranslateTrans message handlers


void CTranslateTrans::OnSignal1() 
{
	// TODO: Add your control notification handler code here
	UpdateData(true);
}

void CTranslateTrans::OnSignal2() 
{
	// TODO: Add your control notification handler code here
	UpdateData(true);
}
