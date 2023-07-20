#include "pch.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

using namespace WBFL::System;

namespace SystemUnitTest
{
	TEST_CLASS(TestTokenizer)
	{
	public:
		
		TEST_METHOD(Test)
		{
			Tokenizer t(_T(","));
			t.push_back(_T("30.0,40.0,50.0"));
			std::vector<std::_tstring> expected{_T("30.0"), _T("40.0"), _T("50.0")};
			std::vector<Float64> expected_double{30.0, 40.0, 50.0};
			std::vector<long> expected_long{30, 40, 50};
			std::vector<unsigned long> expected_ulong{30, 40, 50};
			std::vector<short> expected_short{30, 40, 50};
			std::vector<unsigned short> expected_ushort{30, 40, 50};
			int i = 0;
			for (auto iter = t.begin(); iter != t.end(); iter++, i++)
			{
				auto value = (*iter);
				Assert::AreEqual(expected[i].c_str(), value.c_str());
				Float64 v;
				Assert::IsTrue(Tokenizer::ParseDouble(value.c_str(), &v));
				Assert::AreEqual(expected_double[i], v);

				long l;
				Assert::IsFalse(Tokenizer::ParseLong(value.c_str(), &l));
				Assert::AreEqual(expected_long[i], l);

				unsigned long ul;
				Assert::IsFalse(Tokenizer::ParseULong(value.c_str(), &ul));
				Assert::AreEqual(expected_ulong[i], ul);

				short s;
				Assert::IsFalse(Tokenizer::ParseShort(value.c_str(), &s));
				Assert::AreEqual(expected_short[i], s);

				unsigned short us;
				Assert::IsFalse(Tokenizer::ParseUShort(value.c_str(), &us));
				Assert::AreEqual(expected_ushort[i], us);
			}
      }
	};
}
