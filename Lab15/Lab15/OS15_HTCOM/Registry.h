#pragma once
#include <objbase.h>


// {5098001B-4970-4326-83F7-7B7EF31CEAC7}
static const GUID CLSID_CA =
{ 0x5098001b, 0x4970, 0x4326, { 0x83, 0xf7, 0x7b, 0x7e, 0xf3, 0x1c, 0xea, 0xc7 } };




extern HMODULE hRnaCA;

static LPCWSTR FNAME = L"RNA.OS15.HTCOM";
static LPCWSTR VINDX = L"RNA.OS15.1";
static LPCWSTR PRGID = L"RNA.OS15";

STDAPI DllInstall(BOOL b, PCWSTR s);
STDAPI DllRegisterServer();
STDAPI DllUnregisterServer();


HRESULT RegisterServer(HMODULE hModule,            // DLL module handle
	const CLSID& clsid,         // Class ID
	const WCHAR* szFriendlyName, // Friendly Name
	const WCHAR* szVerIndProgID, // Programmatic
	const WCHAR* szProgID);     //   IDs

HRESULT UnregisterServer(const CLSID& clsid,
	const WCHAR* szVerIndProgID,
	const WCHAR* szProgID);