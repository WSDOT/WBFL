///////////////////////////////////////////////////////////////////////
// GenericBridge - Generic Bridge Modeling Framework
// Copyright © 1999-2015  Washington State Department of Transportation
//                        Bridge and Structures Office
//
// This library is a part of the Washington Bridge Foundation Libraries
// and was developed as part of the Alternate Route Project
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the Alternate Route Library Open Source License as 
// published by the Washington State Department of Transportation,
// Bridge and Structures Office.
//
// This program is distributed in the hope that it will be useful,
// but is distributed AS IS, WITHOUT ANY WARRANTY; without even the
// implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR 
// PURPOSE.  See the Alternate Route Library Open Source License for more details.
//
// You should have received a copy of the Alternate Route Library Open Source License
// along with this program; if not, write to the Washington State
// Department of Transportation, Bridge and Structures Office,
// P.O. Box 47340, Olympia, WA 98503, USA or e-mail
// Bridge_Support@wsdot.wa.gov
///////////////////////////////////////////////////////////////////////

#ifndef _GENERICBRIDGECP_H_
#define _GENERICBRIDGECP_H_


template <class T>
class CProxyDPierEvents : public IConnectionPointImpl<T, &IID_IPierEvents, CComDynamicUnkArray>
{
	//Warning this class may be recreated by the wizard.
public:
	VOID Fire_OnPierChanged(IPier * pier)
	{
		T* pT = static_cast<T*>(this);
		int nConnectionIndex;
		int nConnections = m_vec.GetSize();
		
		for (nConnectionIndex = 0; nConnectionIndex < nConnections; nConnectionIndex++)
		{
			pT->Lock();
			CComPtr<IUnknown> sp = m_vec.GetAt(nConnectionIndex);
			pT->Unlock();
         CComQIPtr<IPierEvents> events(sp);
         if ( events)
            events->OnPierChanged(pier);
		}
	
	}
/*
	VOID Fire_OnGeometryChanged()
	{
		T* pT = static_cast<T*>(this);
		int nConnectionIndex;
		int nConnections = m_vec.GetSize();
		
		for (nConnectionIndex = 0; nConnectionIndex < nConnections; nConnectionIndex++)
		{
			pT->Lock();
			CComPtr<IUnknown> sp = m_vec.GetAt(nConnectionIndex);
			pT->Unlock();
			IDispatch* pDispatch = reinterpret_cast<IDispatch*>(sp.p);
			if (pDispatch != NULL)
			{
				DISPPARAMS disp = { NULL, NULL, 0, 0 };
				pDispatch->Invoke(0x2af8, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_METHOD, &disp, NULL, NULL, NULL);
			}
		}
	
	}
	VOID Fire_OnStructureChanged()
	{
		T* pT = static_cast<T*>(this);
		int nConnectionIndex;
		int nConnections = m_vec.GetSize();
		
		for (nConnectionIndex = 0; nConnectionIndex < nConnections; nConnectionIndex++)
		{
			pT->Lock();
			CComPtr<IUnknown> sp = m_vec.GetAt(nConnectionIndex);
			pT->Unlock();
			IDispatch* pDispatch = reinterpret_cast<IDispatch*>(sp.p);
			if (pDispatch != NULL)
			{
				DISPPARAMS disp = { NULL, NULL, 0, 0 };
				pDispatch->Invoke(0x2af9, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_METHOD, &disp, NULL, NULL, NULL);
			}
		}
	
	}
	VOID Fire_OnLoadsChanged()
	{
		T* pT = static_cast<T*>(this);
		int nConnectionIndex;
		int nConnections = m_vec.GetSize();
		
		for (nConnectionIndex = 0; nConnectionIndex < nConnections; nConnectionIndex++)
		{
			pT->Lock();
			CComPtr<IUnknown> sp = m_vec.GetAt(nConnectionIndex);
			pT->Unlock();
			IDispatch* pDispatch = reinterpret_cast<IDispatch*>(sp.p);
			if (pDispatch != NULL)
			{
				DISPPARAMS disp = { NULL, NULL, 0, 0 };
				pDispatch->Invoke(0x2afa, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_METHOD, &disp, NULL, NULL, NULL);
			}
		}
	
	}
*/
};


