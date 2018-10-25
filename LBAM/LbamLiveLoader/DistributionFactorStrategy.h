///////////////////////////////////////////////////////////////////////
// LBAM Live Loader - Longitindal Bridge Analysis Model
// Copyright © 1999-2017  Washington State Department of Transportation
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

#ifndef __iDistributionFactorStrategy_H_
#define __iDistributionFactorStrategy_H_

// Use Strategy pattern for determining distribution factor values for various effect types
// This eliminates lots of case statements in the live loader code, but is still complex.
// NASTY stuff - Thanks AASHTO LRFD spec! (or "Why the Simplified Method Ain't So Simple")

class iDistributionFactorStrategy
{
public:
   // single distribution factor for optimized response in question
   virtual void GetOptimalDfs(PoiIDType poiID, BSTR Stage, ForceEffectType effect,
                              DistributionFactorType distributionType,
                              Float64* leftFactor, DistributionFactorType* usedLeftDistributionType,
                              Float64* rightFactor, DistributionFactorType* usedRightDistributionType) = 0;

   // All three distribution factors for concurrent response
   virtual void GetConcurrentDfs(PoiIDType poiID, BSTR Stage, 
                                 DistributionFactorType distributionType,
                                 Float64* leftFxFactor, Float64* leftFyFactor, Float64* leftMzFactor, 
                                 Float64* rightFxFactor, Float64* rightFyFactor, Float64* rightMzFactor) = 0;
};

// strategy for force results
class ForceDistributionFactorStrategy : public iDistributionFactorStrategy
{
public:
   ForceDistributionFactorStrategy(IGetDistributionFactors* getDistributionFactors, OptimizationType optimization):
   m_GetDistributionFactors(getDistributionFactors),
   m_Optimization(optimization)
   {;}

   virtual void GetOptimalDfs(PoiIDType poiID, BSTR Stage, ForceEffectType effect,
                              DistributionFactorType distributionType,
                              Float64* leftFactor, DistributionFactorType* usedLeftDistributionType,
                              Float64* rightFactor, DistributionFactorType* usedRightDistributionType);

   virtual void GetConcurrentDfs(PoiIDType poiID, BSTR Stage, 
                                 DistributionFactorType distributionType,
                                 Float64* leftFxFactor, Float64* leftFyFactor, Float64* leftMzFactor, 
                                 Float64* rightFxFactor, Float64* rightFyFactor, Float64* rightMzFactor);

private:
   IGetDistributionFactors* m_GetDistributionFactors;
   OptimizationType         m_Optimization;
};

// strategy for deflection results
class DeflectionDistributionFactorStrategy : public iDistributionFactorStrategy
{
public:
   DeflectionDistributionFactorStrategy(IGetDistributionFactors* getDistributionFactors):
   m_GetDistributionFactors(getDistributionFactors)
   {;}

   virtual void GetOptimalDfs(PoiIDType poiID, BSTR Stage, ForceEffectType effect,
                                       DistributionFactorType distributionType,
                                       Float64* leftFactor, DistributionFactorType* usedLeftDistributionType,
                                       Float64* rightFactor, DistributionFactorType* usedRightDistributionType);

   virtual void GetConcurrentDfs(PoiIDType poiID, BSTR Stage, 
                                 DistributionFactorType distributionType,
                                 Float64* leftFxFactor, Float64* leftFyFactor, Float64* leftMzFactor, 
                                 Float64* rightFxFactor, Float64* rightFyFactor, Float64* rightMzFactor);

private:
   IGetDistributionFactors* m_GetDistributionFactors;
};

// strategy for Reaction results
class ReactionDistributionFactorStrategy : public iDistributionFactorStrategy
{
public:
   ReactionDistributionFactorStrategy(IGetDistributionFactors* getDistributionFactors):
   m_GetDistributionFactors(getDistributionFactors)
   {;}

   virtual void GetOptimalDfs(PoiIDType poiID, BSTR Stage, ForceEffectType effect, 
                                       DistributionFactorType distributionType,
                                       Float64* leftFactor, DistributionFactorType* usedLeftDistributionType,
                                       Float64* rightFactor, DistributionFactorType* usedRightDistributionType);

   virtual void GetConcurrentDfs(PoiIDType poiID, BSTR Stage, 
                                 DistributionFactorType distributionType,
                                 Float64* leftFxFactor, Float64* leftFyFactor, Float64* leftMzFactor, 
                                 Float64* rightFxFactor, Float64* rightFyFactor, Float64* rightMzFactor);

private:
   IGetDistributionFactors* m_GetDistributionFactors;
};

// strategy for SupportDeflection results
class SupportDeflectionDistributionFactorStrategy : public iDistributionFactorStrategy
{
public:
   SupportDeflectionDistributionFactorStrategy(IGetDistributionFactors* getDistributionFactors):
   m_GetDistributionFactors(getDistributionFactors)
   {;}

   virtual void GetOptimalDfs(PoiIDType poiID, BSTR Stage, ForceEffectType effect, 
                                       DistributionFactorType distributionType,
                                       Float64* leftFactor, DistributionFactorType* usedLeftDistributionType,
                                       Float64* rightFactor, DistributionFactorType* usedRightDistributionType);

   virtual void GetConcurrentDfs(PoiIDType poiID, BSTR Stage, 
                                 DistributionFactorType distributionType,
                                 Float64* leftFxFactor, Float64* leftFyFactor, Float64* leftMzFactor, 
                                 Float64* rightFxFactor, Float64* rightFyFactor, Float64* rightMzFactor);

private:
   IGetDistributionFactors* m_GetDistributionFactors;
};


#endif