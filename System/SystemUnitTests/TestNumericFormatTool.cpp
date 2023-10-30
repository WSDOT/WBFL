#include "pch.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

using namespace WBFL::System;

namespace SystemUnitTest
{
	TEST_CLASS(TestNumericFormatTool)
	{
	public:
		
		TEST_METHOD(TestDefaults)
		{
			NumericFormatTool tool;
			Assert::IsTrue(NumericFormatTool::Format::Automatic == tool.GetFormat());
			Assert::AreEqual((Uint16)0, tool.GetWidth());
			Assert::AreEqual((Uint16)0, tool.GetPrecision());
      }

		TEST_METHOD(AsString_Automatic)
		{
			NumericFormatTool tool;
			Assert::AreEqual(_T("10.25"), tool.AsString(10.25).c_str());

			tool.SetWidth(10);
			tool.SetPrecision(2);
			Assert::AreEqual(_T("   1.2e+02"), tool.AsString(123.456789).c_str());
			Assert::AreEqual(_T("  1.23e+08"), tool.AsString(123456789.0).c_str());

			tool.SetPrecision(3);
			Assert::AreEqual(_T("       123"), tool.AsString(123.456789).c_str());
			Assert::AreEqual(_T(" 1.235e+08"), tool.AsString(123456789.0).c_str());

			tool.SetPrecision(4);
			Assert::AreEqual(_T("     123.5"), tool.AsString(123.456789).c_str());
			Assert::AreEqual(_T("1.2346e+08"), tool.AsString(123456789.0).c_str());
		}

		TEST_METHOD(AsString_Fixed)
		{
			NumericFormatTool tool;

			tool.SetFormat(NumericFormatTool::Format::Fixed);
			Assert::AreEqual(_T("10.250000"), tool.AsString(10.25).c_str());

			tool.SetWidth(10);
			tool.SetPrecision(2);
			Assert::AreEqual(_T("    123.46"), tool.AsString(123.456789).c_str());
			Assert::AreEqual(_T("  1.23e+08"), tool.AsString(123456789.0).c_str());

			tool.SetPrecision(3);
			Assert::AreEqual(_T("   123.457"), tool.AsString(123.456789).c_str());
			Assert::AreEqual(_T(" 1.235e+08"), tool.AsString(123456789.0).c_str());

			tool.SetPrecision(4);
			Assert::AreEqual(_T("  123.4568"), tool.AsString(123.456789).c_str());
			Assert::AreEqual(_T("1.2346e+08"), tool.AsString(123456789.0).c_str());
		}

		TEST_METHOD(AsString_Scientific)
		{
			NumericFormatTool tool;

			tool.SetFormat(NumericFormatTool::Format::Scientific);
			Assert::AreEqual(_T("1.025000e+01"), tool.AsString(10.25).c_str());
		
			tool.SetWidth(10);
			tool.SetPrecision(2);
			Assert::AreEqual(_T("  1.23e+02"), tool.AsString(123.456789).c_str());
			Assert::AreEqual(_T("  1.23e+08"), tool.AsString(123456789.0).c_str());

			tool.SetPrecision(3);
			Assert::AreEqual(_T(" 1.235e+02"), tool.AsString(123.456789).c_str());
			Assert::AreEqual(_T(" 1.235e+08"), tool.AsString(123456789.0).c_str());

			tool.SetPrecision(4);
			Assert::AreEqual(_T("1.2346e+02"), tool.AsString(123.456789).c_str());
			Assert::AreEqual(_T("1.2346e+08"), tool.AsString(123456789.0).c_str());
		}

		TEST_METHOD(AsString_Engineering)
		{
			NumericFormatTool tool;

			tool.SetFormat(NumericFormatTool::Format::Engineering);
			Assert::AreEqual(_T("10.e+00"), tool.AsString(10.25).c_str());

			tool.SetWidth(10);
			tool.SetPrecision(2);
			Assert::AreEqual(_T("123.4567890e+00"), tool.AsString(123.456789).c_str());
			Assert::AreEqual(_T("123.4567890e+06"), tool.AsString(123456789.0).c_str());

			tool.SetPrecision(3);
			Assert::AreEqual(_T("123.4567890e+00"), tool.AsString(123.456789).c_str());
			Assert::AreEqual(_T("123.4567890e+06"), tool.AsString(123456789.0).c_str());

			tool.SetPrecision(4);
			Assert::AreEqual(_T("123.4567890e+00"), tool.AsString(123.456789).c_str());
			Assert::AreEqual(_T("123.4567890e+06"), tool.AsString(123456789.0).c_str());
		}

		TEST_METHOD(Infinity)
		{
			NumericFormatTool tool;
			Assert::AreEqual(_T("INF"), tool.AsString(Float64_Max).c_str());
			Assert::AreEqual(_T("-INF"), tool.AsString(-Float64_Max).c_str());
		}
	};
}
