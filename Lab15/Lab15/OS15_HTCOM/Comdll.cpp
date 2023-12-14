#include "pch.h"
#include "Comdll.h"
#include "SEQLOG.h"
#include "CA.h"
#include "CFactory.h"
#include "Registry.h"


STDAPI DllCanUnloadNow() 
{
	SEQ;
	HRESULT rc = E_UNEXPECTED;
	if ((g_ServerLocks == 0) && (g_Components == 0))
		rc = S_OK;
	else
		rc = S_FALSE;

	LOG("DllCanUnloadNow: rc = ", rc);
	return rc;
}

STDAPI DllGetClassObject(const CLSID& clsid, const IID& iid, void** ppv) 
{
	SEQ;
	CFactory* pF;
	HRESULT rc = E_UNEXPECTED;
	if (clsid != CLSID_CA)
		rc = CLASS_E_CLASSNOTAVAILABLE;
	else if ((pF = new CFactory()) == NULL)
		rc = E_OUTOFMEMORY;
	else {
		rc = pF->QueryInterface(iid, ppv);
		pF->Release();
	}
	LOG("DllGetClassObject: rc = ", rc);
	return rc;
}