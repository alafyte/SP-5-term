#pragma once
#include <objbase.h>
#include "HT.h"

// {806658C7-51D8-45C2-A6FD-746686A5ED55}
static const GUID IID_IHTManipulator =
{ 0x806658c7, 0x51d8, 0x45c2, { 0xa6, 0xfd, 0x74, 0x66, 0x86, 0xa5, 0xed, 0x55 } };



interface IHTManipulator :IUnknown
{
	STDMETHOD(Create(HTHANDLE** handle, int capacity, int secSnapshotInterval, int maxKeyLength, int maxPayloadLength, const wchar_t* fileName)) = 0;
	STDMETHOD(Open(HTHANDLE** handle, const wchar_t* fileName, bool isMapFile = false)) = 0;
	STDMETHOD(Snap(BOOL& rc, HTHANDLE* htHandle)) = 0;
	STDMETHOD(Close(BOOL& rc, const HTHANDLE* htHandle)) = 0;
};


// {7D7D2F9A-A049-4806-AEA3-166F402008A5}
static const GUID IID_IHTDataManipulator =
{ 0x7d7d2f9a, 0xa049, 0x4806, { 0xae, 0xa3, 0x16, 0x6f, 0x40, 0x20, 0x8, 0xa5 } };



interface IHTDataManipulator :IUnknown
{
	STDMETHOD(Get(Element** resultElement, HTHANDLE* htHandle, const Element* element)) = 0;
	STDMETHOD(Insert(BOOL& rc, HTHANDLE* htHandle, const Element* element)) = 0;
	STDMETHOD(Update(BOOL& rc, HTHANDLE* htHandle, const Element* oldElement, const void* newPayload, int newPayloadLength)) = 0;
	STDMETHOD(Delete(BOOL& rc, HTHANDLE* htHandle, const Element* element)) = 0;
};

// {FCBDD4CD-64BE-447C-937F-5A2543960A6A}
static const GUID IID_IElement =
{ 0xfcbdd4cd, 0x64be, 0x447c, { 0x93, 0x7f, 0x5a, 0x25, 0x43, 0x96, 0xa, 0x6a } };


interface IElement :IUnknown
{
	STDMETHOD(CreateElementGet(Element** element, const void* key, int keyLength)) = 0;
	STDMETHOD(CreateElementInsert(Element** element, const void* key, int keyLength, const void* payload, int payloadLength)) = 0;
	STDMETHOD(CreateElementUpdate(Element** element, const Element* oldElement, const void* newPayload, int newPayloadLength)) = 0;
};

// {B304CBAD-97E8-4CC1-9ACC-AB082B7DF1E3}
static const GUID IID_IHTUtil =
{ 0xb304cbad, 0x97e8, 0x4cc1, { 0x9a, 0xcc, 0xab, 0x8, 0x2b, 0x7d, 0xf1, 0xe3 } };


interface IHTUtil :IUnknown
{
	STDMETHOD(getLastError(const char** error, const HTHANDLE* htHandle)) = 0;
	STDMETHOD(print(const Element* element)) = 0;
};

