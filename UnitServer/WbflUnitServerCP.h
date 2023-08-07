#ifndef _WBFLUNITSERVERCP_H_
#define _WBFLUNITSERVERCP_H_


template <class T>
class CProxyDUnitSystemEvents : public IConnectionPointImpl<T, &IID_IUnitSystemEvents, CComDynamicUnkArray>
{
	//Warning this class may be recreated by the wizard.
public:
	VOID Fire_OnUpdateDisplay()
	{
		T* pT = static_cast<T*>(this);
		int nConnectionIndex;
		int nConnections = this->m_vec.GetSize();
		
		for (nConnectionIndex = 0; nConnectionIndex < nConnections; nConnectionIndex++)
		{
			pT->Lock();
			CComPtr<IUnknown> sp = this->m_vec.GetAt(nConnectionIndex);
			pT->Unlock();
         CComQIPtr<IUnitSystemEvents> events(sp);
         if ( events ) 
            events->OnUpdateDisplay();
		}
	
	}
	VOID Fire_OnUnitServerChanged()
	{
		T* pT = static_cast<T*>(this);
		int nConnectionIndex;
		int nConnections = this->m_vec.GetSize();
		
		for (nConnectionIndex = 0; nConnectionIndex < nConnections; nConnectionIndex++)
		{
			pT->Lock();
			CComPtr<IUnknown> sp = this->m_vec.GetAt(nConnectionIndex);
			pT->Unlock();
         CComQIPtr<IUnitSystemEvents> events(sp);
         if ( events )
            events->OnUnitServerChanged();
		}
	
	}
};

template <class T>
class CProxyDDisplayUnitEvents : public IConnectionPointImpl<T, &IID_IDisplayUnitEvents, CComDynamicUnkArray>
{
	//Warning this class may be recreated by the wizard.
public:
	VOID Fire_OnFormatChanged(IDisplayUnit * displayUnit)
	{
		T* pT = static_cast<T*>(this);
		int nConnectionIndex;
		int nConnections = this->m_vec.GetSize();
		
		for (nConnectionIndex = 0; nConnectionIndex < nConnections; nConnectionIndex++)
		{
			pT->Lock();
			CComPtr<IUnknown> sp = this->m_vec.GetAt(nConnectionIndex);
			pT->Unlock();
         CComQIPtr<IDisplayUnitEvents> events(sp);
         if ( events )
            events->OnFormatChanged(displayUnit);
		}
	
	}
};

template <class T>
class CProxyDDisplayUnitGroupEvents : public IConnectionPointImpl<T, &IID_IDisplayUnitGroupEvents, CComDynamicUnkArray>
{
	//Warning this class may be recreated by the wizard.
public:
	VOID Fire_OnFormatChanged(IDisplayUnitGroup * group, IDisplayUnit * displayUnit)
	{
		T* pT = static_cast<T*>(this);
		int nConnectionIndex;
		int nConnections = this->m_vec.GetSize();
		
		for (nConnectionIndex = 0; nConnectionIndex < nConnections; nConnectionIndex++)
		{
			pT->Lock();
			CComPtr<IUnknown> sp = this->m_vec.GetAt(nConnectionIndex);
			pT->Unlock();
         CComQIPtr<IDisplayUnitGroupEvents> events(sp);
         if ( events ) 
            events->OnFormatChanged(group,displayUnit);
		}
	
	}
	VOID Fire_OnDisplayUnitCreated(IDisplayUnitGroup * group, IDisplayUnit * displayUnit)
	{
		T* pT = static_cast<T*>(this);
		int nConnectionIndex;
		int nConnections = this->m_vec.GetSize();
		
		for (nConnectionIndex = 0; nConnectionIndex < nConnections; nConnectionIndex++)
		{
			pT->Lock();
			CComPtr<IUnknown> sp = this->m_vec.GetAt(nConnectionIndex);
			pT->Unlock();
         CComQIPtr<IDisplayUnitGroupEvents> events(sp);
         if ( events ) 
            events->OnDisplayUnitCreated(group,displayUnit);
		}
	
	}
	VOID Fire_OnDisplayUnitRemoved(IDisplayUnitGroup * group, BSTR displayUnit)
	{
		T* pT = static_cast<T*>(this);
		int nConnectionIndex;
		int nConnections = this->m_vec.GetSize();
		
		for (nConnectionIndex = 0; nConnectionIndex < nConnections; nConnectionIndex++)
		{
			pT->Lock();
			CComPtr<IUnknown> sp = this->m_vec.GetAt(nConnectionIndex);
			pT->Unlock();
         CComQIPtr<IDisplayUnitGroupEvents> events(sp);
         if ( events ) 
            events->OnDisplayUnitRemoved(group,displayUnit);
		}
	}
	VOID Fire_OnDisplayUnitGroupCleared(IDisplayUnitGroup * group)
	{
		T* pT = static_cast<T*>(this);
		int nConnectionIndex;
		int nConnections = this->m_vec.GetSize();
		
		for (nConnectionIndex = 0; nConnectionIndex < nConnections; nConnectionIndex++)
		{
			pT->Lock();
			CComPtr<IUnknown> sp = this->m_vec.GetAt(nConnectionIndex);
			pT->Unlock();
         CComQIPtr<IDisplayUnitGroupEvents> events(sp);
         if ( events ) 
            events->OnDisplayUnitGroupCleared(group);
		}
	}
};


