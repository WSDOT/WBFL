///////////////////////////////////////////////////////////////////////
// LBAM Live Load Test - Test driver for LBAM analysis library
// Copyright © 1999-2013  Washington State Department of Transportation
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

#include "StdAfx.h"
#include "WBFLLBAMLiveLoader.h"
#include "DistributionFactorStrategy.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//////////////////
// Free functions to retrieve distribution factors
//////////////////

// use member function pointers to simplify life (at least cut down on a pile of repetitive code)
typedef HRESULT(__stdcall IDistributionFactor::* PdfFn)(Float64* factor);

inline void GetDF(IDistributionFactor* leftDf, IDistributionFactor* rightDf, PdfFn Function, Float64* leftFactor, Float64* rightFactor)
{
   CHRException hr;
   hr = (leftDf->*Function)(leftFactor);
   if (rightDf!=NULL)
   {
      hr = (rightDf->*Function)(rightFactor);
   }
   else
   {
      *rightFactor = *leftFactor;
   }
}

inline void GetDF1(IDistributionFactor* Df, PdfFn Function, Float64* Factor)
{
   CHRException hr;
   hr = (Df->*Function)(Factor);
}


///////////////////////////////////////////////////////
// Force strategy
///////////////////////////////////////////////////////
// optimized effects
static void GetOptForceSglDf(ForceEffectType effect, OptimizationType optimization, 
              IDistributionFactor* left_df, IDistributionFactor* right_df,
              Float64* left_factor, Float64* right_factor)
{
   if (effect==fetMz)
   {
      if  (optimization==optMinimize)
      {
         // negative moment
         GetDF(left_df, right_df, &IDistributionFactor::get_GNMSgl, left_factor, right_factor);
      }
      else
      {
         // all other effects use positive moment value
         GetDF(left_df, right_df, &IDistributionFactor::get_GPMSgl, left_factor, right_factor);
      }
   }
   else
   {
      // all other cases use shear
      GetDF(left_df, right_df, &IDistributionFactor::get_GVSgl, left_factor, right_factor);
   }

}

static void GetOptForceMulDf(ForceEffectType effect, OptimizationType optimization, 
              IDistributionFactor* left_df, IDistributionFactor* right_df,
              Float64* left_factor, Float64* right_factor)
{
   if (effect==fetMz)
   {
      if  (optimization==optMinimize)
      {
         // negative moment
         GetDF(left_df, right_df, &IDistributionFactor::get_GNMMul, left_factor, right_factor);
      }
      else
      {
         // all other effects use positive moment value
         GetDF(left_df, right_df, &IDistributionFactor::get_GPMMul, left_factor, right_factor);
      }
   }
   else
   {
      // all other cases use shear
      GetDF(left_df, right_df, &IDistributionFactor::get_GVMul, left_factor, right_factor);
   }
}

void ForceDistributionFactorStrategy::GetOptimalDfs(PoiIDType poiID, BSTR Stage, ForceEffectType effect,
                                                    DistributionFactorType distributionType,
                                                    Float64* leftFactor, DistributionFactorType* usedLeftDistributionType,
                                                    Float64* rightFactor, DistributionFactorType* usedRightDistributionType)
{
   CHRException hr;

   CComPtr<IDistributionFactor> left_df, right_df;
   hr = m_GetDistributionFactors->GetPOIDistributionFactor(poiID, Stage, &left_df, &right_df);

   if (left_df==NULL)
   {
      ATLASSERT(0);
      hr = E_FAIL; // this should never happen
   }

   switch (distributionType)
   {
   case dftSingleLane:
      {
         GetOptForceSglDf(effect, m_Optimization, left_df, right_df, leftFactor, rightFactor);
         *usedLeftDistributionType = dftSingleLane;
         *usedRightDistributionType = dftSingleLane;
         break;
      }
   case dftMultipleLane:
      {
         GetOptForceMulDf(effect, m_Optimization, left_df, right_df, leftFactor, rightFactor);
         *usedLeftDistributionType = dftMultipleLane;
         *usedRightDistributionType = dftMultipleLane;
         break;
      }
   case dftEnvelope:
      {
         Float64 left_sgl_factor, right_sgl_factor;
         GetOptForceSglDf(effect, m_Optimization, left_df, right_df, &left_sgl_factor, &right_sgl_factor);
         Float64 left_mul_factor, right_mul_factor;
         GetOptForceMulDf(effect, m_Optimization, left_df, right_df, &left_mul_factor, &right_mul_factor);

         // take max of single and multiple lane values
         if (right_sgl_factor> right_mul_factor)
         {
            *rightFactor = right_sgl_factor;
            *usedRightDistributionType = dftSingleLane;
         }
         else
         {
            *rightFactor = right_mul_factor;
            *usedRightDistributionType = dftMultipleLane;
         }

         if (left_sgl_factor> left_mul_factor)
         {
            *leftFactor = left_sgl_factor;
            *usedLeftDistributionType = dftSingleLane;
         }
         else
         {
            *leftFactor = left_mul_factor;
            *usedLeftDistributionType = dftMultipleLane;
         }
      }
      break;
   case dftFatigue:
      {
         GetDF(left_df, right_df, &IDistributionFactor::get_GFat, leftFactor, rightFactor);
         *usedLeftDistributionType = dftFatigue;
         *usedRightDistributionType = dftFatigue;
      }
      break;
   case dftPedestrian:
      {
         GetDF(left_df, right_df, &IDistributionFactor::get_GPedestrian, leftFactor, rightFactor);
         *usedLeftDistributionType = dftPedestrian;
         *usedRightDistributionType = dftPedestrian;
      }
      break;
   default:
      ATLASSERT(0);
      *leftFactor = 1.0;
      *rightFactor = 1.0;
      *usedLeftDistributionType = dftNone;
      *usedRightDistributionType = dftNone;
   }
}

