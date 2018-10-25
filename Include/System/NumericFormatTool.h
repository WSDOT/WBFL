///////////////////////////////////////////////////////////////////////
// System - WBFL low level system services
// Copyright © 1999-2012  Washington State Department of Transportation
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

#ifndef INCLUDED_SYSTEM_NUMERICFORMATTOOL_H_
#define INCLUDED_SYSTEM_NUMERICFORMATTOOL_H_
#pragma once

#include <string>
#include <System\SysExp.h>
#include <System\INumericFormatToolBase.h>

// LOCAL INCLUDES
//

// FORWARD DECLARATIONS
//
class sysSectionValue;

// MISCELLANEOUS
//

/*****************************************************************************
CLASS 
   sysNumericFormatTool

   Formats numeric values and returns them as strings.  Extends the standard
   iostream capabilities by adding engineering notation.


DESCRIPTION
   Formats numeric values and returns them as strings.  Extends the standard
   iostream capabilities by adding engineering notation.


COPYRIGHT
   Copyright (c) 1997
   Washington State Department Of Transportation
   All Rights Reserved

LOG
   rab : 11.03.1997 : Created file
*****************************************************************************/

class SYSCLASS sysNumericFormatTool : public sysINumericFormatToolBase
{
public:
   // GROUP: ENUMERATIONS
   enum Format { Automatic = 1,   // Like fixed, except adjusts precision downwards
                                  // to eliminate trailing zeros
                 Fixed = 2,       // Fixed format
                 Scientific = 3,  // Exponential format
                 Engineering = 4  // Exponential format where the exponent is a
                                  // multiple of three
   };

   // GROUP: LIFECYCLE

   //------------------------------------------------------------------------
   // Default constructor.
   sysNumericFormatTool(Format format = Automatic, Uint16 width = 0, Uint16 precision = 0);

   //------------------------------------------------------------------------
   // Copy constructor
   sysNumericFormatTool(const sysNumericFormatTool& rOther);

   //------------------------------------------------------------------------
   // Destructor
   virtual ~sysNumericFormatTool();

   // GROUP: OPERATORS

   //------------------------------------------------------------------------
   // Assignment operator
   sysNumericFormatTool& operator = (const sysNumericFormatTool& rOther);

   // GROUP: OPERATIONS

   //------------------------------------------------------------------------
   std::_tstring AsString(Float64 value) const;
   std::_tstring AsString(const sysSectionValue& value) const;

   // GROUP: ACCESS

   //------------------------------------------------------------------------
   void SetFormat(Format f);

   //------------------------------------------------------------------------
   void SetWidth(Uint16 w);

   //------------------------------------------------------------------------
   void SetPrecision(Uint16 p);

   // GROUP: INQUIRY
   // GROUP: DEBUG

protected:
   // GROUP: DATA MEMBERS
   // GROUP: LIFECYCLE
   // GROUP: OPERATORS

   // GROUP: OPERATIONS
   //------------------------------------------------------------------------
   void MakeCopy(const sysNumericFormatTool& rOther);

   //------------------------------------------------------------------------
   void MakeAssignment(const sysNumericFormatTool& rOther);

   // GROUP: ACCESS
   // GROUP: INQUIRY

private:
   // GROUP: DATA MEMBERS
   Format m_Format;
   Uint16 m_Width;
   Uint16 m_Precision;

   // GROUP: LIFECYCLE
   // GROUP: OPERATORS
   // GROUP: OPERATIONS
   // GROUP: ACCESS
   // GROUP: INQUIRY
};

// INLINE METHODS
//
inline void sysNumericFormatTool::SetFormat(Format f)
{
   m_Format = f;
}

inline void sysNumericFormatTool::SetWidth(Uint16 w)
{
   m_Width = w;
}

inline void sysNumericFormatTool::SetPrecision(Uint16 p)
{
   m_Precision = p;
}

// EXTERNAL REFERENCES
//

#endif // INCLUDED_SYSTEM_NUMERICFORMATTOOL_H_
