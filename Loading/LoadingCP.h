///////////////////////////////////////////////////////////////////////
// Loading - Generic library to describe bridge loadings
// Copyright © 1999-2017  Washington State Department of Transportation
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

#ifndef _LOADINGCP_H_
#define _LOADINGCP_H_

//template <class T>
//class CProxyDLoadCasesEvents : public IConnectionPointImpl<T, &DIID_DLoadCasesEvents, CComDynamicUnkArray>
//{
//	//Warning this class may be recreated by the wizard.
//public:
//	VOID Fire_QueryInterface(GUID * riid, VOID * * ppvObj)
//	{
//		T* pT = static_cast<T*>(this);
//		int nConnectionIndex;
//		CComVariant* pvars = new CComVariant[2];
//		int nConnections = m_vec.GetSize();
//		
//		for (nConnectionIndex = 0; nConnectionIndex < nConnections; nConnectionIndex++)
//		{
//			pT->Lock();
//			CComPtr<IUnknown> sp = m_vec.GetAt(nConnectionIndex);
//			pT->Unlock();
//			IDispatch* pDispatch = reinterpret_cast<IDispatch*>(sp.p);
//			if (pDispatch != NULL)
//			{
//				pvars[1] = riid;
//				pvars[0] = ppvObj;
//				DISPPARAMS disp = { pvars, NULL, 2, 0 };
//				pDispatch->Invoke(0x60000000, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_METHOD, &disp, NULL, NULL, NULL);
//			}
//		}
//		delete[] pvars;
//	
//	}
//	ULONG Fire_AddRef()
//	{
//		CComVariant varResult;
//		T* pT = static_cast<T*>(this);
//		int nConnectionIndex;
//		int nConnections = m_vec.GetSize();
//		
//		for (nConnectionIndex = 0; nConnectionIndex < nConnections; nConnectionIndex++)
//		{
//			pT->Lock();
//			CComPtr<IUnknown> sp = m_vec.GetAt(nConnectionIndex);
//			pT->Unlock();
//			IDispatch* pDispatch = reinterpret_cast<IDispatch*>(sp.p);
//			if (pDispatch != NULL)
//			{
//				VariantClear(&varResult);
//				DISPPARAMS disp = { NULL, NULL, 0, 0 };
//				pDispatch->Invoke(0x60000001, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_METHOD, &disp, &varResult, NULL, NULL);
//			}
//		}
//		return varResult.ulVal;
//	
//	}
//	ULONG Fire_Release()
//	{
//		CComVariant varResult;
//		T* pT = static_cast<T*>(this);
//		int nConnectionIndex;
//		int nConnections = m_vec.GetSize();
//		
//		for (nConnectionIndex = 0; nConnectionIndex < nConnections; nConnectionIndex++)
//		{
//			pT->Lock();
//			CComPtr<IUnknown> sp = m_vec.GetAt(nConnectionIndex);
//			pT->Unlock();
//			IDispatch* pDispatch = reinterpret_cast<IDispatch*>(sp.p);
//			if (pDispatch != NULL)
//			{
//				VariantClear(&varResult);
//				DISPPARAMS disp = { NULL, NULL, 0, 0 };
//				pDispatch->Invoke(0x60000002, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_METHOD, &disp, &varResult, NULL, NULL);
//			}
//		}
//		return varResult.ulVal;
//	
//	}
//	VOID Fire_GetTypeInfoCount(UINT * pctinfo)
//	{
//		T* pT = static_cast<T*>(this);
//		int nConnectionIndex;
//		CComVariant* pvars = new CComVariant[1];
//		int nConnections = m_vec.GetSize();
//		
//		for (nConnectionIndex = 0; nConnectionIndex < nConnections; nConnectionIndex++)
//		{
//			pT->Lock();
//			CComPtr<IUnknown> sp = m_vec.GetAt(nConnectionIndex);
//			pT->Unlock();
//			IDispatch* pDispatch = reinterpret_cast<IDispatch*>(sp.p);
//			if (pDispatch != NULL)
//			{
//				pvars[0] = pctinfo;
//				DISPPARAMS disp = { pvars, NULL, 1, 0 };
//				pDispatch->Invoke(0x60010000, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_METHOD, &disp, NULL, NULL, NULL);
//			}
//		}
//		delete[] pvars;
//	
//	}
//	VOID Fire_GetTypeInfo(UINT itinfo, ULONG lcid, VOID * * pptinfo)
//	{
//		T* pT = static_cast<T*>(this);
//		int nConnectionIndex;
//		CComVariant* pvars = new CComVariant[3];
//		int nConnections = m_vec.GetSize();
//		
//		for (nConnectionIndex = 0; nConnectionIndex < nConnections; nConnectionIndex++)
//		{
//			pT->Lock();
//			CComPtr<IUnknown> sp = m_vec.GetAt(nConnectionIndex);
//			pT->Unlock();
//			IDispatch* pDispatch = reinterpret_cast<IDispatch*>(sp.p);
//			if (pDispatch != NULL)
//			{
//				pvars[2] = itinfo;
//				pvars[1] = lcid;
//				pvars[0] = pptinfo;
//				DISPPARAMS disp = { pvars, NULL, 3, 0 };
//				pDispatch->Invoke(0x60010001, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_METHOD, &disp, NULL, NULL, NULL);
//			}
//		}
//		delete[] pvars;
//	
//	}
//	VOID Fire_GetIDsOfNames(GUID * riid, TCHAR*  * rgszNames, UINT cNames, ULONG lcid, LONG * rgdispid)
//	{
//		T* pT = static_cast<T*>(this);
//		int nConnectionIndex;
//		CComVariant* pvars = new CComVariant[5];
//		int nConnections = m_vec.GetSize();
//		
//		for (nConnectionIndex = 0; nConnectionIndex < nConnections; nConnectionIndex++)
//		{
//			pT->Lock();
//			CComPtr<IUnknown> sp = m_vec.GetAt(nConnectionIndex);
//			pT->Unlock();
//			IDispatch* pDispatch = reinterpret_cast<IDispatch*>(sp.p);
//			if (pDispatch != NULL)
//			{
//				pvars[4] = riid;
//				pvars[3] = rgszNames;
//				pvars[2] = cNames;
//				pvars[1] = lcid;
//				pvars[0] = rgdispid;
//				DISPPARAMS disp = { pvars, NULL, 5, 0 };
//				pDispatch->Invoke(0x60010002, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_METHOD, &disp, NULL, NULL, NULL);
//			}
//		}
//		delete[] pvars;
//	
//	}
//	VOID Fire_Invoke(LONG dispidMember, GUID * riid, ULONG lcid, USHORT wFlags, DISPPARAMS * pdispparams, VARIANT * pvarResult, EXCEPINFO * pexcepinfo, UINT * puArgErr)
//	{
//		T* pT = static_cast<T*>(this);
//		int nConnectionIndex;
//		CComVariant* pvars = new CComVariant[8];
//		int nConnections = m_vec.GetSize();
//		
//		for (nConnectionIndex = 0; nConnectionIndex < nConnections; nConnectionIndex++)
//		{
//			pT->Lock();
//			CComPtr<IUnknown> sp = m_vec.GetAt(nConnectionIndex);
//			pT->Unlock();
//			IDispatch* pDispatch = reinterpret_cast<IDispatch*>(sp.p);
//			if (pDispatch != NULL)
//			{
//				pvars[7] = dispidMember;
//				pvars[6] = riid;
//				pvars[5] = lcid;
//				pvars[4] = wFlags;
//				pvars[3] = pdispparams;
//				pvars[2] = pvarResult;
//				pvars[1] = pexcepinfo;
//				pvars[0] = puArgErr;
//				DISPPARAMS disp = { pvars, NULL, 8, 0 };
//				pDispatch->Invoke(0x60010003, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_METHOD, &disp, NULL, NULL, NULL);
//			}
//		}
//		delete[] pvars;
//	
//	}
//	VOID Fire_OnLoadCasesChanged(ldILoadCase * Load, ChangeType change)
//	{
//		T* pT = static_cast<T*>(this);
//		int nConnectionIndex;
//		CComVariant* pvars = new CComVariant[2];
//		int nConnections = m_vec.GetSize();
//		
//		for (nConnectionIndex = 0; nConnectionIndex < nConnections; nConnectionIndex++)
//		{
//			pT->Lock();
//			CComPtr<IUnknown> sp = m_vec.GetAt(nConnectionIndex);
//			pT->Unlock();
//			IDispatch* pDispatch = reinterpret_cast<IDispatch*>(sp.p);
//			if (pDispatch != NULL)
//			{
//				pvars[1] = Load;
//				pvars[0] = change;
//				DISPPARAMS disp = { pvars, NULL, 2, 0 };
//				pDispatch->Invoke(cttLoadCasesChanged, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_METHOD, &disp, NULL, NULL, NULL);
//			}
//		}
//		delete[] pvars;
//	
//	}
//	VOID Fire_OnLoadCasesRenamed(BSTR oldName, BSTR newName)
//	{
//		T* pT = static_cast<T*>(this);
//		int nConnectionIndex;
//		CComVariant* pvars = new CComVariant[2];
//		int nConnections = m_vec.GetSize();
//		
//		for (nConnectionIndex = 0; nConnectionIndex < nConnections; nConnectionIndex++)
//		{
//			pT->Lock();
//			CComPtr<IUnknown> sp = m_vec.GetAt(nConnectionIndex);
//			pT->Unlock();
//			IDispatch* pDispatch = reinterpret_cast<IDispatch*>(sp.p);
//			if (pDispatch != NULL)
//			{
//				pvars[1] = oldName;
//				pvars[0] = newName;
//				DISPPARAMS disp = { pvars, NULL, 2, 0 };
//				pDispatch->Invoke(cttLoadCasesRenamed, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_METHOD, &disp, NULL, NULL, NULL);
//			}
//		}
//		delete[] pvars;
//	
//	}
//	VOID Fire_OnLoadCasesAdded(ldILoadCase * Load)
//	{
//		T* pT = static_cast<T*>(this);
//		int nConnectionIndex;
//		CComVariant* pvars = new CComVariant[1];
//		int nConnections = m_vec.GetSize();
//		
//		for (nConnectionIndex = 0; nConnectionIndex < nConnections; nConnectionIndex++)
//		{
//			pT->Lock();
//			CComPtr<IUnknown> sp = m_vec.GetAt(nConnectionIndex);
//			pT->Unlock();
//			IDispatch* pDispatch = reinterpret_cast<IDispatch*>(sp.p);
//			if (pDispatch != NULL)
//			{
//				pvars[0] = Load;
//				DISPPARAMS disp = { pvars, NULL, 1, 0 };
//				pDispatch->Invoke(cttLoadCasesAdded, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_METHOD, &disp, NULL, NULL, NULL);
//			}
//		}
//		delete[] pvars;
//	
//	}
//	VOID Fire_OnLoadCasesBeforeRemove(ldILoadCase * Load)
//	{
//		T* pT = static_cast<T*>(this);
//		int nConnectionIndex;
//		CComVariant* pvars = new CComVariant[1];
//		int nConnections = m_vec.GetSize();
//		
//		for (nConnectionIndex = 0; nConnectionIndex < nConnections; nConnectionIndex++)
//		{
//			pT->Lock();
//			CComPtr<IUnknown> sp = m_vec.GetAt(nConnectionIndex);
//			pT->Unlock();
//			IDispatch* pDispatch = reinterpret_cast<IDispatch*>(sp.p);
//			if (pDispatch != NULL)
//			{
//				pvars[0] = Load;
//				DISPPARAMS disp = { pvars, NULL, 1, 0 };
//				pDispatch->Invoke(cttLoadCasesBeforeRemove, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_METHOD, &disp, NULL, NULL, NULL);
//			}
//		}
//		delete[] pvars;
//	
//	}
//};


