#include "pch.h"
#include "CppUnitTest.h"


using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace WBFL::COGO;

namespace CoordGeomUnitTest
{
	TEST_CLASS(TestSuperelevation)
	{
	public:
		
		TEST_METHOD(Test)
		{
         auto alignment = Alignment::Create();
         auto profile = Profile::Create();
         alignment->AddProfile(0, profile);
         auto surface = Surface::Create();
         profile->AddSurface(0, surface);

         auto super = Superelevation::Create();
         surface->AddSuperelevation(super);


         // Check default values
         Assert::IsTrue(IsEqual(super->GetBeginTransition().GetValue(), 0.0));
         Assert::IsTrue(super->GetBeginTransition().GetStationZoneIndex() == INVALID_INDEX);

         Assert::IsTrue(IsEqual(super->GetBeginFullSuperelevation().GetValue(), 0.0));
         Assert::IsTrue(super->GetBeginFullSuperelevation().GetStationZoneIndex() == INVALID_INDEX);

         Assert::IsTrue(IsEqual(super->GetEndFullSuperelevation().GetValue(), 0.0));
         Assert::IsTrue(super->GetEndFullSuperelevation().GetStationZoneIndex() == INVALID_INDEX);

         Assert::IsTrue(IsEqual(super->GetEndTransition().GetValue(), 0.0));
         Assert::IsTrue(super->GetEndTransition().GetStationZoneIndex() == INVALID_INDEX);

         Assert::IsTrue(super->GetBeginTransitionType() == Superelevation::TransitionType::Linear);
         Assert::IsTrue(super->GetEndTransitionType() == Superelevation::TransitionType::Linear);

         Float64 l1, l2;
         std::tie(l1, l2) = super->GetBeginTransitionParameters();
         Assert::IsTrue(IsZero(l1) && IsZero(l2));

         std::tie(l1, l2) = super->GetEndTransitionParameters();
         Assert::IsTrue(IsZero(l1) && IsZero(l2));

         // Setup some real parameters
         super->Init(500, 550, 1550, 1600, 0.06, 0);

         Assert::IsTrue(IsEqual(super->GetSlope(400, -0.02), -0.02)); // before super
         Assert::IsTrue(IsEqual(super->GetSlope(525, -0.02), 0.02)); // half-way through begin transition
         Assert::IsTrue(IsEqual(super->GetSlope(1000, -0.02), 0.06)); // in full super
         Assert::IsTrue(IsEqual(super->GetSlope(1575, -0.02), 0.02)); // half-way through end transition
         Assert::IsTrue(IsEqual(super->GetSlope(1800, -0.02), -0.02)); // after super

         super->SetBeginTransitionType(Superelevation::TransitionType::Parabolic);
         super->SetBeginTransitionParameters(25, 25);
         super->SetEndTransitionType(Superelevation::TransitionType::Parabolic);
         super->SetEndTransitionParameters(25, 25);

         Assert::IsTrue(IsEqual(super->GetSlope(400, -0.02), -0.02)); // before super
         Assert::IsTrue(IsEqual(super->GetSlope(520, -0.02), 0.0056)); // 5 before half-way through begin transition
         Assert::IsTrue(IsEqual(super->GetSlope(525, -0.02), 0.02)); // half-way through begin transition
         Assert::IsTrue(IsEqual(super->GetSlope(530, -0.02), 0.0344)); // 5 after half-way through begin transition
         Assert::IsTrue(IsEqual(super->GetSlope(1000, -0.02), 0.06)); // in full super
         Assert::IsTrue(IsEqual(super->GetSlope(1570, -0.02), 0.0344)); // 5 before half-way through end transition
         Assert::IsTrue(IsEqual(super->GetSlope(1575, -0.02), 0.02)); // half-way through end transition
         Assert::IsTrue(IsEqual(super->GetSlope(1580, -0.02), 0.0056)); // 5 after half-way through end transition
         Assert::IsTrue(IsEqual(super->GetSlope(1800, -0.02), -0.02)); // after super
      }
	};
}
