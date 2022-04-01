#pragma once
#include <string>
#include <windows.h> 
#define MAX_PATH 1024
using namespace std;
extern wstring ANSIToUnicode(const string& str);
extern wstring UTF8ToUnicode(const string& str);
extern string UnicodeToANSI(const wstring& str);
extern string UnicodeToUTF8(const wstring& str);

extern wstring DWORD2BitString(DWORD dValue);
extern vector<wstring> split(const wstring &s, const wstring &seperator);
extern void FileTimeToWCHAR(FILETIME *lpFileTime, WCHAR *szTime);

extern void ExtractTypeNameAndTagFromFileName(wstring wsFileName,BOOL bIsFolder, vector<wstring> *pvTag, WCHAR *lpszFileTag,WCHAR *lpszTypeName);
//extern void ExtractTypeNameAndTagFromFileName(wstring wsFileName, BOOL bIsFolder, vector<wstring> *pvTag);
extern wstring GetParentPath(wstring wsPath);

extern BOOL IsPathExists(WCHAR *lpszFilePath);

extern wstring GetFirstDriverCharW(wstring wsFilePath);

extern BOOL IsStrFinded(wstring wsFilePath, wstring wsFindStr);