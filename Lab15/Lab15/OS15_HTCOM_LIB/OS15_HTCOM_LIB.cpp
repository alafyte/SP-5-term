// OS14_LIB.cpp : Defines the functions for the static library.
//
#include "pch.h"
#include "framework.h"
#include "OS15.h"
#include "Interface.h"

namespace OS15
{
	OS15HANDEL Init()
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

	namespace Manipulator
	{
		HTHANDLE* Create(OS15HANDEL h, int capacity, int secSnapshotInterval, int maxKeyLength, int maxPayloadLength, const wchar_t* HTUsersGroup, const wchar_t* fileName)
		{
			IHTManipulator* pIManipulator = nullptr;
			HRESULT hr0 = ((IUnknown*)h)->QueryInterface(IID_IHTManipulator, (void**)&pIManipulator);

			if (SUCCEEDED(hr0))
			{
				HTHANDLE* ht;
				HRESULT hr1 = pIManipulator->Create(&ht, capacity, secSnapshotInterval, maxKeyLength, maxPayloadLength, HTUsersGroup, fileName);
				if (!SUCCEEDED(hr1))
				{
					IERR("IHTManipulator::Create");
					throw (int)hr1;
				}
				else
				{
					return ht;
				}
			}
			else
			{
				IERR("IHTManipulator");
				throw (int)hr0;
			}
		}

		HTHANDLE* Open(OS15HANDEL h, const wchar_t* fileName, bool isMapFile)
		{
			IHTManipulator* pIManipulator = nullptr;
			HRESULT hr0 = ((IUnknown*)h)->QueryInterface(IID_IHTManipulator, (void**)&pIManipulator);

			if (SUCCEEDED(hr0))
			{
				HTHANDLE* ht;
				HRESULT hr1 = pIManipulator->Open(&ht, fileName, isMapFile);
				if (!SUCCEEDED(hr1))
				{
					IERR("IHTManipulator::Open");
					throw (int)hr1;
				}
				else
				{
					return ht;
				}
			}
			else
			{
				IERR("IHTManipulator");
				throw (int)hr0;
			}
		}

		HTHANDLE* Open(OS15HANDEL h, const wchar_t* HTUser, const wchar_t* HTPassword, const wchar_t* fileName, bool isMapFile)
		{
			IHTManipulator* pIManipulator = nullptr;
			HRESULT hr0 = ((IUnknown*)h)->QueryInterface(IID_IHTManipulator, (void**)&pIManipulator);

			if (SUCCEEDED(hr0))
			{
				HTHANDLE* ht;
				HRESULT hr1 = pIManipulator->Open(&ht, HTUser, HTPassword, fileName, isMapFile);
				if (!SUCCEEDED(hr1))
				{
					IERR("IHTManipulator::Open");
					throw (int)hr1;
				}
				else
				{
					return ht;
				}
			}
			else
			{
				IERR("IHTManipulator");
				throw (int)hr0;
			}
		}

		BOOL Snap(OS15HANDEL h, HTHANDLE* htHandle)
		{
			IHTManipulator* pIManipulator = nullptr;
			HRESULT hr0 = ((IUnknown*)h)->QueryInterface(IID_IHTManipulator, (void**)&pIManipulator);

			if (SUCCEEDED(hr0))
			{
				BOOL rc;
				HRESULT hr1 = pIManipulator->Snap(rc, htHandle);
				if (!SUCCEEDED(hr1))
				{
					IERR("IHTManipulator::Snap");
					throw (int)hr1;
				}
				else
				{
					return rc;
				}
			}
			else
			{
				IERR("IHTManipulator");
				throw (int)hr0;
			}
		}

		BOOL Close(OS15HANDEL h, const HTHANDLE* htHandle)
		{
			IHTManipulator* pIManipulator = nullptr;
			HRESULT hr0 = ((IUnknown*)h)->QueryInterface(IID_IHTManipulator, (void**)&pIManipulator);

			if (SUCCEEDED(hr0))
			{
				BOOL rc;
				HRESULT hr1 = pIManipulator->Close(rc, htHandle);
				if (!SUCCEEDED(hr1))
				{
					IERR("IHTManipulator::Close");
					throw (int)hr1;
				}
				else
				{
					return rc;
				}
			}
			else
			{
				IERR("IHTManipulator");
				throw (int)hr0;
			}
		}
	}

	namespace DataManipulator
	{
		Element* Get(OS15HANDEL h, HTHANDLE* htHandle, const Element* element)
		{
			IHTDataManipulator* pIDataManipulator = nullptr;
			HRESULT hr0 = ((IUnknown*)h)->QueryInterface(IID_IHTDataManipulator, (void**)&pIDataManipulator);

			if (SUCCEEDED(hr0))
			{
				Element* el;
				HRESULT hr1 = pIDataManipulator->Get(&el, htHandle, element);
				if (!SUCCEEDED(hr1))
				{
					IERR("IHTDataManipulator::Get");
					throw (int)hr1;
				}
				else
				{
					return el;
				}
			}
			else
			{
				IERR("IHTDataManipulator");
				throw (int)hr0;
			}
		}

		BOOL Insert(OS15HANDEL h, HTHANDLE* htHandle, const Element* element)
		{
			IHTDataManipulator* pIDataManipulator = nullptr;
			HRESULT hr0 = ((IUnknown*)h)->QueryInterface(IID_IHTDataManipulator, (void**)&pIDataManipulator);

			if (SUCCEEDED(hr0))
			{
				BOOL rc;
				HRESULT hr1 = pIDataManipulator->Insert(rc, htHandle, element);
				if (!SUCCEEDED(hr1))
				{
					IERR("IHTDataManipulator::Insert");
					throw (int)hr1;
				}
				else
				{
					return rc;
				}
			}
			else
			{
				IERR("IHTDataManipulator");
				throw (int)hr0;
			}
		}

