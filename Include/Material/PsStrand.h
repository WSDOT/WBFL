///////////////////////////////////////////////////////////////////////
// Material - Analytical and Product modeling of civil engineering materials
// Copyright © 1999-2017  Washington State Department of Transportation
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

#ifndef INCLUDED_MATERIAL_PSSTRAND_H_
#define INCLUDED_MATERIAL_PSSTRAND_H_
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
   matPsStrand

   Prestress strand steel product model.


DESCRIPTION
   Prestress strand steel product model. This product model is modeled after
   AASHTO M203

LOG
   rab : 11.17.1997 : Created file
*****************************************************************************/

class MATCLASS matPsStrand
{
public:
   // GROUP: ENUMERATIONS

   //------------------------------------------------------------------------
   enum Grade { Gr1725 = 0x0001, 
                Gr1860 = 0x0002 };

   //------------------------------------------------------------------------
   enum Type { LowRelaxation  = 0x0004, 
               StressRelieved = 0x0008};

   //------------------------------------------------------------------------
   enum Size { D635  = 0x0010,// 1/4"
               D794  = 0x0020,// 5/16"
               D953  = 0x0040,// 3/8"
               D1111 = 0x0080,// 7/16"
               D1270 = 0x0100,// 1/2"
               D1524 = 0x0200,// 0.6"
               D1778 = 0x0400,// 0.7"
               D1320 = 0x0800,// 1/2 HBS (Special)
               D1575 = 0x1000,// 0.62"
   }; 

   //------------------------------------------------------------------------
   enum Coating { None        = 0x00010000, 
                  SmoothEpoxy = 0x00020000,
                  GritEpoxy   = 0x00040000
   };

   // GROUP: LIFECYCLE

   //------------------------------------------------------------------------
   // Default constructor. Initializes the strand to a .5" Grade 250 low
   // relaxation strand (name is "Unknown").
   matPsStrand();

   //------------------------------------------------------------------------
   // Initializes the object with the supplied parameters.
   matPsStrand(const std::_tstring& name,Grade grade,Type type,Coating coating,Size size,
               Float64 fpu, Float64 fpy, Float64 modE,
               Float64 d, Float64 a);

   //------------------------------------------------------------------------
   // Copy constructor
   matPsStrand(const matPsStrand& rOther);

   //------------------------------------------------------------------------
   // Destructor
   virtual ~matPsStrand();

   // GROUP: OPERATORS
   //------------------------------------------------------------------------
   // Assignment operator
   matPsStrand& operator = (const matPsStrand& rOther);

   //------------------------------------------------------------------------
   // Returns true of the strand material objects are the same, otherwise
   // returns false;
   bool operator==(const matPsStrand& rOther) const;

   //------------------------------------------------------------------------
   // Returns true of the strand material objects are different, otherwise
   // returns false;
   bool operator!=(const matPsStrand& rOther) const;

   // GROUP: OPERATIONS
   // GROUP: ACCESS

   //------------------------------------------------------------------------
   void SetName(const std::_tstring& name);

   //------------------------------------------------------------------------
   std::_tstring GetName() const;

   //------------------------------------------------------------------------
   void SetGrade(Grade grade);

   //------------------------------------------------------------------------
   Grade GetGrade() const;

   //------------------------------------------------------------------------
   void SetType(Type type);

   //------------------------------------------------------------------------
   Type GetType() const;

   //------------------------------------------------------------------------
   void SetSize(Size size);

   //------------------------------------------------------------------------
   Size GetSize() const;

   //------------------------------------------------------------------------
   void SetCoating(Coating coating);

   //------------------------------------------------------------------------
   Coating GetCoating() const;

   //------------------------------------------------------------------------
   void SetNominalDiameter(Float64 d);

   //------------------------------------------------------------------------
   Float64 GetNominalDiameter() const;

   //------------------------------------------------------------------------
   void SetNominalArea(Float64 a);

   //------------------------------------------------------------------------
   Float64 GetNominalArea() const;

   //------------------------------------------------------------------------
   void SetUltimateStrength(Float64 fpu);

   //------------------------------------------------------------------------
   Float64 GetUltimateStrength() const;

   //------------------------------------------------------------------------
   void SetYieldStrength(Float64 fpu);

   //------------------------------------------------------------------------
   Float64 GetYieldStrength() const;

   //------------------------------------------------------------------------
   void SetE(Float64 e);

   //------------------------------------------------------------------------
   Float64 GetE() const;

   static std::_tstring GetSize(matPsStrand::Size size,bool bUnitsUS);

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
   void MakeCopy(const matPsStrand& rOther);

   //------------------------------------------------------------------------
   virtual void MakeAssignment(const matPsStrand& rOther);

   // GROUP: ACCESS
   // GROUP: INQUIRY

private:
   // GROUP: DATA MEMBERS
   std::_tstring m_Name;
   Grade       m_Grade;
   Type        m_Type;
   Size        m_Size;
   Coating     m_Coating;
   Float64     m_Diameter;
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
inline void matPsStrand::SetSize(Size size)
{
   m_Size = size;
}

inline matPsStrand::Size matPsStrand::GetSize() const
{
   return m_Size;
}

inline void matPsStrand::SetCoating(Coating coating)
{
   m_Coating = coating;
}

inline matPsStrand::Coating matPsStrand::GetCoating() const
{
   return m_Coating;
}

inline void matPsStrand::SetNominalDiameter(Float64 d)
{
   m_Diameter = d;
}

inline Float64 matPsStrand::GetNominalDiameter() const
{
   return m_Diameter;
}

inline void matPsStrand::SetNominalArea(Float64 a)
{
   m_Area = a;
}

inline Float64 matPsStrand::GetNominalArea() const
{
   return m_Area;
}

inline void matPsStrand::SetUltimateStrength(Float64 fpu)
{
   m_Fpu = fpu;
}

inline Float64 matPsStrand::GetUltimateStrength() const
{
   return m_Fpu;
}

inline void matPsStrand::SetYieldStrength(Float64 fpy)
{
   m_Fpy = fpy;
}

inline Float64 matPsStrand::GetYieldStrength() const
{
   return m_Fpy;
}

inline void matPsStrand::SetE(Float64 e)
{
   m_ModE = e;
}

inline Float64 matPsStrand::GetE() const
{
   return m_ModE;
}

// EXTERNAL REFERENCES
//

#endif // INCLUDED_MATERIAL_PSSTRAND_H_