template <class T>
class CProxyDLongitudinalPierDescriptionEvents : public IConnectionPointImpl<T, &IID_ILongitudinalPierDescriptionEvents, CComDynamicUnkArray>
{
	//Warning this class may be recreated by the wizard.
public:
	VOID Fire_OnChanged()
	{
		T* pT = static_cast<T*>(this);
		int nConnectionIndex;
		int nConnections = m_vec.GetSize();
		
		for (nConnectionIndex = 0; nConnectionIndex < nConnections; nConnectionIndex++)
		{
			pT->Lock();
			CComPtr<IUnknown> sp = m_vec.GetAt(nConnectionIndex);
			pT->Unlock();
         CComQIPtr<ILongitudinalPierDescriptionEvents> events(sp);
         if ( events )
            events->OnChanged();
		}
	
	}
};


template <class T>
class CProxyDSpanEvents : public IConnectionPointImpl<T, &IID_ISpanEvents, CComDynamicUnkArray>
{
	//Warning this class may be recreated by the wizard.
public:
	VOID Fire_OnSpanChanged(ISpan * span)
	{
		T* pT = static_cast<T*>(this);
		int nConnectionIndex;
		int nConnections = m_vec.GetSize();
		
		for (nConnectionIndex = 0; nConnectionIndex < nConnections; nConnectionIndex++)
		{
			pT->Lock();
			CComPtr<IUnknown> sp = m_vec.GetAt(nConnectionIndex);
			pT->Unlock();
         CComQIPtr<ISpanEvents> events(sp);
         if ( events )
            events->OnSpanChanged(span);
		}
	}
};


template <class T>
class CProxyDSegmentEvents : public IConnectionPointImpl<T, &IID_ISegmentEvents, CComDynamicUnkArray>
{
	//Warning this class may be recreated by the wizard.
public:
	VOID Fire_OnSegmentChanged(ISegment * Segment)
	{
		T* pT = static_cast<T*>(this);
		int nConnectionIndex;
		int nConnections = m_vec.GetSize();
		
		for (nConnectionIndex = 0; nConnectionIndex < nConnections; nConnectionIndex++)
		{
			pT->Lock();
			CComPtr<IUnknown> sp = m_vec.GetAt(nConnectionIndex);
			pT->Unlock();
         CComQIPtr<ISegmentEvents> events(sp);
         if ( events )
            events->OnSegmentChanged(Segment);
		}
	}
};

template <class T>
class CProxyDSuperstructureMemberEvents : public IConnectionPointImpl<T, &IID_ISuperstructureMemberEvents, CComDynamicUnkArray>
{
	//Warning this class may be recreated by the wizard.
public:
	VOID Fire_OnSuperstructureMemberChanged(ISuperstructureMember * ssm)
	{
		T* pT = static_cast<T*>(this);
		int nConnectionIndex;
		int nConnections = m_vec.GetSize();
		
		for (nConnectionIndex = 0; nConnectionIndex < nConnections; nConnectionIndex++)
		{
			pT->Lock();
			CComPtr<IUnknown> sp = m_vec.GetAt(nConnectionIndex);
			pT->Unlock();
         CComQIPtr<ISuperstructureMemberEvents> events(sp);
         if ( events )
            events->OnSuperstructureMemberChanged(ssm);
		}
	}
};

template <class T>
class CProxyDSegmentItemEvents : public IConnectionPointImpl<T, &IID_ISegmentItemEvents, CComDynamicUnkArray>
{
	//Warning this class may be recreated by the wizard.
public:
	VOID Fire_OnSegmentItemChanged(ISegmentItem * segmentItem)
	{
		T* pT = static_cast<T*>(this);
		int nConnectionIndex;
		int nConnections = m_vec.GetSize();
		
		for (nConnectionIndex = 0; nConnectionIndex < nConnections; nConnectionIndex++)
		{
			pT->Lock();
			CComPtr<IUnknown> sp = m_vec.GetAt(nConnectionIndex);
			pT->Unlock();
         CComQIPtr<ISegmentItemEvents> events(sp);
         if ( events )
            events->OnSegmentItemChanged(segmentItem);
		}
	}
};



