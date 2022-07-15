///////////////////////////////////////////////////////////////////////
// LRFD - Utility library to support equations, methods, and procedures
//        from the AASHTO LRFD Bridge Design Specification
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

#ifndef INCLUDED_LRFD_STRANDPOOL_H_
#define INCLUDED_LRFD_STRANDPOOL_H_
#pragma once

// SYSTEM INCLUDES
//
#include <map>
#include <Lrfd\LrfdExp.h>
#include <Materials/PsStrand.h>
#include <Lrfd\PsStrand.h>
#include <System\SingletonKiller.h>
#include <Lrfd\VersionMgr.h>


// PROJECT INCLUDES
//

// LOCAL INCLUDES
//

// FORWARD DECLARATIONS
//

// MISCELLANEOUS
//
class lrfdStrandIter;

/*****************************************************************************
CLASS 
   lrfdStrandPool

   Flyweight pool for prestressing strands.


DESCRIPTION
   Flyweight pool for prestressing strands.  All of the strands described in
   AASHTO M203 are stored in this flyweight pool.

LOG
   rab : 12.10.1997 : Created file
*****************************************************************************/

class LRFDCLASS lrfdStrandPool
{
public:
   // GROUP: LIFECYCLE
   // GROUP: OPERATORS
   // GROUP: OPERATIONS
   // GROUP: ACCESS

   //------------------------------------------------------------------------
   // Returns a pointer to an instance of the strand pool.
   static lrfdStrandPool* GetInstance();

   //------------------------------------------------------------------------
   const WBFL::Materials::PsStrand* GetStrand(Int64 key,lrfdVersionMgr::Units units);

   //------------------------------------------------------------------------
   const WBFL::Materials::PsStrand* GetStrand(Int64 key);

   //------------------------------------------------------------------------
   const WBFL::Materials::PsStrand* GetStrand(WBFL::Materials::PsStrand::Grade grade,
                                WBFL::Materials::PsStrand::Type type,
                                WBFL::Materials::PsStrand::Coating coating,
                                WBFL::Materials::PsStrand::Size size );

   //------------------------------------------------------------------------
   // Returns the lookup key for pStrand.  If pStrand is not a member of
   // the strand pool, returns -1
   Int64 GetStrandKey(const WBFL::Materials::PsStrand* pStrand);

   bool CompareStrands(const WBFL::Materials::PsStrand* pStrandA, const WBFL::Materials::PsStrand* pStrandB, bool bCompareGrade = true, bool bCompareType = true, bool bCompareCoating = false, bool bCompareSize = false);

   // GROUP: INQUIRY
   // GROUP: DEBUG
#if defined _DEBUG
   //------------------------------------------------------------------------
   // Returns <b>true</b> if the class is in a valid state, otherwise returns
   // <b>false</b>.
   virtual bool AssertValid() const;

   //------------------------------------------------------------------------
   // Dumps the contents of the class to the given stream.
   virtual void Dump(WBFL::Debug::LogContext& os) const;
#endif // _DEBUG

#if defined _UNITTEST
   //------------------------------------------------------------------------
   static bool TestMe(WBFL::Debug::Log& rlog);
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
   static lrfdStrandPool* ms_pInstance;
   static std::map<Int64, std::shared_ptr<WBFL::Materials::PsStrand> > ms_USStrand;
   static std::map<Int64, std::shared_ptr<WBFL::Materials::PsStrand> > ms_SIStrand;

   typedef WBFL::System::SingletonKiller<lrfdStrandPool> Killer;
   friend Killer;
   static Killer ms_Killer;

   // GROUP: LIFECYCLE

   //------------------------------------------------------------------------
   // Default constructor
   lrfdStrandPool();

   // Prevent accidental copying and assignment
   lrfdStrandPool(const lrfdStrandPool&);
   lrfdStrandPool& operator=(const lrfdStrandPool&) = delete;

   virtual ~lrfdStrandPool();

   // GROUP: OPERATORS
   // GROUP: OPERATIONS
   // GROUP: ACCESS
   // GROUP: INQUIRY

   friend lrfdStrandIter;
};


/*****************************************************************************
CLASS 
   lrfdStrandIter

   Iterates over the various strand stored in lrfdStrandPool.


DESCRIPTION
   Iterates over the various strand stored in lrfdStrandPool.
   The strands are filtered by Grade and Type.

LOG
   rab : 12.10.1997 : Created file
*****************************************************************************/

class LRFDCLASS lrfdStrandIter
{
public:
   // GROUP: LIFECYCLE

