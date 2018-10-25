#pragma once
#include <WBFLCogo.h>
#include <WBFLBridgeGeometry.h>

class CTestBridge
{
public:
   CTestBridge(void);
   ~CTestBridge(void);
   static void Test(void);

private:
   static void Test1();
   static void Test2();
   static void Test3();
   static void Test4();
   static void TestDiaphragmLayout();
   static void TestSlabLayout();

   static void CreateStraightAlignment(Float64 refStation,Float64 x,Float64 y,Float64 direction,IAlignment** ppAlignment);
   static void CreateBridge(IBridgeGeometry** ppBridge);
};
