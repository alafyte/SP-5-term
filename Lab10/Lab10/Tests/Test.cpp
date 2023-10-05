#include "Test.h"

using namespace HT;

namespace Test
{
	BOOL Test1_Create()
	{
		HTHANDLE* ht = Create(100, 5, 20, 50, L"./storage/HTexample.ht");
		if (ht)
		{
			return true;
		}
		return false;
	}

	BOOL Test2_Insert()
	{
		std::string key1 = "testkey1";
		std::string data1 = "testdata1";

		Element* element1 = new Element(key1.c_str(), key1.length(), data1.c_str(), data1.length());
		HTHANDLE* ht = Open(L"./storage/HTexample.ht");

		Insert(ht, element1);
		if (Insert(ht, element1))
		{
			return false;
		}
		return true;
	}

	BOOL Test3_Get()
	{
		std::string key1 = "testkey1";
		std::string data1 = "testdata1";

		Element* element1 = new Element(key1.c_str(), key1.length(), data1.c_str(), data1.length());
		HTHANDLE* ht = Open(L"./storage/HTexample.ht");
		Element* foundElem = Get(ht, element1);


		if (foundElem && strcmp((char*)element1->key, (char*)foundElem->key) == 0 && strcmp((char*)element1->payload, (char*)foundElem->payload) == 0)
		{
			Close(ht);
			return true;
		}
		return false;
	}

	BOOL Test4_Delete()
	{
		std::string key1 = "testkey1";
		std::string data1 = "testdata1";

		Element* element1 = new Element(key1.c_str(), key1.length(), data1.c_str(), data1.length());
		HTHANDLE* ht = Open(L"./storage/HTexample.ht");

		HT::Delete(ht, element1);
		return HT::Delete(ht, element1);
	}

	BOOL Test5_Close()
	{
		HTHANDLE* ht = Open(L"./storage/HTexample.ht");
		return Close(ht);
	}
}