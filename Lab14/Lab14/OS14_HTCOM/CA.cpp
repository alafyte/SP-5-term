#include "pch.h"
#include "CA.h"
#include "SEQLOG.h"

static void CALLBACK SnapAsyncWrapper(LPVOID prm, DWORD dwTimerLowValue, DWORD dwTimerHighValue);

CA::CA() :m_Ref(1) 
{
	SEQ;
	InterlockedIncrement((LONG*)&g_Components);
	LOG("OS14::Adder g_Components = ", g_Components);
};

CA::~CA() 
{
	SEQ;
	InterlockedDecrement((LONG*)&g_Components);
	LOG("OS14::~Adder g_Components = ", g_Components);
};

HRESULT STDMETHODCALLTYPE CA::QueryInterface(REFIID riid, void** ppv)
{
	SEQ;
	HRESULT rc = S_OK;
	*ppv = NULL;
	if (riid == IID_IUnknown)
		*ppv = (IHTManipulator*)this;
	else if (riid == IID_IHTManipulator)
		*ppv = (IHTManipulator*)this;
	else if (riid == IID_IHTDataManipulator)
		*ppv = (IHTDataManipulator*)this;
	else if (riid == IID_IHTUtil)
		*ppv = (IHTUtil*)this;
	else if (riid == IID_IElement)
		*ppv = (IElement*)this;
	else rc = E_NOINTERFACE;

	if (rc == S_OK) this->AddRef();
	LOG("OS14::QueryInterface rc = ", rc);
	return rc;
};

ULONG STDMETHODCALLTYPE CA::AddRef(void) 
{
	SEQ;
	InterlockedIncrement((LONG*)&(this->m_Ref));
	LOG("OS14::AddRef m_Ref = ", this->m_Ref);
	return this->m_Ref;
};

ULONG STDMETHODCALLTYPE CA::Release(void) 
{
	SEQ;
	ULONG rc = this->m_Ref;
	if ((rc = InterlockedDecrement((LONG*)&(this->m_Ref))) == 0) delete this;
	LOG("OS14::Release rc = ", rc);
	return rc;
};

HRESULT STDMETHODCALLTYPE CA::Create(
	HTHANDLE** handle,
	int	  capacity,					// емкость хранилища
	int   secSnapshotInterval,		// переодичность сохранения в сек.
	int   maxKeyLength,             // максимальный размер ключа
	int   maxPayloadLength,			// максимальный размер данных
	const wchar_t* HTUsersGroup,
	const wchar_t* fileName)		// имя файла 
{

	if (!isGroupExisting(HTUsersGroup)) 
	{
		std::cout << "Error: group doesn't exist" << std::endl;
		*handle = NULL;
		return S_OK;
	}
	if (!isCurrentUserInGroup(HTUsersGroup)) 
	{
		std::wcout << "Error: user is not in group " << HTUsersGroup << std::endl;
		*handle = NULL;
		return S_OK;
	}
	if (!isCurrentUserInGroup(L"Администраторы")) 
	{
		std::cout << "Error: user is not admin" << std::endl;
		*handle = NULL;
		return S_OK;
	}

	HANDLE hf = CreateFile(
		fileName,
		GENERIC_WRITE | GENERIC_READ,
		NULL,
		NULL,
		OPEN_ALWAYS,
		FILE_ATTRIBUTE_NORMAL,
		NULL);
	if (hf == INVALID_HANDLE_VALUE)
		throw "Create or open file failed";

	int sizeMap = sizeof(HTHANDLE) + GetElementSize(maxKeyLength, maxPayloadLength) * capacity;
	HANDLE hm = CreateFileMapping(
		hf,
		NULL,
		PAGE_READWRITE,
		0, sizeMap,
		fileName);
	if (!hm)
		throw "Create File Mapping failed";

	LPVOID lp = MapViewOfFile(
		hm,
		FILE_MAP_ALL_ACCESS,
		0, 0, 0);
	if (!lp)
	{
		*handle = NULL;
		return S_OK;
	}

	ZeroMemory(lp, sizeMap);

	HTHANDLE* htHandle = new(lp) HTHANDLE(capacity, secSnapshotInterval, maxKeyLength, maxPayloadLength, HTUsersGroup, fileName);
	htHandle->File = hf;
	htHandle->FileMapping = hm;
	htHandle->Addr = lp;
	htHandle->LastSnaptime = time(NULL);
	htHandle->Mutex = CreateMutex(NULL, FALSE, fileName);

	htHandle->SnapshotTimer = CreateWaitableTimer(0, FALSE, 0);
	LARGE_INTEGER Li{};
	Li.QuadPart = -(10000000 * htHandle->SecSnapshotInterval);
	SetWaitableTimer(htHandle->SnapshotTimer, &Li, htHandle->SecSnapshotInterval * 1000, SnapAsyncWrapper, htHandle, FALSE);

	*handle = htHandle;
	return S_OK;
}