template <class T>
class CProxyDGenericBridgeEvents : public IConnectionPointImpl<T, &IID_IGenericBridgeEvents, CComDynamicUnkArray>
{
	//Warning this class may be recreated by the wizard.
public:
	VOID Fire_OnBridgeChanged(IGenericBridge * bridge)
	{
		T* pT = static_cast<T*>(this);
		int nConnectionIndex;
		int nConnections = m_vec.GetSize();
		
		for (nConnectionIndex = 0; nConnectionIndex < nConnections; nConnectionIndex++)
		{
			pT->Lock();
			CComPtr<IUnknown> sp = m_vec.GetAt(nConnectionIndex);
			pT->Unlock();
         CComQIPtr<IGenericBridgeEvents> events(sp);
         if (events)
            events->OnBridgeChanged(bridge);
		}
	}
};


template <class T>
class CProxyDPierCollectionEvents : public IConnectionPointImpl<T, &IID_IPierCollectionEvents, CComDynamicUnkArray>
{
	//Warning this class may be recreated by the wizard.
public:
	VOID Fire_OnPierChanged(IPier * Pier)
	{
		T* pT = static_cast<T*>(this);
		int nConnectionIndex;
		int nConnections = m_vec.GetSize();
		
		for (nConnectionIndex = 0; nConnectionIndex < nConnections; nConnectionIndex++)
		{
			pT->Lock();
			CComPtr<IUnknown> sp = m_vec.GetAt(nConnectionIndex);
			pT->Unlock();
         CComQIPtr<IPierCollectionEvents> events(sp);
         if ( events )
            events->OnPierChanged(Pier);
		}
	}
	VOID Fire_OnPierAdded(IPier * Pier)
	{
		T* pT = static_cast<T*>(this);
		int nConnectionIndex;
		int nConnections = m_vec.GetSize();
		
		for (nConnectionIndex = 0; nConnectionIndex < nConnections; nConnectionIndex++)
		{
			pT->Lock();
			CComPtr<IUnknown> sp = m_vec.GetAt(nConnectionIndex);
			pT->Unlock();
         CComQIPtr<IPierCollectionEvents> events(sp);
         if ( events )
            events->OnPierAdded(Pier);
		}
	}
	VOID Fire_OnPierRemoved(PierIndexType idx)
	{
		T* pT = static_cast<T*>(this);
		int nConnectionIndex;
		int nConnections = m_vec.GetSize();
		
		for (nConnectionIndex = 0; nConnectionIndex < nConnections; nConnectionIndex++)
		{
			pT->Lock();
			CComPtr<IUnknown> sp = m_vec.GetAt(nConnectionIndex);
			pT->Unlock();
         CComQIPtr<IPierCollectionEvents> events(sp);
         if ( events )
            events->OnPierRemoved(idx);
		}
	}
};








template <class T>
class CProxyDSuperstructureMemberCollectionEvents : public IConnectionPointImpl<T, &IID_ISuperstructureMemberCollectionEvents, CComDynamicUnkArray>
{
	//Warning this class may be recreated by the wizard.
public:
	VOID Fire_OnSuperstructureMemberChanged(ISuperstructureMember * mbr)
	{
		T* pT = static_cast<T*>(this);
		int nConnectionIndex;
		int nConnections = m_vec.GetSize();
		
		for (nConnectionIndex = 0; nConnectionIndex < nConnections; nConnectionIndex++)
		{
			pT->Lock();
			CComPtr<IUnknown> sp = m_vec.GetAt(nConnectionIndex);
			pT->Unlock();
         CComQIPtr<ISuperstructureMemberCollectionEvents> events(sp);
         if ( events )
            events->OnSuperstructureMemberChanged(mbr);
		}
	}
	VOID Fire_OnSuperstructureMemberAdded(LONG idx)
	{
		T* pT = static_cast<T*>(this);
		int nConnectionIndex;
		int nConnections = m_vec.GetSize();
		
		for (nConnectionIndex = 0; nConnectionIndex < nConnections; nConnectionIndex++)
		{
			pT->Lock();
			CComPtr<IUnknown> sp = m_vec.GetAt(nConnectionIndex);
			pT->Unlock();
         CComQIPtr<ISuperstructureMemberCollectionEvents> events(sp);
         if ( events )
            events->OnSuperstructureMemberAdded(idx);
		}
	}
	VOID Fire_OnSuperstructureMemberRemoved(LONG idx)
	{
		T* pT = static_cast<T*>(this);
		int nConnectionIndex;
		int nConnections = m_vec.GetSize();
		
		for (nConnectionIndex = 0; nConnectionIndex < nConnections; nConnectionIndex++)
		{
			pT->Lock();
			CComPtr<IUnknown> sp = m_vec.GetAt(nConnectionIndex);
			pT->Unlock();
         CComQIPtr<ISuperstructureMemberCollectionEvents> events(sp);
         if ( events )
            events->OnSuperstructureMemberRemoved(idx);
		}
	}
	VOID Fire_OnSuperstructureMemberMoved(LONG from, LONG to)
	{
		T* pT = static_cast<T*>(this);
		int nConnectionIndex;
		int nConnections = m_vec.GetSize();
		
		for (nConnectionIndex = 0; nConnectionIndex < nConnections; nConnectionIndex++)
		{
			pT->Lock();
			CComPtr<IUnknown> sp = m_vec.GetAt(nConnectionIndex);
			pT->Unlock();
         CComQIPtr<ISuperstructureMemberCollectionEvents> events(sp);
         if ( events )
            events->OnSuperstructureMemberMoved(from,to);
		}
	}
	VOID Fire_OnSuperstructureMemberCollectionChanged(ISuperstructureMemberCollection * members)
	{
		T* pT = static_cast<T*>(this);
		int nConnectionIndex;
		int nConnections = m_vec.GetSize();
		
		for (nConnectionIndex = 0; nConnectionIndex < nConnections; nConnectionIndex++)
		{
			pT->Lock();
			CComPtr<IUnknown> sp = m_vec.GetAt(nConnectionIndex);
			pT->Unlock();
         CComQIPtr<ISuperstructureMemberCollectionEvents> events(sp);
         if ( events )
            events->OnSuperstructureMemberCollectionChanged(members);
		}
	}
};