template <class T>
class CProxyDDistributedLoadEvents : public IConnectionPointImpl<T, &IID_ldIDistributedLoadEvents, CComDynamicUnkArray>
{
	//Warning this class may be recreated by the wizard.
public:
	VOID Fire_OnDistributedLoadChanged(ldIDistributedLoad * me)
	{
		T* pT = static_cast<T*>(this);
		int nConnectionIndex;
		int nConnections = m_vec.GetSize();
		
		for (nConnectionIndex = 0; nConnectionIndex < nConnections; nConnectionIndex++)
		{
			pT->Lock();
			CComPtr<IUnknown> sp = m_vec.GetAt(nConnectionIndex);
			pT->Unlock();
         CComQIPtr<ldIDistributedLoadEvents> events(sp);
         if (events)
            events->OnDistributedLoadChanged(me);
		}
	}
};

template <class T>
class CProxyDDistributedLoadsEvents : public IConnectionPointImpl<T, &IID_ldIDistributedLoadsEvents, CComDynamicUnkArray>
{
	//Warning this class may be recreated by the wizard.
public:
	VOID Fire_OnDistributedLoadsChanged(ldIDistributedLoadItem * Load)
	{
		T* pT = static_cast<T*>(this);
		int nConnectionIndex;
		int nConnections = m_vec.GetSize();
		
		for (nConnectionIndex = 0; nConnectionIndex < nConnections; nConnectionIndex++)
		{
			pT->Lock();
			CComPtr<IUnknown> sp = m_vec.GetAt(nConnectionIndex);
			pT->Unlock();
         CComQIPtr<ldIDistributedLoadsEvents> events(sp);
         if ( events )
            events->OnDistributedLoadsChanged(Load);
		}
	}
	VOID Fire_OnDistributedLoadsAdded(ldIDistributedLoadItem * Load)
	{
		T* pT = static_cast<T*>(this);
		int nConnectionIndex;
		int nConnections = m_vec.GetSize();
		
		for (nConnectionIndex = 0; nConnectionIndex < nConnections; nConnectionIndex++)
		{
			pT->Lock();
			CComPtr<IUnknown> sp = m_vec.GetAt(nConnectionIndex);
			pT->Unlock();
         CComQIPtr<ldIDistributedLoadsEvents> events(sp);
         if ( events )
            events->OnDistributedLoadsAdded(Load);
		}
	}
	VOID Fire_OnDistributedLoadsBeforeRemove(ldIDistributedLoadItem * Load)
	{
		T* pT = static_cast<T*>(this);
		int nConnectionIndex;
		int nConnections = m_vec.GetSize();
		
		for (nConnectionIndex = 0; nConnectionIndex < nConnections; nConnectionIndex++)
		{
			pT->Lock();
			CComPtr<IUnknown> sp = m_vec.GetAt(nConnectionIndex);
			pT->Unlock();
         CComQIPtr<ldIDistributedLoadsEvents> events(sp);
         if ( events )
            events->OnDistributedLoadsBeforeRemove(Load);
		}
	}
};

