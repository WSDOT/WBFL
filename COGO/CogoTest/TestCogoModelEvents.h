///////////////////////////////////////////////////////////////////////
// COGOTest - Test Driver for Coordinate Geometry Library
// Copyright © 1999-2016  Washington State Department of Transportation
//                        Bridge and Structures Office
//
// This library is a part of the Washington Bridge Foundation Libraries
// and was developed as part of the Alternate Route Project
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the Alternate Route Open Source License as 
// published by the Washington State Department of Transportation,
// Bridge and Structures Office.
//
// This program is distributed in the hope that it will be useful,
// but is distributed AS IS, WITHOUT ANY WARRANTY; without even the
// implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR 
// PURPOSE.  See the Alternate Route Library Open Source License for more details.
//
// You should have received a copy of the Alternate Route Open Source License
// along with this program; if not, write to the Washington State
// Department of Transportation, Bridge and Structures Office,
// P.O. Box 47340, Olympia, WA 98503, USA or e-mail
// Bridge_Support@wsdot.wa.gov
///////////////////////////////////////////////////////////////////////

// TestCogoModelEvents.h: interface for the CTestCogoModelEvents class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TestCogoModelEvents_H__9066FECB_C9F3_11D3_8A20_006097C68A9C__INCLUDED_)
#define AFX_TestCogoModelEvents_H__9066FECB_C9F3_11D3_8A20_006097C68A9C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class ATL_NO_VTABLE CTestCogoModelEvents :
   public CComObjectRootEx<CComSingleThreadModel>,
   public ICogoModelEvents
{
public:
   CTestCogoModelEvents();

   static void Test();

   void InitEventTest() { m_bTestState = false; }
   bool PassedEventTest() { return m_bTestState; }

BEGIN_COM_MAP(CTestCogoModelEvents)
   COM_INTERFACE_ENTRY(ICogoModelEvents)
END_COM_MAP()

// ICogoModelEvents
public:
	STDMETHOD(OnPointChanged)(ICogoModel* cm,CogoElementKey key,IPoint2d* point);
	STDMETHOD(OnPointAdded)(ICogoModel* cm,CogoElementKey key,IPoint2d* point);
	STDMETHOD(OnPointRemoved)(ICogoModel* cm,CogoElementKey key);
	STDMETHOD(OnPointsCleared)(ICogoModel* cm);

	STDMETHOD(OnLineSegmentChanged)(ICogoModel* cm,CogoElementKey key,ILineSegment2d* lineSeg);
	STDMETHOD(OnLineSegmentAdded)(ICogoModel* cm,CogoElementKey key,ILineSegment2d* lineSeg);
	STDMETHOD(OnLineSegmentRemoved)(ICogoModel* cm,CogoElementKey key);
	STDMETHOD(OnLineSegmentsCleared)(ICogoModel* cm);

	STDMETHOD(OnProfilePointChanged)(ICogoModel* cm,CogoElementKey key,IProfilePoint* pp);
	STDMETHOD(OnProfilePointAdded)(ICogoModel* cm,CogoElementKey key,IProfilePoint* pp);
	STDMETHOD(OnProfilePointRemoved)(ICogoModel* cm,CogoElementKey key);
	STDMETHOD(OnProfilePointsCleared)(ICogoModel* cm);

	STDMETHOD(OnVertCurveChanged)(ICogoModel* cm,CogoElementKey key,IVertCurve* vc);
	STDMETHOD(OnVertCurveAdded)(ICogoModel* cm,CogoElementKey key,IVertCurve* vc);
	STDMETHOD(OnVertCurveRemoved)(ICogoModel* cm,CogoElementKey key);
	STDMETHOD(OnVertCurvesCleared)(ICogoModel* cm);

	STDMETHOD(OnHorzCurveChanged)(ICogoModel* cm,CogoElementKey key,IHorzCurve* hc);
	STDMETHOD(OnHorzCurveAdded)(ICogoModel* cm,CogoElementKey key,IHorzCurve* hc);
	STDMETHOD(OnHorzCurveRemoved)(ICogoModel* cm,CogoElementKey key);
	STDMETHOD(OnHorzCurvesCleared)(ICogoModel* cm);

	STDMETHOD(OnAlignmentChanged)(ICogoModel* cm,CogoElementKey key, IAlignment* alignment);
	STDMETHOD(OnProfileChanged)(ICogoModel* cm,IProfile* profile);
   STDMETHOD(OnAlignmentAdded)(ICogoModel* cm,CogoElementKey key,IAlignment* alignment);
   STDMETHOD(OnAlignmentRemoved)(ICogoModel* cm,CogoElementKey key);
   STDMETHOD(OnAlignmentsCleared)(ICogoModel* cm);

	STDMETHOD(OnPathChanged)(ICogoModel* cm,CogoElementKey key, IPath* path);
   STDMETHOD(OnPathAdded)(ICogoModel* cm,CogoElementKey key,IPath* path);
   STDMETHOD(OnPathRemoved)(ICogoModel* cm,CogoElementKey key);
   STDMETHOD(OnPathsCleared)(ICogoModel* cm);

private:
   bool m_bTestState;
   void Pass() { m_bTestState = true; }
};

#endif // !defined(AFX_TestCogoModelEvents_H__9066FECB_C9F3_11D3_8A20_006097C68A9C__INCLUDED_)