// concurrent effects
static void GetConcForceSglDf(OptimizationType optimization, 
              IDistributionFactor* left_df, IDistributionFactor* right_df,
              Float64* leftFxFactor, Float64* leftFyFactor, Float64* leftMzFactor, 
              Float64* rightFxFactor, Float64* rightFyFactor, Float64* rightMzFactor)
{
   Float64 left_sheardf,  right_sheardf;
   Float64 left_momentdf, right_momentdf;
   GetDF(left_df, right_df, &IDistributionFactor::get_GVSgl, &left_sheardf, &right_sheardf);

   if (optimization==optMinimize)
   {
      GetDF(left_df, right_df, &IDistributionFactor::get_GNMSgl, &left_momentdf, &right_momentdf);
   }
   else 
   {
      // all other effects use positive moment value
      GetDF(left_df, right_df, &IDistributionFactor::get_GPMSgl, &left_momentdf, &right_momentdf);
   }

   *leftFxFactor  = left_sheardf;
   *leftFyFactor  = left_sheardf;
   *leftMzFactor  = left_momentdf;
   *rightFxFactor = right_sheardf;
   *rightFyFactor = right_sheardf;
   *rightMzFactor = right_momentdf;
}

static void GetConcForceMulDf(OptimizationType optimization, 
              IDistributionFactor* left_df, IDistributionFactor* right_df,
              Float64* leftFxFactor, Float64* leftFyFactor, Float64* leftMzFactor, 
              Float64* rightFxFactor, Float64* rightFyFactor, Float64* rightMzFactor)
{
   Float64 left_sheardf,  right_sheardf;
   Float64 left_momentdf, right_momentdf;
   GetDF(left_df, right_df, &IDistributionFactor::get_GVMul, &left_sheardf, &right_sheardf);

   if (optimization==optMinimize)
   {
      GetDF(left_df, right_df, &IDistributionFactor::get_GNMMul, &left_momentdf, &right_momentdf);
   }
   else 
   {
      // all other effects use positive moment value
      GetDF(left_df, right_df, &IDistributionFactor::get_GPMMul, &left_momentdf, &right_momentdf);
   }

   *leftFxFactor  = left_sheardf;
   *leftFyFactor  = left_sheardf;
   *leftMzFactor  = left_momentdf;
   *rightFxFactor = right_sheardf;
   *rightFyFactor = right_sheardf;
   *rightMzFactor = right_momentdf;
}