template <class T>
class CProxyDSettlementLoadEvents : public IConnectionPointImpl<T, &IID_ldISettlementLoadEvents, CComDynamicUnkArray>
{
	//Warning this class may be recreated by the wizard.
public:
	VOID Fire_OnSettlementLoadChanged(ldISettlementLoad * me)
	{
		T* pT = static_cast<T*>(this);
		int nConnectionIndex;
		int nConnections = m_vec.GetSize();
		
		for (nConnectionIndex = 0; nConnectionIndex < nConnections; nConnectionIndex++)
		{
			pT->Lock();
			CComPtr<IUnknown> sp = m_vec.GetAt(nConnectionIndex);
			pT->Unlock();
         CComQIPtr<ldISettlementLoadEvents> events(sp);
         if ( events )
            events->OnSettlementLoadChanged(me);
		}
	}
};

template <class T>
class CProxyDSettlementLoadsEvents : public IConnectionPointImpl<T, &IID_ldISettlementLoadsEvents, CComDynamicUnkArray>
{
	//Warning this class may be recreated by the wizard.
public:
	VOID Fire_OnSettlementLoadsChanged(ldISettlementLoadItem * Load)
	{
		T* pT = static_cast<T*>(this);
		int nConnectionIndex;
		int nConnections = m_vec.GetSize();
		
		for (nConnectionIndex = 0; nConnectionIndex < nConnections; nConnectionIndex++)
		{
			pT->Lock();
			CComPtr<IUnknown> sp = m_vec.GetAt(nConnectionIndex);
			pT->Unlock();
         CComQIPtr<ldISettlementLoadsEvents> events(sp);
         if ( events )
            events->OnSettlementLoadsChanged(Load);
		}
	}
	VOID Fire_OnSettlementLoadsAdded(ldISettlementLoadItem * Load)
	{
		T* pT = static_cast<T*>(this);
		int nConnectionIndex;
		int nConnections = m_vec.GetSize();
		
		for (nConnectionIndex = 0; nConnectionIndex < nConnections; nConnectionIndex++)
		{
			pT->Lock();
			CComPtr<IUnknown> sp = m_vec.GetAt(nConnectionIndex);
			pT->Unlock();
         CComQIPtr<ldISettlementLoadsEvents> events(sp);
         if ( events )
            events->OnSettlementLoadsAdded(Load);
		}
	}
	VOID Fire_OnSettlementLoadsBeforeRemove(ldISettlementLoadItem * Load)
	{
		T* pT = static_cast<T*>(this);
		int nConnectionIndex;
		int nConnections = m_vec.GetSize();
		
		for (nConnectionIndex = 0; nConnectionIndex < nConnections; nConnectionIndex++)
		{
			pT->Lock();
			CComPtr<IUnknown> sp = m_vec.GetAt(nConnectionIndex);
			pT->Unlock();
         CComQIPtr<ldISettlementLoadsEvents> events(sp);
         if ( events )
            events->OnSettlementLoadsBeforeRemove(Load);
		}
	}
};

