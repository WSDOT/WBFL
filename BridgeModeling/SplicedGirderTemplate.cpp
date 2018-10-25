///////////////////////////////////////////////////////////////////////
// BMF - Bridge Modeling Framework - Product modeling of bridge structures
// Copyright (C) 1999  Washington State Department of Transportation
//                     Bridge and Structures Office
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

#include <BridgeModeling\BridgeModelingLib.h>

/****************************************************************************
CLASS
   bmfSplicedGirderTemplate
****************************************************************************/

#include <BridgeModeling\SplicedGirderTemplate.h>
#include <BridgeModeling\SplicedGirder.h>
#include <BridgeModeling\GirderProfile.h>
#include <GeomModel\PrecastBeam.h>
#include <MathEx.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

////////////////////////// PUBLIC     ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
bmfSplicedGirderTemplate::bmfSplicedGirderTemplate(const std::string& name,
                                                   const bmfGirderProfile* pProfile,
                                                   Uint16 nSplices,
                                                   Float64* segmentLength,
                                                   Float64* closurePourSize,
                                                   const matConcreteEx* pConc,
                                                   const matPsStrand* pStrand,
                                                   const matPsStrand* pPTStrand,
                                                   const bmfStrandPattern* strPtrn,
                                                   const bmfStrandPattern& tmpPtrn,
                                                   const bmfLrLayout*      lrLayout,
                                                   const bmfDucts& ducts):
bmfGirderTemplate( name, pProfile ),
m_pConc( pConc ),
m_pStrand( pStrand ),
m_pPTStrand( pPTStrand )
{
   m_nSplices = nSplices;
   for ( Uint16 splice = 0; splice < nSplices; splice++ )
   {
      m_ClosurePourSize[splice]  = closurePourSize[splice];
      m_SegmentLength[splice]    = segmentLength[splice];
   }

   for ( SegmentIndexType segment = 0; segment < nSplices+1; segment++ )
   {
      m_StrandPattern[segment]   = strPtrn[segment];
      m_LrLayout[segment]        = lrLayout[segment];
   }

   m_TempPattern = tmpPtrn;

   m_Ducts = ducts;
}

bmfSplicedGirderTemplate::bmfSplicedGirderTemplate(const bmfSplicedGirderTemplate& rOther) :
bmfGirderTemplate( rOther )
{
   MakeCopy( rOther );
}

bmfSplicedGirderTemplate::~bmfSplicedGirderTemplate()
{
}

//======================== OPERATORS  =======================================
bmfSplicedGirderTemplate& bmfSplicedGirderTemplate::operator= (const bmfSplicedGirderTemplate& rOther)
{
   if( this != &rOther )
   {
      MakeAssignment(rOther);
   }

   return *this;
}

//======================== OPERATIONS =======================================
SegmentIndexType bmfSplicedGirderTemplate::GetNumSegments() const
{
   return GetNumSplices() + 1;
}

Uint16 bmfSplicedGirderTemplate::GetNumSplices() const
{
   return m_nSplices;
}

bmfGirder* bmfSplicedGirderTemplate::CreateGirder()
{
   return new bmfSplicedGirder( this );
}

bmfGirderTemplate* bmfSplicedGirderTemplate::CreateClone() const
{
   return new bmfSplicedGirderTemplate( *this );
}

void bmfSplicedGirderTemplate::SetStrandPattern( SegmentIndexType segment, const bmfStrandPattern& rPattern )
{
   m_StrandPattern[segment] = rPattern;
}

const bmfStrandPattern& bmfSplicedGirderTemplate::GetStrandPattern(SegmentIndexType segment) const
{
   return m_StrandPattern[segment];
}

bmfStrandPattern& bmfSplicedGirderTemplate::GetStrandPattern(SegmentIndexType segment)
{
   return m_StrandPattern[segment];
}

void bmfSplicedGirderTemplate::SetTemporaryStrandPattern( const bmfStrandPattern& rPattern )
{
   m_TempPattern = rPattern;
}

const bmfStrandPattern& bmfSplicedGirderTemplate::GetTemporaryStrandPattern() const
{
   return m_TempPattern;
}

bmfStrandPattern& bmfSplicedGirderTemplate::GetTemporaryStrandPattern()
{
   return m_TempPattern;
}

const bmfLrLayout& bmfSplicedGirderTemplate::GetLrLayout(SegmentIndexType segment) const
{
   return m_LrLayout[segment];
}

void bmfSplicedGirderTemplate::SetLrLayout(SegmentIndexType segment,const bmfLrLayout& rLayout)
{
   m_LrLayout[segment] = rLayout;
}

gmIPrecastBeam* bmfSplicedGirderTemplate::CreateShape(Float64 distFromStart,Float64 length) const
{
   const bmfGirderProfile* pProfile = GetProfile();
   gmIShape* pShape = pProfile->CreateShape(distFromStart,length);
   gmIPrecastBeam* pBeam = dynamic_cast<gmIPrecastBeam*>(pShape);
   CHECK(pBeam != NULL);
   return pBeam;
}

