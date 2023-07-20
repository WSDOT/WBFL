#include "pch.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace WBFL::LRFD;

namespace LrfdUnitTests
{
	TEST_CLASS(TestRebarPool)
	{
	public:
		
		TEST_METHOD(Test)
		{
			std::vector<WBFL::Materials::Rebar::Size> sizes{WBFL::Materials::Rebar::Size::bs3, WBFL::Materials::Rebar::Size::bs4, WBFL::Materials::Rebar::Size::bs5, WBFL::Materials::Rebar::Size::bs6, WBFL::Materials::Rebar::Size::bs7, WBFL::Materials::Rebar::Size::bs8, WBFL::Materials::Rebar::Size::bs9, WBFL::Materials::Rebar::Size::bs10, WBFL::Materials::Rebar::Size::bs11, WBFL::Materials::Rebar::Size::bs14, WBFL::Materials::Rebar::Size::bs18};
			std::vector<WBFL::Materials::Rebar::Type> types{WBFL::Materials::Rebar::Type::A615, WBFL::Materials::Rebar::Type::A706, WBFL::Materials::Rebar::Type::A1035};
			std::vector<WBFL::Materials::Rebar::Grade> grades{WBFL::Materials::Rebar::Grade::Grade40, WBFL::Materials::Rebar::Grade::Grade60, WBFL::Materials::Rebar::Grade::Grade75, WBFL::Materials::Rebar::Grade::Grade80, WBFL::Materials::Rebar::Grade100, WBFL::Materials::Rebar::Grade::Grade120};

			auto pool = RebarPool::GetInstance();

			for (auto type : types)
			{
				for (auto grade : grades)
				{
					for (auto size : sizes)
					{
						const auto* rebar = pool->GetRebar(type, grade, size);
						auto key = pool->GetRebarKey(rebar);
						const auto* same_rebar = pool->GetRebar(key);
						Assert::IsTrue(rebar == same_rebar);
					}
				}
			}
		}

		TEST_METHOD(MapOldRebarKey)
		{
			std::vector<Int32> old_keys{-1, 0, 3, 4, 5, 6, 7, 8, 9, 10, 11, 14, 18};
			std::vector<WBFL::Materials::Rebar::Size> sizes{WBFL::Materials::Rebar::Size::bsNone, WBFL::Materials::Rebar::Size::bsNone, WBFL::Materials::Rebar::Size::bs3, WBFL::Materials::Rebar::Size::bs4, WBFL::Materials::Rebar::Size::bs5, WBFL::Materials::Rebar::Size::bs6, WBFL::Materials::Rebar::Size::bs7, WBFL::Materials::Rebar::Size::bs8, WBFL::Materials::Rebar::Size::bs9, WBFL::Materials::Rebar::Size::bs10, WBFL::Materials::Rebar::Size::bs11, WBFL::Materials::Rebar::Size::bs14, WBFL::Materials::Rebar::Size::bs18};

			auto key_iter = old_keys.begin();
			auto end = old_keys.end();
			auto size_iter = sizes.begin();
			for (; key_iter != end; key_iter++, size_iter++)
			{
				WBFL::Materials::Rebar::Grade g;
				WBFL::Materials::Rebar::Type t;
				WBFL::Materials::Rebar::Size s;
				Assert::IsTrue(RebarPool::MapOldRebarKey(*key_iter, g, t, s));
				Assert::IsTrue(g == WBFL::Materials::Rebar::Grade::Grade60);
				Assert::IsTrue(t == WBFL::Materials::Rebar::Type::A615);
				Assert::IsTrue(s == *size_iter);
			}
		}
	};
}