template <class T>
class CProxyDTemperatureLoadEvents : public IConnectionPointImpl<T, &IID_ldITemperatureLoadEvents, CComDynamicUnkArray>
{
	//Warning this class may be recreated by the wizard.
public:
	VOID Fire_OnTemperatureLoadChanged(ldITemperatureLoad * me)
	{
		T* pT = static_cast<T*>(this);
		int nConnectionIndex;
		int nConnections = m_vec.GetSize();
		
		for (nConnectionIndex = 0; nConnectionIndex < nConnections; nConnectionIndex++)
		{
			pT->Lock();
			CComPtr<IUnknown> sp = m_vec.GetAt(nConnectionIndex);
			pT->Unlock();
         CComQIPtr<ldITemperatureLoadEvents> events(sp);
         if ( events )
            events->OnTemperatureLoadChanged(me);
		}
	}
};


template <class T>
class CProxyDTemperatureLoadsEvents : public IConnectionPointImpl<T, &IID_ldITemperatureLoadsEvents, CComDynamicUnkArray>
{
	//Warning this class may be recreated by the wizard.
public:
	VOID Fire_OnTemperatureLoadsChanged(ldITemperatureLoadItem * Load)
	{
		T* pT = static_cast<T*>(this);
		int nConnectionIndex;
		int nConnections = m_vec.GetSize();
		
		for (nConnectionIndex = 0; nConnectionIndex < nConnections; nConnectionIndex++)
		{
			pT->Lock();
			CComPtr<IUnknown> sp = m_vec.GetAt(nConnectionIndex);
			pT->Unlock();
         CComQIPtr<ldITemperatureLoadsEvents> events(sp);
         if (events)
            events->OnTemperatureLoadsChanged(Load);
		}
	}
	VOID Fire_OnTemperatureLoadsAdded(ldITemperatureLoadItem * Load)
	{
		T* pT = static_cast<T*>(this);
		int nConnectionIndex;
		int nConnections = m_vec.GetSize();
		
		for (nConnectionIndex = 0; nConnectionIndex < nConnections; nConnectionIndex++)
		{
			pT->Lock();
			CComPtr<IUnknown> sp = m_vec.GetAt(nConnectionIndex);
			pT->Unlock();
         CComQIPtr<ldITemperatureLoadsEvents> events(sp);
         if (events)
            events->OnTemperatureLoadsAdded(Load);
		}
	}
	VOID Fire_OnTemperatureLoadsBeforeRemove(ldITemperatureLoadItem * Load)
	{
		T* pT = static_cast<T*>(this);
		int nConnectionIndex;
		int nConnections = m_vec.GetSize();
		
		for (nConnectionIndex = 0; nConnectionIndex < nConnections; nConnectionIndex++)
		{
			pT->Lock();
			CComPtr<IUnknown> sp = m_vec.GetAt(nConnectionIndex);
			pT->Unlock();
         CComQIPtr<ldITemperatureLoadsEvents> events(sp);
         if (events)
            events->OnTemperatureLoadsBeforeRemove(Load);
		}
	}
};

template <class T>
class CProxyDStrainLoadEvents : public IConnectionPointImpl<T, &IID_ldIStrainLoadEvents, CComDynamicUnkArray>
{
	//Warning this class may be recreated by the wizard.
public:
	VOID Fire_OnStrainLoadChanged(ldIStrainLoad * me)
	{
		T* pT = static_cast<T*>(this);
		int nConnectionIndex;
		int nConnections = m_vec.GetSize();
		
		for (nConnectionIndex = 0; nConnectionIndex < nConnections; nConnectionIndex++)
		{
			pT->Lock();
			CComPtr<IUnknown> sp = m_vec.GetAt(nConnectionIndex);
			pT->Unlock();
         CComQIPtr<ldIStrainLoadEvents> events(sp);
         if (events)
            events->OnStrainLoadChanged(me);
		}
	}
};

template <class T>
class CProxyDStrainLoadsEvents : public IConnectionPointImpl<T, &IID_ldIStrainLoadsEvents, CComDynamicUnkArray>
{
	//Warning this class may be recreated by the wizard.
public:
	VOID Fire_OnStrainLoadsChanged(ldIStrainLoadItem * Load)
	{
		T* pT = static_cast<T*>(this);
		int nConnectionIndex;
		int nConnections = m_vec.GetSize();
		
		for (nConnectionIndex = 0; nConnectionIndex < nConnections; nConnectionIndex++)
		{
			pT->Lock();
			CComPtr<IUnknown> sp = m_vec.GetAt(nConnectionIndex);
			pT->Unlock();
         CComQIPtr<ldIStrainLoadsEvents> events(sp);
         if ( events )
            events->OnStrainLoadsChanged(Load);
		}
	}
	VOID Fire_OnStrainLoadsAdded(ldIStrainLoadItem * Load)
	{
		T* pT = static_cast<T*>(this);
		int nConnectionIndex;
		int nConnections = m_vec.GetSize();
		
		for (nConnectionIndex = 0; nConnectionIndex < nConnections; nConnectionIndex++)
		{
			pT->Lock();
			CComPtr<IUnknown> sp = m_vec.GetAt(nConnectionIndex);
			pT->Unlock();
         CComQIPtr<ldIStrainLoadsEvents> events(sp);
         if ( events )
            events->OnStrainLoadsAdded(Load);
		}
	}
	VOID Fire_OnStrainLoadsBeforeRemove(ldIStrainLoadItem * Load)
	{
		T* pT = static_cast<T*>(this);
		int nConnectionIndex;
		int nConnections = m_vec.GetSize();
		
		for (nConnectionIndex = 0; nConnectionIndex < nConnections; nConnectionIndex++)
		{
			pT->Lock();
			CComPtr<IUnknown> sp = m_vec.GetAt(nConnectionIndex);
			pT->Unlock();
         CComQIPtr<ldIStrainLoadsEvents> events(sp);
         if ( events )
            events->OnStrainLoadsBeforeRemove(Load);
		}
	}

};


