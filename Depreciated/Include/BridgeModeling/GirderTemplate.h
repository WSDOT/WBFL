///////////////////////////////////////////////////////////////////////
// BMF - Bridge Modeling Framework - Product modeling of bridge structures
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

#ifndef INCLUDED_BRIDGEMODELING_GIRDERTEMPLATE_H_
#define INCLUDED_BRIDGEMODELING_GIRDERTEMPLATE_H_
#pragma once

// SYSTEM INCLUDES
//
#include <vector>
#include <string>

// PROJECT INCLUDES
//
#include <BridgeModeling\BridgeModelingExp.h>

// LOCAL INCLUDES
//

// FORWARD DECLARATIONS
//
class bmfGirder;
class bmfGirderProfile;

// MISCELLANEOUS
//

/*****************************************************************************
CLASS 
   bmfGirderTemplate

   Describes the general layout of a girder.


DESCRIPTION
   Describes the general layout of a girder.  A basic girder (bmfGirder) is
   described by its cross section.  The cross section is project along the
   length of the girder to make it a prismatic solid.

COPYRIGHT
   Copyright (c) 1997
   Washington State Department Of Transportation
   All Rights Reserved

LOG
   rab : 05.17.1997 : Created file
*****************************************************************************/

class BMFCLASS bmfGirderTemplate
{
public:
   // GROUP: LIFECYCLE

   //------------------------------------------------------------------------
   // Default constructor
   bmfGirderTemplate(const std::_tstring& name,const bmfGirderProfile* pProfile);

   //------------------------------------------------------------------------
   // Copy constructor
   bmfGirderTemplate(const bmfGirderTemplate& rOther);

   //------------------------------------------------------------------------
   // Destructor
   virtual ~bmfGirderTemplate();

   // GROUP: OPERATORS

   //------------------------------------------------------------------------
   // Assignment operator
   //
   // Returns reference to itself
   bmfGirderTemplate& operator = (const bmfGirderTemplate& rOther);

   // GROUP: OPERATIONS

   //------------------------------------------------------------------------
   virtual bmfGirder* CreateGirder() = 0;

   //------------------------------------------------------------------------
   virtual bmfGirderTemplate* CreateClone() const = 0;

   // GROUP: ACCESS

   //------------------------------------------------------------------------
   void SetName(const std::_tstring& name);

   //------------------------------------------------------------------------
   std::_tstring GetName() const;

   //------------------------------------------------------------------------
   const bmfGirderProfile* GetProfile() const;

   // GROUP: INQUIRY

protected:
   // GROUP: DATA MEMBERS
   // GROUP: LIFECYCLE
   // GROUP: OPERATORS
   // GROUP: OPERATIONS
   void MakeCopy(const bmfGirderTemplate& rOther);
   virtual void MakeAssignment(const bmfGirderTemplate& rOther);

   // GROUP: ACCESS
   // GROUP: INQUIRY

private:
   // GROUP: DATA MEMBERS
   std::_tstring m_Name;
   const bmfGirderProfile* m_pProfile;

   // GROUP: LIFECYCLE
   // GROUP: OPERATORS
   // GROUP: OPERATIONS
   // GROUP: ACCESS
   // GROUP: INQUIRY
};

// INLINE METHODS
//

// EXTERNAL REFERENCES
//

#endif // INCLUDED_BRIDGEMODELING_GIRDERTEMPLATE_H_

