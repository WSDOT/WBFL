///////////////////////////////////////////////////////////////////////
// Graphing - Line graph plotting and graph definition management library
// Copyright © 1999-2024  Washington State Department of Transportation
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

#include <Graphing/GraphingExp.h>

namespace WBFL
{
   namespace Graphing
   {
      /// Abstract base class for defining graph builders. This class implements methods for managing the GraphBuilder name and the end-user documentation for the resulting graph.
      class GRAPHINGCLASS GraphBuilder
      {
      public:
         GraphBuilder(LPCTSTR name = _T("Unnamed"));
         GraphBuilder(const GraphBuilder& other) = default;
	      virtual ~GraphBuilder() = default;

         GraphBuilder& operator=(const GraphBuilder& other) = default;

         /// Sets the name of the graph builder
         void SetName(LPCTSTR strName);

         /// Returns the name of the graph builder
         virtual const std::_tstring& GetName() const;

         /// Initializes the associated end-user documentation
         void InitDocumentation(LPCTSTR lpszDocSetName, ///< Name of the documentation set
                                UINT nHID ///< Help topic identifier
         );

         /// Sets the end-user documentation set name
         void SetDocumentationSetName(LPCTSTR lpszDocSetName);

         /// Returns the documentation set name
         const CString& GetDocumentationSetName() const;

         /// Sets the help topic identifier
         void SetHelpID(UINT nID);

         /// Returns the help topic identifier
         UINT GetHelpID() const;

         /// Sets a bitmap to be displayed on menus for the graph
         void SetMenuBitmap(const CBitmap* pBmp);

         /// Returns a bitmap for display on the menus
         const CBitmap* GetMenuBitmap();

         /// Creates the UI controls. The controls must be derived from the MFC CControlBar
         /// class (typically a CDialogBar). pParent will be the parent window of the control bar
         /// and nID will be the control bar ID passed into its Create method. Returns 0 when successful.
         virtual int InitializeGraphController(CWnd* pParent,UINT nID) = 0;

         /// Called by the framework when the graph needs to be drawn. The graph
         /// is drawn in the pGraphWnd using the pDC device context.
         virtual void DrawGraph(CWnd* pGraphWnd,CDC* pDC) = 0;

         /// Creates a clone of this graph builder. Implementation of this
         /// method is essential if your application permits multiple views
         /// of the same graph
         virtual std::unique_ptr<GraphBuilder> Clone() const = 0;

         /// Called by the framework when the view class OnUpdate is called
         virtual void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint);

         /// Called by the framework to determine if printing commands can be enabled
         virtual BOOL CanPrint();

         /// Called by the framework when an instance of the graph is left-button double-clicked on.
         /// Returns true if the double click was handled which stops further processing of the event
         virtual bool HandleDoubleClick(UINT nFlags,CPoint point);

      protected:
         std::_tstring m_strName;
         const CBitmap* m_pBitmap = nullptr;

         CString m_strDocSetName;
         UINT m_nHelpID = 0;
      };

   }; // Graphing
}; // WBFL
