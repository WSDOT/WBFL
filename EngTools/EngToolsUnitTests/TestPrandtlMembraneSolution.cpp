#include "pch.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace WBFL::EngTools;
using namespace WBFL::Geometry;

namespace EngToolsUnitTests
{
	TEST_CLASS(TestPrandtlMembraneSolution)
	{
	public:
		
		TEST_METHOD(Test)
		{
			auto mesh = std::make_unique<UniformFDMesh>(0.25, 0.25);
			mesh->HasSymmetry(true);
			mesh->AddElementRow(0, 6);
			mesh->AddElementRow(0, 6);
			mesh->AddElementRow(0, 6);
			std::vector<Float64> meshValues;

			PrandtlMembraneSolution solution(100, 5, 2, std::move(mesh), meshValues);
			Assert::AreEqual(100.0, solution.GetJ());
			auto [slope,idx] = solution.GetMaxSlope();
			Assert::AreEqual(5.0, slope);
			Assert::AreEqual((IndexType)2, idx);
			Assert::AreEqual(5. / 200., solution.GetTmaxPerUnitTorque());
			auto rect = solution.GetMeshElement(0);
			Assert::AreEqual(0.25, rect.GetHeight());
			Assert::AreEqual(0.25, rect.GetWidth());
			Assert::IsTrue(Point2d(0, 0) == rect.GetLocatorPoint(Shape::LocatorPoint::TopLeft));

			rect = solution.GetMeshElement(11);
			Assert::AreEqual(0.25, rect.GetHeight());
			Assert::AreEqual(0.25, rect.GetWidth());
			Assert::IsTrue(Point2d(1.25, -0.25) == rect.GetLocatorPoint(Shape::LocatorPoint::TopLeft));
		}
	};
}
