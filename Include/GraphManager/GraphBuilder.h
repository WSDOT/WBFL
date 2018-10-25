///////////////////////////////////////////////////////////////////////
// GraphManager - Manages graph definitions
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

// GraphManager.h: interface for the CGraphManager class.
//
//////////////////////////////////////////////////////////////////////

#pragma once

#include <GraphManager\GraphManagerExp.h>

//////////////////////////////////////////////////////
// CGraphBuilder
// Abstract base class for defining graph builders
class GRAPHMANAGERCLASS CGraphBuilder
{
public:
	CGraphBuilder();
   CGraphBuilder(const CGraphBuilder& other);
	virtual ~CGraphBuilder();

   virtual void SetName(LPCTSTR strName);
   virtual LPCTSTR GetName() const;

   void SetMenuBitmap(const CBitmap* pBmp);
   const CBitmap* GetMenuBitmap();

   // Creates the UI controls. The controls must be derived from the MFC CControlBar
   // class (typically a CDialogBar). pParent will be the parent window of the control bar
   // and nID will be the control bar ID passed into its Create method
   virtual int CreateControls(CWnd* pParent,UINT nID) = 0;

   // Called by the framework when the graph needs to be drawn. The graph
   // is drawn in the pGraphWnd using the pDC device context.
   virtual void DrawGraph(CWnd* pGraphWnd,CDC* pDC) = 0;

   // Creates a clone of this graph builder. Implementation of this
   // method is essential if your application permits multiple views
   // of the same graph
   virtual CGraphBuilder* Clone() = 0;

   // Called by the framework when the view class OnUpdate is called
   virtual void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint);

   // Called by the framework to determine if printing commands can be enabled
   virtual BOOL CanPrint();

protected:
   CString m_strName;
   const CBitmap* m_pBitmap;
};
