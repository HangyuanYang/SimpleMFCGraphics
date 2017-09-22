; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CTextDlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "Graphic.h"
LastPage=0

ClassCount=11
Class1=CGraphicApp
Class2=CGraphicDoc
Class3=CGraphicView
Class4=CMainFrame

ResourceCount=8
Resource1=IDD_DLG_ROTATE
Class5=CAboutDlg
Resource2=IDD_ConFirm
Class6=SettingDlg
Resource3=IDD_DLG_SETTING
Class7=CRotateDlg
Resource4=IDD_ABOUTBOX
Class8=CZoomDlg
Resource5=IDR_MAINFRAME
Class9=CTranslateTrans
Resource6=IDD_DLG_ZOOM
Class10=CConfirmDlg
Resource7=IDD_Dlg_TranslateTrans
Class11=CTextDlg
Resource8=IDD_DLG_TEXT

[CLS:CGraphicApp]
Type=0
HeaderFile=Graphic.h
ImplementationFile=Graphic.cpp
Filter=N

[CLS:CGraphicDoc]
Type=0
HeaderFile=GraphicDoc.h
ImplementationFile=GraphicDoc.cpp
Filter=N
BaseClass=CDocument
VirtualFilter=DC
LastObject=CGraphicDoc

[CLS:CGraphicView]
Type=0
HeaderFile=GraphicView.h
ImplementationFile=GraphicView.cpp
Filter=C
BaseClass=CView
VirtualFilter=VWC
LastObject=CGraphicView


[CLS:CMainFrame]
Type=0
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp
Filter=T
LastObject=IDD_GUN
BaseClass=CFrameWnd
VirtualFilter=fWC




