#pragma once
#include "pch.h"
#include "HT.h"
#define OS13HANDEL void*
#define IERR(s)    std::cout<<"error "<<s<<std::endl

static const GUID CLSID_CA =
{ 0x91b55c31, 0x81a3, 0x4c32, { 0x94, 0x48, 0xc9, 0x3d, 0xd2, 0xda, 0xac, 0x47 } };

namespace OS13
{
	OS13HANDEL Init();
	namespace Manipulator
	{
		HTHANDLE* Create(OS13HANDEL h, int capacity, int secSnapshotInterval, int maxKeyLength, int maxPayloadLength, const wchar_t* fileName);
		HTHANDLE* Open(OS13HANDEL h, const wchar_t* fileName, bool isMapFile = false);
		BOOL Snap(OS13HANDEL h, HTHANDLE* htHandle);
		BOOL Close(OS13HANDEL h, const HTHANDLE* htHandle);
	}
	namespace DataManipulator
	{
		Element* Get(OS13HANDEL h, HTHANDLE* htHandle, const Element* element);
		BOOL Insert(OS13HANDEL h, HTHANDLE* htHandle, const Element* element);
		BOOL Update(OS13HANDEL h, HTHANDLE* htHandle, const Element* oldElement, const void* newPayload, int newPayloadLength);
		BOOL Delete(OS13HANDEL h, HTHANDLE* htHandle, const Element* element);
	}
	namespace HTElement
	{
		Element* CreateElementGet(OS13HANDEL h, const void* key, int keyLength);
		Element* CreateElementInsert(OS13HANDEL h, const void* key, int keyLength, const void* payload, int payloadLength);
		Element* CreateElementUpdate(OS13HANDEL h, const Element* oldElement, const void* newPayload, int newPayloadLength);
	}
	namespace Utils
	{
		const char* getLastError(OS13HANDEL h, const HTHANDLE* htHandle);
		void print(OS13HANDEL h, const Element* element);
	}
	void Dispose(OS13HANDEL h);
}

