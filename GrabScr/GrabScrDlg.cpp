
// GrabScrDlg.cpp : implementation file
//  Copyright (c)  Adam J. Godzik 
//	Krakow 2016
//	Start work : 2016.03.18  22:00
//	End work : 2016.03.19 11:30 
//
//
//


#include "stdafx.h"
#include "GrabScr.h"
#include "GrabScrDlg.h"
#include "afxdialogex.h"

#include "Debug.h"

extern CDebug mDebug;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


CString StrippedDir(CString Ci)
{
 int v=0,i,l=Ci.GetLength();

 for (i=l;i>0;i--)
     if ( Ci.GetAt(i)=='\\') {v=i;break;}
 if ( v==0) return Ci;
 else return Ci.Left(v+1);
}

// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CGrabScrDlg dialog




CGrabScrDlg::CGrabScrDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CGrabScrDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CGrabScrDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CGrabScrDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_GRAB, &CGrabScrDlg::OnBnClickedButtonGrab)
	ON_WM_TIMER()
END_MESSAGE_MAP()


// CGrabScrDlg message handlers

BOOL CGrabScrDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	index = 0;

	char path[160];
	GetModuleFileName( NULL ,path ,158);
    CString Cs = path;
	mCsHomePath = StrippedDir(Cs);

	// disable debug
	/*
				 	// open remote debug file
	{
			char path[MAX_PATH];
			GetModuleFileName( NULL ,path ,MAX_PATH);
			StrippedDir( path);
			strcat_s(path, MAX_PATH-20 ,"Debug.txt");
			mDebug.CDebugOpen( path);
			 
	}

	mDebug.CDebugPut("Log is started : ");
	*/

	// create directory !!!!!!!!!!!!!!!!  - level down from the application home
 
	CString CS_Full_DirPath;
	CS_Full_DirPath = mCsHomePath;
	CS_Full_DirPath += _T("JPG\\");
	BOOL bret =   CreateDirectory( CS_Full_DirPath   , NULL );

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here

	HWND hWnd = NULL ; // screen 
	HDC hDC;

	hDC = ::GetDC( hWnd );	
	hdcMem = CreateCompatibleDC( hDC);     
	bitmap = CreateCompatibleBitmap( hDC, GetDeviceCaps(hDC ,HORZRES), GetDeviceCaps(hDC ,VERTRES));     // memory bitmap
	SelectObject(hdcMem, bitmap);	
	::ReleaseDC( NULL , hDC );

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CGrabScrDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CGrabScrDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CGrabScrDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CGrabScrDlg::DebugHDC(int id , HDC hdcMem   )
{
	mDebug.CDebugPut((char *)"DebugHDC:%d", id  );
	mDebug.CDebugPut((char *)"HORZSIZE :%d",  GetDeviceCaps(hdcMem , HORZSIZE ) );
	mDebug.CDebugPut((char *)"VERTSIZE :%d",  GetDeviceCaps(hdcMem , VERTSIZE ) );
	mDebug.CDebugPut((char *)"BITSPIXEL :%d",  GetDeviceCaps(hdcMem , BITSPIXEL ) );
	mDebug.CDebugPut((char *)"HORZRES :%d",  GetDeviceCaps(hdcMem , HORZRES ) );
	mDebug.CDebugPut((char *)"VERTRES :%d",  GetDeviceCaps(hdcMem , VERTRES ) );
}


// get unique file name

CString CGrabScrDlg::CreateFilePath (int fformat)
{
	CString CS_Full_path;
	CS_Full_path = mCsHomePath;

	CTime t = CTime::GetCurrentTime(); 

	char lpath[32] ;
	sprintf_s( lpath, 30, "%02i%02i%02i%02i%02i%03i.JPG", t.GetMonth(),t.GetDay(),t.GetHour(),t.GetMinute(),t.GetSecond(),index  );

	CS_Full_path += _T("JPG\\");
	CS_Full_path += lpath;
 
	index += 1;

	return CS_Full_path;
}

// initialize grabbing

void CGrabScrDlg::OnBnClickedButtonGrab()
{
 	CWnd *dlg  = theApp.m_pMainWnd;
    ::ShowWindow( dlg->m_hWnd , SW_HIDE );
    SetTimer( 100, 200,NULL);   // delay to update the window state - disapear
}

// complete grabbing

void CGrabScrDlg::OnTimer(UINT_PTR nIDEvent)
{
	KillTimer(100);
	HWND hWnd = NULL ;
	HDC hDC;

	hDC = ::GetDC( hWnd );	
	BitBlt( hdcMem, 0, 0, GetDeviceCaps(hDC, HORZRES), GetDeviceCaps(hDC, VERTRES), hDC, 0, 0, SRCCOPY);
	::ReleaseDC( hWnd , hDC );

	SaveGrabbedImage( CreateFilePath (  FILE_FORMAT_JPG ) ,   bitmap    );

	CWnd *dlg  = theApp.m_pMainWnd;
    ::ShowWindow( dlg->m_hWnd  , SW_SHOW );
}

//  save to the file 

BOOL CGrabScrDlg::SaveGrabbedImage( CString filename , HBITMAP bitmap    )
{
	CImage img; 
	img.Attach((HBITMAP)bitmap );
	img.Save(filename);
	return TRUE;
}



 
