#define _CRT_SECURE_NO_WARNINGS
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
	HANDLE hStopEvent = CreateEvent(NULL, TRUE, FALSE, L"STOP_HT");
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
		ht = OS13::Manipulator::Open(h1, fileName);

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

			OS13::Manipulator::Close(h1, ht);
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