template <class T>
class CProxyDAxlesEvents : public IConnectionPointImpl<T, &IID_ldIAxlesEvents, CComDynamicUnkArray>
{
	//Warning this class may be recreated by the wizard.
public:
	VOID Fire_OnAxlesChanged(ldIAxle * Axle)
	{
		T* pT = static_cast<T*>(this);
		int nConnectionIndex;
		int nConnections = m_vec.GetSize();
		
		for (nConnectionIndex = 0; nConnectionIndex < nConnections; nConnectionIndex++)
		{
			pT->Lock();
			CComPtr<IUnknown> sp = m_vec.GetAt(nConnectionIndex);
			pT->Unlock();
         CComQIPtr<ldIAxlesEvents> events(sp);
         if (events)
            events->OnAxlesChanged(Axle);
		}
	}
	VOID Fire_OnAxlesAdded(ldIAxle * Axle, AxleIndexType position)
	{
		T* pT = static_cast<T*>(this);
		int nConnectionIndex;
		int nConnections = m_vec.GetSize();
		
		for (nConnectionIndex = 0; nConnectionIndex < nConnections; nConnectionIndex++)
		{
			pT->Lock();
			CComPtr<IUnknown> sp = m_vec.GetAt(nConnectionIndex);
			pT->Unlock();
         CComQIPtr<ldIAxlesEvents> events(sp);
         if (events)
            events->OnAxlesAdded(Axle,position);
		}
	}
	VOID Fire_OnAxlesBeforeRemove(ldIAxle * Axle, AxleIndexType position)
	{
		T* pT = static_cast<T*>(this);
		int nConnectionIndex;
		int nConnections = m_vec.GetSize();
		
		for (nConnectionIndex = 0; nConnectionIndex < nConnections; nConnectionIndex++)
		{
			pT->Lock();
			CComPtr<IUnknown> sp = m_vec.GetAt(nConnectionIndex);
			pT->Unlock();
         CComQIPtr<ldIAxlesEvents> events(sp);
         if (events)
            events->OnAxlesBeforeRemove(Axle,position);
		}
	}
	VOID Fire_OnAxlesMoveTo(AxleIndexType from, AxleIndexType to)
	{
		T* pT = static_cast<T*>(this);
		int nConnectionIndex;
		int nConnections = m_vec.GetSize();
		
		for (nConnectionIndex = 0; nConnectionIndex < nConnections; nConnectionIndex++)
		{
			pT->Lock();
			CComPtr<IUnknown> sp = m_vec.GetAt(nConnectionIndex);
			pT->Unlock();
         CComQIPtr<ldIAxlesEvents> events(sp);
         if (events)
            events->OnAxlesMoveTo(from,to);
		}
	}
	VOID Fire_OnAxlesCopyTo(AxleIndexType from, AxleIndexType to)
	{
		T* pT = static_cast<T*>(this);
		int nConnectionIndex;
		int nConnections = m_vec.GetSize();
		
		for (nConnectionIndex = 0; nConnectionIndex < nConnections; nConnectionIndex++)
		{
			pT->Lock();
			CComPtr<IUnknown> sp = m_vec.GetAt(nConnectionIndex);
			pT->Unlock();
         CComQIPtr<ldIAxlesEvents> events(sp);
         if (events)
            events->OnAxlesCopyTo(from,to);
		}
	}
	VOID Fire_OnAxlesReverse()
	{
		T* pT = static_cast<T*>(this);
		int nConnectionIndex;
		int nConnections = m_vec.GetSize();
		
		for (nConnectionIndex = 0; nConnectionIndex < nConnections; nConnectionIndex++)
		{
			pT->Lock();
			CComPtr<IUnknown> sp = m_vec.GetAt(nConnectionIndex);
			pT->Unlock();
         CComQIPtr<ldIAxlesEvents> events(sp);
         if (events)
            events->OnAxlesReverse();
		}
	}
};

template <class T>
class CProxyDAxleEvents : public IConnectionPointImpl<T, &IID_ldIAxleEvents, CComDynamicUnkArray>
{
	//Warning this class may be recreated by the wizard.
public:
	VOID Fire_OnAxleChanged(ldIAxle * me)
	{
		T* pT = static_cast<T*>(this);
		int nConnectionIndex;
		int nConnections = m_vec.GetSize();
		
		for (nConnectionIndex = 0; nConnectionIndex < nConnections; nConnectionIndex++)
		{
			pT->Lock();
			CComPtr<IUnknown> sp = m_vec.GetAt(nConnectionIndex);
			pT->Unlock();
         CComQIPtr<ldIAxleEvents> events(sp);
         if (events)
            events->OnAxleChanged(me);
		}
	}
};

template <class T>
class CProxyDVehicularLoadEvents : public IConnectionPointImpl<T, &IID_ldIVehicularLoadEvents, CComDynamicUnkArray>
{
	//Warning this class may be recreated by the wizard.
public:
	VOID Fire_OnVehicularLoadChanged(ldIVehicularLoad * me, ldLoadingChangeType type)
	{
		T* pT = static_cast<T*>(this);
		int nConnectionIndex;
		int nConnections = m_vec.GetSize();
		
		for (nConnectionIndex = 0; nConnectionIndex < nConnections; nConnectionIndex++)
		{
			pT->Lock();
			CComPtr<IUnknown> sp = m_vec.GetAt(nConnectionIndex);
			pT->Unlock();
         CComQIPtr<ldIVehicularLoadEvents> events(sp);
         if ( events )
            events->OnVehicularLoadChanged(me,type);
		}
	}
};

