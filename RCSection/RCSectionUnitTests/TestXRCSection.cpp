#include "pch.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace WBFL::RCSection;

namespace RCSectionUnitTest
{
	TEST_CLASS(TestXRCSection)
	{
	public:
		
		TEST_METHOD(Test)
		{
			try
			{
				THROW_RCSECTION(_T("Test exception"));
			}
			catch (XRCSection& e)
			{
				Assert::AreEqual(0, e.GetReason());
			}
		}

		TEST_METHOD(TestThrow)
		{
			// Throw() performs a polymorphic re-throw of *this - distinct from the THROW_RCSECTION
			// macro's direct throw. Catching through a base-class reference confirms the concrete
			// XRCSection type is preserved by the rethrow.
			XRCSection original(_T("Original reason"), _T("SomeFile.cpp"), 42);

			try
			{
				original.Throw();
				Assert::Fail(_T("Throw() did not throw"));
			}
			catch (const WBFL::System::XBase& e)
			{
				Assert::IsTrue(dynamic_cast<const XRCSection*>(&e) != nullptr);
			}
		}

		TEST_METHOD(TestGetErrorMessage)
		{
			try
			{
				THROW_RCSECTION(_T("Something went wrong"));
				Assert::Fail(_T("THROW_RCSECTION did not throw"));
			}
			catch (XRCSection& e)
			{
				auto msg = e.GetErrorMessage();
				// the reason text supplied to THROW_RCSECTION must appear in the composed error message
				Assert::IsTrue(msg.find(_T("Something went wrong")) != std::_tstring::npos);
			}
		}
	};
}
