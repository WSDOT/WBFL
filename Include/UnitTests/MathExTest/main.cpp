#include <iostream>
#include <MathEx.h>

int main(void)
{
   // Zeroness checks
   double a;
   double b;

   a = 1.00001;
   b = 1.00002;
   std::cout << "(" << a << " == " << b << ") = " << (IsEqual(a,b)?"true":"false") << std::endl;

   a = 1.0000001;
   b = 1.0000002;
   std::cout << "(" << a << " == " << b << ") = " << (IsEqual(a,b)?"true":"false") << std::endl;

   a = 1.000001e20;
   b = 1.000002e20;
   std::cout << "(" << a << " == " << b << ") = " << (IsEqual(a,b)?"true":"false") << std::endl;

   a = 1.1e20;
   b = 1.2e20;
   std::cout << "(" << a << " == " << b << ") = " << (IsEqual(a,b)?"true":"false") << std::endl;
   
   a = 12.3456789;
   b = 12.3456789;
   std::cout << "(" << a << " == " << b << ") = " << (IsEqual(a,b)?"true":"false") << std::endl;
   
   a = 12.3456798;
   b = 12.3456789;
   std::cout << "(" << a << " == " << b << ") = " << (IsEqual(a,b)?"true":"false") << std::endl;

   a = 0.;
   b = 1.;
   std::cout << "(" << a << " == " << b << ") = " << (IsEqual(a,b)?"true":"false") << std::endl;

   a = 1.;
   b = 0.;
   std::cout << "(" << a << " == " << b << ") = " << (IsEqual(a,b)?"true":"false") << std::endl;

   a = 0.;
   b = 0.;
   std::cout << "(" << a << " == " << b << ") = " << (IsEqual(a,b)?"true":"false") << std::endl;

   a = 1e-20;
   b = 1e-10;
   std::cout << "(" << a << " == " << b << ") = " << (IsEqual(a,b)?"true":"false") << std::endl;

   return 1;
}