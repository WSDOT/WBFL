///////////////////////////////////////////////////////////////////////
// GenericBridge - Generic Bridge Modeling Framework
// Copyright © 1999-2011  Washington State Department of Transportation
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

// GirderSections.h 

#ifndef INCLUDED_GIRDERSECTIONS_H_
#define INCLUDED_GIRDERSECTIONS_H_

#include "resource.h"       // main symbols
#include "GirderSectionImpl.h"
#include <xutility>

class CFlangedBeam : 
   public CGirderSectionImpl<CFlangedBeam,&CLSID_FlangedGirderSection,
                             IFlangedGirderSection, &IID_IFlangedGirderSection,
                             IPrecastBeam,&CLSID_PrecastBeam>
{
public:
   DECLARE_REGISTRY_RESOURCEID(IDR_FLANGEDBEAM)
	   
   STDMETHODIMP get_MinWebThickness(Float64* tWeb)
   {
      CHECK_RETVAL(tWeb);
      Float64 t1,t2;
      m_Beam->get_T1(&t1);
      m_Beam->get_T2(&t2);
      *tWeb = _cpp_min(t1,t2);
      return S_OK;
   }

   STDMETHODIMP get_EffectiveWebThickness(Float64* tWeb)
   {
      return get_MinWebThickness(tWeb);
   }

   STDMETHODIMP get_MinBottomFlangeThickness(Float64* tf)
   {
      return m_Beam->get_D4(tf); // IBeam
   }

   STDMETHODIMP get_TopFlangeThickness(CollectionIndexType idx,Float64* tFlange)
   {
      if ( idx != 0 )
         return E_INVALIDARG;

      return m_Beam->get_D1(tFlange);
   }

   STDMETHODIMP get_BottomFlangeThickness(CollectionIndexType idx,Float64* tFlange)
   {
      if ( idx != 0 )
         return E_INVALIDARG;

      return m_Beam->get_D4(tFlange);
   }

   STDMETHODIMP get_SplittingZoneDimension(Float64* pSZD)
   {
      return m_Beam->get_Height(pSZD);
   }

   STDMETHODIMP get_SplittingDirection(SplittingDirection* pSD)
   {
      CHECK_RETVAL(pSD);
      *pSD = sdVertical;
      return S_OK;
   }
};


class CBulbTeeSection : 
   public CGirderSectionImpl<CBulbTeeSection,&CLSID_BulbTeeSection,
                             IBulbTeeSection, &IID_IBulbTeeSection,
                             IBulbTee,&CLSID_BulbTee>
{
public:
   DECLARE_REGISTRY_RESOURCEID(IDR_BULBTEE)
	   
   STDMETHODIMP get_MinWebThickness(Float64* tWeb)
   {
      CHECK_RETVAL(tWeb);
      Float64 t1,t2;
      m_Beam->get_T1(&t1);
      m_Beam->get_T2(&t2);
      *tWeb = _cpp_min(t1,t2);
      return S_OK;
   }

   STDMETHODIMP get_EffectiveWebThickness(Float64* tWeb)
   {
      return get_MinWebThickness(tWeb);
   }

   STDMETHODIMP get_MinBottomFlangeThickness(Float64* tf)
   {
      return m_Beam->get_D4(tf); // IBeam
   }

   STDMETHODIMP get_TopFlangeThickness(CollectionIndexType idx,Float64* tFlange)
   {
      if ( idx != 0 )
         return E_INVALIDARG;

      return m_Beam->get_D1(tFlange);
   }

   STDMETHODIMP get_BottomFlangeThickness(CollectionIndexType idx,Float64* tFlange)
   {
      if ( idx != 0 )
         return E_INVALIDARG;

      return m_Beam->get_D5(tFlange);
   }

   STDMETHODIMP get_SplittingZoneDimension(Float64* pSZD)
   {
      return m_Beam->get_Height(pSZD);
   }

   STDMETHODIMP get_SplittingDirection(SplittingDirection* pSD)
   {
      CHECK_RETVAL(pSD);
      *pSD = sdVertical;
      return S_OK;
   }
};

class CNUGirderSection : 
   public CGirderSectionImpl<CNUGirderSection,&CLSID_NUGirderSection,
                             INUGirderSection,&IID_INUGirderSection,
                             INUBeam,&CLSID_NUBeam>
{
public:
   DECLARE_REGISTRY_RESOURCEID(IDR_NUGIRDERSECTION)
	   
   STDMETHODIMP get_MinWebThickness(Float64* tWeb)
   {
      return m_Beam->get_T(tWeb);
   }
	   
   STDMETHODIMP get_EffectiveWebThickness(Float64* tWeb)
   {
      return get_MinWebThickness(tWeb);
   }

   STDMETHODIMP get_MinBottomFlangeThickness(Float64* tf)
   {
      return m_Beam->get_D5(tf); // NUBeam
   } 

   STDMETHODIMP get_TopFlangeThickness(CollectionIndexType idx,Float64* tFlange)
   {
      if ( idx != 0 )
         return E_INVALIDARG;

      return m_Beam->get_D1(tFlange);
   }

   STDMETHODIMP get_BottomFlangeThickness(CollectionIndexType idx,Float64* tFlange)
   {
      if ( idx != 0 )
         return E_INVALIDARG;

      return m_Beam->get_D5(tFlange);
   }

   STDMETHODIMP get_SplittingZoneDimension(Float64* pSZD)
   {
      return m_Beam->get_Height(pSZD);
   }

   STDMETHODIMP get_SplittingDirection(SplittingDirection* pSD)
   {
      CHECK_RETVAL(pSD);
      *pSD = sdVertical;
      return S_OK;
   }
};

#endif //  INCLUDED_GIRDERSECTIONS_H_