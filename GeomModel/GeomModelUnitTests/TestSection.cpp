#include "pch.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace WBFL::Geometry;

namespace GeomModelUnitTest
{
	TEST_CLASS(TestSection)
	{
	public:
		TEST_METHOD(Test)
		{
         // Test to verify non-structural components are not included in elastic properties,
         // but are included in mass properties
         WBFL::Geometry::Rectangle rect1(Point2d(0, 0), 20, 10);
         WBFL::Geometry::Rectangle rect2(Point2d(0, 0), 20, 10);
         rect2.Move(Shape::LocatorPoint::BottomCenter, rect1.GetLocatorPoint(Shape::LocatorPoint::TopCenter));
         Section section;
         section.AddComponent(rect1, 1, 1, 0, 0, SectionComponent::ComponentType::Structural);
         section.AddComponent(rect2, 1, 2, 0, 0, SectionComponent::ComponentType::Nonstructural);
         MassProperties mProp = section.GetMassProperties();
         Assert::IsTrue(IsEqual(mProp.GetMassPerLength(), 600.));

         ElasticProperties eProp = section.GetElasticProperties();
         Assert::IsTrue(IsEqual(eProp.GetEA(), 200.));


         // Create a hollow box and check the properties
         //             10
         //   +------------------------+
         //   |           8            |
         //   |  +------------------+  |       EA   = 40.0
         //   |  |                  |  |       EIxx = 343.33333
         //   |  |                  |  |       EIyy = 453.33333
         //   |  |                  |5 | 8     EIxy = 0.0
         //   |  |                  |  |       cg   = (5,4)
         //   |  |                  |  |
         //   |  +------------------+  |
         //   |                        |
         //   +------------------------+
         //
         section.Clear();

         WBFL::Geometry::Rectangle outerRect(Point2d(5, 4), 10, 8);;
         WBFL::Geometry::Rectangle innerRect(Point2d(5, 4), 8, 5);

         section.AddComponent(outerRect, 1.0, 1.0, 0.0, 0.0, SectionComponent::ComponentType::Structural);
         section.AddComponent(innerRect, 0.0, 0.0, 1.0, 1.0, SectionComponent::ComponentType::Structural);

         ElasticProperties props = section.GetElasticProperties();
         Assert::IsTrue(IsEqual(props.GetEA(), 40.0));
         Assert::IsTrue(IsEqual(props.GetEIxx(), 343.33333));
         Assert::IsTrue(IsEqual(props.GetEIxy(), 0.00000));
         Assert::IsTrue(IsEqual(props.GetEIyy(), 453.33333));
         Assert::IsTrue(IsEqual(props.GetCentroid().X(), 5.0));
         Assert::IsTrue(IsEqual(props.GetCentroid().Y(), 4.0));

         MassProperties mprops = section.GetMassProperties();
         Assert::IsTrue(IsEqual(mprops.GetMassPerLength(), 40.0));

         Rect2d box = section.GetBoundingBox();
         Assert::IsTrue(IsEqual(box.Left(), 0.0));
         Assert::IsTrue(IsEqual(box.Right(), 10.0));
         Assert::IsTrue(IsEqual(box.Bottom(), 0.0));
         Assert::IsTrue(IsEqual(box.Top(), 8.0));

         // tweak the bounding box and use it for a clipping rectangle
         // Cover the top portion just above the void and clip.
         // Area should be 10x1.5 = 15
         box.Left() = -100;
         box.Right() = 100;
         box.Bottom() = 6.5;
         box.Top() = 100;

         auto clip = section.CreateClippedSection(box, Section::ClipRegion::In);
         props = clip->GetElasticProperties();
         Assert::IsTrue(IsEqual(props.GetEA(), 15.0));

         // Clip with line... Use the bottom of the clipping rect.
         Line2d clipLine(box.BottomRight(), box.BottomLeft());
         clip = section.CreateClippedSection(clipLine, Line2d::Side::Left);
         props = clip->GetElasticProperties();
         Assert::IsTrue(IsEqual(props.GetEA(), 15.0));
      }
	};
}
