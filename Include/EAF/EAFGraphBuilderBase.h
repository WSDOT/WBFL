///////////////////////////////////////////////////////////////////////
// EAF - Extensible Application Framework
// Copyright © 1999-2017  Washington State Department of Transportation
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


#pragma once

// EAFGraphBuilderBase.h : header file
//

#include <EAF\EAFExp.h>
#include <EAF\EAFGraphChildFrame.h>
#include <EAF\EAFGraphControlWindow.h>
#include <GraphManager\GraphBuilder.h>

/////////////////////////////////////////////////////////////////////////////
// CEAFGraphBuilderBase
//
// This is the base class for all graph builders that want to create graphs
// in CEAFGraphView. This class extends CGraphBuilder by adding command
// routing capabilities. With command routing, the graph builder can
// process commands initiated from the CEAFGraphControlWindow. This is often
// more convienent as it is the responsibility of the graph builder to
// draw the actual graph.

class EAFCLASS CEAFGraphBuilderBase : public CCmdTarget, // we want to handle commands!
                                      public CGraphBuilder
{
public:
   CEAFGraphBuilderBase();
   CEAFGraphBuilderBase(const CEAFGraphBuilderBase& other);
   virtual ~CEAFGraphBuilderBase();

   // Implements CGraphBuilder::InitializeGraphController. Calls
   // CreateGraphController
   virtual int InitializeGraphController(CWnd* pParent,UINT nID);

   // Called by InitializeGraphController when it is time to
   // create the actual graph controller UI element (this must be
   // a CEAFGraphControlWindow derived object)
   virtual BOOL CreateGraphController(CWnd* pParent,UINT nID) = 0;

   // Returns the frame window
   virtual CEAFGraphChildFrame* GetFrame();

   // Returns the view window
   virtual CEAFGraphView* GetView();

   // returns a pointer to the graph control window. The windows does not
   // have to be created to return a valid pointer from this method.
   // A valid CEAFGraphControlWindow (C++) object must exist prior to CreateGraphController
   // being called.
   virtual CEAFGraphControlWindow* GetGraphControlWindow() = 0;

   // called by the framework when the view's OnUpdate method is called
   virtual void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint);

   virtual void DrawGraph(CWnd* pGraphWnd,CDC* pDC);

   void InvalidateGraph() { m_bValidGraph = false; }
   bool IsValidGraph() { return m_bValidGraph; }

   virtual void Update();

   virtual BOOL CanPrint();

protected:
   DECLARE_MESSAGE_MAP()

   // Called by the framework when the graph needs to be updated
   // Return true if the graph was succesfully updated
   virtual bool UpdateNow() = 0;

   virtual void DrawGraphNow(CWnd* pGraphWnd,CDC* pDC) = 0;

   bool m_bValidGraph;
   bool m_bUpdateError;
   std::_tstring m_ErrorMsg;

   CEAFGraphChildFrame* m_pFrame; // pointer to the frame window associated with the graph view
};
