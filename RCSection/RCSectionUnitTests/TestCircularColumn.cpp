#include "pch.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace WBFL::RCSection;

namespace RCSectionUnitTest
{
	TEST_CLASS(TestCircularColumn)
	{
	public:
		
		TEST_METHOD(Test)
		{
         CircularColumn column(72, 3, 10, 4, 60, 29000);

         auto results = column.ComputeInteraction(37);
         
         struct PM { Float64 P; Float64 M; };

         static PM datum[] = {
            {287.2848746, 10493.21979},
            {-259.9527058, 27246.45396},
            {-846.4345725, 43248.35621},
            {-1492.644891, 58743.86342},
            {-2259.446164, 74511.36885},
            {-3014.816758, 87409.23471},
            {-3844.13023, 98740.05594},
            {-4590.484531, 106425.1228},
            {-5520.696536, 112896.4532},
            {-6330.609276, 115562.4822},
            {-7160.623561, 115308.0894},
            {-7983.30927, 112623.8928},
            {-8930.346629, 106717.6939},
            {-9691.083634, 99502.87508},
            {-10539.87688, 88865.96765},
            {-11314.52527, 76585.26225},
            {-12003.65098, 63477.17158},
            {-12598.89774, 50389.12453},
            {-13233.81625, 34420.86843},
            {-13696.65124, 21339.02324},
            {-14093.40885, 8930.83373},
            {-14249.39515, 3758.73538},
            {-14263.19028, 3476.500725},
            {-14275.69861, 3216.658878},
            {-14287.07821, 2976.708707},
            {-14297.46005, 2754.506713},
            {-14306.95557, 2548.224968},
            {-14315.66016, 2356.295113},
            {-14323.65596, 2177.363962},
            {-14331.014, 2010.257996},
            {-14337.79594, 1853.954921},
            {-14344.05373, 1707.565645},
            {-14349.8368, 1570.303536},
            {-14355.18674, 1441.475904},
            {-14360.14027, 1320.470342},
            {-14364.72995, 1206.743856},
            {-14368.98471, 1099.813739}
         };

         IndexType count = results.size();
         Assert::IsTrue(count == 37);

         for (IndexType i = 0; i < count; i++)
         {
            Float64 M = results[i].first;
            Float64 P = results[i].second;

            Assert::IsTrue(IsEqual(datum[i].P, P, 0.0001));
            Assert::IsTrue(IsEqual(datum[i].M, M, 0.0001));
         }
      }
	};
}