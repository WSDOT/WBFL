#include "pch.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace WBFL::LRFD;

class TestListener : public LRFRVersionMgrListener
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
	TEST_CLASS(TestLRFRVersionMgr)
	{
	public:
		
      TEST_METHOD(Version)
      {
         LRFRAutoVersion av;

         Assert::IsTrue(LRFRVersionMgr::GetLatestVersion() == LRFRVersionMgr::SetVersion(LRFRVersionMgr::Version::ThirdEdition2018));
         Assert::IsTrue(LRFRVersionMgr::Version::ThirdEdition2018 == LRFRVersionMgr::GetVersion());
      }

      TEST_METHOD(Strings)
      {
         LRFRAutoVersion av;

         Assert::AreEqual(_T("The Manual for Bridge Evaluation"), LRFRVersionMgr::GetCodeString());

         LRFRVersionMgr::SetVersion(LRFRVersionMgr::Version::SecondEdition2011);
         Assert::AreEqual(_T("Second Edition 2011"), LRFRVersionMgr::GetVersionString());
         Assert::AreEqual(_T("LRFR2011"), LRFRVersionMgr::GetVersionString(true));

         Assert::AreEqual(_T("LRFR2008"), LRFRVersionMgr::GetVersionString(LRFRVersionMgr::Version::FirstEdition2008, true));
         Assert::AreEqual(_T("First Edition 2008"), LRFRVersionMgr::GetVersionString(LRFRVersionMgr::Version::FirstEdition2008, false));

         Assert::AreEqual(_T("LRFR2010"), LRFRVersionMgr::GetVersionString(LRFRVersionMgr::Version::FirstEditionWith2010Interims, true));
         Assert::AreEqual(_T("First Edition 2008, with 2010 interim provisions"), LRFRVersionMgr::GetVersionString(LRFRVersionMgr::Version::FirstEditionWith2010Interims, false));

         Assert::AreEqual(_T("LRFR2011"), LRFRVersionMgr::GetVersionString(LRFRVersionMgr::Version::SecondEdition2011, true));
         Assert::AreEqual(_T("Second Edition 2011"), LRFRVersionMgr::GetVersionString(LRFRVersionMgr::Version::SecondEdition2011, false));

         Assert::AreEqual(_T("LRFR2011i"), LRFRVersionMgr::GetVersionString(LRFRVersionMgr::Version::SecondEditionWith2011Interims, true));
         Assert::AreEqual(_T("Second Edition 2011, with 2011 interim provisions"), LRFRVersionMgr::GetVersionString(LRFRVersionMgr::Version::SecondEditionWith2011Interims, false));

         Assert::AreEqual(_T("LRFR2013"), LRFRVersionMgr::GetVersionString(LRFRVersionMgr::Version::SecondEditionWith2013Interims, true));
         Assert::AreEqual(_T("Second Edition 2011, with 2011-2013 interim provisions"), LRFRVersionMgr::GetVersionString(LRFRVersionMgr::Version::SecondEditionWith2013Interims, false));

         Assert::AreEqual(_T("LRFR2015"), LRFRVersionMgr::GetVersionString(LRFRVersionMgr::Version::SecondEditionWith2014Interims, true));
         Assert::AreEqual(_T("Second Edition 2011, with 2011-2014 interim provisions"), LRFRVersionMgr::GetVersionString(LRFRVersionMgr::Version::SecondEditionWith2014Interims, false));

         Assert::AreEqual(_T("LRFR2015"), LRFRVersionMgr::GetVersionString(LRFRVersionMgr::Version::SecondEditionWith2015Interims, true));
         Assert::AreEqual(_T("Second Edition 2011, with 2011-2015 interim provisions"), LRFRVersionMgr::GetVersionString(LRFRVersionMgr::Version::SecondEditionWith2015Interims, false));

         Assert::AreEqual(_T("LRFR2016"), LRFRVersionMgr::GetVersionString(LRFRVersionMgr::Version::SecondEditionWith2016Interims, true));
         Assert::AreEqual(_T("Second Edition 2011, with 2011-2016 interim provisions"), LRFRVersionMgr::GetVersionString(LRFRVersionMgr::Version::SecondEditionWith2016Interims, false));

         Assert::AreEqual(_T("LRFR2018"), LRFRVersionMgr::GetVersionString(LRFRVersionMgr::Version::ThirdEdition2018, true));
         Assert::AreEqual(_T("Third Edition 2018"), LRFRVersionMgr::GetVersionString(LRFRVersionMgr::Version::ThirdEdition2018, false));

         Assert::AreEqual(_T("LRFR2020"), LRFRVersionMgr::GetVersionString(LRFRVersionMgr::Version::ThirdEditionWith2020Interims, true));
         Assert::AreEqual(_T("Third Edition 2018, with 2020 interim provisions"), LRFRVersionMgr::GetVersionString(LRFRVersionMgr::Version::ThirdEditionWith2020Interims, false));

         // these will fail when new editions are added
         // this means more tests are required for the new editions and this test needs to be updated
         // for the new last version. also update the tests below
         Assert::AreEqual(_T("LRFR2020"), LRFRVersionMgr::GetVersionString(LRFRVersionMgr::Version::LastVersion, true));
         Assert::AreEqual(_T("Third Edition 2018, with 2020 interim provisions"), LRFRVersionMgr::GetVersionString(LRFRVersionMgr::Version::LastVersion, false));

         Assert::IsTrue(LRFRVersionMgr::GetVersion(_T("LRFR2008")) == LRFRVersionMgr::Version::FirstEdition2008);
         Assert::IsTrue(LRFRVersionMgr::GetVersion(_T("LRFR2010")) == LRFRVersionMgr::Version::FirstEditionWith2010Interims);
         Assert::IsTrue(LRFRVersionMgr::GetVersion(_T("LRFR2011")) == LRFRVersionMgr::Version::SecondEdition2011);
         Assert::IsTrue(LRFRVersionMgr::GetVersion(_T("LRFR2011i")) == LRFRVersionMgr::Version::SecondEditionWith2011Interims);
         Assert::IsTrue(LRFRVersionMgr::GetVersion(_T("LRFR2013")) == LRFRVersionMgr::Version::SecondEditionWith2013Interims);
         Assert::IsTrue(LRFRVersionMgr::GetVersion(_T("LRFR2014")) == LRFRVersionMgr::Version::SecondEditionWith2014Interims);
         Assert::IsTrue(LRFRVersionMgr::GetVersion(_T("LRFR2015")) == LRFRVersionMgr::Version::SecondEditionWith2015Interims);
         Assert::IsTrue(LRFRVersionMgr::GetVersion(_T("LRFR2016")) == LRFRVersionMgr::Version::SecondEditionWith2016Interims);
         Assert::IsTrue(LRFRVersionMgr::GetVersion(_T("LRFR2018")) == LRFRVersionMgr::Version::ThirdEdition2018);
         Assert::IsTrue(LRFRVersionMgr::GetVersion(_T("LRFR2020")) == LRFRVersionMgr::Version::ThirdEditionWith2020Interims);

         Assert::ExpectException<std::invalid_argument>([]() {LRFRVersionMgr::GetVersion(_T("BadVersion")); });
      }

      TEST_METHOD(Listeners)
      {
         LRFRAutoVersion av;

         Assert::AreEqual((IndexType)0, LRFRVersionMgr::ListenerCount());

         TestListener listener;
         Assert::IsFalse(listener.bOnRegister);
         Assert::IsFalse(listener.bOnUnregister);
         Assert::IsFalse(listener.bOnUpdate);

         LRFRVersionMgr::RegisterListener(&listener);
         Assert::AreEqual((IndexType)1, LRFRVersionMgr::ListenerCount());
         Assert::IsTrue(listener.bOnRegister);
         Assert::IsFalse(listener.bOnUnregister);
         Assert::IsFalse(listener.bOnUpdate);

         LRFRVersionMgr::SetVersion(LRFRVersionMgr::Version::FirstEditionWith2010Interims);
         Assert::IsTrue(listener.bOnUpdate);

         listener.bOnUpdate = false;
         LRFRVersionMgr::BeginDamage();
         LRFRVersionMgr::SetVersion(LRFRVersionMgr::Version::SecondEditionWith2016Interims);
         Assert::IsFalse(listener.bOnUpdate);
         Assert::IsTrue(LRFRVersionMgr::IsDamaged());
         LRFRVersionMgr::EndDamage();
         Assert::IsTrue(listener.bOnUpdate);

         Assert::IsFalse(listener.bOnUnregister);
         LRFRVersionMgr::UnregisterListener(&listener);
         Assert::IsTrue(listener.bOnUnregister);

         Assert::ExpectException<std::invalid_argument>([]() {LRFRVersionMgr::UnregisterListener(nullptr); });
         Assert::ExpectException<std::invalid_argument>([&]() {LRFRVersionMgr::UnregisterListener(&listener); }); // not currently registered
      }

	};
}
