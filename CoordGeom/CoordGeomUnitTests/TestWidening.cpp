#include "pch.h"
#include "CppUnitTest.h"


using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace WBFL::COGO;

namespace CoordGeomUnitTest
{
	TEST_CLASS(TestWidening)
	{
	public:
		
		TEST_METHOD(Test)
		{
         auto alignment = Alignment::Create();
         auto profile = Profile::Create();
         auto surface = Surface::Create();
         profile->AddSurface(0, surface);
         alignment->AddProfile(0, profile);

         auto template1 = surface->CreateSurfaceTemplate(100.00);
         template1->UpdateSegmentParameters(0, 10, 0.02, SurfaceTemplateSegment::SlopeType::Horizontal);
         template1->UpdateSegmentParameters(1, 10, -0.02, SurfaceTemplateSegment::SlopeType::Horizontal);

         auto template2 = surface->CreateSurfaceTemplate(600.00);
         template2->UpdateSegmentParameters(0, 10, 0.02, SurfaceTemplateSegment::SlopeType::Horizontal);
         template2->UpdateSegmentParameters(1, 10, -0.02, SurfaceTemplateSegment::SlopeType::Horizontal);

         auto widening = Widening::Create(100, 200, 500, 600, 10.0, 0, 1);

         surface->AddWidening(widening);

         // before widening
         Assert::IsTrue(IsEqual(widening->GetWidening(0.0, 0), 0.0));
         Assert::IsTrue(IsEqual(widening->GetWidening(0.0, 1), 0.0));

         // half way through entry widening transition
         Assert::IsTrue(IsEqual(widening->GetWidening(150.0, 0), 5.0));
         Assert::IsTrue(IsEqual(widening->GetWidening(150.0, 1), 5.0));

         // full widening
         Assert::IsTrue(IsEqual(widening->GetWidening(400.0, 0), 10.0));
         Assert::IsTrue(IsEqual(widening->GetWidening(400.0, 1), 10.0));

         // half way through exit widening transition
         Assert::IsTrue(IsEqual(widening->GetWidening(550.0, 0), 5.0));
         Assert::IsTrue(IsEqual(widening->GetWidening(550.0, 1), 5.0));

         // after widening
         Assert::IsTrue(IsEqual(widening->GetWidening(700.0, 0), 0.0));
         Assert::IsTrue(IsEqual(widening->GetWidening(700.0, 1), 0.0));
      }
	};
}
