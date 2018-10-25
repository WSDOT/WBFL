///////////////////////////////////////////////////////////////////////
// LBAM Live Loader - Longitindal Bridge Analysis Model
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

#include "stdafx.h"
#include "Truck.h"
#include "MathEx.h"
#include "LiveLoaderUtils.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


void FixedTruck::Initialize(IVehicularLoad* pVehicularLoad, bool applyImpact, ILiveLoadConfiguration* config)
{
   CHRException hr;

   m_Axles.clear();
   m_ActiveAxles.clear();

   m_PivotAxleIndex = 0;

   CComPtr<IAxles> axles;
   hr = pVehicularLoad->get_Axles(&axles);

   AxleIndexType nAxles;
   hr = axles->get_Count(&nAxles);

   // nothing to do if there are no axles
   if (0 < nAxles)
   {
      m_Axles.reserve(nAxles);
      m_ActiveAxles.reserve(nAxles);

      // deal with variable axle spacing
      hr = pVehicularLoad->get_VariableAxle(&m_VariableAxleIndex);
      if (IsVariableAxle())
      {
         if ((nAxles-2) < m_VariableAxleIndex)
         {
            CComBSTR name;
            pVehicularLoad->get_Name(&name);
            CComBSTR msg = ::CreateErrorMsg1S(IDS_E_VAR_AXLE_OOR, name);
            THROW_LBAMLL_MSG(VAR_AXLE_OOR,msg);
         }
         else
         {
            hr = pVehicularLoad->get_VariableMaxSpacing(&m_MaxVariableAxleSpacing);

            // get initial axle spacing if placement
            if (config != NULL)
            {
               hr = config->get_VariableSpacing(&m_VariableAxleSpacing);
            }
         }
      }

      // See if we are picking up any axles
      bool is_axle_config = false;
      CComPtr<IIndexArray> axle_config;
      if (config != NULL)
      {
         hr = config->get_AxleConfig(&axle_config);

         CollectionIndexType axle_config_size;
         hr = axle_config->get_Count(&axle_config_size);
         if (0 < axle_config_size)
         {
            is_axle_config = true;
         }
      }

      // create axle array with factored axle weights
      Float64 truck_factor;
      hr = pVehicularLoad->get_TruckFactor(&truck_factor);
      ATLASSERT(0.0 <= truck_factor);

      Float64 truck_im = 1.0;
      if (applyImpact)
      {
         hr = pVehicularLoad->get_IMTruck(&truck_im);
         //ATLASSERT(0.0 < truck_im);

         truck_factor *= truck_im;
      }

      for (AxleIndexType axleIdx = 0; axleIdx < nAxles; axleIdx++)
      {
         CComPtr<IAxle> axle;
         hr = axles->get_Item(axleIdx, &axle);

         Float64 weight;
         hr = axle->get_Weight(&weight);

         weight *= truck_factor;

         Float64 spacing;
         hr = axle->get_Spacing(&spacing);

         // Add our axle
         m_Axles.push_back( FtAxle(spacing, weight) );

         // Apply axle unless it's in current configuration
         m_ActiveAxles.push_back(AxleOn);

         if (is_axle_config)
         {
            CollectionIndexType fi;
            HRESULT hResult = axle_config->Find(axleIdx, &fi);
            if ( SUCCEEDED(hResult) )
            {
               m_ActiveAxles[axleIdx] = AxleOff;
            }
         }

         if (axleIdx == m_VariableAxleIndex)
         {
            // we are at variable axle
            // set initial spacing to min if not specified by placement
            m_MinVariableAxleSpacing = spacing;
            if (config == NULL)
            {
               m_VariableAxleSpacing =  m_MinVariableAxleSpacing;
            }

            // error check
            if (m_VariableAxleSpacing    < m_MinVariableAxleSpacing || 
                m_MaxVariableAxleSpacing < m_VariableAxleSpacing )
            {
               CComBSTR name;
               pVehicularLoad->get_Name(&name);
               CComBSTR msg = ::CreateErrorMsg1S(IDS_E_VAR_SPACING_OOR, name);
               THROW_LBAMLL_MSG(VAR_AXLE_OOR,msg);
            }
         }
      }

      // deal with factoring axle weights and truck direction
      m_TruckDirection = ltdForward;
      if (config != NULL)
      {
         hr = config->get_TruckDirection(&m_TruckDirection);
         hr = config->get_PivotAxleIndex(&m_PivotAxleIndex);
      }

      // Compute axle locations
      ComputeAxleLocations();
   }

   LiveLoadApplicabilityType applicability;
   pVehicularLoad->get_Applicability(&applicability);
   switch( applicability )
   {
   case llaEntireStructure:
      m_bNegMomentsAndReactions = false;
      break;

   case llaContraflexure:
   case llaNegMomentAndInteriorPierReaction:
      m_bNegMomentsAndReactions = true;
      break;

   default:
      ATLASSERT(false); // is there a new applicability type?
      m_bNegMomentsAndReactions = false;
   }
}

