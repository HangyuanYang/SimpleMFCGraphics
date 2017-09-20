// SettingDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Graphic.h"
#include "SettingDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// SettingDlg dialog


SettingDlg::SettingDlg(CWnd* pParent /*=NULL*/)
	: CDialog(SettingDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(SettingDlg)
	m_LineWidth = 0;
	m_LineStyle = 0;
	m_nFILLMODEL = 1;
	//}}AFX_DATA_INIT
}


void SettingDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(SettingDlg)
	DDX_Text(pDX, IDC_LINEWIDTH, m_LineWidth);
	DDX_Radio(pDX, IDC_LINEMODEL1, m_LineStyle);
	DDX_Radio(pDX, IDC_FILL1, m_nFILLMODEL);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(SettingDlg, CDialog)
	//{{AFX_MSG_MAP(SettingDlg)
	ON_BN_CLICKED(IDC_LINEMODEL1, OnLineModel)
	ON_BN_CLICKED(IDC_LINEMODEL2, OnLineModel)
	ON_BN_CLICKED(IDC_LINEMODEL3, OnLineModel)
	ON_BN_CLICKED(IDC_LINEMODEL4, OnLineModel)
	ON_BN_CLICKED(IDC_LINEMODEL5, OnLineModel)
	ON_BN_CLICKED(IDC_FILL1, OnFill)
	ON_BN_CLICKED(IDC_FILL2, OnFill)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// SettingDlg message handlers

void SettingDlg::OnLineModel() 
{
	// TODO: Add your control notification handler code here
	UpdateData(true);
}

void SettingDlg::OnFill() 
{
	// TODO: Add your control notification handler code here
	UpdateData(true);
}
