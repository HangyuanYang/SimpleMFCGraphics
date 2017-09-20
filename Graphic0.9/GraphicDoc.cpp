// GraphicDoc.cpp : implementation of the CGraphicDoc class
//

#include "stdafx.h"
#include "Graphic.h"

#include "GraphicDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CGraphicDoc

IMPLEMENT_DYNCREATE(CGraphicDoc, CDocument)

BEGIN_MESSAGE_MAP(CGraphicDoc, CDocument)
	//{{AFX_MSG_MAP(CGraphicDoc)
	ON_COMMAND(ID_FILE_OPEN, OnFileOpen)
	ON_COMMAND(ID_FILE_SAVE_AS, OnFileSaveAs)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGraphicDoc construction/destruction

CGraphicDoc::CGraphicDoc()
{
	// TODO: add one-time construction code here
	flagOpen=0;
}

CGraphicDoc::~CGraphicDoc()
{
}

BOOL CGraphicDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CGraphicDoc serialization

void CGraphicDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

/////////////////////////////////////////////////////////////////////////////
// CGraphicDoc diagnostics

#ifdef _DEBUG
void CGraphicDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CGraphicDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CGraphicDoc commands

void CGraphicDoc::OnFileOpen() 
{
	// TODO: Add your command handler code here
	LPCTSTR lpszFilter="BMP Files(*.bmp)|*.bmp|任何文件|*.*||";
	CFileDialog dlg(TRUE,lpszFilter,NULL,OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT,lpszFilter,NULL);
	CString filepath;
	CFile file;

	//打开文件对话框
	if(dlg.DoModal()==IDOK){
		filepath=dlg.GetPathName();
		FilePath=filepath;
		if(file.Open(filepath,CFile::modeRead|CFile::shareDenyNone,NULL)==0)
		{
			//读取文件失败
			AfxMessageBox("无法打开文件！",MB_OK,0);
			return;
		}
		//读取文件头
		file.Read(&bf,sizeof(bf));
		//判断是否是BMP文件
		if(bf.bfType!=0x4d42)//'BM'
		{
			AfxMessageBox("非BMP文件！",MB_OK,0);
			return;
		}
		//判断文件是否损坏
		if(file.GetLength()!=bf.bfSize)
		{
			AfxMessageBox("文件已损坏，请检查！",MB_OK,0);
			return;
		}
		//读文件信息头
		file.Read(&bi,sizeof(bi));
		//计算调色板数目
		numquad=0;
		if(bi.biBitCount<24)
		{
			numquad=1<<bi.biBitCount;
		}
		//为图像信息pbi申请空间
		pbi=(BITMAPINFO*)HeapAlloc(GetProcessHeap(),0,sizeof(BITMAPINFOHEADER)+numquad*sizeof(RGBQUAD));
		memcpy(pbi,&bi,sizeof(bi));
		quad=(RGBQUAD*)((BYTE*)pbi+sizeof(BITMAPINFOHEADER));
		//读取调色板
		if(numquad!=0)
		{
			file.Read(quad,sizeof(RGBQUAD)*numquad);
		}
		//为图像数据申请空间
		bi.biSizeImage=bf.bfSize-bf.bfOffBits;
		lpbuf=(BYTE*)HeapAlloc(GetProcessHeap(),0,bi.biSizeImage);
		//读取图像数据
		file.Read(lpbuf,bi.biSizeImage);
		//图像读取完毕，关闭文件，设置标志
		file.Close();
		flagOpen=1;
		this->UpdateAllViews(NULL);
	}
}


void CGraphicDoc::OnFileSaveAs() 
{
	// TODO: Add your command handler code here
	LPCTSTR lpszFilter="BMP Files(*.bmp)|*.bmp|任何文件|*.*||";
	CFileDialog  dlg(FALSE,lpszFilter,NULL,OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT,lpszFilter,NULL);
	if (dlg.DoModal()!=IDOK)return;
	CFile file;
	CFileException fe;
	if (!file.Open(dlg.GetPathName(),CFile::modeCreate | CFile::modeReadWrite | CFile::shareExclusive, &fe))
	{
		// 失败
		ReportSaveLoadException(dlg.GetPathName(), &fe, TRUE, AFX_IDP_INVALID_FILENAME);
		return;
	}
	file.SeekToBegin();
	file.Write(&bf,sizeof(bf));
	file.Write(&bi,sizeof(bi));
	if(numquad!=0)
	{
		file.Write(quad,sizeof(RGBQUAD)*numquad);
	}
	file.WriteHuge(lpbuf,bi.biSizeImage);
	file.Close(); 
}
