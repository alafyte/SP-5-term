#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <Windows.h>
#include <wchar.h>
#include <string>
#include <conio.h>
#pragma comment(lib, "../x64/Debug/Dll_Lab11.lib")

#include "../DLL_Lab11/HT.h"


int main(int argc, char* argv[])
{
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

		HT::HTHANDLE* ht;
		ht = HT::Open(fileName);

		if (ht)
		{
			std::cout << "HT-Storage Created " << std::endl;
			std::wcout << "Filename: " << fileName << std::endl;
			std::cout << "SnapshotIntervalSec: " << ht->SecSnapshotInterval << std::endl;
			std::cout << "Capacity: " << ht->Capacity << std::endl;
			std::cout << "MaxKeyLength: " << ht->MaxKeyLength << std::endl;
			std::cout << "MaxPayloadLength: " << ht->MaxPayloadLength << std::endl;

			while (!_kbhit())
				SleepEx(0, TRUE);

			HT::Close(ht);
		}
		else
			throw "Error while opening a storage";
	}
	catch (const char* err)
	{
		std::cout << err << std::endl;
		return -1;
	}
	return 0;
}
