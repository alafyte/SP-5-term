#pragma once
#include <objbase.h>

extern ULONG g_ServerLocks;

class CFactory : public IClassFactory
{
public:
	virtual HRESULT STDMETHODCALLTYPE QueryInterface(REFIID riid, void** ppv);
	virtual ULONG STDMETHODCALLTYPE AddRef(void);
	virtual ULONG STDMETHODCALLTYPE Release(void);


	virtual HRESULT STDMETHODCALLTYPE CreateInstance(IUnknown* pUO, const IID& id, void** ppv);
	virtual HRESULT STDMETHODCALLTYPE LockServer(BOOL b);

	CFactory();
	~CFactory();

private:
	ULONG m_Ref;
};