   //------------------------------------------------------------------------
   // Default constructor
   lrfdStrandIter(WBFL::Materials::PsStrand::Grade grade = WBFL::Materials::PsStrand::Grade::Gr1725,
                  WBFL::Materials::PsStrand::Type type = WBFL::Materials::PsStrand::Type::LowRelaxation,
                  WBFL::Materials::PsStrand::Coating coating = WBFL::Materials::PsStrand::Coating::None);

   //------------------------------------------------------------------------
   lrfdStrandIter(const lrfdStrandIter& rOther);

   //------------------------------------------------------------------------
   // Destructor
   ~lrfdStrandIter();

   // GROUP: OPERATORS
   //------------------------------------------------------------------------
   lrfdStrandIter& operator=(const lrfdStrandIter& rOther);

   // GROUP: OPERATIONS

   //------------------------------------------------------------------------
   virtual void Begin();

   //------------------------------------------------------------------------
   virtual void End();

   //------------------------------------------------------------------------
   virtual void Next();

   //------------------------------------------------------------------------
   virtual void Move(Int64 pos);

   //------------------------------------------------------------------------
   virtual void MoveBy(Int64 dPos);

   //------------------------------------------------------------------------
   operator void*() const;

   //------------------------------------------------------------------------
   const WBFL::Materials::PsStrand* GetCurrentStrand() const;

   // GROUP: ACCESS

   //------------------------------------------------------------------------
   // Sets the grade of prestress steel for which the available sizes will
   // be iterated over. Sets the iterator to the first element in the
   // iteration sequence.
   void SetGrade(WBFL::Materials::PsStrand::Grade grade);

   //------------------------------------------------------------------------
   // Returns the grade of prestress steel for which the available sizes
   // are being iterated over.
   WBFL::Materials::PsStrand::Grade GetGrade() const;

   //------------------------------------------------------------------------
   // Sets the type of prestress steel for which the available sizes will
   // be iterated over. Sets the iterator to the first element in the
   // iteration sequence.
   void SetType(WBFL::Materials::PsStrand::Type type);

   //------------------------------------------------------------------------
   // Returns the type of prestress steel for which the available sizes
   // are being iterated over.
   WBFL::Materials::PsStrand::Type GetType() const;

   //------------------------------------------------------------------------
   // Sets the coating type of prestress steel for which the available sizes will
   // be iterated over. Sets the iterator to the first element in the
   // iteration sequence.
   void SetCoating(WBFL::Materials::PsStrand::Coating coating);

   //------------------------------------------------------------------------
   // Returns the coating type of prestress steel for which the available sizes
   // are being iterated over.
   WBFL::Materials::PsStrand::Coating GetCoating() const;

   // GROUP: INQUIRY
   // GROUP: DEBUG
#if defined _DEBUG
   //------------------------------------------------------------------------
   // Returns <b>true</b> if the class is in a valid state, otherwise returns
   // <b>false</b>.
   virtual bool AssertValid() const;

   //------------------------------------------------------------------------
   // Dumps the contents of the class to the given stream.
   virtual void Dump(WBFL::Debug::LogContext& os) const;
#endif // _DEBUG

#if defined _UNITTEST
   //------------------------------------------------------------------------
   static bool TestMe(WBFL::Debug::Log& rlog);
#endif // _UNITTEST


protected:
   // GROUP: DATA MEMBERS
   // GROUP: LIFECYCLE
   // GROUP: OPERATORS
   // GROUP: OPERATIONS
   void MakeAssignment(const lrfdStrandIter& rOther);

   // GROUP: ACCESS
   // GROUP: INQUIRY

private:
   // GROUP: DATA MEMBERS
   std::vector< const WBFL::Materials::PsStrand* > m_Strands;
   std::vector< const WBFL::Materials::PsStrand* >::iterator m_Begin;
   std::vector< const WBFL::Materials::PsStrand* >::iterator m_End;
   std::vector< const WBFL::Materials::PsStrand* >::iterator m_Current;
   WBFL::Materials::PsStrand::Grade m_Grade;
   WBFL::Materials::PsStrand::Type m_Type;
   WBFL::Materials::PsStrand::Coating m_Coating;

   // GROUP: LIFECYCLE
   // GROUP: OPERATORS
   // GROUP: OPERATIONS
   void MakeCopy(const lrfdStrandIter& rOther);

   // GROUP: ACCESS
   // GROUP: INQUIRY
};

// INLINE METHODS
//

// EXTERNAL REFERENCES
//

#endif // INCLUDED_LRFD_STRANDPOOL_H_
