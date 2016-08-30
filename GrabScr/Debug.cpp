

#include "stdafx.h"
//#include "MouseTest.h"

#include "Windowsx.h"
#include "Math.h"
#include <stdio.h>

#include "Debug.h"
 

CDebug mDebug;

//	mDebug.CDebugPut("Draw switch "  );
//	mDebug.CDebugPut("Mode :%d %d   ", p->Turn ,p->Turn );
// 	mDebug.CDebugPut("Angle  :%6.2f Sweep:%6.2f  ", p->mStartAngle ,p->mSweepAngle );
//  need to update bounding rect



int StrippedDir(char *path)
{
 
	int v=0,i,l=  strlen( path );

 for (i=l;i>0;i--)
     if ( path[i] =='\\') {v=i;break;}
 
	 if ( v==0) return l;
 else 
	 {
		  path[v+1] =0;
		 return v;
	 }
}


HWND FindApplicationWinHandle( char *CsTitle )
{
  // short  sw =  GetWin32Version();
  // if ( !sw  ) return NULL;

	OSVERSIONINFO  osv;
	osv.dwOSVersionInfoSize = sizeof (OSVERSIONINFO);
    GetVersionEx (&osv);

 // works
	// HWND  hwDispatch = FindWindow( "Disp32Class", "Hidden Window" );

  char wd[140];
  //int i;
  int len =  strlen(CsTitle);

  HWND hWnd = ::GetTopWindow(NULL);
 
 //mDebug.CDebugPut("Search:  ");

  while ( hWnd )
       {
         ::GetWindowText(hWnd,(LPSTR)wd,80);
 
		  
 //mDebug.CDebugPut(wd);

         wd[len]=0;
 
         if    ( !strcmp( wd, CsTitle) )
             return hWnd;
         hWnd = ::GetNextWindow(hWnd ,GW_HWNDNEXT);
       }
  return NULL;
}
 
CDebug::CDebug() 
{
	mError = 0;
	mFilename = 0;
	hFile=NULL; 
	mHwnd = NULL;
	mAppHwnd = NULL;
}

CDebug::CDebug( char *filename ) 
{
	mError = 1;
	if ( strlen(filename) <  MAX_PATH )  
	{
		strcpy_s(  FileName, MAX_PATH  , filename);
		mFilename = 1;
	}
	else
		mError = 1;   
 	hFile=NULL;
	mHwnd = NULL;
	mAppHwnd = NULL;
}
	
