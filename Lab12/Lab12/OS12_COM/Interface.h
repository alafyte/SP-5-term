#pragma once
#include <objbase.h>

// {874DD560-A2D9-4308-9085-78EFB7110174}
static const GUID IID_IAdder =
{ 0x874dd560, 0xa2d9, 0x4308, { 0x90, 0x85, 0x78, 0xef, 0xb7, 0x11, 0x1, 0x74 } };


interface IAdder :IUnknown
{
	STDMETHOD(Add(const double x, const double y, double& z)) = 0;
	STDMETHOD(Sub(const double x, const double y, double& z)) = 0;
};

// {982F3A31-6D12-4B29-90A0-90F2AFE2ECCE}
static const GUID IID_IMultiplier =
{ 0x982f3a31, 0x6d12, 0x4b29, { 0x90, 0xa0, 0x90, 0xf2, 0xaf, 0xe2, 0xec, 0xce } };



interface IMultiplier :IUnknown 
{
	STDMETHOD(Mul(const double x, const double y, double& z)) = 0;
	STDMETHOD(Div(const double x, const double y, double& z)) = 0;
};