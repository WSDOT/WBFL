///////////////////////////////////////////////////////////////////////
// System - WBFL low level system services
// Copyright © 1999-2016  Washington State Department of Transportation
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

#ifndef INCLDUED_SYSTEM_SECTIONVALUE_H_
#define INCLDUED_SYSTEM_SECTIONVALUE_H_
#pragma once

#include <System\SysExp.h>


// LOCAL INCLUDES
//

// FORWARD DECLARATIONS
//

// MISCELLANEOUS
//

/*****************************************************************************
CLASS 
   sysSectionValue

   Encapsulates the notion of a value at a section.


DESCRIPTION
   Encapsulates the notion of a value at a section.  In section based
   analysis, it is not uncommon to have discontinuities at a section.
   This class supports that by providing left and right values.

BUGS
   There are currently no known problems with this class.

COPYRIGHT
   Copyright (c) 1997
   Washington State Department Of Transportation
   All Rights Reserved

LOG
   rab : 08.19.1997 : Created file
*****************************************************************************/

class SYSCLASS sysSectionValue
{
public:
   // GROUP: LIFECYCLE

   //------------------------------------------------------------------------
   sysSectionValue(Float64 val = 0.);

   //------------------------------------------------------------------------
   sysSectionValue(Float64 left,Float64 right);

   //------------------------------------------------------------------------
   sysSectionValue(const sysSectionValue& rOther);

   //------------------------------------------------------------------------
   ~sysSectionValue();

   // GROUP: OPERATORS

   //------------------------------------------------------------------------
   sysSectionValue& operator=(const sysSectionValue& rOther);
   //------------------------------------------------------------------------
   sysSectionValue& operator=(Float64 val);
   //------------------------------------------------------------------------
   sysSectionValue& operator+=(const sysSectionValue& rOther);
   //------------------------------------------------------------------------
   sysSectionValue& operator-=(const sysSectionValue& rOther);
   //------------------------------------------------------------------------
   sysSectionValue& operator*=(const sysSectionValue& rOther);
   //------------------------------------------------------------------------
   sysSectionValue& operator/=(const sysSectionValue& rOther);
   //------------------------------------------------------------------------
   sysSectionValue  operator-();
   //------------------------------------------------------------------------
   sysSectionValue& operator+=(Float64 val);
   //------------------------------------------------------------------------
   sysSectionValue& operator-=(Float64 val);
   //------------------------------------------------------------------------
   sysSectionValue& operator*=(Float64 val);
   //------------------------------------------------------------------------
   sysSectionValue& operator/=(Float64 val);

   // GROUP: OPERATIONS
   // GROUP: ACCESS

   //------------------------------------------------------------------------
   Float64& Left();
   //------------------------------------------------------------------------
   const Float64& Left() const;
   //------------------------------------------------------------------------
   Float64& Right();
   //------------------------------------------------------------------------
   const Float64& Right() const;

   //------------------------------------------------------------------------
   std::_tstring AsString() const;
   // GROUP: INQUIRY

protected:
   // GROUP: DATA MEMBERS
   // GROUP: LIFECYCLE
   // GROUP: OPERATORS
   // GROUP: OPERATIONS
   void MakeCopy(const sysSectionValue& rOther);
   void MakeAssignment(const sysSectionValue& rOther);

   // GROUP: ACCESS
   // GROUP: INQUIRY

private:
   // GROUP: DATA MEMBERS
   Float64 m_Left;
   Float64 m_Right;

   // GROUP: LIFECYCLE
   // GROUP: OPERATORS
   // GROUP: OPERATIONS
   // GROUP: ACCESS
   // GROUP: INQUIRY
};

//------------------------------------------------------------------------
SYSFUNC sysSectionValue operator+(const sysSectionValue& a,const sysSectionValue& b);

//------------------------------------------------------------------------
SYSFUNC sysSectionValue operator-(const sysSectionValue& a,const sysSectionValue& b);

//------------------------------------------------------------------------
SYSFUNC sysSectionValue operator*(const sysSectionValue& a,const sysSectionValue& b);

//------------------------------------------------------------------------
SYSFUNC sysSectionValue operator/(const sysSectionValue& a,const sysSectionValue& b);

//------------------------------------------------------------------------
SYSFUNC std::_tostream& operator<<(std::_tostream& os,const sysSectionValue& a);

#endif // INCLDUED_SYSTEM_SECTIONVALUE_H_
