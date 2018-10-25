///////////////////////////////////////////////////////////////////////
// BMF - Bridge Modeling Framework - Product modeling of bridge structures
// Copyright © 1999-2015  Washington State Department of Transportation
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
   bmfPrismaticGirderProfile
****************************************************************************/

#include <BridgeModeling\PrismaticGirderProfile.h>        // class implementation
#include <GeomModel\IShape.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

////////////////////////// PUBLIC     ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
bmfPrismaticGirderProfile::bmfPrismaticGirderProfile(const gmIShape* pShape) :
m_Shape( pShape->CreateClone() )
{
}

bmfPrismaticGirderProfile::~bmfPrismaticGirderProfile()
{
}

//======================== OPERATORS  =======================================
//======================== OPERATIONS =======================================
bmfGirderProfile* bmfPrismaticGirderProfile::CreateClone() const
{
   return new bmfPrismaticGirderProfile(m_Shape.get());
}

gmIShape* bmfPrismaticGirderProfile::CreateShape(Float64 x,Float64 girderLength) const
{
   return m_Shape->CreateClone();
}

//======================== ACCESS     =======================================
//======================== INQUIRY    =======================================

////////////////////////// PROTECTED  ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
//======================== OPERATORS  =======================================
//======================== OPERATIONS =======================================
//======================== ACCESS     =======================================
//======================== INQUIRY    =======================================

////////////////////////// PRIVATE    ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
//======================== OPERATORS  =======================================
//======================== OPERATIONS =======================================
//======================== ACCESS     =======================================
//======================== INQUERY    =======================================

