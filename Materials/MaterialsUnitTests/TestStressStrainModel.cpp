#include "pch.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace WBFL::Materials;

namespace MaterialsUnitTest
{
	TEST_CLASS(TestStressStrainModel)
	{
	public:
		
		TEST_METHOD(Test)
		{
			// StressStrain model is an abstract base class. It doesn't do anything.
			// Nothing to test
			//Assert::Fail();
		}
	};
}
