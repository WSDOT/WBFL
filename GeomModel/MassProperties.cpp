///////////////////////////////////////////////////////////////////////
// GeomModel - Geometric Modeling of shapes and sections
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

#include <GeomModel/GeomModelLib.h>
#include <GeomModel/MassProperties.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

using namespace WBFL::Geometry;

MassProperties::MassProperties():
m_Mpl(0)
{
}

MassProperties::MassProperties(Float64 mpl):
m_Mpl(mpl)
{
}

MassProperties::~MassProperties()
{
}

MassProperties MassProperties::operator+(const MassProperties& other)
{
   return MassProperties(m_Mpl + other.m_Mpl);
}

MassProperties MassProperties::operator-(const MassProperties& other)
{
   return MassProperties(m_Mpl - other.m_Mpl);
}

MassProperties& MassProperties::operator+=(const MassProperties& other)
{
   m_Mpl += other.m_Mpl;
   return *this;
}

MassProperties& MassProperties::operator-=(const MassProperties& other)
{
   m_Mpl -= other.m_Mpl;
   return *this;
}

void MassProperties::SetMassPerLength(Float64 mpl)
{
   m_Mpl = mpl;
}

Float64 MassProperties::GetMassPerLength() const
{
   return m_Mpl;
}

#if defined _DEBUG
bool MassProperties::AssertValid() const
{
   return true;
}

void MassProperties::Dump(dbgDumpContext& os) const
{
   os << "Dump for MassProperties" << endl;
   os << " m_Mpl   = "<< m_Mpl << endl;
}
#endif // _DEBUG

#if defined _UNITTEST
#include <MathEx.h>
bool MassProperties::TestMe(dbgLog& rlog)
{
   TESTME_PROLOGUE("MassProperties");

   MassProperties props;

   // Default value should be zero
   TRY_TESTME(IsZero(props.GetMassPerLength()));

   props.SetMassPerLength(50.0);
   TRY_TESTME(IsEqual(props.GetMassPerLength(), 50.0));

   // Add mass properties
   MassProperties props2;
   props.SetMassPerLength(100);
   props2.SetMassPerLength(5.5);
   props += props2;
   TRY_TESTME(IsEqual(props.GetMassPerLength(), 105.5));

   props.SetMassPerLength(100);
   props2.SetMassPerLength(5.5);
   props2 += props;
   TRY_TESTME(IsEqual(props2.GetMassPerLength(), 105.5));

   props.SetMassPerLength(100);
   props2.SetMassPerLength(5.5);
   auto props3 = props + props2;
   TRY_TESTME(IsEqual(props3.GetMassPerLength(), 105.5));

   props.SetMassPerLength(100);
   props2.SetMassPerLength(5.5);
   props3 = props2 + props;
   TRY_TESTME(IsEqual(props3.GetMassPerLength(), 105.5));


   props.SetMassPerLength(100);
   props2.SetMassPerLength(5.5);
   props -= props2;
   TRY_TESTME(IsEqual(props.GetMassPerLength(), 94.5));

   props.SetMassPerLength(100);
   props2.SetMassPerLength(5.5);
   props2 -= props;
   TRY_TESTME(IsEqual(props2.GetMassPerLength(), -94.5));

   props.SetMassPerLength(100);
   props2.SetMassPerLength(5.5);
   props3 = props - props2;
   TRY_TESTME(IsEqual(props3.GetMassPerLength(), 94.5));

   props.SetMassPerLength(100);
   props2.SetMassPerLength(5.5);
   props3 = props2 - props;
   TRY_TESTME(IsEqual(props3.GetMassPerLength(), -94.5));

   TESTME_EPILOG("MassProperties");
}
#endif // _UNITTEST
