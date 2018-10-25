// GeometryTest.h: interface for the CGeometryTest class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GEOMETRYTEST_H__9ACFED6A_9EBA_11D3_8CDF_C5F740C1124A__INCLUDED_)
#define AFX_GEOMETRYTEST_H__9ACFED6A_9EBA_11D3_8CDF_C5F740C1124A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

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

#endif // !defined(AFX_GEOMETRYTEST_H__9ACFED6A_9EBA_11D3_8CDF_C5F740C1124A__INCLUDED_)
