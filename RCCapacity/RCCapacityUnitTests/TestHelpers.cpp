#include "pch.h"
#include "CppUnitTest.h"
#include "TestHelpers.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

void TestISupportUnitServer(IUnknown* punk)
{
   CComQIPtr<ISupportUnitServer> sus(punk);
   Assert::IsTrue(sus != nullptr);

   CComPtr<IUnitServer> unitServer;
   Assert::AreEqual(E_POINTER, sus->get_UnitServer(nullptr));
   Assert::AreEqual(S_OK, sus->get_UnitServer(&unitServer));
   Assert::IsTrue(unitServer != nullptr);
   Assert::AreEqual(E_INVALIDARG, sus->putref_UnitServer(nullptr));
   Assert::AreEqual(S_OK, sus->putref_UnitServer(unitServer));
}