template <class T>
class CProxyDVehicularLoadsEvents : public IConnectionPointImpl<T, &IID_ldIVehicularLoadsEvents, CComDynamicUnkArray>
{
	//Warning this class may be recreated by the wizard.
public:
	VOID Fire_OnVehicularLoadsChanged(ldIVehicularLoad * Load, ldLoadingChangeType change)
	{
		T* pT = static_cast<T*>(this);
		int nConnectionIndex;
		int nConnections = m_vec.GetSize();
		
		for (nConnectionIndex = 0; nConnectionIndex < nConnections; nConnectionIndex++)
		{
			pT->Lock();
			CComPtr<IUnknown> sp = m_vec.GetAt(nConnectionIndex);
			pT->Unlock();
         CComQIPtr<ldIVehicularLoadsEvents> events(sp);
         if ( events )
            events->OnVehicularLoadsChanged(Load,change);
		}
	}
	VOID Fire_OnVehicularLoadsRenamed(BSTR oldName, BSTR newName)
	{
		T* pT = static_cast<T*>(this);
		int nConnectionIndex;
		int nConnections = m_vec.GetSize();
		
		for (nConnectionIndex = 0; nConnectionIndex < nConnections; nConnectionIndex++)
		{
			pT->Lock();
			CComPtr<IUnknown> sp = m_vec.GetAt(nConnectionIndex);
			pT->Unlock();
         CComQIPtr<ldIVehicularLoadsEvents> events(sp);
         if ( events )
            events->OnVehicularLoadsRenamed(oldName,newName);
		}
	}
	VOID Fire_OnVehicularLoadsAdded(ldIVehicularLoad * Load)
	{
		T* pT = static_cast<T*>(this);
		int nConnectionIndex;
		int nConnections = m_vec.GetSize();
		
		for (nConnectionIndex = 0; nConnectionIndex < nConnections; nConnectionIndex++)
		{
			pT->Lock();
			CComPtr<IUnknown> sp = m_vec.GetAt(nConnectionIndex);
			pT->Unlock();
         CComQIPtr<ldIVehicularLoadsEvents> events(sp);
         if ( events )
            events->OnVehicularLoadsAdded(Load);
		}
	}
	VOID Fire_OnVehicularLoadsBeforeRemove(ldIVehicularLoad * Load)
	{
		T* pT = static_cast<T*>(this);
		int nConnectionIndex;
		int nConnections = m_vec.GetSize();
		
		for (nConnectionIndex = 0; nConnectionIndex < nConnections; nConnectionIndex++)
		{
			pT->Lock();
			CComPtr<IUnknown> sp = m_vec.GetAt(nConnectionIndex);
			pT->Unlock();
         CComQIPtr<ldIVehicularLoadsEvents> events(sp);
         if ( events )
            events->OnVehicularLoadsBeforeRemove(Load);
		}
	}
};

template <class T>
class CProxyDLoadCaseEvents : public IConnectionPointImpl<T, &IID_ldILoadCaseEvents, CComDynamicUnkArray>
{
	//Warning this class may be recreated by the wizard.
public:
	VOID Fire_OnLoadCaseChanged(ldILoadCase * me, ldLoadingChangeType type)
	{
		T* pT = static_cast<T*>(this);
		int nConnectionIndex;
		int nConnections = m_vec.GetSize();
		
		for (nConnectionIndex = 0; nConnectionIndex < nConnections; nConnectionIndex++)
		{
			pT->Lock();
			CComPtr<IUnknown> sp = m_vec.GetAt(nConnectionIndex);
			pT->Unlock();
         CComQIPtr<ldILoadCaseEvents> events(sp);
         if (events)
            events->OnLoadCaseChanged(me,type);
		}
	}
	VOID Fire_OnLoadCaseRenamed(BSTR oldName, BSTR newName)
	{
		T* pT = static_cast<T*>(this);
		int nConnectionIndex;
		int nConnections = m_vec.GetSize();
		
		for (nConnectionIndex = 0; nConnectionIndex < nConnections; nConnectionIndex++)
		{
			pT->Lock();
			CComPtr<IUnknown> sp = m_vec.GetAt(nConnectionIndex);
			pT->Unlock();
         CComQIPtr<ldILoadCaseEvents> events(sp);
         if (events)
            events->OnLoadCaseRenamed(oldName,newName);
		}
	}
};
template <class T>
class CProxyDLoadCasesEvents : public IConnectionPointImpl<T, &IID_ldILoadCasesEvents, CComDynamicUnkArray>
{
	//Warning this class may be recreated by the wizard.
public:
	VOID Fire_OnLoadCasesChanged(ldILoadCase * Load, ldLoadingChangeType change)
	{
		T* pT = static_cast<T*>(this);
		int nConnectionIndex;
		int nConnections = m_vec.GetSize();
		
		for (nConnectionIndex = 0; nConnectionIndex < nConnections; nConnectionIndex++)
		{
			pT->Lock();
			CComPtr<IUnknown> sp = m_vec.GetAt(nConnectionIndex);
			pT->Unlock();
         CComQIPtr<ldILoadCasesEvents> events(sp);
         if (events)
            events->OnLoadCasesChanged(Load,change);
		}
	}
	VOID Fire_OnLoadCasesRenamed(BSTR oldName, BSTR newName)
	{
		T* pT = static_cast<T*>(this);
		int nConnectionIndex;
		int nConnections = m_vec.GetSize();
		
		for (nConnectionIndex = 0; nConnectionIndex < nConnections; nConnectionIndex++)
		{
			pT->Lock();
			CComPtr<IUnknown> sp = m_vec.GetAt(nConnectionIndex);
			pT->Unlock();
         CComQIPtr<ldILoadCasesEvents> events(sp);
         if (events)
            events->OnLoadCasesRenamed(oldName,newName);
		}
	}
	VOID Fire_OnLoadCasesAdded(ldILoadCase * Load)
	{
		T* pT = static_cast<T*>(this);
		int nConnectionIndex;
		int nConnections = m_vec.GetSize();
		
		for (nConnectionIndex = 0; nConnectionIndex < nConnections; nConnectionIndex++)
		{
			pT->Lock();
			CComPtr<IUnknown> sp = m_vec.GetAt(nConnectionIndex);
			pT->Unlock();
         CComQIPtr<ldILoadCasesEvents> events(sp);
         if (events)
            events->OnLoadCasesAdded(Load);
		}
	}
	VOID Fire_OnLoadCasesBeforeRemove(ldILoadCase * Load)
	{
		T* pT = static_cast<T*>(this);
		int nConnectionIndex;
		int nConnections = m_vec.GetSize();
		
		for (nConnectionIndex = 0; nConnectionIndex < nConnections; nConnectionIndex++)
		{
			pT->Lock();
			CComPtr<IUnknown> sp = m_vec.GetAt(nConnectionIndex);
			pT->Unlock();
         CComQIPtr<ldILoadCasesEvents> events(sp);
         if (events)
            events->OnLoadCasesBeforeRemove(Load);
		}
	}
};
template <class T>
class CProxyDLoadGroupEvents : public IConnectionPointImpl<T, &IID_ldILoadGroupEvents, CComDynamicUnkArray>
{
	//Warning this class may be recreated by the wizard.
public:
	VOID Fire_OnLoadGroupChanged(ldILoadGroup * me, ldLoadingChangeType type)
	{
		T* pT = static_cast<T*>(this);
		int nConnectionIndex;
		int nConnections = m_vec.GetSize();
		
		for (nConnectionIndex = 0; nConnectionIndex < nConnections; nConnectionIndex++)
		{
			pT->Lock();
			CComPtr<IUnknown> sp = m_vec.GetAt(nConnectionIndex);
			pT->Unlock();
         CComQIPtr<ldILoadGroupEvents> events(sp);
         if ( events )
            events->OnLoadGroupChanged(me,type);
		}
	}
	VOID Fire_OnLoadGroupRenamed(BSTR oldName, BSTR newName)
	{
		T* pT = static_cast<T*>(this);
		int nConnectionIndex;
		int nConnections = m_vec.GetSize();
		
		for (nConnectionIndex = 0; nConnectionIndex < nConnections; nConnectionIndex++)
		{
			pT->Lock();
			CComPtr<IUnknown> sp = m_vec.GetAt(nConnectionIndex);
			pT->Unlock();
         CComQIPtr<ldILoadGroupEvents> events(sp);
         if ( events )
            events->OnLoadGroupRenamed(oldName,newName);
		}
	}
};