template <class T>
class CProxyDDisplayUnitMgrEvents : public IConnectionPointImpl<T, &IID_IDisplayUnitMgrEvents, CComDynamicUnkArray>
{
	//Warning this class may be recreated by the wizard.
public:
	VOID Fire_OnFormatChanged(IDisplayUnitGroup * group, IDisplayUnit * displayUnit)
	{
		T* pT = static_cast<T*>(this);
		int nConnectionIndex;
		int nConnections = this->m_vec.GetSize();
		
		for (nConnectionIndex = 0; nConnectionIndex < nConnections; nConnectionIndex++)
		{
			pT->Lock();
			CComPtr<IUnknown> sp = this->m_vec.GetAt(nConnectionIndex);
			pT->Unlock();
         CComQIPtr<IDisplayUnitMgrEvents> events(sp);
         if ( events )
            events->OnFormatChanged(group,displayUnit);
		}
	
	}
	VOID Fire_OnDisplayUnitCreated(IDisplayUnitGroup * group, IDisplayUnit * displayUnit)
	{
		T* pT = static_cast<T*>(this);
		int nConnectionIndex;
		int nConnections = this->m_vec.GetSize();
		
		for (nConnectionIndex = 0; nConnectionIndex < nConnections; nConnectionIndex++)
		{
			pT->Lock();
			CComPtr<IUnknown> sp = this->m_vec.GetAt(nConnectionIndex);
			pT->Unlock();
         CComQIPtr<IDisplayUnitMgrEvents> events(sp);
         if ( events )
            events->OnDisplayUnitCreated(group,displayUnit);
		}
	
	}
	VOID Fire_OnDisplayUnitRemoved(IDisplayUnitGroup * group, BSTR displayUnit)
	{
		T* pT = static_cast<T*>(this);
		int nConnectionIndex;
		int nConnections = this->m_vec.GetSize();
		
		for (nConnectionIndex = 0; nConnectionIndex < nConnections; nConnectionIndex++)
		{
			pT->Lock();
			CComPtr<IUnknown> sp = this->m_vec.GetAt(nConnectionIndex);
			pT->Unlock();
         CComQIPtr<IDisplayUnitMgrEvents> events(sp);
         if ( events )
            events->OnDisplayUnitRemoved(group,displayUnit);
		}
	
	}
	VOID Fire_OnDisplayUnitGroupCleared(IDisplayUnitGroup * group)
	{
		T* pT = static_cast<T*>(this);
		int nConnectionIndex;
		int nConnections = this->m_vec.GetSize();
		
		for (nConnectionIndex = 0; nConnectionIndex < nConnections; nConnectionIndex++)
		{
			pT->Lock();
			CComPtr<IUnknown> sp = this->m_vec.GetAt(nConnectionIndex);
			pT->Unlock();
         CComQIPtr<IDisplayUnitMgrEvents> events(sp);
         if ( events )
            events->OnDisplayUnitGroupCleared(group);
		}
	
	}
	VOID Fire_OnDisplayUnitGroupCreated(IDisplayUnitGroup * group)
	{
		T* pT = static_cast<T*>(this);
		int nConnectionIndex;
		int nConnections = this->m_vec.GetSize();
		
		for (nConnectionIndex = 0; nConnectionIndex < nConnections; nConnectionIndex++)
		{
			pT->Lock();
			CComPtr<IUnknown> sp = this->m_vec.GetAt(nConnectionIndex);
			pT->Unlock();
         CComQIPtr<IDisplayUnitMgrEvents> events(sp);
         if ( events )
            events->OnDisplayUnitGroupCreated(group);
		}
	
	}
	VOID Fire_OnDisplayUnitGroupRemoved(BSTR group)
	{
		T* pT = static_cast<T*>(this);
		int nConnectionIndex;
		int nConnections = this->m_vec.GetSize();
		
		for (nConnectionIndex = 0; nConnectionIndex < nConnections; nConnectionIndex++)
		{
			pT->Lock();
			CComPtr<IUnknown> sp = this->m_vec.GetAt(nConnectionIndex);
			pT->Unlock();
         CComQIPtr<IDisplayUnitMgrEvents> events(sp);
         if ( events )
            events->OnDisplayUnitGroupRemoved(group);
		}
	
	}
	VOID Fire_OnDisplayUnitGroupsCleared()
	{
		T* pT = static_cast<T*>(this);
		int nConnectionIndex;
		int nConnections = this->m_vec.GetSize();
		
		for (nConnectionIndex = 0; nConnectionIndex < nConnections; nConnectionIndex++)
		{
			pT->Lock();
			CComPtr<IUnknown> sp = this->m_vec.GetAt(nConnectionIndex);
			pT->Unlock();
         CComQIPtr<IDisplayUnitMgrEvents> events(sp);
         if ( events )
            events->OnDisplayUnitGroupsCleared();
		}
	
	}
};


