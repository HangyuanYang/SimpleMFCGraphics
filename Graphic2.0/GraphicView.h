// GraphicView.h : interface of the CGraphicView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_GRAPHICVIEW_H__8CB6C56A_60F8_4039_9E42_04CD8024CCE8__INCLUDED_)
#define AFX_GRAPHICVIEW_H__8CB6C56A_60F8_4039_9E42_04CD8024CCE8__INCLUDED_


#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/*
#define Pnum 10000000
static CPoint Pts[Pnum];
static const int fx[4]={0,1,0,-1};
static const int fy[4]={1,0,-1,0};
*/

class CGraphicView : public CView
{
protected: // create from serialization only
	CGraphicView();
	DECLARE_DYNCREATE(CGraphicView)

// Attributes
public:
	CGraphicDoc* GetDocument();
    CDC MemDC; //首先定义一个显示设备对象
    CBitmap MemBitmap;//定义一个位图对象
	int nWidth;
	int nHeight;
	CPoint m_ptOrigin;
	int m_nDrawType;
	bool m_bDraw;
	UINT m_LineWidth;
	int	m_LineStyle;
	COLORREF m_Color;
	int m_nFILLMODEL;
	int m_nAngle;
	int m_nRotateModel;
	int imagePointX;
	int imagePointY;
	Image* m_pImg;
	int m_ZoomRow;
	int m_ZoomColumn;
	int m_TranslateLevel;
	int m_TranslateVertical;
	float m_rTrans;
	float m_cTrans;
	bool isGray;
	bool imageConfirm;
	bool isAll;
	bool ism_p;

//	CHOOSEFONT m_cf;
//	CFont m_font;
//	CString m_strFontName;


// Operations
public:
	void initial();
	void NormalTrans();
	void CopyToMemDC();
	void imageConfirmnation();
	void imageDraw();
	void sprayGun(CPoint);

	bool Load( LPCTSTR pszFileName );
	int GetEncoderClsid(const WCHAR* , CLSID* );
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGraphicView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CGraphicView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CGraphicView)
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnLine();
	afx_msg void OnRectangle();
	afx_msg void OnDot();
	afx_msg void OnEllipse();
	afx_msg void OnSector();
	afx_msg void OnPolyline();
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnSimplebrush();
	afx_msg void OnBitmapbrush();
	afx_msg void OnTransparentbrush();
 	afx_msg void OnColor();
	afx_msg void OnSetting();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnErase();
	afx_msg void OnFillarea();
	afx_msg void OnRotate();
	afx_msg void OnPaint();
	afx_msg void OnGray();
	afx_msg void OnAll();
	afx_msg void OnZoom();
	afx_msg void OnTranslate();
	afx_msg void OnGauss();
	afx_msg void OnFileSave();
	afx_msg void OnFileSaveAs();
	afx_msg void OnFileNew();
	afx_msg void OnText();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnMedian();
	afx_msg void OnBilateral();
	afx_msg void OnSimpleNoScale();
	afx_msg void OnNot();
	afx_msg void OnLevelfilp();
	afx_msg void OnVerticalfilp();
	afx_msg void OnLaplace();
	afx_msg void OnSobel();
	afx_msg void OnGun();
	afx_msg void OnRoundrect();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

static CString pas("password");

#ifndef _DEBUG  // debug version in GraphicView.cpp
inline CGraphicDoc* CGraphicView::GetDocument()
   { return (CGraphicDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GRAPHICVIEW_H__8CB6C56A_60F8_4039_9E42_04CD8024CCE8__INCLUDED_)
