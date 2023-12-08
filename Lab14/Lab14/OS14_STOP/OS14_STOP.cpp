#define _CRT_SECURE_NO_WARNINGS
#include <Windows.h>
#include <iostream>
#include <Windows.h>
#include <wchar.h>
#include <string>
#include <conio.h>
#pragma comment(lib, "../x64/Debug/OS14_HTCOM_LIB.lib")

#include "../OS14_HTCOM_LIB/HT.h"
#include "../OS14_HTCOM_LIB/OS14.h"

int main(int argc, char* argv[])
{
	HANDLE hStopEvent = CreateEvent(NULL,
		TRUE,
		FALSE,
		L"STOP_HT");
	wchar_t* fileName;
	wchar_t* username;
	wchar_t* password;

	try
	{
		OS14HANDEL h1 = OS14::Init();
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

			ht = OS14::Manipulator::Open(h1, username, password, fileName, true);
		}
		else if (argc == 2)
		{
			const size_t cSize = strlen(argv[1]) + 1;
			wchar_t* wc = new wchar_t[cSize];
			mbstowcs(wc, argv[1], cSize);
			fileName = wc;
			ht = OS14::Manipulator::Open(h1, fileName, true);
		}
		else
		{
			throw "Invalid file name";
		}



		if (ht)
		{
			if (!OS14::Manipulator::Snap(h1, ht))
				throw "Error while Span in HT";

			SetEvent(hStopEvent);
		}
		else
			throw "Error while opening a storage";

		OS14::Dispose(h1);
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