template <class T>
class CProxyDUnitModeControllerEvents : public IConnectionPointImpl<T, &IID_IUnitModeControllerEvents, CComDynamicUnkArray>
{
	//Warning this class may be recreated by the wizard.
public:
	VOID Fire_OnUnitModeChanged(UnitModeType newMode)
	{
		T* pT = static_cast<T*>(this);
		int nConnectionIndex;
		int nConnections = this->m_vec.GetSize();
		
		for (nConnectionIndex = 0; nConnectionIndex < nConnections; nConnectionIndex++)
		{
			pT->Lock();
			CComPtr<IUnknown> sp = this->m_vec.GetAt(nConnectionIndex);
			pT->Unlock();
         CComQIPtr<IUnitModeControllerEvents> events(sp);
         if ( events )
            events->OnUnitModeChanged(newMode);
		}
	}
};

template <class T>
class CProxyDUnitsEvents : public IConnectionPointImpl<T, &IID_IUnitsEvents, CComDynamicUnkArray>
{
	//Warning this class may be recreated by the wizard.
public:
	VOID Fire_OnUnitAdded(IUnit * Unit)
	{
		T* pT = static_cast<T*>(this);
		int nConnectionIndex;
		int nConnections = this->m_vec.GetSize();
		
		for (nConnectionIndex = 0; nConnectionIndex < nConnections; nConnectionIndex++)
		{
			pT->Lock();
			CComPtr<IUnknown> sp = this->m_vec.GetAt(nConnectionIndex);
			pT->Unlock();
         CComQIPtr<IUnitsEvents> events(sp);
         if ( events )
            events->OnUnitAdded(Unit);
		}
	}
	VOID Fire_OnUnitRemoved(BSTR Unit)
	{
		T* pT = static_cast<T*>(this);
		int nConnectionIndex;
		int nConnections = this->m_vec.GetSize();
		
		for (nConnectionIndex = 0; nConnectionIndex < nConnections; nConnectionIndex++)
		{
			pT->Lock();
			CComPtr<IUnknown> sp = this->m_vec.GetAt(nConnectionIndex);
			pT->Unlock();
         CComQIPtr<IUnitsEvents> events(sp);
         if ( events )
            events->OnUnitRemoved(Unit);
		}
	}
	VOID Fire_OnUnitsCleared()
	{
		T* pT = static_cast<T*>(this);
		int nConnectionIndex;
		int nConnections = this->m_vec.GetSize();
		
		for (nConnectionIndex = 0; nConnectionIndex < nConnections; nConnectionIndex++)
		{
			pT->Lock();
			CComPtr<IUnknown> sp = this->m_vec.GetAt(nConnectionIndex);
			pT->Unlock();
         CComQIPtr<IUnitsEvents> events(sp);
         if ( events )
            events->OnUnitsCleared();
		}
	}
};

