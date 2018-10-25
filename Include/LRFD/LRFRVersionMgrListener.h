///////////////////////////////////////////////////////////////////////
// LRFD - Utility library to support equations, methods, and procedures
//        from the AASHTO LRFD Bridge Design Specification
// Copyright © 1999-2011  Washington State Department of Transportation
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

#pragma once

#include <Lrfd\LrfdExp.h>


/*****************************************************************************
CLASS 
   lrfrVersionMgrListener

   Listener class for lrfrVersionMgr.


DESCRIPTION
   Listener class for lrfrVersionMgr.


COPYRIGHT
   Copyright (c) 2009
   Washington State Department Of Transportation
   All Rights Reserved

LOG
   rab : 12.07.2009 : Created file
*****************************************************************************/

class LRFDCLASS lrfrVersionMgrListener
{
public:
   //------------------------------------------------------------------------
   // Default constructor
   lrfrVersionMgrListener();

   //------------------------------------------------------------------------
   // Copy constructor
   lrfrVersionMgrListener(const lrfrVersionMgrListener& rOther);

   //------------------------------------------------------------------------
   // Destructor
   virtual ~lrfrVersionMgrListener();

   //------------------------------------------------------------------------
   // Assignment operator
   lrfrVersionMgrListener& operator = (const lrfrVersionMgrListener& rOther);

   //------------------------------------------------------------------------
   virtual void OnRegistered();

   //------------------------------------------------------------------------
   virtual void OnUnregistered();

   //------------------------------------------------------------------------
   virtual void OnUpdate();

   // GROUP: ACCESS
   // GROUP: INQUIRY
   // GROUP: DEBUG
#if defined _DEBUG
   //------------------------------------------------------------------------
   // Returns <b>true</b> if the class is in a valid state, otherwise returns
   // <b>false</b>.
   virtual bool AssertValid() const;

   //------------------------------------------------------------------------
   // Dumps the contents of the class to the given stream.
   virtual void Dump(dbgDumpContext& os) const;
#endif // _DEBUG
};
