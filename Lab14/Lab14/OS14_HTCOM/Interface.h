#pragma once
#include <objbase.h>
#include "HT.h"

// {22578C7B-D98C-4FF0-99B8-0B3ED7F61FC8}
static const GUID IID_IHTManipulator =
{ 0x22578c7b, 0xd98c, 0x4ff0, { 0x99, 0xb8, 0xb, 0x3e, 0xd7, 0xf6, 0x1f, 0xc8 } };



interface IHTManipulator :IUnknown
{
	STDMETHOD(Create(HTHANDLE** handle, int capacity, int secSnapshotInterval, int maxKeyLength, int maxPayloadLength, const wchar_t* HTUsersGroup, const wchar_t* fileName)) = 0;
	STDMETHOD(Open(HTHANDLE** handle, const wchar_t* fileName, bool isMapFile = false)) = 0;
	STDMETHOD(Open(HTHANDLE** handle, const wchar_t* HTUser, const wchar_t* HTPassword, const wchar_t* fileName, bool isMapFile = false)) = 0;
	STDMETHOD(Snap(BOOL& rc, HTHANDLE* htHandle)) = 0;
	STDMETHOD(Close(BOOL& rc,const HTHANDLE* htHandle)) = 0;
};


// {378C1F00-B395-458A-8F74-E1B124C2992B}
static const GUID IID_IHTDataManipulator =
{ 0x378c1f00, 0xb395, 0x458a, { 0x8f, 0x74, 0xe1, 0xb1, 0x24, 0xc2, 0x99, 0x2b } };




interface IHTDataManipulator :IUnknown
{
	STDMETHOD(Get(Element** resultElement, HTHANDLE* htHandle, const Element* element)) = 0;
	STDMETHOD(Insert(BOOL& rc, HTHANDLE* htHandle, const Element* element)) = 0;
	STDMETHOD(Update(BOOL& rc, HTHANDLE* htHandle, const Element* oldElement, const void* newPayload, int newPayloadLength)) = 0;
	STDMETHOD(Delete(BOOL& rc, HTHANDLE* htHandle, const Element* element)) = 0;
};

// {1EB43C55-8FEA-4DB1-8159-122E4617C45E}
static const GUID IID_IElement =
{ 0x1eb43c55, 0x8fea, 0x4db1, { 0x81, 0x59, 0x12, 0x2e, 0x46, 0x17, 0xc4, 0x5e } };



interface IElement :IUnknown
{
	STDMETHOD(CreateElementGet(Element** element, const void* key, int keyLength)) = 0;
	STDMETHOD(CreateElementInsert(Element** element, const void* key, int keyLength, const void* payload, int payloadLength)) = 0;
	STDMETHOD(CreateElementUpdate(Element** element, const Element* oldElement, const void* newPayload, int newPayloadLength)) = 0;
};

// {AEACFA12-EC8B-46E6-B193-9B6186B6DF77}
static const GUID IID_IHTUtil =
{ 0xaeacfa12, 0xec8b, 0x46e6, { 0xb1, 0x93, 0x9b, 0x61, 0x86, 0xb6, 0xdf, 0x77 } };



interface IHTUtil :IUnknown
{
	STDMETHOD(getLastError(const char** error, const HTHANDLE* htHandle)) = 0;
	STDMETHOD(print(const Element* element)) = 0;
};

