// GraphicView.cpp : implementation of the CGraphicView class
//

#include "StdAfx.h"
#include "Graphic.h"

#include "GraphicDoc.h"
#include "GraphicView.h"
#include "SettingDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CGraphicView

IMPLEMENT_DYNCREATE(CGraphicView, CView)

BEGIN_MESSAGE_MAP(CGraphicView, CView)
	//{{AFX_MSG_MAP(CGraphicView)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_COMMAND(IDM_LINE, OnLine)
	ON_COMMAND(IDM_RECTANGLE, OnRectangle)
	ON_COMMAND(IDM_DOT, OnDot)
	ON_COMMAND(IDM_ELLIPSE, OnEllipse)
	ON_COMMAND(IDM_SECTOR, OnSector)
	ON_COMMAND(IDM_Polyline, OnPolyline)
	ON_WM_MOUSEMOVE()
	ON_COMMAND(IDM_SIMPLEBRUSH, OnSimplebrush)
	ON_COMMAND(IDM_BITMAPBRUSH, OnBitmapbrush)
	ON_COMMAND(IDM_TRANSPARENTBRUSH, OnTransparentbrush)
 	ON_COMMAND(IDM_COLOR, OnColor)
	ON_COMMAND(IDM_SETTING, OnSetting)
	ON_COMMAND(ID_FILE_SAVE, OnFileSave)
	ON_COMMAND(ID_FILE_OPEN, OnFileOpen)
	ON_WM_LBUTTONDBLCLK()
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGraphicView construction/destruction

CGraphicView::CGraphicView()
{
	// TODO: add construction code here
	m_nDrawType=0;
	m_bDraw=false;
	m_LineStyle=0;
	m_LineWidth=1;
	m_Color=RGB(50,200,100);
}

CGraphicView::~CGraphicView()
{
}

BOOL CGraphicView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CGraphicView drawing

void CGraphicView::OnDraw(CDC* pDC)
{
	CGraphicDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here

  //GDI+使用尝试
	Graphics graphics(pDC->m_hDC);
	Pen pen(Color(255, 0, 255));
	graphics.DrawLine(&pen, 0, 0, 200, 100);

}

/////////////////////////////////////////////////////////////////////////////
// CGraphicView printing

BOOL CGraphicView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CGraphicView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CGraphicView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CGraphicView diagnostics

#ifdef _DEBUG
void CGraphicView::AssertValid() const
{
	CView::AssertValid();
}

void CGraphicView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CGraphicDoc* CGraphicView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CGraphicDoc)));
	return (CGraphicDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CGraphicView message handlers


void CGraphicView::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	m_ptOrigin=point;
	m_bDraw=true;
	CView::OnLButtonDown(nFlags, point);
}

void CGraphicView::OnLButtonUp(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	//创建并获得设备描述
	CClientDC dc(this);
	m_bDraw=false;

	CPen pen(m_LineStyle,m_LineWidth,m_Color);//创建画笔
	dc.SelectObject(&pen);		//选择画笔

	switch (m_nDrawType){
	  case 1:/*绘制点*/ 
		  dc.SetPixel(point,m_Color); 
		  break;   
	  case 2:/*绘制直线*/
		  dc.MoveTo(m_ptOrigin);
		  /*调用MoveTo函数移动到原点*/
		  dc.LineTo(point);
		  /*调用LineTo函数绘制到终点*/
		  break;
	  case 3:/*绘制矩形*/
		  dc.Rectangle(CRect(m_ptOrigin,point));
		  break;
	  case 4:/*绘制椭圆*/
		  dc.Ellipse(CRect(m_ptOrigin,point));
		  break;
	}
	//-_-  case中无法声明变量
	if(m_nDrawType==7){
		CBrush brush(m_Color);
	    //利用画刷填充鼠标拖曳过程中形成的矩形区域 
        dc.FillRect(CRect(m_ptOrigin,point),&brush);
	}
	if(m_nDrawType==8){
		  //创建位图对象
		  CBitmap bitmap;
		  //加载位图资源
		  bitmap.LoadBitmap(IDB_BITMAP1);
		  //创建位图画刷
		  CBrush brush(&bitmap);
		  //利用红色画刷填充鼠标拖曳过程中形成的矩形区域
		  dc.FillRect(CRect(m_ptOrigin,point),&brush);
	}
	if(m_nDrawType==9){
		  //创建一个空画刷
		  CBrush *pBrush=CBrush::FromHandle((HBRUSH)GetStockObject(NULL_BRUSH));
		  //将空画刷选入设备描述表
		  CBrush *pOldBrush = dc.SelectObject(pBrush);
		  //绘制一个矩形
		  dc.Rectangle(CRect(m_ptOrigin,point));
		  //恢复先前的画刷
		  dc.SelectObject(pOldBrush);
	}
//??
	OnPrepareDC(&dc);
	dc.DPtoLP(&m_ptOrigin);
	dc.DPtoLP(&point);

	CView::OnLButtonUp(nFlags, point);
}

