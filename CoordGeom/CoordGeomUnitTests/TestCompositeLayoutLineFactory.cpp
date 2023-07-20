#include "pch.h"
#include "CppUnitTest.h"


using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace WBFL::COGO;

namespace CoordGeomUnitTest
{
	TEST_CLASS(TestCompositeLayoutLineFactory)
	{
	public:
		
		TEST_METHOD(Test)
		{
			CompositeLayoutLineFactory composite_factory;

			SimpleLayoutLineFactory factory;
			factory.AddPath(100, nullptr);

			composite_factory.AddFactory(std::make_shared<SimpleLayoutLineFactory>(factory));
			composite_factory.AddFactory(std::make_shared<SimpleLayoutLineFactory>(factory));
			auto layout_lines = composite_factory.Create(nullptr);
			Assert::AreEqual((size_t)2, layout_lines.size());
			Assert::AreEqual((IDType)100, layout_lines.front().first);
			Assert::IsNull(layout_lines.front().second.get());
			Assert::AreEqual((IDType)100, layout_lines.back().first);
			Assert::IsNull(layout_lines.back().second.get());
		}
	};
}
