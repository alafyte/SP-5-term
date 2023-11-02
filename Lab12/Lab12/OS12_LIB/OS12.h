#pragma once
#define OS12HANDEL void*
#define IERR(s)    std::cout<<"error "<<s<<std::endl

static const GUID CLSID_CA =
{ 0x7433176a, 0xced8, 0x466f, { 0xb4, 0x54, 0x63, 0x2a, 0xec, 0xc7, 0x76, 0xc5 } };

namespace OS12
{
	OS12HANDEL Init();
	//   if CoCreateInstance(... IID_Unknown)!= succesfull --> throw (int)HRESULT  
	namespace Adder
	{
		double Add(OS12HANDEL h, double x, double y);        // return x+y
		//  if QueryInteface(IID_IAdder) != succesfull -->  throw (int)HRESULT     
		double Sub(OS12HANDEL h, double x, double y);        // return x-y
		//  if QueryInteface(IID_IAdder) != succesfull -->  throw (int)HRESULT
	}
	namespace Multiplier
	{
		double Mul(OS12HANDEL h, double x, double y);        // return x*y
		//  if QueryInteface(IID_IMultiplier) != succesfull -->  throw (int)HRESULT 
		double Div(OS12HANDEL h, double x, double y);        // return x/y
		//  if QueryInteface(IID_IMultiplier) != succesfull -->  throw (int)HRESULT 
	}
	void Dispose(OS12HANDEL h);
}

