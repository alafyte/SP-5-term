#pragma comment(lib, "../x64/debug/OS10_HTAPI.lib")

#include "../OS10_HTAPI/pch.h"
#include "../OS10_HTAPI/HT.h"

using namespace std;

int main()
{
	HT::HTHANDLE* ht1 = nullptr;
	HT::HTHANDLE* ht2 = nullptr;

	try
	{
		cout << "--- ht1 ---" << endl;
		ht1 = HT::Create(1000, 3, 10, 256, L"./storage/HTexample.ht");
		if (ht1)
			cout << "-- create: success" << endl;
		else
			throw "-- create: error";

		cout << "ht1: " << ht1->Addr << endl;

		if (HT::Insert(ht1, new HT::Element("name", 4, "Anna", 4)))
			cout << "-- insert: success" << endl;
		else
			throw "-- insert: error";
	}
	catch (const char* msg)
	{
		cout << msg << endl;

		if (ht1 != nullptr)
			cout << HT::GetLastError(ht1) << endl;
	}

	try
	{
		cout << "\n--- ht2 ---" << endl;
		ht2 = HT::Open(L"./storage/HTexample.ht");
		if (ht2)
			cout << "-- open: success" << endl;
		else
			throw "-- open: error";

		cout << "ht2: " << ht2->Addr << endl;

		HT::Element* hte = HT::Get(ht1, new HT::Element("name", 4));
		if (hte)
			cout << "-- get: success" << endl;
		else
			throw "-- get: error";

		HT::print(hte);
	}
	catch (const char* msg)
	{
		cout << msg << endl;

		if (ht1 != nullptr)
			cout << HT::GetLastError(ht1) << endl;
	}

}

