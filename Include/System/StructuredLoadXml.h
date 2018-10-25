///////////////////////////////////////////////////////////////////////
// System - WBFL low level system services
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

#ifndef INCLUDED_SYSTEM_STRUCTUREDLOADXML_H_
#define INCLUDED_SYSTEM_STRUCTUREDLOADXML_H_
#pragma once

// SYSTEM INCLUDES
//
#include <list>
#include <istream>
#include <System\SysExp.h>
#include <System\IStructuredLoad.h>
#include <System\XStructuredLoad.h>
#include <System\LineParseXml.h>

// FORWARD DECLARATIONS
//

// MISCELLANEOUS
//

/*****************************************************************************
CLASS 
   sysStructuredLoadXml

   This class implements the IStructuredLoad interface for xml files.


DESCRIPTION
   Read xml files using the IStructuredLoad interface.
   DON'T expect this class to be a general xml reader!!! 
   This class is designed to read files written by the IStructuredSaveXml 
   class only. Anything more is pushing it.

LOG
   rdp : 07.15.1998 : Created file
*****************************************************************************/

class SYSCLASS sysStructuredLoadXml : public sysIStructuredLoad
{
public:
   // GROUP: LIFECYCLE

   //------------------------------------------------------------------------
   // Constructor
   // Open with an empty stream. This class will write the entire xml file,
   // including header and footer information.
   sysStructuredLoadXml();

   //------------------------------------------------------------------------
   // Destructor
   virtual ~sysStructuredLoadXml();

   // GROUP: OPERATORS
   // GROUP: OPERATIONS

   //------------------------------------------------------------------------
   // Initializes the structured load object before reading from a stream.
   // Call this method before calling any other method of this class.
   void BeginLoad(std::_tistream* pis);

   //------------------------------------------------------------------------
   // Call this method after you are done with your structured load
   void EndLoad();

   //------------------------------------------------------------------------
   // Check for the Beginning of a named structured data unit. If true is 
   // returned, the beginning of the unit was found and the file pointer is
   // advanced. If false is returned, the file pointer does not advance.
   // After a unit has been entered, GetVersion may be called to get its
   // version
   virtual bool BeginUnit(LPCTSTR name) override;

   //------------------------------------------------------------------------
   // Check for the end of a structured data chunk that was started by a call to 
   // BeginUnit.
   virtual bool EndUnit() override;

   //------------------------------------------------------------------------
   // Get the version number of the current unit
   virtual Float64 GetVersion() override;

   //------------------------------------------------------------------------
   // Get the version number of the unit that is the parent to this unit
   virtual Float64 GetParentVersion() override;

   virtual std::_tstring GetParentUnit() override;

   //------------------------------------------------------------------------
   // Get the version number of the top-most unit
   virtual Float64 GetTopVersion() override;

   //------------------------------------------------------------------------
   // Property read routines. All of these calls try to read a property at the
   // current file pointer location. If the function returns true, the property
   // was read and the file pointer advances. If the function returns false,
   // the property was not at the current locaton and the file pointer does not
   // advance.
   // Read a string property
   virtual bool Property(LPCTSTR name, std::_tstring* pvalue) override;

   //------------------------------------------------------------------------
   // Read a real number property
   virtual bool Property(LPCTSTR name, Float64* pvalue) override;

   //------------------------------------------------------------------------
   // Read an integral property
   virtual bool Property(LPCTSTR name, Int16* pvalue) override;

   //------------------------------------------------------------------------
   // Read an unsigned integral property
   virtual bool Property(LPCTSTR name, Uint16* pvalue) override;

   //------------------------------------------------------------------------
   // Read an integral property
   virtual bool Property(LPCTSTR name, Int32* pvalue) override;

   //------------------------------------------------------------------------
   // Read an unsigned integral property
   virtual bool Property(LPCTSTR name, Uint32* pvalue) override;

   //------------------------------------------------------------------------
   // Read an integral property
   virtual bool Property(LPCTSTR name, Int64* pvalue) override;

   //------------------------------------------------------------------------
   // Read an unsigned integral property
   virtual bool Property(LPCTSTR name, Uint64* pvalue) override;

   //------------------------------------------------------------------------
   // Read an integral property
   virtual bool Property(LPCTSTR name, LONG* pvalue) override;

   //------------------------------------------------------------------------
   // Read an unsigned integral property
   virtual bool Property(LPCTSTR name, ULONG* pvalue) override;

   //------------------------------------------------------------------------
   // Read a bool property
   virtual bool Property(LPCTSTR name, bool* pvalue) override;

   //------------------------------------------------------------------------
   // Am I at the end of the "File"?
   virtual bool Eof() const override;

   //------------------------------------------------------------------------
   // Dump state as a text string. This is primarily to be used for
   // error handling.
   virtual std::_tstring GetStateDump() const override;

   virtual std::_tstring GetUnit() const override;

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
   std::_tistream*   m_pIStream;
   std::ios_base::iostate m_IoState;
   sysLineParseXml m_LineParser;
   long          m_LineNumber;

   long          m_Level;   // unit nesting level
   typedef std::pair<std::_tstring, Float64> ListItem;
   typedef std::list<ListItem> UnitList;
   typedef UnitList::const_iterator UnitListConstIterator;
   UnitList   m_UnitList; // stack of information about current units.

   // GROUP: LIFECYCLE
   // Prevent accidental copying and assignment
   sysStructuredLoadXml(const sysStructuredLoadXml&);
   sysStructuredLoadXml& operator=(const sysStructuredLoadXml&) = delete;

   // GROUP: OPERATORS
   // GROUP: OPERATIONS
   //------------------------------------------------------------------------
   // Read next block of xml from stream. This routine assumes that new xml
   // blocks start on a new line.
   void ReadNext();

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

#endif // INCLUDED_SYSTEM_STRUCTUREDLOADXML_H_
