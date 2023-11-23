#pragma once
#include <objbase.h>
#include <iostream>
#include "Interface.h"
#include "HT.h"

extern ULONG g_Components;

class CA : IHTManipulator, IHTDataManipulator, IHTUtil, IElement
{
public:
	CA();
	~CA();


	virtual HRESULT STDMETHODCALLTYPE QueryInterface(REFIID riid, void** ppv);
	virtual ULONG STDMETHODCALLTYPE AddRef(void);
	virtual ULONG STDMETHODCALLTYPE Release(void);


	virtual HRESULT STDMETHODCALLTYPE Create   //  создать HT             
	(
		HTHANDLE** handle,
		int	  capacity,					   // емкость хранилища
		int   secSnapshotInterval,		   // переодичность сохранения в сек.
		int   maxKeyLength,                // максимальный размер ключа
		int   maxPayloadLength,            // максимальный размер данных
		const wchar_t* fileName           // имя файла 
	); 	// != NULL успешное завершение 

	virtual HRESULT STDMETHODCALLTYPE Open     //  открыть HT             
	(
		HTHANDLE** handle,
		const wchar_t* fileName,         // имя файла 
		bool isMapFile = false
	); 	// != NULL успешное завершение  

	virtual HRESULT STDMETHODCALLTYPE Snap         // выполнить Snapshot
	(
		BOOL& rc,
		HTHANDLE* htHandle           // управление HT (File, FileMapping)
	);

	virtual HRESULT STDMETHODCALLTYPE Close        // snap и закрыть HT  и  очистить htHandle
	(
		BOOL& rc,
		const HTHANDLE* htHandle           // управление HT (File, FileMapping)
	);	//  == TRUE успешное завершение   


	virtual HRESULT STDMETHODCALLTYPE Insert      // добавить элемент в хранилище
	(
		BOOL& rc,
		HTHANDLE* htHandle,            // управление HT
		const Element* element              // элемент
	);	//  == TRUE успешное завершение 

	virtual HRESULT STDMETHODCALLTYPE Delete      // удалить элемент в хранилище
	(
		BOOL& rc,
		HTHANDLE* htHandle,            // управление HT (ключ)
		const Element* element              // элемент 
	);	//  == TRUE успешное завершение 


	virtual HRESULT STDMETHODCALLTYPE Get     //  читать элемент в хранилище
	(
		Element** resultElement,
		HTHANDLE* htHandle,            // управление HT
		const Element* element              // элемент 
	); 	//  != NULL успешное завершение 


	virtual HRESULT STDMETHODCALLTYPE Update     //  именить элемент в хранилище
	(
		BOOL& rc,
		HTHANDLE* htHandle,            // управление HT
		const Element* oldElement,          // старый элемент (ключ, размер ключа)
		const void* newPayload,          // новые данные  
		int             newPayloadLength     // размер новых данных
	); 	//  != NULL успешное завершение 

	virtual HRESULT STDMETHODCALLTYPE getLastError  // получить сообщение о последней ошибке
	(
		const char** error,
		const HTHANDLE* htHandle                         // управление HT
	);

	virtual HRESULT STDMETHODCALLTYPE print                               // распечатать элемент 
	(
		const Element* element              // элемент 
	);

	virtual HRESULT STDMETHODCALLTYPE CreateElementGet
	(
		Element** element, 
		const void* key, 
		int keyLength
	);

	virtual HRESULT STDMETHODCALLTYPE CreateElementInsert
	(
		Element** element, 
		const void* key, 
		int keyLength,
		const void* payload, 
		int payloadLength
	);

	virtual HRESULT STDMETHODCALLTYPE CreateElementUpdate
	(
		Element** element, 
		const Element* oldElement, 
		const void* newPayload, 
		int newPayloadLength
	);

	void CALLBACK snapAsync(LPVOID prm, DWORD, DWORD);

private:
	volatile ULONG m_Ref;
	int GetElementSize
	(
		int   maxKeyLength,                // максимальный размер ключа
		int   maxPayloadLength	  // максимальный размер данных
	);
	int hashFunction(const char* key, int capacity);
	int nextHash(int currentHash, const char* key, int capacity);

	int findFreeIndex(const HTHANDLE* htHandle, const Element* element);
	BOOL writeToMemory(const HTHANDLE* const htHandle, const Element* const element, int index);
	int incrementCount(HTHANDLE* const htHandle);

	int findIndex(const HTHANDLE* htHandle, const Element* element);
	Element* readFromMemory(const HTHANDLE* const htHandle, Element* const element, int index);
	BOOL clearMemoryByIndex(const HTHANDLE* const htHandle, int index);
	int decrementCount(HTHANDLE* const htHandle);

	const char* WriteLastError(HTHANDLE* const htHandle, const char* msg);

	HTHANDLE* OpenHTFromFile(const wchar_t* fileName);
	HTHANDLE* OpenHTFromMapName(const wchar_t* fileName);

};