///////////////////////////////////////////////////////////////////////
// BMF - Bridge Modeling Framework - Product modeling of bridge structures
// Copyright © 1999-2022  Washington State Department of Transportation
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

#include <BridgeModeling\BridgeModelingLib.h>

/****************************************************************************
CLASS
   bmfBundlePattern
****************************************************************************/

#include <BridgeModeling\BundlePattern.h>
#include <MathEx.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

////////////////////////// PUBLIC     ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
bmfBundlePattern::bmfBundlePattern()
{
}

bmfBundlePattern::bmfBundlePattern(const bmfBundlePattern& rOther)
{
   MakeCopy(rOther);
}

bmfBundlePattern::~bmfBundlePattern()
{
}

//======================== OPERATORS  =======================================
bmfBundlePattern& bmfBundlePattern::operator= (const bmfBundlePattern& rOther)
{
   if( this != &rOther )
   {
      MakeAssignment(rOther);
   }

   return *this;
}

//======================== OPERATIONS =======================================
void bmfBundlePattern::AddBundle(Float64 offset,StrandIndexType maxStrands)
{
   PRECONDITION( offset > 0 );

   BundleData bd;
   bd.Offset = offset;
   bd.MaxStrands = maxStrands;
   m_Bundles.push_back( bd );

   ASSERTVALID;
}

CollectionIndexType bmfBundlePattern::GetBundleCount() const
{
   return m_Bundles.size();
}

Float64 bmfBundlePattern::GetBundleOffset(CollectionIndexType idx) const
{
   PRECONDITION( idx < m_Bundles.size() );

   const BundleData& bd = m_Bundles[idx];
   return bd.Offset;
}

Float64 bmfBundlePattern::GetBundleHeight(CollectionIndexType idx) const
{
   PRECONDITION( idx < m_Bundles.size() );

   Float64 height = 0.0;
   for ( CollectionIndexType i = 0; i < (idx+1); i++ )
   {
      const BundleData& bd = m_Bundles[i];
      height += bd.Offset;
   }

   return height;
}

StrandIndexType bmfBundlePattern::GetMaxStrandCount(CollectionIndexType idx) const
{
   PRECONDITION( idx < m_Bundles.size() );

   const BundleData& bd = m_Bundles[idx];
   return bd.MaxStrands;
}

void bmfBundlePattern::RemoveBundle(CollectionIndexType idx)
{
   PRECONDITION( idx < m_Bundles.size() );

   m_Bundles.erase( m_Bundles.begin() + idx );

   ASSERTVALID;
}

void bmfBundlePattern::RemoveAllBundles()
{
   m_Bundles.clear();

   ASSERTVALID;
}

gpPoint2d bmfBundlePattern::GetCenterOfGravity(StrandIndexType nStrands) const
{
   Float64 height  = 0.0;
   Float64 sum_nsh = 0.0; // sum of #strands used in the i_th bundle * height of the bundle
   StrandIndexType cStrandsRemaining = nStrands;

   #if defined _DEBUG
   // We are going to do a little extra work in the debug version just
   // to make sure this method is correct.
   StrandIndexType cSumMaxStrands = 0;
   #endif // _DEBUG

   std::vector<BundleData>::const_iterator iter;
   for ( iter = m_Bundles.begin(); cStrandsRemaining > 0 && iter < m_Bundles.end(); iter++ )
   {
      const BundleData& bd = *iter;
      StrandIndexType cStrandsUsedInThisBundle = _cpp_min( bd.MaxStrands, cStrandsRemaining );

      height += bd.Offset;
      sum_nsh += height * cStrandsUsedInThisBundle;

      cStrandsRemaining -= cStrandsUsedInThisBundle;

      #if defined _DEBUG
      cSumMaxStrands += bd.MaxStrands;
      #endif // _DEBUG
   }

   #if defined _DEBUG
   if ( cStrandsRemaining > 0 )
   {
      CHECK( cSumMaxStrands < nStrands );
   }
   else
   {
      CHECK( nStrands <= cSumMaxStrands );
   }
   #endif // _DEBUG

   if ( cStrandsRemaining > 0 )
   {
      // All the specified max # of strands were used up, some strands remain.
      // Force these into the last bundle.
      sum_nsh += height * cStrandsRemaining;
   }

   gpPoint2d cg;
   cg.X() = 0.0; // always on centerline of girder

   if ( nStrands == 0 )
      cg.Y() = GetBundleHeight(0);
   else
      cg.Y() = sum_nsh / nStrands;

   return cg;
}

