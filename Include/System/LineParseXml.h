///////////////////////////////////////////////////////////////////////
// System - WBFL low level system services
// Copyright © 1999-2014  Washington State Department of Transportation
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

#ifndef INCLUDED_SYSTEM_LINEPARSEXML_H_
#define INCLUDED_SYSTEM_LINEPARSEXML_H_

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
   sysLineParseXml

   crappy little single-line parser for the xml file loader and saver


DESCRIPTION


COPYRIGHT
   Copyright © 1997-1998
   Washington State Department Of Transportation
   All Rights Reserved

LOG
   rdp : 07.16.1998 : Created file
*****************************************************************************/

class SYSCLASS sysLineParseXml
{
public:
   // types of lines that can be parsed
   enum LineType {BeginUnit, EndUnit, Property, Eof, Unknown};
   // GROUP: LIFECYCLE

   //------------------------------------------------------------------------
   // Default constructor
   sysLineParseXml();

   //------------------------------------------------------------------------
   // Destructor
   virtual ~sysLineParseXml();

   // GROUP: OPERATORS
   // GROUP: OPERATIONS

   //------------------------------------------------------------------------
   // Parse the line and return the type. 
   // line is expected to be cleared of whitespace and be one of the four
   // following types:
   //
   //   <UNIT_NAME VERSION="1.0">    // a BeginUnit
   //   <UNIT_NAME>                  // a BeginUnit with no version
   //   </UNIT_NAME>                 // an EndUnit
   //   <NAME>value</>               // a Property
   //
   LineType ParseLine(const std::_tstring& line);

   //------------------------------------------------------------------------
   // Tell the parser that the last line parsed was the end of file
   void SetEndOfFile() {m_Type=Eof;}

   //------------------------------------------------------------------------
   // Dump state as a text string. This is primarily to be used for
   // error handling.
   virtual std::_tstring GetStateDump() const;
   
   
   // GROUP: ACCESS
   //------------------------------------------------------------------------
   // Get the type of the line just parsed.
   LineType GetType() const;

   //------------------------------------------------------------------------
   // Get the name of the line just parsed. Returns null string if none
   std::_tstring GetName() const;

   //------------------------------------------------------------------------
   // Get the value of the line just parsed. For BeginUnits, this is the version.
   // Returns false if there was a problem parsing the Property.
   bool GetValue(std::_tstring* value);
   bool GetValue(Float64* value);
   bool GetValue(Int16* value);
   bool GetValue(Uint16* value);
   bool GetValue(Int32* value);
   bool GetValue(Uint32* value);
   bool GetValue(Int64* value);
   bool GetValue(Uint64* value);
   bool GetValue(LONG* value);
   bool GetValue(ULONG* value);
   bool GetValue(bool* value);
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

   std::_tstring m_Line;  // the line
   LineType    m_Type;
   std::_tstring m_Name;
   std::_tstring m_Value;

   // GROUP: LIFECYCLE

   // Prevent accidental copying and assignment
   sysLineParseXml(const sysLineParseXml&);
   sysLineParseXml& operator=(const sysLineParseXml&);

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

#endif // INCLUDED_SYSTEM_LINEPARSEXML_H_