static void CALLBACK SnapAsyncWrapper(LPVOID prm, DWORD dwTimerLowValue, DWORD dwTimerHighValue)
{
	CA* caInstance = new CA();
	caInstance->snapAsync(prm, dwTimerLowValue, dwTimerHighValue);
	delete caInstance;
}

void CALLBACK CA::snapAsync(LPVOID prm, DWORD, DWORD)
{
	HTHANDLE* htHandle = (HTHANDLE*)prm;
	BOOL rc;
	Snap(rc, htHandle);
	if (rc)
		std::cout << "SpanshotAsync success" << std::endl;
}

HRESULT STDMETHODCALLTYPE CA::Open
(
	HTHANDLE** handle,
	const wchar_t* fileName,
	bool isMapFile)         // имя файла
{
	HTHANDLE* htHandle;
	if (isMapFile)
	{
		htHandle = OpenHTFromMapName(fileName);
	}
	else
	{
		htHandle = OpenHTFromFile(fileName);
		if (htHandle)
		{
			htHandle->SnapshotTimer = CreateWaitableTimer(0, FALSE, 0);
			LARGE_INTEGER Li{};
			Li.QuadPart = -(10000000 * htHandle->SecSnapshotInterval);
			SetWaitableTimer(htHandle->SnapshotTimer, &Li, htHandle->SecSnapshotInterval * 1000, SnapAsyncWrapper, htHandle, FALSE);
		}
	}

	if (htHandle && !isCurrentUserInGroup(htHandle->HTUsersGroup))
	{
		std::wcout << "Error: user is not in group " << htHandle->HTUsersGroup << std::endl;
		BOOL rc;
		Close(rc, htHandle);
		*handle = NULL;
		return S_OK;
	}

	*handle = htHandle;
	return S_OK;
}

HRESULT CA::Open(HTHANDLE** handle, const wchar_t* HTUser, const wchar_t* HTPassword, const wchar_t* fileName, bool isMapFile)
{

	HTHANDLE* htHandle;
	if (isMapFile)
	{
		htHandle = OpenHTFromMapName(fileName);
	}
	else
	{
		htHandle = OpenHTFromFile(fileName);
		if (htHandle)
		{
			htHandle->SnapshotTimer = CreateWaitableTimer(0, FALSE, 0);
			LARGE_INTEGER Li{};
			Li.QuadPart = -(10000000 * htHandle->SecSnapshotInterval);
			SetWaitableTimer(htHandle->SnapshotTimer, &Li, htHandle->SecSnapshotInterval * 1000, SnapAsyncWrapper, htHandle, FALSE);
		}
	}

	if (htHandle && !(isUserInGroup(HTUser, htHandle->HTUsersGroup) && verifyCredentials(HTUser, HTPassword)))
	{
		std::wcout << "Error: user is not in group " << htHandle->HTUsersGroup << " or their credetials are incorrect" << std::endl;
		BOOL rc;
		Close(rc, htHandle);
		*handle = NULL;
		return S_OK;
	}

	*handle = htHandle;
	return S_OK;
}

HTHANDLE* CA::OpenHTFromFile(const wchar_t* fileName)
{
	HANDLE hf = CreateFile(
		fileName,
		GENERIC_WRITE | GENERIC_READ,
		NULL,
		NULL,
		OPEN_ALWAYS,
		FILE_ATTRIBUTE_NORMAL,
		NULL);
	if (hf == INVALID_HANDLE_VALUE)
		return NULL;

	HANDLE hm = CreateFileMapping(
		hf,
		NULL,
		PAGE_READWRITE,
		0, 0,
		fileName);
	if (!hm)
		return NULL;

	LPVOID lp = MapViewOfFile(
		hm,
		FILE_MAP_ALL_ACCESS,
		0, 0, 0);
	if (!lp)
		return NULL;

	HTHANDLE* htHandle = (HTHANDLE*)lp;
	htHandle->File = hf;
	htHandle->FileMapping = hm;
	htHandle->Addr = lp;
	htHandle->LastSnaptime = time(NULL);
	htHandle->Mutex = CreateMutex(NULL, FALSE, fileName);

	return htHandle;
}

