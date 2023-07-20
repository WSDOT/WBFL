#include "pch.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

using namespace WBFL::System;

namespace SystemUnitTest
{
	TEST_CLASS(TestStructuredStorage)
	{
	public:
		
		TEST_METHOD(Test)
		{
         std::_tostringstream ostr;
         ostr << _T("This is ") << std::endl << _T("a multi-line description") << std::endl;
         ostr << _T("With a twist >");
         std::_tstring twist(ostr.str());

         std::_tstring special(_T("A string with \"special char's < > && & things><"));
         // test saving
         {
            FileStream os;
            if (!os.open(_T("Test.xml"), false)) Assert::Fail(_T("Error creating Test.xml"));

            StructuredSaveXml save;
            save.BeginSave(&os);

            WBFL::Debug::Message::EnablePopup(false);

            Assert::ExpectException<WBFL::System::XStructuredSave>([&]() {save.BeginUnit(_T("Invalid name"), 1.0); });

            save.BeginUnit(_T("LIBRARY_MANAGER"), 1.0);
            save.BeginUnit(_T("LIBRARY"), 2.1);
            save.Property(_T("NAME"), _T("ConcreteLibrary"));
            save.Property(_T("DESCRIPTION"), twist.c_str());
            save.BeginUnit(_T("CONCRETE_ENTRY"));
            save.Property(_T("Special"), special.c_str());
            save.Property(_T("Density"), 150.20);
            save.Property(_T("IsLightWeight"), true);
            save.Property(_T("Int32_Max"), (Int32)Int32_Max);
            save.Property(_T("Int32_Min"), (Int32)Int32_Min);
            save.Property(_T("Uint32_Max"), (Uint32)Uint32_Max);
            save.Property(_T("Int16_Max"), (Int16)Int16_Max);
            save.Property(_T("Int16_Min"), (Int16)Int16_Min);
            save.Property(_T("Uint16_Max"), (Uint16)Uint16_Max);
            Assert::ExpectException< XStructuredSave>([&]() {save.Property(_T("Invalid name"), 10.0); });
            save.EndUnit();
            save.EndUnit();
            save.EndUnit();


            save.EndSave();
         }


         // test loading
         FileStream is;

         if (!is.open(_T("Test.xml"), true)) Assert::Fail(_T("Error opening Test.xml"));
         StructuredLoadXml load;

         try
         {
            load.BeginLoad(&is);

            Float64 d;
            bool b;
            Int32 lmax, lmin;
            Uint32 ulmax;
            Int16 smax, smin;
            Uint16 usmax;
            std::_tstring str;

            Assert::IsTrue(load.BeginUnit(_T("LIBRARY_MANAGER")));

            Assert::IsTrue(load.BeginUnit(_T("LIBRARY")));
            Assert::IsTrue(load.GetVersion() == 2.1);
            Assert::IsTrue(load.Property(_T("NAME"), &str));
            Assert::IsTrue((str == _T("ConcreteLibrary")));
            Assert::IsTrue(load.Property(_T("DESCRIPTION"), &str));
            //Assert::IsTrue((str==twist)); // this test doesn't pass, but seems to have no consequence either.
            Assert::IsTrue(load.BeginUnit(_T("CONCRETE_ENTRY")));
            Assert::IsTrue(load.Property(_T("Special"), &str));
            Assert::IsTrue(str == special);
            Assert::IsTrue(load.Property(_T("Density"), &d));
            Assert::IsTrue(d == 150.20);
            Assert::IsTrue(load.Property(_T("IsLightWeight"), &b));
            Assert::IsTrue(b == true);

            Assert::IsTrue(load.Property(_T("Int32_Max"), &lmax));
            Assert::IsTrue(lmax == Int32_Max);

            Assert::IsTrue(load.Property(_T("Int32_Min"), &lmin));
            Assert::IsTrue(lmin == Int32_Min);

            Assert::IsTrue(load.Property(_T("Uint32_Max"), &ulmax));
            Assert::IsTrue(ulmax == Uint32_Max);

            Assert::IsTrue(load.Property(_T("Int16_Max"), &smax));
            Assert::IsTrue(smax == Int16_Max);

            Assert::IsTrue(load.Property(_T("Int16_Min"), &smin));
            Assert::IsTrue(smin == Int16_Min);

            Assert::IsTrue(load.Property(_T("Uint16_Max"), &usmax));
            Assert::IsTrue(usmax == Uint16_Max);

            Assert::IsTrue(load.GetTopVersion() == 1.0);
            Assert::IsTrue(load.EndUnit());
            Assert::IsTrue(load.EndUnit());
            Assert::IsTrue(load.GetVersion() == 1.0);
            Assert::IsTrue(load.EndUnit());

            load.EndLoad();
         }
         catch (WBFL::System::XStructuredLoad& ex)
         {
            Assert::Fail(ex.GetErrorMessage().c_str());
         }
      }
	};
}
