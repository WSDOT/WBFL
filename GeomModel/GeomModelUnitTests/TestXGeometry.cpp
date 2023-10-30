#include "pch.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace WBFL::Geometry;

namespace GeomModelUnitTest
{
	TEST_CLASS(TestXGeometry)
	{
	public:
		TEST_METHOD(Test)
		{
			Assert::ExpectException<XGeometry>([]() {THROW_GEOMETRY(WBFL_GEOMETRY_E_INVALIDARG);});

			try
			{
				THROW_GEOMETRY(WBFL_GEOMETRY_E_INVALIDARG);
			}
			catch (XGeometry& e)
			{
				Assert::AreEqual(e.GetReason(), WBFL_GEOMETRY_E_INVALIDARG);
			}
		}
	};
}
