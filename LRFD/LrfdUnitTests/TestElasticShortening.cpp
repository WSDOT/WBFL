#include "pch.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace WBFL::LRFD;
using namespace WBFL::Geometry;

namespace LrfdUnitTests
{
	TEST_CLASS(TestElasticShortening)
	{
	public:
		
		TEST_METHOD(Test)
		{
         ElasticShortening loss(1396188351.8669250,   // jacking stress
            1396188351.8669250,   // jacking stress
            13649830.249787496, // initial relaxation
            13649830.249787496, // initial relaxation
            0.0064399871199999998,   // Area of permanent prestressing steel 
            0.00027999943999999999,   // Area of temporary prestressing steel
            true, // true if using gross section properties
            0.62990801437499999,    // area of girder
            0.39932946471524378,    // moment of inertia of girder
            0.030045082782056004,
            0.0,
            Point2d(0.0000000000000000, 0.51298403618676713), // eccentricity of permanent ps strands
            Point2d(0.0000000000000000, -1.0362262731314777), // eccentricity of temporary ps strands
            1516937.3391309734,  // Dead load moment of girder only
            1.0,     // coefficient for post-tension members (N-1)/(2N)
            34677961973.070450,   // Modulus of elasticity of concrete at transfer
            196500582855.34500,    // Modulus of elasticity of prestressing steel
            ElasticShortening::FcgpComputationMethod::Iterative);

         Assert::AreEqual(95196105.393141612, loss.PermanentStrand_ElasticShorteningLosses(), 0.0001);
         Assert::AreEqual(43118834.868635789, loss.TemporaryStrand_ElasticShorteningLosses(), 0.0001);

         loss.SetFcgpComputationMethod(ElasticShortening::FcgpComputationMethod::AssumedFpe);
         Assert::AreEqual(96316297.844561726, loss.PermanentStrand_ElasticShorteningLosses(), 0.0001);
         Assert::AreEqual(43338299.881045476, loss.TemporaryStrand_ElasticShorteningLosses(), 0.0001);

         loss.GrossProperties(false);
         loss.SetFcgpComputationMethod(ElasticShortening::FcgpComputationMethod::Iterative);
         Assert::AreEqual(102860193.25564618, loss.PermanentStrand_ElasticShorteningLosses(), 0.0001);
         Assert::AreEqual(44620361.803334452, loss.TemporaryStrand_ElasticShorteningLosses(), 0.0001);

         loss.SetFcgpComputationMethod(ElasticShortening::FcgpComputationMethod::AssumedFpe);
         Assert::AreEqual(96316297.844561726, loss.PermanentStrand_ElasticShorteningLosses(), 0.0001);
         Assert::AreEqual(43338299.881045476, loss.TemporaryStrand_ElasticShorteningLosses(), 0.0001);
      }
	};
}
