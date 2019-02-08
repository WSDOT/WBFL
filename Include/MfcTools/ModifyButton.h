///////////////////////////////////////////////////////////////////////
// MfcTools - Extension library for MFC
// Copyright © 1999-2019  Washington State Department of Transportation
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

#ifndef INCLUDED_MODIFYBUTTON_H_
#define INCLUDED_MODIFYBUTTON_H_
#pragma once

#include <MfcTools\MfcToolsExp.h>
#include "afxcmn.h"


class CGetFolderControl;


// a pure virtual interface class to make this work with both getfolder and getfile
class IGetEdit
{
public:
   virtual ~IGetEdit() {}
   virtual void Edit() = 0;
};

/////////////////////////// Classes /////////////////////////////////
class MFCTOOLSCLASS CModifyButton : public CButton
{
public:
  CModifyButton();
  void SetBuddy(IGetEdit* pBuddy);

protected:
  //{{AFX_VIRTUAL(CModifyButton)
  public:
  virtual BOOL PreTranslateMessage(MSG* pMsg) override;
  //}}AFX_VIRTUAL

  //{{AFX_MSG(CModifyButton)
  afx_msg BOOL OnClicked();
  //}}AFX_MSG

  DECLARE_MESSAGE_MAP()

  IGetEdit* m_pBuddy;
  BOOL m_bFirstCall;
  CToolTipCtrl m_ToolTip;
};

#endif