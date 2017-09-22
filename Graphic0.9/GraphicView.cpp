// GraphicView.cpp : implementation of the CGraphicView class
//

#include "StdAfx.h"
#include "Graphic.h"

#include "GraphicDoc.h"
#include "GraphicView.h"
#include "SettingDlg.h"
#include "RotateDlg.h"
#include "ZoomDlg.h"
#include "ConfirmDlg.h"
#include "TranslateTrans.h"
#include "COLOR_DATA.h"
#include <vector>
#include <cmath>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;

#endif

	using namespace Gdiplus;
	using namespace std;
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
	ON_WM_ERASEBKGND()
	ON_COMMAND(ID_ERASE, OnErase)
	ON_COMMAND(ID_FILLAREA, OnFillarea)
	ON_COMMAND(ID_ROTATE, OnRotate)
	ON_WM_PAINT()
	ON_COMMAND(ID_GRAY, OnGray)
	ON_COMMAND(ID_ALL, OnAll)
	ON_COMMAND(ID_ZOOM, OnZoom)
	ON_COMMAND(ID_TRANSLATE, OnTranslate)
	ON_COMMAND(ID_GAUSS, OnGauss)
	ON_COMMAND(ID_FILE_SAVE, OnFileSave)
	ON_COMMAND(ID_FILE_SAVE_AS, OnFileSaveAs)
	ON_COMMAND(ID_FILE_NEW, OnFileNew)
	ON_COMMAND(IDD_TEXT, OnText)
	ON_WM_LBUTTONDBLCLK()
	ON_WM_CREATE()
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
	m_LineWidth=5;
	m_Color=RGB(50,200,100);
	m_nFILLMODEL=1;
	m_nAngle=0;
	m_nRotateModel=0;
	imagePointX=0;
	imagePointY=0;
	m_TranslateLevel=0;
	m_TranslateVertical=0;
	m_rTrans=1;
	m_cTrans=1;
	isGray=false;
	imageConfirm=false;
	isAll=false;
}


CGraphicView::~CGraphicView()
{
}

void CGraphicView::initial(){
	//initial
	m_nRotateModel=0;
	m_nAngle=0;
	imagePointX = 0;
	imagePointY = 0;
	m_TranslateLevel=0;
	m_TranslateVertical=0;
	m_rTrans=1;
	m_cTrans=1;
	isGray=false;
	imageConfirm=false;
	isAll=false;
}

BOOL CGraphicView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs
	// 固定鼠标指针样式在MoveMouse时不变
    cs.lpszClass = AfxRegisterWndClass(CS_DBLCLKS,NULL,(HBRUSH)GetStockObject(WHITE_BRUSH),NULL);

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CGraphicView drawing


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
//cancel system background erase function
BOOL CGraphicView::OnEraseBkgnd(CDC* pDC) 
{
	// TODO: Add your message handler code here and/or call default
	
	// nothing
	return CView::OnEraseBkgnd(pDC);
	//return true;
}

int CGraphicView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;
	/*
    TEXTMETRIC tm;  
    MemDC.GetTextMetrics(&tm);//获取当前字符高度和宽度值，来矫正插入光标的大小  
    CreateSolidCaret(tm.tmAveCharWidth/8,tm.tmHeight);//创建插入符  
    ShowCaret();//显示插入符  
  
    SetTimer(1,50, NULL);//设置定时器消息，1表示定时器标识符，50表示50ms产生一个消息，NULL指的是进入消息队列产生WM_TIMER消息  

	*/
	// TODO: Add your specialized creation code here

	return 0;
}

inline void CGraphicView::NormalTrans(){
//有缺陷
/*
	CDC* pDC = GetDC();
	Graphics graphics(pDC->GetSafeHdc());

	pDC->BitBlt(0, 0 ,nWidth,nHeight,&MemDC,0,0,SRCCOPY);
	//平移
	graphics.TranslateTransform((float)m_TranslateLevel, (float)m_TranslateVertical); 
	//缩放
	graphics.ScaleTransform(m_rTrans,m_cTrans);
  	//源点移动到旋转中心
	graphics.TranslateTransform(1.0f*(imagePointX+m_ZoomRow/2),1.0f*(imagePointY+m_ZoomColumn/2));
	//旋转
	if(!m_nRotateModel)graphics.RotateTransform(1.0f*m_nAngle); 
	else graphics.RotateTransform(1.0f*(1080-m_nAngle));
	//还原源点	
	graphics.TranslateTransform(1.0f*(0-(imagePointX+m_ZoomRow/2)), 1.0f*(0-(imagePointY+m_ZoomColumn/2)));

	ReleaseDC(pDC);
*/
}

void CGraphicView::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	CClientDC dc(this);
	CBrush brush(m_Color);
	CGraphicDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
    CDC *pDC=GetDC();
    CRect rect;
    this->GetClientRect(&rect);

	m_ptOrigin=point;
	m_bDraw=true;
    
	
	//获取屏幕DC
	HDC hDC=::GetDC(NULL);
	//获取当前点的RGB值
	COLORREF clr=::GetPixel(hDC, point.x, point.y); 
	Gdiplus::Graphics graphics(MemDC.GetSafeHdc());

	//改变鼠标指针形状
	HCURSOR hCur;
	switch(m_nDrawType){
	case 1://点
		MemDC.SetPixel(point,m_Color); 
		pDC->BitBlt(0, 0 ,nWidth,nHeight,&MemDC,0,0,SRCCOPY);
		break;   
	case 2://直线
	case 3://矩形
    case 4://椭圆
    case 5://扇形
		hCur=LoadCursor(NULL,IDC_CROSS);
		::SetCursor(hCur);
		break;
	case 10://橡皮擦
		hCur=LoadCursor(NULL,IDC_NO);
		::SetCursor(hCur);
	    break;
	case 11:
		//这个填充能用。。就是有点卡
		if(clr!=m_Color){
			MemDC.SelectObject(brush);									
			ExtFloodFill(MemDC,point.x,point.y,clr,FLOODFILLSURFACE);	
			pDC->BitBlt(0, 0 ,nWidth,nHeight,&MemDC,0,0,SRCCOPY);
		}
		break;
	/*fail
	case 12://rotate

		if (!pDoc) return;
		//using GDI+
		CRect rect;
		this->GetClientRect(&rect);
		Bitmap bm(rect.Width(),rect.Height(),PixelFormat24bppRGB);
		bm.RotateFlip(RotateFlipType(Rotate90FlipNone));
		Graphics myg2(dc);
		CDC *pDC=GetDC();
		CDC dcCompatible;
        dcCompatible.CreateCompatibleDC( pDC );  // 创建与当前DC（pDC）兼容的DC
        dcCompatible.SelectObject( &bm );
		pDC->FillSolidRect(&rect,RGB(0,0,0));
		pDC->BitBlt( 0, 0, rect.Width(), rect.Height(), &dcCompatible, 0, 0, SRCCOPY );


		break;
	*/
	}


	ReleaseDC(pDC);
	CView::OnLButtonDown(nFlags, point);
}

