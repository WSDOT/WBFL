///////////////////////////////////////////////////////////////////////
// Sections - Model bridge member cross sections
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

// CompositeSection.h : Declaration of the CCompositeSection

#ifndef __COMPOSITESECTION_H_
#define __COMPOSITESECTION_H_

#include "resource.h"       // main symbols

#include "WBFLComCollections.h"

class CCompositeSection;
typedef CComVectorCollectionNoEnum<ICompositeSection,ICompositeSectionItem,CollectionIndexType> CompositeSectionVectorImpl;
typedef CPersistentCollection<CCompositeSection,CompositeSectionVectorImpl,CollectionIndexType> PersistentCompositeSection;

/////////////////////////////////////////////////////////////////////////////
// CCompositeSection
class ATL_NO_VTABLE CCompositeSection : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CCompositeSection, &CLSID_CompositeSection>,
   public IObjectSafetyImpl<CCompositeSection,INTERFACESAFE_FOR_UNTRUSTED_CALLER | INTERFACESAFE_FOR_UNTRUSTED_DATA>,
	public ISupportErrorInfo,
   public ISection,
   public IXYPosition,
	public PersistentCompositeSection
{
public:
	CCompositeSection()
	{
	}

DECLARE_REGISTRY_RESOURCEID(IDR_COMPOSITESECTION)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CCompositeSection)
	COM_INTERFACE_ENTRY(ICompositeSection)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
   COM_INTERFACE_ENTRY(ISection)
   COM_INTERFACE_ENTRY(IXYPosition)
   COM_INTERFACE_ENTRY(IObjectSafety)
   COM_INTERFACE_ENTRY_CHAIN(PersistentCompositeSection)
END_COM_MAP()

protected:
   CComBSTR GetCollectionName()
   {
      return CComBSTR("CompositeSection"); // This is the "Unit Name" stored in the persistance stream
   }

public:
// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid) override;

// ICompositeSection
public:
   STDMETHOD(get_StructuredStorage)(/*[out,retval]*/IStructuredStorage2* *pStg) override;
	STDMETHOD(get_XYPosition)(/*[out, retval]*/ IXYPosition* *pVal) override;
	STDMETHOD(get_Section)(/*[out, retval]*/ ISection* *pVal) override;
//	STDMETHOD(get_Item)(/*[in]*/ CollectionIndexType idx, /*[out, retval]*/ ICompositeSectionItem* *pVal) override;
//	STDMETHOD(get__NewEnum)(/*[out, retval]*/ IUnknown* *pVal) override;
	STDMETHOD(get_Count)(/*[out, retval]*/ CollectionIndexType *pVal) override;
//	STDMETHOD(Remove)(/*[in]*/ CollectionIndexType idx) override;
	STDMETHOD(AddSectionEx)(/*[in]*/ ICompositeSectionItem* sectionItem) override;
   STDMETHOD(AddSection)(/*[in]*/ IShape* shape,/*[in]*/ Float64 E,/*[in]*/ Float64 density,/*[in]*/ VARIANT_BOOL bVoid,/*[in]*/ VARIANT_BOOL bStructural) override;

// ISection
public:
   STDMETHOD(get_BoundingBox)(/*[out, retval]*/ IRect2d* *pVal) override;
	STDMETHOD(get_ElasticProperties)(/*[out, retval]*/ IElasticProperties* *pVal) override;
	STDMETHOD(get_MassProperties)(/*[out, retval]*/ IMassProperties* *pVal) override;
	STDMETHOD(ClipIn)(/*[in]*/ IRect2d* rect,/*[out,retval]*/ ISection** section) override;
	STDMETHOD(ClipWithLine)(/*[in]*/ ILine2d* line,/*[out,retval]*/ ISection** section) override;
	STDMETHOD(Clone)(ISection** clone) override;

// IXYPosition
public:
	STDMETHOD(Offset)(/*[in]*/ Float64 dx,/*[in]*/ Float64 dy) override;
	STDMETHOD(OffsetEx)(/*[in]*/ ISize2d* pSize) override;
	STDMETHOD(get_LocatorPoint)(/*[in]*/ LocatorPointType lp, /*[out,retval]*/ IPoint2d** point) override;
	STDMETHOD(put_LocatorPoint)(/*[in]*/ LocatorPointType lp, /*[in]*/ IPoint2d* point) override;
	STDMETHOD(MoveEx)(/*[in]*/ IPoint2d* pFrom,/*[in]*/ IPoint2d* pTo) override;
	STDMETHOD(RotateEx)(/*[in]*/ IPoint2d* pPoint,/*[in]*/ Float64 angle) override;
	STDMETHOD(Rotate)(/*[in]*/ Float64 cx,/*[in]*/ Float64 cy,/*[in]*/ Float64 angle) override;
};

#endif //__COMPOSITESECTION_H_
