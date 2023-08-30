#include "pch.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace WBFL::LRFD;

class TestListener : public BDSManagerListener
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
			BDSAutoVersion av;

			Assert::IsTrue(BDSManager::GetLatestEdition() == BDSManager::SetEdition(BDSManager::Edition::SecondEdition1998));
			Assert::IsTrue(BDSManager::Edition::SecondEdition1998 == BDSManager::GetEdition());

			Assert::IsTrue(BDSManager::Units::US == BDSManager::SetUnits(BDSManager::Units::SI));
			Assert::IsTrue(BDSManager::Units::SI == BDSManager::GetUnits());

			// SI units were dropped from LRFD starting with 4th Edition 2007
			BDSManager::SetEdition(BDSManager::Edition::FourthEdition2007); // will force to US units
			Assert::IsTrue(BDSManager::Units::US == BDSManager::GetUnits());

			BDSManager::SetUnits(BDSManager::Units::SI); // units wont change, they will stay US units
			Assert::IsTrue(BDSManager::Units::US == BDSManager::GetUnits());
		}

		TEST_METHOD(Strings)
		{
			BDSAutoVersion av;

			Assert::AreEqual(_T("AASHTO LRFD Bridge Design Specifications"), BDSManager::GetSpecificationName());

			BDSManager::SetEdition(BDSManager::Edition::SecondEdition1998);
			Assert::AreEqual(_T("Second Edition 1998"), BDSManager::GetEditionAsString());
			Assert::AreEqual(_T("AashtoLrfd1998"), BDSManager::GetEditionAsString(true));

			Assert::AreEqual(_T("Customary U.S. Units"), BDSManager::GetUnitAsString());
			BDSManager::SetUnits(BDSManager::Units::SI);
			Assert::AreEqual(_T("SI Units"), BDSManager::GetUnitAsString());

         Assert::AreEqual(_T("AashtoLrfd1994"), BDSManager::GetEditionAsString(BDSManager::Edition::FirstEdition1994, true));
         Assert::AreEqual(_T("First Edition 1994"), BDSManager::GetEditionAsString(BDSManager::Edition::FirstEdition1994, false));

         Assert::AreEqual(_T("AashtoLrfd1996"), BDSManager::GetEditionAsString(BDSManager::Edition::FirstEditionWith1996Interims, true));
         Assert::AreEqual(_T("First Edition 1994 with 1996 interim provisions"), BDSManager::GetEditionAsString(BDSManager::Edition::FirstEditionWith1996Interims, false));

         Assert::AreEqual(_T("AashtoLrfd1997"), BDSManager::GetEditionAsString(BDSManager::Edition::FirstEditionWith1997Interims, true));
         Assert::AreEqual(_T("First Edition 1994 with 1996 - 1997 interim provisions"), BDSManager::GetEditionAsString(BDSManager::Edition::FirstEditionWith1997Interims, false));

         Assert::AreEqual(_T("AashtoLrfd1998"), BDSManager::GetEditionAsString(BDSManager::Edition::SecondEdition1998, true));
         Assert::AreEqual(_T("Second Edition 1998"), BDSManager::GetEditionAsString(BDSManager::Edition::SecondEdition1998, false));

         Assert::AreEqual(_T("AashtoLrfd1999"), BDSManager::GetEditionAsString(BDSManager::Edition::SecondEditionWith1999Interims, true));
         Assert::AreEqual(_T("Second Edition 1998 with 1999 interim provisions"), BDSManager::GetEditionAsString(BDSManager::Edition::SecondEditionWith1999Interims, false));

         Assert::AreEqual(_T("AashtoLrfd2000"), BDSManager::GetEditionAsString(BDSManager::Edition::SecondEditionWith2000Interims, true));
         Assert::AreEqual(_T("Second Edition 1998 with 1999 - 2000 interim provisions"), BDSManager::GetEditionAsString(BDSManager::Edition::SecondEditionWith2000Interims, false));

         Assert::AreEqual(_T("AashtoLrfd2001"), BDSManager::GetEditionAsString(BDSManager::Edition::SecondEditionWith2001Interims, true));
         Assert::AreEqual(_T("Second Edition 1998 with 1999 - 2001 interim provisions"), BDSManager::GetEditionAsString(BDSManager::Edition::SecondEditionWith2001Interims, false));

         Assert::AreEqual(_T("AashtoLrfd2002"), BDSManager::GetEditionAsString(BDSManager::Edition::SecondEditionWith2002Interims, true));
         Assert::AreEqual(_T("Second Edition 1998 with 1999 - 2002 interim provisions"), BDSManager::GetEditionAsString(BDSManager::Edition::SecondEditionWith2002Interims, false));

         Assert::AreEqual(_T("AashtoLrfd2003"), BDSManager::GetEditionAsString(BDSManager::Edition::SecondEditionWith2003Interims, true));
         Assert::AreEqual(_T("Second Edition 1998 with 1999 - 2003 interim provisions"), BDSManager::GetEditionAsString(BDSManager::Edition::SecondEditionWith2003Interims, false));

         Assert::AreEqual(_T("AashtoLrfd2004"), BDSManager::GetEditionAsString(BDSManager::Edition::ThirdEdition2004, true));
         Assert::AreEqual(_T("Third Edition 2004"), BDSManager::GetEditionAsString(BDSManager::Edition::ThirdEdition2004, false));

         Assert::AreEqual(_T("AashtoLrfd2005"), BDSManager::GetEditionAsString(BDSManager::Edition::ThirdEditionWith2005Interims, true));
         Assert::AreEqual(_T("Third Edition 2004 with 2005 interim provisions"), BDSManager::GetEditionAsString(BDSManager::Edition::ThirdEditionWith2005Interims, false));

         Assert::AreEqual(_T("AashtoLrfd2006"), BDSManager::GetEditionAsString(BDSManager::Edition::ThirdEditionWith2006Interims, true));
         Assert::AreEqual(_T("Third Edition 2004 with 2005 - 2006 interim provisions"), BDSManager::GetEditionAsString(BDSManager::Edition::ThirdEditionWith2006Interims, false));

         Assert::AreEqual(_T("AashtoLrfd2007"), BDSManager::GetEditionAsString(BDSManager::Edition::FourthEdition2007, true));
         Assert::AreEqual(_T("4th Edition 2007"), BDSManager::GetEditionAsString(BDSManager::Edition::FourthEdition2007, false));

         Assert::AreEqual(_T("AashtoLrfd2008"), BDSManager::GetEditionAsString(BDSManager::Edition::FourthEditionWith2008Interims, true));
         Assert::AreEqual(_T("4th Edition 2007 with 2008 interim provisions"), BDSManager::GetEditionAsString(BDSManager::Edition::FourthEditionWith2008Interims, false));

         Assert::AreEqual(_T("AashtoLrfd2009"), BDSManager::GetEditionAsString(BDSManager::Edition::FourthEditionWith2009Interims, true));
         Assert::AreEqual(_T("4th Edition 2007 with 2008 - 2009 interim provisions"), BDSManager::GetEditionAsString(BDSManager::Edition::FourthEditionWith2009Interims, false));

         Assert::AreEqual(_T("AashtoLrfd2010"), BDSManager::GetEditionAsString(BDSManager::Edition::FifthEdition2010, true));
         Assert::AreEqual(_T("Fifth Edition 2010"), BDSManager::GetEditionAsString(BDSManager::Edition::FifthEdition2010, false));

         Assert::AreEqual(_T("AashtoLrfd2012"), BDSManager::GetEditionAsString(BDSManager::Edition::SixthEdition2012, true));
         Assert::AreEqual(_T("Sixth Edition 2012"), BDSManager::GetEditionAsString(BDSManager::Edition::SixthEdition2012, false));

         Assert::AreEqual(_T("AashtoLrfd2013"), BDSManager::GetEditionAsString(BDSManager::Edition::SixthEditionWith2013Interims, true));
         Assert::AreEqual(_T("Sixth Edition 2012 with 2013 interim provisions"), BDSManager::GetEditionAsString(BDSManager::Edition::SixthEditionWith2013Interims, false));

         Assert::AreEqual(_T("AashtoLrfd2014"), BDSManager::GetEditionAsString(BDSManager::Edition::SeventhEdition2014, true));
         Assert::AreEqual(_T("Seventh Edition 2014"), BDSManager::GetEditionAsString(BDSManager::Edition::SeventhEdition2014, false));

         Assert::AreEqual(_T("AashtoLrfd2015"), BDSManager::GetEditionAsString(BDSManager::Edition::SeventhEditionWith2015Interims, true));
         Assert::AreEqual(_T("Seventh Edition 2014 with 2015 interim provisions"), BDSManager::GetEditionAsString(BDSManager::Edition::SeventhEditionWith2015Interims, false));

         Assert::AreEqual(_T("AashtoLrfd2016"), BDSManager::GetEditionAsString(BDSManager::Edition::SeventhEditionWith2016Interims, true));
         Assert::AreEqual(_T("Seventh Edition 2014 with 2016 interim provisions"), BDSManager::GetEditionAsString(BDSManager::Edition::SeventhEditionWith2016Interims, false));

         Assert::AreEqual(_T("AashtoLrfd2017"), BDSManager::GetEditionAsString(BDSManager::Edition::EighthEdition2017, true));
         Assert::AreEqual(_T("8th Edition 2017"), BDSManager::GetEditionAsString(BDSManager::Edition::EighthEdition2017, false));
   
         Assert::AreEqual(_T("AashtoLrfd2020"), BDSManager::GetEditionAsString(BDSManager::Edition::NinthEdition2020, true));
         Assert::AreEqual(_T("9th Edition 2020"), BDSManager::GetEditionAsString(BDSManager::Edition::NinthEdition2020, false));

         // these will fail when new editions are added
         // this means more tests are required for the new editions and this test needs to be updated
         // for the new last version. also update the tests below
         Assert::AreEqual(_T("AashtoLrfd2020"), BDSManager::GetEditionAsString(BDSManager::Edition::LastEdition, true));
         Assert::AreEqual(_T("9th Edition 2020"), BDSManager::GetEditionAsString(BDSManager::Edition::LastEdition, false));


         Assert::IsTrue(BDSManager::GetEdition(_T("AashtoLrfd2020")) == BDSManager::Edition::NinthEdition2020);
         Assert::IsTrue(BDSManager::GetEdition(_T("AashtoLrfd2017")) == BDSManager::Edition::EighthEdition2017);
         Assert::IsTrue(BDSManager::GetEdition(_T("AashtoLrfd2016")) == BDSManager::Edition::SeventhEditionWith2016Interims);
         Assert::IsTrue(BDSManager::GetEdition(_T("AashtoLrfd2015")) == BDSManager::Edition::SeventhEditionWith2015Interims);
         Assert::IsTrue(BDSManager::GetEdition(_T("AashtoLrfd2014")) == BDSManager::Edition::SeventhEdition2014);
         Assert::IsTrue(BDSManager::GetEdition(_T("AashtoLrfd2013")) == BDSManager::Edition::SixthEditionWith2013Interims);
         Assert::IsTrue(BDSManager::GetEdition(_T("AashtoLrfd2012")) == BDSManager::Edition::SixthEdition2012);
         Assert::IsTrue(BDSManager::GetEdition(_T("AashtoLrfd2010")) == BDSManager::Edition::FifthEdition2010);
         Assert::IsTrue(BDSManager::GetEdition(_T("AashtoLrfd2009")) == BDSManager::Edition::FourthEditionWith2009Interims);
         Assert::IsTrue(BDSManager::GetEdition(_T("AashtoLrfd2008")) == BDSManager::Edition::FourthEditionWith2008Interims);
         Assert::IsTrue(BDSManager::GetEdition(_T("AashtoLrfd2007")) == BDSManager::Edition::FourthEdition2007);
         Assert::IsTrue(BDSManager::GetEdition(_T("AashtoLrfd2006")) == BDSManager::Edition::ThirdEditionWith2006Interims);
         Assert::IsTrue(BDSManager::GetEdition(_T("AashtoLrfd2005")) == BDSManager::Edition::ThirdEditionWith2005Interims);
         Assert::IsTrue(BDSManager::GetEdition(_T("AashtoLrfd2004")) == BDSManager::Edition::ThirdEdition2004);
         Assert::IsTrue(BDSManager::GetEdition(_T("AashtoLrfd2003")) == BDSManager::Edition::SecondEditionWith2003Interims);
         Assert::IsTrue(BDSManager::GetEdition(_T("AashtoLrfd2002")) == BDSManager::Edition::SecondEditionWith2002Interims);
         Assert::IsTrue(BDSManager::GetEdition(_T("AashtoLrfd2001")) == BDSManager::Edition::SecondEditionWith2001Interims);
         Assert::IsTrue(BDSManager::GetEdition(_T("AashtoLrfd2000")) == BDSManager::Edition::SecondEditionWith2000Interims);
         Assert::IsTrue(BDSManager::GetEdition(_T("AashtoLrfd1999")) == BDSManager::Edition::SecondEditionWith1999Interims);
         Assert::IsTrue(BDSManager::GetEdition(_T("AashtoLrfd1998")) == BDSManager::Edition::SecondEdition1998);
         Assert::IsTrue(BDSManager::GetEdition(_T("AashtoLrfd1997")) == BDSManager::Edition::FirstEditionWith1997Interims);
         Assert::IsTrue(BDSManager::GetEdition(_T("AashtoLrfd1996")) == BDSManager::Edition::FirstEditionWith1996Interims);
         Assert::IsTrue(BDSManager::GetEdition(_T("AashtoLrfd1994")) == BDSManager::Edition::FirstEdition1994);

         Assert::ExpectException<std::invalid_argument>([]() {BDSManager::GetEdition(_T("BadVersion")); });
		}

      TEST_METHOD(Listeners)
      {
         Assert::AreEqual((IndexType)0, BDSManager::ListenerCount());

         TestListener listener;
         Assert::IsFalse(listener.bOnRegister);
         Assert::IsFalse(listener.bOnUnregister);
         Assert::IsFalse(listener.bOnUpdate);

         BDSManager::RegisterListener(&listener);
         Assert::AreEqual((IndexType)1, BDSManager::ListenerCount());
         Assert::IsTrue(listener.bOnRegister);
         Assert::IsFalse(listener.bOnUnregister);
         Assert::IsFalse(listener.bOnUpdate);

         BDSManager::SetEdition(BDSManager::Edition::FifthEdition2010);
         Assert::IsTrue(listener.bOnUpdate);

         listener.bOnUpdate = false;
         BDSManager::BeginDamage();
         BDSManager::SetEdition(BDSManager::Edition::NinthEdition2020);
         Assert::IsFalse(listener.bOnUpdate);
         Assert::IsTrue(BDSManager::IsDamaged());
         BDSManager::EndDamage();
         Assert::IsTrue(listener.bOnUpdate);

         Assert::IsFalse(listener.bOnUnregister);
         BDSManager::UnregisterListener(&listener);
         Assert::IsTrue(listener.bOnUnregister);

         Assert::ExpectException<std::invalid_argument>([]() {BDSManager::UnregisterListener(nullptr); });
         Assert::ExpectException<std::invalid_argument>([&]() {BDSManager::UnregisterListener(&listener); }); // not currently registered
      }
	};
}
