// GeometryTest.h: interface for the CGeometryTest class.
//
//////////////////////////////////////////////////////////////////////

#pragma once

class CGeometryTest  
{
public:
	static void Test();
	CGeometryTest();
	virtual ~CGeometryTest();

private:
   static void TestSize2d();
   static void TestPoint2d();
   static void TestRect2d();
   static void TestVector2d();
   static void TestPoint2dCollection();
   static void TestLineSegment2d();
   static void TestLine2d();

};

