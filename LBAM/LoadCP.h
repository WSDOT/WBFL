///////////////////////////////////////////////////////////////////////
// LBAM - Longitindal Bridge Analysis Model
// Copyright © 1999-2023  Washington State Department of Transportation
//                        Bridge and Structures Office
//
// This library is a part of the Washington Bridge Foundation Libraries
// and was developed as part of the Alternate Route Project
//
// This library is free software; you can redistribute it and/or modify it under
// the terms of the Alternate Route Library Open Source License as published by 
// the Washington State Department of Transportation, Bridge and Structures Office.
//
// This program is distributed in the hope that it will be useful, but is distributed 
// AS IS, WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY 
// or FITNESS FOR A PARTICULAR PURPOSE. See the Alternate Route Library Open Source 
// License for more details.
//
// You should have received a copy of the Alternate Route Library Open Source License 
// along with this program; if not, write to the Washington State Department of 
// Transportation, Bridge and Structures Office, P.O. Box  47340, 
// Olympia, WA 98503, USA or e-mail Bridge_Support@wsdot.wa.gov
///////////////////////////////////////////////////////////////////////

#ifndef _LoadCP_H_
#define _LoadCP_H_

template <class T>
class CProxyDDistributedLoadEvents : public IConnectionPointImpl<T, &IID_IDistributedLoadEvents, CComDynamicUnkArray>
{
	//Warning this class may be recreated by the wizard.
public:
	VOID Fire_OnDistributedLoadChanged(IDistributedLoad * me)
	{
		T* pT = static_cast<T*>(this);
		int nConnectionIndex;
		int nConnections = m_vec.GetSize();
		
		for (nConnectionIndex = 0; nConnectionIndex < nConnections; nConnectionIndex++)
		{
			pT->Lock();
			CComPtr<IUnknown> sp = m_vec.GetAt(nConnectionIndex);
			pT->Unlock();
         CComQIPtr<IDistributedLoadEvents> events(sp);
         if ( events )
            events->OnDistributedLoadChanged(me);
		}
	}
};

template <class T>
class CProxyDSettlementLoadEvents : public IConnectionPointImpl<T, &IID_ISettlementLoadEvents, CComDynamicUnkArray>
{
	//Warning this class may be recreated by the wizard.
public:
	VOID Fire_OnSettlementLoadChanged(ISettlementLoad * me)
	{
		T* pT = static_cast<T*>(this);
		int nConnectionIndex;
		int nConnections = m_vec.GetSize();
		
		for (nConnectionIndex = 0; nConnectionIndex < nConnections; nConnectionIndex++)
		{
			pT->Lock();
			CComPtr<IUnknown> sp = m_vec.GetAt(nConnectionIndex);
			pT->Unlock();
         CComQIPtr<ISettlementLoadEvents> events(sp);
         if ( events )
            events->OnSettlementLoadChanged(me);
		}
	}
};


template <class T>
class CProxyDTemperatureLoadEvents : public IConnectionPointImpl<T, &IID_ITemperatureLoadEvents, CComDynamicUnkArray>
{
	//Warning this class may be recreated by the wizard.
public:
	VOID Fire_OnTemperatureLoadChanged(ITemperatureLoad * me)
	{
		T* pT = static_cast<T*>(this);
		int nConnectionIndex;
		int nConnections = m_vec.GetSize();
		
		for (nConnectionIndex = 0; nConnectionIndex < nConnections; nConnectionIndex++)
		{
			pT->Lock();
			CComPtr<IUnknown> sp = m_vec.GetAt(nConnectionIndex);
			pT->Unlock();
         CComQIPtr<ITemperatureLoadEvents> events(sp);
         if ( events )
            events->OnTemperatureLoadChanged(me);
		}
	}
};




