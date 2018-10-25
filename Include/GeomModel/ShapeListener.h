///////////////////////////////////////////////////////////////////////
// GeomModel - Geometric Modeling of shapes and sections
// Copyright © 1999-2018  Washington State Department of Transportation
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

#ifndef INCLUDED_GEOMMODEL_SHAPELISTENER_H_
#define INCLUDED_GEOMMODEL_SHAPELISTENER_H_
#pragma once

// SYSTEM INCLUDES
//

// PROJECT INCLUDES
//
#include <GeomModel\GeomModelExp.h>

// LOCAL INCLUDES
//

// FORWARD DECLARATIONS
//
class gmIShape;

// MISCELLANEOUS
//

/*****************************************************************************
CLASS 
   gmShapeListener

   Provides a callback interface for shape observers.


DESCRIPTION
   Provides a callback interface for shape observers.  When a shape changes, 
   a listener is notified through the callback methods in this interface. 
   Each callback is implemented with a do-nothing function.  Subclasses need
   only override those events they are interested in listening to.

   In addition to the interface specified below,  this class implements the
   standard listener interface.

LOG
   rdp : 12.11.1997 : Created file
*****************************************************************************/

class GEOMMODELCLASS gmShapeListener
{
public:


   //------------------------------------------------------------------------
   // Hints supported by this listener. Values defined in .cpp file
   static const int PROPERTIES;   // A shape changed form
   static const int DISPLAY;      // Color or display mode change

   // GROUP: LIFECYCLE

   //------------------------------------------------------------------------
   // Default constructor
   gmShapeListener();


   //------------------------------------------------------------------------
   // Destructor
   virtual ~gmShapeListener();

   // GROUP: OPERATORS

   // GROUP: OPERATIONS

   //------------------------------------------------------------------------
   // OnRegistered
   // Called by the shape (broadcaster) pointed to by pShape when this 
   // listener is registered.
   void OnRegistered(const gmIShape* pShape) const;

   //------------------------------------------------------------------------
   // OnUnregistered
   // Called by the shape (broadcaster) pointed to by pShape when this listener 
   // is registered.
   void OnUnregistered(const gmIShape* pShape) const;

   //------------------------------------------------------------------------
   // OnUpdate
   // Called by the subject gmShapeImp object whenever it changes.  lHint 
   // contains one or more of the hints given above.
   virtual void OnUpdate(const gmIShape* pShape, Int32 lHint) = 0;

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
   //------------------------------------------------------------------------
   // Copy constructor
   gmShapeListener(const gmShapeListener& rOther);
   //------------------------------------------------------------------------
   // Assignment operator
   gmShapeListener& operator = (const gmShapeListener& rOther);

   // GROUP: OPERATORS
   // GROUP: OPERATIONS
   // GROUP: ACCESS
   // GROUP: INQUIRY
};

// INLINE METHODS
//

// EXTERNAL REFERENCES
//

#endif // INCLUDED_GEOMMODEL_SHAPELISTENER_H_
