///////////////////////////////////////////////////////////////////////
// BAM - Bridge Analysis Model, Analytical modeling of bridge structures
// Copyright © 1999-2013  Washington State Department of Transportation
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

#ifndef INCLUDED_BRIDGEANALYSIS_SUPPORTELEMENT_H_
#define INCLUDED_BRIDGEANALYSIS_SUPPORTELEMENT_H_
#pragma once

#include <BridgeAnalysis\BridgeAnalysisExp.h>
#include <BridgeAnalysis\LoadCase.h>
#include <GraphicsLib\PointMapper.h>
#include <map>

class bamBridgeModel;
class bamLoad;
class bamSpanElement;


struct bamSupportElementInfo
{
   SupportIDType m_SupportElementId;
   Float64 m_Location;
   bamSupportFixity m_SupportFixity;
};

typedef bamSupportElementInfo bamSupportElementInfo;

class bamSupportElement
{
public:
   bamSupportElement(SupportIDType id,Float64 location,bamSupportFixity fixity);
   bamSupportElement(const bamSupportElementInfo& rSupportElementInfo);
   virtual ~bamSupportElement();

   void GetSupportElementInfo(bamSupportElementInfo& rSupportElementInfo) const;

   SupportIDType GetID() const;

   Float64 GetLocation() const;
   bamSupportFixity GetFixity() const;

   virtual bamSupportElement* Clone() const;

   bamLoad* GetSelfWeightLoad();
   void Draw(HDC hDC,const grlibPointMapper& mapper) const;

   COLORREF m_Color;

   // Method:      AddSpanElement
   // Description: To be caled when a SpanElement is connected
   //              to this SupportElement
   void AddSpanElement(bamSpanElement* pSpanElement);

   // Method:      RemoveSpanElement
   // Description: To be called when a previously connected SpanElement
   //              is disconnected from this SupportElement
   void RemoveSpanElement(bamSpanElement* pSpanElement);

   // Method:      OnRemove
   // Description: To be called when a SupportElement is about
   //              to be removed from the model
   void OnRemove();

protected:
   void SetSupportSize(Int16 size); // in thousandths of an inch
   Int16 GetSupportSize() const;

private:
   SupportIDType m_ID;
   Float64 m_Location;
   Int16 m_SupportSize;
   bamSupportFixity m_Fixity;
   bamBridgeModel* m_pModel;

   typedef std::map<SpanIDType, bamSpanElement*, std::less<SpanIDType>, std::allocator<bamSpanElement*> > SpanElementContainer;
   typedef SpanElementContainer::iterator SpanElementIterator;
   SpanElementContainer m_SpanElements;


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

// inline
inline SupportIDType bamSupportElement::GetID() const { return m_ID; }
inline void bamSupportElement::SetSupportSize(Int16 size) {m_SupportSize = size;}
inline Int16  bamSupportElement::GetSupportSize() const {return m_SupportSize;}

#endif // INCLUDED_BRIDGEANALYSIS_SUPPORTELEMENT_H_