#include "pch.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace WBFL::Geometry;

namespace GeomModelUnitTest
{
	TEST_CLASS(TestShapeProperties)
	{
	public:
		
		TEST_METHOD(PointArea)
		{
         ShapeProperties a(4., Point2d(0, 0), 0., 0., 0, 0, 0, 0, 0);
         Assert::IsTrue(a.GetCoordinateSystem() == ShapeProperties::CoordinateSystemType::Centroidal);
         Assert::IsTrue(Point2d(0, 0) == a.GetCentroid());
         Assert::IsTrue(IsZero(4 - a.GetArea()));
         Assert::IsTrue(IsZero(a.GetI11()));
         Assert::IsTrue(IsZero(a.GetI22()));
         Assert::IsTrue(IsZero(a.GetIxy()));
         Assert::IsTrue(IsZero(a.GetI12Max()));
         Assert::IsTrue(IsZero(a.GetI12Min()));
         Assert::IsTrue(IsZero(a.GetYtop()));
         Assert::IsTrue(IsZero(a.GetYbottom()));
         Assert::IsTrue(IsZero(a.GetXright()));
         Assert::IsTrue(IsZero(a.GetXleft()));

         // move origin
         Point2d orn(4, -2);
         a.SetOrigin(orn);
         Assert::IsTrue(a.GetCoordinateSystem() == ShapeProperties::CoordinateSystemType::UserDefined);
         Assert::IsTrue(Point2d(-4, 2) == a.GetCentroid());
         Assert::IsTrue(IsZero(4 - a.GetArea()));
         Assert::IsTrue(IsZero(-63.43 - ToDegrees(a.GetPrincipalDirection()), .1));
         Assert::IsTrue(IsZero(16 - a.GetIxx()));
         Assert::IsTrue(IsZero(64 - a.GetIyy()));
         Assert::IsTrue(IsZero(32 + a.GetIxy()));
         Assert::IsTrue(IsZero(80 - a.GetI11()));
         Assert::IsTrue(IsZero(a.GetI22()));
         Assert::IsTrue(IsZero(40 - a.GetI12Max()));
         Assert::IsTrue(IsZero(40 + a.GetI12Min()));
         Assert::IsTrue(IsZero(a.GetYtop()));
         Assert::IsTrue(IsZero(a.GetYbottom()));
         Assert::IsTrue(IsZero(a.GetXright()));
         Assert::IsTrue(IsZero(a.GetXleft()));

         // rotate 90 deg
         a.SetOrientation(M_PI / 2);
         Assert::IsTrue(a.GetCoordinateSystem() == ShapeProperties::CoordinateSystemType::UserDefined);
         Assert::IsTrue(Point2d(2, 4) == a.GetCentroid());
         Assert::IsTrue(IsZero(4 - a.GetArea()));
         Assert::IsTrue(IsZero(64 - a.GetIxx()));
         Assert::IsTrue(IsZero(16 - a.GetIyy()));
         Assert::IsTrue(IsZero(32 - a.GetIxy()));
         Assert::IsTrue(IsZero(80. - a.GetI11()));
         Assert::IsTrue(IsZero(a.GetI22()));
         Assert::IsTrue(IsZero(40 - a.GetI12Max()));
         Assert::IsTrue(IsZero(40 + a.GetI12Min()));
      }

      TEST_METHOD(Rectangle)
      {
         // try a 2x4 rectangle
         ShapeProperties gs2x4(8., Point2d(0, 0), 128. / 12., 32. / 12., 0.0, 1, 2, 1, 2);
         Assert::IsTrue(IsZero(8 - gs2x4.GetArea()));
         Assert::IsTrue(IsZero(128. / 12. - gs2x4.GetI11()));
         Assert::IsTrue(IsZero(32. / 12 - gs2x4.GetI22()));
         Assert::IsTrue(IsZero(gs2x4.GetIxy()));
         Assert::IsTrue(IsZero(4 - gs2x4.GetI12Max()));
         Assert::IsTrue(IsZero(4 + gs2x4.GetI12Min()));
         Assert::IsTrue(IsZero(2 - gs2x4.GetYtop()));
         Assert::IsTrue(IsZero(2 - gs2x4.GetYbottom()));
         Assert::IsTrue(IsZero(1 - gs2x4.GetXright()));
         Assert::IsTrue(IsZero(1 - gs2x4.GetXleft()));

         // move origin to user-defined location
         Point2d orn(4, -2);
         gs2x4.SetOrigin(orn);
         Assert::IsTrue(IsZero(8 - gs2x4.GetArea()));
         Assert::IsTrue(IsZero((128. / 12. + 32) - gs2x4.GetIxx()));
         Assert::IsTrue(IsZero((32. / 12 + 128) - gs2x4.GetIyy()));
         Assert::IsTrue(IsZero(64 + gs2x4.GetIxy()));
         Assert::IsTrue(IsZero(-62.25 - ToDegrees(gs2x4.GetPrincipalDirection()), .01));
         Assert::IsTrue(IsZero(77.67 - gs2x4.GetI12Max(), .01));
         Assert::IsTrue(IsZero(2 - gs2x4.GetYtop()));
         Assert::IsTrue(IsZero(2 - gs2x4.GetYbottom()));
         Assert::IsTrue(IsZero(1 - gs2x4.GetXright()));
         Assert::IsTrue(IsZero(1 - gs2x4.GetXleft()));

         // move origin back to centroid
         gs2x4.SetCoordinateSystem(ShapeProperties::CoordinateSystemType::Centroidal);
         Assert::IsTrue(gs2x4.GetCoordinateSystem() == ShapeProperties::CoordinateSystemType::Centroidal);
         Assert::IsTrue(Point2d(0, 0) == gs2x4.GetOrigin());
         Assert::IsTrue(IsZero(8 - gs2x4.GetArea()));
         Assert::IsTrue(IsZero(128. / 12. - gs2x4.GetI11()));
         Assert::IsTrue(IsZero(32. / 12 - gs2x4.GetI22()));
         Assert::IsTrue(IsZero(gs2x4.GetIxy()));
         Assert::IsTrue(IsZero(4 - gs2x4.GetI12Max()));
         Assert::IsTrue(IsZero(4 + gs2x4.GetI12Min()));
         Assert::IsTrue(IsZero(2 - gs2x4.GetYtop()));
         Assert::IsTrue(IsZero(2 - gs2x4.GetYbottom()));
         Assert::IsTrue(IsZero(1 - gs2x4.GetXright()));
         Assert::IsTrue(IsZero(1 - gs2x4.GetXleft()));

         // try rotation to principal
         ShapeProperties gsr(4., Point2d(0, 0), 16., 64., -32, 1, 2, 1, 2);
         gsr.SetCoordinateSystem(ShapeProperties::CoordinateSystemType::Principal);
         Assert::IsTrue(gsr.GetCoordinateSystem() == ShapeProperties::CoordinateSystemType::Principal);
         Assert::IsTrue(IsZero(4 - gsr.GetArea()));
         Assert::IsTrue(IsZero(80. - gsr.GetI11()));
         Assert::IsTrue(IsZero(gsr.GetI22()));
         Assert::IsTrue(IsZero(gsr.GetIxy()));
         Assert::IsTrue(IsZero(40 - gsr.GetI12Max()));
         Assert::IsTrue(IsZero(40 + gsr.GetI12Min()));

         // try addition and subtraction
         ShapeProperties s1(4., Point2d(4, 2), 0, 0, 0, 0, 0, 0, 0);
         ShapeProperties s2(4., Point2d(-4, -2), 0, 0, 0, 0, 0, 0, 0);
         ShapeProperties s4(-4., Point2d(-4, -2), 0, 0, 0, 0, 0, 0, 0);
         ShapeProperties s3 = s1 + s2;
         Assert::IsTrue(IsZero(8 - s3.GetArea()));
         Assert::IsTrue(IsZero(160. - s3.GetI11()));
         Assert::IsTrue(IsZero(s3.GetI22()));
         Assert::IsTrue(IsZero(32 - s3.GetIxx()));
         Assert::IsTrue(IsZero(128 - s3.GetIyy()));
         Assert::IsTrue(IsZero(64 - s3.GetIxy()));

         s3 = s3 + s4;
         s3.SetXleft(0);
         s3.SetXright(0);
         s3.SetYtop(0);
         s3.SetYbottom(0);
         Assert::IsTrue(s3 == s1);
      }

      TEST_METHOD(L6x4x7_8)
      {
         // Properties of a L6x4x7/8
         Float64 area = 7.98;
         Float64 ixx = 27.7;
         Float64 iyy = 9.75;
         Float64 ixy = 7.153;
         Float64 cgx = 1.12;
         Float64 cgy = 2.12;
         Float64 xLeft = 0;
         Float64 yBottom = 0;
         Float64 xRight = 4.0;
         Float64 yTop = 6.0;

         ShapeProperties props(area, Point2d(cgx, cgy), ixx, iyy, ixy, xLeft, yBottom, xRight, yTop);

         //
         // Test properties
         //
         Assert::IsTrue(IsEqual(props.GetArea(), area));
         Assert::IsTrue(IsEqual(props.GetIxx(), ixx));
         Assert::IsTrue(IsEqual(props.GetIyy(), iyy));
         Assert::IsTrue(IsEqual(props.GetIxy(), ixy));
         Assert::IsTrue(IsEqual(props.GetCentroid().X(), cgx));
         Assert::IsTrue(IsEqual(props.GetCentroid().Y(), cgy));

         Assert::IsTrue(IsEqual(props.GetXleft(), xLeft));
         Assert::IsTrue(IsEqual(props.GetXright(), xRight));
         Assert::IsTrue(IsEqual(props.GetYtop(), yTop));
         Assert::IsTrue(IsEqual(props.GetYbottom(), yBottom));

         Assert::IsTrue(props.GetCoordinateSystem() == ShapeProperties::CoordinateSystemType::Centroidal);

         // Default orientation is 0.0
         Assert::IsTrue(IsZero(props.GetOrientation()));

         // Default origin is (0.0,0.0)
         Assert::IsTrue(props.GetOrigin() == Point2d(0, 0));

         //
         // Principle Direction
         //
         Assert::IsTrue(IsEqual(props.GetPrincipalDirection(), 0.33645));

         //
         // Principle Values
         //
         Assert::IsTrue(IsEqual(props.GetI11(), 30.20176));
         Assert::IsTrue(IsEqual(props.GetI22(), 7.248239));
         Assert::IsTrue(IsEqual(props.GetI12Min(), -11.47676));
         Assert::IsTrue(IsEqual(props.GetI12Max(), 11.47676));

         //
         // Move the origin
         //
         Point2d pnt(10, 20);
         props.SetOrigin(pnt);
         Assert::IsTrue(props.GetCoordinateSystem() == ShapeProperties::CoordinateSystemType::UserDefined);
         Assert::IsTrue(props.GetOrigin() == pnt);
         Assert::IsTrue(props.GetCentroid() == Point2d(cgx - 10, cgy - 20));
         Assert::IsTrue(IsEqual(props.GetIxx(), ixx + area * (cgy - 20) * (cgy - 20)));
         Assert::IsTrue(IsEqual(props.GetIyy(), iyy + area * (cgx - 10) * (cgx - 10)));
         Assert::IsTrue(IsEqual(props.GetIxy(), ixy + area * (cgx - 10) * (cgy - 20)));

         // Put the origin back at (0,0)
         pnt.Move(0, 0);
         props.SetOrigin(pnt);

         Assert::IsTrue(IsEqual(props.GetArea(), area));
         Assert::IsTrue(IsEqual(props.GetIxx(), ixx + area * cgy * cgy));
         Assert::IsTrue(IsEqual(props.GetIyy(), iyy + area * cgx * cgx));
         Assert::IsTrue(IsEqual(props.GetIxy(), ixy + area * cgx * cgy));

         //
         // Test Orientation
         //
         props.SetOrientation(M_PI);
         Assert::IsTrue(IsEqual(props.GetOrientation(), M_PI));
         Assert::IsTrue(props.GetCoordinateSystem() == ShapeProperties::CoordinateSystemType::UserDefined);

         Assert::IsTrue(IsEqual(props.GetArea(), area));
         Assert::IsTrue(IsEqual(props.GetIxx(), ixx + area * cgy * cgy));
         Assert::IsTrue(IsEqual(props.GetIyy(), iyy + area * cgx * cgx));
         Assert::IsTrue(IsEqual(props.GetIxy(), ixy + area * cgx * cgy));
         Assert::IsTrue(props.GetCentroid() == Point2d(-cgx, -cgy));

         //
         // Test CoordinateSystem property
         //

         // global
         props.SetCoordinateSystem(ShapeProperties::CoordinateSystemType::Global);
         Assert::IsTrue(props.GetCoordinateSystem() == ShapeProperties::CoordinateSystemType::Global);

         Assert::IsTrue(IsEqual(props.GetIxx(), ixx + area * cgy * cgy));
         Assert::IsTrue(IsEqual(props.GetIyy(), iyy + area * cgx * cgx));
         Assert::IsTrue(IsEqual(props.GetIxy(), ixy + area * cgx * cgy));
         Assert::IsTrue(IsEqual(props.GetArea(), area));
         Assert::IsTrue(IsEqual(props.GetOrientation(), 0.0));
         Assert::IsTrue(props.GetCentroid() == Point2d(cgx, cgy));
         Assert::IsTrue(props.GetOrigin() == Point2d(0, 0));

         // centroidal
         props.SetCoordinateSystem(ShapeProperties::CoordinateSystemType::Centroidal);
         Assert::IsTrue(props.GetCoordinateSystem() == ShapeProperties::CoordinateSystemType::Centroidal);

         Assert::IsTrue(IsEqual(props.GetIxx(), ixx));
         Assert::IsTrue(IsEqual(props.GetIyy(), iyy));
         Assert::IsTrue(IsEqual(props.GetIxy(), ixy));
         Assert::IsTrue(IsEqual(props.GetArea(), area));
         Assert::IsTrue(IsEqual(props.GetOrientation(), 0.0));

         Assert::IsTrue(props.GetCentroid() == Point2d(cgx, cgy));
         Assert::IsTrue(props.GetOrigin() == Point2d(cgx, cgy));

         // principle
         props.SetCoordinateSystem(ShapeProperties::CoordinateSystemType::Principal);
         Assert::IsTrue(props.GetCoordinateSystem() == ShapeProperties::CoordinateSystemType::Principal);

         Assert::IsTrue(IsEqual(props.GetIxx(), 30.20176));
         Assert::IsTrue(IsEqual(props.GetIyy(), 7.248239));
         Assert::IsTrue(IsEqual(props.GetIxy(), 0.0));
         Assert::IsTrue(IsEqual(props.GetArea(), area));
         Assert::IsTrue(IsEqual(props.GetOrientation(), 0.33645));

         Assert::IsTrue(props.GetCentroid() == Point2d(0, 0));
         Assert::IsTrue(props.GetOrigin() == Point2d(cgx, cgy));

         // user
         props.SetCoordinateSystem(ShapeProperties::CoordinateSystemType::UserDefined);
         Assert::IsTrue(props.GetCoordinateSystem() == ShapeProperties::CoordinateSystemType::UserDefined);

         Assert::IsTrue(IsEqual(props.GetIxx(), 30.20176));
         Assert::IsTrue(IsEqual(props.GetIyy(), 7.248239));
         Assert::IsTrue(IsEqual(props.GetIxy(), 0.0));
         Assert::IsTrue(IsEqual(props.GetArea(), area));
         Assert::IsTrue(IsEqual(props.GetOrientation(), 0.33645));

         Assert::IsTrue(props.GetCentroid() == Point2d(0, 0));
         Assert::IsTrue(props.GetOrigin() == Point2d(cgx, cgy));
      }

      TEST_METHOD(JoinProperties)
      {
         ShapeProperties prop1, prop2;

         // Initialize shape 1
         // Rectangle 5 wide x 10 high
         // Bottom Left at 5,15
         prop1.SetArea(50);
         prop1.SetIxx(416.66667);
         prop1.SetIyy(104.16667);
         prop1.SetIxy(0);
         prop1.SetCentroid(Point2d(7.5, 20));
         prop1.SetXleft(2.5);
         prop1.SetXright(2.5);
         prop1.SetYtop(5.0);
         prop1.SetYbottom(5.0);

         // Initialize shape 2
         // Rectangle 2 wide x 5 high
         // Bottom left at 20,5
         prop2.SetArea(10);
         prop2.SetIxx(20.833333);
         prop2.SetIyy(3.33333);
         prop2.SetIxy(0);
         prop2.SetCentroid(Point2d(21, 7.5));
         prop2.SetXleft(1.0);
         prop2.SetXright(1.0);
         prop2.SetYtop(2.5);
         prop2.SetYbottom(2.5);

         // Add the properties together
         prop1 += prop2;

         // Transform to global coordinates for easier validation
         prop1.SetCoordinateSystem(ShapeProperties::CoordinateSystemType::Global);

         Assert::IsTrue(IsEqual(prop1.GetArea(), 60.));
         Assert::IsTrue(IsEqual(prop1.GetIxx(), 21000.));
         Assert::IsTrue(IsEqual(prop1.GetIyy(), 7330.));
         Assert::IsTrue(IsEqual(prop1.GetIxy(), 9075.));
         Assert::IsTrue(prop1.GetCentroid() == Point2d(9.75, 17.91666666666667));

         Assert::IsTrue(IsEqual(prop1.GetXleft(), 4.75));
         Assert::IsTrue(IsEqual(prop1.GetXright(), 12.25));
         Assert::IsTrue(IsEqual(prop1.GetYtop(), 7.083333333));
         Assert::IsTrue(IsEqual(prop1.GetYbottom(), 12.91666667));

         // Add a shape with no area and make sure results stay the same
         // The xleft, xright, ytop, and ybottom values will be effected.
         ShapeProperties prop3;
         prop1 += prop3;

         // Confirm nothing changed

         // Transform to global coordinates for easier validation
         prop1.SetCoordinateSystem(ShapeProperties::CoordinateSystemType::Global);

         Assert::IsTrue(IsEqual(prop1.GetArea(), 60.));
         Assert::IsTrue(IsEqual(prop1.GetIxx(), 21000.));
         Assert::IsTrue(IsEqual(prop1.GetIyy(), 7330.));
         Assert::IsTrue(IsEqual(prop1.GetIxy(), 9075.));
         Assert::IsTrue(prop1.GetCentroid() == Point2d(9.75, 17.91666666666667));

         Assert::IsTrue(IsEqual(prop1.GetXleft(), 9.75));
         Assert::IsTrue(IsEqual(prop1.GetXright(), 12.25));
         Assert::IsTrue(IsEqual(prop1.GetYtop(), 7.083333333));
         Assert::IsTrue(IsEqual(prop1.GetYbottom(), 17.91666667));
      }

      TEST_METHOD(AddOperator1)
      {
         // Test the addition of properties when both properties objects are in
         // centroidal coordinates
         ShapeProperties shape1(10, Point2d(10, 10), 10, 10, 10, 10, 10, 10, 10);
         ShapeProperties shape2(20, Point2d(20, 20), 20, 20, 20, 20, 20, 20, 20);

         ShapeProperties shape3 = shape1 + shape2;

         Assert::IsTrue(IsEqual(shape3.GetArea(), 30.));
         Assert::IsTrue(IsEqual(shape3.GetIxx(), 696.6666666666));
         Assert::IsTrue(IsEqual(shape3.GetIyy(), 696.6666666666));
         Assert::IsTrue(IsEqual(shape3.GetIxy(), 696.6666666666));
         Assert::IsTrue(Point2d(16.666666666666, 16.6666666666666) == shape3.GetCentroid());
         Assert::IsTrue(IsEqual(shape3.GetXleft(), 16.666666666666666));
         Assert::IsTrue(IsEqual(shape3.GetXright(), 23.333333333333333));
         Assert::IsTrue(IsEqual(shape3.GetYbottom(), 16.666666666666666));
         Assert::IsTrue(IsEqual(shape3.GetYtop(), 23.333333333333333));
      }

      TEST_METHOD(AddOperator2)
      {
         // Test the addition of properties when one property object is in centroidal
         // coordinates and one is in global coordinates

         ShapeProperties shape1(10, Point2d(10, 10), 10, 10, 10, 10, 10, 10, 10);
         ShapeProperties shape2(20, Point2d(20, 20), 20, 20, 20, 20, 20, 20, 20);
         shape2.SetCoordinateSystem(ShapeProperties::CoordinateSystemType::Global);

         Assert::IsTrue(IsEqual(shape2.GetArea(), 20.));
         Assert::IsTrue(IsEqual(shape2.GetIxx(), 8020.));
         Assert::IsTrue(IsEqual(shape2.GetIyy(), 8020.));
         Assert::IsTrue(IsEqual(shape2.GetIxy(), 8020.));
         Assert::IsTrue(Point2d(20, 20) == shape2.GetCentroid());
         Assert::IsTrue(IsEqual(shape2.GetXleft(), 20.));
         Assert::IsTrue(IsEqual(shape2.GetXright(), 20.));
         Assert::IsTrue(IsEqual(shape2.GetYbottom(), 20.));
         Assert::IsTrue(IsEqual(shape2.GetYtop(), 20.));

         ShapeProperties shape3 = shape1 + shape2;

         Assert::IsTrue(IsEqual(shape3.GetArea(), 30.));
         Assert::IsTrue(IsEqual(shape3.GetIxx(), 696.6666666666));
         Assert::IsTrue(IsEqual(shape3.GetIyy(), 696.6666666666));
         Assert::IsTrue(IsEqual(shape3.GetIxy(), 696.6666666666));
         Assert::IsTrue(Point2d(16.666666666666, 16.6666666666666) == shape3.GetCentroid());
         Assert::IsTrue(IsEqual(shape3.GetXleft(), 16.666666666666666));
         Assert::IsTrue(IsEqual(shape3.GetXright(), 23.333333333333333));
         Assert::IsTrue(IsEqual(shape3.GetYbottom(), 16.666666666666666));
         Assert::IsTrue(IsEqual(shape3.GetYtop(), 23.333333333333333));
      }

      TEST_METHOD(Assignment1)
      {
         // Test the mutators and accessors when property object is in centroidal units
         // This is just a raw test to make sure we get back what we put in.
         // This test makes no assumptions about the correctness of the section properties!!!
         ShapeProperties shape;

         shape.SetArea(10);
         Assert::IsTrue(IsEqual(shape.GetArea(), 10.));

         shape.SetCentroid(Point2d(10, 10));
         Assert::IsTrue(Point2d(10, 10) == shape.GetCentroid());

         shape.SetIxx(10);
         Assert::IsTrue(IsEqual(shape.GetIxx(), 10.));

         shape.SetIyy(10);
         Assert::IsTrue(IsEqual(shape.GetIyy(), 10.));

         shape.SetIxy(10);
         Assert::IsTrue(IsEqual(shape.GetIxy(), 10.));

         shape.SetOrigin(Point2d(10, 10));
         Assert::IsTrue(Point2d(10, 10) == shape.GetOrigin());

         shape.SetOrientation(0.5);
         Assert::IsTrue(IsEqual(shape.GetOrientation(), 0.5));

         shape.SetXleft(10);
         Assert::IsTrue(IsEqual(shape.GetXleft(), 10.));

         shape.SetXright(10);
         Assert::IsTrue(IsEqual(shape.GetXright(), 10.));

         shape.SetYtop(10);
         Assert::IsTrue(IsEqual(shape.GetYtop(), 10.));

         shape.SetYbottom(10);
         Assert::IsTrue(IsEqual(shape.GetYbottom(), 10.));
      }

      TEST_METHOD(Assignment2)
      {
         // Test the mutators and accessors when property object is in centroidal units
         // This test verifies section properties remain correct.
         ShapeProperties shape(10, Point2d(10, 10), 10, 10, 10, 10, 10, 10, 10);

         shape.SetCentroid(Point2d(20, 20));
         Assert::IsTrue(Point2d(20, 20) == shape.GetCentroid());
         Assert::IsTrue(IsEqual(shape.GetArea(), 10.));
         Assert::IsTrue(IsEqual(shape.GetIxx(), 10.));
         Assert::IsTrue(IsEqual(shape.GetIyy(), 10.));
         Assert::IsTrue(IsEqual(shape.GetIxy(), 10.));

         shape.SetIxx(20);
         Assert::IsTrue(Point2d(20, 20) == shape.GetCentroid());
         Assert::IsTrue(IsEqual(shape.GetArea(), 10.));
         Assert::IsTrue(IsEqual(shape.GetIxx(), 20.));
         Assert::IsTrue(IsEqual(shape.GetIyy(), 10.));
         Assert::IsTrue(IsEqual(shape.GetIxy(), 10.));

         shape.SetIyy(20);
         Assert::IsTrue(Point2d(20, 20) == shape.GetCentroid());
         Assert::IsTrue(IsEqual(shape.GetArea(), 10.));
         Assert::IsTrue(IsEqual(shape.GetIxx(), 20.));
         Assert::IsTrue(IsEqual(shape.GetIyy(), 20.));
         Assert::IsTrue(IsEqual(shape.GetIxy(), 10.));

         shape.SetIxy(20);
         Assert::IsTrue(Point2d(20, 20) == shape.GetCentroid());
         Assert::IsTrue(IsEqual(shape.GetArea(), 10.));
         Assert::IsTrue(IsEqual(shape.GetIxx(), 20.));
         Assert::IsTrue(IsEqual(shape.GetIyy(), 20.));
         Assert::IsTrue(IsEqual(shape.GetIxy(), 20.));
      }
   };
}
