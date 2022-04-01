#include "stdafx.h"
#include "Transcoder.h"
wstring ANSIToUnicode(const string& str)
{
	int  len = 0;
	len = str.length();
	int  unicodeLen = ::MultiByteToWideChar(CP_ACP, 0, str.c_str(), -1, NULL, 0);
	wchar_t *  pUnicode;
	pUnicode = new  wchar_t[unicodeLen + 1];
	memset(pUnicode, 0, (unicodeLen + 1) * sizeof(wchar_t));
	::MultiByteToWideChar(CP_ACP, 0, str.c_str(), -1, (LPWSTR)pUnicode, unicodeLen);
	wstring  rt;
	rt = (wchar_t*)pUnicode;
	delete  pUnicode;

	return  rt;
}
wstring UTF8ToUnicode(const string& str)
{
	int  len = 0;
	len = str.length();
	int  unicodeLen = MultiByteToWideChar(CP_UTF8, 0, str.c_str(), -1, NULL, 0);
	wchar_t *  pUnicode;
	pUnicode = new  wchar_t[unicodeLen + 1];
	memset(pUnicode, 0, (unicodeLen + 1) * sizeof(wchar_t));
	MultiByteToWideChar(CP_UTF8, 0, str.c_str(), -1, (LPWSTR)pUnicode, unicodeLen);
	wstring  rt;
	rt = (wchar_t*)pUnicode;
	delete  pUnicode;

	return  rt;
}
string UnicodeToANSI(const wstring& str)
{
	char*     pElementText;
	int    iTextLen;
	// wide char to multi char
	iTextLen = WideCharToMultiByte(CP_ACP, 0, str.c_str(), -1, NULL, 0, NULL, NULL);
	pElementText = new char[iTextLen + 1];
	memset((void*)pElementText, 0, sizeof(char) * (iTextLen + 1));
	::WideCharToMultiByte(CP_ACP, 0, str.c_str(), -1, pElementText, iTextLen, NULL, NULL);
	string strText;
	strText = pElementText;
	delete[] pElementText;
	return strText;
}
string UnicodeToUTF8(const wstring& str)
{
	char*     pElementText;
	int    iTextLen;
	// wide char to multi char
	iTextLen = WideCharToMultiByte(CP_UTF8, 0, str.c_str(), -1, NULL, 0, NULL, NULL);
	pElementText = new char[iTextLen + 1];
	memset((void*)pElementText, 0, sizeof(char) * (iTextLen + 1));
	::WideCharToMultiByte(CP_UTF8, 0, str.c_str(), -1, pElementText, iTextLen, NULL, NULL);
	string strText;
	strText = pElementText;
	delete[] pElementText;
	return strText;
}

wstring DWORD2BitString(DWORD dValue) {
	wstring tempStr;
	for (DWORD i = 0; i < 32; i++) {
		if (((dValue << i) >> 31) & 1) {
			tempStr.append(L"1");
		}
		else
		{
			tempStr.append(L"0");
		}
		if ((i + 1) % 8 == 0) {
			tempStr.append(L" ");
		}
	}
	return tempStr;
}

vector<wstring> split(const wstring &s, const wstring &seperator) {
	vector<wstring> result;
	typedef wstring::size_type string_size;
	string_size i = 0;

	while (i != s.size()) {
		//找到字符串中首个不等于分隔符的字母；
		int flag = 0;
		while (i != s.size() && flag == 0) {
			flag = 1;
			for (string_size x = 0; x < seperator.size(); ++x)
				if (s[i] == seperator[x]) {
					++i;
					flag = 0;
					break;
				}
		}

		//找到又一个分隔符，将两个分隔符之间的字符串取出；
		flag = 0;
		string_size j = i;
		while (j != s.size() && flag == 0) {
			for (string_size x = 0; x < seperator.size(); ++x)
				if (s[j] == seperator[x]) {
					flag = 1;
					break;
				}
			if (flag == 0)
				++j;
		}
		if (i != j) {
			result.push_back(s.substr(i, j - i));
			i = j;
		}
	}
	return result;
}