template <class T>
class CProxyDTemporaryPierItemCollectionEvents : public IConnectionPointImpl<T, &IID_ITemporaryPierItemCollectionEvents, CComDynamicUnkArray>
{
	//Warning this class may be recreated by the wizard.
public:
	VOID Fire_OnTemporaryPierItemChanged(ITemporaryPierItem * tpi)
	{
		T* pT = static_cast<T*>(this);
		int nConnectionIndex;
		int nConnections = m_vec.GetSize();
		
		for (nConnectionIndex = 0; nConnectionIndex < nConnections; nConnectionIndex++)
		{
			pT->Lock();
			CComPtr<IUnknown> sp = m_vec.GetAt(nConnectionIndex);
			pT->Unlock();
         CComQIPtr<ITemporaryPierItemCollectionEvents> events(sp);
         if ( events )
            events->OnTemporaryPierItemChanged(tpi);
		}
	}
	VOID Fire_OnTemporaryPierItemAdded(CollectionIndexType idx)
	{
		T* pT = static_cast<T*>(this);
		int nConnectionIndex;
		int nConnections = m_vec.GetSize();
		
		for (nConnectionIndex = 0; nConnectionIndex < nConnections; nConnectionIndex++)
		{
			pT->Lock();
			CComPtr<IUnknown> sp = m_vec.GetAt(nConnectionIndex);
			pT->Unlock();
         CComQIPtr<ITemporaryPierItemCollectionEvents> events(sp);
         if ( events )
            events->OnTemporaryPierItemAdded(idx);
		}
	}
	VOID Fire_OnTemporaryPierItemRemoved(IDType ID)
	{
		T* pT = static_cast<T*>(this);
		int nConnectionIndex;
		int nConnections = m_vec.GetSize();
		
		for (nConnectionIndex = 0; nConnectionIndex < nConnections; nConnectionIndex++)
		{
			pT->Lock();
			CComPtr<IUnknown> sp = m_vec.GetAt(nConnectionIndex);
			pT->Unlock();
         CComQIPtr<ITemporaryPierItemCollectionEvents> events(sp);
         if ( events )
            events->OnTemporaryPierItemRemoved(ID);
		}
	}
};

template <class T>
class CProxyDTemporaryPierItemEvents : public IConnectionPointImpl<T, &IID_ITemporaryPierItemEvents, CComDynamicUnkArray>
{
	//Warning this class may be recreated by the wizard.
public:
	VOID Fire_OnTemporaryPierChanged(IDType ID)
	{
		T* pT = static_cast<T*>(this);
		int nConnectionIndex;
		int nConnections = m_vec.GetSize();
		
		for (nConnectionIndex = 0; nConnectionIndex < nConnections; nConnectionIndex++)
		{
			pT->Lock();
			CComPtr<IUnknown> sp = m_vec.GetAt(nConnectionIndex);
			pT->Unlock();
         CComQIPtr<ITemporaryPierItemEvents> events(sp);
         if ( events )
            events->OnTemporaryPierChanged(ID);
		}
	}
};

