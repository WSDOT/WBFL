#include "pch.h"
#include "CppUnitTest.h"
#include <array>
#include <GeomModel/GeomModel.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace WBFL::RCSection;
using namespace WBFL::Geometry;

namespace RCSectionUnitTest
{
	TEST_CLASS(TestSectionBuilder)
	{
	public:
		
		TEST_METHOD(TestRectangularColumn)
		{
			auto section = SectionBuilder::RectangularColumn(24, 24, 2, 5, 5, 0.27, std::shared_ptr<const WBFL::Materials::StressStrainModel>(), std::shared_ptr<const WBFL::Materials::StressStrainModel>(), true);

			Assert::AreEqual((IndexType)17, section->GetShapeCount());
			Assert::AreEqual((IndexType)0, section->GetPrimaryShapeIndex());
			Assert::AreEqual(576., section->GetShape(0).GetProperties().GetArea());

			Assert::IsTrue(Point2d(0, 0) == section->GetShape(0).GetProperties().GetCentroid());

			// we don't know the order the bars points are generated, but we know what they should be.
			// here are the expected bar points
			std::array<Point2d, 16> barPoints
			{
				Point2d(-10, 10), Point2d(-5, 10), Point2d(0, 10), Point2d(5, 10), Point2d(10, 10),
				Point2d(-10,  5),                                                  Point2d(10,  5),
				Point2d(-10,  0),                                                  Point2d(10,  0),
				Point2d(-10, -5),                                                  Point2d(10, -5),
   		   Point2d(-10,-10), Point2d(-5,-10), Point2d(0,-10), Point2d(5,-10), Point2d(10,-10)
			};

			// create an array of boolean values, initialized to false
			// if a bar point is found, change the value to true
			std::array<bool, 16> bBarFound;
			std::fill(std::begin(bBarFound), std::end(bBarFound), false);
			for (IndexType i = 0; i < 16; i++)
			{
				IndexType shapeIdx = i + 1;
				auto properties = section->GetShape(shapeIdx).GetProperties();
				const auto& point = properties.GetCentroid();
				Assert::AreEqual(0.27, properties.GetArea());
				auto found = std::find_if(std::begin(barPoints), std::end(barPoints), [&point](const auto& p) {return p == point; });
				Assert::IsTrue(found != barPoints.end());
				bBarFound[i] = true;
			}
			// all bars should be found
			std::for_each(std::begin(bBarFound), std::end(bBarFound), [](auto& bFound) {Assert::IsTrue(bFound); });
		}

		TEST_METHOD(TestCircularColumn)
		{
			auto section = SectionBuilder::CircularColumn(14, 2, 36, 0.27, PI_OVER_2, std::shared_ptr<const WBFL::Materials::StressStrainModel>(), std::shared_ptr<const WBFL::Materials::StressStrainModel>(), true);

			Assert::AreEqual((IndexType)37, section->GetShapeCount());
			Assert::AreEqual((IndexType)0, section->GetPrimaryShapeIndex());
			Assert::AreEqual(M_PI*14*14/4, section->GetShape(0).GetProperties().GetArea());

			Assert::IsTrue(Point2d(0, 0) == section->GetShape(0).GetProperties().GetCentroid());

			// we don't know the order the bars points are generated, but we know what they should be.
			// here are the expected bar points
			std::vector<Point2d> barPoints;
			GeometricOperations::GenerateCircle(36, Point2d(0, 0), 5.0, PI_OVER_2, &barPoints);

			// create an array of boolean values, initialized to false
			// if a bar point is found, change the value to true
			std::array<bool, 36> bBarFound;
			std::fill(std::begin(bBarFound), std::end(bBarFound), false);
			for (IndexType i = 0; i < 36; i++)
			{
				IndexType shapeIdx = i + 1;
				auto properties = section->GetShape(shapeIdx).GetProperties();
				const auto& point = properties.GetCentroid();
				Assert::AreEqual(0.27, properties.GetArea());
				auto found = std::find_if(std::begin(barPoints), std::end(barPoints), [&point](const auto& p) {return p == point; });
				Assert::IsTrue(found != barPoints.end());
				bBarFound[i] = true;
			}
			// all bars should be found
			std::for_each(std::begin(bBarFound), std::end(bBarFound), [](auto& bFound) {Assert::IsTrue(bFound); });
		}
	};
}
