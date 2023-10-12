#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <Windows.h>
#include <wchar.h>
#include <string>
#pragma comment(lib, "../x64/Debug/Dll_Lab11.lib")

#include "../DLL_Lab11/HT.h"


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
		HT::HTHANDLE* HT;
		HT = HT::Create(capacity, snapshotIntervalSec, maxKeyLength, maxPayloadLength, fileName);
		if (HT == NULL)
			throw "Invalid handle";
		HT::Close(HT);
		std::cout << "HT-Storage Created " << std::endl;
		std::wcout << "Filepath: " << fileName << std::endl;
		std::cout << "SnapshotIntervalSec: " << snapshotIntervalSec << std::endl;
		std::cout << "Capacity: " << capacity << std::endl;
		std::cout << "MaxKeyLength: " << maxKeyLength << std::endl;
		std::cout << "MaxPayloadLength: " << maxPayloadLength << std::endl;
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