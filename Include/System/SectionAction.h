///////////////////////////////////////////////////////////////////////
// System - WBFL low level system services
// Copyright © 1999-2023  Washington State Department of Transportation
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

#ifndef INCLUDED_SYSTEM_SECTIONACTION_H_
#define INCLUDED_SYSTEM_SECTIONACTION_H_
#pragma once

#include <System\SysExp.h>
#include <System\SectionValue.h>

// LOCAL INCLUDES
//

// FORWARD DECLARATIONS
//

// MISCELLANEOUS
//

/*****************************************************************************
CLASS 
   sysSectionAction

   Encapsulates structural actions at a section of a structural member.


DESCRIPTION
   Encapsulates structural actions at a section of a structural member. 
   Structural actions include axial force, shear, moment, axial deflection,
   deflection,  and rotation.

LOG
   rab : 11.11.1998 : Created file
*****************************************************************************/

class SYSCLASS sysSectionAction
{
public:
   // GROUP: LIFECYCLE

   //------------------------------------------------------------------------
   // Default constructor
   sysSectionAction(Float64 val = 0.0);

   //------------------------------------------------------------------------
   // Copy constructor
   sysSectionAction(const sysSectionAction& rOther);

   //------------------------------------------------------------------------
   // Destructor
   virtual ~sysSectionAction();

   // GROUP: OPERATORS
   //------------------------------------------------------------------------
   // Assignment operator
   sysSectionAction& operator=(const sysSectionAction& rOther);
   //------------------------------------------------------------------------
   sysSectionAction& operator=(const sysSectionValue& val);
   //------------------------------------------------------------------------
   sysSectionAction& operator=(Float64 val);
   //------------------------------------------------------------------------
   sysSectionAction& operator+=(const sysSectionAction& rOther);
   //------------------------------------------------------------------------
   sysSectionAction& operator-=(const sysSectionAction& rOther);
   //------------------------------------------------------------------------
   sysSectionAction& operator*=(const sysSectionAction& rOther);
   //------------------------------------------------------------------------
   sysSectionAction& operator/=(const sysSectionAction& rOther);
   //------------------------------------------------------------------------
   sysSectionAction  operator-();
   //------------------------------------------------------------------------
   sysSectionAction& operator+=(Float64 val);
   //------------------------------------------------------------------------
   sysSectionAction& operator+=(const sysSectionValue& val);
   //------------------------------------------------------------------------
   sysSectionAction& operator-=(Float64 val);
   //------------------------------------------------------------------------
   sysSectionAction& operator-=(const sysSectionValue& val);
   //------------------------------------------------------------------------
   sysSectionAction& operator*=(Float64 val);
   //------------------------------------------------------------------------
   sysSectionAction& operator*=(const sysSectionValue& val);
   //------------------------------------------------------------------------
   sysSectionAction& operator/=(Float64 val);
   //------------------------------------------------------------------------
   sysSectionAction& operator/=(const sysSectionValue& val);

   // GROUP: OPERATIONS
   // GROUP: ACCESS
   //------------------------------------------------------------------------
   sysSectionValue& Fx();
   //------------------------------------------------------------------------
   const sysSectionValue& Fx() const;
   //------------------------------------------------------------------------
   sysSectionValue& Fy();
   //------------------------------------------------------------------------
   const sysSectionValue& Fy() const;
   //------------------------------------------------------------------------
   sysSectionValue& Mz();
   //------------------------------------------------------------------------
   const sysSectionValue& Mz() const;
   //------------------------------------------------------------------------
   sysSectionValue& Dx();
   //------------------------------------------------------------------------
   const sysSectionValue& Dx() const;
   //------------------------------------------------------------------------
   sysSectionValue& Dy();
   //------------------------------------------------------------------------
   const sysSectionValue& Dy() const;
   //------------------------------------------------------------------------
   sysSectionValue& Rz();
   //------------------------------------------------------------------------
   const sysSectionValue& Rz() const;

   // GROUP: INQUIRY

protected:
   // GROUP: DATA MEMBERS
   // GROUP: LIFECYCLE
   // GROUP: OPERATORS
   // GROUP: OPERATIONS
   //------------------------------------------------------------------------
   void MakeCopy(const sysSectionAction& rOther);

   //------------------------------------------------------------------------
   void MakeAssignment(const sysSectionAction& rOther);

   // GROUP: ACCESS

   // GROUP: INQUIRY

private:
   // GROUP: DATA MEMBERS
   sysSectionValue m_Fx;
   sysSectionValue m_Fy;
   sysSectionValue m_Mz;
   sysSectionValue m_Dx;
   sysSectionValue m_Dy;
   sysSectionValue m_Rz;

   // GROUP: LIFECYCLE
   // GROUP: OPERATORS
   // GROUP: OPERATIONS
   // GROUP: ACCESS
   // GROUP: INQUIRY

public:
   // GROUP: DEBUG
   #if defined _DEBUG
   //------------------------------------------------------------------------
   // Returns true if the object is in a valid state, otherwise returns false.
   virtual bool AssertValid() const;

   //------------------------------------------------------------------------
   // Dumps the contents of the object to the given dump context.
   virtual void Dump(dbgDumpContext& os) const;
   #endif // _DEBUG

   #if defined _UNITTEST
   //------------------------------------------------------------------------
   // Runs a self-diagnostic test.  Returns true if the test passed,
   // otherwise false.
   static bool TestMe(dbgLog& rlog);
   #endif // _UNITTEST
};

// INLINE METHODS
//

// EXTERNAL REFERENCES
//

//------------------------------------------------------------------------
SYSFUNC sysSectionAction operator+(const sysSectionAction& a,const sysSectionAction& b);

//------------------------------------------------------------------------
SYSFUNC sysSectionAction operator-(const sysSectionAction& a,const sysSectionAction& b);

//------------------------------------------------------------------------
SYSFUNC sysSectionAction operator*(const sysSectionAction& a,const sysSectionAction& b);

//------------------------------------------------------------------------
SYSFUNC sysSectionAction operator*(const sysSectionAction& a,const sysSectionValue& b);

//------------------------------------------------------------------------
SYSFUNC sysSectionAction operator*(const sysSectionValue& a,const sysSectionAction& b);

//------------------------------------------------------------------------
SYSFUNC sysSectionAction operator/(const sysSectionAction& a,const sysSectionAction& b);

//------------------------------------------------------------------------
SYSFUNC std::ostream& operator<<(std::ostream& os,const sysSectionAction& a);

#endif // INCLUDED_SYSTEM_SECTIONACTION_H_
