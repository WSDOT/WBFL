///////////////////////////////////////////////////////////
//
// CUnknown.cpp 
//   - Implementation of IUnknown base class
//
#include "StdAfx.h"
#include "CUnknown.h"

///////////////////////////////////////////////////////////
//
// Count of active objects
//   - Use to determine if we can unload the DLL.
//
long CUnknown::s_cActiveComponents = 0 ;


///////////////////////////////////////////////////////////
//
// Constructor
//
CUnknown::CUnknown(IUnknown* pUnknownOuter)
: m_cRef(1)
{
	// Set m_pUnknownOuter pointer.
	if (pUnknownOuter == NULL)
	{
		m_pUnknownOuter = reinterpret_cast<IUnknown*>
		                     (static_cast<INondelegatingUnknown*>
		                     (this)) ;  // notice cast
	}
	else
	{
		m_pUnknownOuter = pUnknownOuter ;
	}

	// Increment count of active components.
	::InterlockedIncrement(&s_cActiveComponents) ;
}

//
// Destructor
//
CUnknown::~CUnknown()
{
	InterlockedDecrement(&s_cActiveComponents) ;
}

//
// FinalRelease - called by Release before it deletes the component
//
void CUnknown::FinalRelease()
{
	m_cRef = 1 ;
}

//
// Nondelegating IUnknown
//   - Override to handle custom interfaces.
//
HRESULT __stdcall 
	CUnknown::NondelegatingQueryInterface(const IID& iid, void** ppv)
{
	// CUnknown supports only IUnknown.
	if (iid == IID_IUnknown)
	{
		return FinishQI(reinterpret_cast<IUnknown*>
		                   (static_cast<INondelegatingUnknown*>(this)), ppv) ;
	}	
	else
	{
		*ppv = NULL ;
		return E_NOINTERFACE ;
	}
}

//
// AddRef
//
ULONG __stdcall CUnknown::NondelegatingAddRef()
{
	return ::InterlockedIncrement(&m_cRef) ;
}

//
// Release
//
ULONG __stdcall CUnknown::NondelegatingRelease()
{
	::InterlockedDecrement(&m_cRef) ;
	if (m_cRef == 0)
	{
		FinalRelease() ;
		delete this ;
		return 0 ;
	}
	return m_cRef ;
}

//
// FinishQI
//   - Helper function to simplify overriding
//     NondelegatingQueryInterface
//
HRESULT CUnknown::FinishQI(IUnknown* pI, void** ppv) 
{
	*ppv = pI ;
	pI->AddRef() ;
	return S_OK ;
}
