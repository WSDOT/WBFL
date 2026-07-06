#include "pch.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace WBFL::Units;

namespace UnitsUnitTest
{
   TEST_CLASS(TestAnnotatedDisplayUnitFormatter)
   {
   public:

      TEST_METHOD(TestDefaultValues)
      {
         AnnotatedDisplayUnitFormatter formatter;
         Assert::AreEqual((Uint32)0, formatter.GetOffsetDigits());
         Assert::IsTrue(IsEqual(formatter.GetMultiplier(), 12.0));
         Assert::IsTrue(formatter.GetAnnotation() == std::_tstring(_T("ft-,in")));
         Assert::AreEqual((Uint32)0, formatter.GetWidth());
         Assert::AreEqual((Uint32)6, formatter.GetPrecision());
         Assert::IsTrue(formatter.GetNotation() == WBFL::System::NumericFormatTool::Format::Automatic);
         Assert::IsTrue(formatter.GetJustification() == AnnotatedDisplayUnitFormatter::Justify::Right);
      }

      TEST_METHOD(TestFeetInches)
      {
         AnnotatedDisplayUnitFormatter formatter;
         formatter.SetOffsetDigits(0);
         formatter.SetMultiplier(12.0);
         formatter.SetFormatSpecifiers(6, 3, AnnotatedDisplayUnitFormatter::Justify::Right, WBFL::System::NumericFormatTool::Format::Fixed, 0.0001);
         formatter.SetAnnotation(_T("ft-,in"));

         Assert::IsTrue(formatter.GetAnnotation() == std::_tstring(_T("ft-,in")));

         Assert::IsTrue(formatter.AsString(1.5) == std::_tstring(_T("1ft-6.000in")));
         Assert::IsTrue(formatter.AsString(-1.5) == std::_tstring(_T("-1ft-6.000in")));
         Assert::IsTrue(formatter.AsString(54.9999999) == std::_tstring(_T("55ft-0.000in")));
         Assert::IsTrue(formatter.AsString(1.91666666666666666666667) == std::_tstring(_T("1ft-11.000in")));

         Assert::IsTrue(formatter.AsString(1.5, false) == std::_tstring(_T("1 6.000")));
         Assert::IsTrue(formatter.AsString(1.9166666666666666667, false) == std::_tstring(_T("1 11.000")));
      }

      TEST_METHOD(TestFeetInchesFraction)
      {
         AnnotatedDisplayUnitFormatter formatter;
         formatter.SetOffsetDigits(0);
         formatter.SetMultiplier(12.0);
         formatter.SetAnnotation(_T("' ,\""));
         formatter.SetFormatSpecifiers(0, 0, AnnotatedDisplayUnitFormatter::Justify::Right, WBFL::System::NumericFormatTool::Format::Fixed, 0.0001);

         Assert::IsTrue(formatter.AsString(1.25) == std::_tstring(_T("1' 3\"")));
         Assert::IsTrue(formatter.AsString(1.25, false) == std::_tstring(_T("1 3")));
         Assert::IsTrue(formatter.AsString(1.9166666666666666667) == std::_tstring(_T("1' 11\"")));
         Assert::IsTrue(formatter.AsString(1.9166666666666666667, false) == std::_tstring(_T("1 11")));
         Assert::IsTrue(formatter.AsString(1.9999999999999999999, false) == std::_tstring(_T("2 0")));
      }

      TEST_METHOD(TestUSStationing)
      {
         AnnotatedDisplayUnitFormatter formatter;
         formatter.SetOffsetDigits(2);
         formatter.SetMultiplier(1.0);
         formatter.SetAnnotation(_T("+"));
         formatter.SetFormatSpecifiers(4, 2, AnnotatedDisplayUnitFormatter::Justify::Right, WBFL::System::NumericFormatTool::Format::Fixed, 0.0001);

         Assert::IsTrue(formatter.AsString(123.456) == std::_tstring(_T("1+23.46")));
         Assert::IsTrue(formatter.AsString(69500.00) == std::_tstring(_T("695+00.00")));
         Assert::IsTrue(formatter.AsString(-999.99) == std::_tstring(_T("-9+99.99")));
         Assert::IsTrue(formatter.AsString(14800.019) == std::_tstring(_T("148+00.02")));
         Assert::IsTrue(formatter.AsString(14800.0019) == std::_tstring(_T("148+00.00")));
      }

      TEST_METHOD(TestSIStationingAndWidthJustification)
      {
         AnnotatedDisplayUnitFormatter formatter;
         formatter.SetOffsetDigits(3);
         formatter.SetMultiplier(1.0);
         formatter.SetAnnotation(_T("+"));
         formatter.SetFormatSpecifiers(6, 3, AnnotatedDisplayUnitFormatter::Justify::Right, WBFL::System::NumericFormatTool::Format::Fixed, 0.0001);

         Assert::IsTrue(formatter.AsString(123.456) == std::_tstring(_T("0+123.456")));

         // Annotated Display Unit Formatter ignores numeric format type (Notation), but
         // does apply width, precision, and justification
         formatter.SetFormatSpecifiers(14, 3, AnnotatedDisplayUnitFormatter::Justify::Right, WBFL::System::NumericFormatTool::Format::Fixed, 0.0001);
         Assert::IsTrue(formatter.AsString(123.456) == std::_tstring(_T("     0+123.456")));

         formatter.SetFormatSpecifiers(14, 3, AnnotatedDisplayUnitFormatter::Justify::Left, WBFL::System::NumericFormatTool::Format::Fixed, 0.0001);
         Assert::IsTrue(formatter.AsString(123.456) == std::_tstring(_T("0+123.456     ")));

         formatter.SetFormatSpecifiers(14, 3, AnnotatedDisplayUnitFormatter::Justify::Right, WBFL::System::NumericFormatTool::Format::Automatic, 0.0001);
         Assert::IsTrue(formatter.AsString(123.456) == std::_tstring(_T("     0+123.456")));

         formatter.SetFormatSpecifiers(14, 3, AnnotatedDisplayUnitFormatter::Justify::Left, WBFL::System::NumericFormatTool::Format::Automatic, 0.0001);
         Assert::IsTrue(formatter.AsString(123.456) == std::_tstring(_T("0+123.456     ")));

         formatter.SetFormatSpecifiers(14, 3, AnnotatedDisplayUnitFormatter::Justify::Right, WBFL::System::NumericFormatTool::Format::Scientific, 0.0001);
         Assert::IsTrue(formatter.AsString(123.456) == std::_tstring(_T("     0+123.456")));

         formatter.SetFormatSpecifiers(14, 3, AnnotatedDisplayUnitFormatter::Justify::Left, WBFL::System::NumericFormatTool::Format::Scientific, 0.0001);
         Assert::IsTrue(formatter.AsString(123.456) == std::_tstring(_T("0+123.456     ")));

         formatter.SetFormatSpecifiers(14, 3, AnnotatedDisplayUnitFormatter::Justify::Right, WBFL::System::NumericFormatTool::Format::Engineering, 0.0001);
         Assert::IsTrue(formatter.AsString(123.456) == std::_tstring(_T("     0+123.456")));

         formatter.SetFormatSpecifiers(14, 3, AnnotatedDisplayUnitFormatter::Justify::Left, WBFL::System::NumericFormatTool::Format::Engineering, 0.0001);
         Assert::IsTrue(formatter.AsString(123.456) == std::_tstring(_T("0+123.456     ")));
      }

      TEST_METHOD(TestOddAnnotations)
      {
         AnnotatedDisplayUnitFormatter formatter;
         formatter.SetOffsetDigits(0);
         formatter.SetMultiplier(12.0);
         formatter.SetFormatSpecifiers(0, 3, AnnotatedDisplayUnitFormatter::Justify::Right, WBFL::System::NumericFormatTool::Format::Fixed, 0.0001);

         // leads with the delimiter -- no separator, "Junk" is the suffix
         formatter.SetAnnotation(_T(",Junk"));
         Assert::IsTrue(formatter.AsString(1.5) == std::_tstring(_T("16.000Junk")));

         // separator is a single space, "Junk" is the suffix
         formatter.SetAnnotation(_T(" ,Junk"));
         Assert::IsTrue(formatter.AsString(1.5) == std::_tstring(_T("1 6.000Junk")));
      }
   };
}