template <class T>
class CProxyDStrainLoadEvents : public IConnectionPointImpl<T, &IID_IStrainLoadEvents, CComDynamicUnkArray>
{
	//Warning this class may be recreated by the wizard.
public:
	VOID Fire_OnStrainLoadChanged(IStrainLoad * me)
	{
		T* pT = static_cast<T*>(this);
		int nConnectionIndex;
		int nConnections = m_vec.GetSize();
		
		for (nConnectionIndex = 0; nConnectionIndex < nConnections; nConnectionIndex++)
		{
			pT->Lock();
			CComPtr<IUnknown> sp = m_vec.GetAt(nConnectionIndex);
			pT->Unlock();
         CComQIPtr<IStrainLoadEvents> events(sp);
         if ( events )
            events->OnStrainLoadChanged(me);
		}
	}
};






template <class T>
class CProxyDDistributedLoadsEvents : public IConnectionPointImpl<T, &IID_IDistributedLoadsEvents, CComDynamicUnkArray>
{
	//Warning this class may be recreated by the wizard.
public:
	VOID Fire_OnDistributedLoadsChanged(IDistributedLoadItem * Load)
	{
		T* pT = static_cast<T*>(this);
		int nConnectionIndex;
		int nConnections = m_vec.GetSize();
		
		for (nConnectionIndex = 0; nConnectionIndex < nConnections; nConnectionIndex++)
		{
			pT->Lock();
			CComPtr<IUnknown> sp = m_vec.GetAt(nConnectionIndex);
			pT->Unlock();
         CComQIPtr<IDistributedLoadsEvents> events(sp);
         if ( events )
            events->OnDistributedLoadsChanged(Load);
		}
	}
	VOID Fire_OnDistributedLoadsAdded(IDistributedLoadItem * Load)
	{
		T* pT = static_cast<T*>(this);
		int nConnectionIndex;
		int nConnections = m_vec.GetSize();
		
		for (nConnectionIndex = 0; nConnectionIndex < nConnections; nConnectionIndex++)
		{
			pT->Lock();
			CComPtr<IUnknown> sp = m_vec.GetAt(nConnectionIndex);
			pT->Unlock();
         CComQIPtr<IDistributedLoadsEvents> events(sp);
         if ( events )
            events->OnDistributedLoadsAdded(Load);
		}
	}
	VOID Fire_OnDistributedLoadsBeforeRemove(IDistributedLoadItem * Load)
	{
		T* pT = static_cast<T*>(this);
		int nConnectionIndex;
		int nConnections = m_vec.GetSize();
		
		for (nConnectionIndex = 0; nConnectionIndex < nConnections; nConnectionIndex++)
		{
			pT->Lock();
			CComPtr<IUnknown> sp = m_vec.GetAt(nConnectionIndex);
			pT->Unlock();
         CComQIPtr<IDistributedLoadsEvents> events(sp);
         if ( events )
            events->OnDistributedLoadsBeforeRemove(Load);
		}
	}
};

template <class T>
class CProxyDSettlementLoadsEvents : public IConnectionPointImpl<T, &IID_ISettlementLoadsEvents, CComDynamicUnkArray>
{
	//Warning this class may be recreated by the wizard.
public:
	VOID Fire_OnSettlementLoadsChanged(ISettlementLoadItem * Load)
	{
		T* pT = static_cast<T*>(this);
		int nConnectionIndex;
		int nConnections = m_vec.GetSize();
		
		for (nConnectionIndex = 0; nConnectionIndex < nConnections; nConnectionIndex++)
		{
			pT->Lock();
			CComPtr<IUnknown> sp = m_vec.GetAt(nConnectionIndex);
			pT->Unlock();
         CComQIPtr<ISettlementLoadsEvents> events(sp);
         if ( events )
            events->OnSettlementLoadsChanged(Load);
		}
	}
	VOID Fire_OnSettlementLoadsAdded(ISettlementLoadItem * Load)
	{
		T* pT = static_cast<T*>(this);
		int nConnectionIndex;
		int nConnections = m_vec.GetSize();
		
		for (nConnectionIndex = 0; nConnectionIndex < nConnections; nConnectionIndex++)
		{
			pT->Lock();
			CComPtr<IUnknown> sp = m_vec.GetAt(nConnectionIndex);
			pT->Unlock();
         CComQIPtr<ISettlementLoadsEvents> events(sp);
         if ( events )
            events->OnSettlementLoadsAdded(Load);
		}
	}
	VOID Fire_OnSettlementLoadsBeforeRemove(ISettlementLoadItem * Load)
	{
		T* pT = static_cast<T*>(this);
		int nConnectionIndex;
		int nConnections = m_vec.GetSize();
		
		for (nConnectionIndex = 0; nConnectionIndex < nConnections; nConnectionIndex++)
		{
			pT->Lock();
			CComPtr<IUnknown> sp = m_vec.GetAt(nConnectionIndex);
			pT->Unlock();
         CComQIPtr<ISettlementLoadsEvents> events(sp);
         if ( events )
            events->OnSettlementLoadsBeforeRemove(Load);
		}
	}
};

