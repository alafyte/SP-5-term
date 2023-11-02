#pragma once
#include <objbase.h>


// {7433176A-CED8-466F-B454-632AECC776C5}
static const GUID CLSID_CA =
{ 0x7433176a, 0xced8, 0x466f, { 0xb4, 0x54, 0x63, 0x2a, 0xec, 0xc7, 0x76, 0xc5 } };

extern HMODULE hRnaCA;

static LPCWSTR FNAME = L"RNA.OS12.COM";
static LPCWSTR VINDX = L"RNA.OS12.1";
static LPCWSTR PRGID = L"RNA.OS12";

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