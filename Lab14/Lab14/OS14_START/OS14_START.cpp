#define _CRT_SECURE_NO_WARNINGS
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
	HANDLE hStopEvent = CreateEvent(NULL, TRUE, FALSE, L"STOP_HT");
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

			ht = OS14::Manipulator::Open(h1, username, password, fileName);
		}
		else if (argc == 2)
		{
			const size_t cSize = strlen(argv[1]) + 1;
			wchar_t* wc = new wchar_t[cSize];
			mbstowcs(wc, argv[1], cSize);
			fileName = wc;
			ht = OS14::Manipulator::Open(h1, fileName);
		}
		else
		{
			throw "Invalid file name";
		}


		if (ht)
		{
			std::cout << "HT-Storage Created " << std::endl;
			std::wcout << "Filename: " << fileName << std::endl;
			std::cout << "SnapshotIntervalSec: " << ht->SecSnapshotInterval << std::endl;
			std::cout << "Capacity: " << ht->Capacity << std::endl;
			std::cout << "MaxKeyLength: " << ht->MaxKeyLength << std::endl;
			std::cout << "MaxPayloadLength: " << ht->MaxPayloadLength << std::endl;

			while (!_kbhit() && WaitForSingleObject(hStopEvent, 0) == WAIT_TIMEOUT)
				SleepEx(0, TRUE);

			OS14::Manipulator::Close(h1, ht);
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
