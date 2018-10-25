#if !defined(AFX_EDITTRUCKPOSITION_H__7667497B_9A21_4ACC_965C_70AF91EB442C__INCLUDED_)
#define AFX_EDITTRUCKPOSITION_H__7667497B_9A21_4ACC_965C_70AF91EB442C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// EditTruckPosition.h : header file
//
#include "lbamviewer.h"

/////////////////////////////////////////////////////////////////////////////
// CEditTruckPosition dialog

class CEditTruckPosition : public CDialog
{
// Construction
public:
	CEditTruckPosition(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CEditTruckPosition)
	enum { IDD = IDD_TRUCK_POSITION };
	double	m_TruckPosition;
	double	m_VariableAxleSpacing;
	BOOL	m_ApplyImpact;
	AxleIndexType m_PivotAxleIndex;
	//}}AFX_DATA

   void Init( double position, TruckDirectionType direction, 
              bool is_var, double varspcg, double minVarspcg, double maxVarspcg, VARIANT_BOOL applyImpact,AxleIndexType nAxles,AxleIndexType pivotAxleIndex)
   {
      m_nAxles              = nAxles;
      m_PivotAxleIndex      = pivotAxleIndex;
      m_TruckPosition       = position;
      m_Direction           = direction;
      m_IsVar               = is_var;
      m_VariableAxleSpacing = varspcg;
      m_MinVarspcg          = minVarspcg;
      m_MaxVarspcg          = maxVarspcg;
      m_ApplyImpact         = applyImpact==VARIANT_FALSE ? FALSE : TRUE;
   }

   bool               m_IsVar;
   TruckDirectionType m_Direction;
   double             m_MinVarspcg;
   double             m_MaxVarspcg;
   AxleIndexType      m_nAxles;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEditTruckPosition)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CEditTruckPosition)
	afx_msg void OnRadioForward();
	afx_msg void OnRadioReverse();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EDITTRUCKPOSITION_H__7667497B_9A21_4ACC_965C_70AF91EB442C__INCLUDED_)