void ForceDistributionFactorStrategy::GetConcurrentDfs(PoiIDType poiID, BSTR Stage, 
                                                       DistributionFactorType distributionType,
                                                       Float64* leftFxFactor, Float64* leftFyFactor, Float64* leftMzFactor, 
                                                       Float64* rightFxFactor, Float64* rightFyFactor, Float64* rightMzFactor)
{
   CHRException hr;
   CComPtr<IDistributionFactor> left_df, right_df;
   hr = m_GetDistributionFactors->GetPOIDistributionFactor(poiID, Stage, &left_df, &right_df);

   if (left_df==NULL)
   {
      ATLASSERT(0);
      hr = E_FAIL; // this should never happen
   }

   switch (distributionType)
   {
   case dftSingleLane:
      {
         GetConcForceSglDf(m_Optimization,left_df, right_df,
                           leftFxFactor, leftFyFactor, leftMzFactor, 
                           rightFxFactor, rightFyFactor, rightMzFactor);
      }
      break;
   case dftMultipleLane:
      {
         GetConcForceMulDf(m_Optimization,left_df, right_df,
                           leftFxFactor, leftFyFactor, leftMzFactor, 
                           rightFxFactor, rightFyFactor, rightMzFactor);
      }
      break;
   case dftEnvelope:
      {
         Float64 left_sgl_fx, left_sgl_fy, left_sgl_mz;
         Float64 right_sgl_fx, right_sgl_fy, right_sgl_mz;
         GetConcForceSglDf(m_Optimization,left_df, right_df,
                           &left_sgl_fx,  &left_sgl_fy,  &left_sgl_mz,
                           &right_sgl_fx, &right_sgl_fy, &right_sgl_mz);

         Float64 left_mul_fx, left_mul_fy, left_mul_mz;
         Float64 right_mul_fx, right_mul_fy, right_mul_mz;
         GetConcForceMulDf(m_Optimization,left_df, right_df,
                           &left_mul_fx,  &left_mul_fy,  &left_mul_mz,
                           &right_mul_fx, &right_mul_fy, &right_mul_mz);

         *leftFxFactor  = max(left_sgl_fx,  left_mul_fx);
         *leftFyFactor  = max(left_sgl_fy,  left_mul_fy);
         *leftMzFactor  = max(left_sgl_mz,  left_mul_mz);
         *rightFxFactor = max(right_sgl_fx, right_mul_fx);
         *rightFyFactor = max(right_sgl_fy, right_mul_fy);
         *rightMzFactor = max(right_sgl_mz, right_mul_mz);

      }
      break;
   case dftFatigue:
      {
         Float64 left_factor, right_factor;
         GetDF(left_df, right_df, &IDistributionFactor::get_GFat, &left_factor, &right_factor);
         *leftFxFactor  = left_factor;
         *leftFyFactor  = left_factor;
         *leftMzFactor  = left_factor;
         *rightFxFactor = right_factor;
         *rightFyFactor = right_factor;
         *rightMzFactor = right_factor;
      }
      break;
   case dftPedestrian:
      {
         Float64 left_factor, right_factor;
         GetDF(left_df, right_df, &IDistributionFactor::get_GPedestrian, &left_factor, &right_factor);
         *leftFxFactor  = left_factor;
         *leftFyFactor  = left_factor;
         *leftMzFactor  = left_factor;
         *rightFxFactor = right_factor;
         *rightFyFactor = right_factor;
         *rightMzFactor = right_factor;
      }
      break;
   default:
      ATLASSERT(0);
      *leftFxFactor  = 1.0;
      *leftFyFactor  = 1.0;
      *leftMzFactor  = 1.0;
      *rightFxFactor = 1.0;
      *rightFyFactor = 1.0;
      *rightMzFactor = 1.0;
   }
}

///////////////////////////////////////////////////////
// Deflection strategy
///////////////////////////////////////////////////////
// optimal effects
static void GetDeflectionSglDf(ForceEffectType forceEffect, IDistributionFactor* left_df, IDistributionFactor* right_df,
                               Float64* left_factor, Float64* right_factor)
{
   if (forceEffect==fetMz)
   {  // rotation factor
      GetDF(left_df, right_df, &IDistributionFactor::get_GTSgl, left_factor, right_factor);
   }
   else
   {
      GetDF(left_df, right_df, &IDistributionFactor::get_GDSgl, left_factor, right_factor);
   }
}

static void GetDeflectionMulDf(ForceEffectType forceEffect, IDistributionFactor* left_df, IDistributionFactor* right_df,
                               Float64* left_factor, Float64* right_factor)
{
   if (forceEffect==fetMz)
   {
      GetDF(left_df, right_df, &IDistributionFactor::get_GTMul, left_factor, right_factor);
   }
   else
   {
      GetDF(left_df, right_df, &IDistributionFactor::get_GDMul, left_factor, right_factor);
   }
}

