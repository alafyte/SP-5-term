#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <wchar.h>
#include <string>
#include <sstream>
#include <ctime>
#include <Windows.h>
#pragma comment(lib, "../x64/Debug/OS14_HTCOM_LIB.lib")

#include "../OS14_HTCOM_LIB/HT.h"
#include "../OS14_HTCOM_LIB/OS14.h"


int main(int argc, char* argv[])
{
	HANDLE hStopEvent = CreateEvent(NULL, TRUE, FALSE, L"STOP_HT");
	srand(time(0));
	wchar_t* fileName;
	wchar_t* username;
	wchar_t* password;
	try
	{
		OS14HANDEL h1 = OS14::Init();
		HTHANDLE* HT;

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

			HT = OS14::Manipulator::Open(h1, username, password, fileName, true);
		}
		else if (argc == 2)
		{
			const size_t cSize = strlen(argv[1]) + 1;
			wchar_t* wc = new wchar_t[cSize];
			mbstowcs(wc, argv[1], cSize);
			fileName = wc;
			HT = OS14::Manipulator::Open(h1, fileName, true);
		}
		else
		{
			throw "Invalid file name";
		}

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
			Element* el1 = OS14::HTElement::CreateElementInsert(h1, key.c_str(), key.length() + 1, "0", 2);
			if ((el = OS14::DataManipulator::Get(h1, HT, el1)) == NULL)
			{
				std::cout << OS14::Utils::getLastError(h1, HT) << std::endl;
			}
			else
			{
				OS14::Utils::print(h1, el);
				if (!OS14::DataManipulator::Delete(h1, HT, el1))
				{
					std::cout << OS14::Utils::getLastError(h1, HT) << std::endl;
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

		OS14::Dispose(h1);
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