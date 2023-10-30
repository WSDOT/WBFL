#include "pch.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace WBFL::Graphing;

namespace GraphingUnitTests
{
	TEST_CLASS(TestPointMapper)
	{
	public:
		
		TEST_METHOD(Anisotropic)
		{
			PointMapper mapper;
			mapper.SetMappingMode(PointMapper::MapMode::Anisotropic);
			mapper.SetWorldExt(5280, 5280);
			mapper.SetWorldOrg(0, 0);
			mapper.SetDeviceExt(100, 200);
			mapper.SetDeviceOrg(0, 200);
			LONG dx, dy;
			mapper.WPtoDP(0.0, 0.0, &dx, &dy);
			Assert::AreEqual((LONG)0, dx);
			Assert::AreEqual((LONG)200, dy);

			mapper.WPtoDP(5280.0, 5280.0, &dx, &dy);
			Assert::AreEqual((LONG)100, dx);
			Assert::AreEqual((LONG)0, dy);

			mapper.WPtoDP(5280.0, 0.0, &dx, &dy);
			Assert::AreEqual((LONG)100, dx);
			Assert::AreEqual((LONG)200, dy);
		}

		TEST_METHOD(Isotropic)
		{
			PointMapper mapper;
			mapper.SetMappingMode(PointMapper::MapMode::Isotropic);
			mapper.SetWorldExt(5280, 5280);
			mapper.SetWorldOrg(0, 0);
			mapper.SetDeviceExt(100, 200);
			mapper.SetDeviceOrg(0, 200);
			LONG dx, dy;
			mapper.WPtoDP(0.0, 0.0, &dx, &dy);
			Assert::AreEqual((LONG)0, dx);
			Assert::AreEqual((LONG)200, dy);

			mapper.WPtoDP(5280.0, 5280.0, &dx, &dy);
			Assert::AreEqual((LONG)100, dx);
			Assert::AreEqual((LONG)100, dy);

			mapper.WPtoDP(5280.0, 0.0, &dx, &dy);
			Assert::AreEqual((LONG)100, dx);
			Assert::AreEqual((LONG)200, dy);
		}
	};
}