void DeflectionDistributionFactorStrategy::GetOptimalDfs(PoiIDType poiID, BSTR Stage, ForceEffectType effect,
                                                                  DistributionFactorType distributionType,
                                                                  Float64* leftFactor, DistributionFactorType* usedLeftDistributionType,
                                                                  Float64* rightFactor, DistributionFactorType* usedRightDistributionType)
{
   CHRException hr;

   CComPtr<IDistributionFactor> left_df, right_df;
   hr = m_GetDistributionFactors->GetPOIDistributionFactor(poiID, Stage, &left_df, &right_df);

   if (left_df==NULL)
   {
      ATLASSERT(0);
      hr = E_FAIL; // this should never happen
   }

   switch (distributionType)
   {
   case dftSingleLane:
      {
         GetDeflectionSglDf(effect, left_df, right_df, leftFactor, rightFactor);
         *usedLeftDistributionType = dftSingleLane;
         *usedRightDistributionType = dftSingleLane;
         break;
      }
   case dftMultipleLane:
      {
         GetDeflectionMulDf(effect, left_df, right_df, leftFactor, rightFactor);
         *usedLeftDistributionType = dftMultipleLane;
         *usedRightDistributionType = dftMultipleLane;
         break;
      }
   case dftEnvelope:
      {
         Float64 left_sgl_factor, right_sgl_factor;
         GetDeflectionSglDf(effect, left_df, right_df, &left_sgl_factor, &right_sgl_factor);
         Float64 left_mul_factor, right_mul_factor;
         GetDeflectionMulDf(effect, left_df, right_df, &left_mul_factor, &right_mul_factor);

         // take max of single and multiple lane values
         if (right_sgl_factor> right_mul_factor)
         {
            *rightFactor = right_sgl_factor;
            *usedRightDistributionType = dftSingleLane;
         }
         else
         {
            *rightFactor = right_mul_factor;
            *usedRightDistributionType = dftMultipleLane;
         }

         if (left_sgl_factor> left_mul_factor)
         {
            *leftFactor = left_sgl_factor;
            *usedLeftDistributionType = dftSingleLane;
         }
         else
         {
            *leftFactor = left_mul_factor;
            *usedLeftDistributionType = dftMultipleLane;
         }
      }
      break;
   case dftFatigue:
      {
         GetDF(left_df, right_df, &IDistributionFactor::get_GFat, leftFactor, rightFactor);
         *usedLeftDistributionType = dftFatigue;
         *usedRightDistributionType = dftFatigue;
      }
      break;
   case dftPedestrian:
      {
         GetDF(left_df, right_df, &IDistributionFactor::get_GPedestrian, leftFactor, rightFactor);
         *usedLeftDistributionType = dftPedestrian;
         *usedRightDistributionType = dftPedestrian;
      }
      break;
   default:
      ATLASSERT(0);
      *leftFactor = 1.0;
      *rightFactor = 1.0;
      *usedLeftDistributionType = dftNone;
      *usedRightDistributionType = dftNone;
   }
}

// concurrent effects
static void GetConcDeflectionSglDf(IDistributionFactor* left_df, IDistributionFactor* right_df,
                                   Float64* leftFxFactor, Float64* leftFyFactor, Float64* leftMzFactor, 
                                   Float64* rightFxFactor, Float64* rightFyFactor, Float64* rightMzFactor)
{
   Float64 left_defdf, right_defdf;
   Float64 left_rotdf, right_rotdf;
   GetDF(left_df, right_df, &IDistributionFactor::get_GDSgl, &left_defdf, &right_defdf);
   GetDF(left_df, right_df, &IDistributionFactor::get_GTSgl, &left_rotdf, &right_rotdf);

   *leftFxFactor  = left_defdf;
   *leftFyFactor  = left_defdf;
   *leftMzFactor  = left_rotdf;
   *rightFxFactor = right_defdf;
   *rightFyFactor = right_defdf;
   *rightMzFactor = right_rotdf;
}

static void GetConcDeflectionMulDf(IDistributionFactor* left_df, IDistributionFactor* right_df,
                                   Float64* leftFxFactor, Float64* leftFyFactor, Float64* leftMzFactor, 
                                   Float64* rightFxFactor, Float64* rightFyFactor, Float64* rightMzFactor)
{
   Float64 left_defdf, right_defdf;
   Float64 left_rotdf, right_rotdf;
   GetDF(left_df, right_df, &IDistributionFactor::get_GDMul, &left_defdf, &right_defdf);
   GetDF(left_df, right_df, &IDistributionFactor::get_GTMul, &left_rotdf, &right_rotdf);

   *leftFxFactor  = left_defdf;
   *leftFyFactor  = left_defdf;
   *leftMzFactor  = left_rotdf;
   *rightFxFactor = right_defdf;
   *rightFyFactor = right_defdf;
   *rightMzFactor = right_rotdf;
}

