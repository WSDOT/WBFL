#include "pch.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace WBFL::Geometry;

namespace GeomModelUnitTest
{
	TEST_CLASS(TestCircularSegment)
	{
	public:

		TEST_METHOD(ShapeProperties)
		{
         Float64 radius = 50;
         Float64 mo = radius;
         CircularSegment circseg(Point2d(0, 0), radius, mo, 0);
         auto props = circseg.GetProperties();

         Assert::IsTrue(IsEqual(props.GetArea(), M_PI * radius * radius / 2));
         Assert::IsTrue(IsEqual(props.GetIxx(), M_PI * radius * radius * radius * radius / 8));
         Assert::IsTrue(IsEqual(props.GetIyy(), pow(radius, 4) * (9 * M_PI * M_PI - 64) / (72 * M_PI)));
         Assert::IsTrue(IsEqual(props.GetIxy(), 0.0));
         Assert::IsTrue(IsEqual(props.GetCentroid().X(), 4 * radius / (3 * M_PI)));
         Assert::IsTrue(IsEqual(props.GetCentroid().Y(), 0.0));
         Assert::IsTrue(props.GetCoordinateSystem() == ShapeProperties::CoordinateSystemType::Centroidal);

         // rotate 90 deg and check results
         circseg.SetRotation(PI_OVER_2);
         props = circseg.GetProperties();
         Assert::IsTrue(IsEqual(props.GetArea(), M_PI * radius * radius / 2));
         Assert::IsTrue(IsEqual(props.GetIxx(), pow(radius, 4) * (9 * M_PI * M_PI - 64) / (72 * M_PI)));
         Assert::IsTrue(IsEqual(props.GetIyy(), M_PI * radius * radius * radius * radius / 8));
         Assert::IsTrue(IsEqual(props.GetIxy(), 0.0));
         Assert::IsTrue(IsEqual(props.GetCentroid().X(), 0.0));
         Assert::IsTrue(IsEqual(props.GetCentroid().Y(), 4 * radius / (3 * M_PI)));
         Assert::IsTrue(props.GetCoordinateSystem() == ShapeProperties::CoordinateSystemType::Centroidal);

         circseg.SetRotation(0.0);
         circseg.SetCenter(Point2d(10, 10));
         circseg.SetRadius(10);
         circseg.SetMidOrdinate(5);
         Assert::IsFalse(circseg.PointInShape(Point2d(1, 1)) );
         Assert::IsFalse(circseg.PointInShape(Point2d(10, 10)) );
         Assert::IsTrue(circseg.PointInShape(Point2d(17, 10)));
      }

      TEST_METHOD(Polygon)
      {
         // PolyPoints are tested by CircularSegment.xls. This
         // spreadsheet plots the polypoints so I can visually verify
         // the shape
         // The following are points reported from the spreadsheet and
         // verified visually. They are coded here for regression testing purposes
         // If the implementation changes, these points should not change
         Float64 px[] = {
            51.7356,
            53.7115,
            55.4346,
            56.8948,
            58.0837,
            58.9944,
            59.6217,
            59.9619,
            60.013,
            59.7748,
            59.2487,
            58.4376,
            57.3463,
            55.981,
            54.3498,
            52.462,
            50.3285,
            47.9617,
            45.3753,
            42.5842,
            39.6046,
            36.4537,
            33.1498,
            29.712,
            26.1601,
            22.5147,
            18.7969,
            15.0283,
            11.2305,
            7.42564,
            3.63566,
            -0.117501,
            -3.81213,
            -7.42685,
            -10.9408,
            -14.3335,
            -17.5855
         };

         Float64 py[] = {
            -17.5855,
            -14.3335,
            -10.9408,
            -7.42685,
            -3.81213,
            -0.117501,
            3.63566,
            7.42564,
            11.2305,
            15.0283,
            18.7969,
            22.5147,
            26.1601,
            29.712,
            33.1498,
            36.4537,
            39.6046,
            42.5842,
            45.3753,
            47.9617,
            50.3285,
            52.462,
            54.3498,
            55.981,
            57.3463,
            58.4376,
            59.2487,
            59.7748,
            60.013,
            59.9619,
            59.6217,
            58.9944,
            58.0837,
            56.8948,
            55.4346,
            53.7115,
            51.7356
         };

         CircularSegment circseg;
         circseg.SetRotation(M_PI / 4);
         circseg.SetRadius(50);
         circseg.SetMidOrdinate(40);
         circseg.SetCenter(Point2d(10, 10));

         const std::vector<Point2d>& vPoints = circseg.GetPolyPoints();
         int i = 0;
         for (const auto& point : vPoints)
         {
            Assert::IsTrue(IsEqual(point.X(), px[i], 0.0001));
            Assert::IsTrue(IsEqual(point.Y(), py[i], 0.0001));
            i++;
         }
      }

      TEST_METHOD(ClipWithLine)
      {
         CircularSegment circseg;
         Float64 radius = 50;
         Float64 mo = radius;
         circseg.SetRadius(radius);
         circseg.SetMidOrdinate(mo);
         circseg.SetCenter(Point2d(10, 10));

         // clipping line well below shape (shape on right of line)
         Line2d line(Point2d(100, -70), Point2d(-100, -70));
         std::unique_ptr<Shape> clipShape(circseg.CreateClippedShape(line, Line2d::Side::Left));
         auto props = clipShape->GetProperties();
         Assert::IsTrue(IsEqual(props.GetArea(), M_PI * radius * radius / 2));

         // reverse clipping line (shape on left of line)
         // entire shape clipped away
         clipShape = std::unique_ptr<Shape>(circseg.CreateClippedShape(line, Line2d::Side::Right));
         Assert::IsNull(clipShape.get());

         // clip shape in such a way that we are left with a quarter circle
         circseg.SetCenter(Point2d(100, 100));
         circseg.SetRotation(PI_OVER_2);
         radius = 50;
         mo = radius;
         circseg.SetRadius(radius);
         circseg.SetMidOrdinate(mo);

         line.ThroughPoints(Point2d(100, -500), Point2d(100, 500));

         clipShape = std::unique_ptr<Shape>(circseg.CreateClippedShape(line, Line2d::Side::Left));
         props = clipShape->GetProperties();
         Float64 val1 = props.GetArea();
         Float64 val2 = M_PI * radius * radius / 4;
         Assert::IsTrue(IsEqual(val1, val2, 0.01));

         // Test relative correctness of centroid.
         // Should be left and above center of circle
         // and x and y should be equal.
         Assert::IsTrue(props.GetCentroid().X() > 100);
         Assert::IsTrue(props.GetCentroid().Y() > 100);
         Assert::IsTrue(IsEqual(props.GetCentroid().X(), props.GetCentroid().Y(), 0.0001));

         // clip in such a way the the result is still a circular segment
         circseg.SetCenter(Point2d(0, 0));
         radius = 50;
         mo = 60;
         circseg.SetRadius(radius);
         circseg.SetMidOrdinate(mo);
         circseg.SetRotation(0);
         line.ThroughPoints(Point2d(40, -100), Point2d(40, 100));
         clipShape = std::unique_ptr<Shape>(circseg.CreateClippedShape(line, Line2d::Side::Left));
         CircularSegment* clip = dynamic_cast<CircularSegment*>(clipShape.get());
         Assert::IsNotNull(clip);
         // center and radius should be the same
         Assert::IsTrue(IsEqual(circseg.GetRadius(), clip->GetRadius()));
         Assert::IsTrue(IsEqual(circseg.GetCenter().X(), clip->GetCenter().X()));
         Assert::IsTrue(IsEqual(circseg.GetCenter().Y(), clip->GetCenter().Y()));
         // mid-ordinate should be the radius less the original mid-ordinate
         Assert::IsTrue(IsEqual(clip->GetMidOrdinate(), mo - radius));

         // reverse the direction of the clipping line
         // result should be a polygon.
         // area clip = area shape - area clip from above
         //
         // get area of source shape and the clip shape from above
         Float64 area1, area2, area3;
         props = circseg.GetProperties();
         area1 = props.GetArea();

         props = clip->GetProperties();
         area2 = props.GetArea();

         clipShape = std::unique_ptr<Shape>(circseg.CreateClippedShape(line, Line2d::Side::Right));

         props = clipShape->GetProperties();
         area3 = props.GetArea();
         val1 = area1 - area2;
         Assert::IsTrue(IsEqual(area3, val1, 0.35));

         // run a clipping line through the straight edge of the shape
         // Clip with line going both direction. Sum of clipped shape areas
         // must be equal to the area of the original shape
         circseg.SetCenter(Point2d(0, 0));
         circseg.SetRadius(100);
         circseg.SetMidOrdinate(70);
         circseg.SetRotation(0);
         props = circseg.GetProperties();
         area1 = props.GetArea();

         line.ThroughPoints(Point2d(90, 90), Point2d(20, -60));
         clipShape = std::unique_ptr<Shape>(circseg.CreateClippedShape(line, Line2d::Side::Left));
         props = clipShape->GetProperties();
         area2 = props.GetArea();

         clipShape = std::unique_ptr<Shape>(circseg.CreateClippedShape(line, Line2d::Side::Right));
         props = clipShape->GetProperties();
         area3 = props.GetArea();

         val1 = area2 + area3;
         Assert::IsTrue(IsEqual(area1, val1));

         // same as above, but this time shape is a full circle (interior angle = 360)
         circseg.SetCenter(Point2d(0, 0));
         circseg.SetRadius(50);
         circseg.SetMidOrdinate(100);
         circseg.SetRotation(0);
         props = circseg.GetProperties();
         area1 = props.GetArea();
         Assert::IsTrue(IsEqual(50.0, props.GetXleft()));
         Assert::IsTrue(IsEqual(50.0, props.GetYbottom()));
         Assert::IsTrue(IsEqual(50.0, props.GetXright()));
         Assert::IsTrue(IsEqual(50.0, props.GetYtop()));

         line.ThroughPoints(Point2d(-50, -50), Point2d(50, 50));

         clipShape = std::unique_ptr<Shape>(circseg.CreateClippedShape(line, Line2d::Side::Left));
         props = clipShape->GetProperties();
         area2 = props.GetArea();
         Assert::IsTrue(IsEqual(area2 * 2, area1, 0.001)); // clip shape half circle

         Float64 cgx1, cgy1;
         cgx1 = props.GetCentroid().X();
         cgy1 = props.GetCentroid().Y();

         clipShape = std::unique_ptr<Shape>(circseg.CreateClippedShape(line, Line2d::Side::Right));
         props = clipShape->GetProperties();
         area3 = props.GetArea();
         Assert::IsTrue(IsEqual(area3 * 2, area1, 0.5)); // clip shape half circle

         Float64 cgx2, cgy2;
         cgx2 = props.GetCentroid().X();
         cgy2 = props.GetCentroid().Y();

         val1 = area2 + area3;
         Assert::IsTrue(IsEqual(area1, val1, 0.2));

         Assert::IsTrue(IsEqual(cgx1, -cgx2, 0.001));
         Assert::IsTrue(IsEqual(cgy1, -cgy2, 0.001));
      }
	};
}
