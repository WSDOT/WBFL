///////////////////////////////////////////////////////////////////////
// Material - Analytical and Product modeling of civil engineering materials
// Copyright © 1999-2010  Washington State Department of Transportation
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
   enum ShapeType { Circle, Square };

   // GROUP: LIFECYCLE

   //------------------------------------------------------------------------
   // Default constructor.  Sets name to "Unknown", shape to Circle and all
   // other parameters to zero.
   matRebar();

   //------------------------------------------------------------------------
   // Constructs a new rebar object using the supplied parameters.
   matRebar(const std::_tstring& name,
            Float64 fpu,
            Float64 fpy,
            Float64 modE,
            ShapeType st,
            Float64 nd, // Nominal dimension
            Float64 na ); // Nominal area

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
   void SetShape(ShapeType st);

   //------------------------------------------------------------------------
   ShapeType GetShape() const;

   //------------------------------------------------------------------------
   void SetNominalDimension(Float64 d);
   Float64 GetNominalDimension() const;
   void SetNominalArea(Float64 a);
   Float64 GetNominalArea() const;
   void SetUltimateStrength(Float64 fpu);
   Float64 GetUltimateStrength() const;
   void SetYieldStrength(Float64 fpu);
   Float64 GetYieldStrength() const;
   void SetE(Float64 e);
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
   ShapeType   m_Shape;
   Float64     m_Dimension;
   Float64     m_Area;
   Float64     m_Fpu;
   Float64     m_Fpy;
   Float64     m_ModE;

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

inline void matRebar::SetShape(ShapeType st)
{
   m_Shape = st;
}

inline matRebar::ShapeType matRebar::GetShape() const
{
   return m_Shape;
}

inline void matRebar::SetNominalDimension(Float64 d)
{
   m_Dimension = d;
}

inline Float64 matRebar::GetNominalDimension() const
{
   return m_Dimension;
}

inline void matRebar::SetNominalArea(Float64 a)
{
   m_Area = a;
}

inline Float64 matRebar::GetNominalArea() const
{
   return m_Area;
}

inline void matRebar::SetUltimateStrength(Float64 fpu)
{
   m_Fpu = fpu;
}

inline Float64 matRebar::GetUltimateStrength() const
{
   return m_Fpu;
}

inline void matRebar::SetYieldStrength(Float64 fpy)
{
   m_Fpy = fpy;
}

inline Float64 matRebar::GetYieldStrength() const
{
   return m_Fpy;
}

inline void matRebar::SetE(Float64 e)
{
   m_ModE = e;
}

inline Float64 matRebar::GetE() const
{
   return m_ModE;
}

// EXTERNAL REFERENCES
//

#endif // INCLUDED_MATERIAL_REBAR_H_
