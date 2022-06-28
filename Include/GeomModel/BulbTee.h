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

#ifndef INCLUDED_GEOMMODEL_BULBTEE_H_
#define INCLUDED_GEOMMODEL_BULBTEE_H_
#pragma once

#include <GeomModel/GeomModelExp.h>
#include <GeomModel/FlangedBeam.h>

namespace WBFL
{
   namespace Geometry
   {
/// Object representing the cross section of a deck bulb tee girder
///
/// \image html BulbTee/BulbTee2.png   
class GEOMMODELCLASS BulbTee : public FlangedBeam
{
public:
   BulbTee();
   BulbTee(Float64 w1, Float64 w2, Float64 w3, Float64 w4, Float64 w5, Float64 w6,
      Float64 d1, Float64 d2, Float64 d3, Float64 d4, Float64 d5, Float64 d6, Float64 d7,
      Float64 t1, Float64 t2, Float64 c1, Float64 c2, Float64 n1, Float64 n2,const Point2d& hookPnt = Point2d(0,0));
   BulbTee(const BulbTee& rOther) = default;
   virtual ~BulbTee();

   BulbTee& BulbTee::operator= (const BulbTee& rOther) = default;

   void SetW1(Float64 w1);
   Float64 GetW1() const;

   void SetW2(Float64 w2);
   Float64 GetW2() const;

   void SetW3(Float64 w3);
   Float64 GetW3() const;

   void SetW4(Float64 w4);
   Float64 GetW4() const;

   void SetW5(Float64 w5);
   Float64 GetW5() const;

   void SetW6(Float64 w6);
   Float64 GetW6() const;

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

   void SetD6(Float64 d6);
   Float64 GetD6() const;

   void SetD7(Float64 d7);
   Float64 GetD7() const;

   void SetT1(Float64 f1);
   Float64 GetT1() const;

   void SetT2(Float64 t2);
   Float64 GetT2() const;

   void SetC1(Float64 c1);
   Float64 GetC1() const;

   void SetC2(Float64 c2);
   Float64 GetC2() const;

   void SetN1(Float64 n1);
   Float64 GetN1() const;

   void SetN2(Float64 n2);
   Float64 GetN2() const;

   /// Returns the least overall height of the beam
   Float64 GetMinHeight() const;
   /// Returns the greatest overall height of the beam
   Float64 GetMaxHeight() const;
   /// Returns the nominal CL height of the beam at the CL of the web
   Float64 GetCLHeight() const;

   /// \image html BulbTee/TopFlangePoints.png   
   void GetTopFlangePoints(Point2d* leftTop, Point2d* leftBottom, Point2d* topCL, Point2d* topCentral, Point2d* rightTop, Point2d* rightBottom) const;

   /// \image html BulbTee/BottomFlangePoints.png   
   void GetBottomFlangePoints(Point2d* leftTop, Point2d* leftBottom, Point2d* rightTop, Point2d* rightBottom) const;

   void GetTopFlangeThickness(Float64* Hl, Float64* Hcl, Float64* Hr) const;

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
   virtual bool AssertValid() const;
   virtual void Dump(WBFL::Debug::LogContext& os) const;
#endif // _DEBUG

#if defined _UNITTEST
   static bool TestMe(WBFL::Debug::Log& rlog);

#endif // _UNITTEST

protected:
   virtual void OnUpdatePolygon(std::unique_ptr<Polygon>& polygon) const override;

private:
   Float64   m_Rotation{ 0.0 };
   Float64   m_C1{ 0.0 };
   Float64   m_C2{ 0.0 };
   Float64   m_D1{ 0.0 };
   Float64   m_D2{ 0.0 };
   Float64   m_D3{ 0.0 };
   Float64   m_D4{ 0.0 };
   Float64   m_D5{ 0.0 };
   Float64   m_D6{ 0.0 };
   Float64   m_D7{ 0.0 };
   Float64   m_T1{ 0.0 };
   Float64   m_T2{ 0.0 };
   Float64   m_W1{ 0.0 };
   Float64   m_W2{ 0.0 };
   Float64   m_W3{ 0.0 };
   Float64   m_W4{ 0.0 };
   Float64   m_W5{ 0.0 };
   Float64   m_W6{ 0.0 };
   Float64   m_N1{ 0.0 };
   Float64   m_N2{ 0.0 };

   void GetHeight(Float64* Hl, Float64* Hc, Float64* Hr) const;
};

   }; // Geometry
}; // WBFL

#endif // INCLUDED_GEOMMODEL_BULBTEE_H_
