///////////////////////////////////////////////////////////////////////
// GenericBridge - Generic Bridge Modeling Framework
// Copyright © 1999-2016  Washington State Department of Transportation
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

// Pier.h : Declaration of the CPier

#ifndef __PIER_H_
#define __PIER_H_

#include "resource.h"       // main symbols
#include "GenericBridgeCP.h"
#include <vector>

class CSpan;

/////////////////////////////////////////////////////////////////////////////
// CPier
class ATL_NO_VTABLE CPier : 
	public CComObjectRootEx<CComSingleThreadModel>,
//   public CComRefCountTracer<CPier,CComObjectRootEx<CComSingleThreadModel> >,
	public CComCoClass<CPier, &CLSID_Pier>,
	public ISupportErrorInfo,
	public IConnectionPointContainerImpl<CPier>,
   public IObjectSafetyImpl<CPier,INTERFACESAFE_FOR_UNTRUSTED_CALLER | INTERFACESAFE_FOR_UNTRUSTED_DATA>,
	public IPier,
   public IStructuredStorage2,
   public ILongitudinalPierDescriptionEvents,
   public ITransversePierDescriptionEvents,
   public IStationEvents,
   public CProxyDPierEvents< CPier >
{
public:
   CPier() :
      m_bstrOrientation("Normal")
	{
      m_pNextSpan = 0;
      m_pPrevSpan = 0;
	}

   HRESULT FinalConstruct();
   void FinalRelease();

   void SetBridge(IGenericBridge* pBridge);
   void SetIndex(PierIndexType index) { m_Index = index; }

   void Init(VARIANT varStation,BSTR bstrOrientation)
   {
      // Validate the orientation before initialize the pier with bad data
      ATLASSERT(bstrOrientation ? SUCCEEDED(ValidateOrientation(bstrOrientation)) : TRUE);

      if ( varStation.vt == VT_R8 )
      {
         m_Station->put_Value(varStation.dblVal);
      }
      else if (varStation.vt == VT_UNKNOWN || varStation.vt == VT_DISPATCH )
      {
         varStation.punkVal->QueryInterface(&m_Station);
      }
      else
      {
         ATLASSERT(FALSE); // Error initialize pier... Bad station type in variant
      }

      if ( bstrOrientation )
         m_bstrOrientation = bstrOrientation;
   }

   static HRESULT ValidateOrientation(BSTR bstrOrientation);

   void SetSpans(CSpan* prevSpan,CSpan* nextSpan)
   {
      m_pPrevSpan = prevSpan;
      m_pNextSpan = nextSpan;
   }

   CSpan* GetPrevSpan()
   {
      return m_pPrevSpan;
   }

   CSpan* GetNextSpan()
   {
      return m_pNextSpan;
   }

   // Sets the value of the pier station without firing events or creating transactions
   // Moves only this pier
   void SetStationValue(Float64 newVal);

   // Sets the value of the pier station, and moves all piers ahead on station, without
   // firing events or creating transactions
   void SetStationValueEx(Float64 newVal);

   // Currently private method, but can easily be moved to the COM
   // interface if need be.
   STDMETHOD(Clone)(IPier* *clone);
   void SetLongitudinalPierDescription(ILongitudinalPierDescription* cloneLPD); // replaces the default LPD with a clone
   void SetTransversePierDescription(ITransversePierDescription* cloneTPD); // replaces the default TPD with a clone

   void RenameStageReferences(BSTR bstrOldName,BSTR bstrNewName);
   void AddDataForStage(BSTR bstrName);
   void RemoveDataForStage(BSTR bstrName);

DECLARE_REGISTRY_RESOURCEID(IDR_PIER)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CPier)
	COM_INTERFACE_ENTRY(IPier)
	COM_INTERFACE_ENTRY(IStructuredStorage2)

	COM_INTERFACE_ENTRY(ISupportErrorInfo)
	COM_INTERFACE_ENTRY(IConnectionPointContainer)

   COM_INTERFACE_ENTRY_IMPL(IConnectionPointContainer)

   COM_INTERFACE_ENTRY(ILongitudinalPierDescriptionEvents)

   COM_INTERFACE_ENTRY(ITransversePierDescriptionEvents)

   COM_INTERFACE_ENTRY(IStationEvents)

   COM_INTERFACE_ENTRY(IObjectSafety)
END_COM_MAP()

BEGIN_CONNECTION_POINT_MAP(CPier)
CONNECTION_POINT_ENTRY(IID_IPierEvents)
END_CONNECTION_POINT_MAP()

private:
   IGenericBridge* m_pBridge; // weak reference to parent
   CSpan* m_pPrevSpan;
   CSpan* m_pNextSpan;
   CComBSTR m_bstrOrientation;
   PierIndexType m_Index;

   CComPtr<IStation> m_Station;
   DWORD m_dwStationCookie;

   CComPtr<ILongitudinalPierDescription> m_LongPierDesc;
   DWORD m_dwLPDCookie;

   CComPtr<ITransversePierDescription> m_TransPierDesc;
   DWORD m_dwTPDCookie;

   CComPtr<IConnection> m_Connection[2]; // key is PositionType qcbBefore = back side of pier;


   HRESULT AdviseLongPierDesc();
   HRESULT UnadviseLongPierDesc();
   HRESULT AdviseTransPierDesc();
   HRESULT UnadviseTransPierDesc();
   HRESULT AdviseStation();
   HRESULT UnadviseStation();

// ISupportsErrorInfo
public:
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

// IPier
public:
   STDMETHOD(get_Station)(/*[out,retval]*/IStation* *station);
   STDMETHOD(putref_Station)(/*[in]*/IStation* station);
   STDMETHOD(get_Orientation)(/*[out,retval]*/ BSTR* orientation);
   STDMETHOD(put_Orientation)(/*[in]*/ BSTR orientation);
	STDMETHOD(get_LongitudinalPierDescription)(/*[out, retval]*/ ILongitudinalPierDescription* *pVal);
   STDMETHOD(get_Direction)(/*[out,retval]*/ IDirection* *direction);
   STDMETHOD(get_SkewAngle)(/*[out,retval]*/ IAngle* *skewAngle);
   STDMETHOD(get_GirderSpacing)(/*[in]*/PositionType posType,/*[out,retval]*/IGirderSpacing** ppGirderSpacing);
   STDMETHOD(get_Connection)(/*[in]*/PositionType posType,/*[out,retval]*/IConnection** ppConnection);
	STDMETHOD(CreateTransversePierDescription)();
	STDMETHOD(get_TransversePierDescription)(/*[out, retval]*/ ITransversePierDescription* *pVal);
	STDMETHOD(RemoveTransversePierDescription)();
   STDMETHOD(get_PrevSpan)(/*[out,retval]*/ISpan** ppSpan);
	STDMETHOD(get_NextSpan)(/*[out,retval]*/ISpan** ppSpan);
   STDMETHOD(get_Index)(/*[out,retval]*/PierIndexType* pIndex);

// IStructuredStorage2
public:
	STDMETHOD(Load)(/*[in]*/ IStructuredLoad2* load);
	STDMETHOD(Save)(/*[in]*/ IStructuredSave2* save);

// ILongitudinalPierDescriptionEvents
public:
	STDMETHOD(OnChanged)()
	{
      Fire_OnPierChanged(this);
		return S_OK;
	}

// IStationEvents
public:
   STDMETHOD(OnStationChanged)(Float64 newVal);
};

#endif //__PIER_H_
