///////////////////////////////////////////////////////////////////////
// LRFD - Utility library to support equations, methods, and procedures
//        from the AASHTO LRFD Bridge Design Specification
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

#ifndef INCLUDED_LRFD_REBARPOOL_H_
#define INCLUDED_LRFD_REBARPOOL_H_
#pragma once

// SYSTEM INCLUDES
//

#include <Lrfd\LrfdExp.h>
#include <Material\Rebar.h>
#include <map>
#include <System\SingletonKiller.h>
#include <boost\shared_ptr.hpp>

// PROJECT INCLUDES
//

// LOCAL INCLUDES
//

// FORWARD DECLARATIONS
//
class lrfdRebarIter;

// MISCELLANEOUS
//

/*****************************************************************************
CLASS 
   lrfdRebarPool

   Flyweight pool for mild steel reinforcement bars.


DESCRIPTION
   Flyweight pool for mild steel reinforcement bars.  All of the bars described in
   AASHTO M31 are stored in this flyweight pool.

   All rebar are Grade 60.


COPYRIGHT
   Copyright (c) 1998
   Washington State Department Of Transportation
   All Rights Reserved

LOG
   rab : 07.10.1998 : Created file
*****************************************************************************/

class LRFDCLASS lrfdRebarPool
{
public:
   // GROUP: LIFECYCLE
   // GROUP: OPERATORS
   // GROUP: OPERATIONS
   // GROUP: ACCESS

   //------------------------------------------------------------------------
   // Returns a pointer to an instance of the rebar pool.
   static lrfdRebarPool* GetInstance();


   //------------------------------------------------------------------------
   const matRebar* GetRebar(Int32 key);

   //------------------------------------------------------------------------
   const matRebar* GetRebar(matRebar::Type type,
                                matRebar::Grade grade,
                                matRebar::Size size );

   //------------------------------------------------------------------------
   // Returns the lookup key for pRebar.  If pRebar is not a member of
   // the rebar pool, returns -1
   Int32 GetRebarKey(const matRebar* pRebar);

   static bool MapOldRebarKey(Int32 oldKey,matRebar::Grade& grade,matRebar::Type& type,matRebar::Size& size);

   static std::_tstring GetMaterialName(matRebar::Type type,matRebar::Grade grade);
   static std::_tstring GetBarSize(matRebar::Size size);
   static matRebar::Size GetBarSize(LPCTSTR strSize);

   static void GetBarSizeRange(matRebar::Type type,matRebar::Grade grade,matRebar::Size& minSize,matRebar::Size& maxSize);
   static void GetTransverseBarSizeRange(matRebar::Type type,matRebar::Grade grade,matRebar::Size& minSize,matRebar::Size& maxSize);

   // GROUP: INQUIRY
   // GROUP: DEBUG
#if defined _DEBUG
   //------------------------------------------------------------------------
   // Returns <b>true</b> if the class is in a valid state, otherwise returns
   // <b>false</b>.
   virtual bool AssertValid() const;

   //------------------------------------------------------------------------
   // Dumps the contents of the class to the given stream.
   virtual void Dump(dbgDumpContext& os) const;
#endif // _DEBUG

#if defined _UNITTEST
   //------------------------------------------------------------------------
   static bool TestMe(dbgLog& rlog);
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
   static lrfdRebarPool* ms_pInstance;
   typedef std::map<Int32,boost::shared_ptr<matRebar> > RebarPool;
   static RebarPool ms_Rebar;

   typedef sysSingletonKillerT<lrfdRebarPool> Killer;
   friend Killer;
   static Killer ms_Killer;

   // GROUP: LIFECYCLE

   //------------------------------------------------------------------------
   // Default constructor
   lrfdRebarPool();

   // Prevent accidental copying and assignment
   lrfdRebarPool(const lrfdRebarPool&);
   lrfdRebarPool& operator=(const lrfdRebarPool&);

   //------------------------------------------------------------------------
   virtual ~lrfdRebarPool();

   // GROUP: OPERATORS
   // GROUP: OPERATIONS
   // GROUP: ACCESS
   // GROUP: INQUIRY

   friend lrfdRebarIter;
};


