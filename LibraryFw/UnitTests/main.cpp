
#include <wbfl.h>
#include <fstream>
#include <iostream>
#include <LibraryFw\UnitTest.h>


int main()
{
   std::ofstream os("UnitTest.Log");
   dbgLog rlog(os);
   // test library persistence
   libUnitTest::TestMe(rlog);

   return 0;
};


