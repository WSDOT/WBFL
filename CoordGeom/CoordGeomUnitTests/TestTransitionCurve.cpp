#include "pch.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace WBFL::COGO;

namespace CoordGeomUnitTest
{
	TEST_CLASS(TestTransitionCurve)
	{
	public:
      void Verify(Float64 L, const TransitionCurve* pCurve, std::array<std::pair<Float64, Float64>, 6>& values)
      {
         static Float64 tol = 0.0001;
         auto size = values.size();
         for (auto i = 0; i < size; i++)
         {
            Float64 s = i * L / (size - 1);
            auto p = pCurve->PointOnCurve(s);

            Assert::IsTrue(IsEqual(values[i].first,  p.X(),tol));
            Assert::IsTrue(IsEqual(values[i].second, p.Y(), tol));
         }
      }

		TEST_METHOD(Test)
		{
         // CCW (left) curves
         Float64 R1 = 0;
         Float64 R2 = 50;
         Float64 L = 100;

         auto curve = TransitionCurve::Create();
         curve->Init(WBFL::Geometry::Point2d(0, 0), 0.0, R1, R2, L, TransitionCurveType::Clothoid);

         std::array<std::pair<Float64, Float64>, 6> values1
         {
            std::make_pair(0.0, 0.0),
            std::make_pair(19.9968, 0.266636),
            std::make_pair(39.8977, 2.12944),
            std::make_pair(59.2271, 7.13362),
            std::make_pair(76.7848, 16.5738),
            std::make_pair(90.4523, 31.0268)
         };
         Verify(L, curve.get(), values1);

         R1 = 300;
         std::array<std::pair<Float64, Float64>, 6> values2
         {
            std::make_pair(0,0),
            std::make_pair(19.9312,1.55332),
            std::make_pair(39.4645,5.73933),
            std::make_pair(57.7564,13.7137),
            std::make_pair(73.2775,26.2078),
            std::make_pair(83.8359,43.0612)
         };

         curve->Init(WBFL::Geometry::Point2d(0,0), 0.0, R1, R2, L, TransitionCurveType::Clothoid);
         Verify(L, curve.get(), values2);

         // CW (right) curves
         R1 = 0;
         R2 = -50;
         curve->Init(WBFL::Geometry::Point2d(0,0), 0.0, R1, R2, L, TransitionCurveType::Clothoid);

         std::array<std::pair<Float64, Float64>, 6> values3
         {
            std::make_pair(0, 0),
            std::make_pair(19.9968, -0.266636),
            std::make_pair(39.8977, -2.12944),
            std::make_pair(59.2271, -7.13362),
            std::make_pair(76.7848, -16.5738),
            std::make_pair(90.4523, -31.0268)
         };
         Verify(L, curve.get(), values3);

         R1 = -50;
         R2 = 0;
         curve->Init(WBFL::Geometry::Point2d(0, 0), 0.0, R1, R2, L, TransitionCurveType::Clothoid);

         std::array<std::pair<Float64, Float64>, 6> values4
         {
            std::make_pair(0, 0),
            std::make_pair(19.5464, -3.69183),
            std::make_pair(36.9765, -13.3656),
            std::make_pair(51.6311, -26.9269),
            std::make_pair(63.9511, -42.6664),
            std::make_pair(74.9797, -59.3491)
         };
         Verify(L, curve.get(), values4);
      }
	};
}