/*****************************************************************************
CLASS 
   lrfdRebarIter

   Iterates over the various rebar sizes stored in lrfdRebarPool.


DESCRIPTION
   Iterates over the various rebar sizes stored in lrfdRebarPool.


COPYRIGHT
   Copyright (c) 1998
   Washington State Department Of Transportation
   All Rights Reserved

LOG
   rab : 07.10.1998 : Created file
*****************************************************************************/

class LRFDCLASS lrfdRebarIter
{
public:
   // GROUP: LIFECYCLE

   //------------------------------------------------------------------------
   // Default constructor
   lrfdRebarIter(matRebar::Type type = matRebar::A615,matRebar::Grade grade = matRebar::Grade60,bool bTransverseBarsOnly=false);

   //------------------------------------------------------------------------
   lrfdRebarIter(const lrfdRebarIter& rOther);

   //------------------------------------------------------------------------
   // Destructor
   ~lrfdRebarIter();

   // GROUP: OPERATORS
   //------------------------------------------------------------------------
   lrfdRebarIter& operator=(const lrfdRebarIter& rOther);

   // GROUP: OPERATIONS

   //------------------------------------------------------------------------
   virtual void Begin();

   //------------------------------------------------------------------------
   virtual void End();

   //------------------------------------------------------------------------
   virtual void Next();

   //------------------------------------------------------------------------
   virtual void Move(Int32 pos);

   //------------------------------------------------------------------------
   virtual void MoveBy(Int32 dPos);

   //------------------------------------------------------------------------
   operator void*() const;

   //------------------------------------------------------------------------
   const matRebar* GetCurrentRebar() const;

   // GROUP: ACCESS

   //------------------------------------------------------------------------
   // Sets the grade of prestress steel for which the available sizes will
   // be iterated over. Sets the iterator to the first element in the
   // iteration sequence.
   void SetGrade(matRebar::Grade grade);

   //------------------------------------------------------------------------
   // Returns the grade of prestress steel for which the available sizes
   // are being iterated over.
   matRebar::Grade GetGrade() const;

   //------------------------------------------------------------------------
   // Sets the type of prestress steel for which the available sizes will
   // be iterated over. Sets the iterator to the first element in the
   // iteration sequence.
   void SetType(matRebar::Type type);

   //------------------------------------------------------------------------
   // Returns the type of prestress steel for which the available sizes
   // are being iterated over.
   matRebar::Type GetType() const;

   // GROUP: INQUIRY
   // GROUP: DEBUG
#if defined _DEBUG
   //------------------------------------------------------------------------
   // Returns <b>true</b> if the class is in a valid state, otherwise returns
   // <b>false</b>.
   virtual bool AssertValid() const;

   //------------------------------------------------------------------------
   // Dumps the contents of the class to the given stream.
   virtual void Dump(dbgDumpContext& os) const;
#endif // _DEBUG

#if defined _UNITTEST
   //------------------------------------------------------------------------
   static bool TestMe(dbgLog& rlog);
#endif // _UNITTEST


protected:
   // GROUP: DATA MEMBERS
   // GROUP: LIFECYCLE
   // GROUP: OPERATORS
   // GROUP: OPERATIONS
   virtual void MakeAssignment(const lrfdRebarIter& rOther);

   // GROUP: ACCESS
   // GROUP: INQUIRY

private:
   // GROUP: DATA MEMBERS
   std::vector< const matRebar* > m_Bars;
   std::vector< const matRebar* >::iterator m_Begin;
   std::vector< const matRebar* >::iterator m_End;
   std::vector< const matRebar* >::iterator m_Current;
   matRebar::Grade m_Grade;
   matRebar::Type m_Type;
   bool m_bTransverseBarsOnly;

   // GROUP: LIFECYCLE
   // GROUP: OPERATORS
   // GROUP: OPERATIONS
   void SetRange();
   void MakeCopy(const lrfdRebarIter& rOther);

   // GROUP: ACCESS
   // GROUP: INQUIRY
};

// INLINE METHODS
//

// EXTERNAL REFERENCES
//

#endif // INCLUDED_LRFD_REBARPOOL_H_
