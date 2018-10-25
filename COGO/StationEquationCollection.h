///////////////////////////////////////////////////////////////////////
// COGO - Coordinate Geometry
// Copyright © 1999-2017  Washington State Department of Transportation
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

// StationEquationCollection.h : Declaration of the CStationEquationCollection
#pragma once
 
#ifndef __StationEquationCOLLECTION_H_
#define __StationEquationCOLLECTION_H_

#include "resource.h"       // main symbols
#include "COGOCP.h"
#include "WBFLComCollections.h"

class CStationEquationCollection;
typedef CComVectorCollection<IStationEquationCollection,IStationEquation,IEnumStationEquations,&IID_IEnumStationEquations,CollectionIndexType> StationEquationVectorImpl;
typedef CPersistentCollection<CStationEquationCollection,StationEquationVectorImpl,CollectionIndexType> PersistentStationEquationCollection;

/////////////////////////////////////////////////////////////////////////////
// CStationEquationCollection
class ATL_NO_VTABLE CStationEquationCollection : 
	public CComObjectRootEx<CComSingleThreadModel>,
//   public CComRefCountTracer<CStationEquationCollection,CComObjectRootEx<CComSingleThreadModel> >,
	public CComCoClass<CStationEquationCollection, &CLSID_StationEquationCollection>,
   public IObjectSafetyImpl<CStationEquationCollection,INTERFACESAFE_FOR_UNTRUSTED_CALLER | INTERFACESAFE_FOR_UNTRUSTED_DATA>,
	public IConnectionPointContainerImpl<CStationEquationCollection>,
	public ISupportErrorInfo,
	public PersistentStationEquationCollection,
   public CProxyDStationEquationCollectionEvents< CStationEquationCollection >
{
public:
	CStationEquationCollection()
	{
      m_bClearing = false;
	}
   bool m_bClearing; // used to keep track if station equations are being removed or cleared

   HRESULT FinalConstruct();
   void FinalRelease();

DECLARE_REGISTRY_RESOURCEID(IDR_STATIONEQUATIONCOLLECTION)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CStationEquationCollection)
	COM_INTERFACE_ENTRY(IStructuredStorage2)
	COM_INTERFACE_ENTRY(IConnectionPointContainer)
	COM_INTERFACE_ENTRY_IMPL(IConnectionPointContainer)

   COM_INTERFACE_ENTRY_IMPL(IConnectionPointContainer)

   COM_INTERFACE_ENTRY(ISupportErrorInfo)
   COM_INTERFACE_ENTRY(IObjectSafety)

   COM_INTERFACE_ENTRY_CHAIN(PersistentStationEquationCollection)
END_COM_MAP()

BEGIN_CONNECTION_POINT_MAP(CStationEquationCollection)
	CONNECTION_POINT_ENTRY(IID_IStationEquationCollectionEvents)
END_CONNECTION_POINT_MAP()

   CComBSTR GetCollectionName() { return CComBSTR("StationEquations"); }
   CComBSTR GetItemName() { return CComBSTR("StationEquation"); }

   HRESULT putref_Alignment(/*[in]*/IAlignment* pAlignment);
   Float64 ComputeNormalizedStation(Float64 back);
   HRESULT BackStationError();
   HRESULT AheadStationError();
   HRESULT StationEquationError(UINT nHelpString,HRESULT hRes);

   virtual HRESULT OnAfterAdd( StoredType* pVal, IndexType idx) override
   { 
      Fire_OnEquationAdded(idx,pVal->second.m_T);
      return S_OK; 
   }
   
   virtual HRESULT OnAfterRemove( IndexType idx) override
   {
      if ( !m_bClearing )
         Fire_OnEquationRemoved(idx);

      return S_OK; 
   }

   virtual HRESULT OnBeforeClear() override
   { 
      m_bClearing = true;
      return S_OK; 
   }
   virtual HRESULT OnAfterClear() override 
   { 
      m_bClearing = false;
      Fire_OnEquationsCleared();
      return S_OK; 
   }


   IAlignment* m_pAlignment; // weak reference

// ISupportsErrorInfo
public:
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid) override;

// IStationEquationCollection
public:
   STDMETHOD(get_Alignment)(/*[out,retval]*/IAlignment** ppAlignment) override;
// STDMETHOD(get__NewEnum)(IUnknown** retval) override;
   //STDMETHOD(get_Item)(CollectionIndexType idx, IStationEquation* *pVal) override;
   //STDMETHOD(get_Count)(CollectionIndexType *pVal) override;
   STDMETHOD(Add)(Float64 back,Float64 ahead,IStationEquation* *pp) override;
   //STDMETHOD(Remove)(CollectionIndexType idx) override;
   STDMETHOD(Clear)() override;
   STDMETHOD(get__EnumStationEquations)(IEnumStationEquations** ppenum) override;
   STDMETHOD(get_StructuredStorage)(IStructuredStorage2* *pVal) override;

   STDMETHOD(Distance)(VARIANT varStation1,VARIANT varStation2,Float64* pDist) override;
   STDMETHOD(Increment)(VARIANT varStation,Float64 value,IStation** station) override;
   STDMETHOD(IncrementBy)(IStation* station,Float64 value) override;
   STDMETHOD(ConvertToNormalizedStation)(VARIANT varStation,Float64* station) override;
   STDMETHOD(ConvertToNormalizedStationEx)(VARIANT varStation,IStation** station) override;
   STDMETHOD(ConvertFromNormalizedStation)(Float64 normalizedStation,IStation** station) override;
   STDMETHOD(ConvertFromNormalizedStationEx)(VARIANT varStation,IStation** station) override;
};

#endif //__StationEquationCOLLECTION_H_
