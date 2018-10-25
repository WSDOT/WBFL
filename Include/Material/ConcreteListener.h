///////////////////////////////////////////////////////////////////////
// Material - Analytical and Product modeling of civil engineering materials
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

#ifndef INCLUDED_MATERIAL_CONCRETELISTENER_H_
#define INCLUDED_MATERIAL_CONCRETELISTENER_H_
#pragma once

// SYSTEM INCLUDES
//

// PROJECT INCLUDES
//
#include <Material\MaterialExp.h>

// LOCAL INCLUDES
//

// FORWARD DECLARATIONS
//
class MATCLASS matConcrete;

// MISCELLANEOUS
//

/*****************************************************************************
CLASS 
   matConcreteListener

   Provides a callback interface for concrete material observers.


DESCRIPTION
   Provides a callback interface for concrete material observers.  When a
   concrete material changes,  a listener is notified through the callback
   methods in this interface.  Each callback is implemented with a do-nothing
   function.  Subclasses need only override those events they are interesting
   in listening to.


COPYRIGHT
   Copyright (c) 1997
   Washington State Department Of Transportation
   All Rights Reserved

LOG
   rab : 11.17.1997 : Created file
*****************************************************************************/

class MATCLASS matConcreteListener
{
public:
   // GROUP: LIFECYCLE

   //------------------------------------------------------------------------
   // Default constructor
   matConcreteListener();

   //------------------------------------------------------------------------
   // Destructor
   virtual ~matConcreteListener();

   // GROUP: OPERATORS
   // GROUP: OPERATIONS

   //------------------------------------------------------------------------
   // Called when the listener is registered with the concrete.
   virtual void OnRegistered(matConcrete* pConcrete);

   //------------------------------------------------------------------------
   // Called when the listener is unregistered with the concrete or when
   // the concrete is about to be destroyed.
   virtual void OnUnregistered(matConcrete* pConcrete);
   
   //------------------------------------------------------------------------
   // Called when the concrete material model has changed.
   virtual void OnConcreteChanged(matConcrete* pConcrete);

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
#if defined _UNITTEST
   //------------------------------------------------------------------------
   // Self-diagnostic test function.  Returns <b>true</b> if the test passes,
   // otherwise return <b>false</b>.
   static bool TestMe(dbgLog& rlog);
#endif // _UNITTEST

protected:
   // GROUP: DATA MEMBERS
   // GROUP: LIFECYCLE
   // GROUP: OPERATORS
   // GROUP: OPERATIONS
   // GROUP: ACCESS
   // GROUP: INQUIRY

private:
   // GROUP: DATA MEMBERS
   // GROUP: LIFECYCLE

   // Prevent accidental copying and assignment
   matConcreteListener(const matConcreteListener&);
   matConcreteListener& operator=(const matConcreteListener&);

   // GROUP: OPERATORS
   // GROUP: OPERATIONS
   // GROUP: ACCESS
   // GROUP: INQUIRY
};

// INLINE METHODS
//

// EXTERNAL REFERENCES
//

#endif // INCLUDED_MATERIAL_CONCRETELISTENER_H_
