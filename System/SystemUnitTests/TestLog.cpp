#include "pch.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

using namespace WBFL::Debug;

namespace SystemUnitTest
{
	class TestLogContext : public LogContext
	{
      public:
      using LogContext::LogContext;

      virtual LogContext& operator<<(const std::_tstring& s) override {m_os << s; return *this;}
      virtual LogContext& operator<<(LPCTSTR s) override { m_os << s; return *this; }
      virtual LogContext& operator<<(TCHAR ch) override { m_os << ch; return *this; }
      virtual LogContext& operator<<(DWORD n) override { m_os << n; return *this; }
      virtual LogContext& operator<<(bool n) override { m_os << n; return *this; }
      virtual LogContext& operator<<(Int16 n) override { m_os << n; return *this; }
      virtual LogContext& operator<<(Uint16 n) override { m_os << n; return *this; }
      virtual LogContext& operator<<(Int32 n) override { m_os << n; return *this; }
      virtual LogContext& operator<<(Uint32 n) override { m_os << n; return *this; }
      virtual LogContext& operator<<(Int64 n) override { m_os << n; return *this; }
      virtual LogContext& operator<<(Uint64 n) override { m_os << n; return *this; }
      virtual LogContext& operator<<(Float32 n) override { m_os << n; return *this; }
      virtual LogContext& operator<<(Float64 n) override { m_os << n; return *this; }
      virtual LogContext& operator<<(Float80 n) override { m_os << n; return *this; }
      virtual LogContext& operator<<(void* n)  override { m_os << n; return *this; }
      virtual LogContext& operator<<(const WBFL::System::SectionValue& n) override { m_os << n; return *this; }

      virtual LogContext& EndLine() { m_os << std::endl; return *this; }

      std::_tostringstream m_os;
   };

	TEST_CLASS(TestLog)
	{
	public:
		
		TEST_METHOD(Test)
		{
         TestLogContext context;
         Log log(context);

         log.LogTestResult(_T("Passed"), Log::TestResult::Passed);
         log.LogTestResult(_T("Failed"), Log::TestResult::Failed);
         log.LogTestResult(_T("NotImplemented"), Log::TestResult::NotImplemented);

         Assert::AreEqual((size_t)3, log.GetNumEntries());
         Assert::AreEqual((size_t)1, log.GetNumErrors());
         Assert::AreEqual((size_t)1, log.GetTestCount(Log::TestResult::Passed));
         Assert::AreEqual((size_t)1, log.GetTestCount(Log::TestResult::Failed));
         Assert::AreEqual((size_t)1, log.GetTestCount(Log::TestResult::NotImplemented));

         log.DumpEntireLog();
         Assert::AreEqual(_T("Passed\nFailed\nNotImplemented\n"), context.m_os.str().c_str());

         context.m_os.str(_T("")); context.m_os.clear();
         log.DumpFilteredLog(Log::TestResult::Passed);
         Assert::AreEqual(_T("Passed\n"), context.m_os.str().c_str());

         context.m_os.str(_T("")); context.m_os.clear();
         log.DumpFilteredLog(Log::TestResult::Failed);
         Assert::AreEqual(_T("Failed\n"), context.m_os.str().c_str());

         context.m_os.str(_T("")); context.m_os.clear();
         log.DumpFilteredLog(Log::TestResult::NotImplemented);
         Assert::AreEqual(_T("NotImplemented\n"), context.m_os.str().c_str());
      }
	};
}