void FixedTruck::ComputeAxleLocations()
{
   m_Front = m_Rear = 0.0;

   long sign = (m_TruckDirection == ltdForward) ? -1 : 1;

   Float64 axleLocation = 0.0;
   AxleIndexType axleIndex = 0;

   // precompute iterator bounds for speed
   AxleIterator axleEnd( m_Axles.end() );
   AxleIterator axleIter(m_Axles.begin());

   for (; axleIter != axleEnd; axleIter++)
   {
      FtAxle& axle = *axleIter;
      axle.m_Location = axleLocation;

      Float64 spacing;
      if ( m_VariableAxleIndex == axleIndex)
      {
         spacing = m_VariableAxleSpacing;
      }
      else
      {
         spacing = axle.m_OriginalSpacing;
      }

      axleLocation += sign * spacing;

      axleIndex++;
   }

   if (!m_Axles.empty())
   {
      // shift all the axles based on the pivot axle offset
      FtAxle& pivotAxle = m_Axles[m_PivotAxleIndex];
      Float64 pivotAxleOffset = pivotAxle.m_Location;

      AxleIterator axleIter2(m_Axles.begin());
      for (; axleIter2 != axleEnd; axleIter2++)
      {
         FtAxle& axle = *axleIter2;
         axle.m_Location -= pivotAxleOffset;
      }

      // cache off truck bounds
      if (m_TruckDirection==ltdForward)
      {
         m_Front = m_Axles.front().m_Location;
         m_Rear  = m_Axles.back().m_Location;
      }
      else
      {
         m_Front = m_Axles.back().m_Location;
         m_Rear  = m_Axles.front().m_Location;
      }
   }
}

// compute response for one influence line
void FixedTruck::EvaluatePrimaryInfl(Float64 position, InfluenceSideType side, IInfluenceLine* influence,
                                     std::vector<AxleState>* appliedAxles,
                                     VARIANT_BOOL* isDualValued, Float64* leftValue, Float64* rightValue)
{
   CHRException hr;
   Float64 left_response=0.0;
   Float64 right_response=0.0;
   *isDualValued = VARIANT_FALSE;

   if ( appliedAxles && !appliedAxles->empty() ) // According to VTune, checking for empty before clearing is faster
      appliedAxles->clear();

   AxleIndexType axleIndex = 0;
   // loop over axles and get response. Only apply active axles
   AxleIterator axleEnd(m_Axles.end());
   AxleIterator iter(m_Axles.begin());
   for (; iter != axleEnd; iter++)
   {
      FtAxle axle = *iter;
      if (m_ActiveAxles[axleIndex]==AxleOn)
      {
         Float64 axle_loc = axle.m_Location + position;
         Float64 axle_wgt = axle.m_Weight;

         Float64 left_inf_resp, right_inf_resp;
         VARIANT_BOOL is_dual;

         hr = influence->Evaluate(axle_loc, side, &is_dual, &left_inf_resp, &right_inf_resp);
         if (is_dual == VARIANT_TRUE)
         {  
            // dual valued - if one is, the entire response is
            *isDualValued = VARIANT_TRUE;
            left_response  += left_inf_resp * axle_wgt;
            right_response += right_inf_resp * axle_wgt;

            if (appliedAxles != NULL)
               appliedAxles->push_back(AxleOn);
         }
         else
         {
            // not dual valued - check to see if response is non-zero
            Float64 response = left_inf_resp * axle_wgt;
            if (response != 0.0)
            {
               left_response  += response;
               right_response += response;
               if (appliedAxles!=NULL)
                  appliedAxles->push_back(AxleOn);
            }
            else
            {
               if (appliedAxles!=NULL)
                  appliedAxles->push_back(AxleOff);
            }
         }
      }
      else
      {
         if (appliedAxles!=NULL)
            appliedAxles->push_back(AxleOff);
      }

      axleIndex++;
   }

   ATLASSERT(appliedAxles!=NULL ? appliedAxles->size() ==  m_Axles.size() : true );

   *leftValue  = left_response;
   *rightValue = right_response;

}