[CLS:CAboutDlg]
Type=0
HeaderFile=Graphic.cpp
ImplementationFile=Graphic.cpp
Filter=D
LastObject=CAboutDlg

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[MNU:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_FILE_SAVE_AS
Command5=ID_FILE_PRINT
Command6=ID_FILE_PRINT_PREVIEW
Command7=ID_FILE_PRINT_SETUP
Command8=ID_FILE_MRU_FILE1
Command9=ID_APP_EXIT
Command10=ID_EDIT_UNDO
Command11=ID_EDIT_CUT
Command12=ID_EDIT_COPY
Command13=ID_EDIT_PASTE
Command14=ID_VIEW_TOOLBAR
Command15=ID_VIEW_STATUS_BAR
Command16=ID_APP_ABOUT
Command17=IDM_SETTING
Command18=IDM_COLOR
Command19=IDM_DOT
Command20=IDM_LINE
Command21=IDM_RECTANGLE
Command22=IDM_ELLIPSE
Command23=IDM_SECTOR
Command24=IDM_Polyline
Command25=IDM_SIMPLEBRUSH
Command26=IDM_BITMAPBRUSH
Command27=IDM_TRANSPARENTBRUSH
Command28=ID_ERASE
Command29=ID_FILLAREA
Command30=IDD_GUN
Command31=IDD_TEXT
Command32=IDD_LEVELFILP
Command33=IDD_VERTICALFILP
Command34=ID_ALL
Command35=ID_TRANSLATE
Command36=ID_ZOOM
Command37=ID_ROTATE
Command38=ID_GRAY
Command39=IDD_NOT
Command40=ID_GAUSS
Command41=IDD_MEDIAN
Command42=IDD_BILATERAL
Command43=IDD_SIMPLE_NO_SCALE
Command44=IDD_LAPLACE
Command45=IDD_SOBEL
CommandCount=45

[ACL:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_FILE_PRINT
Command5=ID_EDIT_UNDO
Command6=ID_EDIT_CUT
Command7=ID_EDIT_COPY
Command8=ID_EDIT_PASTE
Command9=ID_EDIT_UNDO
Command10=ID_EDIT_CUT
Command11=ID_EDIT_COPY
Command12=ID_EDIT_PASTE
Command13=ID_NEXT_PANE
Command14=ID_PREV_PANE
CommandCount=14

[TB:IDR_MAINFRAME]
Type=1
Class=?
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_EDIT_CUT
Command5=ID_EDIT_COPY
Command6=ID_EDIT_PASTE
Command7=ID_FILE_PRINT
Command8=ID_APP_ABOUT
CommandCount=8

[DLG:IDD_DLG_SETTING]
Type=1
Class=SettingDlg
ControlCount=13
Control1=IDC_STATIC,static,1342308352
Control2=IDC_LINEWIDTH,edit,1350639745
Control3=IDC_STATIC,button,1342177287
Control4=IDC_LINEMODEL1,button,1342373897
Control5=IDC_LINEMODEL2,button,1342242825
Control6=IDC_LINEMODEL3,button,1342242825
Control7=IDC_LINEMODEL4,button,1342242825
Control8=IDC_LINEMODEL5,button,1342242825
Control9=IDC_STATIC,button,1342177287
Control10=IDC_FILL1,button,1342373897
Control11=IDC_FILL2,button,1342242825
Control12=IDOK,button,1342242817
Control13=IDCANCEL,button,1342242816

[CLS:SettingDlg]
Type=0
HeaderFile=SettingDlg.h
ImplementationFile=SettingDlg.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=IDC_LINEMODEL4

[DLG:IDD_DLG_ROTATE]
Type=1
Class=CRotateDlg
ControlCount=7
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308865
Control4=IDC_STATIC,static,1342308865
Control5=IDC_ROTATEANGLE,edit,1350639745
Control6=IDC_ROTATEMODEL1,button,1342373897
Control7=IDC_ROTATEMODEL2,button,1342242825

[CLS:CRotateDlg]
Type=0
HeaderFile=RotateDlg.h
ImplementationFile=RotateDlg.cpp
BaseClass=CDialog
Filter=D
LastObject=IDC_ROTATEMODEL1
VirtualFilter=dWC

[DLG:IDD_DLG_ZOOM]
Type=1
Class=CZoomDlg
ControlCount=7
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308865
Control4=IDC_STATIC,static,1342308865
Control5=IDC_STATIC,static,1342308865
Control6=IDC_ZOOMROW,edit,1350639745
Control7=IDC_ZOOMCOLUMN,edit,1350639745

[CLS:CZoomDlg]
Type=0
HeaderFile=ZoomDlg.h
ImplementationFile=ZoomDlg.cpp
BaseClass=CDialog
Filter=D
LastObject=CZoomDlg
VirtualFilter=dWC

[CLS:CTranslateTrans]
Type=0
HeaderFile=TranslateTrans.h
ImplementationFile=TranslateTrans.cpp
BaseClass=CDialog
Filter=D
LastObject=CTranslateTrans
VirtualFilter=dWC

[DLG:IDD_Dlg_TranslateTrans]
Type=1
Class=CTranslateTrans
ControlCount=11
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308865
Control4=IDC_STATIC,static,1342308865
Control5=IDC_STATIC,static,1342308865
Control6=IDC_TRANSLATELEVEL,edit,1350639745
Control7=IDC_TRANSLATEVERTICAL,edit,1350639745
Control8=IDC_plus1,button,1342373897
Control9=IDC_minus1,button,1342242825
Control10=IDC_plus2,button,1342373897
Control11=IDC_minus2,button,1342242825

[DLG:IDD_ConFirm]
Type=1
Class=CConfirmDlg
ControlCount=3
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308865

[CLS:CConfirmDlg]
Type=0
HeaderFile=ConfirmDlg.h
ImplementationFile=ConfirmDlg.cpp
BaseClass=CDialog
Filter=D
LastObject=CConfirmDlg

[DLG:IDD_DLG_TEXT]
Type=1
Class=CTextDlg
ControlCount=8
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_TEXTX,static,1342308865
Control4=IDC_TEXTY,static,1342308865
Control5=IDC_EDITX,edit,1350639745
Control6=IDC_EDITY,edit,1350639745
Control7=IDC_EDITCONTENT,edit,1350631558
Control8=IDC_STATIC,static,1342308865

[CLS:CTextDlg]
Type=0
HeaderFile=TextDlg.h
ImplementationFile=TextDlg.cpp
BaseClass=CDialog
Filter=D
LastObject=IDC_EDIT1
VirtualFilter=dWC