HTHANDLE* CA::OpenHTFromMapName(const wchar_t* fileName)
{
	HANDLE hm = OpenFileMapping(
		FILE_MAP_ALL_ACCESS,
		false,
		fileName);
	if (!hm)
		return NULL;

	LPVOID lp = MapViewOfFile(
		hm,
		FILE_MAP_ALL_ACCESS,
		0, 0, 0);
	if (!lp)
		return NULL;

	HTHANDLE* htHandle = new HTHANDLE();
	memcpy(htHandle, lp, sizeof(HTHANDLE));
	htHandle->File = NULL;
	htHandle->FileMapping = hm;
	htHandle->Addr = lp;
	htHandle->SnapshotTimer = NULL;

	return htHandle;
}


HRESULT STDMETHODCALLTYPE CA::Get     //  читать элемент из хранилища
(
	Element** resultElement,
	HTHANDLE* htHandle,            // управление HT
	const Element* element)              // элемент 
{
	int index = findIndex(htHandle, element);
	if (index < 0)
	{
		WriteLastError(htHandle, "Not found element (GET)");
		*resultElement = NULL;
		return S_OK;
	}

	Element* foundElement = new Element();
	readFromMemory(htHandle, foundElement, index);

	*resultElement = foundElement;

	return S_OK;
}

HRESULT STDMETHODCALLTYPE CA::Insert		// добавить элемент в хранилище
(
	BOOL& rc,
	HTHANDLE* htHandle,            // управление HT
	const Element* element)              // элемент
{
	if (htHandle->Count >= htHandle->Capacity)
	{
		WriteLastError(htHandle, "Not found free memory");
		rc = false;
		return S_OK;
	}

	WaitForSingleObject(htHandle->Mutex, INFINITE);
	int freeIndex = findFreeIndex(htHandle, element);

	if (freeIndex < 0)
	{
		WriteLastError(htHandle, "Key already exists");
		ReleaseMutex(htHandle->Mutex);
		rc = false;
		return S_OK;
	}

	writeToMemory(htHandle, element, freeIndex);
	incrementCount(htHandle);
	ReleaseMutex(htHandle->Mutex);

	rc = true;
	return S_OK;
}

HRESULT STDMETHODCALLTYPE CA::Update     //  именить элемент в хранилище
(
	BOOL& rc,
	HTHANDLE* htHandle,            // управление HT
	const Element* oldElement,          // старый элемент (ключ, размер ключа)
	const void* newPayload,          // новые данные  
	int             newPayloadLength)     // размер новых данных
{
	WaitForSingleObject(htHandle->Mutex, INFINITE);
	int index = findIndex(htHandle, oldElement);
	if (index < 0)
	{
		WriteLastError(htHandle, "Not found element (UPDATE)");
		ReleaseMutex(htHandle->Mutex);
		rc = false;
		return S_OK;
	}

	Element* updateElement = new Element(oldElement, newPayload, newPayloadLength);
	writeToMemory(htHandle, updateElement, index);
	ReleaseMutex(htHandle->Mutex);

	rc = true;
	return S_OK;
}

HRESULT STDMETHODCALLTYPE CA::Delete      // удалить элемент в хранилище
(
	BOOL& rc,
	HTHANDLE* htHandle,            // управление HT (ключ)
	const Element* element)				 // элемент 
{
	WaitForSingleObject(htHandle->Mutex, INFINITE);
	int index = findIndex(htHandle, element);
	if (index < 0)
	{
		WriteLastError(htHandle, "Not found element (DELETE)");
		ReleaseMutex(htHandle->Mutex);
		rc = false;
		return S_OK;
	}

	clearMemoryByIndex(htHandle, index);
	decrementCount(htHandle);
	ReleaseMutex(htHandle->Mutex);

	rc = true;
	return S_OK;
}

HRESULT STDMETHODCALLTYPE CA::Snap         // выполнить Snapshot
(
	BOOL& rc,
	HTHANDLE* htHandle)           // управление HT (File, FileMapping)
{
	WaitForSingleObject(htHandle->Mutex, INFINITE);
	if (!FlushViewOfFile(htHandle->Addr, NULL)) 
	{
		WriteLastError(htHandle, "Snapshot error");
		ReleaseMutex(htHandle->Mutex);
		rc = false;
		return S_OK;
	}
	htHandle->LastSnaptime = time(NULL);
	ReleaseMutex(htHandle->Mutex);

	rc = true;
	return S_OK;
}

