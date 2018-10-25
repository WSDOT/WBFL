///////////////////////////////////////////////////////////////////////
// BAM - Bridge Analysis Model, Analytical modeling of bridge structures
// Copyright © 1999-2014  Washington State Department of Transportation
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

#ifndef INCLUDED_BRIDGEANALYSIS_SPANELEMENT_H_
#define INCLUDED_BRIDGEANALYSIS_SPANELEMENT_H_
#pragma once

#include <BridgeAnalysis\BridgeAnalysisExp.h>
#include <BridgeAnalysis\SegmentInfo.h>
#include <GraphicsLib\PointMapper.h>


class bamLoad;
class bamSupportElement;
class bamBridgeModel;

struct bamSpanElementInfo
{
   bamSpanElementInfo();
   SpanIDType m_Id;
   Int32 m_SegmentCount;
   bamSegmentInfo* m_pSegmentInfo;
   SupportIDType m_StartSupportId;
   SupportIDType m_EndSupportId;
};

inline bamSpanElementInfo::bamSpanElementInfo()
{
   m_Id = -1;
   m_SegmentCount = 0;
   m_pSegmentInfo = 0;
   m_StartSupportId = 0;
   m_EndSupportId = 0;
}

typedef bamSpanElementInfo bamSpanElementInfo;

class bamSpanElement
{
public:
   bamSpanElement(const bamSpanElementInfo& rSpanElementInfo);
   bamSpanElement(SpanIDType id,Float64 ax,Float64 iz,Float64 mode,Float64 density);
   virtual ~bamSpanElement();

   SpanIDType GetID() const;
   Float64 GetAx() const;
   Float64 GetIz() const;
   Float64 GetModE() const;
   Float64 GetDensity() const;

   void GetSpanElementInfo(bamSpanElementInfo& rSpanElementInfo) const;

   Float64 Length() const;

   void SetStartSupport(bamSupportElement* pSupportElement);
   bamSupportElement* GetStartSupport() const;
   void SetEndSupport(bamSupportElement* pSupportElement);
   bamSupportElement* GetEndSupport() const;
   void RemoveSupportElement(bamSupportElement* pSupportElement);
   const bamSupportElement& StartSupport() const;
   const bamSupportElement& EndSupport() const;
   void OnRemove();

   virtual bamSpanElement* Clone() const;

   bamLoad* GetSelfWeightLoad();

   void Draw(HDC hDC,const grlibPointMapper& mapper) const;

   COLORREF m_Color;

private:
   SpanIDType m_ID;
   Float64 m_Ax;
   Float64 m_Iz;
   Float64 m_ModE;
   Float64 m_Density;
   bamSupportElement* m_pStartSupport;
   bamSupportElement* m_pEndSupport;
   bamBridgeModel* m_pModel;

   void SetModel(bamBridgeModel* pModel);

   friend bamBridgeModel;

public:
   // GROUP: DEBUG
   #if defined _DEBUG
   //------------------------------------------------------------------------
   // Returns true if the object is in a valid state, otherwise returns false.
   virtual bool AssertValid() const;

   //------------------------------------------------------------------------
   // Dumps the contents of the object to the given dump context.
   virtual void Dump(dbgDumpContext& os) const;
   #endif // _DEBUG

   #if defined _UNITTEST
   //------------------------------------------------------------------------
   // Runs a self-diagnostic test.  Returns true if the test passed,
   // otherwise false.
   static bool TestMe(dbgLog& rlog);
   #endif // _UNITTEST
};

#endif // INCLUDED_BRIDGEANALYSIS_SPANELEMENT_H_