void FileTimeToWCHAR(FILETIME *lpFileTime, WCHAR *szTime) {
	FILETIME ftLocalFileTime;
	SYSTEMTIME SystemTime;
	FileTimeToLocalFileTime(lpFileTime, &ftLocalFileTime);
	FileTimeToSystemTime(&ftLocalFileTime, &SystemTime);

	wchar_t tempStr1[32];
	//szTime = { 0 };
	wcscpy(szTime, L"");
	_itow_s(SystemTime.wYear, tempStr1, 32,10);
	wcscat(szTime, tempStr1);
	wcscat(szTime, L"/");
	_itow_s(SystemTime.wMonth, tempStr1, 32, 10);
	wcscat(szTime, tempStr1);
	wcscat(szTime, L"/");
	_itow_s(SystemTime.wDay, tempStr1, 32, 10);
	wcscat(szTime, tempStr1);
	wcscat(szTime, L" ");

	_itow_s(SystemTime.wHour, tempStr1, 32, 10);
	wcscat(szTime, tempStr1);
	wcscat(szTime, L":");
	_itow_s(SystemTime.wMinute, tempStr1, 32, 10);
	wcscat(szTime, tempStr1);

}

void ExtractTypeNameAndTagFromFileName(wstring wsFileName, BOOL bIsFolder, vector<wstring> *pvTag, WCHAR *lpszFileTag, WCHAR *lpszTypeName) {
	ZeroMemory(lpszFileTag,MAX_PATH);
	if (bIsFolder) {
		wcscpy_s(lpszTypeName,MAX_PATH,L"Folder");
		vector<wstring> vSplitStrings;
		vSplitStrings = split(wsFileName, L"#");
		if (vSplitStrings.size() > 1) {
			for (int i = 1; i < vSplitStrings.size(); i++) {				
				pvTag->push_back(vSplitStrings[i]);		
				wcscat_s(lpszFileTag, MAX_PATH, vSplitStrings[i].c_str());
				wcscat_s(lpszFileTag, MAX_PATH, L";");
			}
		}
	}
	else {
		vector<wstring> vSplitStrings;
		vSplitStrings = split(wsFileName, L".");
		if (vSplitStrings.size() > 1) 
		{
			wcscpy_s(lpszTypeName, MAX_PATH, vSplitStrings.back().c_str());
		}else{
			wcscpy_s(lpszTypeName, MAX_PATH, L"File");
		}
		vector<wstring> vTag;
		vTag = split(vSplitStrings[0], L"#");
		if (vTag.size() > 1) {
			for (int i = 1; i < vTag.size(); i++) {
				pvTag->push_back(vTag[i]);
				wcscat_s(lpszFileTag, MAX_PATH, vTag[i].c_str());
				wcscat_s(lpszFileTag, MAX_PATH, L";");
			}
		}
	}	
}

wstring GetParentPath(wstring wsPath) {
	wstring wsReturn;

	vector<wstring> vSplitStrings;
	if((int)wsPath.find(L"\\")>=(int)0){
		vSplitStrings = split(wsPath, L"\\");
		if (vSplitStrings.size() > 1) {
			wsReturn.append(vSplitStrings[0]);
			for (int i = 1; i < vSplitStrings.size()-1; i++) {
				wsReturn.append(L"\\");
				wsReturn.append(vSplitStrings[i]);		
			}
			
		}
		else {
			wsReturn.append(vSplitStrings[0]);
		}
	}
	else {
		wsReturn = L"";
		 
	}
	return wsReturn;
}

BOOL IsPathExists(WCHAR *lpszFilePath) {
	int nRet = _taccess(lpszFilePath,0);
	return 0 == nRet || EACCES == nRet;
}

wstring GetFirstDriverCharW(wstring wsFilePath) {
	wstring wsDriverChar;
	wsDriverChar.assign(wsFilePath,0,1);
	return wsDriverChar;
}

BOOL IsStrFinded(wstring wsFilePath,wstring wsFindStr) {
	int index = wsFilePath.find(wsFindStr);
	int compareNum = 0;
	//wprintf(L"%d\n", );
	return (index >= compareNum);
}