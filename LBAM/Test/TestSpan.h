///////////////////////////////////////////////////////////////////////
// LBAM Test - Test driver for LBAM analysis library
// Copyright © 1999-2012  Washington State Department of Transportation
//                        Bridge and Structures Office
//
// This library is a part of the Washington Bridge Foundation Libraries
// and was developed as part of the Alternate Route Project
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the Alternate Route Library Open Source License as 
// published by the Washington State Department of Transportation,
// Bridge and Structures Office.
//
// This program is distributed in the hope that it will be useful,
// but is distributed AS IS, WITHOUT ANY WARRANTY; without even the
// implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR 
// PURPOSE.  See the Alternate Route Library Open Source License for more details.
//
// You should have received a copy of the Alternate Route Library Open Source License
// along with this program; if not, write to the Washington State
// Department of Transportation, Bridge and Structures Office,
// P.O. Box 47340, Olympia, WA 98503, USA or e-mail
// Bridge_Support@wsdot.wa.gov
///////////////////////////////////////////////////////////////////////

// TestSpan.h: interface for the CTestSpan class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TESTSpan_H__4A50DAE5_753F_11D5_B02C_00105A9AF985__INCLUDED_)
#define AFX_TESTSpan_H__4A50DAE5_753F_11D5_B02C_00105A9AF985__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CTestSpan :
public CComObjectRootEx<CComSingleThreadModel>,
public ISpanEvents,
public ISpansEvents
{
public:
	static void Test();

	CTestSpan();
	virtual ~CTestSpan();

BEGIN_COM_MAP(CTestSpan)
   COM_INTERFACE_ENTRY(ISpanEvents)
   COM_INTERFACE_ENTRY(ISpansEvents)
END_COM_MAP()


public:
   STDMETHOD(OnSpanChanged)(/*[in]*/ISpan* Span, BSTR stage, ChangeType change);

   STDMETHOD(OnSpansChanged)(/*[in]*/ISpan* Span, BSTR stage, ChangeType change);
   STDMETHOD(OnSpansAdded)(ISpan* item, SpanIndexType idx);
   STDMETHOD(OnSpansBeforeRemove)(ISpan* item, SpanIndexType idx);
	STDMETHOD(OnSpansMoveTo)(SpanIndexType from, SpanIndexType to);
	STDMETHOD(OnSpansCopyTo)(SpanIndexType from, SpanIndexType to);
	STDMETHOD(OnSpansReverse)();

   HRESULT OnCreateSegment(ISpan* pseg)
   {return S_OK;}


   bool m_csStiffnessFired;
   bool m_csStressPointsFired;
   bool m_csCombinationFired;
   DWORD m_CsCookie;

};

#endif // !defined(AFX_TESTSpan_H__4A50DAE5_753F_11D5_B02C_00105A9AF985__INCLUDED_)