template <class T>
class CProxyDSpanCollectionEvents : public IConnectionPointImpl<T, &IID_ISpanCollectionEvents, CComDynamicUnkArray>
{
	//Warning this class may be recreated by the wizard.
public:
	VOID Fire_OnSpanChanged(ISpan * span)
	{
		T* pT = static_cast<T*>(this);
		int nConnectionIndex;
		int nConnections = m_vec.GetSize();
		
		for (nConnectionIndex = 0; nConnectionIndex < nConnections; nConnectionIndex++)
		{
			pT->Lock();
			CComPtr<IUnknown> sp = m_vec.GetAt(nConnectionIndex);
			pT->Unlock();
         CComQIPtr<ISpanCollectionEvents> events(sp);
         if ( events )
            events->OnSpanChanged(span);
		}
	}
};

template <class T>
class CProxyDStageCollectionEvents : public IConnectionPointImpl<T, &IID_IStageCollectionEvents, CComDynamicUnkArray>
{
	//Warning this class may be recreated by the wizard.
public:
	VOID Fire_OnStageRenamed(BSTR bstrOldName, IStage * Stage)
	{
		T* pT = static_cast<T*>(this);
		int nConnectionIndex;
		int nConnections = m_vec.GetSize();
		
		for (nConnectionIndex = 0; nConnectionIndex < nConnections; nConnectionIndex++)
		{
			pT->Lock();
			CComPtr<IUnknown> sp = m_vec.GetAt(nConnectionIndex);
			pT->Unlock();
         CComQIPtr<IStageCollectionEvents> events(sp);
         if ( events )
            events->OnStageRenamed(bstrOldName,Stage);
		}
	}
	VOID Fire_OnStageDescriptionChanged(IStage * Stage)
	{
		T* pT = static_cast<T*>(this);
		int nConnectionIndex;
		int nConnections = m_vec.GetSize();
		
		for (nConnectionIndex = 0; nConnectionIndex < nConnections; nConnectionIndex++)
		{
			pT->Lock();
			CComPtr<IUnknown> sp = m_vec.GetAt(nConnectionIndex);
			pT->Unlock();
         CComQIPtr<IStageCollectionEvents> events(sp);
         if ( events )
            events->OnStageDescriptionChanged(Stage);
		}
	}
	VOID Fire_OnStageAdded(StageIndexType idx)
	{
		T* pT = static_cast<T*>(this);
		int nConnectionIndex;
		int nConnections = m_vec.GetSize();
		
		for (nConnectionIndex = 0; nConnectionIndex < nConnections; nConnectionIndex++)
		{
			pT->Lock();
			CComPtr<IUnknown> sp = m_vec.GetAt(nConnectionIndex);
			pT->Unlock();
         CComQIPtr<IStageCollectionEvents> events(sp);
         if ( events )
            events->OnStageAdded(idx);
		}
	}
	VOID Fire_OnStageRemoved(StageIndexType idx, BSTR Name)
	{
		T* pT = static_cast<T*>(this);
		int nConnectionIndex;
		int nConnections = m_vec.GetSize();
		
		for (nConnectionIndex = 0; nConnectionIndex < nConnections; nConnectionIndex++)
		{
			pT->Lock();
			CComPtr<IUnknown> sp = m_vec.GetAt(nConnectionIndex);
			pT->Unlock();
         CComQIPtr<IStageCollectionEvents> events(sp);
         if ( events )
            events->OnStageRemoved(idx,Name);
		}
	}
	VOID Fire_OnStageMoved(BSTR Name, StageIndexType from, StageIndexType to)
	{
		T* pT = static_cast<T*>(this);
		int nConnectionIndex;
		int nConnections = m_vec.GetSize();
		
		for (nConnectionIndex = 0; nConnectionIndex < nConnections; nConnectionIndex++)
		{
			pT->Lock();
			CComPtr<IUnknown> sp = m_vec.GetAt(nConnectionIndex);
			pT->Unlock();
         CComQIPtr<IStageCollectionEvents> events(sp);
         if ( events )
            events->OnStageMoved(Name,from,to);
		}
	}
};