HRESULT STDMETHODCALLTYPE CA::print                               // распечатать элемент 
(
	const Element* element)              // элемент 
{
	std::cout << "Element:" << std::endl;
	std::cout << "{" << std::endl;
	std::cout << "\t\"key\": \"" << (char*)element->key << "\"," << std::endl;
	std::cout << "\t\"keyLength\": " << element->keyLength << "," << std::endl;
	std::cout << "\t\"payload\": \"" << (char*)element->payload << "\"," << std::endl;
	std::cout << "\t\"payloadLength\": " << element->payloadLength << std::endl;
	std::cout << "}" << std::endl;

	return S_OK;
}

HRESULT STDMETHODCALLTYPE CA::Close        // snap и закрыть HT  и  очистить htHandle
(
	BOOL& rc,
	const HTHANDLE* htHandle)           // управление HT (File, FileMapping)
{
	HANDLE hf = htHandle->File;
	HANDLE hfm = htHandle->FileMapping;

	if (!CancelWaitableTimer(htHandle->SnapshotTimer))
		throw "Cancel snapshotTimer failed";
	if (!UnmapViewOfFile(htHandle->Addr))
		throw "Unmapping view failed";
	if (!CloseHandle(hfm))
		throw "Close File Mapping failed";
	if (hf != NULL)
		if (!CloseHandle(hf))
			throw "Close File failed";

	rc = true;
	return S_OK;
}

int CA::GetElementSize(int maxKeyLength, int maxPayloadLength)
{
	return maxKeyLength + maxPayloadLength + sizeof(int) * 2;
}

int CA::hashFunction(const char* key, int capacity)
{
	unsigned long i = 0;
	for (int j = 0; key[j]; j++)
		i += key[j];
	return i % capacity;
}

int CA::nextHash(int currentHash, const char* key, int capacity)
{
	return ++currentHash;
}

int CA::findFreeIndex(
	const HTHANDLE* htHandle,           // управление HT
	const Element* element)				// элемент
{
	int index = hashFunction((char*)element->key, htHandle->Capacity);

	Element* foundElement = new Element();
	do
	{
		if (index >= htHandle->Capacity || foundElement->key != NULL &&
			memcmp(foundElement->key, element->key, element->keyLength) == NULL)
		{
			index = -1;
			break;
		}

		readFromMemory(htHandle, foundElement, index);
		index = nextHash(index, (char*)element->key, htHandle->Capacity);
	} while (
		foundElement->keyLength != NULL &&
		foundElement->payloadLength != NULL);

	delete foundElement;
	return index - 1;
}

int CA::findIndex(
	const HTHANDLE* htHandle,           // управление HT
	const Element* element)				// элемент
{
	int index = hashFunction((char*)element->key, htHandle->Capacity);

	Element* foundElement = new Element();
	do
	{
		if (index >= htHandle->Capacity)
		{
			index = -1;
			break;
		}

		readFromMemory(htHandle, foundElement, index);
		index = nextHash(index, (char*)element->key, htHandle->Capacity);
	} while (
		memcmp(foundElement->key, element->key, element->keyLength) != NULL);

	delete foundElement;
	return index - 1;
}

BOOL CA::writeToMemory(const HTHANDLE* const htHandle, const Element* const element, int index)
{
	LPVOID lp = htHandle->Addr;

	lp = (HTHANDLE*)lp + 1;
	lp = (BYTE*)lp + GetElementSize(htHandle->MaxKeyLength, htHandle->MaxPayloadLength) * index;

	memcpy(lp, element->key, element->keyLength);
	lp = (BYTE*)lp + htHandle->MaxKeyLength;
	memcpy(lp, &element->keyLength, sizeof(int));
	lp = (int*)lp + 1;
	memcpy(lp, element->payload, element->payloadLength);
	lp = (BYTE*)lp + htHandle->MaxPayloadLength;
	memcpy(lp, &element->payloadLength, sizeof(int));

	return true;
}

int CA::incrementCount(HTHANDLE* const htHandle)
{
	return ++htHandle->Count;
}

