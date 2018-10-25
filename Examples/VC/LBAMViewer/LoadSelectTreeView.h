#if !defined(AFX_LOADSELECTTREEVIEW_H__91FB666D_BC0E_4D3B_A2B6_C5288A5767D7__INCLUDED_)
#define AFX_LOADSELECTTREEVIEW_H__91FB666D_BC0E_4D3B_A2B6_C5288A5767D7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// LoadSelectTreeView.h : header file
//
#include "LBAMViewerDoc.h"
#include <map>

class iDataSetBuilder;

// generic class for creating iDataSetBuilder's
class iDataSetBuilderBuilder 
{
public:
   virtual iDataSetBuilder* Create(PoiIDType PoiID)=0;
};

/////////////////////////////////////////////////////////////////////////////
// CLoadSelectTreeView view
struct IconTracker;
class iDataSetBuilder;

class CLoadSelectTreeView : public CTreeView
{
protected:
	CLoadSelectTreeView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CLoadSelectTreeView)

// Attributes
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLoadSelectTreeView)
	public:
	virtual void OnInitialUpdate();
	protected:
	virtual void OnDraw(CDC* pDC);      // overridden to draw this view
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CLoadSelectTreeView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
protected:
	//{{AFX_MSG(CLoadSelectTreeView)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSelchanged(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
   // image list related stuff
   void BuildImageList();
	CImageList          m_TreeImages;
	CImageList          m_TreeStateImages;

   // keep track of our icons
   struct IconTracker
   {
      int ImageIdx;
      int SelectedImageIdx;

      IconTracker():
      ImageIdx(-1),
      SelectedImageIdx(-1)
      {;}
   };
   IconTracker  m_FolderImages;
   IconTracker  m_LoadGroupImages;
   IconTracker  m_LoadCaseImages;
   IconTracker  m_LoadCombinationImages;
   IconTracker  m_TruckLaneImages;
   IconTracker  m_TruckImages;
   IconTracker  m_EnvelopeTruckImages;
   IconTracker  m_EnvelopeTruckLaneImages;
   IconTracker  m_LaneImages;
   IconTracker  m_PedestrianImages;
   IconTracker  m_InfluenceLineImages;
   IconTracker  m_ContraflexureImages;
   IconTracker  m_LiveLoadModelTLImages;
   IconTracker  m_LiveLoadModelTOImages;
   IconTracker  m_PropertyImages;
   IconTracker  m_DfImages;

   // each node on the tree contains a dataset builder object that is used to create
   // graph curves when selected
   void ClearTreeItems();

   IndexType m_LastIndex;
   typedef std::map<IndexType, iDataSetBuilder*> TreeItemContainer;
   typedef TreeItemContainer::iterator   TreeItemIterator;
   typedef TreeItemContainer::value_type TreeItemValueType;
   TreeItemContainer m_TreeItems;

// Operations
public:
void UpdateLoadGroups(CLBAMViewerDoc* pDoc, CTreeCtrl* tree, HTREEITEM hitm);
void UpdateLoadCases(CLBAMViewerDoc* pDoc, CTreeCtrl* tree, HTREEITEM hitm);
void UpdateLoadCombinations(CLBAMViewerDoc* pDoc, CTreeCtrl* tree, HTREEITEM hitm);
void UpdateLiveLoads(CLBAMViewerDoc* pDoc, CTreeCtrl* tree, HTREEITEM hitm);
void UpdateLiveLoadModel(LiveLoadModelType llmType, ILiveLoadModel* pLlm, CLBAMViewerDoc* pVDoc, CTreeCtrl* pTree, HTREEITEM parent);
void UpdatePoiDependentTree(CLBAMViewerDoc* pVDoc, CTreeCtrl* pTree, HTREEITEM parent, 
                            IconTracker &icons, iDataSetBuilderBuilder& builder);
void UpdateSupportInfluence(CLBAMViewerDoc* pVDoc, CTreeCtrl* tree, HTREEITEM hitm);
void UpdateContraflexure(CLBAMViewerDoc* pVDoc, CTreeCtrl* tree, HTREEITEM hitm);
void UpdateProperties(CLBAMViewerDoc* pVDoc, CTreeCtrl* tree, HTREEITEM hitm);
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LOADSELECTTREEVIEW_H__91FB666D_BC0E_4D3B_A2B6_C5288A5767D7__INCLUDED_)
