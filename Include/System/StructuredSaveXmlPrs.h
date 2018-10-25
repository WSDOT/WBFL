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

#ifndef INCLUDED_SYSTEM_STRUCTUREDSAVEXMLPRS_H_
#define INCLUDED_SYSTEM_STRUCTUREDSAVEXMLPRS_H_
#pragma once

#include <System\SysExp.h>
#include <System\IStructuredSave.h>
#include <System\XStructuredSave.h>

// FORWARD DECLARATIONS
//
// implementation class
class sysStructuredSaveXmlPrs_Impl;
struct IStream;

// MISCELLANEOUS
//

/*****************************************************************************
CLASS 
   sysStructuredSaveXmlPrs

   This class implements the IStructuredSave interface for xml files.


DESCRIPTION
   Write to xml files using the IStructuredSave interface.


COPYRIGHT
   Copyright © 1997-1998
   Washington State Department Of Transportation
   All Rights Reserved

LOG
   rdp : 07.15.1998 : Created file
*****************************************************************************/

class SYSCLASS sysStructuredSaveXmlPrs : public sysIStructuredSave
{
public:
   // GROUP: LIFECYCLE

   //------------------------------------------------------------------------
   // Constructor
   sysStructuredSaveXmlPrs();

   //------------------------------------------------------------------------
   // Destructor
   virtual ~sysStructuredSaveXmlPrs();

   // GROUP: OPERATORS
   // GROUP: OPERATIONS
   //------------------------------------------------------------------------
   // Initializes the structured save object before writing a stream.
   // Call this method before calling any other method of this class.
   void BeginSave(IStream* pis);

   //------------------------------------------------------------------------
   // Call this method after you are done with your structured save
   void EndSave();

   //------------------------------------------------------------------------
   // Mark the Beginning of a structured data chunk. This call must be always
   // balanced by a corresponding call to EndUnit. An optional version number
   // may be used to tag major units.
   // Version 0.0 means no version was attached.
   virtual void BeginUnit(LPCTSTR name, Float64 version=0.0);

   //------------------------------------------------------------------------
   // Mark the end of a structured data chunk that was started by a call to 
   // BeginUnit.
   virtual void EndUnit();

   //------------------------------------------------------------------------
   // Get the version number of the current unit
   virtual Float64 GetVersion();

   //------------------------------------------------------------------------
   // Get the version number of the unit that is the parent to this unit
   virtual Float64 GetParentVersion();

   virtual std::_tstring GetParentUnit();

   //------------------------------------------------------------------------
   // Get the version number of the top-most unit
   virtual Float64 GetTopVersion();

   //------------------------------------------------------------------------
   // Write a string property
   virtual void Property(LPCTSTR name, LPCTSTR value);

   //------------------------------------------------------------------------
   // Write a real number property
   virtual void Property(LPCTSTR name, Float64 value);

   //------------------------------------------------------------------------
   // Write an integral property
   virtual void Property(LPCTSTR name, Int16 value);

   //------------------------------------------------------------------------
   // Write an unsigned integral property
   virtual void Property(LPCTSTR name, Uint16 value);

   //------------------------------------------------------------------------
   // Write an integral property
   virtual void Property(LPCTSTR name, Int32 value);

   //------------------------------------------------------------------------
   // Write an unsigned integral property
   virtual void Property(LPCTSTR name, Uint32 value);

   //------------------------------------------------------------------------
   // Write an integral property
   virtual void Property(LPCTSTR name, Int64 value);

   //------------------------------------------------------------------------
   // Write an unsigned integral property
   virtual void Property(LPCTSTR name, Uint64 value);

   //------------------------------------------------------------------------
   // Write an unsigned integral property
   virtual void Property(LPCTSTR name, LONG value);

   //------------------------------------------------------------------------
   // Write an unsigned integral property
   virtual void Property(LPCTSTR name, ULONG value);

   //------------------------------------------------------------------------
   // Write a bool property
   virtual void Property(LPCTSTR name, bool value);

   virtual void PutUnit(LPCTSTR xml);

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
   std::auto_ptr<sysStructuredSaveXmlPrs_Impl> m_pImp;

   // GROUP: LIFECYCLE

   // Prevent accidental copying and assignment
   sysStructuredSaveXmlPrs(const sysStructuredSaveXmlPrs&);
   sysStructuredSaveXmlPrs& operator=(const sysStructuredSaveXmlPrs&);

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

#endif // INCLUDED_SYSTEM_STRUCTUREDSAVEXML_H_
