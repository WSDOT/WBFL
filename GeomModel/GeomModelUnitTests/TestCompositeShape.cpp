#include "pch.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace WBFL::Geometry;

class TestShape : public ShapeImpl
{
public:
   TestShape(const ShapeProperties& prop) :m_Props(prop) {}
   virtual ShapeProperties GetProperties() const override { return m_Props; }
   virtual std::unique_ptr<Shape> CreateClone() const override { return std::make_unique<TestShape>(*this); }
   virtual std::unique_ptr<Shape> CreateClippedShape(const Line2d& line, Line2d::Side side) const override { return std::make_unique<TestShape>(*this); }
   virtual std::unique_ptr<Shape> CreateClippedShape(const Rect2d& r, Shape::ClipRegion region) const override { return std::make_unique<TestShape>(*this); }
   virtual Float64 GetFurthestDistance(const Line2d& line, Line2d::Side side) const override { return 0; }
   virtual std::pair<Point2d, Float64> GetFurthestPoint(const Line2d& line, Line2d::Side side) const override { return std::make_pair(Point2d(0, 0), 0); }
   virtual Rect2d GetBoundingBox() const override { return Rect2d(); }
   virtual bool PointInShape(const Point2d& p) const override { return true; }
   virtual Float64 GetPerimeter() const override { return 0.0; }
   virtual std::vector<Point2d> GetPolyPoints() const override { return m_DummyPoints; }
   virtual void Reflect(const Line2d& line) override {};
   virtual std::unique_ptr<Shape> CreateReflectedShape(const Line2d& line) const override { auto clone = CreateClone(); clone->Reflect(line); return clone; }
   bool operator==(const TestShape& rhs) const { return m_Props == rhs.m_Props; }
protected:
   virtual void DoOffset(const Size2d& delta) override {}
   virtual void DoRotate(const Point2d& center, Float64 angle) override {}
private:
   ShapeProperties m_Props;
   std::vector<Point2d> m_DummyPoints;
};

namespace GeomModelUnitTest
{
	TEST_CLASS(TestCompositeShape)
	{
	public:

		TEST_METHOD(Test)
		{
         // create an angle shape. by composing two rectangles
         // Taken from "Statics" 1st Ed. by J.L. Merriam, page 373
         TestShape outer(ShapeProperties(2000, Point2d(20, 25), 416666., 266666., 0, 20, 25, 20, 25));
         TestShape inner(ShapeProperties(-1200, Point2d(25, 30), -160000., -90000., 0, 15, 20, 15, 20));
         CompositeShape anglec;
         anglec.AddShape(outer);
         anglec.AddShape(inner);

         Assert::IsTrue(TestHookPoint(anglec));

         ShapeProperties aprops = anglec.GetProperties();
         Assert::IsTrue(IsEqual(aprops.GetArea(), 800.));
         Assert::IsTrue(IsEqual(aprops.GetIxx(), 181666., 10.));
         Assert::IsTrue(IsEqual(aprops.GetIyy(), 101666., 10.));
         Assert::IsTrue(IsEqual(aprops.GetIxy(), -75000., 10.));
         Assert::IsTrue(anglec.GetBoundingBox() == Rect2d(0, 0, 40, 50));

         // delete inner rectangle
         Assert::IsTrue(anglec.GetShapeCount() == 2);
         try
         {
            anglec.RemoveShape(100);
            Assert::Fail();
         }
         catch (WBFL::Geometry::XGeometry& e)
         {
            UNREFERENCED_PARAMETER(e);
            Assert::IsTrue(true); // an exception should be thrown
         }

         try
         {
            anglec.RemoveShape(1);
         }
         catch (WBFL::Geometry::XGeometry& e)
         {
            UNREFERENCED_PARAMETER(e);
            Assert::Fail(); // should not throw
         }

         Assert::IsTrue(anglec.GetShapeCount() == 1);
         aprops = anglec.GetProperties();
         Assert::IsTrue(IsEqual(aprops.GetArea(), 2000.));
         Assert::IsTrue(IsEqual(aprops.GetIxx(), 416666., 10.));
         Assert::IsTrue(IsEqual(aprops.GetIyy(), 266666., 10.));
         Assert::IsTrue(IsEqual(aprops.GetIxy(), 0., 10.));
         Assert::IsTrue(anglec.GetBoundingBox() == Rect2d(0, 0, 40, 50));
      }
	};
}
