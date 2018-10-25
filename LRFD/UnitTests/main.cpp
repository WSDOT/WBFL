#include <Lrfd\UnitTest.h>
#include <iostream>

#define TEST_IT(x) \
std::cout << "Testing " << #x << "..." << (x::TestMe() ? "Passed" : "Failed") << std::endl

int main(void)
{
   bool st=0;

   dbgDiagBase::EnableWarnPopup(false);

   // create a test logger
#if defined _DEBUG
   dbgFileDumpContext dc("UnitTest_Debug.Log");
#else
   dbgFileDumpContext dc("UnitTest_Release.Log");
#endif
   dbgLog tl(&dc);


   return lrfdUnitTest::TestMe(tl);
}