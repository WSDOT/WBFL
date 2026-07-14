#include "pch.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace WBFL::Units;

namespace UnitsUnitTest
{
	TEST_CLASS(TestLibrary)
	{
	public:

		TEST_METHOD(Test)
		{
			Library library;

			Assert::IsFalse(library.Contains(_T("US")));

			IndirectMeasure us;
			us.Name = _T("US");
			library.AddEntry(_T("US"), us);

			Assert::IsTrue(library.Contains(_T("US")));
			Assert::IsFalse(library.Contains(_T("SI")));

			IndirectMeasure& entry = library.GetEntry(_T("US"));
			Assert::AreEqual(_T("US"), entry.Name.c_str());

			const Library& constLibrary = library;
			IndirectMeasure copy = constLibrary.GetEntry(_T("US"));
			Assert::AreEqual(_T("US"), copy.Name.c_str());

			Assert::ExpectException<EntryNotFound>([&library]() { library.GetEntry(_T("SI")); });

			library.RemoveEntry(_T("US"));
			Assert::IsFalse(library.Contains(_T("US")));
		}
	};
}
