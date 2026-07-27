///////////////////////////////////////////////////////////////////////
// Fem2D - Two-dimensional Beam Analysis Engine
// Copyright � 1999-2026  Washington State Department of Transportation
//                        Bridge and Structures Office
//
// This library is a part of the Washington Bridge Foundation Libraries
// and was developed as part of the Alternate Route Project
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the Alternate Route Library Open Source License as
// published by the Washington State Department of Transportation,
// Bridge and Structures Office.
//
// This program is distributed in the hope that it will be useful,
// but is distributed AS IS, WITHOUT ANY WARRANTY; without even the
// implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
// PURPOSE.  See the Alternate Route Library Open Source License for more details.
//
// You should have received a copy of the Alternate Route Library Open Source License
// along with this program; if not, write to the Washington State
// Department of Transportation, Bridge and Structures Office,
// P.O. Box 47340, Olympia, WA 98503, USA or e-mail
// Bridge_Support@wsdot.wa.gov
///////////////////////////////////////////////////////////////////////

// Internal implementation detail. PointLoad, DistributedLoad, and
// MemberStrain each implement this pure-virtual interface via a private
// companion object (see the Pimpl design note in PointLoad.h); Member only
// ever talks to its applied loads through this interface.

#pragma once

#include <WBFLTypes.h>
#include <FEA2D\Enums.h>

namespace WBFL
{
   namespace FEA2D
   {
      namespace Internals
      {
         // pure virtual class for defining member loads to members
         class MbrLoad
         {
         public:
            virtual void GetForceVector(long leftBC,long rightBC,Float64 Length,Float64 Angle,Float64 *vector) = 0;
            virtual void GetInternalForces(Float64 x,Float64 Length,Float64 Angle,WBFL::FEA2D::MemberFaceType face,Float64* pFx,Float64* pFy,Float64* pMz) = 0;
            virtual void GetDispVector(long leftBC,long rightBC,Float64 Length,Float64 Angle,Float64 EA, Float64 EI,Float64 *vector) = 0;
            virtual void GetDeflection(Float64 x,long leftBC,long rightBC,Float64 Length,Float64 Angle,
                                         Float64 EA,Float64 EI,
                                         Float64* pdx,Float64* pdy,Float64* prz) = 0;
            virtual void GetOriginForces(Float64 Length,Float64 Angle,Float64* pFx,Float64* pFy,Float64* pMz) = 0;
            virtual ~MbrLoad() = default;
         };
      };
   };
};
