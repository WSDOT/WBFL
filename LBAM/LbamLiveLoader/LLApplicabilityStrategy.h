///////////////////////////////////////////////////////////////////////
// LBAM Live Loader - Longitindal Bridge Analysis Model
// Copyright © 1999-2010  Washington State Department of Transportation
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

#ifndef __iLLApplicabilityStrategy_H_
#define __iLLApplicabilityStrategy_H_


// class for determining applicable locations for live load response
enum ApplicabilityLoc {appNone=0, appRight=1, appLeft=2, appBoth=3}; // meant to be bitwise or'ed

class iLLApplicabilityStrategy
{
public:
   virtual ApplicabilityLoc GetApplicability(long poiId, BSTR stage,  
                                          VARIANT_BOOL isApplicable, LiveLoadApplicabilityType llapplicability, 
                                          ForceEffectType optimizedEffect, OptimizationType optimization)=0;
};

//////////////////////////
// Forces
//////////////////////////
class ForceLLApplicabilityStrategy: public iLLApplicabilityStrategy
{
public:
   ForceLLApplicabilityStrategy(ILiveLoadNegativeMomentRegion* llnmr):
   m_LiveLoadNegativeMomentRegion(llnmr)
   {;}

   virtual ApplicabilityLoc GetApplicability(long poiId, BSTR stage,  
                                          VARIANT_BOOL isApplicable, LiveLoadApplicabilityType llapplicability, 
                                          ForceEffectType optimizedEffect, OptimizationType optimization)
   {
      if (isApplicable==VARIANT_FALSE)
      {
         // placement is not applicable
         return appNone;
      }
      else if (llapplicability==llaEntireStructure)
      {
         return appBoth;
      }
      else if (llapplicability==llaContraflexure)
      {
         // only applicable for negative moment in contraflexure zone
         if (optimizedEffect==fetMz && optimization==optMinimize)
         {
            InZoneType is_in_zone;
            HRESULT hr = m_LiveLoadNegativeMomentRegion->get_IsPOIInNegativeLiveLoadMomentZone(poiId, stage, &is_in_zone);
            PROCESS_HR(hr);

            if (is_in_zone==izInside)
               return appBoth;
            else if (is_in_zone==izLeftEdge)
               return appRight;
            else if (is_in_zone==izRightEdge)
               return appLeft;
         }
      }

      return appNone;
   }

private:
   ILiveLoadNegativeMomentRegion* m_LiveLoadNegativeMomentRegion;
};


//////////////////////////
// Deflections
//////////////////////////
class DeflectionLLApplicabilityStrategy: public iLLApplicabilityStrategy
{
public:
   DeflectionLLApplicabilityStrategy()
   {;}

   virtual ApplicabilityLoc GetApplicability(long poiId, BSTR stage,  
                                          VARIANT_BOOL isApplicable, LiveLoadApplicabilityType llapplicability, 
                                          ForceEffectType optimizedEffect, OptimizationType optimization)
   {
      if (isApplicable==VARIANT_FALSE)
      {
         // placement is not applicable
         return appNone;
      }
      else if (llapplicability==llaEntireStructure)
      {
         return appBoth;
      }
      else
         return appNone;
   }

};


//////////////////////////
// Reactions
//////////////////////////
class ReactionLLApplicabilityStrategy: public iLLApplicabilityStrategy
{
public:
   ReactionLLApplicabilityStrategy(ISupportLocations* supportlocs):
   m_SupportLocations(supportlocs)
   {;}

   virtual ApplicabilityLoc GetApplicability(long supportId, BSTR stage,  
                                          VARIANT_BOOL isApplicable, LiveLoadApplicabilityType llapplicability, 
                                          ForceEffectType optimizedEffect, OptimizationType optimization)
   {
      if (isApplicable==VARIANT_FALSE)
      {
         // placement is not applicable
         return appNone;
      }
      else if (llapplicability==llaEntireStructure)
      {
         return appBoth;
      }
      else if (llapplicability==llaContraflexure)
      {
         // only applicable for interior supports
         HRESULT hr;
         VARIANT_BOOL isInteriorSupport;
         hr = m_SupportLocations->IsInteriorSupport(supportId, &isInteriorSupport);
         if (isInteriorSupport == VARIANT_TRUE && optimization == optMaximize )
         {
            return appBoth;
         }
      }

      return appNone;
   }

private:
   ISupportLocations* m_SupportLocations;
};


//////////////////////////
// Support Deflections
//////////////////////////
// Inherits all behavior from DeflectionLLApplicabilityStrategy
class SupportDeflectionLLApplicabilityStrategy: public DeflectionLLApplicabilityStrategy
{
public:
   SupportDeflectionLLApplicabilityStrategy()
   {;}
};


#endif