#include "pch.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace WBFL::Geometry;

namespace GeomModelUnitTest
{
	TEST_CLASS(TestSectionComponent)
	{
	public:
		
		TEST_METHOD(Test)
		{
			std::unique_ptr<Shape> shape;
			SectionComponent sc(std::move(shape), 100, 101, 200, 201, SectionComponent::ComponentType::Structural);
			Assert::AreEqual(sc.GetForegroundModE(), 100.0);
			Assert::AreEqual(sc.GetForegroundDensity(), 101.0);
			Assert::AreEqual(sc.GetBackgroundModE(), 200.0);
			Assert::AreEqual(sc.GetBackgroundDensity(), 201.0);
			Assert::IsTrue(sc.GetComponentType() == SectionComponent::ComponentType::Structural);
		}
	};
}
