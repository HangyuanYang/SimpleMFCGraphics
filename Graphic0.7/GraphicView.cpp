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
	ON_WM_ERASEBKGND()
	ON_COMMAND(ID_ERASE, OnErase)
	ON_COMMAND(ID_FILLAREA, OnFillarea)
	ON_COMMAND(ID_ROTATE, OnRotate)
	ON_WM_PAINT()
	ON_COMMAND(ID_IMPORTSAMPLE, OnImportsample)
	ON_WM_LBUTTONDBLCLK()
	ON_COMMAND(ID_GRAY, OnGray)
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
	m_nFILLMODEL=1;
}

CGraphicView::~CGraphicView()
{
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

void CGraphicView::OnDraw(CDC* pDC)
{
	CGraphicDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here

//双缓冲实现技术
/*C++ code*/
//	RECT rc;
//	GetClientRect(&rc);
//	Bitmap bmp(int(rc.right),int(rc.bottom));

//	Graphics bmpGraphics(&bmp);
//	bmpGraphics.SetSmoothingMode(SmoothingModeAntiAlias);

/*Drawing on bitmap*/
//	SolidBrush bkBrush(Color(0,0,0));
//	bmpGraphics.FillRectangle(&bkBrush,0,0,rc.right,rc.bottom);

/*Drawing on DC*/
//	Graphics graphics(pDC->m_hDC);
/*Important! Create a CacheBitmap object for quick drawing*/
//	CachedBitmap cachedBmp(&bmp,&graphics);
//	graphics.DrawCachedBitmap(&cachedBmp,0,0);






    //GDI+使用尝试
//	Graphics graphics(pDC->m_hDC);
//	Pen pen(Color(255, 0, 255));
//	graphics.DrawLine(&pen, 0, 0, 200, 100);
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
	CClientDC dc(this);
	CBrush brush(m_Color);
	CGraphicDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	m_ptOrigin=point;
	m_bDraw=true;

	
	//获取屏幕DC
	HDC hDC=::GetDC(NULL);
	//获取当前点的RGB值
	COLORREF clr=::GetPixel(hDC, point.x, point.y); 
	Gdiplus::Graphics graphics(hDC);
	Pen pen(Color(255, 255, 0, 0));


	//改变鼠标指针形状
	HCURSOR hCur;
	switch(m_nDrawType){
	case 1://点
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
			dc.SelectObject(brush);
			ExtFloodFill(dc,point.x,point.y,clr,FLOODFILLSURFACE);
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
	CView::OnLButtonDown(nFlags, point);
}

void CGraphicView::OnLButtonUp(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	//创建并获得设备描述
	CClientDC dc(this);
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
	    pOldBrush= dc.SelectObject(pBrush);
	}else{
		brush.CreateSolidBrush(m_Color);
		pOldBrush=dc.SelectObject(&brush);
	}

	
    //画出线宽大于1的实线/虚线/点线
	LOGBRUSH logBrush;  
	logBrush.lbStyle = BS_SOLID;  
	logBrush.lbColor = m_Color;  
	CPen pen1(m_LineStyle,m_LineWidth,m_Color);//创建画笔
	CPen pen2(PS_DASH | PS_GEOMETRIC | PS_ENDCAP_ROUND,m_LineWidth,&logBrush);//创建画笔
	CPen pen3(PS_DOT | PS_GEOMETRIC | PS_ENDCAP_ROUND,m_LineWidth,&logBrush);//创建画笔
	dc.SelectObject(&pen1);
	if(m_LineStyle==1)dc.SelectObject(&pen2);		//选择画笔
	else  if(m_LineStyle!=0)dc.SelectObject(&pen3);		//选择画笔
	

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
		  //恢复先前的画刷
		  dc.SelectObject(pOldBrush);
		  break;
	  case 4:/*绘制椭圆*/
		  dc.Ellipse(CRect(m_ptOrigin,point));
		  //恢复先前的画刷
		  dc.SelectObject(pOldBrush);
		  break;
	}

	//-_-  case中无法声明变量
	if(m_nDrawType==7){
		//Simplebrush
		CBrush brush(m_Color);
	    //利用画刷填充鼠标拖曳过程中形成的矩形区域 
        dc.FillRect(CRect(m_ptOrigin,point),&brush);
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
		dc.FillRect(CRect(m_ptOrigin,point),&brush);
	}
	if(m_nDrawType==9){
		//Transparentbrush
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

    //画出线宽大于1的实线/虚线/点线
	LOGBRUSH logBrush;  
	logBrush.lbStyle = BS_SOLID;  
	logBrush.lbColor = m_Color;  
	CPen pen1(m_LineStyle,m_LineWidth,m_Color);//创建画笔
	CPen pen2(PS_DASH | PS_GEOMETRIC | PS_ENDCAP_ROUND,m_LineWidth,&logBrush);//创建画笔
	CPen pen3(PS_DOT | PS_GEOMETRIC | PS_ENDCAP_ROUND,m_LineWidth,&logBrush);//创建画笔
	dc.SelectObject(&pen1);
	if(m_LineStyle==1)dc.SelectObject(&pen2);		//选择画笔
	else  if(m_LineStyle!=0)dc.SelectObject(&pen3);		//选择画笔

	if(m_bDraw==true)
		switch(m_nDrawType){
			case 5://SECTOR
				dc.MoveTo(m_ptOrigin);                  
				dc.LineTo(point);
				break;
			case 6://Polyline
				dc.MoveTo(m_ptOrigin);                  
				dc.LineTo(point);
				//修改线段的起点        
				m_ptOrigin=point;
				break;
			case 10://erase
				CBrush brush(RGB(255,255,255));
				CPoint pt1;
				CPoint pt2;
				pt1.x=point.x-10;
				pt1.y=point.y-10;
				pt2.x=point.x+10;
				pt2.y=point.y+10;
				dc.FillRect(CRect(pt1,pt2),&brush);
				break;
		}
	//恢复设备描述

	CView::OnMouseMove(nFlags, point);
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


BOOL CGraphicView::OnEraseBkgnd(CDC* pDC) 
{
	// TODO: Add your message handler code here and/or call default
	
	// nothing
	 //return CView::OnEraseBkgnd(pDC);
	return true;
}

void CGraphicView::OnImportsample() 
{
	// TODO: Add your command handler code here
	using namespace Gdiplus;
	CDC *pDC=GetDC();
	Graphics graphics(pDC->GetSafeHdc());
	Image image(L"E:\\study\\东南大学\\学科作业\\MFC\\Graphic\\Graphic0.6\\res\\lena.bmp");

	CRect rect;
	this->GetClientRect(&rect);
	pDC->FillSolidRect(&rect,RGB(255,255,255));
	graphics.DrawImage(&image, 50, 50);
	rotatecount=0;
}

void CGraphicView::OnRotate() 
{
	// TODO: Add your command handler code here
	using namespace Gdiplus;
	rotatecount++;
	CDC *pDC=GetDC();
	Graphics graphics(pDC->GetSafeHdc());
	Image image(L"E:\\study\\东南大学\\学科作业\\MFC\\Graphic\\Graphic0.6\\res\\lena.bmp");
	graphics.TranslateTransform(150,150); //源点移动到旋转中心
	graphics.RotateTransform(30.0f*rotatecount); //旋转
	graphics.TranslateTransform(-150, -150);//还原源点

    CRect rect;
	this->GetClientRect(&rect);
	pDC->FillSolidRect(&rect,RGB(255,255,255));
    //在某个起点显示图像
    graphics.DrawImage(&image, 50, 50);
}


void CGraphicView::OnGray() 
{
	// TODO: Add your command handler code here
	using namespace Gdiplus;
	CDC *pDC=GetDC();
	CRect rect;
	this->GetClientRect(&rect);
	pDC->FillSolidRect(&rect,RGB(255,255,255));
	Graphics graphics(pDC->GetSafeHdc());
	Image image(L"E:\\study\\东南大学\\学科作业\\MFC\\Graphic\\Graphic0.6\\res\\lena.bmp");
	ColorMatrix colorMatrix=
	{
		0.298f,0.298f,0.298f,0,0,
		0.586f,0.586f,0.586f,0,0,
		0.113f,0.113f,0.113f,0,0,
		0,0,0,1,0,
		0,0,0,0,1
	};
	ImageAttributes attr;
	attr.SetColorMatrix(&colorMatrix);
	Graphics g(pDC->GetSafeHdc());
	Rect destRect(50,50,image.GetWidth(),image.GetHeight());
	g.DrawImage(&image, destRect, 0,0,image.GetWidth(),image.GetHeight(),UnitPixel,&attr);
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

void CGraphicView::OnErase() 
{
	// TODO: Add your command handler code here
	m_nDrawType=10;
}

void CGraphicView::OnFillarea() 
{
	// TODO: Add your command handler code here
	m_nDrawType=11;
}




/////////////////////////////////Addtion Functions
void CGraphicView::FillAreaqaq(CPoint point,COLORREF originColor)
{
   
   // BFS is so slow
   /*
   int x,y,l,r,ll,rr,tx,ty;
   //创建获得设备描述
   CClientDC dc(this);
   HDC hDC=::GetDC(NULL);
   RECT rc;
   GetClientRect(&rc);
   dc.SetPixel(point,m_Color);
   l=r=0;
   Pts[l]=point;
   while(l<=r){
     ll=l%Pnum;
	 x=Pts[ll].x;
	 y=Pts[ll].y;
     for(int i=0;i<4;i++){
	   tx=x+fx[i];
	   ty=y+fy[i];
	   CPoint xp(tx,ty);
	   if(tx>=0&&ty>=0&&tx<=rc.bottom&&ty<=rc.right&&originColor==::GetPixel(hDC,tx,ty)){
		    dc.SetPixel(xp,m_Color);
			++r;rr=r%Pnum;
			Pts[rr]=xp;
	   }
	 }
	 l++;
   }
   */
}

void CGraphicView::OnPaint() 
{
	CPaintDC dc(this); // device context for painting

	
///////////////////////////////////////////////////////////////////////////////
//加载图片

	CGraphicDoc* pDoc = GetDocument();//得到文档指针,注意,文档的命名是与工程名有关的!!不同的程序不一样.
	ASSERT_VALID(pDoc); 
	
	//是否已打开某个BMP文件
	if(pDoc->flagOpen==1)
	{
		//这个函数显示DIB
		SetDIBitsToDevice(dc.m_hDC,  //DIB将输出的设备描述表
			0,               //设备描述表中位图输出起始逻辑x地址
			0,               //设备描述表中位图输出起始逻辑x地址 
			pDoc->bi.biWidth,  //DIB的宽度
			pDoc->bi.biHeight, //DIB的高度
			0,                 //DIB开始读取输出的像素数据的x位置
			0,                 //DIB开始读取输出的像素数据的y位置
			0,                 //DIB中像素的水平行号,它对应lpBits内存缓冲区第一行数据
			pDoc->bi.biHeight, //DIB的行数，对应包含在由lpBits所指内存缓冲区中的数据
			pDoc->lpbuf,       //包含像素数据的内存缓冲区的指针
			pDoc->pbi,        //指向初始化了的BITMAPINFO数据结构的指针，描述了位图的大小和色彩数据
			DIB_RGB_COLORS);   //指定是显示的颜色
	  Invalidate(false);
	  return;
	}
	// Do not call CView::OnPaint() for painting messages
	//WRONG!!
	//Invalidate(true);



	OnDraw(&dc); //调用了OnDraw   VC6.0
	// TODO: Add your message handler code here
	
	// Do not call CView::OnPaint() for painting messages

}