void DeflectionDistributionFactorStrategy::GetConcurrentDfs(SupportIDType poiID, BSTR Stage, 
                                                       DistributionFactorType distributionType,
                                                       Float64* leftFxFactor, Float64* leftFyFactor, Float64* leftMzFactor, 
                                                       Float64* rightFxFactor, Float64* rightFyFactor, Float64* rightMzFactor)
{
   CHRException hr;
   CComPtr<IDistributionFactor> left_df, right_df;
   hr = m_GetDistributionFactors->GetPOIDistributionFactor(poiID, Stage, &left_df, &right_df);

   if (left_df==NULL)
   {
      ATLASSERT(0);
      hr = E_FAIL; // this should never happen
   }

   switch (distributionType)
   {
   case dftSingleLane:
      {
         GetConcDeflectionSglDf(left_df, right_df,
                           leftFxFactor, leftFyFactor, leftMzFactor, 
                           rightFxFactor, rightFyFactor, rightMzFactor);
      }
      break;
   case dftMultipleLane:
      {
         GetConcDeflectionMulDf(left_df, right_df,
                           leftFxFactor, leftFyFactor, leftMzFactor, 
                           rightFxFactor, rightFyFactor, rightMzFactor);
      }
      break;
   case dftEnvelope:
      {
         Float64 left_sgl_fx, left_sgl_fy, left_sgl_mz;
         Float64 right_sgl_fx, right_sgl_fy, right_sgl_mz;
         GetConcDeflectionSglDf(left_df, right_df,
                           &left_sgl_fx,  &left_sgl_fy,  &left_sgl_mz,
                           &right_sgl_fx, &right_sgl_fy, &right_sgl_mz);

         Float64 left_mul_fx, left_mul_fy, left_mul_mz;
         Float64 right_mul_fx, right_mul_fy, right_mul_mz;
         GetConcDeflectionMulDf(left_df, right_df,
                           &left_mul_fx,  &left_mul_fy,  &left_mul_mz,
                           &right_mul_fx, &right_mul_fy, &right_mul_mz);

         *leftFxFactor  = max(left_sgl_fx,  left_mul_fx);
         *leftFyFactor  = max(left_sgl_fy,  left_mul_fy);
         *leftMzFactor  = max(left_sgl_mz,  left_mul_mz);
         *rightFxFactor = max(right_sgl_fx, right_mul_fx);
         *rightFyFactor = max(right_sgl_fy, right_mul_fy);
         *rightMzFactor = max(right_sgl_mz, right_mul_mz);

      }
      break;
   case dftFatigue:
      {
         Float64 left_factor, right_factor;
         GetDF(left_df, right_df, &IDistributionFactor::get_GFat, &left_factor, &right_factor);
         *leftFxFactor  = left_factor;
         *leftFyFactor  = left_factor;
         *leftMzFactor  = left_factor;
         *rightFxFactor = right_factor;
         *rightFyFactor = right_factor;
         *rightMzFactor = right_factor;
      }
      break;
   case dftPedestrian:
      {
         Float64 left_factor, right_factor;
         GetDF(left_df, right_df, &IDistributionFactor::get_GPedestrian, &left_factor, &right_factor);
         *leftFxFactor  = left_factor;
         *leftFyFactor  = left_factor;
         *leftMzFactor  = left_factor;
         *rightFxFactor = right_factor;
         *rightFyFactor = right_factor;
         *rightMzFactor = right_factor;
      }
      break;
   default:
      ATLASSERT(0);
      *leftFxFactor  = 1.0;
      *leftFyFactor  = 1.0;
      *leftMzFactor  = 1.0;
      *rightFxFactor = 1.0;
      *rightFyFactor = 1.0;
      *rightMzFactor = 1.0;
   }
}

