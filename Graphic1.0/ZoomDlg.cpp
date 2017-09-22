// ZoomDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Graphic.h"
#include "ZoomDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CZoomDlg dialog


CZoomDlg::CZoomDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CZoomDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CZoomDlg)
	m_ZoomRow = 123;
	m_ZoomColumn = 123;
	//}}AFX_DATA_INIT
}


void CZoomDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CZoomDlg)
	DDX_Text(pDX, IDC_ZOOMROW, m_ZoomRow);
	DDV_MinMaxInt(pDX, m_ZoomRow, 1, 1000);
	DDX_Text(pDX, IDC_ZOOMCOLUMN, m_ZoomColumn);
	DDV_MinMaxInt(pDX, m_ZoomColumn, 1, 1000);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CZoomDlg, CDialog)
	//{{AFX_MSG_MAP(CZoomDlg)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CZoomDlg message handlers
