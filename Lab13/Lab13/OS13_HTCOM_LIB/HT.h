#pragma once
#include "pch.h"
#include <Windows.h>


struct Element   // элемент 
{
	Element();
	Element(const void* key, int keyLength);                                             // for get
	Element(const void* key, int keyLength, const void* payload, int  payloadLength);    // for insert
	Element(const Element* oldElement, const void* newPayload, int  newPayloadLength);   // for update
	const void* key;                 // значение ключа 
	int         keyLength;           // рахмер ключа
	const void* payload;             // данные 
	int         payloadLength;       // размер данных
};

struct HTHANDLE    // блок управления HT
{
	HTHANDLE();
	HTHANDLE(int capacity, int secSnapshotInterval, int maxKeyLength, int maxPayloadLength, const wchar_t* fileName);
	int     Capacity;               // емкость хранилища в количестве элементов 
	int     SecSnapshotInterval;    // переодичность сохранения в сек. 
	int     MaxKeyLength;           // максимальная длина ключа
	int     MaxPayloadLength;       // максимальная длина данных
	wchar_t FileName[512];          // имя файла 
	HANDLE  File;                   // File HANDLE != 0, если файл открыт
	HANDLE  FileMapping;            // Mapping File HANDLE != 0, если mapping создан  
	LPVOID  Addr;                   // Addr != NULL, если mapview выполнен  
	char    LastErrorMessage[512];  // сообщение об последней ошибке или 0x00  
	time_t  LastSnaptime;           // дата последнего snap'a (time())

	int Count;						// текущее количество элементов в хэш-таблице
	HANDLE SnapshotTimer;			// таймер для snapshot
	HANDLE Mutex;					// mutex для синхронизации нескольких экземпляров HtHandle
};
 