void CGraphicView::OnLButtonUp(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	//创建并获得设备描述
	CClientDC dc(this);
	CDC* pDC=GetDC();
    CRect rect;
    this->GetClientRect(&rect);

	m_bDraw=false;

	//恢复鼠标指针形状
	HCURSOR hCur=LoadCursor(NULL,IDC_ARROW);
    ::SetCursor(hCur);

	CBrush brush;
	CBrush *pOldBrush;

	//实心/空心
	if(m_nFILLMODEL==1){
	    CBrush *pBrush=CBrush::FromHandle((HBRUSH)GetStockObject(NULL_BRUSH));
       //将空画刷选入设备描述表
	    pOldBrush= MemDC.SelectObject(pBrush);
	}else{
		brush.CreateSolidBrush(m_Color);
		pOldBrush=MemDC.SelectObject(&brush);
	}

	
    //画出线宽大于1的实线/虚线/点线/点划线/双点划线
	LOGBRUSH logBrush;  
	logBrush.lbStyle = BS_SOLID;  
	logBrush.lbColor = m_Color;  
	//创建实线画笔
	CPen pen1(m_LineStyle,m_LineWidth,m_Color);
	//创建虚线画笔
	CPen pen2(PS_DASH | PS_GEOMETRIC | PS_ENDCAP_ROUND,m_LineWidth,&logBrush);
	//创建点线画笔
	CPen pen3(PS_DOT | PS_GEOMETRIC | PS_ENDCAP_ROUND,m_LineWidth,&logBrush);
	//创建点划线画笔
	CPen pen4(PS_DASHDOT | PS_GEOMETRIC | PS_ENDCAP_ROUND,m_LineWidth,&logBrush);
	//创建双点划线画笔
	CPen pen5(PS_DASHDOTDOT | PS_GEOMETRIC | PS_ENDCAP_ROUND,m_LineWidth,&logBrush);
	MemDC.SelectObject(&pen1);
	if(m_LineStyle==1)MemDC.SelectObject(&pen2);		//选择画笔
	else if(m_LineStyle==2)MemDC.SelectObject(&pen3);
	else if(m_LineStyle==3)MemDC.SelectObject(&pen4);
	else if(m_LineStyle!=0)MemDC.SelectObject(&pen5);		//选择画笔
	

	switch (m_nDrawType){
	  case 2:/*绘制直线*/
		  MemDC.MoveTo(m_ptOrigin);
		  /*调用MoveTo函数移动到原点*/
		  MemDC.LineTo(point);
		  /*调用LineTo函数绘制到终点*/
		  break;
	  case 3:/*绘制矩形*/
		  MemDC.Rectangle(CRect(m_ptOrigin,point));
		  //恢复先前的画刷
		  MemDC.SelectObject(pOldBrush);
		  break;
	  case 4:/*绘制椭圆*/
		  MemDC.Ellipse(CRect(m_ptOrigin,point));
		  //恢复先前的画刷
		  MemDC.SelectObject(pOldBrush);
		  break;
	}

	//-_-  case中无法声明变量
	if(m_nDrawType==7){
		//Simplebrush
		CBrush brush(m_Color);
	    //利用画刷填充鼠标拖曳过程中形成的矩形区域 
        MemDC.FillRect(CRect(m_ptOrigin,point),&brush);
	}
	if(m_nDrawType==8){
		//Bitmapbrush
		//创建位图对象
		CBitmap bitmap;
		//加载位图资源
		bitmap.LoadBitmap(IDB_BITMAP1);
		//创建位图画刷
		CBrush brush(&bitmap);
		//利用红色画刷填充鼠标拖曳过程中形成的矩形区域
		MemDC.FillRect(CRect(m_ptOrigin,point),&brush);
	}
	if(m_nDrawType==9){
		//Transparentbrush
		//创建一个空画刷
		CBrush *pBrush=CBrush::FromHandle((HBRUSH)GetStockObject(NULL_BRUSH));
		//将空画刷选入设备描述表
		CBrush *pOldBrush = MemDC.SelectObject(pBrush);
		//绘制一个矩形
		MemDC.Rectangle(CRect(m_ptOrigin,point));
		//恢复先前的画刷
		MemDC.SelectObject(pOldBrush);
	}
	pDC->BitBlt(0, 0 ,nWidth,nHeight,&MemDC,0,0,SRCCOPY);
////??
	OnPrepareDC(&MemDC);
	MemDC.DPtoLP(&m_ptOrigin);
	MemDC.DPtoLP(&point);


	ReleaseDC(pDC);
	CView::OnLButtonUp(nFlags, point);
}