///////////////////////////////////////////////////////
// Reaction strategy
///////////////////////////////////////////////////////
// optimal effects
void ReactionDistributionFactorStrategy::GetOptimalDfs(SupportIDType sptID, BSTR Stage, ForceEffectType effect,
                                                       DistributionFactorType distributionType,
                                                       Float64* leftFactor, DistributionFactorType* usedLeftDistributionType,
                                                       Float64* rightFactor, DistributionFactorType* usedRightDistributionType)
{
   CHRException hr;

   CComPtr<IDistributionFactor> df;
   hr = m_GetDistributionFactors->GetSupportDistributionFactor(sptID, Stage, &df);

   if (df==NULL)
   {
      ATLASSERT(0);
      hr = E_FAIL; // this should never happen
   }

   // we know that left and right will be the same so get the left value and assigned it to the right below
   switch (distributionType)
   {
   case dftSingleLane:
      {
         GetDF1(df, &IDistributionFactor::get_GRSgl, leftFactor);
         *usedLeftDistributionType = dftSingleLane;
         break;
      }
   case dftMultipleLane:
      {
         GetDF1(df, &IDistributionFactor::get_GRMul, leftFactor);
         *usedLeftDistributionType = dftMultipleLane;
         break;
      }
   case dftEnvelope:
      {
         Float64 sgl_factor;
         GetDF1(df, &IDistributionFactor::get_GRSgl, &sgl_factor);
         Float64 mul_factor;
         GetDF1(df, &IDistributionFactor::get_GRMul, &mul_factor);

         // take max of single and multiple lane values
         if (sgl_factor> mul_factor)
         {
            *leftFactor = sgl_factor;
            *usedLeftDistributionType = dftSingleLane;
         }
         else
         {
            *leftFactor = mul_factor;
            *usedLeftDistributionType = dftMultipleLane;
         }
      }
      break;
   case dftFatigue:
      {
         GetDF1(df, &IDistributionFactor::get_GFat, leftFactor);
         *usedLeftDistributionType = dftFatigue;
      }
      break;
   case dftPedestrian:
      {
         GetDF1(df, &IDistributionFactor::get_GPedestrian, leftFactor);
         *usedLeftDistributionType = dftPedestrian;
      }
      break;
   default:
      ATLASSERT(0);
      *leftFactor = 1.0;
      *usedLeftDistributionType = dftNone;
   }

   *rightFactor = *leftFactor;
   *usedRightDistributionType = *usedLeftDistributionType;
}

// concurrent effects
static void GetConcReactionSglDf(IDistributionFactor* Df,
                                   Float64* leftFxFactor, Float64* leftFyFactor, Float64* leftMzFactor, 
                                   Float64* rightFxFactor, Float64* rightFyFactor, Float64* rightMzFactor)
{
   Float64 fac;
   GetDF1(Df, &IDistributionFactor::get_GRSgl, &fac);

   *leftFxFactor  = fac;
   *leftFyFactor  = fac;
   *leftMzFactor  = fac;
   *rightFxFactor = fac;
   *rightFyFactor = fac;
   *rightMzFactor = fac;
}

static void GetConcReactionMulDf(IDistributionFactor* Df,
                                   Float64* leftFxFactor, Float64* leftFyFactor, Float64* leftMzFactor, 
                                   Float64* rightFxFactor, Float64* rightFyFactor, Float64* rightMzFactor)
{
   Float64 fac;
   GetDF1(Df, &IDistributionFactor::get_GRMul, &fac);

   *leftFxFactor  = fac;
   *leftFyFactor  = fac;
   *leftMzFactor  = fac;
   *rightFxFactor = fac;
   *rightFyFactor = fac;
   *rightMzFactor = fac;
}

