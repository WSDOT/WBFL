#include "pch.h"
#include "CppUnitTest.h"


using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace WBFL::COGO;

namespace CoordGeomUnitTest
{
	TEST_CLASS(TestPathSegment)
	{
	public:
		
		TEST_METHOD(Test)
		{
         auto segment = PathSegment::Create(0.0, 0.0, 10.0, 10.0);

         Assert::IsTrue(IsEqual(segment->GetLength(), sqrt(200)));

         // LocatePoint
         auto point = segment->LocatePoint(5.0, OffsetType::AlongDirection, 5.0, 0.0);
         Assert::IsTrue(point == WBFL::Geometry::Point2d(5 * sin(M_PI / 4) + 5, 5 * cos(M_PI / 4)));

         point = segment->LocatePoint(5.0, OffsetType::AlongDirection, 5.0, M_PI / 4);
         Assert::IsTrue(point == WBFL::Geometry::Point2d(10 * sin(M_PI / 4), 10 * cos(M_PI / 4)));

         auto offset_path = segment->CreateOffsetPath(10);
         Assert::IsTrue(offset_path.front()->GetStartPoint() == WBFL::Geometry::Point2d(7.071067812, -7.071067812));
         Assert::IsTrue(offset_path.front()->GetEndPoint() == WBFL::Geometry::Point2d(17.071067812, 10 - 7.071067812));
         Assert::IsTrue(offset_path.front()->GetStartTangent() == WBFL::Geometry::Line2d(offset_path.front()->GetStartPoint(), WBFL::Geometry::Vector2d(1.0, M_PI / 4)));
         Assert::IsTrue(offset_path.front()->GetEndTangent() == WBFL::Geometry::Line2d(offset_path.front()->GetEndPoint(), WBFL::Geometry::Vector2d(1.0, M_PI / 4)));
         Assert::IsTrue(offset_path.front()->GetStartTangent() == offset_path.front()->GetEndTangent());

         offset_path = segment->CreateOffsetPath(-10);
         Assert::IsTrue(offset_path.front()->GetStartPoint() == WBFL::Geometry::Point2d(-7.071067812, 7.071067812));
         Assert::IsTrue(offset_path.front()->GetEndPoint() == WBFL::Geometry::Point2d(10 - 7.071067812, 17.071067812));
      }
	};
}
