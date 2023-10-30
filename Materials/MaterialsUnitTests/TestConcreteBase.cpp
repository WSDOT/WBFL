#include "pch.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace WBFL::Materials;

namespace MaterialsUnitTest
{
	TEST_CLASS(TestConcreteBase)
	{
	public:
		
		TEST_METHOD(Test)
		{
			Assert::AreEqual(_T("Normal Weight Concrete"), ConcreteBase::GetTypeName(ConcreteType::Normal, true).c_str());
			Assert::AreEqual(_T("Normal"), ConcreteBase::GetTypeName(ConcreteType::Normal, false).c_str());
			Assert::IsTrue(ConcreteType::Normal == ConcreteBase::GetTypeFromTypeName(_T("Normal")));

			Assert::AreEqual(_T("All Lightweight Concrete"), ConcreteBase::GetTypeName(ConcreteType::AllLightweight, true).c_str());
			Assert::AreEqual(_T("AllLightweight"), ConcreteBase::GetTypeName(ConcreteType::AllLightweight, false).c_str());
			Assert::IsTrue(ConcreteType::AllLightweight == ConcreteBase::GetTypeFromTypeName(_T("AllLightweight")));

			Assert::AreEqual(_T("Sand Lightweight Concrete"), ConcreteBase::GetTypeName(ConcreteType::SandLightweight, true).c_str());
			Assert::AreEqual(_T("SandLightweight"), ConcreteBase::GetTypeName(ConcreteType::SandLightweight, false).c_str());
			Assert::IsTrue(ConcreteType::SandLightweight == ConcreteBase::GetTypeFromTypeName(_T("SandLightweight")));

			Assert::AreEqual(_T("PCI Ultra High Performance Concrete (PCI-UHPC)"), ConcreteBase::GetTypeName(ConcreteType::PCI_UHPC, true).c_str());
			Assert::AreEqual(_T("PCI-UHPC"), ConcreteBase::GetTypeName(ConcreteType::PCI_UHPC, false).c_str());
			Assert::IsTrue(ConcreteType::PCI_UHPC == ConcreteBase::GetTypeFromTypeName(_T("PCI-UHPC")));

			Assert::AreEqual(_T("Ultra High Performance Concrete (UHPC)"), ConcreteBase::GetTypeName(ConcreteType::UHPC, true).c_str());
			Assert::AreEqual(_T("UHPC"), ConcreteBase::GetTypeName(ConcreteType::UHPC, false).c_str());
			Assert::IsTrue(ConcreteType::UHPC == ConcreteBase::GetTypeFromTypeName(_T("UHPC")));
		}
	};
}