void ReactionDistributionFactorStrategy::GetConcurrentDfs(SupportIDType sptID, BSTR Stage,
                                                       DistributionFactorType distributionType,
                                                       Float64* leftFxFactor, Float64* leftFyFactor, Float64* leftMzFactor, 
                                                       Float64* rightFxFactor, Float64* rightFyFactor, Float64* rightMzFactor)
{
   CHRException hr;
   CComPtr<IDistributionFactor> df;
   hr = m_GetDistributionFactors->GetSupportDistributionFactor(sptID, Stage, &df);

   if (df==NULL)
   {
      ATLASSERT(0);
      hr = E_FAIL; // this should never happen
   }

   switch (distributionType)
   {
   case dftSingleLane:
      {
         GetConcReactionSglDf(df, 
                           leftFxFactor, leftFyFactor, leftMzFactor, 
                           rightFxFactor, rightFyFactor, rightMzFactor);
      }
      break;
   case dftMultipleLane:
      {
         GetConcReactionMulDf(df, 
                           leftFxFactor, leftFyFactor, leftMzFactor, 
                           rightFxFactor, rightFyFactor, rightMzFactor);
      }
      break;
   case dftEnvelope:
      {
         Float64 left_sgl_fx, left_sgl_fy, left_sgl_mz;
         Float64 right_sgl_fx, right_sgl_fy, right_sgl_mz;
         GetConcReactionSglDf(df,
                           &left_sgl_fx,  &left_sgl_fy,  &left_sgl_mz,
                           &right_sgl_fx, &right_sgl_fy, &right_sgl_mz);

         Float64 left_mul_fx, left_mul_fy, left_mul_mz;
         Float64 right_mul_fx, right_mul_fy, right_mul_mz;
         GetConcReactionMulDf(df, 
                           &left_mul_fx,  &left_mul_fy,  &left_mul_mz,
                           &right_mul_fx, &right_mul_fy, &right_mul_mz);

         *leftFxFactor  = max(left_sgl_fx,  left_mul_fx);
         *leftFyFactor  = max(left_sgl_fy,  left_mul_fy);
         *leftMzFactor  = max(left_sgl_mz,  left_mul_mz);
         *rightFxFactor = max(right_sgl_fx, right_mul_fx);
         *rightFyFactor = max(right_sgl_fy, right_mul_fy);
         *rightMzFactor = max(right_sgl_mz, right_mul_mz);
      }
      break;
   case dftFatigue:
      {
         Float64 factor;
         GetDF1(df, &IDistributionFactor::get_GFat, &factor);
         *leftFxFactor  = factor;
         *leftFyFactor  = factor;
         *leftMzFactor  = factor;
         *rightFxFactor = factor;
         *rightFyFactor = factor;
         *rightMzFactor = factor;
      }
      break;
   case dftPedestrian:
      {
         Float64 factor;
         GetDF1(df, &IDistributionFactor::get_GPedestrian, &factor);
         *leftFxFactor  = factor;
         *leftFyFactor  = factor;
         *leftMzFactor  = factor;
         *rightFxFactor = factor;
         *rightFyFactor = factor;
         *rightMzFactor = factor;
      }
      break;
   default:
      ATLASSERT(0);
      *leftFxFactor  = 1.0;
      *leftFyFactor  = 1.0;
      *leftMzFactor  = 1.0;
      *rightFxFactor = 1.0;
      *rightFyFactor = 1.0;
      *rightMzFactor = 1.0;
   }
}

///////////////////////////////////////////////////////
// SupportDeflection strategy
///////////////////////////////////////////////////////
// optimal effects
void SupportDeflectionDistributionFactorStrategy::GetOptimalDfs(SupportIDType sptID, BSTR Stage, ForceEffectType effect,
                                                       DistributionFactorType distributionType,
                                                       Float64* leftFactor, DistributionFactorType* usedLeftDistributionType,
                                                       Float64* rightFactor, DistributionFactorType* usedRightDistributionType)
{
   CHRException hr;

   CComPtr<IDistributionFactor> df;
   hr = m_GetDistributionFactors->GetSupportDistributionFactor(sptID, Stage, &df);

   if (df==NULL)
   {
      ATLASSERT(0);
      hr = E_FAIL; // this should never happen
   }

   // Same as for deflection factors
   switch (distributionType)
   {
   case dftSingleLane:
      {
         GetDeflectionSglDf(effect, df, NULL, leftFactor, rightFactor);
         *usedLeftDistributionType = dftSingleLane;
         *usedRightDistributionType = dftSingleLane;
         break;
      }
   case dftMultipleLane:
      {
         GetDeflectionMulDf(effect, df, NULL, leftFactor, rightFactor);
         *usedLeftDistributionType = dftMultipleLane;
         *usedRightDistributionType = dftMultipleLane;
         break;
      }
   case dftEnvelope:
      {
         Float64 left_sgl_factor, right_sgl_factor;
         GetDeflectionSglDf(effect, df, NULL, &left_sgl_factor, &right_sgl_factor);
         Float64 left_mul_factor, right_mul_factor;
         GetDeflectionMulDf(effect, df, NULL, &left_mul_factor, &right_mul_factor);

         // take max of single and multiple lane values
         if (right_sgl_factor> right_mul_factor)
         {
            *rightFactor = right_sgl_factor;
            *usedRightDistributionType = dftSingleLane;
         }
         else
         {
            *rightFactor = right_mul_factor;
            *usedRightDistributionType = dftMultipleLane;
         }

         if (left_sgl_factor> left_mul_factor)
         {
            *leftFactor = left_sgl_factor;
            *usedLeftDistributionType = dftSingleLane;
         }
         else
         {
            *leftFactor = left_mul_factor;
            *usedLeftDistributionType = dftMultipleLane;
         }
      }
      break;
   case dftFatigue:
      {
         GetDF(df, NULL, &IDistributionFactor::get_GFat, leftFactor, rightFactor);
         *usedLeftDistributionType = dftFatigue;
         *usedRightDistributionType = dftFatigue;
      }
      break;
   case dftPedestrian:
      {
         GetDF(df, NULL, &IDistributionFactor::get_GPedestrian, leftFactor, rightFactor);
         *usedLeftDistributionType = dftPedestrian;
         *usedRightDistributionType = dftPedestrian;
      }
      break;
   default:
      ATLASSERT(0);
      *leftFactor = 1.0;
      *rightFactor = 1.0;
      *usedLeftDistributionType = dftNone;
      *usedRightDistributionType = dftNone;
   }
}


