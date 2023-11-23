#pragma once
#include <objbase.h>


// {91B55C31-81A3-4C32-9448-C93DD2DAAC47}
static const GUID CLSID_CA =
{ 0x91b55c31, 0x81a3, 0x4c32, { 0x94, 0x48, 0xc9, 0x3d, 0xd2, 0xda, 0xac, 0x47 } };


extern HMODULE hRnaCA;

static LPCWSTR FNAME = L"RNA.OS13.HTCOM";
static LPCWSTR VINDX = L"RNA.OS13.1";
static LPCWSTR PRGID = L"RNA.OS13";

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