template <class T>
class CProxyDTemperatureLoadsEvents : public IConnectionPointImpl<T, &IID_ITemperatureLoadsEvents, CComDynamicUnkArray>
{
	//Warning this class may be recreated by the wizard.
public:
	VOID Fire_OnTemperatureLoadsChanged(ITemperatureLoadItem * Load)
	{
		T* pT = static_cast<T*>(this);
		int nConnectionIndex;
		int nConnections = m_vec.GetSize();
		
		for (nConnectionIndex = 0; nConnectionIndex < nConnections; nConnectionIndex++)
		{
			pT->Lock();
			CComPtr<IUnknown> sp = m_vec.GetAt(nConnectionIndex);
			pT->Unlock();
         CComQIPtr<ITemperatureLoadsEvents> events(sp);
         if ( events )
            events->OnTemperatureLoadsChanged(Load);
		}
	}
	VOID Fire_OnTemperatureLoadsAdded(ITemperatureLoadItem * Load)
	{
		T* pT = static_cast<T*>(this);
		int nConnectionIndex;
		int nConnections = m_vec.GetSize();
		
		for (nConnectionIndex = 0; nConnectionIndex < nConnections; nConnectionIndex++)
		{
			pT->Lock();
			CComPtr<IUnknown> sp = m_vec.GetAt(nConnectionIndex);
			pT->Unlock();
         CComQIPtr<ITemperatureLoadsEvents> events(sp);
         if ( events )
            events->OnTemperatureLoadsAdded(Load);
		}
	}
	VOID Fire_OnTemperatureLoadsBeforeRemove(ITemperatureLoadItem * Load)
	{
		T* pT = static_cast<T*>(this);
		int nConnectionIndex;
		int nConnections = m_vec.GetSize();
		
		for (nConnectionIndex = 0; nConnectionIndex < nConnections; nConnectionIndex++)
		{
			pT->Lock();
			CComPtr<IUnknown> sp = m_vec.GetAt(nConnectionIndex);
			pT->Unlock();
         CComQIPtr<ITemperatureLoadsEvents> events(sp);
         if ( events )
            events->OnTemperatureLoadsBeforeRemove(Load);
		}
	}
};

