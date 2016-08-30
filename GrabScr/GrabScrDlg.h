
// GrabScrDlg.h : header file
//

#pragma once

#define FILE_FORMAT_BMP  0
#define FILE_FORMAT_JPG  1
#define FILE_FORMAT_GIF  2
// both file format use
#define FILE_FORMAT_BJG  3

#define USE_FORMAT_BMP  0
#define USE_FORMAT_JPG  1
#define USE_FORMAT_GIF  2
#define USE_FORMAT_BJG  3

#define USE_DIB_IFACE   0
#define USE_CIM_IFACE   1

// CGrabScrDlg dialog
class CGrabScrDlg : public CDialogEx
{
// Construction
public:
	CGrabScrDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_GRABSCR_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;
	CString mCsHomePath;
	HDC hdcMem;       // contente of the memory compatible bitmap
	HBITMAP bitmap;   // memory bitmap
	int index;

	BOOL SaveGrabbedImage( CString filename , HBITMAP bitmap );
	CString CreateFilePath (int fformat);
	void DebugHDC(int id , HDC hdcMem   );

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonGrab();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
};