int CDebug::CDebugOpen( char *filename)
{
	mError = 1;
	if ( strlen(filename) <  MAX_PATH )  
		strcpy_s(  FileName, MAX_PATH  , filename);
	else
		{mError = 2; return mError; }

	mFilename = 1;


	hFile  = CreateFile(   (LPCTSTR) FileName , GENERIC_WRITE,FILE_SHARE_READ, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
 
	if ( hFile  == INVALID_HANDLE_VALUE ) { hFile = NULL; return 5;}

	return 0;
}

int CDebug::CDebugOpen()
{
	if ( mFilename == 0 )  return 3;

	hFile  = CreateFile(   (LPCTSTR) FileName , GENERIC_WRITE,FILE_SHARE_READ, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
 
	if ( hFile  == INVALID_HANDLE_VALUE ) { hFile = NULL; return 6;}

	return 0;
}

int CDebug::CDebugClose( ) 
{
	if ( mFilename == 0 )  return 4;
	
	if ( hFile ) CloseHandle( hFile);  
    else return 6;

	hFile = NULL;
	return 0;
}


void CDebug::SendCharToFile( char c)
{
  DWORD lpNumberOfBytesWritten;

  char cbuf[2];
  cbuf[0]=c;

  if ( hFile )
    WriteFile(
      hFile,
    (LPCVOID)cbuf,
    1,
    &lpNumberOfBytesWritten,
   NULL
    );
}


void CDebug::LogDebugStringExt( char *pstr )
{
    int i=0;
	SendCharToFile(13);
	SendCharToFile(10);

 	while ( 1 )
 		if (  pstr[i] != 0 )  SendCharToFile( pstr[i++]); 
		else break;
}


COPYDATASTRUCT MyCDS;
char buffer[1024];
int  msize = 0;

void CDebug::DspDebugStringExt( char *pstr )
{
	int l = strlen(pstr)+1;

	if ( l > 1022 ) return;
	
	memcpy(buffer,pstr,l);
	msize = l;
	
	MyCDS.dwData = 0x1000;
	MyCDS.cbData = msize;
	MyCDS.lpData = buffer;


   if( mHwnd != NULL )
      SendMessage( mHwnd,
                   WM_COPYDATA,
                   (WPARAM)(HWND) mAppHwnd,
                   (LPARAM) (LPVOID) &MyCDS );

}


void CDebug::CDebugPut(char *text)
{
 
 LogDebugStringExt( (char *)text);
 

}
void CDebug::CDebugPut(char *sformat,int value) 
{
 char *pb;
 pb = (char *)malloc( 256);
 sprintf_s( pb,   250, sformat ,  value    );
 LogDebugStringExt( (char *)pb);
 free(pb);

}
void CDebug::CDebugPut(char *sformat,int value1,int value2)
{
 char *pb;
 pb = (char *)malloc( 256);
 sprintf_s( pb,   250, sformat ,  value1   ,value2  );
 LogDebugStringExt( (char *)pb);
 free(pb);

}

void CDebug::CDebugPut(char *sformat,double fvalue1,double fvalue2) 
{
 char *pb;
 pb = (char *)malloc( 256);
 sprintf_s( pb,   250, sformat ,  fvalue1   ,fvalue2  );
 LogDebugStringExt( (char *)pb);
 free(pb);

}

void CDebug::CDebugPut(char *sformat,double fvalue1,double fvalue2 , double fvalue3 ) 
{
 char *pb;
 pb = (char *)malloc( 256);
 sprintf_s( pb,   250, sformat ,  fvalue1   ,fvalue2 ,fvalue3  );
 LogDebugStringExt( (char *)pb);
 free(pb);

}

void CDebug::CDebugPut(char *sformat,int value1,int value2,int value3)
{
 char *pb;
 pb = (char *)malloc( 256);
 sprintf_s( pb,   250, sformat ,  value1   ,value2 , value3 );
 LogDebugStringExt( (char *)pb);
 free(pb);

}
void CDebug::CDebugPut(char *sformat,int value1,int value2,int value3,int value4)
{
 char *pb;
 pb = (char *)malloc( 256);
 sprintf_s( pb,   250, sformat ,  value1   ,value2 , value3 ,value4 );
 LogDebugStringExt( (char *)pb);
 free(pb);

}



int  CDebug::CDebugOpenRemoteDisplay(HWND ThisAppHwnd )
{

mAppHwnd =	ThisAppHwnd;

BOOL bl = ChangeWindowMessageFilter( WM_COPYDATA,MSGFLT_ADD);
if ( bl == FALSE ) return 0;

 mHwnd = FindApplicationWinHandle( (char *)"DebugDsp - DebugDsp" );

return ( mHwnd != NULL );
}



void CDebug::CDebugDsp(char *text)
{
 
 if ( mHwnd == NULL ) return;
	
	DspDebugStringExt( (char *)text);
 

}
void CDebug::CDebugDsp(char *sformat,int value) 
{
 char *pb;

  if ( mHwnd == NULL ) return;

 pb = (char *)malloc( 256);
 sprintf_s( pb,   250, sformat ,  value    );
 DspDebugStringExt( (char *)pb);
 free(pb);

}
void CDebug::CDebugDsp(char *sformat,int value1,int value2)
{
 char *pb;

  if ( mHwnd == NULL ) return;

 pb = (char *)malloc( 256);
 sprintf_s( pb,   250, sformat ,  value1   ,value2  );
 DspDebugStringExt( (char *)pb);
 free(pb);

}

void CDebug::CDebugDsp(char *sformat,double fvalue1,double fvalue2  ) 
{
 char *pb;

  if ( mHwnd == NULL ) return;

 pb = (char *)malloc( 256);
 sprintf_s( pb,   250, sformat ,  fvalue1   ,fvalue2   );
 DspDebugStringExt( (char *)pb);
 free(pb);

}


void CDebug::CDebugDsp(char *sformat,double fvalue1,double fvalue2 , double fvalue3) 
{
 char *pb;

  if ( mHwnd == NULL ) return;

 pb = (char *)malloc( 256);
 sprintf_s( pb,   250, sformat ,  fvalue1   ,fvalue2  ,   fvalue3 );
 DspDebugStringExt( (char *)pb);
 free(pb);

}


void CDebug::CDebugDsp(char *sformat,int value1,int value2,int value3)
{
 char *pb;
 
  if ( mHwnd == NULL ) return;

 pb = (char *)malloc( 256);
 sprintf_s( pb,   250, sformat ,  value1   ,value2 , value3 );
 DspDebugStringExt( (char *)pb);
 free(pb);

}
void CDebug::CDebugDsp(char *sformat,int value1,int value2,int value3,int value4)
{
 char *pb;

  if ( mHwnd == NULL ) return;

 pb = (char *)malloc( 256);
 sprintf_s( pb,   250, sformat ,  value1   ,value2 , value3 ,value4 );
 DspDebugStringExt( (char *)pb);

 free(pb);

}


 void CDebug::CDebugErrorMessage(int i )
 {
    MessageBox(NULL , "Can't add bend ", "MyApp", MB_OK );

 }