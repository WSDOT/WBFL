///////////////////////////////////////////////////////////////////////
// GenericBridgeTools - Tools for manipluating the Generic Bridge Modeling
// Copyright © 1999-2019  Washington State Department of Transportation
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

// StrandModelBase.h : Declaration of the CStrandModelBase

#pragma once

#include "resource.h"       // main symbols
#include <array>
#include <map>

// This class is a base class for all strand models. It provides
// the common implementation

/////////////////////////////////////////////////////////////////////////////
// CStrandModelBase
class CStrandModelBase
{
public:
   CStrandModelBase()
   {
      // default harping point... fraction of girder length, measured from ends of girder
      m_HPMeasure = hpmFractionOfGirderLength;
      m_EndHPMeasure = hpmFractionOfGirderLength;
      m_HPReference = hprEndOfGirder;
      m_EndHPReference = hprEndOfGirder;
      m_HPStart = 0.0;
      m_HP1 = 0.4;
      m_HP2 = 0.4;
      m_HPEnd = 0.0;
      m_bUseMinHpDistance = VARIANT_FALSE;
      m_MinHpDist = 0;

      m_StraightStrandProfileType = FollowGirder;
      m_TemporaryStrandProfileType = Linear;

      m_pSegment = nullptr;
      m_pGirder = nullptr;
   }

protected:

   // HPStart and HP1 are measured from the left end of the girder
   // HPEnd and HP2 are measured from the right end of the girder
   Float64 m_HPStart, m_HPEnd; // location of the m_HarpGridEnd harp grids
   Float64 m_HP1, m_HP2; // harping point location (location of the m_HarpGridHp harp grids)
   HarpPointReference m_HPReference; // describes from where the harping point is measured
   HarpPointMeasure m_HPMeasure;    // describes how the middle harping point is located

   HarpPointReference m_EndHPReference; // describes from where the harping point is measured for the end harp points
   HarpPointMeasure m_EndHPMeasure; // describes how the end harping point is located

   VARIANT_BOOL m_bUseMinHpDistance;
   Float64 m_MinHpDist;

   std::array<CComPtr<IPrestressingStrand>, 3> m_StrandMaterial;
   StrandProfileType m_StraightStrandProfileType;
   StrandProfileType m_TemporaryStrandProfileType;

   ISuperstructureMemberSegment* m_pSegment; // weak reference to the superstructure member segment for this girder
   IPrecastGirder* m_pGirder; // weak reference to precast girder

   virtual HRESULT OnInitialize() { return S_OK; }

   std::map<Float64, CComPtr<IPoint2d>> m_CGs[3]; // cache of strand CG. Key is location where computed. Array index is strandtype

// IStrandModel (partial implementation - base classes to do the rest)
public:
   STDMETHOD(Initialize)(ISuperstructureMemberSegment* segment,IPrecastGirder* pGirder);
   STDMETHOD(putref_StrandMaterial)(StrandType strandType,IPrestressingStrand* pMaterial);
   STDMETHOD(get_StrandMaterial)(StrandType strandType, IPrestressingStrand** ppMaterial);

   STDMETHOD(SetHarpingPoints)(Float64 hp1, Float64 hp2);
   STDMETHOD(GetHarpingPoints)(Float64* hp1, Float64* hp2);
   STDMETHOD(SetEndHarpingPoints)(Float64 hp1, Float64 hp2);
   STDMETHOD(GetEndHarpingPoints)(Float64* hp1, Float64* hp2);
   STDMETHOD(put_HarpingPointMeasure)(HarpPointMeasure measure);
   STDMETHOD(get_HarpingPointMeasure)(HarpPointMeasure* measure);
   STDMETHOD(put_EndHarpingPointMeasure)(HarpPointMeasure measure);
   STDMETHOD(get_EndHarpingPointMeasure)(HarpPointMeasure* measure);
   STDMETHOD(put_HarpingPointReference)(HarpPointReference hpRef);
   STDMETHOD(get_HarpingPointReference)(HarpPointReference* hpRef);
   STDMETHOD(put_EndHarpingPointReference)(HarpPointReference hpRef);
   STDMETHOD(get_EndHarpingPointReference)(HarpPointReference* hpRef);
   STDMETHOD(put_UseMinHarpPointDistance)(VARIANT_BOOL bUseMin);
   STDMETHOD(get_UseMinHarpPointDistance)(VARIANT_BOOL* bUseMin);
   STDMETHOD(put_MinHarpPointDistance)(Float64 minHpDist);
   STDMETHOD(get_MinHarpPointDistance)(Float64* minHpDist);
   STDMETHOD(GetHarpingPointLocations)(Float64* hp1, Float64* hp2);
   STDMETHOD(GetEndHarpingPointLocations)(Float64* hp1, Float64* hp2);

   STDMETHOD(put_StraightStrandProfileType)(StrandProfileType profileType);
   STDMETHOD(get_StraightStrandProfileType)(StrandProfileType* pProfileType);
   STDMETHOD(put_TemporaryStrandProfileType)(StrandProfileType profileType);
   STDMETHOD(get_TemporaryStrandProfileType)(StrandProfileType* pProfileType);

protected:
   void GetHarpPointLocations(Float64& hp1, Float64& hp2,Float64& hp3,Float64& hp4) const;
   void GetHarpPointLocations(Float64& hp1, Float64& hp2) const;
   void GetEndHarpPointLocations(Float64& hp1, Float64& hp2) const;
   Float64 GetHarpPointLocation(Float64 hp, HarpPointReference hpRef, HarpPointMeasure hpMeasure, bool bRight, bool bLocatingEndHarpPoint) const;
   Float64 GetGirderWidthAdjustment(Float64 Xs) const;
};
