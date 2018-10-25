#pragma once

#include "resource.h"
#include <WBFLCogo.h>

// CHorizontalAlignmentPage dialog

class CHorizontalAlignmentPage : public CPropertyPage
{
	DECLARE_DYNAMIC(CHorizontalAlignmentPage)

public:
	CHorizontalAlignmentPage();
	virtual ~CHorizontalAlignmentPage();

// Dialog Data
	enum { IDD = IDD_ALIGNMENT_HORIZONTAL };

   Float64 m_Direction;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
   CComPtr<IDirectionDisplayUnitFormatter> m_DirFormatter;

	DECLARE_MESSAGE_MAP()
public:
   virtual BOOL OnInitDialog();
};