void CGraphicView::OnMouseMove(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	//创建并获得设备描述
	CClientDC dc(this);
	CDC *pDC=GetDC();
    CRect rect;
    this->GetClientRect(&rect);

	CBrush brush;
	CBrush *pOldBrush;

	//实心/空心
	if(m_nFILLMODEL==1){
	    CBrush *pBrush=CBrush::FromHandle((HBRUSH)GetStockObject(NULL_BRUSH));
       //将空画刷选入设备描述表
	    pOldBrush=pDC->SelectObject(pBrush);
	}else{
		brush.CreateSolidBrush(m_Color);
		pOldBrush=pDC->SelectObject(&brush);
	}

    //画出线宽大于1的实线/虚线/点线/点划线/双点划线
	LOGBRUSH logBrush;  
	logBrush.lbStyle = BS_SOLID;  
	logBrush.lbColor = m_Color;  
	//创建实线画笔
	CPen pen1(m_LineStyle,m_LineWidth,m_Color);
	//创建虚线画笔
	CPen pen2(PS_DASH | PS_GEOMETRIC | PS_ENDCAP_ROUND,m_LineWidth,&logBrush);
	//创建点线画笔
	CPen pen3(PS_DOT | PS_GEOMETRIC | PS_ENDCAP_ROUND,m_LineWidth,&logBrush);
	//创建点划线画笔
	CPen pen4(PS_DASHDOT | PS_GEOMETRIC | PS_ENDCAP_ROUND,m_LineWidth,&logBrush);
	//创建双点划线画笔
	CPen pen5(PS_DASHDOTDOT | PS_GEOMETRIC | PS_ENDCAP_ROUND,m_LineWidth,&logBrush);
	MemDC.SelectObject(&pen1);pDC->SelectObject(&pen1);
	if(m_LineStyle==1)MemDC.SelectObject(&pen2),pDC->SelectObject(&pen2);
	else if(m_LineStyle==2)MemDC.SelectObject(&pen3),pDC->SelectObject(&pen3);
	else if(m_LineStyle==3)MemDC.SelectObject(&pen4),pDC->SelectObject(&pen4);
	else if(m_LineStyle!=0)MemDC.SelectObject(&pen5),pDC->SelectObject(&pen5);	

	if(m_bDraw==true){
		switch(m_nDrawType){
			case 2://Line
				pDC->BitBlt(0, 0 ,nWidth,nHeight,&MemDC,0,0,SRCCOPY);
				pDC->MoveTo(m_ptOrigin);  
				pDC->LineTo(point);  
				break;
			case 3://Rectangle
				pDC->BitBlt(0, 0 ,nWidth,nHeight,&MemDC,0,0,SRCCOPY);
				pDC->Rectangle(CRect(m_ptOrigin,point));
				//恢复先前的画刷
				pDC->SelectObject(pOldBrush);
				break;
			case 4:
			    pDC->BitBlt(0, 0 ,nWidth,nHeight,&MemDC,0,0,SRCCOPY);
				pDC->Ellipse(CRect(m_ptOrigin,point));
				//恢复先前的画刷
				pDC->SelectObject(pOldBrush);
				break;
			case 5://SECTOR
				MemDC.MoveTo(m_ptOrigin);                  
				MemDC.LineTo(point);
			    pDC->BitBlt(0, 0 ,nWidth,nHeight,&MemDC,0,0,SRCCOPY);
				break;
			case 6://Polyline
				MemDC.MoveTo(m_ptOrigin);                  
				MemDC.LineTo(point);
				//修改线段的起点        
				m_ptOrigin=point;
				pDC->BitBlt(0, 0 ,nWidth,nHeight,&MemDC,0,0,SRCCOPY); 
				break;
			case 10://erase
				CBrush brush(RGB(255,255,255));
				CPoint pt1;
				CPoint pt2;
				pt1.x=point.x-m_LineWidth*2;
				pt1.y=point.y-m_LineWidth*2;
				pt2.x=point.x+m_LineWidth*2;
				pt2.y=point.y+m_LineWidth*2;
				MemDC.FillRect(CRect(pt1,pt2),&brush);
				pDC->BitBlt(0, 0 ,nWidth,nHeight,&MemDC,0,0,SRCCOPY);  
				break;
		}

		//-_-  case中无法声明变量
		if(m_nDrawType==7){
			//Simplebrush
			pDC->BitBlt(0, 0 ,nWidth,nHeight,&MemDC,0,0,SRCCOPY);
			CBrush brush(m_Color);
			//利用画刷填充鼠标拖曳过程中形成的矩形区域 
			pDC->FillRect(CRect(m_ptOrigin,point),&brush);
		}
		if(m_nDrawType==8){
			//Bitmapbrush
			pDC->BitBlt(0, 0 ,nWidth,nHeight,&MemDC,0,0,SRCCOPY);
			//创建位图对象
			CBitmap bitmap;
			//加载位图资源
			bitmap.LoadBitmap(IDB_BITMAP1);
			//创建位图画刷
			CBrush brush(&bitmap);
			//利用红色画刷填充鼠标拖曳过程中形成的矩形区域
			pDC->FillRect(CRect(m_ptOrigin,point),&brush);
		}
		if(m_nDrawType==9){
			//Transparentbrush
			pDC->BitBlt(0, 0 ,nWidth,nHeight,&MemDC,0,0,SRCCOPY);
			//创建一个空画刷
			CBrush *pBrush=CBrush::FromHandle((HBRUSH)GetStockObject(NULL_BRUSH));
			//将空画刷选入设备描述表
			CBrush *pOldBrush = pDC->SelectObject(pBrush);
			//绘制一个矩形
			pDC->Rectangle(CRect(m_ptOrigin,point));
			//恢复先前的画刷
			pDC->SelectObject(pOldBrush);
		}
	}
	//恢复设备描述
	CView::OnMouseMove(nFlags, point);
	ReleaseDC(pDC);
}


