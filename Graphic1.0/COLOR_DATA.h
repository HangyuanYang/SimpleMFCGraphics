// COLOR_DATA.h: interface for the CCOLOR_DATA class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_COLOR_DATA_H__459B12B9_818D_4E4C_A3DF_D5405B44A757__INCLUDED_)
#define AFX_COLOR_DATA_H__459B12B9_818D_4E4C_A3DF_D5405B44A757__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//高斯模糊函数
#define GAUSS_FUN(x, y) (exp(-(x*x)/(double)(2*y*y)))/(sqrt(2.0*3.14159265)*y)  
  
//暂定sigma=10  
const double sigma=10;  

class COLOR_DATA  
{
public:
	COLOR_DATA();
	virtual ~COLOR_DATA();
    double dDistance;
	COLORREF dwColor;
};

#endif // !defined(AFX_COLOR_DATA_H__459B12B9_818D_4E4C_A3DF_D5405B44A757__INCLUDED_)
