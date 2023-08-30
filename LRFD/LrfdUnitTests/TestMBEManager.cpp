#include "pch.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace WBFL::LRFD;

class TestListener : public MBEManagerListener
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
	TEST_CLASS(TestMBEManager)
	{
	public:
		
      TEST_METHOD(Version)
      {
         MBEAutoVersion av;

         Assert::IsTrue(MBEManager::GetLatestEdition() == MBEManager::SetEdition(MBEManager::Edition::ThirdEdition2018));
         Assert::IsTrue(MBEManager::Edition::ThirdEdition2018 == MBEManager::GetEdition());
      }

      TEST_METHOD(Strings)
      {
         MBEAutoVersion av;

         Assert::AreEqual(_T("The Manual for Bridge Evaluation"), MBEManager::GetSpecificationName());

         MBEManager::SetEdition(MBEManager::Edition::SecondEdition2011);
         Assert::AreEqual(_T("Second Edition 2011"), MBEManager::GetEditionAsString());
         Assert::AreEqual(_T("LRFR2011"), MBEManager::GetEditionAsString(true));

         Assert::AreEqual(_T("LRFR2008"), MBEManager::GetEditionAsString(MBEManager::Edition::FirstEdition2008, true));
         Assert::AreEqual(_T("First Edition 2008"), MBEManager::GetEditionAsString(MBEManager::Edition::FirstEdition2008, false));

         Assert::AreEqual(_T("LRFR2010"), MBEManager::GetEditionAsString(MBEManager::Edition::FirstEditionWith2010Interims, true));
         Assert::AreEqual(_T("First Edition 2008, with 2010 interim provisions"), MBEManager::GetEditionAsString(MBEManager::Edition::FirstEditionWith2010Interims, false));

         Assert::AreEqual(_T("LRFR2011"), MBEManager::GetEditionAsString(MBEManager::Edition::SecondEdition2011, true));
         Assert::AreEqual(_T("Second Edition 2011"), MBEManager::GetEditionAsString(MBEManager::Edition::SecondEdition2011, false));

         Assert::AreEqual(_T("LRFR2011i"), MBEManager::GetEditionAsString(MBEManager::Edition::SecondEditionWith2011Interims, true));
         Assert::AreEqual(_T("Second Edition 2011, with 2011 interim provisions"), MBEManager::GetEditionAsString(MBEManager::Edition::SecondEditionWith2011Interims, false));

         Assert::AreEqual(_T("LRFR2013"), MBEManager::GetEditionAsString(MBEManager::Edition::SecondEditionWith2013Interims, true));
         Assert::AreEqual(_T("Second Edition 2011, with 2011-2013 interim provisions"), MBEManager::GetEditionAsString(MBEManager::Edition::SecondEditionWith2013Interims, false));

         Assert::AreEqual(_T("LRFR2015"), MBEManager::GetEditionAsString(MBEManager::Edition::SecondEditionWith2014Interims, true));
         Assert::AreEqual(_T("Second Edition 2011, with 2011-2014 interim provisions"), MBEManager::GetEditionAsString(MBEManager::Edition::SecondEditionWith2014Interims, false));

         Assert::AreEqual(_T("LRFR2015"), MBEManager::GetEditionAsString(MBEManager::Edition::SecondEditionWith2015Interims, true));
         Assert::AreEqual(_T("Second Edition 2011, with 2011-2015 interim provisions"), MBEManager::GetEditionAsString(MBEManager::Edition::SecondEditionWith2015Interims, false));

         Assert::AreEqual(_T("LRFR2016"), MBEManager::GetEditionAsString(MBEManager::Edition::SecondEditionWith2016Interims, true));
         Assert::AreEqual(_T("Second Edition 2011, with 2011-2016 interim provisions"), MBEManager::GetEditionAsString(MBEManager::Edition::SecondEditionWith2016Interims, false));

         Assert::AreEqual(_T("LRFR2018"), MBEManager::GetEditionAsString(MBEManager::Edition::ThirdEdition2018, true));
         Assert::AreEqual(_T("Third Edition 2018"), MBEManager::GetEditionAsString(MBEManager::Edition::ThirdEdition2018, false));

         Assert::AreEqual(_T("LRFR2020"), MBEManager::GetEditionAsString(MBEManager::Edition::ThirdEditionWith2020Interims, true));
         Assert::AreEqual(_T("Third Edition 2018, with 2020 interim provisions"), MBEManager::GetEditionAsString(MBEManager::Edition::ThirdEditionWith2020Interims, false));

         // these will fail when new editions are added
         // this means more tests are required for the new editions and this test needs to be updated
         // for the new last version. also update the tests below
         Assert::AreEqual(_T("LRFR2020"), MBEManager::GetEditionAsString(MBEManager::Edition::LastEdition, true));
         Assert::AreEqual(_T("Third Edition 2018, with 2020 interim provisions"), MBEManager::GetEditionAsString(MBEManager::Edition::LastEdition, false));

         Assert::IsTrue(MBEManager::GetEdition(_T("LRFR2008")) == MBEManager::Edition::FirstEdition2008);
         Assert::IsTrue(MBEManager::GetEdition(_T("LRFR2010")) == MBEManager::Edition::FirstEditionWith2010Interims);
         Assert::IsTrue(MBEManager::GetEdition(_T("LRFR2011")) == MBEManager::Edition::SecondEdition2011);
         Assert::IsTrue(MBEManager::GetEdition(_T("LRFR2011i")) == MBEManager::Edition::SecondEditionWith2011Interims);
         Assert::IsTrue(MBEManager::GetEdition(_T("LRFR2013")) == MBEManager::Edition::SecondEditionWith2013Interims);
         Assert::IsTrue(MBEManager::GetEdition(_T("LRFR2014")) == MBEManager::Edition::SecondEditionWith2014Interims);
         Assert::IsTrue(MBEManager::GetEdition(_T("LRFR2015")) == MBEManager::Edition::SecondEditionWith2015Interims);
         Assert::IsTrue(MBEManager::GetEdition(_T("LRFR2016")) == MBEManager::Edition::SecondEditionWith2016Interims);
         Assert::IsTrue(MBEManager::GetEdition(_T("LRFR2018")) == MBEManager::Edition::ThirdEdition2018);
         Assert::IsTrue(MBEManager::GetEdition(_T("LRFR2020")) == MBEManager::Edition::ThirdEditionWith2020Interims);

         Assert::ExpectException<std::invalid_argument>([]() {MBEManager::GetEdition(_T("BadVersion")); });
      }

      TEST_METHOD(Listeners)
      {
         MBEAutoVersion av;

         Assert::AreEqual((IndexType)0, MBEManager::ListenerCount());

         TestListener listener;
         Assert::IsFalse(listener.bOnRegister);
         Assert::IsFalse(listener.bOnUnregister);
         Assert::IsFalse(listener.bOnUpdate);

         MBEManager::RegisterListener(&listener);
         Assert::AreEqual((IndexType)1, MBEManager::ListenerCount());
         Assert::IsTrue(listener.bOnRegister);
         Assert::IsFalse(listener.bOnUnregister);
         Assert::IsFalse(listener.bOnUpdate);

         MBEManager::SetEdition(MBEManager::Edition::FirstEditionWith2010Interims);
         Assert::IsTrue(listener.bOnUpdate);

         listener.bOnUpdate = false;
         MBEManager::BeginDamage();
         MBEManager::SetEdition(MBEManager::Edition::SecondEditionWith2016Interims);
         Assert::IsFalse(listener.bOnUpdate);
         Assert::IsTrue(MBEManager::IsDamaged());
         MBEManager::EndDamage();
         Assert::IsTrue(listener.bOnUpdate);

         Assert::IsFalse(listener.bOnUnregister);
         MBEManager::UnregisterListener(&listener);
         Assert::IsTrue(listener.bOnUnregister);

         Assert::ExpectException<std::invalid_argument>([]() {MBEManager::UnregisterListener(nullptr); });
         Assert::ExpectException<std::invalid_argument>([&]() {MBEManager::UnregisterListener(&listener); }); // not currently registered
      }

	};
}
