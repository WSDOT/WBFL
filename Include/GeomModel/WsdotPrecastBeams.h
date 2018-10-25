///////////////////////////////////////////////////////////////////////
// GeomModel - Geometric Modeling of shapes and sections
// Copyright © 1999-2014, Washington State Department of Transportation, All Rights Reserved
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

#ifndef INCLUDED_GEOMMODEL_WSDOTPRECASTBEAMS_H_
#define INCLUDED_GEOMMODEL_WSDOTPRECASTBEAMS_H_
#pragma once

// SYSTEM INCLUDES
//

// PROJECT INCLUDES
//
#include <GeomModel\GeomModelExp.h>
#include <System\SingletonKiller.h>
#include <GeomModel\PrecastBeam.h>

// FORWARD DECLARATIONS
//

// MISCELLANEOUS
//

/*****************************************************************************
CLASS 
   gmWsdotPrecastBeams

   Library class for WSDOT precast I Beams.


DESCRIPTION
   This class contains prototypes for W52G, W50G, W58G, and W74G precast I
   beams. This class is implemented as a singleton


COPYRIGHT
   Copyright (c) 1997
   Washington State Department Of Transportation
   All Rights Reserved

LOG
   rdp : 12.30.1997 : Created file
*****************************************************************************/

class GEOMMODELCLASS gmWsdotPrecastBeams
{
public:
   // GROUP: LIFECYCLE

   // Since we can't guarantee when unitSysUnitMgr's list of listeners
   // is created or destroyed,  this must be a singleton. 
   // (It's list is a static member, but even if it wasn't, we don't
   // know the implemenation details)
   // Being a singleton will force an object of this type to have a
   // lifetime that is entirely contained within the lifetime of
   // unitSysUnitsMgr
   static gmWsdotPrecastBeams& GetInstance(); // Return a reference because it can never be NULL

   //------------------------------------------------------------------------
   // Metric Beams
   // prototype w42g
   const gmPrecastBeam& W42MG();

   //------------------------------------------------------------------------
   // prototype w50g
   const gmPrecastBeam& W50MG();

   //------------------------------------------------------------------------
   // prototype w58g
   const gmPrecastBeam& W58MG(); 

   //------------------------------------------------------------------------
   // prototype w74g
   const gmPrecastBeam& W74MG();

   //------------------------------------------------------------------------
   // prototype w42g
   const gmPrecastBeam& W42G();

   //------------------------------------------------------------------------
   // prototype w50g
   const gmPrecastBeam& W50G();

   //------------------------------------------------------------------------
   // prototype w58g
   const gmPrecastBeam& W58G(); 

   //------------------------------------------------------------------------
   // prototype w74g
   const gmPrecastBeam& W74G();

   // GROUP: OPERATORS
   // GROUP: OPERATIONS
   // GROUP: ACCESS
   // GROUP: INQUIRY
   // GROUP: DEBUG
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
   static gmWsdotPrecastBeams* ms_pInstance;

   typedef sysSingletonKillerT<gmWsdotPrecastBeams> Killer;
   friend Killer;
   static Killer ms_Killer;

   std::auto_ptr<gmPrecastBeam> ms_pW42MG;
   std::auto_ptr<gmPrecastBeam> ms_pW50MG;
   std::auto_ptr<gmPrecastBeam> ms_pW58MG;
   std::auto_ptr<gmPrecastBeam> ms_pW74MG;

   std::auto_ptr<gmPrecastBeam> ms_pW42G;
   std::auto_ptr<gmPrecastBeam> ms_pW50G;
   std::auto_ptr<gmPrecastBeam> ms_pW58G;
   std::auto_ptr<gmPrecastBeam> ms_pW74G;

   // GROUP: LIFECYCLE

   //------------------------------------------------------------------------
   // Default constructor
   gmWsdotPrecastBeams();

   //------------------------------------------------------------------------
   // Destructor
   virtual ~gmWsdotPrecastBeams();

   // Prevent accidental copying and assignment
   gmWsdotPrecastBeams(const gmWsdotPrecastBeams&);
   gmWsdotPrecastBeams& operator=(const gmWsdotPrecastBeams&);

   // GROUP: OPERATORS
   // GROUP: OPERATIONS
   // GROUP: ACCESS
   // GROUP: INQUIRY
};

// INLINE METHODS
//

// EXTERNAL REFERENCES
//

#endif // INCLUDED_GEOMMODEL_WSDOTPRECASTBEAMS_H_