		BOOL Update(OS15HANDEL h, HTHANDLE* htHandle, const Element* oldElement, const void* newPayload, int newPayloadLength)
		{
			IHTDataManipulator* pIDataManipulator = nullptr;
			HRESULT hr0 = ((IUnknown*)h)->QueryInterface(IID_IHTDataManipulator, (void**)&pIDataManipulator);

			if (SUCCEEDED(hr0))
			{
				BOOL rc;
				HRESULT hr1 = pIDataManipulator->Update(rc, htHandle, oldElement, newPayload, newPayloadLength);
				if (!SUCCEEDED(hr1))
				{
					IERR("IHTDataManipulator::Update");
					throw (int)hr1;
				}
				else
				{
					return rc;
				}
			}
			else
			{
				IERR("IHTDataManipulator");
				throw (int)hr0;
			}
		}

		BOOL Delete(OS15HANDEL h, HTHANDLE* htHandle, const Element* element)
		{
			IHTDataManipulator* pIDataManipulator = nullptr;
			HRESULT hr0 = ((IUnknown*)h)->QueryInterface(IID_IHTDataManipulator, (void**)&pIDataManipulator);

			if (SUCCEEDED(hr0))
			{
				BOOL rc;
				HRESULT hr1 = pIDataManipulator->Delete(rc, htHandle, element);
				if (!SUCCEEDED(hr1))
				{
					IERR("IHTDataManipulator::Delete");
					throw (int)hr1;
				}
				else
				{
					return rc;
				}
			}
			else
			{
				IERR("IHTDataManipulator");
				throw (int)hr0;
			}
		}
	}

	namespace HTElement
	{
		Element* CreateElementGet(OS15HANDEL h, const void* key, int keyLength)
		{
			IElement* pIElement = nullptr;
			HRESULT hr0 = ((IUnknown*)h)->QueryInterface(IID_IElement, (void**)&pIElement);

			if (SUCCEEDED(hr0))
			{
				Element* element;
				HRESULT hr1 = pIElement->CreateElementGet(&element, key, keyLength);
				if (!SUCCEEDED(hr1))
				{
					IERR("IElement::CreateElementGet");
					throw (int)hr1;
				}
				else
				{
					return element;
				}
			}
			else
			{
				IERR("IElement");
				throw (int)hr0;
			}
		}

		Element* CreateElementInsert(OS15HANDEL h, const void* key, int keyLength, const void* payload, int payloadLength)
		{
			IElement* pIElement = nullptr;
			HRESULT hr0 = ((IUnknown*)h)->QueryInterface(IID_IElement, (void**)&pIElement);

			if (SUCCEEDED(hr0))
			{
				Element* element;
				HRESULT hr1 = pIElement->CreateElementInsert(&element, key, keyLength, payload, payloadLength);
				if (!SUCCEEDED(hr1))
				{
					IERR("IElement::CreateElementInsert");
					throw (int)hr1;
				}
				else
				{
					return element;
				}
			}
			else
			{
				IERR("IElement");
				throw (int)hr0;
			}
		}

		Element* CreateElementUpdate(OS15HANDEL h, const Element* oldElement, const void* newPayload, int newPayloadLength)
		{
			IElement* pIElement = nullptr;
			HRESULT hr0 = ((IUnknown*)h)->QueryInterface(IID_IElement, (void**)&pIElement);

			if (SUCCEEDED(hr0))
			{
				Element* element;
				HRESULT hr1 = pIElement->CreateElementUpdate(&element, oldElement, newPayload, newPayloadLength);
				if (!SUCCEEDED(hr1))
				{
					IERR("IElement::CreateElementUpdate");
					throw (int)hr1;
				}
				else
				{
					return element;
				}
			}
			else
			{
				IERR("IElement");
				throw (int)hr0;
			}
		}
	}

	namespace Utils
	{
		const char* getLastError(OS15HANDEL h, const HTHANDLE* htHandle)
		{
			IHTUtil* pIUtil = nullptr;
			HRESULT hr0 = ((IUnknown*)h)->QueryInterface(IID_IHTUtil, (void**)&pIUtil);

			if (SUCCEEDED(hr0))
			{
				const char* error;
				HRESULT hr1 = pIUtil->getLastError(&error, htHandle);
				if (!SUCCEEDED(hr1))
				{
					IERR("IHTUtil::getLastError");
					throw (int)hr1;
				}
				else
				{
					return error;
				}
			}
			else
			{
				IERR("IHTUtil");
				throw (int)hr0;
			}
		}

		void print(OS15HANDEL h, const Element* element)
		{
			IHTUtil* pIUtil = nullptr;
			HRESULT hr0 = ((IUnknown*)h)->QueryInterface(IID_IHTUtil, (void**)&pIUtil);

			if (SUCCEEDED(hr0))
			{
				HRESULT hr1 = pIUtil->print(element);
				if (!SUCCEEDED(hr1))
				{
					IERR("IHTUtil::print");
					throw (int)hr1;
				}
			}
			else
			{
				IERR("IHTUtil");
				throw (int)hr0;
			}
		}
	}
	void Dispose(OS15HANDEL h)
	{
		((IUnknown*)h)->Release();
		CoFreeUnusedLibraries();
	}
}

