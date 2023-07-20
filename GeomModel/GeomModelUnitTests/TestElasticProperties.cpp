#include "pch.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace WBFL::Geometry;

namespace GeomModelUnitTest
{
	TEST_CLASS(TestElasticProperties)
	{
	public:
      TEST_METHOD(Test)
      {
         // try a point area
         ElasticProperties gpa(4., Point2d(0, 0), 0., 0., 0, 0, 0, 0, 0);
         Assert::IsTrue(gpa.GetCoordinateSystem() == ElasticProperties::CoordinateSystemType::Centroidal);
         Assert::IsTrue(Point2d(0, 0) == gpa.GetCentroid());
         Assert::IsTrue(IsZero(4 - gpa.GetEA()));
         Assert::IsTrue(IsZero(gpa.GetEI11()));
         Assert::IsTrue(IsZero(gpa.GetEI22()));
         Assert::IsTrue(IsZero(gpa.GetEIxy()));
         Assert::IsTrue(IsZero(gpa.GetEI12Max()));
         Assert::IsTrue(IsZero(gpa.GetEI12Min()));
         Assert::IsTrue(IsZero(gpa.GetYtop()));
         Assert::IsTrue(IsZero(gpa.GetYbottom()));
         Assert::IsTrue(IsZero(gpa.GetXright()));
         Assert::IsTrue(IsZero(gpa.GetXleft()));

         // move origin
         Point2d orn(4, -2);
         gpa.SetOrigin(orn);
         Assert::IsTrue(gpa.GetCoordinateSystem() == ElasticProperties::CoordinateSystemType::UserDefined);
         Assert::IsTrue(Point2d(-4, 2) == gpa.GetCentroid());
         Assert::IsTrue(IsZero(4 - gpa.GetEA()));
         Assert::IsTrue(IsZero(-63.43 - ToDegrees(gpa.GetPrincipalDirection()), .1));
         Assert::IsTrue(IsZero(16 - gpa.GetEIxx()));
         Assert::IsTrue(IsZero(64 - gpa.GetEIyy()));
         Assert::IsTrue(IsZero(32 + gpa.GetEIxy()));
         Assert::IsTrue(IsZero(80 - gpa.GetEI11()));
         Assert::IsTrue(IsZero(gpa.GetEI22()));
         Assert::IsTrue(IsZero(40 - gpa.GetEI12Max()));
         Assert::IsTrue(IsZero(40 + gpa.GetEI12Min()));
         Assert::IsTrue(IsZero(gpa.GetYtop()));
         Assert::IsTrue(IsZero(gpa.GetYbottom()));
         Assert::IsTrue(IsZero(gpa.GetXright()));
         Assert::IsTrue(IsZero(gpa.GetXleft()));

         // rotate 90 deg
         gpa.SetOrientation(M_PI / 2);
         Assert::IsTrue(gpa.GetCoordinateSystem() == ElasticProperties::CoordinateSystemType::UserDefined);
         Assert::IsTrue(Point2d(2, 4) == gpa.GetCentroid());
         Assert::IsTrue(IsZero(4 - gpa.GetEA()));
         Assert::IsTrue(IsZero(64 - gpa.GetEIxx()));
         Assert::IsTrue(IsZero(16 - gpa.GetEIyy()));
         Assert::IsTrue(IsZero(32 - gpa.GetEIxy()));
         Assert::IsTrue(IsZero(80. - gpa.GetEI11()));
         Assert::IsTrue(IsZero(gpa.GetEI22()));
         Assert::IsTrue(IsZero(40 - gpa.GetEI12Max()));
         Assert::IsTrue(IsZero(40 + gpa.GetEI12Min()));
      }

      TEST_METHOD(Rectangle)
      {
         // try a 2x4 rectangle
         ElasticProperties gs2x4(8., Point2d(0, 0), 128. / 12., 32. / 12., 0, 1, 2, 1, 2);
         Assert::IsTrue(IsZero(8 - gs2x4.GetEA()));
         Assert::IsTrue(IsZero(128. / 12. - gs2x4.GetEI11()));
         Assert::IsTrue(IsZero(32. / 12 - gs2x4.GetEI22()));
         Assert::IsTrue(IsZero(gs2x4.GetEIxy()));
         Assert::IsTrue(IsZero(4 - gs2x4.GetEI12Max()));
         Assert::IsTrue(IsZero(4 + gs2x4.GetEI12Min()));
         Assert::IsTrue(IsZero(2 - gs2x4.GetYtop()));
         Assert::IsTrue(IsZero(2 - gs2x4.GetYbottom()));
         Assert::IsTrue(IsZero(1 - gs2x4.GetXright()));
         Assert::IsTrue(IsZero(1 - gs2x4.GetXleft()));

         // move origin to user-defined location
         Point2d orn(4, -2);
         gs2x4.SetOrigin(orn);
         Assert::IsTrue(IsZero(8 - gs2x4.GetEA()));
         Assert::IsTrue(IsZero((128. / 12. + 32) - gs2x4.GetEIxx()));
         Assert::IsTrue(IsZero((32. / 12 + 128) - gs2x4.GetEIyy()));
         Assert::IsTrue(IsZero(64 + gs2x4.GetEIxy()));
         Assert::IsTrue(IsZero(-62.25 - ToDegrees(gs2x4.GetPrincipalDirection()), .01));
         Assert::IsTrue(IsZero(77.67 - gs2x4.GetEI12Max(), .01));
         Assert::IsTrue(IsZero(2 - gs2x4.GetYtop()));
         Assert::IsTrue(IsZero(2 - gs2x4.GetYbottom()));
         Assert::IsTrue(IsZero(1 - gs2x4.GetXright()));
         Assert::IsTrue(IsZero(1 - gs2x4.GetXleft()));

         // move origin back to centroid
         gs2x4.SetCoordinateSystem(ElasticProperties::CoordinateSystemType::Centroidal);
         Assert::IsTrue(gs2x4.GetCoordinateSystem() == ElasticProperties::CoordinateSystemType::Centroidal);
         Assert::IsTrue(IsZero(8 - gs2x4.GetEA()));
         Assert::IsTrue(IsZero(128. / 12. - gs2x4.GetEI11()));
         Assert::IsTrue(IsZero(32. / 12 - gs2x4.GetEI22()));
         Assert::IsTrue(IsZero(gs2x4.GetEIxy()));
         Assert::IsTrue(IsZero(4 - gs2x4.GetEI12Max()));
         Assert::IsTrue(IsZero(4 + gs2x4.GetEI12Min()));
         Assert::IsTrue(IsZero(2 - gs2x4.GetYtop()));
         Assert::IsTrue(IsZero(2 - gs2x4.GetYbottom()));
         Assert::IsTrue(IsZero(1 - gs2x4.GetXright()));
         Assert::IsTrue(IsZero(1 - gs2x4.GetXleft()));
      }

      TEST_METHOD(Rotate)
      {
         // try rotation to principal
         ElasticProperties gsr(4., Point2d(0, 0), 16., 64., -32, 1, 2, 1, 2);
         gsr.SetCoordinateSystem(ElasticProperties::CoordinateSystemType::Principal);
         Assert::IsTrue(gsr.GetCoordinateSystem() == ElasticProperties::CoordinateSystemType::Principal);
         Assert::IsTrue(IsZero(4 - gsr.GetEA()));
         Assert::IsTrue(IsZero(80. - gsr.GetEI11()));
         Assert::IsTrue(IsZero(gsr.GetEI22()));
         Assert::IsTrue(IsZero(gsr.GetEIxy()));
         Assert::IsTrue(IsZero(40 - gsr.GetEI12Max()));
         Assert::IsTrue(IsZero(40 + gsr.GetEI12Min()));
      }

      TEST_METHOD(AddSubtract)
      {
         // try addition and subraction
         ElasticProperties gps1(4., Point2d(4, 2), 0, 0, 0, 0, 0, 0, 0);
         ElasticProperties gps2(4., Point2d(-4, -2), 0, 0, 0, 0, 0, 0, 0);
         ElasticProperties gps4(-4., Point2d(-4, -2), 0, 0, 0, 0, 0, 0, 0);
         ElasticProperties gps3 = gps1 + gps2;
         Assert::IsTrue(IsZero(8 - gps3.GetEA()));
         Assert::IsTrue(IsZero(160. - gps3.GetEI11()));
         Assert::IsTrue(IsZero(gps3.GetEI22()));
         Assert::IsTrue(IsZero(32 - gps3.GetEIxx()));
         Assert::IsTrue(IsZero(128 - gps3.GetEIyy()));
         Assert::IsTrue(IsZero(64 - gps3.GetEIxy()));

         gps3 = gps3 + gps4;
         gps3.SetXleft(0);
         gps3.SetXright(0);
         gps3.SetYtop(0);
         gps3.SetYbottom(0);
         Assert::IsTrue(gps3 == gps1);
      }
	};
}
