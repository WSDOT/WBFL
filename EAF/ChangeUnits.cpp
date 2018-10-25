///////////////////////////////////////////////////////////////////////
// EAF - Extensible Application Framework
// Copyright © 1999-2010  Washington State Department of Transportation
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

#include "StdAfx.h"
#include "ChangeUnits.h"

#include "AgentTools.h"
#include <EAF\EAFDisplayUnits.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

txnChangeUnits::txnChangeUnits(IBroker* pBroker,eafTypes::UnitMode oldUnits,eafTypes::UnitMode newUnits)
{
   m_pBroker     = pBroker;
   m_UnitMode[0] = oldUnits;
   m_UnitMode[1] = newUnits;
}

std::string txnChangeUnits::Name() const
{
   return "Change Units";
}

txnTransaction* txnChangeUnits::CreateClone() const
{
   return new txnChangeUnits(m_pBroker,m_UnitMode[0],m_UnitMode[1]);
}

bool txnChangeUnits::IsUndoable()
{
   return true;
}

bool txnChangeUnits::IsRepeatable()
{
   return false;
}

bool txnChangeUnits::Execute()
{
   return DoExecute(1);
}

void txnChangeUnits::Undo()
{
   DoExecute(0);
}

bool txnChangeUnits::DoExecute(int i)
{
   GET_IFACE(IDisplayUnits,pDisplayUnits);
   //GET_IFACE(IEvents,pEvents);
   //pEvents->HoldEvents();

   eafTypes::UnitMode old_units = pDisplayUnits->GetUnitMode();
   if ( old_units != m_UnitMode[i] )
   {
      pDisplayUnits->SetUnitMode( m_UnitMode[i] );
   }

//   pEvents->FirePendingEvents();

   return true;
}