void CGraphicView::OnSetting(){
	//TODO: Add your command handler code here
	SettingDlg dlg;
	dlg.m_LineWidth=m_LineWidth;
	dlg.m_LineStyle=m_LineStyle;
	dlg.m_nFILLMODEL=m_nFILLMODEL;
	if(IDOK==dlg.DoModal()){
		m_LineWidth=dlg.m_LineWidth;
		m_LineStyle=dlg.m_LineStyle;
		m_nFILLMODEL=dlg.m_nFILLMODEL;
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

void CGraphicView::OnAll() 
{
	// TODO: Add your command handler code here
	if(imageConfirm){
		AfxMessageBox("图像已固定！");
		return;
	}
    CDC* pDC = GetDC();
	Graphics graphics(pDC->GetSafeHdc());
    CRect rect;
    this->GetClientRect(&rect);

	CGraphicDoc* pDoc = GetDocument();//得到文档指针,注意,文档的命名是与工程名有关的!!不同的程序不一样.
	ASSERT_VALID(pDoc); 
	if(pDoc->flagOpen==0)
	{
	  AfxMessageBox("请先打开图片!");
	}else
	{
	  isAll=true;
	  pDC->BitBlt(0, 0 ,nWidth,nHeight,&MemDC,0,0,SRCCOPY);

	  graphics.DrawImage(m_pImg, 0, 0, rect.Width(),rect.Height()); // 绘制图像
	}

	ReleaseDC(pDC);
}

void CGraphicView::OnZoom() 
{
	// TODO: Add your command handler code here
	if(imageConfirm){
		AfxMessageBox("图像已固定！");
		return;
	}
	CDC* pDC = GetDC();
	Graphics graphics(pDC->GetSafeHdc());
    CRect rect;
    this->GetClientRect(&rect);

	CGraphicDoc* pDoc = GetDocument();//得到文档指针,注意,文档的命名是与工程名有关的!!不同的程序不一样.
	ASSERT_VALID(pDoc);

	if(pDoc->flagOpen==0)
	{
	  AfxMessageBox("请先打开图片!");
    }
	else
	{
	  CZoomDlg dlg;
	  dlg.m_ZoomRow=m_ZoomRow;
	  dlg.m_ZoomColumn=m_ZoomColumn;
	  if(IDOK==dlg.DoModal()){
		isAll=false;
		m_rTrans=(float)dlg.m_ZoomRow/(float)m_ZoomRow;
	    m_cTrans=(float)dlg.m_ZoomColumn/(float)m_ZoomColumn;

		NormalTrans();
		pDC->BitBlt(0, 0 ,nWidth,nHeight,&MemDC,0,0,SRCCOPY);
		//平移
		graphics.TranslateTransform((float)m_TranslateLevel, (float)m_TranslateVertical); 
		//缩放
		graphics.ScaleTransform(m_rTrans,m_cTrans);
  		//源点移动到旋转中心
		graphics.TranslateTransform(1.0f*(imagePointX+m_ZoomRow/2),1.0f*(imagePointY+m_ZoomColumn/2));
		//旋转
		if(!m_nRotateModel)graphics.RotateTransform(1.0f*m_nAngle); 
		else graphics.RotateTransform(1.0f*(1080-m_nAngle));
		//还原源点	
		graphics.TranslateTransform(1.0f*(0-(imagePointX+m_ZoomRow/2)), 1.0f*(0-(imagePointY+m_ZoomColumn/2)));

		graphics.DrawImage(m_pImg, imagePointX,imagePointY); // 绘制图像
	
	  }
      
	}
	ReleaseDC(pDC);
}

void CGraphicView::OnRotate() 
{
	// TODO: Add your command handler code here
	if(imageConfirm){
		AfxMessageBox("图像已固定！");
		return;
	}
	CDC* pDC = GetDC();
	Graphics graphics(pDC->GetSafeHdc());

    CRect rect;
    this->GetClientRect(&rect);

	CGraphicDoc* pDoc = GetDocument();//得到文档指针,注意,文档的命名是与工程名有关的!!不同的程序不一样.
	ASSERT_VALID(pDoc);

	if(pDoc->flagOpen==0)
	{
	  AfxMessageBox("请先打开图片!");
    }
	else
	{
	  CRotateDlg dlg;
	  dlg.m_nRotateModel=m_nRotateModel;
  	  dlg.m_nAngle=0;
	  if(IDOK==dlg.DoModal()){
		isAll=false;
		m_nRotateModel=dlg.m_nRotateModel;
		if(m_nRotateModel==0)m_nAngle+=dlg.m_nAngle;
		else m_nAngle-=dlg.m_nAngle;

		NormalTrans();
		pDC->BitBlt(0, 0 ,nWidth,nHeight,&MemDC,0,0,SRCCOPY);
		//平移
		graphics.TranslateTransform((float)m_TranslateLevel, (float)m_TranslateVertical); 
		//缩放
		graphics.ScaleTransform(m_rTrans,m_cTrans);
  		//源点移动到旋转中心
		graphics.TranslateTransform(1.0f*(imagePointX+m_ZoomRow/2),1.0f*(imagePointY+m_ZoomColumn/2));
		//旋转
		if(!m_nRotateModel)graphics.RotateTransform(1.0f*m_nAngle); 
		else graphics.RotateTransform(1.0f*(1080-m_nAngle));
		//还原源点	
		graphics.TranslateTransform(1.0f*(0-(imagePointX+m_ZoomRow/2)), 1.0f*(0-(imagePointY+m_ZoomColumn/2)));


		//在某个起点显示图像
		graphics.DrawImage(m_pImg, imagePointX, imagePointY);

	  }
	}
	ReleaseDC(pDC);
}

void CGraphicView::OnTranslate() 
{
	// TODO: Add your command handler code here
	if(imageConfirm){
		AfxMessageBox("图像已固定！");
		return;
	}
	CDC* pDC = GetDC();
	Graphics graphics(pDC->GetSafeHdc());
    CRect rect;
    this->GetClientRect(&rect);

	CGraphicDoc* pDoc = GetDocument();//得到文档指针,注意,文档的命名是与工程名有关的!!不同的程序不一样.
	ASSERT_VALID(pDoc);

	if(pDoc->flagOpen==0)
	{
	  AfxMessageBox("请先打开图片!");
    }
	else
	{
	  CTranslateTrans dlg;
	  dlg.m_TranslateLevel=0;
	  dlg.m_TranslateVertical=0;
	  if(IDOK==dlg.DoModal()){
		isAll=false;
		if(dlg.m_signal1==0)m_TranslateLevel+=dlg.m_TranslateLevel;
		else m_TranslateLevel-=dlg.m_TranslateLevel;
		if(dlg.m_signal2==0)m_TranslateVertical+=dlg.m_TranslateVertical;
		else m_TranslateVertical-=dlg.m_TranslateVertical;
		
		NormalTrans();
		pDC->BitBlt(0, 0 ,nWidth,nHeight,&MemDC,0,0,SRCCOPY);
		//平移
		graphics.TranslateTransform((float)m_TranslateLevel, (float)m_TranslateVertical); 
		//缩放
		graphics.ScaleTransform(m_rTrans,m_cTrans);
  		//源点移动到旋转中心
		graphics.TranslateTransform(1.0f*(imagePointX+m_ZoomRow/2),1.0f*(imagePointY+m_ZoomColumn/2));
		//旋转
		if(!m_nRotateModel)graphics.RotateTransform(1.0f*m_nAngle); 
		else graphics.RotateTransform(1.0f*(1080-m_nAngle));
		//还原源点	
		graphics.TranslateTransform(1.0f*(0-(imagePointX+m_ZoomRow/2)), 1.0f*(0-(imagePointY+m_ZoomColumn/2)));

		graphics.DrawImage(m_pImg, imagePointX,imagePointY); // 绘制图像
	
	  }
	}
	ReleaseDC(pDC);
}



void CGraphicView::OnGray() 
{
	// TODO: Add your command handler code here
	if(imageConfirm){
		AfxMessageBox("图像已固定！");
		return;
	}
	CDC *pDC=GetDC();
	Graphics graphics(pDC->GetSafeHdc());
    CRect rect;
    this->GetClientRect(&rect);

	CGraphicDoc* pDoc = GetDocument();//得到文档指针,注意,文档的命名是与工程名有关的!!不同的程序不一样.
	ASSERT_VALID(pDoc);

	if(pDoc->flagOpen==0)
	{
	  AfxMessageBox("请先打开图片!");
    }
	else
	{
	  isAll=false;
	  isGray=true;
	  
	  NormalTrans();
	  pDC->BitBlt(0, 0 ,nWidth,nHeight,&MemDC,0,0,SRCCOPY);
	  //平移
	  graphics.TranslateTransform((float)m_TranslateLevel, (float)m_TranslateVertical); 
	  //缩放
	  graphics.ScaleTransform(m_rTrans,m_cTrans);
  	  //源点移动到旋转中心
	  graphics.TranslateTransform(1.0f*(imagePointX+m_ZoomRow/2),1.0f*(imagePointY+m_ZoomColumn/2));
	  //旋转
	  if(!m_nRotateModel)graphics.RotateTransform(1.0f*m_nAngle); 
	  else graphics.RotateTransform(1.0f*(1080-m_nAngle));
	  //还原源点	
	  graphics.TranslateTransform(1.0f*(0-(imagePointX+m_ZoomRow/2)), 1.0f*(0-(imagePointY+m_ZoomColumn/2)));

	  ColorMatrix colorMatrix=
	  {
		 0.299f,0.299f,0.299f,0,0,
		0.587f,0.587f,0.587f,0,0,
		0.114f,0.114f,0.114f,0,0,
		0,0,0,1,0,
		0,0,0,0,1
	  };

	  ImageAttributes attr;
	  attr.SetColorMatrix(&colorMatrix);
	
	  Rect destRect(imagePointX,imagePointY,m_pImg->GetWidth(),m_pImg->GetHeight());
	  graphics.DrawImage(m_pImg, destRect, 0,0,m_pImg->GetWidth(),m_pImg->GetHeight(),UnitPixel,&attr);
	}

	ReleaseDC(pDC);
}


//高斯平滑  
void CGraphicView::OnGauss()   
{  
	// TODO: Add your command handler code here
	CDC *pDC=GetDC();
	Graphics graphics(MemDC.GetSafeHdc());
    CRect rect;
    this->GetClientRect(&rect);
	//获取屏幕DC
	HDC hDC=::GetDC(NULL);

	COLORREF *pCopy;
	pCopy=new COLORREF[rect.Width()*rect.Height()];
	int nRadius=2;
	for(int ny=0;ny<rect.Width();++ny)
      for (int nx=0;nx<rect.Height();++nx){  
		std::vector<COLOR_DATA> cdList;  
        cdList.reserve(200);  
        COLOR_DATA cd;  
        double dTotal=0;  
        for (int m=nx-nRadius; m<=nx+nRadius;++m){
          if (m<0 || m>=nWidth ) continue;  
            for (int n=ny-nRadius;n<=ny+nRadius;++n){  
                    if (n<0 || n>=nHeight ) continue;  
                    cd.dDistance=GAUSS_FUN(sqrt((double)((m-nx)*(m-nx)+(n-ny)*(n-ny))), sigma);  
                    dTotal+=cd.dDistance;
					cd.dwColor=::GetPixel(hDC, nx, ny); 
                    cdList.push_back(cd);  
			}  
		}
         if ( cdList.size()>0 )  
         {//这里来计算整个邻域内所有像素点的加权平均值  
	    	std::vector<COLOR_DATA>::const_iterator itor=cdList.begin();  
            double r=0, g=0, b=0;  
            for ( ; itor!=cdList.end(); ++itor )   
            {  
               double dRate=itor->dDistance/dTotal;//距离中心点越远，权值越小  
               r+=GetRValue(itor->dwColor)*dRate;  
               g+=GetGValue(itor->dwColor)*dRate;  
               b+=GetBValue(itor->dwColor)*dRate;  
            }  
            *(pCopy+nx*rect.Width()+ny)=RGB((int)r, (int)g, (int)b);  
         }  
	  }
    for(int y=0;y<rect.Width();++y)
      for (int x=0;x<rect.Height();++x)
	    pDC->SetPixel(x,y,*(pCopy+x*rect.Width()+y));
    
    delete[] pCopy;
	ReleaseDC(pDC);
}

///////////////////////////////////////////
void CGraphicView::imageDraw(){
	CDC* pDC = GetDC();
	Graphics graphics(MemDC.GetSafeHdc());
    CRect rect;
    this->GetClientRect(&rect);

	if(isAll){
	  MemDC.DeleteDC();
      MemBitmap.DeleteObject();
	  nWidth=rect.Width();
	  nHeight=rect.Height();
	  MemBitmap.CreateCompatibleBitmap(pDC,nWidth,nHeight);

	  //随后建立与屏幕显示兼容的内存显示设备
	  MemDC.CreateCompatibleDC(pDC);
	  //下面建立一个与屏幕显示兼容的位图，至于位图的大小嘛，可以用窗口的大小
	  //将位图选入到内存显示设备中
	  //只有选入了位图的内存显示设备才有地方绘图，画到指定的位图上
	  CBitmap *pOldBit=MemDC.SelectObject(&MemBitmap);
	  MemDC.BitBlt(0, 0 ,nWidth,nHeight,pDC,0,0,SRCCOPY);

	  ReleaseDC(pDC);
	  return;
	}
	NormalTrans();
	pDC->BitBlt(0, 0 ,nWidth,nHeight,&MemDC,0,0,SRCCOPY);
	//平移
	graphics.TranslateTransform((float)m_TranslateLevel, (float)m_TranslateVertical); 
	//缩放
	graphics.ScaleTransform(m_rTrans,m_cTrans);
  	//源点移动到旋转中心
	graphics.TranslateTransform(1.0f*(imagePointX+m_ZoomRow/2),1.0f*(imagePointY+m_ZoomColumn/2));
	//旋转
	if(!m_nRotateModel)graphics.RotateTransform(1.0f*m_nAngle); 
	else graphics.RotateTransform(1.0f*(1080-m_nAngle));
	//还原源点	
	graphics.TranslateTransform(1.0f*(0-(imagePointX+m_ZoomRow/2)), 1.0f*(0-(imagePointY+m_ZoomColumn/2)));

	if(isGray){
	  ColorMatrix colorMatrix=
	  {
		 0.299f,0.299f,0.299f,0,0,
		0.587f,0.587f,0.587f,0,0,
		0.114f,0.114f,0.114f,0,0,
		0,0,0,1,0,
		0,0,0,0,1
	  };

	  ImageAttributes attr;
	  attr.SetColorMatrix(&colorMatrix);
	
	  Rect destRect(imagePointX,imagePointY,m_pImg->GetWidth(),m_pImg->GetHeight());
	  graphics.DrawImage(m_pImg, destRect, 0,0,m_pImg->GetWidth(),m_pImg->GetHeight(),UnitPixel,&attr);
	}

	
	pDC->BitBlt(0, 0 ,nWidth,nHeight,&MemDC,0,0,SRCCOPY);

	ReleaseDC(pDC);
}

void CGraphicView::imageConfirmnation(){
	CGraphicDoc* pDoc = GetDocument();//得到文档指针,注意,文档的命名是与工程名有关的!!不同的程序不一样.
	ASSERT_VALID(pDoc);
	if(!imageConfirm&&pDoc->flagOpen!=0){
		CConfirmDlg dlg;
		if(dlg.DoModal()==IDOK){
			imageConfirm=true;
			imageDraw();
		}
	}
}

void CGraphicView::OnDot() 
{
	// TODO: Add your command handler code here
	imageConfirmnation();

	m_nDrawType=1;
}

void CGraphicView::OnLine() 
{
	// TODO: Add your command handler code here
	imageConfirmnation();

	m_nDrawType=2;
}

void CGraphicView::OnRectangle() 
{
	// TODO: Add your command handler code here
	imageConfirmnation();

	m_nDrawType=3;
}


void CGraphicView::OnEllipse() 
{
	// TODO: Add your command handler code here
	imageConfirmnation();

	m_nDrawType=4;
}


void CGraphicView::OnSector() 
{
	// TODO: Add your command handler code here
	imageConfirmnation();

	m_nDrawType=5;
}


void CGraphicView::OnPolyline() 
{
	// TODO: Add your command handler code here
	imageConfirmnation();

	m_nDrawType=6;
}

void CGraphicView::OnSimplebrush() 
{
	// TODO: Add your command handler code here
	imageConfirmnation();

	m_nDrawType=7;
}

void CGraphicView::OnBitmapbrush() 
{
	// TODO: Add your command handler code here
	imageConfirmnation();

	m_nDrawType=8;
}

void CGraphicView::OnTransparentbrush() 
{
	// TODO: Add your command handler code here
	imageConfirmnation();
	
	m_nDrawType=9;
}

void CGraphicView::OnErase() 
{
	// TODO: Add your command handler code here
	imageConfirmnation();

	m_nDrawType=10;
}

void CGraphicView::OnFillarea() 
{
	// TODO: Add your command handler code here
	imageConfirmnation();

	m_nDrawType=11;
}

void CGraphicView::OnText() 
{
	// TODO: Add your command handler code here




/*	CFontDialog dlg; 
    if(IDOK==dlg.DoModal()) 
    { 
		CDC* pDC=GetDC();
        //if(m_font.m_hObject) 
            //m_font.DeleteObject(); 
        m_font.CreateFontIndirect(dlg.m_cf.lpLogFont); 
        m_strFontName=dlg.m_cf.lpLogFont->lfFaceName; 
        CFont *pOldFont=pDC->SelectObject(&m_font);
        pDC->TextOut(0,0,m_strFontName); 
        pDC->SelectObject(pOldFont); 
		m_font.DeleteObject();
		ReleaseDC(pDC);
    }*/
}

//////////////////////////////////////

void CGraphicView::OnDraw(CDC* pDC)
{
	
	CGraphicDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
	CRect rect;
	this->GetClientRect(&rect);

	/*
	//重要!!!!及时释放CBitmap (还得先释放CDC)
	if (MemBitmap.m_hObject != NULL){
	   MemDC.DeleteDC();
       MemBitmap.DeleteObject();
	}*/
    if (MemBitmap.m_hObject == NULL){
		nWidth=rect.Width();
		nHeight=rect.Height();
		MemBitmap.CreateCompatibleBitmap(pDC,nWidth,nHeight);

		//随后建立与屏幕显示兼容的内存显示设备
		MemDC.CreateCompatibleDC(pDC);
		//下面建立一个与屏幕显示兼容的位图，至于位图的大小嘛，可以用窗口的大小
		//将位图选入到内存显示设备中
		//只有选入了位图的内存显示设备才有地方绘图，画到指定的位图上
		CBitmap *pOldBit=MemDC.SelectObject(&MemBitmap);
        MemDC.FillSolidRect(0,0,rect.Width(),rect.Height(),RGB(255,255,255));
	}else{
		pDC->BitBlt(0, 0 ,nWidth,nHeight,&MemDC,0,0,SRCCOPY); 
		if(rect.Width()>nWidth&&rect.Height()>nHeight){
			MemDC.DeleteDC();
			MemBitmap.DeleteObject();
			nWidth=rect.Width();
			nHeight=rect.Height();
			MemBitmap.CreateCompatibleBitmap(pDC,nWidth,nHeight);

			//随后建立与屏幕显示兼容的内存显示设备
			MemDC.CreateCompatibleDC(pDC);
			//下面建立一个与屏幕显示兼容的位图，至于位图的大小嘛，可以用窗口的大小
			//将位图选入到内存显示设备中
			//只有选入了位图的内存显示设备才有地方绘图，画到指定的位图上
			CBitmap *pOldBit=MemDC.SelectObject(&MemBitmap);
			MemDC.BitBlt(0, 0 ,nWidth,nHeight, pDC, 0, 0, SRCCOPY); 
		}
	}
//    MemDC.MoveTo(0,0);
//    MemDC.LineTo(100,100);


//双缓冲实现技术
/*C++ code*/
//	RECT rc;
//	GetClientRect(&rc);
//	Bitmap bmp(int(rc.right),int(rc.bottom));

//	Graphics bmpGraphics(&bmp);
//	bmpGraphics.SetSmoothingMode(SmoothingModeAntiAlias);

/*Drawing on DC*/
//	Graphics graphics(pDC->m_hDC);
/*Important! Create a CacheBitmap object for quick drawing*/
//	CachedBitmap cachedBmp(&bmp,&graphics);
//	graphics.DrawCachedBitmap(&cachedBmp,0,0);






    //GDI+使用尝试
//	Graphics graphics(MemDC.GetSafeHdc());
//	Pen pen(Color(255, 0, 255));
//	graphics.DrawLine(&pen, 0, 0, 200, 100);

}

//OnPaint 与OnDraw高度相关  先调用 OnPaint 再调用 OnDraw
void CGraphicView::OnPaint() 
{
	CPaintDC dc(this); // device context for painting

	
///////////////////////////////////////////////////////////////////////////////
//加载图片

	CGraphicDoc* pDoc = GetDocument();//得到文档指针,注意,文档的命名是与工程名有关的!!不同的程序不一样.
	ASSERT_VALID(pDoc); 


	//手动清空
	CDC* pDC=GetDC();
    CRect rect;
    this->GetClientRect(&rect);
	pDC->FillSolidRect(&rect,RGB(255,255,255));
	OnDraw(&dc); //调用了OnDraw   VC6.0

	//是否已打开某个BMP文件
	if(pDoc->flagOpen==1)
	{	
		initial();
		Load((LPCTSTR)(pDoc->FilePath));
		//这个函数显示DIB
		/*SetDIBitsToDevice(dc.m_hDC,  //DIB将输出的设备描述表
			imagePointX,               //设备描述表中位图输出起始逻辑x地址
			imagePointY,               //设备描述表中位图输出起始逻辑x地址 
			pDoc->bi.biWidth,  //DIB的宽度
			pDoc->bi.biHeight, //DIB的高度
			0,                 //DIB开始读取输出的像素数据的x位置
			0,                 //DIB开始读取输出的像素数据的y位置
			0,                 //DIB中像素的水平行号,它对应lpBits内存缓冲区第一行数据
			pDoc->bi.biHeight, //DIB的行数，对应包含在由lpBits所指内存缓冲区中的数据
			pDoc->lpbuf,       //包含像素数据的内存缓冲区的指针
			pDoc->pbi,        //指向初始化了的BITMAPINFO数据结构的指针，描述了位图的大小和色彩数据
			DIB_RGB_COLORS);   //指定是显示的颜色*/
      Graphics graphics(MemDC.GetSafeHdc());

	  m_ZoomRow=m_pImg->GetWidth();
	  m_ZoomColumn=m_pImg->GetHeight();

	  graphics.DrawImage(m_pImg, imagePointX, imagePointY);
	  pDC->BitBlt(0, 0 ,nWidth,nHeight,&MemDC,0,0,SRCCOPY);


	  pDoc->flagOpen=2;
	  //Invalidate(false);
	  return;
	}
	if(pDoc->flagOpen==2){
      Graphics graphics(pDC->GetSafeHdc());

	  pDC->BitBlt(0, 0 ,nWidth,nHeight,&MemDC,0,0,SRCCOPY);
	  graphics.DrawImage(m_pImg, imagePointX, imagePointY);
	}
	// Do not call CView::OnPaint() for painting messages
	//WRONG!!
	//Invalidate(true);

	// TODO: Add your message handler code here
	
	// Do not call CView::OnPaint() for painting messages

	
	ReleaseDC(pDC);
}

bool CGraphicView::Load( LPCTSTR pszFileName )
{
	ASSERT( pszFileName != NULL );

	CFile file;
	DWORD dwSize;

        // 打开文件
	if ( !file.Open( pszFileName,
		CFile::modeRead | 
		CFile::shareDenyWrite ) )
	{
		TRACE( _T( "Load (file): Error opening file %s\n" ), pszFileName );
		return FALSE;
	};

        // 依据文件大小分配HGLOBAL内存
	dwSize = (DWORD)file.GetLength();
	HGLOBAL hGlobal = GlobalAlloc( GMEM_MOVEABLE | GMEM_NODISCARD, dwSize );
	if ( !hGlobal )
	{
		TRACE( _T( "Load (file): Error allocating memory\n" ) );
		return FALSE;
	};

	char *pData = reinterpret_cast<char*>(GlobalLock(hGlobal));
	if ( !pData )
	{
		TRACE( _T( "Load (file): Error locking memory\n" ) );
		GlobalFree( hGlobal );
		return FALSE;
	};

        // 将文件内容读到HGLOBAL内存中
	TRY
	{
		file.Read( pData, dwSize );
	}
	CATCH( CFileException, e );                                          
	{
		TRACE( _T( "Load (file): An exception occured while reading the file %s\n"),
			pszFileName );
		GlobalFree( hGlobal );
		e->Delete();
		file.Close();
		return FALSE;
	}
	END_CATCH

	GlobalUnlock( hGlobal );
	file.Close();

        // 利用hGlobal内存中的数据创建stream
	IStream *pStream = NULL;
	if ( CreateStreamOnHGlobal( hGlobal, TRUE, &pStream ) != S_OK )
	{
		return FALSE;
	}

	m_pImg = Image::FromStream( pStream );
     ASSERT( m_pImg != NULL );

	// 要加上这一句，否则由GlobalAlloc得来的hGlobal内存没有被释放，导致内存泄露，由于
	// CreateStreamOnHGlobal第二个參数被设置为TRUE，所以调用pStream->Release()会自己主动
	// 将hGlobal内存（參见msdn对CreateStreamOnHGlobal的说明）
	pStream->Release();
    return true;
}


int CGraphicView::GetEncoderClsid(const WCHAR* format, CLSID* pClsid)
{
   UINT num= 0;
   UINT size= 0;

   ImageCodecInfo* pImageCodecInfo= NULL;

   GetImageEncodersSize(&num, &size);
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
    if(wcscmp(pImageCodecInfo[j].MimeType, format)== 0)
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
	CGraphicDoc* pDoc = GetDocument();//得到文档指针,注意,文档的命名是与工程名有关的!!不同的程序不一样.
	ASSERT_VALID(pDoc);
	if(pDoc->flagOpen==0){
	  OnFileSaveAs();
	  return;
	}
	
	CDC* pDC=GetDC();
    CRect rect;
    this->GetClientRect(&rect);

	MemDC.DeleteDC();
	MemBitmap.DeleteObject();
	nWidth=rect.Width();
	nHeight=rect.Height();
	MemBitmap.CreateCompatibleBitmap(pDC,nWidth,nHeight);

	//随后建立与屏幕显示兼容的内存显示设备
	MemDC.CreateCompatibleDC(pDC);
	//下面建立一个与屏幕显示兼容的位图，至于位图的大小嘛，可以用窗口的大小
	//将位图选入到内存显示设备中
	//只有选入了位图的内存显示设备才有地方绘图，画到指定的位图上
	CBitmap *pOldBit=MemDC.SelectObject(&MemBitmap);
	MemDC.BitBlt(0, 0 ,nWidth,nHeight, pDC, 0, 0, SRCCOPY); 


	CFile file;
	file.Remove(pDoc->FilePath);
	USES_CONVERSION;      //将cstring转化为const wchar*
    WCHAR* pBuf = T2W((LPCTSTR)pDoc->FilePath);
    Bitmap bm((HBITMAP)MemBitmap, NULL);//定义bitmap
    CLSID Clsid; 
	//文件名和path中的有关和下面的无关额
	if(pDoc->FileExt==_T("bmp"))GetEncoderClsid(L"image/bmp", &Clsid); 
	else if(pDoc->FileExt==_T("jpg"))GetEncoderClsid(L"image/jpg", &Clsid); 
	else if(pDoc->FileExt==_T("jpeg"))GetEncoderClsid(L"image/jpeg", &Clsid); 
	else if(pDoc->FileExt==_T("png"))GetEncoderClsid(L"image/png", &Clsid); 
    bm.Save(pBuf, &Clsid, NULL);

	ReleaseDC(pDC);
}

void CGraphicView::OnFileSaveAs() 
{
	// TODO: Add your command handler code here
	LPCTSTR lpszFilter="BMP Files(*.bmp)|*.bmp|JPG Files(*.jpg)|*.bmp|JPEG Files(*.jpeg)|*.jpeg|PNG Files(*.png)|*.bmp|";
	CFileDialog  dlg(FALSE,lpszFilter,NULL,OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT,lpszFilter,NULL);
	
	CDC* pDC=GetDC();
    CRect rect;
    this->GetClientRect(&rect);

	MemDC.DeleteDC();
	MemBitmap.DeleteObject();
	nWidth=rect.Width();
	nHeight=rect.Height();
	MemBitmap.CreateCompatibleBitmap(pDC,nWidth,nHeight);

	//随后建立与屏幕显示兼容的内存显示设备
	MemDC.CreateCompatibleDC(pDC);
	//下面建立一个与屏幕显示兼容的位图，至于位图的大小嘛，可以用窗口的大小
	//将位图选入到内存显示设备中
	//只有选入了位图的内存显示设备才有地方绘图，画到指定的位图上
	CBitmap *pOldBit=MemDC.SelectObject(&MemBitmap);
	MemDC.BitBlt(0, 0 ,nWidth,nHeight, pDC, 0, 0, SRCCOPY); 

	if (dlg.DoModal()!=IDOK)return;
	CString filepath=dlg.GetPathName();
	CString fileExt=dlg.GetFileExt();
	CFile file;
	USES_CONVERSION;      //将cstring转化为const wchar*
    WCHAR* pBuf = T2W((LPCTSTR)filepath);
    Bitmap bm((HBITMAP)MemBitmap, NULL);//定义bitmap
    CLSID Clsid; 
	//文件名和path中的有关和下面的无关额
	if(fileExt==_T("bmp"))GetEncoderClsid(L"image/bmp", &Clsid); 
	else if(fileExt==_T("jpg"))GetEncoderClsid(L"image/jpg", &Clsid); 
	else if(fileExt==_T("jpeg"))GetEncoderClsid(L"image/jpeg", &Clsid); 
	else if(fileExt==_T("png"))GetEncoderClsid(L"image/png", &Clsid); 
    bm.Save(pBuf, &Clsid, NULL);

	ReleaseDC(pDC);
}

void CGraphicView::OnFileNew() 
{
	// TODO: Add your command handler code here
	CGraphicDoc* pDoc = GetDocument();//得到文档指针,注意,文档的命名是与工程名有关的!!不同的程序不一样.
	ASSERT_VALID(pDoc);

	initial();
    CRect rect;
    this->GetClientRect(&rect);
	CDC* pDC=GetDC();

	pDoc->FilePath="";
	pDoc->FileExt="";
	pDoc->flagOpen=0;


	MemDC.DeleteDC();
	MemBitmap.DeleteObject();
	nWidth=rect.Width();
	nHeight=rect.Height();
	MemBitmap.CreateCompatibleBitmap(pDC,nWidth,nHeight);

	//随后建立与屏幕显示兼容的内存显示设备
	MemDC.CreateCompatibleDC(pDC);
	//下面建立一个与屏幕显示兼容的位图，至于位图的大小嘛，可以用窗口的大小
	//将位图选入到内存显示设备中
	//只有选入了位图的内存显示设备才有地方绘图，画到指定的位图上
	CBitmap *pOldBit=MemDC.SelectObject(&MemBitmap);
	MemDC.FillSolidRect(0,0,rect.Width(),rect.Height(),RGB(255,255,255));
	pDC->FillSolidRect(0,0,rect.Width(),rect.Height(),RGB(255,255,255));

	ReleaseDC(pDC);
}
