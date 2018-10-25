///////////////////////////////////////////////////////////////////////
// LBAM Live Load Test - Test driver for LBAM analysis library
// Copyright © 1999-2014, Washington State Department of Transportation, All Rights Reserved
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

// TestLiveLoadModelResponse.h: interface for the TestLiveLoadModelResponse class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TestLiveLoadModelResponse_H__0D3A1E9E_4612_4A70_B90E_98892D621FDA__INCLUDED_)
#define AFX_TestLiveLoadModelResponse_H__0D3A1E9E_4612_4A70_B90E_98892D621FDA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class TestLiveLoadModelResponse:
public CComObjectRootEx<CComSingleThreadModel>
{

public:
	TestLiveLoadModelResponse();
	virtual ~TestLiveLoadModelResponse();

	static void Test();

BEGIN_COM_MAP(TestLiveLoadModelResponse)
END_COM_MAP()

BEGIN_SINK_MAP(TestLiveLoadModelResponse)
END_SINK_MAP()

public:

};

#endif // !defined(AFX_TestLiveLoadModelResponse_H__0D3A1E9E_4612_4A70_B90E_98892D621FDA__INCLUDED_)


