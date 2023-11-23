#define _CRT_SECURE_NO_WARNINGS
#include <Windows.h>
#include <iostream>
#include <Windows.h>
#include <wchar.h>
#include <string>
#include <conio.h>
#pragma comment(lib, "../x64/Debug/OS13_HTCOM_LIB.lib")

#include "../OS13_HTCOM_LIB/HT.h"
#include "../OS13_HTCOM_LIB/OS13.h"

int main(int argc, char* argv[])
{
	HANDLE hStopEvent = CreateEvent(NULL,
		TRUE,
		FALSE,
		L"STOP_HT");
	wchar_t* fileName;
	try
	{
		if (argv[1])
		{
			const size_t cSize = strlen(argv[1]) + 1;
			wchar_t* wc = new wchar_t[cSize];
			mbstowcs(wc, argv[1], cSize);
			fileName = wc;
		}
		else
		{
			throw "Invalid file name";
		}

		OS13HANDEL h1 = OS13::Init();
		HTHANDLE* ht;
		ht = OS13::Manipulator::Open(h1, fileName, true);

		if (ht)
		{
			if (!OS13::Manipulator::Snap(h1, ht))
				throw "Error while Span in HT";

			SetEvent(hStopEvent);
		}
		else
			throw "Error while opening a storage";

		OS13::Dispose(h1);
	}
	catch (const char* err)
	{
		std::cout << err << std::endl;
		return -1;
	}
	catch (const std::exception&)
	{
		std::cout << "Произошла ошибка. Проверьте параметры и повторите попытку" << std::endl;
		return -1;
	}

	return 0;
}