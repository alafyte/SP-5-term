#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <Windows.h>
#include <wchar.h>
#include <string>
#pragma comment(lib, "../x64/Debug/OS13_HTCOM_LIB.lib")

#include "../OS13_HTCOM_LIB/HT.h"
#include "../OS13_HTCOM_LIB/OS13.h"


int main(int argc, char* argv[])
{
	int capacity, snapshotIntervalSec, maxKeyLength, maxPayloadLength;
	wchar_t* fileName;

	try
	{
		if (argv[1] && argv[2] && argv[3] && argv[4] && argv[5])
		{
			capacity = std::stoi(argv[1]);
			snapshotIntervalSec = std::stoi(argv[2]);
			maxKeyLength = std::stoi(argv[3]);
			maxPayloadLength = std::stoi(argv[4]);

			const size_t cSize = strlen(argv[5]) + 1;
			wchar_t* wc = new wchar_t[cSize];
			mbstowcs(wc, argv[5], cSize);

			fileName = wc;
		}
		else
		{
			throw "Invalid command line arguments";
		}
		OS13HANDEL h1 = OS13::Init();
		HTHANDLE* HT = OS13::Manipulator::Create(h1, capacity, snapshotIntervalSec, maxKeyLength, maxPayloadLength, fileName);
		if (HT == NULL)
			throw "Invalid handle";

		OS13::Manipulator::Close(h1, HT);
		std::cout << "HT-Storage Created " << std::endl;
		std::wcout << "Filepath: " << fileName << std::endl;
		std::cout << "SnapshotIntervalSec: " << snapshotIntervalSec << std::endl;
		std::cout << "Capacity: " << capacity << std::endl;
		std::cout << "MaxKeyLength: " << maxKeyLength << std::endl;
		std::cout << "MaxPayloadLength: " << maxPayloadLength << std::endl;

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