Element* CA::readFromMemory(const HTHANDLE* const htHandle, Element* const element, int index)
{
	LPVOID lp = htHandle->Addr;

	lp = (HTHANDLE*)lp + 1;
	lp = (BYTE*)lp + GetElementSize(htHandle->MaxKeyLength, htHandle->MaxPayloadLength) * index;

	element->key = lp;
	lp = (BYTE*)lp + htHandle->MaxKeyLength;
	element->keyLength = *(int*)lp;
	lp = (int*)lp + 1;
	element->payload = lp;
	lp = (BYTE*)lp + htHandle->MaxPayloadLength;
	element->payloadLength = *(int*)lp;

	return element;
}

BOOL CA::clearMemoryByIndex(const HTHANDLE* const htHandle, int index)
{
	LPVOID lp = htHandle->Addr;
	int sizeElement = GetElementSize(htHandle->MaxKeyLength, htHandle->MaxPayloadLength);

	lp = (HTHANDLE*)lp + 1;
	lp = (BYTE*)lp + sizeElement * index;

	ZeroMemory(lp, sizeElement);

	return true;
}

int CA::decrementCount(HTHANDLE* const htHandle)
{
	return --htHandle->Count;
}

const char* CA::WriteLastError(HTHANDLE* const htHandle, const char* msg)
{
	memcpy(htHandle->LastErrorMessage, msg, sizeof(htHandle->LastErrorMessage));
	return htHandle->LastErrorMessage;
}

HRESULT STDMETHODCALLTYPE CA::getLastError  // получить сообщение о последней ошибке
(
	const char** error,
	const HTHANDLE* htHandle                         // управление HT
)
{
	*error = htHandle->LastErrorMessage;
	return S_OK;
}

HRESULT STDMETHODCALLTYPE CA::CreateElementGet
(
	Element** element,
	const void* key,
	int keyLength
)
{
	*element = new Element(key, keyLength);
	return S_OK;
}

HRESULT STDMETHODCALLTYPE CA::CreateElementInsert
(
	Element** element,
	const void* key,
	int keyLength,
	const void* payload,
	int payloadLength
)
{
	*element = new Element(key, keyLength, payload, payloadLength);
	return S_OK;
}

HRESULT STDMETHODCALLTYPE CA::CreateElementUpdate
(
	Element** element,
	const Element* oldElement,
	const void* newPayload,
	int newPayloadLength
)
{
	*element = new Element(oldElement, newPayload, newPayloadLength);
	return S_OK;
}

BOOL CA::isGroupExisting(LPCWSTR groupName) 
{
	GROUP_INFO_0* groupsInfo;
	DWORD readed = 0, total = 0;
	NetLocalGroupEnum(
		NULL,
		0,
		(LPBYTE*)&groupsInfo,
		MAX_PREFERRED_LENGTH,
		&readed,
		&total,
		NULL
	);
	bool exosts = false;
	for (int i = 0; i < readed; i++) 
	{
		int res = lstrcmpW(groupName, groupsInfo[i].grpi0_name);
		if (res == 0) {
			exosts = true;
			break;
		}
	}
	NetApiBufferFree((LPVOID)groupsInfo);
	return exosts;
}

BOOL CA::isUserInGroup(LPCWSTR userName, LPCWSTR groupName) 
{
	GROUP_USERS_INFO_0* groupUsersInfo;
	DWORD uc = 0, tc = 0;
	NET_API_STATUS ns = NetUserGetLocalGroups(
		NULL,
		userName,
		0,
		LG_INCLUDE_INDIRECT,
		(LPBYTE*)&groupUsersInfo,
		MAX_PREFERRED_LENGTH,
		&uc,
		&tc
	);
	bool exists = false;
	if (ns == NERR_Success) 
	{
		for (int i = 0; i < uc; i++) 
		{
			int res = lstrcmpW(groupName, groupUsersInfo[i].grui0_name);
			if (res == 0) 
			{
				exists = true;
				break;
			}
		}
		NetApiBufferFree((LPVOID)groupUsersInfo);
	}
	return exists;
}

BOOL CA::isCurrentUserInGroup(LPCWSTR groupName) 
{
	WCHAR currentUserName[512];
	DWORD lenUserName = 512;
	GetUserName(currentUserName, &lenUserName);
	return isUserInGroup(currentUserName, groupName);
}

BOOL CA::verifyCredentials(LPCWSTR name, LPCWSTR pass) 
{
	bool res;
	HANDLE hToken = 0;
	res = LogonUserW(
		name,
		L".",
		pass,
		LOGON32_LOGON_INTERACTIVE,
		LOGON32_PROVIDER_DEFAULT,
		&hToken
	);
	CloseHandle(hToken);
	return res;
}