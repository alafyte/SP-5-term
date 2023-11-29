#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <wchar.h>
#include <string>
#include <sstream>
#include <ctime>
#include <Windows.h>
#pragma comment(lib, "../x64/Debug/OS13_HTCOM_LIB.lib")

#include "../OS13_HTCOM_LIB/HT.h"
#include "../OS13_HTCOM_LIB/OS13.h"


int main(int argc, char* argv[])
{
	HANDLE hStopEvent = CreateEvent(NULL, TRUE, FALSE, L"STOP_HT");
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
		OS13HANDEL h1 = OS13::Init();

		HTHANDLE* HT;
		HT = OS13::Manipulator::Open(h1, fileName, true);

		if (HT == NULL)
			throw "Invalid handle";

		while (WaitForSingleObject(hStopEvent, 0) == WAIT_TIMEOUT)
		{
			int numberKey = rand() % 50 + 1;
			std::string key;
			std::stringstream convert;
			convert << numberKey;
			key = convert.str();
			std::cout << key << ' ' << std::endl;
			Element* el;
			Element* el1 = OS13::HTElement::CreateElementInsert(h1, key.c_str(), key.length() + 1, "0", 2);
			if ((el = OS13::DataManipulator::Get(h1, HT, el1)) == NULL)
			{
				std::cout << OS13::Utils::getLastError(h1, HT) << std::endl;
			}
			else
			{
				OS13::Utils::print(h1, el);
				if (!OS13::DataManipulator::Delete(h1, HT, el1))
				{
					std::cout << OS13::Utils::getLastError(h1, HT) << std::endl;
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

		OS13::Dispose(h1);
	}
	catch (const char* err)
	{
		std::cout << err << std::endl;
		return 1;
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