template <class T>
class CProxyDStrainLoadsEvents : public IConnectionPointImpl<T, &IID_IStrainLoadsEvents, CComDynamicUnkArray>
{
	//Warning this class may be recreated by the wizard.
public:
	VOID Fire_OnStrainLoadsChanged(IStrainLoadItem * Load)
	{
		T* pT = static_cast<T*>(this);
		int nConnectionIndex;
		int nConnections = m_vec.GetSize();
		
		for (nConnectionIndex = 0; nConnectionIndex < nConnections; nConnectionIndex++)
		{
			pT->Lock();
			CComPtr<IUnknown> sp = m_vec.GetAt(nConnectionIndex);
			pT->Unlock();
         CComQIPtr<IStrainLoadsEvents> events(sp);
         if ( events )
            events->OnStrainLoadsChanged(Load);
		}
	}
	VOID Fire_OnStrainLoadsAdded(IStrainLoadItem * Load)
	{
		T* pT = static_cast<T*>(this);
		int nConnectionIndex;
		int nConnections = m_vec.GetSize();
		
		for (nConnectionIndex = 0; nConnectionIndex < nConnections; nConnectionIndex++)
		{
			pT->Lock();
			CComPtr<IUnknown> sp = m_vec.GetAt(nConnectionIndex);
			pT->Unlock();
         CComQIPtr<IStrainLoadsEvents> events(sp);
         if ( events )
            events->OnStrainLoadsAdded(Load);
		}
	}
	VOID Fire_OnStrainLoadsBeforeRemove(IStrainLoadItem * Load)
	{
		T* pT = static_cast<T*>(this);
		int nConnectionIndex;
		int nConnections = m_vec.GetSize();
		
		for (nConnectionIndex = 0; nConnectionIndex < nConnections; nConnectionIndex++)
		{
			pT->Lock();
			CComPtr<IUnknown> sp = m_vec.GetAt(nConnectionIndex);
			pT->Unlock();
         CComQIPtr<IStrainLoadsEvents> events(sp);
         if ( events )
            events->OnStrainLoadsBeforeRemove(Load);
		}
	}
};


template <class T>
class CProxyDPointLoadEvents : public IConnectionPointImpl<T, &IID_IPointLoadEvents, CComDynamicUnkArray>
{
	//Warning this class may be recreated by the wizard.
public:
	VOID Fire_OnPointLoadChanged(IPointLoad * me)
	{
		T* pT = static_cast<T*>(this);
		int nConnectionIndex;
		int nConnections = m_vec.GetSize();
		
		for (nConnectionIndex = 0; nConnectionIndex < nConnections; nConnectionIndex++)
		{
			pT->Lock();
			CComPtr<IUnknown> sp = m_vec.GetAt(nConnectionIndex);
			pT->Unlock();
         CComQIPtr<IPointLoadEvents> events(sp);
         if ( events )
            events->OnPointLoadChanged(me);
		}
	}
};

template <class T>
class CProxyDPointLoadsEvents : public IConnectionPointImpl<T, &IID_IPointLoadsEvents, CComDynamicUnkArray>
{
	//Warning this class may be recreated by the wizard.
public:
	VOID Fire_OnPointLoadsChanged(IPointLoadItem * Load)
	{
		T* pT = static_cast<T*>(this);
		int nConnectionIndex;
		int nConnections = m_vec.GetSize();
		
		for (nConnectionIndex = 0; nConnectionIndex < nConnections; nConnectionIndex++)
		{
			pT->Lock();
			CComPtr<IUnknown> sp = m_vec.GetAt(nConnectionIndex);
			pT->Unlock();
         CComQIPtr<IPointLoadsEvents> events(sp);
         if ( events )
            events->OnPointLoadsChanged(Load);
		}
	}
	VOID Fire_OnPointLoadsAdded(IPointLoadItem * Load)
	{
		T* pT = static_cast<T*>(this);
		int nConnectionIndex;
		int nConnections = m_vec.GetSize();
		
		for (nConnectionIndex = 0; nConnectionIndex < nConnections; nConnectionIndex++)
		{
			pT->Lock();
			CComPtr<IUnknown> sp = m_vec.GetAt(nConnectionIndex);
			pT->Unlock();
         CComQIPtr<IPointLoadsEvents> events(sp);
         if ( events )
            events->OnPointLoadsAdded(Load);
		}
	}
	VOID Fire_OnPointLoadsBeforeRemove(IPointLoadItem * Load)
	{
		T* pT = static_cast<T*>(this);
		int nConnectionIndex;
		int nConnections = m_vec.GetSize();
		
		for (nConnectionIndex = 0; nConnectionIndex < nConnections; nConnectionIndex++)
		{
			pT->Lock();
			CComPtr<IUnknown> sp = m_vec.GetAt(nConnectionIndex);
			pT->Unlock();
         CComQIPtr<IPointLoadsEvents> events(sp);
         if ( events )
            events->OnPointLoadsBeforeRemove(Load);
		}
	}
};




#endif