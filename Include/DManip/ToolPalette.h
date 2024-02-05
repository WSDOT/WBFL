///////////////////////////////////////////////////////////////////////
// DManip - Direct Manipulation Framework
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

#pragma once

#include <DManip/DManipExp.h>
#include <vector>
#include <afxcmn.h>

namespace WBFL
{
	namespace DManip
	{
		class iTool;
	};
};

/// @brief This class provides a customization of the MFC CDialogBar class.
/// This class adds the capability to add task based tools to a dialog bar.
/// The dialog bar resource must have an icon control for each tool. The ID
/// of the icon control must batch the tool's ID.
class DMANIPCLASS CToolPalette : public CDialogBar
{
// Construction
public:
	CToolPalette();   // standard constructor


// Dialog Data
	//{{AFX_DATA(CToolPalette)
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CToolPalette)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg) override;
	protected:
	virtual void DoDataExchange(CDataExchange* pDX) override;    // DDX/DDV support
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam) override;
	virtual void PreSubclassWindow() override;
	//}}AFX_VIRTUAL

public:
   /// @brief Adds a tool to the tool palette
   void AddTool(std::shared_ptr<WBFL::DManip::iTool> tool);

	/// @brief Returns a tool object based on its position (index)
	std::shared_ptr<WBFL::DManip::iTool> GetTool(IndexType idx);

	/// @brief Searches for a tool object
	/// @param id ID of the tool object
	/// @return The tool object if found, otherwise nullptr
	std::shared_ptr<WBFL::DManip::iTool> FindTool(IDType id);

   /// @brief Removes a tool object based on its position (index)
   /// @param idx 
   void RemoveTool(IndexType idx);

   /// @brief Removes a tool object based on its ID
   /// @param id 
   void RemoveTool(IDType id);

   /// @brief Called by the framework to create a tool tip from the icon control's window
	/// This method can also be called by subclasses to add tool tips based on other
	/// non-tool controls (such as check boxes or push buttons) that are part of the dialog bar.
   void AddTooltip(CWnd* pWnd);

// Implementation
protected:
   using ToolContainer = std::vector<std::shared_ptr<WBFL::DManip::iTool>>;
   ToolContainer m_Tools;

   CToolTipCtrl m_ctrlToolTip;

	// Generated message map functions
	//{{AFX_MSG(CToolPalette)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
