#include "pch.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace WBFL::Geometry;

namespace GeomModelUnitTest
{
	TEST_CLASS(TestMassProperties)
	{
	public:

      TEST_METHOD(Test)
      {
         MassProperties props;

         // Default value should be zero
         Assert::IsTrue(IsZero(props.GetMassPerLength()));

         props.SetMassPerLength(50.0);
         Assert::IsTrue(IsEqual(props.GetMassPerLength(), 50.0));

         // Add mass properties
         MassProperties props2;
         props.SetMassPerLength(100);
         props2.SetMassPerLength(5.5);
         props += props2;
         Assert::IsTrue(IsEqual(props.GetMassPerLength(), 105.5));

         props.SetMassPerLength(100);
         props2.SetMassPerLength(5.5);
         props2 += props;
         Assert::IsTrue(IsEqual(props2.GetMassPerLength(), 105.5));

         props.SetMassPerLength(100);
         props2.SetMassPerLength(5.5);
         auto props3 = props + props2;
         Assert::IsTrue(IsEqual(props3.GetMassPerLength(), 105.5));

         props.SetMassPerLength(100);
         props2.SetMassPerLength(5.5);
         props3 = props2 + props;
         Assert::IsTrue(IsEqual(props3.GetMassPerLength(), 105.5));


         props.SetMassPerLength(100);
         props2.SetMassPerLength(5.5);
         props -= props2;
         Assert::IsTrue(IsEqual(props.GetMassPerLength(), 94.5));

         props.SetMassPerLength(100);
         props2.SetMassPerLength(5.5);
         props2 -= props;
         Assert::IsTrue(IsEqual(props2.GetMassPerLength(), -94.5));

         props.SetMassPerLength(100);
         props2.SetMassPerLength(5.5);
         props3 = props - props2;
         Assert::IsTrue(IsEqual(props3.GetMassPerLength(), 94.5));

         props.SetMassPerLength(100);
         props2.SetMassPerLength(5.5);
         props3 = props2 - props;
         Assert::IsTrue(IsEqual(props3.GetMassPerLength(), -94.5));
      }
	};
}
