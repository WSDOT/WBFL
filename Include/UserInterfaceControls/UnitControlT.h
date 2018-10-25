#ifndef INCLUDED_REINFORCEDCONCRETE_UNITCONTROLT_H_
#define INCLUDED_REINFORCEDCONCRETE_UNITCONTROLT_H_

// SYSTEM INCLUDES
//
#include <vector>

// PROJECT INCLUDES
//
#include <units\PhysicalT.h>
#include <units\SysUnits.h>
#include <UserInterfaceControls\IDialogUnitPersistence.h>

// LOCAL INCLUDES
//

// FORWARD DECLARATIONS
//

// MISCELLANEOUS
//


/*****************************************************************************
CLASS 
   uicUnitControlT

   Template class for custom unit control


DESCRIPTION
   This class provides support for an edit box - list box unit control.


COPYRIGHT
   Copyright (c) 1997
   Washington State Department Of Transportation
   All Rights Reserved

LOG
   rdp : 03.18.1998 : Created file
*****************************************************************************/

template <class T> class uicUnitControlT
{
public:
   // GROUP: LIFECYCLE

   //------------------------------------------------------------------------
   // Constructor
   // Pass in vector of units to be used in control and Id's of the parent
   // Dialog, Edit box and Combo Box. 
   // The default unit becomes the first unit in the units list. Call 
   // SetDialogUnitPersistence to set up persistence for this control.
   uicUnitControlT(const std::vector<const T*>& units, 
                 CWnd* pParentDlg, int dlgId, int editCtrlId, int comboCtrlId)
   {
      PRECONDITION(editCtrlId);
      PRECONDITION(comboCtrlId);
      PRECONDITION(dlgId);
      PRECONDITION(!units.empty());
      m_Units       = units;
      m_pDlg        = pParentDlg;
      m_DlgId       = dlgId;
      m_EditCtrlId  = editCtrlId;
      m_ComboCtrlId = comboCtrlId;
      m_pMapper     = 0;

      m_DoBoundsChecking = false;
      m_UpperBound       =0;
      m_LowerBound       =0;

      // default to first unit if no previous
      m_CurrentUnitTag = m_Units[0]->UnitTag();
   }

   //------------------------------------------------------------------------
   // Destructor
   virtual ~uicUnitControlT()
   {
      // save units off to Persistence
      m_pMapper->SetLastUnit(m_DlgId, m_ComboCtrlId,m_CurrentUnitTag);
   }

   // GROUP: OPERATORS
   // GROUP: OPERATIONS

   //------------------------------------------------------------------------
   // Set parent dialog. This function should be used to initialize the pointer
   // to the parent dialog in cases where it is not available in the constructor.
   // Ideally, this should only be called once just after the constructor.
   void SetParentDialog(CWnd* pParentDialog)
   {
      PRECONDITION(pParentDialog);
      m_pDlg = pParentDialog;
   }
   //------------------------------------------------------------------------
   // Set up Persistence mapper. This should be done once only soon after
   // construction. This class does not take responsibility for lifetime
   // ownership of the pointer.
   void SetDialogUnitPersistence(uicIDialogUnitPersistence* pMapper)
   {
      // get the previous unit from Persistence store
      PRECONDITION(pMapper);
      m_pMapper = pMapper;

      m_CurrentUnitTag = m_pMapper->GetLastUnit(m_DlgId, m_ComboCtrlId);
      if (m_CurrentUnitTag.empty())
         m_CurrentUnitTag = m_Units[0]->UnitTag();
   }

   //------------------------------------------------------------------------
   // Enables bounds checking on the two values specified in system units.
   void EnableBoundsChecking(double lowerBound, double upperBound)
   {
      m_DoBoundsChecking = true;
      m_UpperBound = max(lowerBound,upperBound);
      m_LowerBound = min(lowerBound,upperBound);
   }

   //------------------------------------------------------------------------
   // Disables bounds checking for the control
   void DisableBoundsChecking()
   {
      m_DoBoundsChecking = false;
   }

   //------------------------------------------------------------------------
   // Check to see if bounds checking is enabled
   bool IsBoundsCheckingEnabled()
   {
      return m_DoBoundsChecking;
   }

   //------------------------------------------------------------------------
   // Call from parent dialogs OnInitDialog method. 
   // Sets up the combo box with the correct text strings and
   // possibily pointers to the physical unit objects
   void OnInitDialog()
   {
      //
      PRECONDITION(m_Units.size());
      PRECONDITION(m_pDlg);
      CComboBox* box = (CComboBox*)m_pDlg->GetDlgItem(m_ComboCtrlId);
      CHECK(box);

      // loop through units and load combo
      std::vector<const T*>::iterator start;
      for(start=m_Units.begin(); start<m_Units.end(); start++)
      {
         std::string tag = (*start)->UnitTag();
         box->AddString(tag.c_str());
      }
      // set box to current unit
      int sel = box->FindString(0,m_CurrentUnitTag.c_str());
      CHECK(sel!=CB_ERR);

      if (sel != CB_ERR)
         box->SetCurSel(sel);
      else
      {
         box->SetCurSel(0);
         m_CurrentUnitTag = m_Units[0]->UnitTag();
      }
   }

   //------------------------------------------------------------------------
   // Instead of writing custom DDX methods, the data exchange stuff
   // can be completely encapsualted within this class.  pValue is a 
   // pointer to the value of the control in system units.
   void DoDataExchange(CDataExchange* pDX,double* pValue)
   {
      PRECONDITION(m_pDlg);
      // get the current unit from the combo box
      CComboBox* box = (CComboBox*)m_pDlg->GetDlgItem(m_ComboCtrlId);
      CHECK(box);

      const T* pcuru = FindUnit(m_CurrentUnitTag);
      CHECK(pcuru);

      if (pcuru)
      {
         CEdit* edit = (CEdit*)m_pDlg->GetDlgItem(m_EditCtrlId);
         CHECK(edit);

         if (pDX->m_bSaveAndValidate)
         {
            // use DDX to convert the value
            double d;
            DDX_Text(pDX, m_EditCtrlId, d );

            if (m_DoBoundsChecking)
            {
               double upper = ::ConvertFromSysUnits(m_UpperBound,*pcuru);
               double lower = ::ConvertFromSysUnits(m_LowerBound,*pcuru);
               DDV_MinMaxDouble(pDX, d, lower, upper );
            }

            *pValue = ::ConvertToSysUnits(d,*pcuru);
         }
         else
         {
            // truncate to float here because double shows a ridiculous number
            // of significant digits.
            float f = ::ConvertFromSysUnits(*pValue,*pcuru);
            DDX_Text(pDX, m_EditCtrlId, f );
         }
      }
   }

   //------------------------------------------------------------------------
   // Call this routine from your handler for the CBN_SELCHANGE for your
   // unit pair ComboBox.
   void OnSelChangeUnits()
   {
      PRECONDITION(m_pDlg);
      CComboBox* box = (CComboBox*)m_pDlg->GetDlgItem(m_ComboCtrlId);
      CHECK(box);
      // get new selection
      CString cnew;
      int newsel = box->GetCurSel();
      box->GetLBText(newsel, cnew);
      std::string snew(cnew.GetBuffer(0));

      // Check to see if CTRL key is down. If it is, do conversion.
      if (::GetKeyState(VK_CONTROL)<0)
      {
         if (m_CurrentUnitTag!=snew)
         {
            // convert string in edit box to system using old units
            double d;
     	      CDataExchange dx(m_pDlg, true);
            DoDataExchange(&dx, &d);

            // change unit to new and transfer back to edit box
            m_CurrentUnitTag = snew;
     	      CDataExchange dx2(m_pDlg, false);
            DoDataExchange(&dx2, &d);
         }
      }
      m_CurrentUnitTag = snew;
   }


   //------------------------------------------------------------------------
   // Sets the unit of measure for the edit/combo control.
   // If bConvert is true, the current value in the edit
   // control is converted to the new unit of measure.
   void SetUnitOfMeasureIndex(int comboIdx, bool bConvert)
   {
      PRECONDITION(m_pDlg);
      CComboBox* box = (CComboBox*)m_pDlg->GetDlgItem(m_ComboCtrlId);
      CHECK(box);
      int count = box->GetCount();
      PRECONDITION(0<=comboIdx&&comboIdx<count);

      CString cs;
      box->GetLBText(comboIdx, cs);
      std::string ss(cs.GetBuffer(0));

      SetUnitOfMeasureString(ss, bConvert);
   }

   //------------------------------------------------------------------------
   // Sets the unit of measure for the edit/combo control.
   // If bConvert is true, the current value in the edit
   // control is converted to the new unit of measure.
   void SetUnitOfMeasureString(std::string& name, bool bConvert)
   {
      PRECONDITION(m_pDlg);
      CComboBox* box = (CComboBox*)m_pDlg->GetDlgItem(m_ComboCtrlId);
      CHECK(box);
      int idx = box->FindString(0,name.c_str());
      CHECK(idx!=CB_ERR)

      if (idx!=CB_ERR)
      {
         // just use the ddx stuff to do the conversion
         double d;
         if (bConvert)
         {
     	      CDataExchange dx(m_pDlg, true);
            DoDataExchange(&dx, &d);
         }

         m_CurrentUnitTag = name;

         if (bConvert)
         {
     	      CDataExchange dx(m_pDlg, false);
            DoDataExchange(&dx, &d);
         }

         // set box to selected units
         box->SetCurSel(idx);
      }
   }

   //------------------------------------------------------------------------
   // Returns the combobox index for the current unit of measure
   int GetUnitOfMeasureIndex()
   {
      PRECONDITION(m_pDlg);
      CComboBox* box = (CComboBox*)m_pDlg->GetDlgItem(m_ComboCtrlId);
      CHECK(box);

      return box->GetCurSel();
   }
   
   //------------------------------------------------------------------------
   // Returns the unit tag string for the current unit of measure
   std::string GetUnitOfMeasureString()
   {
      PRECONDITION(m_pDlg);
      CComboBox* box = (CComboBox*)m_pDlg->GetDlgItem(m_ComboCtrlId);
      CHECK(box);
      int sel = box->GetCurSel();
      CString tag;
      box->GetLBText(sel, tag);
      return tag.GetBuffer(0);
   }

   // GROUP: ACCESS
   // GROUP: INQUIRY
   // GROUP: DEBUG

protected:
   // GROUP: DATA MEMBERS
   // GROUP: LIFECYCLE
   // GROUP: OPERATORS
   // GROUP: OPERATIONS
   // GROUP: ACCESS
   // GROUP: INQUIRY

private:
   // GROUP: DATA MEMBERS
   uicIDialogUnitPersistence*          m_pMapper;
   std::vector<const T*> m_Units;
   int   m_DlgId;
   int   m_EditCtrlId;
   int   m_ComboCtrlId;
   std::string   m_CurrentUnitTag;
   CWnd* m_pDlg;

   bool   m_DoBoundsChecking;
   double m_UpperBound;
   double m_LowerBound;

   // GROUP: LIFECYCLE

   // Prevent accidental copying and assignment
   uicUnitControlT();
   uicUnitControlT(const uicUnitControlT&);
   uicUnitControlT& operator=(const uicUnitControlT&);

   // GROUP: OPERATORS
   // GROUP: OPERATIONS
   // find a unit based on tag
   const T*  FindUnit(const std::string& stag)
   {
      std::vector<const T*>::iterator start;
      for(start=m_Units.begin(); start<m_Units.end(); start++)
      {
         if (stag == (*start)->UnitTag())
            return *start;
      }
      return 0;
   }

   // GROUP: ACCESS
   // GROUP: INQUIRY
};

// INLINE METHODS
//

// EXTERNAL REFERENCES
//
// some favorites already created for you.

typedef uicUnitControlT<unitLength>  uicLengthUnitEdit;
typedef uicUnitControlT<unitForce>   uicForceUnitEdit;
typedef uicUnitControlT<unitStress>  uicStressUnitEdit;
typedef uicUnitControlT<unitDensity> uicDensityUnitEdit;


#endif // INCLUDED_REINFORCEDCONCRETE_UNITCONTROLT_H_