template <class T>
class CProxyDStageEvents : public IConnectionPointImpl<T, &IID_IStageEvents, CComDynamicUnkArray>
{
	//Warning this class may be recreated by the wizard.
public:
	VOID Fire_OnNameChanged(BSTR bstrOldName, IStage * Stage)
	{
		T* pT = static_cast<T*>(this);
		int nConnectionIndex;
		int nConnections = m_vec.GetSize();
		
		for (nConnectionIndex = 0; nConnectionIndex < nConnections; nConnectionIndex++)
		{
			pT->Lock();
			CComPtr<IUnknown> sp = m_vec.GetAt(nConnectionIndex);
			pT->Unlock();
         CComQIPtr<IStageEvents> events(sp);
         if ( events )
            events->OnNameChanged(bstrOldName,Stage);
		}
	}
	VOID Fire_OnDescriptionChanged(IStage * Stage)
	{
		T* pT = static_cast<T*>(this);
		int nConnectionIndex;
		int nConnections = m_vec.GetSize();
		
		for (nConnectionIndex = 0; nConnectionIndex < nConnections; nConnectionIndex++)
		{
			pT->Lock();
			CComPtr<IUnknown> sp = m_vec.GetAt(nConnectionIndex);
			pT->Unlock();
         CComQIPtr<IStageEvents> events(sp);
         if ( events )
            events->OnDescriptionChanged(Stage);
		}
	}
};

template <class T>
class CProxyDColumnEvents : public IConnectionPointImpl<T, &IID_IColumnEvents, CComDynamicUnkArray>
{
	//Warning this class may be recreated by the wizard.
public:
	VOID Fire_OnColumnChanged(IColumn * column)
	{
		T* pT = static_cast<T*>(this);
		int nConnectionIndex;
		int nConnections = m_vec.GetSize();
		
		for (nConnectionIndex = 0; nConnectionIndex < nConnections; nConnectionIndex++)
		{
			pT->Lock();
			CComPtr<IUnknown> sp = m_vec.GetAt(nConnectionIndex);
			pT->Unlock();
         CComQIPtr<IColumnEvents> events(sp);
         if ( events )
            events->OnColumnChanged(column);
		}
	}
};

template <class T>
class CProxyDColumnSpacingEvents : public IConnectionPointImpl<T, &IID_IColumnSpacingEvents, CComDynamicUnkArray>
{
	//Warning this class may be recreated by the wizard.
public:
	VOID Fire_OnColumnCountChanged(ColumnIndexType newVal)
	{
		T* pT = static_cast<T*>(this);
		int nConnectionIndex;
		int nConnections = m_vec.GetSize();
		
		for (nConnectionIndex = 0; nConnectionIndex < nConnections; nConnectionIndex++)
		{
			pT->Lock();
			CComPtr<IUnknown> sp = m_vec.GetAt(nConnectionIndex);
			pT->Unlock();
         CComQIPtr<IColumnSpacingEvents> events(sp);
         if ( events )
            events->OnColumnCountChanged(newVal);
		}
	}
	VOID Fire_OnColumnSpacingChanged()
	{
		T* pT = static_cast<T*>(this);
		int nConnectionIndex;
		int nConnections = m_vec.GetSize();
		
		for (nConnectionIndex = 0; nConnectionIndex < nConnections; nConnectionIndex++)
		{
			pT->Lock();
			CComPtr<IUnknown> sp = m_vec.GetAt(nConnectionIndex);
			pT->Unlock();
         CComQIPtr<IColumnSpacingEvents> events(sp);
         if ( events )
            events->OnColumnSpacingChanged();
		}
	}
};

template <class T>
class CProxyDCrossBeamEvents : public IConnectionPointImpl<T, &IID_ICrossBeamEvents, CComDynamicUnkArray>
{
	//Warning this class may be recreated by the wizard.
public:
	VOID Fire_OnCrossBeamChanged(ICrossBeam * crossBeam)
	{
		T* pT = static_cast<T*>(this);
		int nConnectionIndex;
		int nConnections = m_vec.GetSize();
		
		for (nConnectionIndex = 0; nConnectionIndex < nConnections; nConnectionIndex++)
		{
			pT->Lock();
			CComPtr<IUnknown> sp = m_vec.GetAt(nConnectionIndex);
			pT->Unlock();
         CComQIPtr<ICrossBeamEvents> events(sp);
         if ( events )
            events->OnCrossBeamChanged(crossBeam);
		}
	}
};