void SupportDeflectionDistributionFactorStrategy::GetConcurrentDfs(SupportIDType sptID, BSTR Stage,
                                                       DistributionFactorType distributionType,
                                                       Float64* leftFxFactor, Float64* leftFyFactor, Float64* leftMzFactor, 
                                                       Float64* rightFxFactor, Float64* rightFyFactor, Float64* rightMzFactor)
{
   CHRException hr;
   CComPtr<IDistributionFactor> df;
   hr = m_GetDistributionFactors->GetSupportDistributionFactor(sptID, Stage, &df);

   if (df==NULL)
   {
      ATLASSERT(0);
      hr = E_FAIL; // this should never happen
   }

   // Same as for deflections
   switch (distributionType)
   {
   case dftSingleLane:
      {
         GetConcDeflectionSglDf(df, NULL,
                           leftFxFactor, leftFyFactor, leftMzFactor, 
                           rightFxFactor, rightFyFactor, rightMzFactor);
      }
      break;
   case dftMultipleLane:
      {
         GetConcDeflectionMulDf(df, NULL,
                           leftFxFactor, leftFyFactor, leftMzFactor, 
                           rightFxFactor, rightFyFactor, rightMzFactor);
      }
      break;
   case dftEnvelope:
      {
         Float64 left_sgl_fx, left_sgl_fy, left_sgl_mz;
         Float64 right_sgl_fx, right_sgl_fy, right_sgl_mz;
         GetConcDeflectionSglDf(df, NULL,
                           &left_sgl_fx,  &left_sgl_fy,  &left_sgl_mz,
                           &right_sgl_fx, &right_sgl_fy, &right_sgl_mz);

         Float64 left_mul_fx, left_mul_fy, left_mul_mz;
         Float64 right_mul_fx, right_mul_fy, right_mul_mz;
         GetConcDeflectionMulDf(df, NULL,
                           &left_mul_fx,  &left_mul_fy,  &left_mul_mz,
                           &right_mul_fx, &right_mul_fy, &right_mul_mz);

         *leftFxFactor  = max(left_sgl_fx,  left_mul_fx);
         *leftFyFactor  = max(left_sgl_fy,  left_mul_fy);
         *leftMzFactor  = max(left_sgl_mz,  left_mul_mz);
         *rightFxFactor = max(right_sgl_fx, right_mul_fx);
         *rightFyFactor = max(right_sgl_fy, right_mul_fy);
         *rightMzFactor = max(right_sgl_mz, right_mul_mz);

      }
      break;
   case dftFatigue:
      {
         Float64 left_factor, right_factor;
         GetDF(df, NULL, &IDistributionFactor::get_GFat, &left_factor, &right_factor);
         *leftFxFactor  = left_factor;
         *leftFyFactor  = left_factor;
         *leftMzFactor  = left_factor;
         *rightFxFactor = right_factor;
         *rightFyFactor = right_factor;
         *rightMzFactor = right_factor;
      }
      break;
   case dftPedestrian:
      {
         Float64 left_factor, right_factor;
         GetDF(df, NULL, &IDistributionFactor::get_GPedestrian, &left_factor, &right_factor);
         *leftFxFactor  = left_factor;
         *leftFyFactor  = left_factor;
         *leftMzFactor  = left_factor;
         *rightFxFactor = right_factor;
         *rightFyFactor = right_factor;
         *rightMzFactor = right_factor;
      }
      break;
   default:
      ATLASSERT(0);
      *leftFxFactor  = 1.0;
      *leftFyFactor  = 1.0;
      *leftMzFactor  = 1.0;
      *rightFxFactor = 1.0;
      *rightFyFactor = 1.0;
      *rightMzFactor = 1.0;
   }
}

