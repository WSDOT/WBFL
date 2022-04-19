///////////////////////////////////////////////////////////////////////
// GeomModel - Geometric Modeling of shapes and sections
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

#ifndef INCLUDED_GEOMETRY_MOHRCIRCLE_H_
#define INCLUDED_GEOMETRY_MOHRCIRCLE_H_
#pragma once

/// Mohr's Circle.
/// This is a privately implemented Mohr's circle object in this DLL.
/// This is the exact same implementation as in the WBFL::EngTools library
/// Reuse of this tiny class is not sufficient reason to have this library depend on WBFL::EngTools
///
/// REFERENCES
///   Advanced Strength and Applied Elasticity
///   A.C. Ugural & S. K. Fenster

class MohrCircle
{
public:
   MohrCircle();
   MohrCircle(Float64 sii, Float64 sjj, Float64 sij);
   MohrCircle(const MohrCircle& rOther) = default;
   ~MohrCircle();

   MohrCircle& operator=(const MohrCircle& rOther) = default;

   /// Computes the state of strains/stresses/etc. on a plane defined by
   /// angle. Angle is in radians and measured
   /// counterclockwise from the global X direction.
   void ComputeState(Float64 angle,Float64& sii, Float64& sjj, Float64& sij) const;

   void SetSii(Float64 sii);
   Float64 GetSii() const { return m_Sii; }

   void SetSjj(Float64 sjj);
   Float64 GetSjj() const { return m_Sjj; }

   void SetSij(Float64 sij);
   Float64 GetSij() const { return m_Sij; }

   /// Returns the maximum principal value.
   Float64 GetSmax() const;

   /// Returns the minimum principal value.
   Float64 GetSmin() const;

   /// Returns the maximum "shear" value.
   Float64 GetTmax() const;

   /// Returns the direction of the principal axis measured counterclockwise
   /// from the global X axis, measured in radians.
   Float64 GetPrincipalDirection() const;

   /// Returns the center point of the mohr's circle.
   Float64 GetCenter() const;

   /// Returns the radius of the mohr's circle.
   Float64 GetRadius() const;

#if defined _DEBUG
   bool AssertValid() const;
   void Dump(dbgDumpContext& os) const;
#endif // _DEBUG

#if defined _UNITTEST
   static bool TestMe(dbgLog& rlog);
#endif // _UNITTEST

private:
   Float64 m_Sii;  // input variables
   Float64 m_Sjj;
   Float64 m_Sij;

   Float64 m_Smin;
   Float64 m_Smax;
   // Note: Internal principal angle is stored in clockwise direction.
   Float64 m_Angle;
   Float64 m_Radius;
   Float64 m_Center;

   void Init();
};

#endif // INCLUDED_GEOMETRY_MOHRCIRCLE_H_

