#pragma once
#include "pch.h"
#include "HT.h"
#define OS14HANDEL void*
#define IERR(s)    std::cout<<"error "<<s<<std::endl

static const GUID CLSID_CA =
{ 0xf147bbb, 0x93bb, 0x4969, { 0xba, 0xec, 0xce, 0xf0, 0x82, 0xb1, 0x91, 0x29 } };

namespace OS14
{
	OS14HANDEL Init();
	namespace Manipulator
	{
		HTHANDLE* Create(OS14HANDEL h, int capacity, int secSnapshotInterval, int maxKeyLength, int maxPayloadLength, const wchar_t* HTUsersGroup, const wchar_t* fileName);
		HTHANDLE* Open(OS14HANDEL h, const wchar_t* fileName, bool isMapFile = false);
		HTHANDLE* Open(OS14HANDEL h, const wchar_t* HTUser, const wchar_t* HTPassword, const wchar_t* fileName, bool isMapFile = false);
		BOOL Snap(OS14HANDEL h, HTHANDLE* htHandle);
		BOOL Close(OS14HANDEL h, const HTHANDLE* htHandle);
	}
	namespace DataManipulator
	{
		Element* Get(OS14HANDEL h, HTHANDLE* htHandle, const Element* element);
		BOOL Insert(OS14HANDEL h, HTHANDLE* htHandle, const Element* element);
		BOOL Update(OS14HANDEL h, HTHANDLE* htHandle, const Element* oldElement, const void* newPayload, int newPayloadLength);
		BOOL Delete(OS14HANDEL h, HTHANDLE* htHandle, const Element* element);
	}
	namespace HTElement
	{
		Element* CreateElementGet(OS14HANDEL h, const void* key, int keyLength);
		Element* CreateElementInsert(OS14HANDEL h, const void* key, int keyLength, const void* payload, int payloadLength);
		Element* CreateElementUpdate(OS14HANDEL h, const Element* oldElement, const void* newPayload, int newPayloadLength);
	}
	namespace Utils
	{
		const char* getLastError(OS14HANDEL h, const HTHANDLE* htHandle);
		void print(OS14HANDEL h, const Element* element);
	}
	void Dispose(OS14HANDEL h);
}