template <class T>
class CProxyDLoadGroupsEvents : public IConnectionPointImpl<T, &IID_ldILoadGroupsEvents, CComDynamicUnkArray>
{
	//Warning this class may be recreated by the wizard.
public:
	VOID Fire_OnLoadGroupsChanged(ldILoadGroup * Load, ldLoadingChangeType change)
	{
		T* pT = static_cast<T*>(this);
		int nConnectionIndex;
		int nConnections = m_vec.GetSize();
		
		for (nConnectionIndex = 0; nConnectionIndex < nConnections; nConnectionIndex++)
		{
			pT->Lock();
			CComPtr<IUnknown> sp = m_vec.GetAt(nConnectionIndex);
			pT->Unlock();
         CComQIPtr<ldILoadGroupsEvents> events(sp);
         if ( events )
            events->OnLoadGroupsChanged(Load,change);
		}
	}
	VOID Fire_OnLoadGroupsRenamed(BSTR oldName, BSTR newName)
	{
		T* pT = static_cast<T*>(this);
		int nConnectionIndex;
		int nConnections = m_vec.GetSize();
		
		for (nConnectionIndex = 0; nConnectionIndex < nConnections; nConnectionIndex++)
		{
			pT->Lock();
			CComPtr<IUnknown> sp = m_vec.GetAt(nConnectionIndex);
			pT->Unlock();
         CComQIPtr<ldILoadGroupsEvents> events(sp);
         if ( events )
            events->OnLoadGroupsRenamed(oldName,newName);
		}
	}
	VOID Fire_OnLoadGroupsAdded(ldILoadGroup * Load)
	{
		T* pT = static_cast<T*>(this);
		int nConnectionIndex;
		int nConnections = m_vec.GetSize();
		
		for (nConnectionIndex = 0; nConnectionIndex < nConnections; nConnectionIndex++)
		{
			pT->Lock();
			CComPtr<IUnknown> sp = m_vec.GetAt(nConnectionIndex);
			pT->Unlock();
         CComQIPtr<ldILoadGroupsEvents> events(sp);
         if ( events )
            events->OnLoadGroupsAdded(Load);
		}
	}
	VOID Fire_OnLoadGroupsBeforeRemove(ldILoadGroup * Load)
	{
		T* pT = static_cast<T*>(this);
		int nConnectionIndex;
		int nConnections = m_vec.GetSize();
		
		for (nConnectionIndex = 0; nConnectionIndex < nConnections; nConnectionIndex++)
		{
			pT->Lock();
			CComPtr<IUnknown> sp = m_vec.GetAt(nConnectionIndex);
			pT->Unlock();
         CComQIPtr<ldILoadGroupsEvents> events(sp);
         if ( events )
            events->OnLoadGroupsBeforeRemove(Load);
		}
	}
};

template <class T>
class CProxyDLoadCombinationEvents : public IConnectionPointImpl<T, &IID_ldILoadCombinationEvents, CComDynamicUnkArray>
{
	//Warning this class may be recreated by the wizard.
public:
	VOID Fire_OnLoadCombinationChanged(ldILoadCombination * me, ldLoadingChangeType type)
	{
		T* pT = static_cast<T*>(this);
		int nConnectionIndex;
		int nConnections = m_vec.GetSize();
		
		for (nConnectionIndex = 0; nConnectionIndex < nConnections; nConnectionIndex++)
		{
			pT->Lock();
			CComPtr<IUnknown> sp = m_vec.GetAt(nConnectionIndex);
			pT->Unlock();
         CComQIPtr<ldILoadCombinationEvents> events(sp);
         if ( events )
            events->OnLoadCombinationChanged(me,type);
		}
	}
	VOID Fire_OnLoadCombinationRenamed(BSTR oldName, BSTR newName)
	{
		T* pT = static_cast<T*>(this);
		int nConnectionIndex;
		int nConnections = m_vec.GetSize();
		
		for (nConnectionIndex = 0; nConnectionIndex < nConnections; nConnectionIndex++)
		{
			pT->Lock();
			CComPtr<IUnknown> sp = m_vec.GetAt(nConnectionIndex);
			pT->Unlock();
         CComQIPtr<ldILoadCombinationEvents> events(sp);
         if ( events )
            events->OnLoadCombinationRenamed(oldName,newName);
		}
	}
};

