// fetchUnityVersion.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <windows.h>

// returns NULL if the value could not be obtained
wchar_t *GetUnityVersion(const wchar_t *szFilename)
{
	// allocate a block of memory for the version info
	DWORD dummy;
	DWORD dwSize = GetFileVersionInfoSize(szFilename, &dummy);
	if (dwSize == 0)
	{
		return NULL;
	}
	BYTE *data = new BYTE[dwSize];

	// load the version info
	if (!GetFileVersionInfo(szFilename, NULL, dwSize, &data[0]))
	{
		delete[] data;
		return NULL;
	}

	wchar_t *pvUnityVersion = NULL;
	unsigned int iUnityVersionLen = 0;

	if (!VerQueryValue(&data[0], _T("\\StringFileInfo\\040904b0\\Unity Version"), (LPVOID *)&pvUnityVersion, &iUnityVersionLen))
	{
		delete[] data;
		return NULL;
	}

	wchar_t *ret = new wchar_t[iUnityVersionLen];
	memcpy(ret, pvUnityVersion, iUnityVersionLen * sizeof(wchar_t));
	delete[] data;
	return ret;
}

int main()
{
	const wchar_t *szFilename = L"C:\\Program Files\\Unity 2018.1.0b2\\Editor\\Unity.exe";

	wchar_t *unityVersion = GetUnityVersion(szFilename);

	if (unityVersion)
	{
		wprintf(L"%s\n", unityVersion);
		delete[] unityVersion;
	}
	else
	{
		printf("error\n");
	}


	return 0;
}
