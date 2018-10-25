///////////////////////////////////////////////////////////////////////
// COGO - Coordinate Geometry Library
// Copyright © 1999-2010  Washington State Department of Transportation
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

// CrossSectionCollection.h : Declaration of the CCrossSectionCollection

#ifndef __CROSSSECTIONCOLLECTION_H_
#define __CROSSSECTIONCOLLECTION_H_
#pragma once

#include "resource.h"       // main symbols
#include "Collections.h"
#include <vector>
#include "COGOCP.h"

typedef std::pair<DWORD,CComVariant> CSType;
typedef std::vector<CSType> CrossSections;
typedef CComEnumOnSTL<IEnumVARIANT,&IID_IEnumVARIANT, VARIANT, CopyFromPair2<CSType,VARIANT>, CrossSections > CrossSectionEnum;
typedef ICollectionOnSTLImpl<ICrossSectionCollection, CrossSections, VARIANT, CopyFromPair2<CSType,VARIANT>,CrossSectionEnum> ICrossSectionColl;

/////////////////////////////////////////////////////////////////////////////
// CCrossSectionCollection
class ATL_NO_VTABLE CCrossSectionCollection : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CCrossSectionCollection, &CLSID_CrossSectionCollection>,
	public ISupportErrorInfo,
   public IObjectSafetyImpl<CCrossSectionCollection,INTERFACESAFE_FOR_UNTRUSTED_CALLER | INTERFACESAFE_FOR_UNTRUSTED_DATA>,
	public IConnectionPointContainerImpl<CCrossSectionCollection>,
	public ICrossSectionColl,
	public ICrossSectionEvents,
   public IStructuredStorage2,
	public CProxyDCrossSectionCollectionEvents< CCrossSectionCollection >,
   public IPersistImpl<CCrossSectionCollection>
{
public:
	CCrossSectionCollection()
	{
      m_pProfile = NULL;
	}

   HRESULT FinalConstruct();
   void FinalRelease();

   void PutProfile(IProfile* pProfile) { m_pProfile = pProfile; }

DECLARE_REGISTRY_RESOURCEID(IDR_CROSSSECTIONCOLLECTION)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CCrossSectionCollection)
	COM_INTERFACE_ENTRY(ICrossSectionCollection)
   COM_INTERFACE_ENTRY(IStructuredStorage2)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
	COM_INTERFACE_ENTRY(IConnectionPointContainer)
	COM_INTERFACE_ENTRY_IMPL(IConnectionPointContainer)
	
   COM_INTERFACE_ENTRY(ICrossSectionEvents)
   COM_INTERFACE_ENTRY(IObjectSafety)

   COM_INTERFACE_ENTRY(IPersist)
END_COM_MAP()

BEGIN_CONNECTION_POINT_MAP(CCrossSectionCollection)
CONNECTION_POINT_ENTRY(IID_ICrossSectionCollectionEvents)
END_CONNECTION_POINT_MAP()


// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

// ICrossSectionCollection
public:
   STDMETHOD(get_StructuredStorage)(IStructuredStorage2* *pStg);
   STDMETHOD(Clone)(/*[out,retval]*/ ICrossSectionCollection* *clone);
   STDMETHOD(get_CrownPointPath)(/*[out,retval]*/IPath** ppPath);
   STDMETHOD(get_Profile)(/*[out,retval]*/IProfile** ppProfile);
	STDMETHOD(get_Factory)(/*[out,retval]*/ICrossSectionFactory* *factory);
	STDMETHOD(putref_Factory)(/*[in]*/ICrossSectionFactory* factory);
   STDMETHOD(get__EnumCrossSections)(/*[out, retval]*/ IEnumCrossSections** retval);  
	STDMETHOD(Clear)();
   STDMETHOD(CreateCrossSection)(/*[in]*/ VARIANT varStation,/*[out,retval]*/ ICrossSection* *objCS);
//   STDMETHOD(get__NewEnum)(/*[out, retval]*/ IUnknown** retval);  
	STDMETHOD(get_Item)(/*[in]*/ long idx,/*[out, retval]*/ ICrossSection* *pVal);
	STDMETHOD(putref_Item)(/*[in]*/ long idx,/*[in]*/ ICrossSection* pVal);
//	STDMETHOD(get_Count)(/*[out, retval]*/ long *pVal);
	STDMETHOD(Add)(/*[in]*/ VARIANT varStation,/*[in]*/ Float64 cpo, /*[in]*/ Float64 left,/*[in]*/ Float64 right,/*[out,retval]*/ICrossSection* *cs);
	STDMETHOD(AddEx)(/*[in]*/ ICrossSection* csect);
	STDMETHOD(Remove)(/*[in]*/ long idx);
	STDMETHOD(CrownSlope)(/*[in]*/ VARIANT varStation,/*[in]*/ Float64 offset,/*[out,retval]*/ Float64* slope);
	STDMETHOD(LeftCrownSlope)(/*[in]*/ VARIANT varStation,/*[out,retval]*/ Float64* slope);
	STDMETHOD(RightCrownSlope)(/*[in]*/ VARIANT varStation,/*[out,retval]*/ Float64* slope);
	STDMETHOD(CrownPointOffset)(/*[in]*/ VARIANT varStation,/*[out,retval]*/Float64* cpoffset);

// IStructuredStorage2
public:
   STDMETHOD(Save)(IStructuredSave2* pSave);
   STDMETHOD(Load)(IStructuredLoad2* pLoad);

// ICrossSectionEvents
	STDMETHOD(OnCrossSectionChanged)(ICrossSection * csect);
   STDMETHOD(OnCrossSectionMoved)(ICrossSection * csect);

// Helper methods
private:
   HRESULT OnBeforeSave(IStructuredSave2* pSave);
   HRESULT OnBeforeLoad(IStructuredLoad2* pLoad);
   HRESULT GetCrossSectionData(VARIANT varStation,Float64* pCPO,Float64* pLeft,Float64* pRight);
   void Advise(ICrossSection* cs,DWORD* pdwCookie);
   void Unadvise(long idx);
   void UnadviseAll();

   CComPtr<ICrossSectionFactory> m_Factory;

   IProfile* m_pProfile;

   CComPtr<IPath> m_CrownPointPath;
   HRESULT UpdateCrownPointPath();
};

#endif //__CROSSSECTIONCOLLECTION_H_