void CGraphicView::OnMouseMove(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	//创建并获得设备描述
	CClientDC dc(this);
	//创建画笔
	CPen pen (m_LineStyle,m_LineWidth, m_Color);
	//把创建的画笔选入设备描述
	CPen *pOldpen=dc.SelectObject(&pen);

	if(m_bDraw==true)
		switch(m_nDrawType){
			case 5:
				dc.MoveTo(m_ptOrigin);                  
				dc.LineTo(point);
				break;
			case 6:
				dc.MoveTo(m_ptOrigin);                  
				dc.LineTo(point);
				//修改线段的起点        
				m_ptOrigin=point;
				break;
		}
	//恢复设备描述
	dc.SelectObject(pOldpen);


	CView::OnMouseMove(nFlags, point);
}


void CGraphicView::OnSetting(){
	//TODO: Add your command handler code here
	SettingDlg dlg;
	dlg.m_LineWidth=m_LineWidth;
	dlg.m_LineStyle=m_LineStyle;
	if(IDOK==dlg.DoModal()){
		m_LineWidth=dlg.m_LineWidth;
		m_LineStyle=dlg.m_LineStyle;
	}
} 

void CGraphicView::OnColor()  {
	// TODO: Add your command handler code here
	CColorDialog dlg;
	dlg.m_cc.Flags|=CC_RGBINIT|CC_FULLOPEN;
	dlg.m_cc.rgbResult=RGB(50,200,100);
	if(IDOK==dlg.DoModal()){
		m_Color=dlg.m_cc.rgbResult; 
	}
}


/*
void CGraphicView::OnInitialUpdate() 
{
	CView::OnInitialUpdate();
	// TODO: Add your specialized code here and/or call the base class
	SetScrollSizes(MM_TEXT,CSize(1024,768)); 
}
*/



//获取图片CLSID
static int GetEncoderClsid(const TCHAR* format, CLSID* pClsid)
{
    UINT num= 0;
    UINT size= 0;
    ImageCodecInfo* pImageCodecInfo= NULL;

    GetImageEncodersSize(&num,&size);
    if(size== 0)
    {
        return -1;
    }

    pImageCodecInfo= (ImageCodecInfo*)(malloc(size));
    if(pImageCodecInfo== NULL)
    {
        return -1;
    }

    GetImageEncoders(num, size, pImageCodecInfo);

    for(UINT j=0; j< num; ++j)
    {
		//??
        if(_tcscmp((char*)pImageCodecInfo[j].MimeType,(char*)format)== 0)
        {
            *pClsid= pImageCodecInfo[j].Clsid;
            free(pImageCodecInfo);

            return j;
        }
    }
    free(pImageCodecInfo);
    return -1;
}

void CGraphicView::OnFileSave() 
{
	
	// TODO: Add your command handler code here
	HDC hmemDC = ::CreateCompatibleDC( hdc );  
	HBITMAP hBmp = ::CreateCompatibleBitmap( hdc, destRect.Width(),destRect.Height() );
	HANDLE hOld = ::SelectObject(hmemDC, hBmp);

	Graphics graphic( hmemDC );
	//下面进行各种文字、图形、图片的绘制

	Bitmap bitmap(hBmp, NULL );
	CLSID clsID;
	//保存不同格式的(.jpg,bmp,png)的图片需要不同的CLSID, imageFormat为用户期望保存的图片格式
	if (_T("jpg") == imageFormat.MakeLower() ){
      GetEncoderClsid(_T("image/jpeg"), &clsID);
	}else if ( _T("bmp") == imageFormat.MakeLower() ){
      GetEncoderClsid(_T("image/bmp"), &clsID);
	}else if ( _T("png") == imageFormat.MakeLower() ){
     GetEncoderClsid(_T("image/png"), &clsID);
	}

	//保存为图片，strFN为图片保存的路径和文件名
	bitmap.Save( strFN, &clsID, NULL );
	::SelectObject( hmemDC, hOld );
	::DeleteObject( hBmp );
	::DeleteDC( hmemDC );
	
}


void CGraphicView::OnFileOpen() 
{
	// TODO: Add your command handler code here
	
}


///////////////////////////////////////////

void CGraphicView::OnDot() 
{
	// TODO: Add your command handler code here
	m_nDrawType=1;
}

void CGraphicView::OnLine() 
{
	// TODO: Add your command handler code here
	m_nDrawType=2;
}

void CGraphicView::OnRectangle() 
{
	// TODO: Add your command handler code here
	m_nDrawType=3;
}


void CGraphicView::OnEllipse() 
{
	// TODO: Add your command handler code here
	m_nDrawType=4;
}


void CGraphicView::OnSector() 
{
	// TODO: Add your command handler code here
	m_nDrawType=5;
}


void CGraphicView::OnPolyline() 
{
	// TODO: Add your command handler code here
	m_nDrawType=6;
}

void CGraphicView::OnSimplebrush() 
{
	// TODO: Add your command handler code here
	m_nDrawType=7;
}

void CGraphicView::OnBitmapbrush() 
{
	// TODO: Add your command handler code here
	m_nDrawType=8;
}

void CGraphicView::OnTransparentbrush() 
{
	// TODO: Add your command handler code here
	m_nDrawType=9;
}