void FixedTruck::EvaluatePrimary(Float64 position, InfluenceSideType side, Float64 flipFactor, 
                                 IInfluenceLine* lftInfluence, IInfluenceLine* rgtInfluence, 
                                 std::vector<AxleState>* lftAppliedAxles, std::vector<AxleState>* rgtAppliedAxles,
                                 VARIANT_BOOL* isDualValued, Float64* leftValue, Float64* rightValue)
{
   CHRException hr;
   Float64 left_response=0.0;
   Float64 right_response=0.0;
   *isDualValued = VARIANT_FALSE;

   if ( lftInfluence )
   {
      Float64 dummy;
      EvaluatePrimaryInfl(position, side, lftInfluence, lftAppliedAxles, isDualValued, leftValue, &dummy);
   }

   if ( rgtInfluence )
   {
      Float64 dummy;
      InfluenceSideType loc_side = side;
      if ( side != ilsBoth && flipFactor == -1 )
      {
         loc_side = (side == ilsPositive ? ilsNegative : ilsPositive);
      }
      EvaluatePrimaryInfl(position, loc_side, rgtInfluence, rgtAppliedAxles, isDualValued, &dummy, rightValue);
   }

   if ( !IsEqual(*leftValue,-(*rightValue)) )
      *isDualValued = VARIANT_TRUE;
}

AxleIndexType FixedTruck::HeaviestCentralAxle()
{
   AxleIterator begin( m_Axles.begin() + 1 );
   AxleIterator end(   m_Axles.end()   - 1 );

   // find the size of the range of central axles
   AxleIndexType nAxles = end - begin;

   // place two iterators at the center of this range
   AxleIterator fwdIter( begin + (nAxles-1)/2 );
   AxleIterator bkIter(  end   - (nAxles-1)/2 );

   // if there is an odd number of axles, then the center most might get missed
   // fix that problem
   if ( 2 < bkIter - fwdIter )
   {
      fwdIter++;
      bkIter--;
   }

   // working out from the center, find the heaviest axle nearest the center
   Float64 maxWeight = 0;
   AxleIterator heaviestIter( fwdIter );
   while ( fwdIter != end && bkIter != begin )
   {
      FtAxle fwdAxle( *fwdIter );
      FtAxle bkAxle ( *bkIter  );

      if ( maxWeight < fwdAxle.m_Weight )
      {
         maxWeight = fwdAxle.m_Weight;
         heaviestIter = fwdIter;
      }

      if ( maxWeight < bkAxle.m_Weight )
      {
         maxWeight = bkAxle.m_Weight;
         heaviestIter = bkIter;
      }

      fwdIter++;
      bkIter--;
   }

   AxleIndexType idx = heaviestIter - m_Axles.begin();
   return idx;
}

TruckDirectionType FixedTruck::GetTruckDirection()
{
   return m_TruckDirection;
}

AxleIndexType FixedTruck::GetPivotAxleIndex()
{
   return m_PivotAxleIndex;
}

void FixedTruck::SetTruckDirection(TruckDirectionType direction,AxleIndexType pivotAxleIndex)
{
   if (direction != m_TruckDirection || m_PivotAxleIndex != pivotAxleIndex)
   {
      m_TruckDirection = direction;
      m_PivotAxleIndex = pivotAxleIndex;

      ComputeAxleLocations();
   }
}

Float64 FixedTruck::GetVariableAxleSpacing()
{
   ATLASSERT(IsVariableAxle()); // shouldn't be asking if not variable axle
   return m_VariableAxleSpacing;
}

