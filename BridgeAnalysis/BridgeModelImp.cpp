///////////////////////////////////////////////////////////////////////
// BAM - Bridge Analysis Model, Analytical modeling of bridge structures
// Copyright © 1999-2012  Washington State Department of Transportation
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

#include <BridgeAnalysis\BridgeAnalysisLib.h>

#include <BridgeAnalysis\BridgeModelImp.h>
#include <BridgeAnalysis\LoadFactoryImp.h>
#include <MathEx.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

bamBridgeModelImp::bamBridgeModelImp() :
bamBridgeModel()
{
}

bamBridgeModelImp::~bamBridgeModelImp()
{
   FlushBeams();
}

bamBridgeModel* bamBridgeModelImp::DoClone() const
{
   return new bamBridgeModelImp;
}

void bamBridgeModelImp::DeepCopy(bamBridgeModel* pModel) const
{
   bamBridgeModel::DeepCopy(pModel);
}

bamLoadFactory* bamBridgeModelImp::CreateLoadFactory()
{
   return new bamLoadFactoryImp(this);
}

void bamBridgeModelImp::AddBeam(rkRoarkBeam* beam)
{
	m_Beams.push_back( boost::shared_ptr<rkRoarkBeam>(beam));
}

void bamBridgeModelImp::AddReaction(Float64 P,PierIDType supportId)
{
   m_Reactions.push_back( std::make_pair(supportId,P) );
}

void bamBridgeModelImp::FlushBeams()
{
   m_Beams.clear();
}

void bamBridgeModelImp::FlushReactions()
{
   m_Reactions.clear();
}

void bamBridgeModelImp::DoCollectResults(PoiIDType poiId,bamSectionResults& results)
{
   // Extracts results from the analysis model that is actually implemented.

   // Initialize the results to zero
   results *= 0.;

   BeamIterator begin = m_Beams.begin();
   BeamIterator end   = m_Beams.end();
   while ( begin != end )
   {
      sysSectionValue dx, dy, rz, fx, fy, mz;
      boost::shared_ptr<rkRoarkBeam>& beam = *begin++;
      SpanIDType spanId;
      Float64 distFromStart;
      Float64 location;

      GetPointOfInterest( poiId, spanId, distFromStart, location);

      fx = 0.0; // not supported by Roark beams
      fy = beam->ComputeShear(location);
      mz = beam->ComputeMoment(location);
      dx = 0.0; // not supported by Roark beams
      dy = beam->ComputeDeflection(location);
      rz = beam->ComputeRotation(location);

      // Sum up the contributions from each beam
      results.Fx() += fx;
      results.Fy() += fy;
      results.Mz() += mz;
      results.Dx() += dx;
      results.Dy() += dy;
      results.Rz() += rz;
   }
}

void bamBridgeModelImp::DoCollectReactions(PierIDType supportId,bamReaction& reaction)
{
   // Get the one and only span and determine if this support
   // is at the start or end end of the span element.
   bool is_at_start;
   SpanIDType span_element_id;
   SpanIDType* ptr = &span_element_id;

   EnumSpanElements(&ptr);

   bamSpanElement* pSpanElement = GetSpanElement(span_element_id);
   if ( supportId == pSpanElement->StartSupport().GetID() )
      is_at_start = true;
   else
      is_at_start = false;

   reaction *= 0.;

   BeamIterator begin = m_Beams.begin();
   BeamIterator end   = m_Beams.end();
   while ( begin != end )
   {
      Float64 Ra,Rb;
      Float64 Ma,Mb;
      Float64 rota, rotb;
      boost::shared_ptr<rkRoarkBeam>& beam = *begin++;

      beam->GetReactions(&Ra,&Rb);
      beam->GetMoments(&Ma,&Mb);
      beam->GetRotations( &rota, &rotb );

      reaction.Fy() += (is_at_start) ? Ra : Rb;
      reaction.Mz() += (is_at_start) ? Ma : Mb;
      reaction.Rz() += (is_at_start) ? rota : rotb;
   }

   ReactionContainer::iterator i;
   for ( i = m_Reactions.begin(); i != m_Reactions.end(); i++ )
   {
      std::pair<SupportIDType,Float64> r = *i;
      if ( (r.first == pSpanElement->StartSupport().GetID() && is_at_start ) ||
           (r.first == pSpanElement->EndSupport().GetID() && !is_at_start) )
      {
         // - sign to convert downward load to an upwards reaction
         reaction.Fy() -= r.second;
      }
   }
}
