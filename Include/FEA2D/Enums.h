///////////////////////////////////////////////////////////////////////
// FEA2D - Two-dimensional Finite Element Analysis Engine
// Copyright © 1999-2026  Washington State Department of Transportation
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

#pragma once

// These enum classes are the mechanism that keeps the core numerics free of
// COM: FEA2D never includes the generated WBFLFem2d.h/WBFLFem2d_i.c. Their
// member names and integer values are kept numerically identical to the
// corresponding enums in the Fem2d COM facade's WBFLFem2d.idl, so that
// facade (which depends on FEA2D, not the other way around) can translate
// between the two with a plain static_cast instead of a lookup table.

namespace WBFL
{
   namespace FEA2D
   {
      /// How a joint/member/etc. collection is accessed - by sequential
      /// index or by ID.
      enum class AccessType
      {
         Index = 0,
         ID = 1
      };

      /// Member end release condition.
      enum class MemberReleaseType
      {
         None = 0,
         Mz = 1,
         Fx = 2
      };

      /// Which end of a member.
      enum class MemberEndType
      {
         Start = 0,
         End = 1
      };

      /// Joint release/support condition (bit flags).
      enum class JointReleaseType
      {
         None = 0,
         Fx = 1,
         Fy = 2,
         Mz = 4,
         All = 7
      };

      /// Coordinate system a load or result is expressed in.
      enum class LoadOrientation
      {
         Global = 0,
         Member = 1,
         GlobalProjected = 2
      };

      /// Direction a distributed load acts in.
      enum class LoadDirection
      {
         Fx = 0,
         Fy = 1
      };

      /// Which face of a member/POI a result is computed on (for
      /// discontinuities at concentrated loads).
      enum class MemberFaceType
      {
         Left = 0,
         Right = 1
      };

      /// Joint-level degree of freedom, for the scripting-client result
      /// surface.
      enum class JointDOF
      {
         Dx = 0,
         Dy = 1,
         Rz = 2
      };

      /// Member-level degree of freedom (start/end x/y/rotation), for the
      /// scripting-client result surface.
      enum class MemberDOF
      {
         DxStart = 0,
         DyStart = 1,
         RzStart = 2,
         DxEnd = 3,
         DyEnd = 4,
         RzEnd = 5
      };
   };
};
