///////////////////////////////////////////////////////////////////////
// FEA2D - Two-dimensional Finite Element Analysis Engine
// Copyright � 1999-2026  Washington State Department of Transportation
//                        Bridge and Structures Office
///////////////////////////////////////////////////////////////////////
// TestPOI.cpp
//
// Mirrors Fem2d\Fem2dUnitTests\TestPOI.cpp.
#include "pch.h"

namespace FEA2DUnitTests
{

TEST_CLASS(TestPOI)
{
public:
   TEST_METHOD(BasicPOIOperations)
   {
      Model model;
      model.CreateJoint(0, 2, 3);
      model.CreateJoint(2, 22, 32);
      model.CreateJoint(4, 44, 34);
      model.CreateJoint(5, 55, 35);

      model.CreateMember(0, 0, 2, 100, 105);
      model.CreateMember(3, 2, 5, 110, 115);
      model.CreateMember(4, 54, 5, 110, 115); // joint doesn't exist - allowed at create time

      POI& pPOI0 = model.CreatePOI(0, 1, -.5); // member 1 doesn't exist either - also allowed
      POI& pPOI3 = model.CreatePOI(3, 4, 1.2);
      ASSERT_THROWS(model.CreatePOI(3, 4, 1.2), ReasonCode::PoiWithIdAlreadyExists);
      ASSERT_THROWS(model.CreatePOI(4, 4, -12.0), ReasonCode::InvalidPoiLocation);

      ASSERT_EQ(pPOI0.GetID(), 0);
      ASSERT_EQ(pPOI3.GetID(), 3);
      ASSERT_EQ(pPOI0.GetMemberID(), 1);
      ASSERT_EQ(pPOI3.GetMemberID(), 4);

      pPOI3.SetMemberID(33);
      ASSERT_EQ(pPOI3.GetMemberID(), 33);

      ASSERT_EQ(pPOI0.GetLocation(), -0.5);
      ASSERT_EQ(pPOI3.GetLocation(), 1.2);

      pPOI3.SetLocation(23.3);
      ASSERT_EQ(pPOI3.GetLocation(), 23.3);

      pPOI3.SetLocation(-1.0);
      ASSERT_THROWS(pPOI3.SetLocation(-1.01), ReasonCode::InvalidPoiLocation);
   }
};
} // namespace FEA2DUnitTests
