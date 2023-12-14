#include "pch.h"
#include "HT.h"


HTHANDLE::HTHANDLE()
{
	this->Capacity = 0;
	this->SecSnapshotInterval = 0;
	this->MaxKeyLength = 0;
	this->MaxPayloadLength = 0;
	ZeroMemory(this->FileName, sizeof(this->FileName));
	this->File = NULL;
	this->FileMapping = NULL;
	this->Addr = NULL;
	ZeroMemory(this->LastErrorMessage, sizeof(this->LastErrorMessage));
	this->LastSnaptime = 0;

	this->Count = 0;
}

HTHANDLE::HTHANDLE(int capacity, int secSnapshotInterval, int maxKeyLength, int maxPayloadLength, const wchar_t* HTUsersGroup, const wchar_t* fileName) : HTHANDLE()
{
	this->Capacity = capacity;
	this->SecSnapshotInterval = secSnapshotInterval;
	this->MaxKeyLength = maxKeyLength;
	this->MaxPayloadLength = maxPayloadLength;
	memcpy(this->FileName, fileName, sizeof(this->FileName));
	memcpy(this->HTUsersGroup, HTUsersGroup, sizeof(this->HTUsersGroup));
}


Element::Element()
{
	key = nullptr;
	keyLength = 0;
	payload = nullptr;
	payloadLength = 0;
}

Element::Element(const void* key, int keyLength) : Element()
{
	this->key = key;
	this->keyLength = keyLength;
}

Element::Element(const void* key, int keyLength, const void* payload, int  payloadLength) : Element()
{
	this->key = key;
	this->keyLength = keyLength;
	this->payload = payload;
	this->payloadLength = payloadLength;
}

Element::Element(const Element* oldElement, const void* newPayload, int  newPayloadLength) : Element()
{
	this->key = oldElement->key;
	this->keyLength = oldElement->keyLength;
	this->payload = newPayload;
	this->payloadLength = newPayloadLength;

	delete oldElement;
}
