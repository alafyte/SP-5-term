#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <wchar.h>
#include <string>
#include <sstream>
#include <ctime>
#include <Windows.h>
#include "sddl.h"
#pragma comment(lib, "../x64/Debug/OS15_HTCOM_LIB.lib")

#include "../OS15_HTCOM_LIB/HT.h"
#include "../OS15_HTCOM_LIB/OS15.h"


SECURITY_ATTRIBUTES getSecurityAttributes();
HANDLE createStopEvent(const wchar_t* stopEventName);

int main(int argc, char* argv[])
{
	HANDLE hStopEvent;
	srand(time(0));
	wchar_t* fileName;
	wchar_t* username;
	wchar_t* password;
	try
	{
		OS15HANDEL h1 = OS15::Init();
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

			HT = OS15::Manipulator::Open(h1, username, password, fileName, true);
			hStopEvent = createStopEvent(fileName);
		}
		else if (argc == 2)
		{
			const size_t cSize = strlen(argv[1]) + 1;
			wchar_t* wc = new wchar_t[cSize];
			mbstowcs(wc, argv[1], cSize);
			fileName = wc;
			HT = OS15::Manipulator::Open(h1, fileName, true);
			hStopEvent = createStopEvent(fileName);
		}
		else
		{
			throw "Invalid file name";
		}

		if (HT == NULL)
		{
			throw "Invalid handle";
		}

		while (WaitForSingleObject(hStopEvent, 0) == WAIT_TIMEOUT)
		{
			int numberKey = rand() % 50 + 1;
			std::string key;
			std::stringstream convert;
			convert << numberKey;
			key = convert.str();
			std::cout << key << ' ' << std::endl;
			Element* el;
			Element* el1 = OS15::HTElement::CreateElementGet(h1, key.c_str(), key.length() + 1);
			Element* el2;
			if ((el = OS15::DataManipulator::Get(h1, HT, el1)) == NULL)
			{
				std::cout << OS15::Utils::getLastError(h1, HT) << std::endl;
			}
			else
			{
				OS15::Utils::print(h1, el);
				std::stringstream ss;
				int num;
				ss << *(char*)el->payload;
				ss >> num;
				int newNum = num + 1;
				std::cout << "old payload: " << *(char*)el->payload << " new value: " << newNum << std::endl;
				std::string payload;
				std::stringstream payloadConvert;
				payloadConvert << newNum;
				payload = payloadConvert.str();

				el2 = OS15::HTElement::CreateElementInsert(h1, key.c_str(), key.length() + 1, payload.c_str(), payload.length() + 1);

				if (!OS15::DataManipulator::Update(h1, HT, el1, el2->payload, el2->payloadLength))
				{
					std::cout << OS15::Utils::getLastError(h1, HT) << std::endl;
				}
				else
				{
					std::cout << "UPDATE SUCCESS" << std::endl;
				}
				if ((el = OS15::DataManipulator::Get(h1, HT, el2)) == NULL)
				{
					std::cout << OS15::Utils::getLastError(h1, HT) << std::endl;
				}
				delete el2;
			}
			Sleep(1000);
			delete el;
		}
		OS15::Dispose(h1);
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


SECURITY_ATTRIBUTES getSecurityAttributes()
{
	const wchar_t* sdd = L"D:"
		L"(D;OICI;GA;;;BG)" //Deny guests
		L"(D;OICI;GA;;;AN)" //Deny anonymous
		L"(A;OICI;GA;;;AU)" //Allow read, write and execute for Users
		L"(A;OICI;GA;;;BA)"; //Allow all for Administrators
	SECURITY_ATTRIBUTES SA;
	ZeroMemory(&SA, sizeof(SA));
	SA.nLength = sizeof(SA);
	ConvertStringSecurityDescriptorToSecurityDescriptor(
		sdd,
		SDDL_REVISION_1,
		&SA.lpSecurityDescriptor,
		NULL);

	return SA;
}

HANDLE createStopEvent(const wchar_t* stopEventName)
{
	std::wstring closeEventName = L"Global\\"; closeEventName += stopEventName; closeEventName += L"-stopEvent";
	SECURITY_ATTRIBUTES SA = getSecurityAttributes();

	HANDLE hStopEvent = CreateEvent(
		&SA,
		TRUE, //FALSE - автоматический сброс; TRUE - ручной
		FALSE,
		closeEventName.c_str());

	return hStopEvent;
}