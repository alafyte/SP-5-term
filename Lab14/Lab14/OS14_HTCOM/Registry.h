#pragma once
#include <objbase.h>


// {0F147BBB-93BB-4969-BAEC-CEF082B19129}
static const GUID CLSID_CA =
{ 0xf147bbb, 0x93bb, 0x4969, { 0xba, 0xec, 0xce, 0xf0, 0x82, 0xb1, 0x91, 0x29 } };



extern HMODULE hRnaCA;

static LPCWSTR FNAME = L"RNA.OS14.HTCOM";
static LPCWSTR VINDX = L"RNA.OS14.1";
static LPCWSTR PRGID = L"RNA.OS14";

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