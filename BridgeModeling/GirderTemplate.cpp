///////////////////////////////////////////////////////////////////////
// BMF - Bridge Modeling Framework - Product modeling of bridge structures
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

#include <BridgeModeling\BridgeModelingLib.h>

/****************************************************************************
CLASS
   bmfGirderTemplate
****************************************************************************/

#include <BridgeModeling\GirderTemplate.h>        // class implementation
#include <BridgeModeling\Girder.h>
#include <BridgeModeling\GirderProfile.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

////////////////////////// PUBLIC     ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
bmfGirderTemplate::bmfGirderTemplate(const std::_tstring& name,const bmfGirderProfile* pProfile) :
m_Name( name ),
m_pProfile( pProfile )
{
}

bmfGirderTemplate::bmfGirderTemplate(const bmfGirderTemplate& rOther)
{
   MakeCopy(rOther);
}

bmfGirderTemplate::~bmfGirderTemplate()
{
}

//======================== OPERATORS  =======================================
bmfGirderTemplate& bmfGirderTemplate::operator= (const bmfGirderTemplate& rOther)
{
   if( this != &rOther )
   {
      MakeAssignment(rOther);
   }

   return *this;
}

//======================== OPERATIONS =======================================
//======================== ACCESS     =======================================
void bmfGirderTemplate::SetName(const std::_tstring& name)
{
   m_Name = name;
}

std::_tstring bmfGirderTemplate::GetName() const
{
   return m_Name;
}

const bmfGirderProfile* bmfGirderTemplate::GetProfile() const
{
   return m_pProfile;
}

//======================== INQUIRY    =======================================

////////////////////////// PROTECTED  ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
//======================== OPERATORS  =======================================
//======================== OPERATIONS =======================================
void bmfGirderTemplate::MakeCopy(const bmfGirderTemplate& rOther)
{
   m_Name     = rOther.m_Name;
   m_pProfile = rOther.m_pProfile;
}

void bmfGirderTemplate::MakeAssignment(const bmfGirderTemplate& rOther)
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

