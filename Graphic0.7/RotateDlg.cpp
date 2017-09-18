// RotateDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Graphic.h"
#include "RotateDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRotateDlg dialog


CRotateDlg::CRotateDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CRotateDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CRotateDlg)
	m_nAngle = 0;
	m_nRotateModel = 0;
	//}}AFX_DATA_INIT
}


void CRotateDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CRotateDlg)
	DDX_Text(pDX, IDC_ROTATEANGLE, m_nAngle);
	DDV_MinMaxInt(pDX, m_nAngle, 0, 1080);
	DDX_Radio(pDX, IDC_ROTATEMODEL1, m_nRotateModel);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CRotateDlg, CDialog)
	//{{AFX_MSG_MAP(CRotateDlg)
	ON_BN_CLICKED(IDC_ROTATEMODEL1, OnRotatemodel)
	ON_BN_CLICKED(IDC_ROTATEMODEL2, OnRotatemodel)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRotateDlg message handlers

void CRotateDlg::OnRotatemodel() 
{
	// TODO: Add your control notification handler code here
	UpdateData(true);
}