template <class T>
class CProxyDUnitServerEvents : public IConnectionPointImpl<T, &IID_IUnitServerEvents, CComDynamicUnkArray>
{
	//Warning this class may be recreated by the wizard.
public:
	VOID Fire_OnUnitAdded(IUnitType * UnitType, IUnit * Unit)
	{
		T* pT = static_cast<T*>(this);
		int nConnectionIndex;
		int nConnections = this->m_vec.GetSize();
		
		for (nConnectionIndex = 0; nConnectionIndex < nConnections; nConnectionIndex++)
		{
			pT->Lock();
			CComPtr<IUnknown> sp = this->m_vec.GetAt(nConnectionIndex);
			pT->Unlock();
         CComQIPtr<IUnitServerEvents> events(sp);
         if ( events )
            events->OnUnitAdded(UnitType,Unit);
		}
	}
	VOID Fire_OnUnitRemoved(IUnitType * UnitType, BSTR Unit)
	{
		T* pT = static_cast<T*>(this);
		int nConnectionIndex;
		int nConnections = this->m_vec.GetSize();
		
		for (nConnectionIndex = 0; nConnectionIndex < nConnections; nConnectionIndex++)
		{
			pT->Lock();
			CComPtr<IUnknown> sp = this->m_vec.GetAt(nConnectionIndex);
			pT->Unlock();
         CComQIPtr<IUnitServerEvents> events(sp);
         if ( events )
            events->OnUnitRemoved(UnitType,Unit);
		}
	}
	VOID Fire_OnUnitsCleared(IUnitType * UnitType)
	{
		T* pT = static_cast<T*>(this);
		int nConnectionIndex;
		int nConnections = this->m_vec.GetSize();
		
		for (nConnectionIndex = 0; nConnectionIndex < nConnections; nConnectionIndex++)
		{
			pT->Lock();
			CComPtr<IUnknown> sp = this->m_vec.GetAt(nConnectionIndex);
			pT->Unlock();
         CComQIPtr<IUnitServerEvents> events(sp);
         if ( events )
            events->OnUnitsCleared(UnitType);
		}
	}
	VOID Fire_OnUnitTypeAdded(IUnitType * UnitType)
	{
		T* pT = static_cast<T*>(this);
		int nConnectionIndex;
		int nConnections = this->m_vec.GetSize();
		
		for (nConnectionIndex = 0; nConnectionIndex < nConnections; nConnectionIndex++)
		{
			pT->Lock();
			CComPtr<IUnknown> sp = this->m_vec.GetAt(nConnectionIndex);
			pT->Unlock();
         CComQIPtr<IUnitServerEvents> events(sp);
         if ( events )
            events->OnUnitTypeAdded(UnitType);
		}
	}
	VOID Fire_OnUnitTypeRemoved(BSTR UnitType)
	{
		T* pT = static_cast<T*>(this);
		int nConnectionIndex;
		int nConnections = this->m_vec.GetSize();
		
		for (nConnectionIndex = 0; nConnectionIndex < nConnections; nConnectionIndex++)
		{
			pT->Lock();
			CComPtr<IUnknown> sp = this->m_vec.GetAt(nConnectionIndex);
			pT->Unlock();
         CComQIPtr<IUnitServerEvents> events(sp);
         if ( events )
            events->OnUnitTypeRemoved(UnitType);
		}
	}
	VOID Fire_OnUnitTypesCleared()
	{
		T* pT = static_cast<T*>(this);
		int nConnectionIndex;
		int nConnections = this->m_vec.GetSize();
		
		for (nConnectionIndex = 0; nConnectionIndex < nConnections; nConnectionIndex++)
		{
			pT->Lock();
			CComPtr<IUnknown> sp = this->m_vec.GetAt(nConnectionIndex);
			pT->Unlock();
         CComQIPtr<IUnitServerEvents> events(sp);
         if ( events )
            events->OnUnitTypesCleared();
		}
	}
};

