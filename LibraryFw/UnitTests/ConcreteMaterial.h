///////////////////////////////////////////////////////////////////////
// LibraryFW - Framework for implementing library features in programs
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

#ifndef INCLUDED_LIBRARYFW_CONCRETEMATERIAL_H_
#define INCLUDED_LIBRARYFW_CONCRETEMATERIAL_H_
#pragma once

// SYSTEM INCLUDES
//

// PROJECT INCLUDES
//
#include <LibraryFw\LibraryEntry.h>
#include <System\SubjectT.h>

// LOCAL INCLUDES
//

// FORWARD DECLARATIONS
//

// MISCELLANEOUS
//

/*****************************************************************************
CLASS 
   libConcreteMaterial

   A library entry class for concrete materials.


DESCRIPTION
   This class may be used to describe concrete materials in a library.


COPYRIGHT
   Copyright © 1997-1998
   Washington State Department Of Transportation
   All Rights Reserved

LOG
   rdp : 07.20.1998 : Created file
*****************************************************************************/

class libConcreteMaterial : public libLibraryEntry
{
public:
   // GROUP: LIFECYCLE

   //------------------------------------------------------------------------
   // Default constructor
   libConcreteMaterial();

   //------------------------------------------------------------------------
   // Copy constructor
   libConcreteMaterial(const libConcreteMaterial& rOther);

   //------------------------------------------------------------------------
   // Destructor
   virtual ~libConcreteMaterial();

   // GROUP: OPERATORS
   //------------------------------------------------------------------------
   // Assignment operator
   libConcreteMaterial& operator = (const libConcreteMaterial& rOther);

   // GROUP: OPERATIONS

   //------------------------------------------------------------------------
   // Edit the entry
   virtual bool Edit(bool allowEditing) {return false;}

   void Notify(int hint) {}


   //------------------------------------------------------------------------
   // Save to structured storage
   virtual bool SaveMe(sysIStructuredSave* pSave);

   //------------------------------------------------------------------------
   // Load from structured storage
   virtual bool LoadMe(sysIStructuredLoad* pLoad);

    // GROUP: ACCESS
   //------------------------------------------------------------------------
   // SetFc - set crushing strength of concrete
   void SetFc(Float64 fc);

   //------------------------------------------------------------------------
   // GetFc - get crushing strength of concrete
   Float64 GetFc() const;

   //------------------------------------------------------------------------
   // SetEc - set Young's modulus of concrete
   void SetEc(Float64 ec);

   //------------------------------------------------------------------------
   // GetEc - set Young's modulus of concrete
   Float64 GetEc() const;

   //------------------------------------------------------------------------
   // SetWeightDensity - set weight density of concrete
   void SetWeightDensity(Float64 d);

   //------------------------------------------------------------------------
   // GetWeightDensity - get weight density of concrete
   Float64 GetWeightDensity() const;

   //------------------------------------------------------------------------
   // SetAggregateSize - max aggregate size
   void SetAggregateSize(Float64 s);

   //------------------------------------------------------------------------
   // GetAggregateSize - max aggregate size
   Float64 GetAggregateSize()const;

   // GROUP: INQUIRY

protected:
   // GROUP: DATA MEMBERS
   // GROUP: LIFECYCLE
   // GROUP: OPERATORS
   // GROUP: OPERATIONS
   void MakeCopy(const libConcreteMaterial& rOther);

   //------------------------------------------------------------------------
   void MakeAssignment(const libConcreteMaterial& rOther);
  // GROUP: ACCESS
  // GROUP: INQUIRY

private:
   // GROUP: DATA MEMBERS
   Float64 m_Fc;
   Float64 m_Ec;
   Float64 m_D;
   Float64 m_AggSize;

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

#endif // INCLUDED_LIBRARYFW_CONCRETEMATERIAL_H_
