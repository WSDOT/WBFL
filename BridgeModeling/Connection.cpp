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

//////////////////X////////////////////X/////////////////////////////////////
// NAME:          Connection           
// SYNOPSIS:      
//////////////////X////////////////////X/////////////////////////////////////

#include <BridgeModeling\Connection.h>            // class implementation

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

////////////////////////// PUBLIC     ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
bmfConnection::bmfConnection() :
m_BearingOffset(0.0),
m_GirderEndSize(0.0),
m_BearingHow(NormalToLine),
m_GirderHow(NormalToLine)
{
} // bmfConnection

bmfConnection::bmfConnection(const std::string& name,
                             Float64 brgOffset,
                             bmfMeasuredHow how_brg,
                             Float64 gdrEndSize,
                             bmfMeasuredHow how_gdr) :
m_Name(name)
{
   m_BearingOffset = brgOffset;
   m_GirderEndSize = gdrEndSize;
   m_BearingHow = how_brg;
   m_GirderHow = how_gdr;
} // bmfConnection

bmfConnection::bmfConnection(const bmfConnection& connection)
{
   MakeCopy( connection );
} // bmfConnection

bmfConnection::~bmfConnection()
{
} // ~bmfConnection

//======================== OPERATORS  =======================================

bmfConnection& bmfConnection::operator = (const bmfConnection& connection)
{
   if ( &connection != this )
      MakeCopy( connection );

   return *this;
} // operator =


//======================== OPERATIONS =======================================
//======================== ACCESS     =======================================
Float64 bmfConnection::GetBearingOffset() const
{
   return m_BearingOffset;
} // GetBearingOffset

bmfMeasuredHow bmfConnection::GetHowBearingOffSetIsMeasured() const
{
   return m_BearingHow;
}

Float64 bmfConnection::GetGirderEndSize() const
{
   return m_GirderEndSize;
} // GetGirderEndSize

bmfMeasuredHow bmfConnection::GetHowGirderEndSizeIsMeasured() const
{
   return m_GirderHow;
}

std::string bmfConnection::GetName() const
{
   return m_Name;
}

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

void bmfConnection::MakeCopy(const bmfConnection& connection)
{
   m_Name          = connection.GetName();
   m_BearingOffset = connection.GetBearingOffset();
   m_GirderEndSize = connection.GetGirderEndSize();
   m_BearingHow    = connection.GetHowBearingOffSetIsMeasured();
   m_GirderHow     = connection.GetHowGirderEndSizeIsMeasured();
}

//======================== ACCESS     =======================================
//======================== INQUERY ==========================================