template <class T>
class CProxyDUnitTypeEvents : public IConnectionPointImpl<T, &IID_IUnitTypeEvents, CComDynamicUnkArray>
{
	//Warning this class may be recreated by the wizard.
public:
	VOID Fire_OnUnitAdded(IUnitType * UnitType, IUnit * Unit)
	{
		T* pT = static_cast<T*>(this);
		int nConnectionIndex;
		int nConnections = this->m_vec.GetSize();
		
		for (nConnectionIndex = 0; nConnectionIndex < nConnections; nConnectionIndex++)
		{
			pT->Lock();
			CComPtr<IUnknown> sp = this->m_vec.GetAt(nConnectionIndex);
			pT->Unlock();
         CComQIPtr<IUnitTypeEvents> events(sp);
         if ( events )
            events->OnUnitAdded(UnitType,Unit);
		}
	}
	VOID Fire_OnUnitRemoved(IUnitType * UnitType, BSTR Unit)
	{
		T* pT = static_cast<T*>(this);
		int nConnectionIndex;
		int nConnections = this->m_vec.GetSize();
		
		for (nConnectionIndex = 0; nConnectionIndex < nConnections; nConnectionIndex++)
		{
			pT->Lock();
			CComPtr<IUnknown> sp = this->m_vec.GetAt(nConnectionIndex);
			pT->Unlock();
         CComQIPtr<IUnitTypeEvents> events(sp);
         if ( events )
            events->OnUnitRemoved(UnitType,Unit);
		}
	}
	VOID Fire_OnUnitsCleared(IUnitType * UnitType)
	{
		T* pT = static_cast<T*>(this);
		int nConnectionIndex;
		int nConnections = this->m_vec.GetSize();
		
		for (nConnectionIndex = 0; nConnectionIndex < nConnections; nConnectionIndex++)
		{
			pT->Lock();
			CComPtr<IUnknown> sp = this->m_vec.GetAt(nConnectionIndex);
			pT->Unlock();
         CComQIPtr<IUnitTypeEvents> events(sp);
         if ( events )
            events->OnUnitsCleared(UnitType);
		}
	}
};

