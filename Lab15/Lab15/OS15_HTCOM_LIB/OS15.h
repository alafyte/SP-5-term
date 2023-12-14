#pragma once
#include "pch.h"
#include "HT.h"
#define OS15HANDEL void*
#define IERR(s)    std::cout<<"error "<<s<<std::endl

static const GUID CLSID_CA =
{ 0x5098001b, 0x4970, 0x4326, { 0x83, 0xf7, 0x7b, 0x7e, 0xf3, 0x1c, 0xea, 0xc7 } };

namespace OS15
{
	OS15HANDEL Init();
	namespace Manipulator
	{
		HTHANDLE* Create(OS15HANDEL h, int capacity, int secSnapshotInterval, int maxKeyLength, int maxPayloadLength, const wchar_t* HTUsersGroup, const wchar_t* fileName);
		HTHANDLE* Open(OS15HANDEL h, const wchar_t* fileName, bool isMapFile = false);
		HTHANDLE* Open(OS15HANDEL h, const wchar_t* HTUser, const wchar_t* HTPassword, const wchar_t* fileName, bool isMapFile = false);
		BOOL Snap(OS15HANDEL h, HTHANDLE* htHandle);
		BOOL Close(OS15HANDEL h, const HTHANDLE* htHandle);
	}
	namespace DataManipulator
	{
		Element* Get(OS15HANDEL h, HTHANDLE* htHandle, const Element* element);
		BOOL Insert(OS15HANDEL h, HTHANDLE* htHandle, const Element* element);
		BOOL Update(OS15HANDEL h, HTHANDLE* htHandle, const Element* oldElement, const void* newPayload, int newPayloadLength);
		BOOL Delete(OS15HANDEL h, HTHANDLE* htHandle, const Element* element);
	}
	namespace HTElement
	{
		Element* CreateElementGet(OS15HANDEL h, const void* key, int keyLength);
		Element* CreateElementInsert(OS15HANDEL h, const void* key, int keyLength, const void* payload, int payloadLength);
		Element* CreateElementUpdate(OS15HANDEL h, const Element* oldElement, const void* newPayload, int newPayloadLength);
	}
	namespace Utils
	{
		const char* getLastError(OS15HANDEL h, const HTHANDLE* htHandle);
		void print(OS15HANDEL h, const Element* element);
	}
	void Dispose(OS15HANDEL h);
}