CollectionIndexType bmfBundlePattern::GetBundleIdx(StrandIndexType iStrand) const
{
   StrandIndexType cStrands = 0;
   for ( StrandIndexType i = 0; i < GetBundleCount(); i++ )
   {
      if ( cStrands <= iStrand && iStrand < (cStrands+GetMaxStrandCount(i)) )
         return i;

      cStrands += GetMaxStrandCount(i);
   }

   // If we got this far, then iStrand is beyond the last bundle so just
   // return the index of the last bundle
   return GetBundleCount() - 1;
}

//======================== ACCESS     =======================================
//======================== INQUIRY    =======================================

////////////////////////// PROTECTED  ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
//======================== OPERATORS  =======================================
//======================== OPERATIONS =======================================
void bmfBundlePattern::MakeCopy(const bmfBundlePattern& rOther)
{
   ASSERTVALID;

   m_Bundles = rOther.m_Bundles;
}

void bmfBundlePattern::MakeAssignment(const bmfBundlePattern& rOther)
{
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
bool bmfBundlePattern::AssertValid() const
{
   // For the data in this class to be valid,  all bundles must have
   // an offset that is >= zero.
   std::vector<BundleData>::const_iterator iter;
   for ( iter = m_Bundles.begin(); iter < m_Bundles.end(); iter++ )
   {
      const BundleData& bd = *iter;
      if ( bd.Offset < 0 )
         return false;

      // Is your strand bundle correct? The max number of
      // strands is zero. Does this make sense?
      WARN( bd.MaxStrands == 0, "Max # Strands = 0 - Does this make sense?" );
   }

   return true;
}

void bmfBundlePattern::Dump(dbgDumpContext& os) const
{
   ASSERTVALID;

   os << "Dump for bmfBundlePattern" << endl;
   std::vector<BundleData>::const_iterator i;

   os << "Strand Bundles" << endl;
   Int16 j = 0;
   for ( i = m_Bundles.begin(); i < m_Bundles.end(); i++, j++ )
   {
      const BundleData& bd = *i;
      os << "m_Bundles[" << j << "].Offset     = " << bd.Offset << endl;
      os << "                      .MaxStrands = " << bd.MaxStrands << endl;
   }
   os << endl;
}
#endif // _DEBUG

#if defined _UNITTEST
bool bmfBundlePattern::TestMe(dbgLog& rlog)
{
   TESTME_PROLOGUE("bmfBundlePattern");

   bmfBundlePattern ptrn;

   TRY_TESTME( ptrn.GetBundleCount() == 0 );

   ptrn.AddBundle( 10.0, 10 );
   TRY_TESTME( ptrn.GetBundleCount() == 1 );

   ptrn.AddBundle( 15.0, 5 );
   TRY_TESTME( ptrn.GetBundleCount() == 2 );

   TRY_TESTME( IsEqual( ptrn.GetBundleOffset(0), 10.0 ) );
   TRY_TESTME( IsEqual( ptrn.GetBundleHeight(0), 10.0 ) );
   TRY_TESTME( ptrn.GetMaxStrandCount(0) == 10 );

   TRY_TESTME( IsEqual( ptrn.GetBundleOffset(1), 15.0 ) );
   TRY_TESTME( IsEqual( ptrn.GetBundleHeight(1), 25.0 ) );
   TRY_TESTME( ptrn.GetMaxStrandCount(1) == 5 );

   gpPoint2d cg;
   for ( Uint32 i = 0; i < ptrn.GetMaxStrandCount(0)+1; i++ )
   {
      cg = ptrn.GetCenterOfGravity(i);
      TRY_TESTME( cg == gpPoint2d(0.0,ptrn.GetBundleHeight(0) ) );
   }

   cg = ptrn.GetCenterOfGravity(13);
   TRY_TESTME( cg == gpPoint2d(0, 13.46153846154 ) );

   cg = ptrn.GetCenterOfGravity(20);
   TRY_TESTME( cg == gpPoint2d(0, 17.5 ) );

   ptrn.RemoveBundle(0);
   TRY_TESTME( ptrn.GetBundleCount() == 1 );
   TRY_TESTME( IsEqual(ptrn.GetBundleOffset(0), 15.0 ) );
   TRY_TESTME( IsEqual(ptrn.GetBundleHeight(0), 15.0 ) );
   TRY_TESTME( ptrn.GetMaxStrandCount(0) == 5 );

   ptrn.RemoveAllBundles();
   cg = ptrn.GetCenterOfGravity(10);
   TRY_TESTME( cg == gpPoint2d(0,0) );

   TESTME_EPILOG("bmfBundlePattern");
}
#endif // _UNITTEST
