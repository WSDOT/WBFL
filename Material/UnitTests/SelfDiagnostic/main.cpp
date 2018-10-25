#include <Material\PsStrandCurve.h>
#include <Material\LinearStressStrainCurve.h>
#include <iostream>

#define TEST_IT(x) \
std::cout << "Testing " << #x << "..." << (x::TestMe() ? "Passed" : "Failed") << std::endl

int main(void)
{
   TEST_IT( matLinearStressStrainCurve );
   TEST_IT( matPsStrandCurve );

   return 1;
}