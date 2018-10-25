///////////////////////////////////////////////////////////////////////
// BAM - Bridge Analysis Model, Analytical modeling of bridge structures
// Copyright © 1999-2016  Washington State Department of Transportation
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
#include <BridgeAnalysis\Load.h>
#include <BridgeAnalysis\Loader.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

bamLoad::bamLoad(IDType elementId,
               bamElementType type,
               bamLoadDirection direction)
{
   m_ElementId = elementId;
   m_ElementType = type;
   m_Direction = direction;
   m_LoadCase = 0;
}

bamLoad::~bamLoad()
{
}

void bamLoad::Apply()
{
   bamLoader& loader = GetLoader();
   loader.ApplyLoad();
}

void bamLoad::Remove()
{
   bamLoader& loader = GetLoader();
   loader.RemoveLoad();
}

void bamLoad::SetLoadCase(bamLoadCase* lc)
{
   m_LoadCase = lc;
}

bamLoadCase& bamLoad::GetLoadCase()
{
   return *m_LoadCase;
}

bamLoadDirection bamLoad::GetDirection()
{
   return m_Direction;
} 

bamLoader& bamLoad::GetLoader()
{
   if (m_pLoader.get() == 0)
      m_pLoader = std::auto_ptr<bamLoader>(CreateLoader());

   return *m_pLoader;
}

bool bamLoad::operator==(const bamLoad& other) const
{
   return IsEqual(other);
}

bool bamLoad::IsEqual(const bamLoad& /*other*/) const
{
   return true;
}

IDType bamLoad::GetElementId() const
{
   return m_ElementId;
}

bamElementType bamLoad::GetElementType() const
{
   return m_ElementType;
}

//======================== DEBUG      =======================================
#if defined _DEBUG
bool bamLoad::AssertValid() const
{
   return true;
}

void bamLoad::Dump(dbgDumpContext& os) const
{
   os << "Dump for bamLoad" << endl;
}
#endif // _DEBUG

#if defined _UNITTEST
bool bamLoad::TestMe(dbgLog& rlog)
{
   TESTME_PROLOGUE("bamLoad");

   TEST_NOT_IMPLEMENTED("Unit Tests Not Implemented for bamLoad");

   TESTME_EPILOG("Load");
}
#endif // _UNITTEST

///////////////////////////////////////////////////////////////////////

bamConcForceY::bamConcForceY(IDType elementId,
                       bamElementType type,
                       Float64 location,
                       Float64 p,
                       bool isFractional,
                       bamLoadDirection direction) :
bamLoad(elementId,type,direction)
{
   m_Location = location;
   m_Magnitude = p;
   m_IsFractional = isFractional;
}

bamConcForceY::~bamConcForceY()
{
}


Float64 bamConcForceY::GetLocation()
{
   return m_Location;
}

Float64 bamConcForceY::GetMagnitude()
{
   return m_Magnitude;
}

bool bamConcForceY::IsFractional()
{
   return m_IsFractional;
}

//======================== DEBUG      =======================================
#if defined _DEBUG
bool bamConcForceY::AssertValid() const
{
   return bamLoad::AssertValid();
}

void bamConcForceY::Dump(dbgDumpContext& os) const
{
   os << "Dump for bamConcForceY" << endl;
   os << "m_Location     = " << m_Location << endl;
   os << "m_IsFractional = " << m_IsFractional << endl;
   os << "m_Magnitude    = " << m_Magnitude << endl;
   bamLoad::Dump( os );
}
#endif // _DEBUG

#if defined _UNITTEST
bool bamConcForceY::TestMe(dbgLog& rlog)
{
   TESTME_PROLOGUE("bamConcForceY");

   TEST_NOT_IMPLEMENTED("Unit Tests Not Implemented for bamConcForceY");

   TESTME_EPILOG("ConcForceY");
}
#endif // _UNITTEST

///////////////////////////////////////////////////////////////////////

bamUnifForceY::bamUnifForceY(IDType elementId,
                       bamElementType type,
                       Float64 start,
                       Float64 end,
                       Float64 w,
                       bool isFractional,
                       bamLoadDirection direction) :
bamLoad(elementId,type,direction)
{
   m_StartLocation = start;
   m_EndLocation = end;
   m_Magnitude = w;
   m_IsFractional = isFractional;
}

bamUnifForceY::~bamUnifForceY()
{
}

Float64 bamUnifForceY::GetStartLocation()
{
   return m_StartLocation;
}

Float64 bamUnifForceY::GetEndLocation()
{
   return m_EndLocation;
}

Float64 bamUnifForceY::GetMagnitude()
{
	return m_Magnitude;
}

bool bamUnifForceY::IsFractional()
{
   return m_IsFractional;
}

//======================== DEBUG      =======================================
#if defined _DEBUG
bool bamUnifForceY::AssertValid() const
{
   return bamLoad::AssertValid();
}

void bamUnifForceY::Dump(dbgDumpContext& os) const
{
   os << "Dump for bamUnifForceY" << endl;
   os << "m_StartLocation = " << m_StartLocation << endl;
   os << "m_EndLocation   = " << m_EndLocation << endl;
   os << "m_IsFractional  = " << m_IsFractional << endl;
   os << "m_Magnitude     = " << m_Magnitude << endl;
   bamLoad::Dump( os );
}
#endif // _DEBUG

#if defined _UNITTEST
bool bamUnifForceY::TestMe(dbgLog& rlog)
{
   TESTME_PROLOGUE("bamUnifForceY");

   TEST_NOT_IMPLEMENTED("Unit Tests Not Implemented for bamUnifForceY");

   TESTME_EPILOG("UnifForceY");
}
#endif // _UNITTEST

///////////////////////////////////////////////////////////////////////

bamConcMomentZ::bamConcMomentZ(IDType elementId,
                               bamElementType type,
                               Float64 location,
                               Float64 m,
                               bool isFractional) :
bamLoad(elementId,type,Global)
{
   m_Location = location;
   m_Magnitude = m;
   m_IsFractional = isFractional;
}

bamConcMomentZ::~bamConcMomentZ()
{
}


Float64 bamConcMomentZ::GetLocation()
{
   return m_Location;
}

Float64 bamConcMomentZ::GetMagnitude()
{
   return m_Magnitude;
}

bool bamConcMomentZ::IsFractional()
{
   return m_IsFractional;
}

//======================== DEBUG      =======================================
#if defined _DEBUG
bool bamConcMomentZ::AssertValid() const
{
   return bamLoad::AssertValid();
}

void bamConcMomentZ::Dump(dbgDumpContext& os) const
{
   os << "Dump for bamConcMomentZ" << endl;
   os << "m_Location     = " << m_Location << endl;
   os << "m_IsFractional = " << m_IsFractional << endl;
   os << "m_Magnitude    = " << m_Magnitude << endl;
   bamLoad::Dump( os );
}
#endif // _DEBUG

#if defined _UNITTEST
bool bamConcMomentZ::TestMe(dbgLog& rlog)
{
   TESTME_PROLOGUE("bamConcMomentZ");

   TEST_NOT_IMPLEMENTED("Unit Tests Not Implemented for bamConcMomentZ");

   TESTME_EPILOG("ConcForceY");
}
#endif // _UNITTEST
