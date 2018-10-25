///////////////////////////////////////////////////////////////////////
// LBAM Analysis - Longitindal Bridge Analysis Model
// Copyright © 1999-2011  Washington State Department of Transportation
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


#if !defined INCLUDED_ANALYSISUTILS_H_
#define INCLUDED_ANALYSISUTILS_H_

#include <vector>

// interfaces to get stage and load group ordering
class IStageOrder
{
public:
   virtual StageIndexType StageCount()=0;
   virtual CComBSTR Stage(StageIndexType index)=0;
   virtual bool GetStageIndex(BSTR stage,StageIndexType* pStageIdx) = 0;
};

class ILoadGroupOrder
{
public:
   virtual CollectionIndexType LoadGroupCount()=0;
   virtual CComBSTR LoadGroup(CollectionIndexType index)=0;
   virtual void GetLoadGroupInfo(BSTR LoadGroup, LoadGroupIDType* femLgId, bool* isTransient)=0;
   virtual void GetLoadGroupInfoByIndex(CollectionIndexType index, LoadCaseIDType* femLcId, bool* isTransient)=0;
   virtual void SetLoadGroupAsActive(BSTR LoadGroup)=0;
};


// very simple adaption of a vector of Float64s that is meant to allow you to
// add points that define regions along a number line. The new function joins
// overlapping regions
class DblRegion: public std::vector<Float64>
{
public:
   void AddLocation(Float64 loc)
   {
      CollectionIndexType size = this->size();
      if (size==0)
      {
         push_back(loc);
      }
      else 
      {
         // TRICKY: overlap only occurs if we are trying to add a left value that's at the same
         //         location of the right end of the previous zone

         Float64 last = back();
         bool is_left = size%2 == 0;

         if (is_left && loc==last)
         {
            // attempt to add an overlapping value - remove location altogether
            pop_back();
         }
         else
         {
            push_back(loc);
         }
      }
   }
};


#endif 