#include "pch.h"
#include "CppUnitTest.h"


using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace WBFL::COGO;

namespace CoordGeomUnitTest
{
	TEST_CLASS(TestSurfaceTemplateSegment)
	{
	public:
		
		TEST_METHOD(Default)
		{
			SurfaceTemplateSegment segment;
			Assert::IsTrue(IsEqual(segment.GetWidth(), 1.0));
			Assert::IsTrue(IsEqual(segment.GetSlope(), 0.02));
			Assert::IsTrue(segment.GetSlopeType() == SurfaceTemplateSegment::SlopeType::Horizontal);
		}

		TEST_METHOD(Constructed)
		{
			SurfaceTemplateSegment segment(20.0,-0.06,SurfaceTemplateSegment::SlopeType::FixedVertical);
			Assert::IsTrue(IsEqual(segment.GetWidth(), 20.0));
			Assert::IsTrue(IsEqual(segment.GetSlope(), -0.06));
			Assert::IsTrue(segment.GetSlopeType() == SurfaceTemplateSegment::SlopeType::FixedVertical);
		}

		TEST_METHOD(Parameters)
		{
			SurfaceTemplateSegment segment(20.0, -0.06, SurfaceTemplateSegment::SlopeType::FixedVertical);
			Float64 width, slope;
			SurfaceTemplateSegment::SlopeType slopeType;
			std::tie(width, slope, slopeType) = segment.GetParameters();
			Assert::IsTrue(IsEqual(width, 20.0));
			Assert::IsTrue(IsEqual(slope, -0.06));
			Assert::IsTrue(slopeType == SurfaceTemplateSegment::SlopeType::FixedVertical);

			segment.SetParameters(10.0, 0.05, SurfaceTemplateSegment::SlopeType::FixedHorizontal);
			std::tie(width, slope, slopeType) = segment.GetParameters();
			Assert::IsTrue(IsEqual(width, 10.0));
			Assert::IsTrue(IsEqual(slope, 0.05));
			Assert::IsTrue(slopeType == SurfaceTemplateSegment::SlopeType::FixedHorizontal);
		}
	};
}
