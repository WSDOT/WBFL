#include "pch.h"
#include "CppUnitTest.h"


using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace WBFL::COGO;

namespace CoordGeomUnitTest
{
	TEST_CLASS(TestSimpleLayoutLineFactory)
	{
	public:
		
		TEST_METHOD(Test)
		{
			SimpleLayoutLineFactory factory;
			factory.AddPath(100, nullptr);
			auto layout_lines = factory.Create(nullptr);
			Assert::AreEqual((size_t)1, layout_lines.size());
			Assert::AreEqual((IDType)100, layout_lines.front().first);
			Assert::IsNull(layout_lines.front().second.get());
		}
	};
}
