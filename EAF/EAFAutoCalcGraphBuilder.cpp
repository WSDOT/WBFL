///////////////////////////////////////////////////////////////////////
// EAF - Extensible Application Framework
// Copyright © 1999-2013  Washington State Department of Transportation
//                        Bridge and Structures Office
//
// This library is a part of the Washington Bridge Foundation Libraries
// and was developed as part of the Alternate Route Project
//
// This library is free software; you can redistribute it and/or modify it under
// the terms of the Alternate Route Library Open Source License as published by 
// the Washington State Department of Transportation, Bridge and Structures Office.
//
// This program is distributed in the hope that it will be useful, but is distributed 
// AS IS, WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY 
// or FITNESS FOR A PARTICULAR PURPOSE. See the Alternate Route Library Open Source 
// License for more details.
//
// You should have received a copy of the Alternate Route Library Open Source License 
// along with this program; if not, write to the Washington State Department of 
// Transportation, Bridge and Structures Office, P.O. Box  47340, 
// Olympia, WA 98503, USA or e-mail Bridge_Support@wsdot.wa.gov
///////////////////////////////////////////////////////////////////////


#include "stdafx.h"
#include "resource.h"
#include <EAF\EAFAutoCalcGraphBuilder.h>
#include <EAF\EAFAutoCalcGraphView.h>
#include <EAF\EAFAutoCalcDoc.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


/////////////////////////////////////////////////////////////////////////////
// CEAFAutoCalcGraphBuilder

CEAFAutoCalcGraphBuilder::CEAFAutoCalcGraphBuilder()
{
   m_bUpdateError = false;
}

CEAFAutoCalcGraphBuilder::CEAFAutoCalcGraphBuilder(const CEAFAutoCalcGraphBuilder& other) :
CEAFGraphBuilderBase(other)
{
   m_bUpdateError = false;
}

CEAFAutoCalcGraphBuilder::~CEAFAutoCalcGraphBuilder()
{
}

BEGIN_MESSAGE_MAP(CEAFAutoCalcGraphBuilder, CEAFGraphBuilderBase)
	//{{AFX_MSG_MAP(CEAFAutoCalcGraphBuilder)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


void CEAFAutoCalcGraphBuilder::Update()
{
   CEAFAutoCalcGraphView* pView = (CEAFAutoCalcGraphView*)GetView();
   CEAFAutoCalcDocMixin* pAutoCalcDoc = pView->GetAutoCalcDocument();
   if ( pAutoCalcDoc->IsAutoCalcEnabled() )
   {
      // AutoCalc is on so continue with normal processing
      CEAFGraphBuilderBase::Update();
   }
   else
   {
      // AutoCalc is off. Skip normal processing.
      // Invalid the view and force it to redraw.
      // The view's OnDraw will display a hint message to tell the user
      // how to update the contents of the view
      pView->Invalidate();
      pView->UpdateWindow();
   }
}

void CEAFAutoCalcGraphBuilder::ForceUpdate()
{
   CEAFGraphBuilderBase::Update();
}
