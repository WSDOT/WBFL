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

#ifndef INCLUDED_GEOMMODEL_NUBEAM_H_
#define INCLUDED_GEOMMODEL_NUBEAM_H_
#pragma once

#include <GeomModel/GeomModelExp.h>
#include <GeomModel/FlangedBeam.h>

namespace WBFL
{
   namespace Geometry
   {
class Polygon;

/// Object representing the cross section of a University of Nebraska (NU) precast concrete I-Beam
///
/// \image html NUBeam/NUBeam.jpg    
class GEOMMODELCLASS NUBeam :  public FlangedBeam
{
public:
   NUBeam();

   NUBeam(Float64 w1, Float64 w2, 
            Float64 d1, Float64 d2, Float64 d3, Float64 d4, Float64 d5,
            Float64 t, 
            Float64 r1, Float64 r2, Float64 r3, Float64 r4, Float64 c1, Float64 endBlockWidth,
            std::shared_ptr<Point2d>& hookPnt);

   NUBeam(const NUBeam& other) = default;
   NUBeam& operator=(const NUBeam& other) = default;

   virtual ~NUBeam();


   void SetW1(Float64 w1);
   Float64 GetW1() const;

   void SetW2(Float64 w2);
   Float64 GetW2() const;

   void SetD1(Float64 d1);
   Float64 GetD1() const;

   void SetD2(Float64 d2);
   Float64 GetD2() const;

   void SetD3(Float64 d3);
   Float64 GetD3() const;

   void SetD4(Float64 d4);
   Float64 GetD4() const;

   void SetD5(Float64 d5);
   Float64 GetD5() const;

   void SetT(Float64 t);
   Float64 GetT() const;

   void SetR1(Float64 r1);
   Float64 GetR1() const;

   void SetR2(Float64 r2);
   Float64 GetR2() const;

   void SetR3(Float64 r3);
   Float64 GetR3() const;

   void SetR4(Float64 r4);
   Float64 GetR4() const;

   void SetC1(Float64 c1);
   Float64 GetC1() const;

   /// When the end block width is greater than T, the geometry of
   // the web and the top and bottom flanges are modified so the web of the 
   // girder is equal to the end block width
   void SetEndBlockWidth(Float64 endBlockWidth);
   Float64 GetEndBlockWidth() const;

   /// Translates a shape by a delta amount.
   virtual void DoOffset(const Size2d& delta) override;

   /// Rotates a shape.  The rotation is centered about point center.  The 
   /// rotation angle is measured in radians counter clockwise.
   virtual void DoRotate(const Point2d& center, Float64 angle) override;


   virtual std::unique_ptr<Shape> CreateClone() const override;

   // Flanged Beam overrides
   virtual IndexType GetTopFlangeCount() const override;
   virtual Float64 GetTopFlangeLocation(IndexType flangeIdx) const override;
   virtual Float64 GetTopFlangeWidth(IndexType flangeIdx) const override;
   virtual IndexType GetBottomFlangeCount() const override;
   virtual Float64 GetBottomFlangeLocation(IndexType flangeIdx) const override;
   virtual Float64 GetBottomFlangeWidth(IndexType flangeIdx) const override;
   virtual Float64 GetTopWidth() const override;
   virtual Float64 GetBottomWidth() const override;
   virtual IndexType GetWebCount() const override;
   virtual Plane3d GetWebPlane(WebIndexType webIdx) const override;
   virtual Float64 GetShearWidth() const override;
   virtual Float64 GetAvgWebWidth() const override;
   virtual Float64 GetMinWebWidth() const override;
   virtual Float64 GetHeight() const override;
   virtual Float64 GetMinBottomFlangeThickness() const override;
   virtual Float64 GetMinTopFlangeThickness() const override;
   virtual MatingSurfaceIndexType GetMatingSurfaceCount() const override;
   virtual Float64 GetMatingSurfaceWidth(MatingSurfaceIndexType idx) const override;
   virtual Float64 GetMatingSurfaceLocation(MatingSurfaceIndexType idx) const override;

#if defined _DEBUG
   virtual bool AssertValid() const override;
   virtual void Dump(WBFL::Debug::LogContext& os) const override;
#endif // _DEBUG

#if defined _UNITTEST
   static bool TestMe(WBFL::Debug::Log& rlog);
#endif // _UNITTEST

protected:
   virtual void OnUpdatePolygon(std::unique_ptr<Polygon>& polygon) const override;

private:
   Float64 m_Rotation{ 0.0 };
   Float64 m_D1{ 0.0 };
   Float64 m_D2{ 0.0 };
   Float64 m_D3{ 0.0 };
   Float64 m_D4{ 0.0 };
   Float64 m_D5{ 0.0 };
   Float64 m_T{ 0.0 };
   Float64 m_W1{ 0.0 };
   Float64 m_W2{ 0.0 };
   Float64 m_R1{ 0.0 };
   Float64 m_R2{ 0.0 };
   Float64 m_R3{ 0.0 };
   Float64 m_R4{ 0.0 };
   Float64 m_C1{ 0.0 };
   Float64 m_EndBlockWidth{ 0.0 };
};

   }; // Geometry
}; // WBFL

#endif // INCLUDED_GEOMMODEL_NUBEAM_H_