template <class T>
class CProxyDLoadCombinationsEvents : public IConnectionPointImpl<T, &IID_ldILoadCombinationsEvents, CComDynamicUnkArray>
{
	//Warning this class may be recreated by the wizard.
public:
	VOID Fire_OnLoadCombinationsChanged(ldILoadCombination * Load, ldLoadingChangeType change)
	{
		T* pT = static_cast<T*>(this);
		int nConnectionIndex;
		int nConnections = m_vec.GetSize();
		
		for (nConnectionIndex = 0; nConnectionIndex < nConnections; nConnectionIndex++)
		{
			pT->Lock();
			CComPtr<IUnknown> sp = m_vec.GetAt(nConnectionIndex);
			pT->Unlock();
         CComQIPtr<ldILoadCombinationsEvents> events(sp);
         if ( events )
            events->OnLoadCombinationsChanged(Load,change);
		}
	}


	VOID Fire_OnLoadCombinationsRenamed(BSTR oldName, BSTR newName)
	{
		T* pT = static_cast<T*>(this);
		int nConnectionIndex;
		int nConnections = m_vec.GetSize();
		
		for (nConnectionIndex = 0; nConnectionIndex < nConnections; nConnectionIndex++)
		{
			pT->Lock();
			CComPtr<IUnknown> sp = m_vec.GetAt(nConnectionIndex);
			pT->Unlock();
         CComQIPtr<ldILoadCombinationsEvents> events(sp);
         if ( events )
            events->OnLoadCombinationsRenamed(oldName,newName);
		}
	}
	VOID Fire_OnLoadCombinationsAdded(ldILoadCombination * Load)
	{
		T* pT = static_cast<T*>(this);
		int nConnectionIndex;
		int nConnections = m_vec.GetSize();
		
		for (nConnectionIndex = 0; nConnectionIndex < nConnections; nConnectionIndex++)
		{
			pT->Lock();
			CComPtr<IUnknown> sp = m_vec.GetAt(nConnectionIndex);
			pT->Unlock();
         CComQIPtr<ldILoadCombinationsEvents> events(sp);
         if ( events )
            events->OnLoadCombinationsAdded(Load);
		}
	}
	VOID Fire_OnLoadCombinationsBeforeRemove(ldILoadCombination * Load)
	{
		T* pT = static_cast<T*>(this);
		int nConnectionIndex;
		int nConnections = m_vec.GetSize();
		
		for (nConnectionIndex = 0; nConnectionIndex < nConnections; nConnectionIndex++)
		{
			pT->Lock();
			CComPtr<IUnknown> sp = m_vec.GetAt(nConnectionIndex);
			pT->Unlock();
         CComQIPtr<ldILoadCombinationsEvents> events(sp);
         if ( events )
            events->OnLoadCombinationsBeforeRemove(Load);
		}
	}
};



template <class T>
class CProxyIPointLoadEvents : public IConnectionPointImpl<T, &IID_ldIPointLoadEvents, CComDynamicUnkArray>
{
	//Warning this class may be recreated by the wizard.
public:
	HRESULT Fire_OnPointLoadChanged(ldIPointLoad * me)
	{
		HRESULT ret = S_OK;
		T* pT = static_cast<T*>(this);
		int nConnectionIndex;
		int nConnections = m_vec.GetSize();
		
		for (nConnectionIndex = 0; nConnectionIndex < nConnections; nConnectionIndex++)
		{
			pT->Lock();
			CComPtr<IUnknown> sp = m_vec.GetAt(nConnectionIndex);
			pT->Unlock();
			ldIPointLoadEvents* pIPointLoadEvents = reinterpret_cast<ldIPointLoadEvents*>(sp.p);
			if (pIPointLoadEvents != NULL)
				ret = pIPointLoadEvents->OnPointLoadChanged(me);
		}	return ret;
	
	}
};

template <class T>
class CProxyIPointLoadsEvents : public IConnectionPointImpl<T, &IID_ldIPointLoadsEvents, CComDynamicUnkArray>
{
	//Warning this class may be recreated by the wizard.
public:
	HRESULT Fire_OnPointLoadChanged(ldIPointLoadItem * Load)
	{
		HRESULT ret = S_OK;
		T* pT = static_cast<T*>(this);
		int nConnectionIndex;
		int nConnections = m_vec.GetSize();
		
		for (nConnectionIndex = 0; nConnectionIndex < nConnections; nConnectionIndex++)
		{
			pT->Lock();
			CComPtr<IUnknown> sp = m_vec.GetAt(nConnectionIndex);
			pT->Unlock();
			ldIPointLoadsEvents* pIPointLoadsEvents = reinterpret_cast<ldIPointLoadsEvents*>(sp.p);
			if (pIPointLoadsEvents != NULL)
				ret = pIPointLoadsEvents->OnPointLoadChanged(Load);
		}	return ret;
	
	}
	HRESULT Fire_OnPointLoadAdded(ldIPointLoadItem * Load)
	{
		HRESULT ret = S_OK;
		T* pT = static_cast<T*>(this);
		int nConnectionIndex;
		int nConnections = m_vec.GetSize();
		
		for (nConnectionIndex = 0; nConnectionIndex < nConnections; nConnectionIndex++)
		{
			pT->Lock();
			CComPtr<IUnknown> sp = m_vec.GetAt(nConnectionIndex);
			pT->Unlock();
			ldIPointLoadsEvents* pIPointLoadsEvents = reinterpret_cast<ldIPointLoadsEvents*>(sp.p);
			if (pIPointLoadsEvents != NULL)
				ret = pIPointLoadsEvents->OnPointLoadAdded(Load);
		}	return ret;
	
	}
	HRESULT Fire_OnPointLoadRemoved()
	{
		HRESULT ret = S_OK;
		T* pT = static_cast<T*>(this);
		int nConnectionIndex;
		int nConnections = m_vec.GetSize();
		
		for (nConnectionIndex = 0; nConnectionIndex < nConnections; nConnectionIndex++)
		{
			pT->Lock();
			CComPtr<IUnknown> sp = m_vec.GetAt(nConnectionIndex);
			pT->Unlock();
			ldIPointLoadsEvents* pIPointLoadsEvents = reinterpret_cast<ldIPointLoadsEvents*>(sp.p);
			if (pIPointLoadsEvents != NULL)
				ret = pIPointLoadsEvents->OnPointLoadRemoved();
		}	return ret;
	
	}
};
#endif