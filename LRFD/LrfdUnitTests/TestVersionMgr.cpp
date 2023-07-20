#include "pch.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace WBFL::LRFD;

class TestListener : public LRFDVersionMgrListener
{
public:
   virtual void OnRegistered() { bOnRegister = true; }
   virtual void OnUnregistered() { bOnUnregister = true; }
   virtual void OnUpdate() { bOnUpdate = true; }

   bool bOnRegister = false;
   bool bOnUnregister = false;
   bool bOnUpdate = false;
};

namespace LrfdUnitTests
{
	TEST_CLASS(TestVersionMgr)
	{
	public:
		
		TEST_METHOD(VersionAndUnits)
		{
			LRFDAutoVersion av;

			Assert::IsTrue(LRFDVersionMgr::GetLatestVersion() == LRFDVersionMgr::SetVersion(LRFDVersionMgr::Version::SecondEdition1998));
			Assert::IsTrue(LRFDVersionMgr::Version::SecondEdition1998 == LRFDVersionMgr::GetVersion());

			Assert::IsTrue(LRFDVersionMgr::Units::US == LRFDVersionMgr::SetUnits(LRFDVersionMgr::Units::SI));
			Assert::IsTrue(LRFDVersionMgr::Units::SI == LRFDVersionMgr::GetUnits());

			// SI units were dropped from LRFD starting with 4th Edition 2007
			LRFDVersionMgr::SetVersion(LRFDVersionMgr::Version::FourthEdition2007); // will force to US units
			Assert::IsTrue(LRFDVersionMgr::Units::US == LRFDVersionMgr::GetUnits());

			LRFDVersionMgr::SetUnits(LRFDVersionMgr::Units::SI); // units wont change, they will stay US units
			Assert::IsTrue(LRFDVersionMgr::Units::US == LRFDVersionMgr::GetUnits());
		}

		TEST_METHOD(Strings)
		{
			LRFDAutoVersion av;

			Assert::AreEqual(_T("AASHTO LRFD Bridge Design Specifications"), LRFDVersionMgr::GetCodeString());

			LRFDVersionMgr::SetVersion(LRFDVersionMgr::Version::SecondEdition1998);
			Assert::AreEqual(_T("Second Edition 1998"), LRFDVersionMgr::GetVersionString());
			Assert::AreEqual(_T("AashtoLrfd1998"), LRFDVersionMgr::GetVersionString(true));

			Assert::AreEqual(_T("Customary U.S. Units"), LRFDVersionMgr::GetUnitString());
			LRFDVersionMgr::SetUnits(LRFDVersionMgr::Units::SI);
			Assert::AreEqual(_T("SI Units"), LRFDVersionMgr::GetUnitString());

         Assert::AreEqual(_T("AashtoLrfd1994"), LRFDVersionMgr::GetVersionString(LRFDVersionMgr::Version::FirstEdition1994, true));
         Assert::AreEqual(_T("First Edition 1994"), LRFDVersionMgr::GetVersionString(LRFDVersionMgr::Version::FirstEdition1994, false));

         Assert::AreEqual(_T("AashtoLrfd1996"), LRFDVersionMgr::GetVersionString(LRFDVersionMgr::Version::FirstEditionWith1996Interims, true));
         Assert::AreEqual(_T("First Edition 1994 with 1996 interim provisions"), LRFDVersionMgr::GetVersionString(LRFDVersionMgr::Version::FirstEditionWith1996Interims, false));

         Assert::AreEqual(_T("AashtoLrfd1997"), LRFDVersionMgr::GetVersionString(LRFDVersionMgr::Version::FirstEditionWith1997Interims, true));
         Assert::AreEqual(_T("First Edition 1994 with 1996 - 1997 interim provisions"), LRFDVersionMgr::GetVersionString(LRFDVersionMgr::Version::FirstEditionWith1997Interims, false));

         Assert::AreEqual(_T("AashtoLrfd1998"), LRFDVersionMgr::GetVersionString(LRFDVersionMgr::Version::SecondEdition1998, true));
         Assert::AreEqual(_T("Second Edition 1998"), LRFDVersionMgr::GetVersionString(LRFDVersionMgr::Version::SecondEdition1998, false));

         Assert::AreEqual(_T("AashtoLrfd1999"), LRFDVersionMgr::GetVersionString(LRFDVersionMgr::Version::SecondEditionWith1999Interims, true));
         Assert::AreEqual(_T("Second Edition 1998 with 1999 interim provisions"), LRFDVersionMgr::GetVersionString(LRFDVersionMgr::Version::SecondEditionWith1999Interims, false));

         Assert::AreEqual(_T("AashtoLrfd2000"), LRFDVersionMgr::GetVersionString(LRFDVersionMgr::Version::SecondEditionWith2000Interims, true));
         Assert::AreEqual(_T("Second Edition 1998 with 1999 - 2000 interim provisions"), LRFDVersionMgr::GetVersionString(LRFDVersionMgr::Version::SecondEditionWith2000Interims, false));

         Assert::AreEqual(_T("AashtoLrfd2001"), LRFDVersionMgr::GetVersionString(LRFDVersionMgr::Version::SecondEditionWith2001Interims, true));
         Assert::AreEqual(_T("Second Edition 1998 with 1999 - 2001 interim provisions"), LRFDVersionMgr::GetVersionString(LRFDVersionMgr::Version::SecondEditionWith2001Interims, false));

         Assert::AreEqual(_T("AashtoLrfd2002"), LRFDVersionMgr::GetVersionString(LRFDVersionMgr::Version::SecondEditionWith2002Interims, true));
         Assert::AreEqual(_T("Second Edition 1998 with 1999 - 2002 interim provisions"), LRFDVersionMgr::GetVersionString(LRFDVersionMgr::Version::SecondEditionWith2002Interims, false));

         Assert::AreEqual(_T("AashtoLrfd2003"), LRFDVersionMgr::GetVersionString(LRFDVersionMgr::Version::SecondEditionWith2003Interims, true));
         Assert::AreEqual(_T("Second Edition 1998 with 1999 - 2003 interim provisions"), LRFDVersionMgr::GetVersionString(LRFDVersionMgr::Version::SecondEditionWith2003Interims, false));

         Assert::AreEqual(_T("AashtoLrfd2004"), LRFDVersionMgr::GetVersionString(LRFDVersionMgr::Version::ThirdEdition2004, true));
         Assert::AreEqual(_T("Third Edition 2004"), LRFDVersionMgr::GetVersionString(LRFDVersionMgr::Version::ThirdEdition2004, false));

         Assert::AreEqual(_T("AashtoLrfd2005"), LRFDVersionMgr::GetVersionString(LRFDVersionMgr::Version::ThirdEditionWith2005Interims, true));
         Assert::AreEqual(_T("Third Edition 2004 with 2005 interim provisions"), LRFDVersionMgr::GetVersionString(LRFDVersionMgr::Version::ThirdEditionWith2005Interims, false));

         Assert::AreEqual(_T("AashtoLrfd2006"), LRFDVersionMgr::GetVersionString(LRFDVersionMgr::Version::ThirdEditionWith2006Interims, true));
         Assert::AreEqual(_T("Third Edition 2004 with 2005 - 2006 interim provisions"), LRFDVersionMgr::GetVersionString(LRFDVersionMgr::Version::ThirdEditionWith2006Interims, false));

         Assert::AreEqual(_T("AashtoLrfd2007"), LRFDVersionMgr::GetVersionString(LRFDVersionMgr::Version::FourthEdition2007, true));
         Assert::AreEqual(_T("4th Edition 2007"), LRFDVersionMgr::GetVersionString(LRFDVersionMgr::Version::FourthEdition2007, false));

         Assert::AreEqual(_T("AashtoLrfd2008"), LRFDVersionMgr::GetVersionString(LRFDVersionMgr::Version::FourthEditionWith2008Interims, true));
         Assert::AreEqual(_T("4th Edition 2007 with 2008 interim provisions"), LRFDVersionMgr::GetVersionString(LRFDVersionMgr::Version::FourthEditionWith2008Interims, false));

         Assert::AreEqual(_T("AashtoLrfd2009"), LRFDVersionMgr::GetVersionString(LRFDVersionMgr::Version::FourthEditionWith2009Interims, true));
         Assert::AreEqual(_T("4th Edition 2007 with 2008 - 2009 interim provisions"), LRFDVersionMgr::GetVersionString(LRFDVersionMgr::Version::FourthEditionWith2009Interims, false));

         Assert::AreEqual(_T("AashtoLrfd2010"), LRFDVersionMgr::GetVersionString(LRFDVersionMgr::Version::FifthEdition2010, true));
         Assert::AreEqual(_T("Fifth Edition 2010"), LRFDVersionMgr::GetVersionString(LRFDVersionMgr::Version::FifthEdition2010, false));

         Assert::AreEqual(_T("AashtoLrfd2012"), LRFDVersionMgr::GetVersionString(LRFDVersionMgr::Version::SixthEdition2012, true));
         Assert::AreEqual(_T("Sixth Edition 2012"), LRFDVersionMgr::GetVersionString(LRFDVersionMgr::Version::SixthEdition2012, false));

         Assert::AreEqual(_T("AashtoLrfd2013"), LRFDVersionMgr::GetVersionString(LRFDVersionMgr::Version::SixthEditionWith2013Interims, true));
         Assert::AreEqual(_T("Sixth Edition 2012 with 2013 interim provisions"), LRFDVersionMgr::GetVersionString(LRFDVersionMgr::Version::SixthEditionWith2013Interims, false));

         Assert::AreEqual(_T("AashtoLrfd2014"), LRFDVersionMgr::GetVersionString(LRFDVersionMgr::Version::SeventhEdition2014, true));
         Assert::AreEqual(_T("Seventh Edition 2014"), LRFDVersionMgr::GetVersionString(LRFDVersionMgr::Version::SeventhEdition2014, false));

         Assert::AreEqual(_T("AashtoLrfd2015"), LRFDVersionMgr::GetVersionString(LRFDVersionMgr::Version::SeventhEditionWith2015Interims, true));
         Assert::AreEqual(_T("Seventh Edition 2014 with 2015 interim provisions"), LRFDVersionMgr::GetVersionString(LRFDVersionMgr::Version::SeventhEditionWith2015Interims, false));

         Assert::AreEqual(_T("AashtoLrfd2016"), LRFDVersionMgr::GetVersionString(LRFDVersionMgr::Version::SeventhEditionWith2016Interims, true));
         Assert::AreEqual(_T("Seventh Edition 2014 with 2016 interim provisions"), LRFDVersionMgr::GetVersionString(LRFDVersionMgr::Version::SeventhEditionWith2016Interims, false));

         Assert::AreEqual(_T("AashtoLrfd2017"), LRFDVersionMgr::GetVersionString(LRFDVersionMgr::Version::EighthEdition2017, true));
         Assert::AreEqual(_T("8th Edition 2017"), LRFDVersionMgr::GetVersionString(LRFDVersionMgr::Version::EighthEdition2017, false));
   
         Assert::AreEqual(_T("AashtoLrfd2020"), LRFDVersionMgr::GetVersionString(LRFDVersionMgr::Version::NinthEdition2020, true));
         Assert::AreEqual(_T("9th Edition 2020"), LRFDVersionMgr::GetVersionString(LRFDVersionMgr::Version::NinthEdition2020, false));

         // these will fail when new editions are added
         // this means more tests are required for the new editions and this test needs to be updated
         // for the new last version. also update the tests below
         Assert::AreEqual(_T("AashtoLrfd2020"), LRFDVersionMgr::GetVersionString(LRFDVersionMgr::Version::LastVersion, true));
         Assert::AreEqual(_T("9th Edition 2020"), LRFDVersionMgr::GetVersionString(LRFDVersionMgr::Version::LastVersion, false));


         Assert::IsTrue(LRFDVersionMgr::GetVersion(_T("AashtoLrfd2020")) == LRFDVersionMgr::Version::NinthEdition2020);
         Assert::IsTrue(LRFDVersionMgr::GetVersion(_T("AashtoLrfd2017")) == LRFDVersionMgr::Version::EighthEdition2017);
         Assert::IsTrue(LRFDVersionMgr::GetVersion(_T("AashtoLrfd2016")) == LRFDVersionMgr::Version::SeventhEditionWith2016Interims);
         Assert::IsTrue(LRFDVersionMgr::GetVersion(_T("AashtoLrfd2015")) == LRFDVersionMgr::Version::SeventhEditionWith2015Interims);
         Assert::IsTrue(LRFDVersionMgr::GetVersion(_T("AashtoLrfd2014")) == LRFDVersionMgr::Version::SeventhEdition2014);
         Assert::IsTrue(LRFDVersionMgr::GetVersion(_T("AashtoLrfd2013")) == LRFDVersionMgr::Version::SixthEditionWith2013Interims);
         Assert::IsTrue(LRFDVersionMgr::GetVersion(_T("AashtoLrfd2012")) == LRFDVersionMgr::Version::SixthEdition2012);
         Assert::IsTrue(LRFDVersionMgr::GetVersion(_T("AashtoLrfd2010")) == LRFDVersionMgr::Version::FifthEdition2010);
         Assert::IsTrue(LRFDVersionMgr::GetVersion(_T("AashtoLrfd2009")) == LRFDVersionMgr::Version::FourthEditionWith2009Interims);
         Assert::IsTrue(LRFDVersionMgr::GetVersion(_T("AashtoLrfd2008")) == LRFDVersionMgr::Version::FourthEditionWith2008Interims);
         Assert::IsTrue(LRFDVersionMgr::GetVersion(_T("AashtoLrfd2007")) == LRFDVersionMgr::Version::FourthEdition2007);
         Assert::IsTrue(LRFDVersionMgr::GetVersion(_T("AashtoLrfd2006")) == LRFDVersionMgr::Version::ThirdEditionWith2006Interims);
         Assert::IsTrue(LRFDVersionMgr::GetVersion(_T("AashtoLrfd2005")) == LRFDVersionMgr::Version::ThirdEditionWith2005Interims);
         Assert::IsTrue(LRFDVersionMgr::GetVersion(_T("AashtoLrfd2004")) == LRFDVersionMgr::Version::ThirdEdition2004);
         Assert::IsTrue(LRFDVersionMgr::GetVersion(_T("AashtoLrfd2003")) == LRFDVersionMgr::Version::SecondEditionWith2003Interims);
         Assert::IsTrue(LRFDVersionMgr::GetVersion(_T("AashtoLrfd2002")) == LRFDVersionMgr::Version::SecondEditionWith2002Interims);
         Assert::IsTrue(LRFDVersionMgr::GetVersion(_T("AashtoLrfd2001")) == LRFDVersionMgr::Version::SecondEditionWith2001Interims);
         Assert::IsTrue(LRFDVersionMgr::GetVersion(_T("AashtoLrfd2000")) == LRFDVersionMgr::Version::SecondEditionWith2000Interims);
         Assert::IsTrue(LRFDVersionMgr::GetVersion(_T("AashtoLrfd1999")) == LRFDVersionMgr::Version::SecondEditionWith1999Interims);
         Assert::IsTrue(LRFDVersionMgr::GetVersion(_T("AashtoLrfd1998")) == LRFDVersionMgr::Version::SecondEdition1998);
         Assert::IsTrue(LRFDVersionMgr::GetVersion(_T("AashtoLrfd1997")) == LRFDVersionMgr::Version::FirstEditionWith1997Interims);
         Assert::IsTrue(LRFDVersionMgr::GetVersion(_T("AashtoLrfd1996")) == LRFDVersionMgr::Version::FirstEditionWith1996Interims);
         Assert::IsTrue(LRFDVersionMgr::GetVersion(_T("AashtoLrfd1994")) == LRFDVersionMgr::Version::FirstEdition1994);

         Assert::ExpectException<std::invalid_argument>([]() {LRFDVersionMgr::GetVersion(_T("BadVersion")); });
		}

      TEST_METHOD(Listeners)
      {
         Assert::AreEqual((IndexType)0, LRFDVersionMgr::ListenerCount());

         TestListener listener;
         Assert::IsFalse(listener.bOnRegister);
         Assert::IsFalse(listener.bOnUnregister);
         Assert::IsFalse(listener.bOnUpdate);

         LRFDVersionMgr::RegisterListener(&listener);
         Assert::AreEqual((IndexType)1, LRFDVersionMgr::ListenerCount());
         Assert::IsTrue(listener.bOnRegister);
         Assert::IsFalse(listener.bOnUnregister);
         Assert::IsFalse(listener.bOnUpdate);

         LRFDVersionMgr::SetVersion(LRFDVersionMgr::Version::FifthEdition2010);
         Assert::IsTrue(listener.bOnUpdate);

         listener.bOnUpdate = false;
         LRFDVersionMgr::BeginDamage();
         LRFDVersionMgr::SetVersion(LRFDVersionMgr::Version::NinthEdition2020);
         Assert::IsFalse(listener.bOnUpdate);
         Assert::IsTrue(LRFDVersionMgr::IsDamaged());
         LRFDVersionMgr::EndDamage();
         Assert::IsTrue(listener.bOnUpdate);

         Assert::IsFalse(listener.bOnUnregister);
         LRFDVersionMgr::UnregisterListener(&listener);
         Assert::IsTrue(listener.bOnUnregister);

         Assert::ExpectException<std::invalid_argument>([]() {LRFDVersionMgr::UnregisterListener(nullptr); });
         Assert::ExpectException<std::invalid_argument>([&]() {LRFDVersionMgr::UnregisterListener(&listener); }); // not currently registered
      }
	};
}
