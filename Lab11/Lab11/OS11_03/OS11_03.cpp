﻿#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <wchar.h>
#include <string>
#include <sstream>
#include <ctime>
#include <Windows.h>
#pragma comment(lib, "../x64/Debug/Dll_Lab11.lib")

#include "../DLL_Lab11/HT.h"


int main(int argc, char* argv[])
{
	srand(time(0));
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
		std::wcout << "filename: " << fileName << std::endl;
		HT::HTHANDLE* HT;
		HT = HT::Open(fileName, true);
		if (HT == NULL)
			throw "Invalid handle";

		while (true)
		{
			int numberKey = rand() % 50 + 1;
			std::string key;
			std::stringstream convert;
			convert << numberKey;
			key = convert.str();
			std::cout << key << ' ' << std::endl;
			HT::Element* el;
			HT::Element* el1 = new HT::Element(key.c_str(), key.length() + 1, "0", 2);
			if ((el = HT::Get(HT, el1)) == NULL)
			{
				std::cout << HT::getLastError(HT) << std::endl;
			}
			else
			{
				HT::print(el);
				if (!HT::Delete(HT, el1))
				{
					std::cout << HT::getLastError(HT) << std::endl;
				}
				else 
				{
					std::cout << "DELETE SUCCESS" << std::endl;
				}
			}
			Sleep(1000);
			delete el;
			delete el1;
		}

	}
	catch (const char* err) 
	{
		std::cout << err << std::endl;
		return 1;
	}
	return 0;
}