///////////////////////////////////////////////////////////////////////
// EngTools - Library of miscellaneous engineering tools
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

#ifndef INCLUDED_ENGTOOLS_BIAXIALBEAMSTRAIN_H_
#define INCLUDED_ENGTOOLS_BIAXIALBEAMSTRAIN_H_
#pragma once

#include <EngTools\EngToolsExp.h>
#include <GeomModel\GeomModel.h>

namespace WBFL
{
   namespace EngTools
   {
/// This class represents a beam strain plane in x-y space
class ENGTOOLSCLASS BiaxialBeamStrain
{
public:
   BiaxialBeamStrain(Float64 strain=0.0);


   BiaxialBeamStrain(const WBFL::Geometry::Point2d& p1, Float64 s1, 
                       const WBFL::Geometry::Point2d& p2, Float64 s2,
                       const WBFL::Geometry::Point2d& p3, Float64 s3);

   BiaxialBeamStrain(const WBFL::Geometry::Line2d& rnaLine,
                       const WBFL::Geometry::Point2d& p3,Float64 strain);

   BiaxialBeamStrain(const WBFL::Geometry::Line2d& rnaLine,
      Float64 dist, Float64 strain);


   ~BiaxialBeamStrain();
   
   BiaxialBeamStrain(const BiaxialBeamStrain& rOther) = default;
   BiaxialBeamStrain& operator=(const BiaxialBeamStrain& rOther) = default;

   Float64 GetAxialStrain(Float64 x, Float64 y) const;
   Float64 GetAxialStrain(const WBFL::Geometry::Point2d& pnt) const;

   Float64 GetXStrainLocation(Float64 Strain, Float64 Y, bool& success) const;
   Float64 GetYStrainLocation(Float64 Strain, Float64 X, bool& success) const;

   void SetStrainPlane(const WBFL::Geometry::Line2d& rnaLine,
                       const WBFL::Geometry::Point2d& p3,Float64 strain);

   void SetStrainPlane(const WBFL::Geometry::Point2d& p1, Float64 s1,
                       const WBFL::Geometry::Point2d& p2, Float64 s2,
                       const WBFL::Geometry::Point2d& p3, Float64 s3);

   void SetStrainPlane(const WBFL::Geometry::Line2d& rnaLine,
                       Float64 dist, Float64 strain);

   void SetStrainPlane(Float64 strain);

#if defined _DEBUG
   bool AssertValid() const;
   void Dump(WBFL::Debug::LogContext& os) const;
#endif // _DEBUG

#if defined _UNITTEST
   static bool TestMe();
#endif // _UNITTEST

private:
   void Update(const WBFL::Geometry::Point2d& p1, Float64 s1,
               const WBFL::Geometry::Point2d& p2, Float64 s2,
               const WBFL::Geometry::Point2d& p3, Float64 s3);

   Float64 m_A{ 0 };
   Float64 m_B{ 0 };
   Float64 m_C{ 0 };
   Float64 m_D{ 0 };
   bool    m_bIsConstantStrain{ true };
};

   } // EngTools
} // WBFL

#endif //INCLUDED_ENGTOOLS_BIAXIALBEAMSTRAIN_H_
