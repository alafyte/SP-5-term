#define _CRT_SECURE_NO_WARNINGS
#include <Windows.h>
#include <iostream>
#include <Windows.h>
#include <wchar.h>
#include <string>
#include <conio.h>
#include "sddl.h"
#pragma comment(lib, "../x64/Debug/OS15_HTCOM_LIB.lib")

#include "../OS15_HTCOM_LIB/HT.h"
#include "../OS15_HTCOM_LIB/OS15.h"


SECURITY_ATTRIBUTES getSecurityAttributes();
HANDLE createStopEvent(const wchar_t* stopEventName);

int main(int argc, char* argv[])
{
	HANDLE hStopEvent;
	wchar_t* fileName;
	wchar_t* username;
	wchar_t* password;

	try
	{
		OS15HANDEL h1 = OS15::Init();
		HTHANDLE* ht;

		if (argc == 4)
		{
			size_t cSize = strlen(argv[1]) + 1;
			wchar_t* wc = new wchar_t[cSize];
			mbstowcs(wc, argv[1], cSize);
			fileName = wc;

			cSize = strlen(argv[2]) + 1;
			wc = new wchar_t[cSize];
			mbstowcs(wc, argv[2], cSize);
			username = wc;

			cSize = strlen(argv[3]) + 1;
			wc = new wchar_t[cSize];
			mbstowcs(wc, argv[3], cSize);
			password = wc;

			ht = OS15::Manipulator::Open(h1, username, password, fileName, true);

			hStopEvent = createStopEvent(fileName);
		}
		else if (argc == 2)
		{
			const size_t cSize = strlen(argv[1]) + 1;
			wchar_t* wc = new wchar_t[cSize];
			mbstowcs(wc, argv[1], cSize);
			fileName = wc;
			ht = OS15::Manipulator::Open(h1, fileName, true);

			hStopEvent = createStopEvent(fileName);
		}
		else
		{
			throw "Invalid file name";
		}



		if (ht)
		{
			if (!OS15::Manipulator::Snap(h1, ht))
				throw "Error while Snap in HT";

			SetEvent(hStopEvent);
		}
		else
			throw "Error while opening a storage";

		OS15::Dispose(h1);
	}
	catch (const char* err)
	{
		std::cout << err << std::endl;
		return -1;
	}
	catch (int err)
	{
		std::cout << "Error code: " << err << std::endl;
		return -1;
	}
	catch (const std::exception&)
	{
		std::cout << "An error has occurred. Check settings and try again" << std::endl;
		return -1;
	}

	return 0;
}


SECURITY_ATTRIBUTES getSecurityAttributes()
{
	const wchar_t* sdd = L"D:"
		L"(D;OICI;GA;;;BG)" //Deny guests
		L"(D;OICI;GA;;;AN)" //Deny anonymous
		L"(A;OICI;GA;;;AU)" //Allow read, write and execute for Users
		L"(A;OICI;GA;;;BA)"; //Allow all for Administrators
	SECURITY_ATTRIBUTES SA;
	ZeroMemory(&SA, sizeof(SA));
	SA.nLength = sizeof(SA);
	ConvertStringSecurityDescriptorToSecurityDescriptor(
		sdd,
		SDDL_REVISION_1,
		&SA.lpSecurityDescriptor,
		NULL);

	return SA;
}

HANDLE createStopEvent(const wchar_t* stopEventName)
{
	std::wstring closeEventName = L"Global\\"; closeEventName += stopEventName; closeEventName += L"-stopEvent";
	SECURITY_ATTRIBUTES SA = getSecurityAttributes();

	HANDLE hStopEvent = CreateEvent(
		&SA,
		TRUE, //FALSE - автоматический сброс; TRUE - ручной
		FALSE,
		closeEventName.c_str());

	return hStopEvent;
}