template <class T>
class CProxyDUnitTypesEvents : public IConnectionPointImpl<T, &IID_IUnitTypesEvents, CComDynamicUnkArray>
{
	//Warning this class may be recreated by the wizard.
public:
	VOID Fire_OnUnitAdded(IUnitType * UnitType, IUnit * Unit)
	{
		T* pT = static_cast<T*>(this);
		int nConnectionIndex;
		int nConnections = this->m_vec.GetSize();
		
		for (nConnectionIndex = 0; nConnectionIndex < nConnections; nConnectionIndex++)
		{
			pT->Lock();
			CComPtr<IUnknown> sp = this->m_vec.GetAt(nConnectionIndex);
			pT->Unlock();
         CComQIPtr<IUnitTypesEvents> events(sp);
         if ( events )
            events->OnUnitAdded(UnitType,Unit);
		}
	}
	VOID Fire_OnUnitRemoved(IUnitType * UnitType, BSTR Unit)
	{
		T* pT = static_cast<T*>(this);
		int nConnectionIndex;
		int nConnections = this->m_vec.GetSize();
		
		for (nConnectionIndex = 0; nConnectionIndex < nConnections; nConnectionIndex++)
		{
			pT->Lock();
			CComPtr<IUnknown> sp = this->m_vec.GetAt(nConnectionIndex);
			pT->Unlock();
         CComQIPtr<IUnitTypesEvents> events(sp);
         if ( events )
            events->OnUnitRemoved(UnitType,Unit);
		}
	}
	VOID Fire_OnUnitsCleared(IUnitType * UnitType)
	{
		T* pT = static_cast<T*>(this);
		int nConnectionIndex;
		int nConnections = this->m_vec.GetSize();
		
		for (nConnectionIndex = 0; nConnectionIndex < nConnections; nConnectionIndex++)
		{
			pT->Lock();
			CComPtr<IUnknown> sp = this->m_vec.GetAt(nConnectionIndex);
			pT->Unlock();
         CComQIPtr<IUnitTypesEvents> events(sp);
         if ( events )
            events->OnUnitsCleared(UnitType);
		}
	}
	VOID Fire_OnUnitTypeAdded(IUnitType * UnitType)
	{
		T* pT = static_cast<T*>(this);
		int nConnectionIndex;
		int nConnections = this->m_vec.GetSize();
		
		for (nConnectionIndex = 0; nConnectionIndex < nConnections; nConnectionIndex++)
		{
			pT->Lock();
			CComPtr<IUnknown> sp = this->m_vec.GetAt(nConnectionIndex);
			pT->Unlock();
         CComQIPtr<IUnitTypesEvents> events(sp);
         if ( events )
            events->OnUnitTypeAdded(UnitType);
		}
	}
	VOID Fire_OnUnitTypeRemoved(BSTR UnitType)
	{
		T* pT = static_cast<T*>(this);
		int nConnectionIndex;
		int nConnections = this->m_vec.GetSize();
		
		for (nConnectionIndex = 0; nConnectionIndex < nConnections; nConnectionIndex++)
		{
			pT->Lock();
			CComPtr<IUnknown> sp = this->m_vec.GetAt(nConnectionIndex);
			pT->Unlock();
         CComQIPtr<IUnitTypesEvents> events(sp);
         if ( events )
            events->OnUnitTypeRemoved(UnitType);
		}
	}
	VOID Fire_OnUnitTypesCleared()
	{
		T* pT = static_cast<T*>(this);
		int nConnectionIndex;
		int nConnections = this->m_vec.GetSize();
		
		for (nConnectionIndex = 0; nConnectionIndex < nConnections; nConnectionIndex++)
		{
			pT->Lock();
			CComPtr<IUnknown> sp = this->m_vec.GetAt(nConnectionIndex);
			pT->Unlock();
         CComQIPtr<IUnitTypesEvents> events(sp);
         if ( events )
            events->OnUnitTypesCleared();
		}
	}
};

template <class T>
class CProxyDDisplayUnitFormatterEvents : public IConnectionPointImpl<T, &IID_IDisplayUnitFormatterEvents, CComDynamicUnkArray>
{
	//Warning this class may be recreated by the wizard.
public:
	VOID Fire_OnFormatChanged()
	{
		T* pT = static_cast<T*>(this);
		int nConnectionIndex;
		int nConnections = this->m_vec.GetSize();
		
		for (nConnectionIndex = 0; nConnectionIndex < nConnections; nConnectionIndex++)
		{
			pT->Lock();
			CComPtr<IUnknown> sp = this->m_vec.GetAt(nConnectionIndex);
			pT->Unlock();
         CComQIPtr<IDisplayUnitFormatterEvents> events(sp);
         if ( events )
            events->OnFormatChanged();
		}
	}
};


template <class T>
class CProxyDDocUnitSystemEvents : public IConnectionPointImpl<T, &IID_IDocUnitSystemEvents, CComDynamicUnkArray>
{
	//Warning this class may be recreated by the wizard.
public:
	VOID Fire_OnUpdateDisplay()
	{
		T* pT = static_cast<T*>(this);
		int nConnectionIndex;
		int nConnections = this->m_vec.GetSize();
		
		for (nConnectionIndex = 0; nConnectionIndex < nConnections; nConnectionIndex++)
		{
			pT->Lock();
			CComPtr<IUnknown> sp = this->m_vec.GetAt(nConnectionIndex);
			pT->Unlock();
         CComQIPtr<IDocUnitSystemEvents> events(sp);
         if ( events )
            events->OnUpdateDisplay();
		}
	}
};
#endif