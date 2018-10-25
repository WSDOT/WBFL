///////////////////////////////////////////////////////////////////////
// System - WBFL low level system services
// Copyright © 1999-2013  Washington State Department of Transportation
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

#ifndef INCLUDED_SYSTEM_COMCATMGR_H_
#define INCLUDED_SYSTEM_COMCATMGR_H_
#pragma once

#include <System\SysExp.h>
#include <ComCat.h>

// LOCAL INCLUDES
//

// FORWARD DECLARATIONS
//

// MISCELLANEOUS
//

/*****************************************************************************
CLASS 
   sysComCatMgr

   Wrapper class for the standard COM Component Category Manager


DESCRIPTION
   Wrapper class for the standard COM Component Category Manager

COPYRIGHT
   Copyright © 1997-1998
   Washington State Department Of Transportation
   All Rights Reserved

LOG
   rab : 12.08.1998 : Created file
*****************************************************************************/

class SYSCLASS sysComCatMgr
{
public:
   // GROUP: LIFECYCLE
   // GROUP: OPERATORS
   // GROUP: OPERATIONS
   static HRESULT CreateCategory(OLECHAR* lpszDesc,const CATID& catid);
   static HRESULT RemoveCategory(const CATID& catid,bool bLeaveIfUsed);
   static HRESULT RegWithCategory(const CLSID& clsid,const CATID& catid,bool bReg);

   // GROUP: ACCESS
   // GROUP: INQUIRY

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
   // Default constructor
   sysComCatMgr();

   //------------------------------------------------------------------------
   // Copy constructor
   sysComCatMgr(const sysComCatMgr& rOther);

   //------------------------------------------------------------------------
   // Destructor
   virtual ~sysComCatMgr();

   // GROUP: OPERATORS
   // GROUP: OPERATIONS
   // GROUP: ACCESS
   // GROUP: INQUIRY
};

// INLINE METHODS
//

// EXTERNAL REFERENCES
//

#endif // INCLUDED_SYSTEM_COMCATMGR_H_
