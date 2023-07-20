#include "pch.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace WBFL::Materials;

namespace MaterialsUnitTest
{
	TEST_CLASS(TestSimpleConcrete)
	{
	public:
		
		TEST_METHOD(Test)
		{
			SimpleConcrete concrete(_T("Test"), 10, 0.150, 0.155, 4000.0, 0.760, 0.800);
			Assert::AreEqual(_T("Test"), concrete.GetName().c_str());
			Assert::AreEqual(10.0, concrete.GetFc());
			Assert::AreEqual(0.150, concrete.GetDensity());
			Assert::AreEqual(0.155, concrete.GetDensityForWeight());
			Assert::AreEqual(4000.0, concrete.GetE());
			Assert::AreEqual(0.760, concrete.GetShearFr());
			Assert::AreEqual(0.800, concrete.GetFlexureFr());
			Assert::IsTrue(ConcreteType::Normal == concrete.GetType());

			Assert::AreEqual(_T("Normal Weight Concrete"), concrete.GetTypeName(ConcreteType::Normal, true).c_str());
			Assert::AreEqual(_T("Normal"), concrete.GetTypeName(ConcreteType::Normal, false).c_str());
			Assert::IsTrue(ConcreteType::Normal == concrete.GetTypeFromTypeName(_T("Normal")));

			Assert::AreEqual(_T("All Lightweight Concrete"), concrete.GetTypeName(ConcreteType::AllLightweight, true).c_str());
			Assert::AreEqual(_T("AllLightweight"), concrete.GetTypeName(ConcreteType::AllLightweight, false).c_str());
			Assert::IsTrue(ConcreteType::AllLightweight == concrete.GetTypeFromTypeName(_T("AllLightweight")));

			Assert::AreEqual(_T("Sand Lightweight Concrete"), concrete.GetTypeName(ConcreteType::SandLightweight, true).c_str());
			Assert::AreEqual(_T("SandLightweight"), concrete.GetTypeName(ConcreteType::SandLightweight, false).c_str());
			Assert::IsTrue(ConcreteType::SandLightweight == concrete.GetTypeFromTypeName(_T("SandLightweight")));

			Assert::AreEqual(_T("PCI Ultra High Performance Concrete (PCI-UHPC)"), concrete.GetTypeName(ConcreteType::PCI_UHPC, true).c_str());
			Assert::AreEqual(_T("PCI-UHPC"), concrete.GetTypeName(ConcreteType::PCI_UHPC, false).c_str());
			Assert::IsTrue(ConcreteType::PCI_UHPC == concrete.GetTypeFromTypeName(_T("PCI-UHPC")));

			Assert::AreEqual(_T("Ultra High Performance Concrete (UHPC)"), concrete.GetTypeName(ConcreteType::UHPC, true).c_str());
			Assert::AreEqual(_T("UHPC"), concrete.GetTypeName(ConcreteType::UHPC, false).c_str());
			Assert::IsTrue(ConcreteType::UHPC == concrete.GetTypeFromTypeName(_T("UHPC")));

			SimpleConcrete same(_T("Test"), 10, 0.150, 0.155, 4000.0, 0.760, 0.800);
			SimpleConcrete different(_T("Test"), 20, 0.150, 0.155, 4000.0, 0.760, 0.800);
			Assert::IsTrue(concrete == same);
			Assert::IsFalse(concrete != same);
			Assert::IsTrue(concrete != different);
			Assert::IsFalse(concrete == different);

		}
	};
}