template <class T>
class CProxyDTransversePierDescriptionEvents : public IConnectionPointImpl<T, &IID_ITransversePierDescriptionEvents, CComDynamicUnkArray>
{
	//Warning this class may be recreated by the wizard.
public:
	VOID Fire_OnChanged()
	{
		T* pT = static_cast<T*>(this);
		int nConnectionIndex;
		int nConnections = m_vec.GetSize();
		
		for (nConnectionIndex = 0; nConnectionIndex < nConnections; nConnectionIndex++)
		{
			pT->Lock();
			CComPtr<IUnknown> sp = m_vec.GetAt(nConnectionIndex);
			pT->Unlock();
         CComQIPtr<ITransversePierDescriptionEvents> events(sp);
         if ( events )
            events->OnChanged();
		}
	}
};


template <class T>
class CProxyIGirderSpacingEvents : public IConnectionPointImpl<T, &IID_IGirderSpacingEvents, CComDynamicUnkArray>
{
	//Warning this class may be recreated by the wizard.
public:
	HRESULT Fire_OnGirderSpacingChanged()
	{
		HRESULT ret;
		T* pT = static_cast<T*>(this);
		int nConnectionIndex;
		int nConnections = m_vec.GetSize();
		
		for (nConnectionIndex = 0; nConnectionIndex < nConnections; nConnectionIndex++)
		{
			pT->Lock();
			CComPtr<IUnknown> sp = m_vec.GetAt(nConnectionIndex);
			pT->Unlock();
			IGirderSpacingEvents* pIGirderSpacingEvents = reinterpret_cast<IGirderSpacingEvents*>(sp.p);
			if (pIGirderSpacingEvents != NULL)
				ret = pIGirderSpacingEvents->OnGirderSpacingChanged();
		}	return ret;
	
	}
};

template <class T>
class CProxyDMaterialEvents : public IConnectionPointImpl<T, &IID_IMaterialEvents, CComDynamicUnkArray>
{
	//Warning this class may be recreated by the wizard.
public:
	VOID Fire_OnMaterialChanged(IMaterial * material)
	{
		T* pT = static_cast<T*>(this);
		int nConnectionIndex;
		int nConnections = m_vec.GetSize();
		
		for (nConnectionIndex = 0; nConnectionIndex < nConnections; nConnectionIndex++)
		{
			pT->Lock();
			CComPtr<IUnknown> sp = m_vec.GetAt(nConnectionIndex);
			pT->Unlock();
         CComQIPtr<IMaterialEvents> events(sp);
         if ( events )
            events->OnMaterialChanged(material);
		}
	}
};

template <class T>
class CProxyDBridgeDeckEvents : public IConnectionPointImpl<T, &IID_IBridgeDeckEvents, CComDynamicUnkArray>
{
	//Warning this class may be recreated by the wizard.
public:
	VOID Fire_OnBridgeDeckChanged(IBridgeDeck* deck)
	{
		T* pT = static_cast<T*>(this);
		int nConnectionIndex;
		int nConnections = m_vec.GetSize();
		
		for (nConnectionIndex = 0; nConnectionIndex < nConnections; nConnectionIndex++)
		{
			pT->Lock();
			CComPtr<IUnknown> sp = m_vec.GetAt(nConnectionIndex);
			pT->Unlock();
         CComQIPtr<IBridgeDeckEvents> events(sp);
         if ( events )
            events->OnBridgeDeckChanged(deck);
		}
	}
};

template <class T>
class CProxyDOverhangPathStrategyEvents : public IConnectionPointImpl<T, &IID_IOverhangPathStrategyEvents, CComDynamicUnkArray>
{
	//Warning this class may be recreated by the wizard.
public:
	VOID Fire_OnStrategyChanged()
	{
		T* pT = static_cast<T*>(this);
		int nConnectionIndex;
		int nConnections = m_vec.GetSize();
		
		for (nConnectionIndex = 0; nConnectionIndex < nConnections; nConnectionIndex++)
		{
			pT->Lock();
			CComPtr<IUnknown> sp = m_vec.GetAt(nConnectionIndex);
			pT->Unlock();
         CComQIPtr<IOverhangPathStrategyEvents> events(sp);
         if ( events )
            events->OnStrategyChanged();
		}
	}
};
#endif