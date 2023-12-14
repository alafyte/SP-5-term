#pragma once
#include <objbase.h>
#include "HT.h"

// {D4DCBBF7-06B2-4DE3-BE9C-9FEE6F58CE49}
static const GUID IID_IHTManipulator =
{ 0xd4dcbbf7, 0x6b2, 0x4de3, { 0xbe, 0x9c, 0x9f, 0xee, 0x6f, 0x58, 0xce, 0x49 } };



interface IHTManipulator :IUnknown
{
	STDMETHOD(Create(HTHANDLE** handle, int capacity, int secSnapshotInterval, int maxKeyLength, int maxPayloadLength, const wchar_t* HTUsersGroup, const wchar_t* fileName)) = 0;
	STDMETHOD(Open(HTHANDLE** handle, const wchar_t* fileName, bool isMapFile = false)) = 0;
	STDMETHOD(Open(HTHANDLE** handle, const wchar_t* HTUser, const wchar_t* HTPassword, const wchar_t* fileName, bool isMapFile = false)) = 0;
	STDMETHOD(Snap(BOOL& rc, HTHANDLE* htHandle)) = 0;
	STDMETHOD(Close(BOOL& rc,const HTHANDLE* htHandle)) = 0;
};


// {17DF1D09-047C-4E41-ADE5-42B34BF73605}
static const GUID IID_IHTDataManipulator =
{ 0x17df1d09, 0x47c, 0x4e41, { 0xad, 0xe5, 0x42, 0xb3, 0x4b, 0xf7, 0x36, 0x5 } };



interface IHTDataManipulator :IUnknown
{
	STDMETHOD(Get(Element** resultElement, HTHANDLE* htHandle, const Element* element)) = 0;
	STDMETHOD(Insert(BOOL& rc, HTHANDLE* htHandle, const Element* element)) = 0;
	STDMETHOD(Update(BOOL& rc, HTHANDLE* htHandle, const Element* oldElement, const void* newPayload, int newPayloadLength)) = 0;
	STDMETHOD(Delete(BOOL& rc, HTHANDLE* htHandle, const Element* element)) = 0;
};


// {2FB232EF-884E-4D46-A7F5-BD14F8882FE3}
static const GUID IID_IElement =
{ 0x2fb232ef, 0x884e, 0x4d46, { 0xa7, 0xf5, 0xbd, 0x14, 0xf8, 0x88, 0x2f, 0xe3 } };



interface IElement :IUnknown
{
	STDMETHOD(CreateElementGet(Element** element, const void* key, int keyLength)) = 0;
	STDMETHOD(CreateElementInsert(Element** element, const void* key, int keyLength, const void* payload, int payloadLength)) = 0;
	STDMETHOD(CreateElementUpdate(Element** element, const Element* oldElement, const void* newPayload, int newPayloadLength)) = 0;
};

// {9B833795-156C-40A5-9B76-151C856A9954}
static const GUID IID_IHTUtil =
{ 0x9b833795, 0x156c, 0x40a5, { 0x9b, 0x76, 0x15, 0x1c, 0x85, 0x6a, 0x99, 0x54 } };


interface IHTUtil :IUnknown
{
	STDMETHOD(getLastError(const char** error, const HTHANDLE* htHandle)) = 0;
	STDMETHOD(print(const Element* element)) = 0;
};