void bmfSplicedGirderTemplate::SetConcrete(const matConcreteEx* pConc)
{
   m_pConc = pConc;
}

const matConcreteEx* bmfSplicedGirderTemplate::GetConcrete() const
{
   return m_pConc;
}

void bmfSplicedGirderTemplate::SetStrand(const matPsStrand* pStrand)
{
   m_pStrand = pStrand;
}

const matPsStrand* bmfSplicedGirderTemplate::GetStrand() const
{
   return m_pStrand;
}

void bmfSplicedGirderTemplate::SetPTStrand(const matPsStrand* pStrand)
{
   m_pPTStrand = pStrand;
}

const matPsStrand* bmfSplicedGirderTemplate::GetPTStrand() const
{
   return m_pPTStrand;
}

void bmfSplicedGirderTemplate::SetDuct(const bmfDucts& ducts)
{
   m_Ducts = ducts;
}

const bmfDucts& bmfSplicedGirderTemplate::GetDucts() const
{
   return m_Ducts;
}

void bmfSplicedGirderTemplate::SetClosurePourSize(Uint16 splice,Float64 size)
{
   m_ClosurePourSize[splice] = size;
}

Float64 bmfSplicedGirderTemplate::GetClosurePourSize(Uint16 splice) const
{
   return m_ClosurePourSize[splice];
}

void bmfSplicedGirderTemplate::SetSegmentLength(SegmentIndexType segment,Float64 length)
{
   m_SegmentLength[segment] = length;
}

Float64 bmfSplicedGirderTemplate::GetSegmentLength(SegmentIndexType segment) const
{
   return m_SegmentLength[segment];
}

//======================== ACCESS     =======================================
//======================== INQUIRY    =======================================

////////////////////////// PROTECTED  ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
//======================== OPERATORS  =======================================
//======================== OPERATIONS =======================================
void bmfSplicedGirderTemplate::MakeCopy(const bmfSplicedGirderTemplate& rOther)
{
   m_nSplices = rOther.m_nSplices;
   for (SegmentIndexType segment = 0; segment < rOther.m_nSplices; segment++)
   {
      m_StrandPattern[segment]   = rOther.m_StrandPattern[segment];
      m_LrLayout[segment]        = rOther.m_LrLayout[segment];
   }

   for (Uint32 splice = 0; splice < m_nSplices; splice++ )
   {
      m_ClosurePourSize[splice] = rOther.m_ClosurePourSize[splice];
      m_SegmentLength[splice]   = rOther.m_SegmentLength[splice];
   }

   m_Ducts             = rOther.m_Ducts;
   m_pStrand           = rOther.m_pStrand;
   m_pPTStrand         = rOther.m_pPTStrand;
   m_TempPattern       = rOther.m_TempPattern;
}

void bmfSplicedGirderTemplate::MakeAssignment(const bmfSplicedGirderTemplate& rOther)
{
   bmfGirderTemplate::MakeAssignment( rOther );
   MakeCopy( rOther );
}

//======================== ACCESS     =======================================
//======================== INQUIRY    =======================================

////////////////////////// PRIVATE    ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
//======================== OPERATORS  =======================================
//======================== OPERATIONS =======================================
//======================== ACCESS     =======================================
//======================== INQUERY    =======================================


//======================== DEBUG      =======================================
#if defined _DEBUG
bool bmfSplicedGirderTemplate::AssertValid() const
{
   if ( !m_StrandPattern[0].AssertValid() )
      return false;

   if ( !m_StrandPattern[1].AssertValid() )
      return false;

   if ( !m_StrandPattern[2].AssertValid() )
      return false;

   if ( !m_TempPattern.AssertValid() )
      return false;

   return true;
}

void bmfSplicedGirderTemplate::Dump(dbgDumpContext& os) const
{
   ASSERTVALID;

   os << "Dump for bmfSplicedGirderTemplate" << endl;

   os << "Strand Pattern - Left" << endl;
   m_StrandPattern[0].Dump( os );
   os << endl;
   os << "Strand Pattern - Middle" << endl;
   m_StrandPattern[1].Dump( os );
   os << endl;
   os << "Strand Pattern - Right" << endl;
   m_StrandPattern[2].Dump( os );
   os << endl;

   os << "LrLayout - Left" << endl;
   m_LrLayout[0].Dump( os );
   os << endl;
   os << "LrLayout - Middle" << endl;
   m_LrLayout[1].Dump( os );
   os << endl;
   os << "LrLayout - Right" << endl;
   m_LrLayout[2].Dump( os );
   os << endl;
}
#endif // _DEBUG

#if defined _UNITTEST
bool bmfSplicedGirderTemplate::TestMe(dbgLog& rlog)
{
   TESTME_PROLOGUE("bmfSplicedGirderTemplate");

   bmfBundlePattern ptrn;

   TEST_NOT_IMPLEMENTED("bmfSplicedGirderTemplate");

   TESTME_EPILOG("bmfSplicedGirderTemplate");
}
#endif // _UNITTEST