void FixedTruck::SetVariableAxleSpacing(Float64 spacing)
{
   if (!IsVariableAxle())
   {
      ATLASSERT(0); // shouldn't be asking if not variable axle
      return;
   }

   Float64 tol = 1.0e-06;
   if (spacing<m_MinVariableAxleSpacing-tol || spacing>m_MaxVariableAxleSpacing+tol)
   {
      ATLASSERT(0); // shouldn't be asking if not variable axle
      return;
   }

   if (spacing != m_VariableAxleSpacing)
   {
      m_VariableAxleSpacing = spacing;

      ComputeAxleLocations();
   }
}

bool FixedTruck::IsVariableAxle()
{
   return (m_VariableAxleIndex == FIXED_AXLE_TRUCK) ? false : true;
}

AxleIndexType FixedTruck::GetVariableAxleIndex()
{
   return m_VariableAxleIndex;
}

Float64 FixedTruck::GetMinVariableAxleSpacing()
{
   if (!IsVariableAxle())
   {
      ATLASSERT(0); // shouldn't be asking if not variable axle
      return 0;
   }
   else
      return m_MinVariableAxleSpacing;
}

Float64 FixedTruck::GetMaxVariableAxleSpacing()
{
   if (!IsVariableAxle())
   {
      ATLASSERT(0); // shouldn't be asking if not variable axle
      return 0;
   }
   else
      return m_MaxVariableAxleSpacing;
}

AxleIndexType FixedTruck::GetNumAxles()
{
   return m_Axles.size();
}

Float64 FixedTruck::GetAxleLocation(AxleIndexType idx)
{
   ATLASSERT(idx>=0 && idx<GetNumAxles());

   return m_Axles[idx].m_Location; // location of axle, measured from the pivot axle
}

Float64 FixedTruck::GetAxlePosition(AxleIndexType idx,Float64 truckPosition)
{
   return GetAxleLocation(idx) + truckPosition;
}

Float64 FixedTruck::MinAxleSpacing()
{
   Float64 minSpacing = Float64_Max;

   AxleIterator axleEnd( m_Axles.end() );
   AxleIterator iter(m_Axles.begin());
   for (; iter != axleEnd-1; iter++ )
   {
      FtAxle axle( *iter );
      minSpacing = _cpp_min(minSpacing,axle.m_OriginalSpacing);
   }

   return minSpacing;
}

Float64 FixedTruck::MaxAxleSpacing()
{
   Float64 maxSpacing = 0;

   AxleIterator axleEnd( m_Axles.end() );
   AxleIterator iter( m_Axles.begin() );
   for (; iter != axleEnd; iter++ )
   {
      FtAxle axle( *iter );
      maxSpacing = _cpp_max(maxSpacing,axle.m_OriginalSpacing);
   }

   return maxSpacing;
}

Float64 FixedTruck::CenterOfGravity()
{
   // center of gravity of truck load, measured from the pivot axle

   Float64 Sum_W_loc = 0;
   Float64 Sum_W  = 0;

   AxleIterator axleEnd( m_Axles.end() );
   AxleIterator iter( m_Axles.begin() );
   for (; iter != axleEnd; iter++ )
   {
      FtAxle axle( *iter );
      Sum_W_loc += (axle.m_Location)*(axle.m_Weight);
      Sum_W     += axle.m_Weight;
   }

   Float64 cg = Sum_W_loc/Sum_W;

   return cg;
}

bool FixedTruck::NegMomentsAndReactions()
{
   return m_bNegMomentsAndReactions;
}

#if defined _DEBUG
void FixedTruck::DumpAxles(Float64 position)
{
   AxleIndexType axleIdx = 0;
   // loop over all axle
   for (AxleIterator iter = m_Axles.begin(); iter != m_Axles.end(); iter++)
   {
      FtAxle axle = *iter;
      if (m_ActiveAxles[axleIdx]==AxleOn)
      {
         Float64 axle_loc = axle.m_Location + position;
         Float64 axle_wgt = axle.m_Weight;

         if ( axleIdx == m_PivotAxleIndex )
         {
            WATCH("P = " << axle_wgt << " X = " << axle_loc << " *");
         }
         else
         {
            WATCH("P = " << axle_wgt << " X = " << axle_loc);
         }

         if ( axleIdx == m_VariableAxleIndex )
         {
            WATCH("   S = " << m_VariableAxleSpacing << " v");
         }
         else
         {
            WATCH("   S = " << iter->m_OriginalSpacing);
         }
      }
      axleIdx++;
   }
   WATCH("");
}
#endif
