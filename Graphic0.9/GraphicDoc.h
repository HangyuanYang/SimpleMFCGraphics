// GraphicDoc.h : interface of the CGraphicDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_GRAPHICDOC_H__B957CE6F_4E8C_4F51_818A_CF27BE0625F1__INCLUDED_)
#define AFX_GRAPHICDOC_H__B957CE6F_4E8C_4F51_818A_CF27BE0625F1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CGraphicDoc : public CDocument
{
protected: // create from serialization only
	CGraphicDoc();
	DECLARE_DYNCREATE(CGraphicDoc)

// Attributes
public:
	//用于打开位图文件：
	int numquad; //调色板数
	int flagOpen;//标志是否打开bmp
	BITMAPINFO* pbi;  //记录图像细节
	BYTE* lpbuf;  //图像数据
	RGBQUAD* quad;  //调色板
	BITMAPFILEHEADER bf;//文件头
	BITMAPINFOHEADER bi;  //信息头 
	CString FilePath;
	CString FileExt;
// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGraphicDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CGraphicDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CGraphicDoc)
	afx_msg void OnFileOpen();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GRAPHICDOC_H__B957CE6F_4E8C_4F51_818A_CF27BE0625F1__INCLUDED_)
