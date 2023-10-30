#include "pch.h"
#include "CppUnitTest.h"
#include <GeomModel/PrecastBeam.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace WBFL::EngTools;

namespace EngToolsUnitTests
{
	TEST_CLASS(TestPrandtlMembraneSolver)
	{
	public:
		
		TEST_METHOD(Test)
		{
         WBFL::Geometry::PrecastBeam beam;
         beam.SetC1(1);
         beam.SetD1(3);
         beam.SetD2(3);
         beam.SetD3(3);
         beam.SetD4(3);
         beam.SetD5(4.5);
         beam.SetD6(5.125);
         beam.SetHeight(100);
         beam.SetT1(6.125);
         beam.SetT2(6.125);
         beam.SetW1(6);
         beam.SetW2(18.4375);
         beam.SetW3(3);
         beam.SetW4(3);
         beam.SetW5(13.125);

         // use symmetry
         PrandtlMembraneSolution solution = PrandtlMembraneSolver::Solve(&beam, 0.25, 0.25);
         Assert::IsTrue(IsEqual(solution.GetJ(), 18506.51360));
         Assert::IsTrue(IsEqual(solution.GetFiniteDifferenceMesh()->GetMeshArea(), 1109.25));
         auto [maxSlope,maxSlopeElementIdx] = solution.GetMaxSlope();
         Assert::IsTrue(IsEqual(maxSlope, 31.320506783765548));
         Assert::IsTrue(maxSlopeElementIdx == 6412);
         Assert::IsTrue(IsEqual(solution.GetTmaxPerUnitTorque(), 0.00084620224738361023));

         // ignore symmetry
         solution = PrandtlMembraneSolver::Solve(&beam, 0.25, 0.25, false);
         Assert::IsTrue(IsEqual(solution.GetJ(), 18506.51360));
         Assert::IsTrue(IsEqual(solution.GetFiniteDifferenceMesh()->GetMeshArea(), 1109.25));
         std::tie(maxSlope,maxSlopeElementIdx) = solution.GetMaxSlope();
         Assert::IsTrue(IsEqual(maxSlope, 31.320506783765548));
         Assert::IsTrue(maxSlopeElementIdx == 6412);
         Assert::IsTrue(IsEqual(solution.GetTmaxPerUnitTorque(), 0.00084620224738361023));

         // use a solver object
         PrandtlMembraneSolver solver;
         solver.Initialize(0.25, 0.25);
         solution = solver.Solve(&beam);
         Assert::IsTrue(IsEqual(solution.GetJ(), 18506.51360));
         Assert::IsTrue(IsEqual(solution.GetFiniteDifferenceMesh()->GetMeshArea(), 1109.25));
         std::tie(maxSlope, maxSlopeElementIdx) = solution.GetMaxSlope();
         Assert::IsTrue(IsEqual(maxSlope, 31.320506783765548));
         Assert::IsTrue(maxSlopeElementIdx == 6412);
         Assert::IsTrue(IsEqual(solution.GetTmaxPerUnitTorque(), 0.00084620224738361023));
		}
	};
}
