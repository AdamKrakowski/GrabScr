#pragma once

int StrippedDir(char *path);

class CDebug {

public:
	CDebug();
	CDebug( char *filename );
	int CDebugOpen( char *filename);
	int CDebugOpen();
	int CDebugClose( );
	void CDebugPut(char *text);
	void CDebugPut(char *text,int value);
	void CDebugPut(char *text,int value1,int value2);
	void CDebugPut(char *text,int value1,int value2,int value3);
	void CDebugPut(char *text,int value1,int value2,int value3,int value4); 
	void CDebugPut(char *text,double fvalue1,double fvalue2);
	void CDebugPut(char *text,double fvalue1,double fvalue2,double fvalue3);

	int  CDebugOpenRemoteDisplay(HWND ThisAppHwnd  );
	void CDebugDsp(char *text);
	void CDebugDsp(char *text,int value);
	void CDebugDsp(char *text,int value1,int value2);
	void CDebugDsp(char *text,int value1,int value2,int value3);
	void CDebugDsp(char *text,int value1,int value2,int value3,int value4); 
	void CDebugDsp(char *text,double fvalue1,double fvalue2);
	void CDebugDsp(char *text,double fvalue1,double fvalue2,double fvalue3);
	void CDebugErrorMessage(int i );

private:
	char FileName[MAX_PATH];
	int  mError;
	int  mFilename;
	HANDLE hFile;
	HWND   mHwnd;
	HWND   mAppHwnd;

	void SendCharToFile( char c);
	void LogDebugStringExt( char *pstr );
	void DspDebugStringExt( char *pstr );

};