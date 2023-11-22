// OS12_LIB.cpp : Defines the functions for the static library.
//

#include "pch.h"
#include "framework.h"
#include "OS12.h"
#include "Interface.h"

namespace OS12
{
	OS12HANDEL Init()
	{
		IUnknown* pIUnknown = NULL;
		CoInitialize(NULL);                        // инициализация библиотеки OLE32
		HRESULT hr0 = CoCreateInstance(CLSID_CA, NULL, CLSCTX_INPROC_SERVER, IID_IUnknown, (void**)&pIUnknown);
		if (SUCCEEDED(hr0))
		{
			std::cout << "CoCreateInstance succeeded" << std::endl;
			return pIUnknown;
		}
		else
		{
			std::cout << "CoCreateInstance error" << std::endl;
			throw (int)hr0;
		}
	}

	namespace Adder
	{
		double Add(OS12HANDEL h, double x, double y)
		{
			IAdder* pIAdder = nullptr;

			HRESULT hr0 = ((IUnknown*)h)->QueryInterface(IID_IAdder, (void**)&pIAdder);

			if (SUCCEEDED(hr0))
			{
				double z = 0.0;
				HRESULT hr1 = pIAdder->Add(x, y, z);
				if (!SUCCEEDED(hr1))
				{
					IERR("IAdder::Add");
					throw (int)hr1;
				}
				else
				{
					return z;
				}
			}
			else
			{
				IERR("IAdder");
				throw (int)hr0;
			}
		}

		double Sub(OS12HANDEL h, double x, double y)
		{
			IAdder* pIAdder = nullptr;
			HRESULT hr0 = ((IUnknown*)h)->QueryInterface(IID_IAdder, (void**)&pIAdder);
			if (SUCCEEDED(hr0))
			{
				double z = 0.0;
				HRESULT hr1 = pIAdder->Sub(x, y, z);

				if (!SUCCEEDED(hr1))
				{
					IERR("IAdder::Sub");
					throw (int)hr1;
				}
				else
				{
					return z;
				}
			}
			else
			{
				IERR("IAdder");
				throw (int)hr0;
			}
		}
	}

	namespace Multiplier
	{
		double Mul(OS12HANDEL h, double x, double y)
		{
			IMultiplier* pMultiplier = nullptr;

			HRESULT hr0 = ((IUnknown*)h)->QueryInterface(IID_IMultiplier, (void**)&pMultiplier);
			if (SUCCEEDED(hr0))
			{
				double z = 0.0;
				HRESULT hr1 = pMultiplier->Mul(x, y, z);
				if (!SUCCEEDED(hr1))
				{
					IERR("IMultiplier::Mul");
					throw (int)hr1;
				}
				else
				{
					return z;
				}
			}
			else
			{
				IERR("IMultiplier");
				throw (int)hr0;
			}
		}

		double Div(OS12HANDEL h, double x, double y)
		{
			IMultiplier* pMultiplier = nullptr;

			HRESULT hr0 = ((IUnknown*)h)->QueryInterface(IID_IMultiplier, (void**)&pMultiplier);
			if (SUCCEEDED(hr0))
			{
				double z = 0.0;
				HRESULT hr1 = pMultiplier->Div(x, y, z);

				if (!SUCCEEDED(hr1))
				{
					IERR("IMultiplier::Div");
					throw (int)hr1;
				}
				else
				{
					return z;
				}
			}
			else
			{
				IERR("IMultiplier");
				throw (int)hr0;
			}
		}
	}

	void Dispose(OS12HANDEL h)
	{
		((IUnknown*)h)->Release();
		CoFreeUnusedLibraries();
	}
}

