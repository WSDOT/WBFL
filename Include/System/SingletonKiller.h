///////////////////////////////////////////////////////////////////////
// System - WBFL low level system services
// Copyright © 1999-2017  Washington State Department of Transportation
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

#ifndef INCLUDED_SYSTEM_SINGLETONKILLER_H_
#define INCLUDED_SYSTEM_SINGLETONKILLER_H_
#pragma once

#include <memory>
#include <System\SysExp.h>


// LOCAL INCLUDES
//

// FORWARD DECLARATIONS
//

// MISCELLANEOUS
//

/*****************************************************************************
CLASS 
   sysSingletonKillerT

   Template class for singleton killers.


DESCRIPTION
   Template class for singleton killers.  Deletes a singleton after it goes
   out of scope.

   See: http://www.sigs.com/publications/docs/cppr/9606/cppr9606.c.vlissides.html

LOG
   rab : 11.03.1997 : Created file
*****************************************************************************/
template <class DOOMED>
class sysSingletonKillerT
{
public:
   sysSingletonKillerT(DOOMED* pDoomed = 0):
   m_pDoomed(pDoomed)
   {
   }

   ~sysSingletonKillerT()
   {
	   delete m_pDoomed;
   }

   void SetDoomed(DOOMED* pDoomed)
   {
      m_pDoomed = pDoomed;
   }

private:
   DOOMED* m_pDoomed;
   sysSingletonKillerT(const sysSingletonKillerT&);
   sysSingletonKillerT& operator=(const sysSingletonKillerT&);
};

#endif // INCLUDED_SYSTEM_SINGLETONKILLER_H_
