///////////////////////////////////////////////////////////////////////
// Material - Analytical and Product modeling of civil engineering materials
// Copyright © 1999-2011  Washington State Department of Transportation
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

#ifndef INCLUDED_MATERIAL_REBAR_H_
#define INCLUDED_MATERIAL_REBAR_H_
#pragma once

// SYSTEM INCLUDES
//

// PROJECT INCLUDES
//
#include <Material\MaterialExp.h>

// LOCAL INCLUDES
//

// FORWARD DECLARATIONS
//

// MISCELLANEOUS
//

/*****************************************************************************
CLASS 
   matRebar

   Product model for mild steel reinforcement (rebar).  Reinforcement bars
   may be circular or square.


DESCRIPTION
   Product model for mild steel reinforcement (rebar).  Reinforcement bars
   may be circular or square.


COPYRIGHT
   Copyright (c) 1997
   Washington State Department Of Transportation
   All Rights Reserved

LOG
   rab : 01.28.1998 : Created file
*****************************************************************************/

class MATCLASS matRebar
{
public:
   // GROUP: ENUMERATIONS

   //------------------------------------------------------------------------
   enum Size { bs3  = 0x0001,
               bs4  = 0x0002,
               bs5  = 0x0004,
               bs6  = 0x0008,
               bs7  = 0x0010,
               bs8  = 0x0020,
               bs9  = 0x0040,
               bs10 = 0x0080,
               bs11 = 0x0100,
               bs14 = 0x0200,
               bs18 = 0x0400,
               bsNone = 0x0FFF
   }; 

   //------------------------------------------------------------------------
   enum Type { A615   = 0x1000,  // A615
               A706 = 0x2000}; // A706

   //------------------------------------------------------------------------
   enum Grade { Grade40 = 0x00010000, 
                Grade60 = 0x00020000,
                Grade75 = 0x00040000,
                Grade80 = 0x00080000,
   };

   // GROUP: LIFECYCLE

   //------------------------------------------------------------------------
   // Default constructor.  Sets name to "Unknown", shape to Circle and all
   // other parameters to zero.
   matRebar();

   //------------------------------------------------------------------------
   // Constructs a new rebar object using the supplied parameters.
   matRebar(const std::_tstring& name,
            Grade grade,
            Type type,
            Size size);

   //------------------------------------------------------------------------
   // Copy constructor
   matRebar(const matRebar& rOther);

   //------------------------------------------------------------------------
   // Destructor
   virtual ~matRebar();

   // GROUP: OPERATORS

   //------------------------------------------------------------------------
   // Assignment operator
   matRebar& operator = (const matRebar& rOther);

   // GROUP: OPERATIONS
   // GROUP: ACCESS

   //------------------------------------------------------------------------
   void SetName(const std::_tstring& name);

   //------------------------------------------------------------------------
   std::_tstring GetName() const;

   //------------------------------------------------------------------------
   void SetSize(Size size);

   //------------------------------------------------------------------------
   Size GetSize() const;

   //------------------------------------------------------------------------
   void SetGrade(Grade grade);

   //------------------------------------------------------------------------
   Grade GetGrade() const;

   //------------------------------------------------------------------------
   void SetType(Type type);

   //------------------------------------------------------------------------
   Type GetType() const;

   //------------------------------------------------------------------------
   Float64 GetNominalDimension() const;
   Float64 GetNominalArea() const;
   Float64 GetUltimateStrength() const;
   Float64 GetYieldStrength() const;
   Float64 GetE() const;

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
   // Self-diagnostic test function.  Returns <b>true</b> if the test passes,
   // otherwise return <b>false</b>.
   static bool TestMe(dbgLog& rlog);
#endif // _UNITTEST

protected:
   // GROUP: DATA MEMBERS
   // GROUP: LIFECYCLE
   // GROUP: OPERATORS
   // GROUP: OPERATIONS
   //------------------------------------------------------------------------
   void MakeCopy(const matRebar& rOther);

   //------------------------------------------------------------------------
   void MakeAssignment(const matRebar& rOther);

   // GROUP: ACCESS
   // GROUP: INQUIRY

private:
   // GROUP: DATA MEMBERS
   std::_tstring m_Name;
   Size m_Size;
   Grade m_Grade;
   Type m_Type;
   Float64     m_Dimension;
   Float64     m_Area;
   Float64     m_Fu;
   Float64     m_Fy;
   Float64     m_Es;

   // GROUP: LIFECYCLE
   // GROUP: OPERATORS
   // GROUP: OPERATIONS
   // GROUP: ACCESS
   // GROUP: INQUIRY
};

// INLINE METHODS
//

inline void matRebar::SetName(const std::_tstring& name)
{
   m_Name = name;
}

inline std::_tstring matRebar::GetName() const
{
   return m_Name;
}

inline void matRebar::SetType(Type type)
{
   m_Type = type;
}

inline matRebar::Type matRebar::GetType() const
{
   return m_Type;
}

inline void matRebar::SetGrade(Grade grade)
{
   m_Grade = grade;
}

inline matRebar::Grade matRebar::GetGrade() const
{
   return m_Grade;
}

inline void matRebar::SetSize(Size size)
{
   m_Size = size;
}

inline matRebar::Size matRebar::GetSize() const
{
   return m_Size;
}

inline Float64 matRebar::GetNominalDimension() const
{
   return m_Dimension;
}

inline Float64 matRebar::GetNominalArea() const
{
   return m_Area;
}

inline Float64 matRebar::GetUltimateStrength() const
{
   return m_Fu;
}

inline Float64 matRebar::GetYieldStrength() const
{
   return m_Fy;
}

inline Float64 matRebar::GetE() const
{
   return m_Es;
}

// EXTERNAL REFERENCES
//

#endif // INCLUDED_MATERIAL_REBAR_H_
