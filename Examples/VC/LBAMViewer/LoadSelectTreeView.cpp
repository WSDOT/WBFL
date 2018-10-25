// LoadSelectTreeView.cpp : implementation file
//

#include "stdafx.h"
#include "lbamviewer.h"
#include "LoadSelectTreeView.h"

#include "LoadGroupDataSetBuilder.h"
#include "LoadCaseDataSetBuilder.h"
#include "LoadCombinationDataSetBuilder.h"
#include "InfluenceLineDataSetBuilder.h"
#include "BasicLiveLoadDataSetBuilder.h"
#include "EnvelopedVehicularDataSetBuilder.h"
#include "ContraflexureDataSetBuilder.h"
#include "LiveLoadModelDataSetBuilder.h"
#include "ReactionInfluenceDataSetBuilder.h"
#include "PropertyDataSetBuilder.h"
#include "StressPointDataSetBuilder.h"
#include "DistributionFactorDataSetBuilder.h"

#include "ChildFrm.h"

#include <MathEx.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define COLOR_MASK RGB(255,255,255)

void InitializeItemData(CTreeCtrl* pTree, HTREEITEM item, IndexType& lastIndex)
{
         pTree->SetItemData(item, ++lastIndex);
         pTree->SetItemState(item, INDEXTOSTATEIMAGEMASK(1), TVIS_STATEIMAGEMASK);
}

CString GetPoiDescription(PoiIDType poi_id, MemberType poi_mt, MemberIDType poi_mbrid, double poi_location)
{
   CString mbrname;
   switch (poi_mt)
   {
   case mtSpan:
      mbrname = _T("Span");
      break;
   case mtSupport:
      mbrname = _T("Support");
      break;
   case mtTemporarySupport:
      mbrname = _T("TemporarySupport");
      break;
   case mtSuperstructureMember:
      mbrname = _T("SuperstructureMember");
      break;
   default:
      ATLASSERT(0);
   }

   CString descr;
   descr.Format(_T("POI %d - %s %d at %f"), poi_id, mbrname, poi_mbrid, poi_location);

   return descr;
}

// class for building influence data set builder
class InfluenceLineDataSetBuilderBuilder: public iDataSetBuilderBuilder
{
public:
   InfluenceLineDataSetBuilderBuilder(IInfluenceLineResponse* response):
   m_Response(response)
   {;}

   iDataSetBuilder* Create(PoiIDType PoiID)
   {
      return new InfluenceLineDataSetBuilder(PoiID, m_Response);
   }

private:
   InfluenceLineDataSetBuilderBuilder();

   CComPtr<IInfluenceLineResponse> m_Response;
};

/////////////////////////////////////////////////////////////////////////////
// CLoadSelectTreeView

IMPLEMENT_DYNCREATE(CLoadSelectTreeView, CTreeView)

CLoadSelectTreeView::CLoadSelectTreeView():
m_LastIndex(100)
{
}

CLoadSelectTreeView::~CLoadSelectTreeView()
{
   ClearTreeItems();
}

void CLoadSelectTreeView::ClearTreeItems()
{
   for (TreeItemIterator it=m_TreeItems.begin(); it!=m_TreeItems.end(); it++)
   {
      if (it->second!=NULL)
      {
         iDataSetBuilder* pds = (iDataSetBuilder*)it->second;
         delete pds;
      }
      else
         ATLASSERT(0); // should have all valid pointers
   }
}


BEGIN_MESSAGE_MAP(CLoadSelectTreeView, CTreeView)
	//{{AFX_MSG_MAP(CLoadSelectTreeView)
	ON_WM_CREATE()
	ON_NOTIFY_REFLECT(TVN_SELCHANGED, OnSelchanged)
	ON_WM_LBUTTONDOWN()
	ON_WM_RBUTTONDOWN()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLoadSelectTreeView drawing

void CLoadSelectTreeView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: add draw code here
}

/////////////////////////////////////////////////////////////////////////////
// CLoadSelectTreeView diagnostics

#ifdef _DEBUG
void CLoadSelectTreeView::AssertValid() const
{
	CTreeView::AssertValid();
}

void CLoadSelectTreeView::Dump(CDumpContext& dc) const
{
	CTreeView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CLoadSelectTreeView message handlers
void CLoadSelectTreeView::OnInitialUpdate() 
{
   HRESULT hr;
	CTreeView::OnInitialUpdate();
	
   // get LBAM
   CDocument *pDoc = GetDocument();
   CLBAMViewerDoc* pVdoc = dynamic_cast<CLBAMViewerDoc*>(pDoc);
   ATLASSERT(pVdoc);

   // create and load up image list for tree control 
   // load two icons for each library. a normal and a selected
   BuildImageList();
	CTreeCtrl& tree = GetTreeCtrl();
   tree.DeleteAllItems();

   tree.SetImageList(&m_TreeImages,LVSIL_NORMAL);

   // Add top-level folders
   // Load Groups
   HTREEITEM hitm = tree.InsertItem(_T("Load Groups"), m_FolderImages.ImageIdx ,m_FolderImages.SelectedImageIdx );
   tree.SetItemData(hitm, -1);

   UpdateLoadGroups( pVdoc, &tree, hitm);

   // Live Loads
   hitm = tree.InsertItem(_T("Live Loads"), m_FolderImages.ImageIdx ,m_FolderImages.SelectedImageIdx );
   tree.SetItemData(hitm, -1);

   UpdateLiveLoads( pVdoc, &tree, hitm);

   // Load Cases
   hitm = tree.InsertItem(_T("Load Cases"), m_FolderImages.ImageIdx ,m_FolderImages.SelectedImageIdx );
   tree.SetItemData(hitm, -1);

   UpdateLoadCases( pVdoc, &tree, hitm);

   // Load Combinations
   hitm = tree.InsertItem(_T("Load Combinations"), m_FolderImages.ImageIdx ,m_FolderImages.SelectedImageIdx );
   tree.SetItemData(hitm, -1);

   UpdateLoadCombinations( pVdoc, &tree, hitm);

   // Influence Lines
   HTREEITEM hinfl = tree.InsertItem(_T("Influence Lines"), m_FolderImages.ImageIdx ,m_FolderImages.SelectedImageIdx );
   tree.SetItemData(hinfl, -1);

   // at pois
   hitm = tree.InsertItem(_T("POIs"), m_FolderImages.ImageIdx ,m_FolderImages.SelectedImageIdx, hinfl);
   tree.SetItemData(hitm, -1);

   CComPtr<IInfluenceLineResponse> influence_response;
   hr = pVdoc->m_pLBAMAnalysisEngine->get_InfluenceLineResponse(&influence_response);
   ATLASSERT(SUCCEEDED(hr));
   InfluenceLineDataSetBuilderBuilder inf_bb(influence_response);
   UpdatePoiDependentTree( pVdoc, &tree, hitm, m_InfluenceLineImages, inf_bb);

   // at supports
   hitm = tree.InsertItem(_T("Supports"), m_FolderImages.ImageIdx ,m_FolderImages.SelectedImageIdx, hinfl);
   tree.SetItemData(hitm, -1);

   UpdateSupportInfluence( pVdoc, &tree, hitm);

   // Contraflexure
   hitm = tree.InsertItem(_T("Contraflexure Response"), m_FolderImages.ImageIdx ,m_FolderImages.SelectedImageIdx );
   tree.SetItemData(hitm, -1);

   UpdateContraflexure( pVdoc, &tree, hitm);

   // Model Properties
   hitm = tree.InsertItem(_T("Structural Properties"), m_FolderImages.ImageIdx ,m_FolderImages.SelectedImageIdx );
   tree.SetItemData(hitm, -1);

   UpdateProperties( pVdoc, &tree, hitm);
}

int CLoadSelectTreeView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
   lpCreateStruct->style |= TVS_HASLINES | TVS_LINESATROOT | TVS_INFOTIP | TVS_TRACKSELECT |
                            TVS_HASBUTTONS | TVS_SHOWSELALWAYS | TVS_DISABLEDRAGDROP;

	if (CTreeView::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	return 0;
}

bool LiveLoadModelHasData(ILiveLoadModel* pLlm)
{
   HRESULT hr;
   CComPtr<IVehicularLoads> pvl;
   hr = pLlm->get_VehicularLoads(&pvl);
   ATLASSERT(SUCCEEDED(hr));
   VehicleIndexType cnt;
   hr = pvl->get_Count(&cnt);

   return cnt>0;
   ATLASSERT(SUCCEEDED(hr));
}

void CLoadSelectTreeView::UpdateLiveLoads(CLBAMViewerDoc* pVDoc, CTreeCtrl* pTree, HTREEITEM parent)
{
   HRESULT hr;

   CComPtr<ILiveLoad> liveload;
   hr = pVDoc->m_pModel->get_LiveLoad(&liveload); // list of LoadGroups in document

   // add a folder for each type of live load
   HTREEITEM hitm;
   CComPtr<ILiveLoadModel> deflection_llm;
   hr = liveload->get_Deflection(&deflection_llm);
   if ( LiveLoadModelHasData(deflection_llm) )
   {
      hitm = pTree->InsertItem(_T("Deflection"), m_FolderImages.ImageIdx ,m_FolderImages.SelectedImageIdx, parent );
      pTree->SetItemData(hitm, -1);

      UpdateLiveLoadModel(lltDeflection, deflection_llm, pVDoc, pTree, hitm);
   }

   CComPtr<ILiveLoadModel> design_llm;
   hr = liveload->get_Design(&design_llm);
   if ( LiveLoadModelHasData(design_llm) )
   {
      hitm = pTree->InsertItem(_T("Design"), m_FolderImages.ImageIdx ,m_FolderImages.SelectedImageIdx, parent );
      pTree->SetItemData(hitm, -1);

      UpdateLiveLoadModel(lltDesign, design_llm, pVDoc, pTree, hitm);
   }

   CComPtr<ILiveLoadModel> fatigue_llm;
   hr = liveload->get_Fatigue(&fatigue_llm);
   if ( LiveLoadModelHasData(fatigue_llm) )
   {
      hitm = pTree->InsertItem(_T("Fatigue"), m_FolderImages.ImageIdx ,m_FolderImages.SelectedImageIdx, parent );
      pTree->SetItemData(hitm, -1);

      UpdateLiveLoadModel(lltFatigue, fatigue_llm, pVDoc, pTree, hitm);
   }

   CComPtr<ILiveLoadModel> permit_llm;
   hr = liveload->get_Permit(&permit_llm);
   if ( LiveLoadModelHasData(permit_llm) )
   {
      hitm = pTree->InsertItem(_T("Permit"), m_FolderImages.ImageIdx ,m_FolderImages.SelectedImageIdx, parent );
      pTree->SetItemData(hitm, -1);

      UpdateLiveLoadModel(lltPermit, permit_llm, pVDoc, pTree, hitm);
   }

   CComPtr<ILiveLoadModel> pedestrian_llm;
   hr = liveload->get_Pedestrian(&pedestrian_llm);
   if ( LiveLoadModelHasData(pedestrian_llm) )
   {
      hitm = pTree->InsertItem(_T("Pedestrian"), m_FolderImages.ImageIdx ,m_FolderImages.SelectedImageIdx, parent );
      pTree->SetItemData(hitm, -1);

      UpdateLiveLoadModel(lltPedestrian, pedestrian_llm, pVDoc, pTree, hitm);
   }

   CComPtr<ILiveLoadModel> special_llm;
   hr = liveload->get_Special(&special_llm);
   if ( LiveLoadModelHasData(special_llm) )
   {
      hitm = pTree->InsertItem(_T("Special"), m_FolderImages.ImageIdx ,m_FolderImages.SelectedImageIdx, parent );
      pTree->SetItemData(hitm, -1);

      UpdateLiveLoadModel(lltSpecial, special_llm, pVDoc, pTree, hitm);
   }
}

void CLoadSelectTreeView::UpdateLiveLoadModel(LiveLoadModelType llmType, ILiveLoadModel* pLlm, CLBAMViewerDoc* pVDoc,
                                              CTreeCtrl* pTree, HTREEITEM parent)
{
   HRESULT hr;
   // live load model responses
   CComPtr<ILiveLoadModelResponse> llm_response;
   hr = pVDoc->m_pLBAMAnalysisEngine->get_LiveLoadModelResponse(&llm_response);
   ATLASSERT(SUCCEEDED(hr));

   // truck + lane
   HTREEITEM llmtl_itm = pTree->InsertItem(CString(_T("LiveLoadModel Truck+Lane Envelope")), m_LiveLoadModelTLImages.ImageIdx , m_LiveLoadModelTLImages.SelectedImageIdx , parent);
   LiveLoadModelDataSetBuilder* llmtl_bldr = new LiveLoadModelDataSetBuilder(llmType, llrTruckLaneCombo, llm_response);
   InitializeItemData(pTree, llmtl_itm, m_LastIndex);
   m_TreeItems.insert(TreeItemValueType(m_LastIndex, llmtl_bldr));

   // truck only
   HTREEITEM llmto_itm = pTree->InsertItem(CString(_T("LiveLoadModel Truck Only Envelope")), m_LiveLoadModelTOImages.ImageIdx , m_LiveLoadModelTOImages.SelectedImageIdx , parent);
   LiveLoadModelDataSetBuilder* llmto_bldr = new LiveLoadModelDataSetBuilder(llmType, llrTruckOnly, llm_response);
   InitializeItemData(pTree, llmto_itm, m_LastIndex);
   m_TreeItems.insert(TreeItemValueType(m_LastIndex, llmto_bldr));

   // Enveloped and basic response engines
   CComPtr<IEnvelopedVehicularResponse> env_response;
   hr = pVDoc->m_pLBAMAnalysisEngine->get_EnvelopedVehicularResponse(&env_response);
   ATLASSERT(SUCCEEDED(hr));

   CComPtr<IBasicVehicularResponse> bv_response;
   hr = pVDoc->m_pLBAMAnalysisEngine->get_BasicVehicularResponse(&bv_response);
   ATLASSERT(SUCCEEDED(hr));

   // loop over individual vehicular loads and get their data
   CComPtr<IVehicularLoads> vehicular_loads;
   hr = pLlm->get_VehicularLoads(&vehicular_loads);
   ATLASSERT(SUCCEEDED(hr));
   VehicleIndexType num_vehicular_loads;
   hr = vehicular_loads->get_Count(&num_vehicular_loads);
   ATLASSERT(SUCCEEDED(hr));
   ATLASSERT(num_vehicular_loads>0); // should have been caught earlier

   for (VehicleIndexType ivl=0; ivl<num_vehicular_loads; ivl++)
   {
      CComBSTR bvln;
      CComPtr<IVehicularLoad> vehicular_load;
      hr = vehicular_loads->get_Item(ivl,&vehicular_load);
      ATLASSERT(SUCCEEDED(hr));
      hr = vehicular_load->get_Name(&bvln);
      ATLASSERT(SUCCEEDED(hr));
      CString vln( bvln );
      HTREEITEM vl_itm = pTree->InsertItem(vln, m_FolderImages.ImageIdx , m_FolderImages.SelectedImageIdx , parent);
      pTree->SetItemData(vl_itm, -1);

      // Add selections based on vl configuration
      VehicularLoadConfigurationType vl_config;
      hr = vehicular_load->get_Configuration(&vl_config);
      ATLASSERT(SUCCEEDED(hr));

      HTREEITEM crenvtl_itm = pTree->InsertItem(CString(_T("Enveloped Truck+Lane Response")), m_EnvelopeTruckLaneImages.ImageIdx , m_EnvelopeTruckLaneImages.SelectedImageIdx , vl_itm);
      EnvelopedVehicularDataSetBuilder* envtrl_bldr = new EnvelopedVehicularDataSetBuilder(llmType, ivl, llrTruckLaneCombo, env_response);
      InitializeItemData(pTree, crenvtl_itm, m_LastIndex);
      m_TreeItems.insert(TreeItemValueType(m_LastIndex, envtrl_bldr));

      // Truck Only
      if (vl_config==vlcDefault || vl_config==vlcTruckPlusLane || vl_config==vlcTruckLaneEnvelope  || vl_config==vlcTruckOnly)
      {
         // get LBAM in order to get pois
         CDocument *pDoc = GetDocument();
         CLBAMViewerDoc* pVdoc = dynamic_cast<CLBAMViewerDoc*>(pDoc);
         ATLASSERT(pVdoc);

         HTREEITEM crenv_itm = pTree->InsertItem(CString(_T("Enveloped Truck Response")), m_EnvelopeTruckImages.ImageIdx , m_EnvelopeTruckImages.SelectedImageIdx , vl_itm);
         EnvelopedVehicularDataSetBuilder* envtr_bldr = new EnvelopedVehicularDataSetBuilder(llmType, ivl, llrTruckOnly, env_response);
         InitializeItemData(pTree, crenv_itm, m_LastIndex);
         m_TreeItems.insert(TreeItemValueType(m_LastIndex, envtr_bldr));

         HTREEITEM cre_itm = pTree->InsertItem(CString(_T("Truck Response")), m_TruckImages.ImageIdx , m_TruckImages.SelectedImageIdx , vl_itm);
         InitializeItemData(pTree, cre_itm, m_LastIndex);
         BasicLiveLoadDataSetBuilder* tr_bldr = new BasicLiveLoadDataSetBuilder(llmType, ivl, llrTruckOnly,
                                                    pVDoc->m_pModel, bv_response);
         m_TreeItems.insert(TreeItemValueType(m_LastIndex, tr_bldr));
      }

      // Lane Only
      if (vl_config==vlcDefault || vl_config==vlcTruckPlusLane || vl_config==vlcTruckLaneEnvelope  || vl_config==vlcLaneOnly)
      {
         HTREEITEM crln_itm = pTree->InsertItem(CString(_T("Lane Response")), m_LaneImages.ImageIdx , m_LaneImages.SelectedImageIdx , vl_itm);
         InitializeItemData(pTree, crln_itm, m_LastIndex);
         BasicLiveLoadDataSetBuilder* ln_bldr = new BasicLiveLoadDataSetBuilder(llmType, ivl, llrLaneOnly,
                                                    pVDoc->m_pModel, bv_response);
         m_TreeItems.insert(TreeItemValueType(m_LastIndex, ln_bldr));
      }

      // Truck/Lane response
      HTREEITEM cr_itm = pTree->InsertItem(CString(_T("Truck+Lane Response")), m_TruckLaneImages.ImageIdx , m_TruckLaneImages.SelectedImageIdx , vl_itm);
      InitializeItemData(pTree, cr_itm, m_LastIndex);

      BasicLiveLoadDataSetBuilder* tl_bldr = new BasicLiveLoadDataSetBuilder(llmType, ivl, llrTruckLaneCombo,
                                                 pVDoc->m_pModel, bv_response);
      m_TreeItems.insert(TreeItemValueType(m_LastIndex, tl_bldr));

      // sidewalk
      double sw_load;
      hr = vehicular_load->get_SidewalkLoad(&sw_load);
      ATLASSERT(SUCCEEDED(hr));
      if (!IsZero(sw_load))
      {
         HTREEITEM crs_itm = pTree->InsertItem(CString(_T("Sidewalk Response")), m_PedestrianImages.ImageIdx , m_PedestrianImages.SelectedImageIdx , vl_itm);
         InitializeItemData(pTree, crs_itm, m_LastIndex);
         BasicLiveLoadDataSetBuilder* s_bldr = new BasicLiveLoadDataSetBuilder(llmType, ivl, llrSidewalkOnly,
                                                    pVDoc->m_pModel, bv_response);
         m_TreeItems.insert(TreeItemValueType(m_LastIndex, s_bldr));
      }
   }
}

void CLoadSelectTreeView::UpdateContraflexure(CLBAMViewerDoc* pVDoc,CTreeCtrl* pTree, HTREEITEM parent)
{
   HRESULT hr;
   CComPtr<ISpans> Spans;
   hr = pVDoc->m_pModel->get_Spans(&Spans); // list of Spans in document

   SpanIndexType nSpans;
   hr = Spans->get_Count(&nSpans);
   if (nSpans != 0)
   {
      CString lg( _T("Contraflexure Response") );
      HTREEITEM hitm = pTree->InsertItem(lg, m_ContraflexureImages.ImageIdx , m_ContraflexureImages.SelectedImageIdx , parent);

      m_LastIndex++;
      InitializeItemData(pTree, hitm, m_LastIndex);

      // create our builder
      CComPtr<IContraflexureResponse> cf_resp;
      hr = pVDoc->m_pLBAMAnalysisEngine->get_ContraflexureResponse(&cf_resp);
      ATLASSERT(cf_resp);

      ContraflexureDataSetBuilder* bdr = new ContraflexureDataSetBuilder(cf_resp );
      m_TreeItems.insert(TreeItemValueType(m_LastIndex, bdr) );
   }
}

void CLoadSelectTreeView::UpdateLoadGroups(CLBAMViewerDoc* pVDoc, CTreeCtrl* pTree, HTREEITEM parent)
{
   HRESULT hr;

   CComPtr<ILoadGroupResponse> lg_response;
   hr = pVDoc->m_pLBAMAnalysisEngine->get_LoadGroupResponse(&lg_response);
   ATLASSERT(SUCCEEDED(hr));

   CComPtr<ILoadGroups> LoadGroups;
   hr = pVDoc->m_pModel->get_LoadGroups(&LoadGroups); // list of LoadGroups in document

   CollectionIndexType nLoadGroups;
   hr = LoadGroups->get_Count(&nLoadGroups);
   if (nLoadGroups != 0)
   {
      for (CollectionIndexType ilgg=0; ilgg<nLoadGroups; ilgg++)
      {
         CComBSTR blg;
         CComPtr<ILoadGroup> LoadGroup;
         hr = LoadGroups->get_Item(ilgg,&LoadGroup);
         hr = LoadGroup->get_Name(&blg);
         CString lg( blg );
         HTREEITEM hitm = pTree->InsertItem(lg, m_LoadGroupImages.ImageIdx , m_LoadGroupImages.SelectedImageIdx , parent);

         m_LastIndex++;
         InitializeItemData(pTree, hitm, m_LastIndex);

         // create our builder
         LoadGroupDataSetBuilder* bdr = new LoadGroupDataSetBuilder(blg, lg_response );
         m_TreeItems.insert(TreeItemValueType(m_LastIndex, bdr) );
      }
   }
}

void CLoadSelectTreeView::UpdateLoadCases(CLBAMViewerDoc* pVDoc, CTreeCtrl* pTree, HTREEITEM parent)
{
   HRESULT hr;

   CComPtr<ILoadCaseResponse> lc_response;
   hr = pVDoc->m_pLBAMAnalysisEngine->get_LoadCaseResponse(&lc_response);
   ATLASSERT(SUCCEEDED(hr));

   CComPtr<ILoadCases> LoadCases;
   hr = pVDoc->m_pModel->get_LoadCases(&LoadCases); // list of LoadCases in document

   CollectionIndexType nLoadCases;
   hr = LoadCases->get_Count(&nLoadCases);
   if (nLoadCases != 0)
   {
      for (CollectionIndexType ilgg=0; ilgg<nLoadCases; ilgg++)
      {
         CComBSTR blg;
         CComPtr<ILoadCase> LoadCase;
         hr = LoadCases->get_Item(ilgg,&LoadCase);
         hr = LoadCase->get_Name(&blg);
         CString lg( blg );
         HTREEITEM hitm = pTree->InsertItem(lg, m_LoadCaseImages.ImageIdx , m_LoadCaseImages.SelectedImageIdx , parent);

         m_LastIndex++;
         InitializeItemData(pTree, hitm, m_LastIndex);

         // create our builder
         LoadCaseDataSetBuilder* bdr = new LoadCaseDataSetBuilder(blg, lc_response );
         m_TreeItems.insert(TreeItemValueType(m_LastIndex, bdr) );
      }
   }
}

void CLoadSelectTreeView::UpdateLoadCombinations(CLBAMViewerDoc* pVDoc, CTreeCtrl* pTree, HTREEITEM parent)
{
   HRESULT hr;

   CComPtr<ILoadCombinationResponse> lc_response;
   hr = pVDoc->m_pLBAMAnalysisEngine->get_LoadCombinationResponse(&lc_response);
   ATLASSERT(SUCCEEDED(hr));

   CComPtr<ILoadCombinations> LoadCombinations;
   hr = pVDoc->m_pModel->get_LoadCombinations(&LoadCombinations); // list of LoadCombinations in document

   CollectionIndexType nLoadCombinations;
   hr = LoadCombinations->get_Count(&nLoadCombinations);
   if (nLoadCombinations != 0)
   {
      for (CollectionIndexType ilgg=0; ilgg<nLoadCombinations; ilgg++)
      {
         CComBSTR blg;
         CComPtr<ILoadCombination> LoadCombination;
         hr = LoadCombinations->get_Item(ilgg,&LoadCombination);
         hr = LoadCombination->get_Name(&blg);
         CString lg( blg );
         HTREEITEM hitm = pTree->InsertItem(lg, m_LoadCombinationImages.ImageIdx , m_LoadCombinationImages.SelectedImageIdx , parent);

         m_LastIndex++;
         InitializeItemData(pTree, hitm, m_LastIndex);

         // create our builder
         LoadCombinationDataSetBuilder* bdr = new LoadCombinationDataSetBuilder(blg, lc_response );
         m_TreeItems.insert(TreeItemValueType(m_LastIndex, bdr) );
      }
   }
}

void CLoadSelectTreeView::UpdateProperties(CLBAMViewerDoc* pVDoc, CTreeCtrl* pTree, HTREEITEM parent)
{
   CComPtr<ILoadGroupResponse> lg_response;
   HRESULT hr = pVDoc->m_pLBAMAnalysisEngine->get_LoadGroupResponse(&lg_response);
   ATLASSERT(SUCCEEDED(hr));

   CComQIPtr<IGetSegmentCrossSection> pgcs(lg_response);
   ATLASSERT(pgcs!=NULL);

   // area
   HTREEITEM hitm = pTree->InsertItem(_T("EAForce"), m_PropertyImages.ImageIdx , m_PropertyImages.SelectedImageIdx , parent);
   m_LastIndex++;
   InitializeItemData(pTree, hitm, m_LastIndex);
   PropertyDataSetBuilder* bdr = new PropertyDataSetBuilder(PropertyDataSetBuilder::ptEAForce, pgcs);
   m_TreeItems.insert(TreeItemValueType(m_LastIndex, bdr) );

   hitm = pTree->InsertItem(_T("EADefl"), m_PropertyImages.ImageIdx , m_PropertyImages.SelectedImageIdx , parent);
   m_LastIndex++;
   InitializeItemData(pTree, hitm, m_LastIndex);
   bdr = new PropertyDataSetBuilder(PropertyDataSetBuilder::ptEADefl, pgcs);
   m_TreeItems.insert(TreeItemValueType(m_LastIndex, bdr) );

   // EI
   hitm = pTree->InsertItem(_T("EIForce"), m_PropertyImages.ImageIdx , m_PropertyImages.SelectedImageIdx , parent);
   m_LastIndex++;
   InitializeItemData(pTree, hitm, m_LastIndex);
   bdr = new PropertyDataSetBuilder(PropertyDataSetBuilder::ptEIForce, pgcs);
   m_TreeItems.insert(TreeItemValueType(m_LastIndex, bdr) );

   hitm = pTree->InsertItem(_T("EIDefl"), m_PropertyImages.ImageIdx , m_PropertyImages.SelectedImageIdx , parent);
   m_LastIndex++;
   InitializeItemData(pTree, hitm, m_LastIndex);
   bdr = new PropertyDataSetBuilder(PropertyDataSetBuilder::ptEIDefl, pgcs);
   m_TreeItems.insert(TreeItemValueType(m_LastIndex, bdr) );

   // Depth
   hitm = pTree->InsertItem(_T("Depth"), m_PropertyImages.ImageIdx , m_PropertyImages.SelectedImageIdx , parent);
   m_LastIndex++;
   InitializeItemData(pTree, hitm, m_LastIndex);
   bdr = new PropertyDataSetBuilder(PropertyDataSetBuilder::ptDepth, pgcs);
   m_TreeItems.insert(TreeItemValueType(m_LastIndex, bdr) );

   // Thermal Coefficient
   hitm = pTree->InsertItem(_T("Thermal Coefficient"), m_PropertyImages.ImageIdx , m_PropertyImages.SelectedImageIdx , parent);
   m_LastIndex++;
   InitializeItemData(pTree, hitm, m_LastIndex);
   bdr = new PropertyDataSetBuilder(PropertyDataSetBuilder::ptThermal, pgcs);
   m_TreeItems.insert(TreeItemValueType(m_LastIndex, bdr) );

   // Stress Coefficients
   CComQIPtr<IGetStressPoints> pgsp(lg_response);
   ATLASSERT(pgcs!=NULL);

   hitm = pTree->InsertItem(_T("Sa - Axial Stress Coefficient"), m_PropertyImages.ImageIdx , m_PropertyImages.SelectedImageIdx , parent);
   m_LastIndex++;
   InitializeItemData(pTree, hitm, m_LastIndex);
   StressPointDataSetBuilder* spbdr = new StressPointDataSetBuilder(StressPointDataSetBuilder::stSa, pgsp);
   m_TreeItems.insert(TreeItemValueType(m_LastIndex, spbdr) );

   hitm = pTree->InsertItem(_T("Sm - Moment Stress Coefficient"), m_PropertyImages.ImageIdx , m_PropertyImages.SelectedImageIdx , parent);
   m_LastIndex++;
   InitializeItemData(pTree, hitm, m_LastIndex);
   spbdr = new StressPointDataSetBuilder(StressPointDataSetBuilder::stSm, pgsp);
   m_TreeItems.insert(TreeItemValueType(m_LastIndex, spbdr) );

   // Distribution Factors
   CComQIPtr<IGetDistributionFactors> pgdf(lg_response); // highly suspicious
   ATLASSERT(pgdf!=NULL);

   hitm = pTree->InsertItem(_T("Distribution Factors"), m_FolderImages.ImageIdx ,m_FolderImages.SelectedImageIdx, parent );
   pTree->SetItemData(hitm, -1);

   // a new level
   parent = hitm;

   hitm = pTree->InsertItem(_T("GPMSgl - Positive moment, Single lane"), m_DfImages.ImageIdx , m_DfImages.SelectedImageIdx , parent);
   m_LastIndex++;
   InitializeItemData(pTree, hitm, m_LastIndex);
   DistributionFactorDataSetBuilder* dfbdr = new DistributionFactorDataSetBuilder(DistributionFactorDataSetBuilder::dtGPMSgl, pgdf);
   m_TreeItems.insert(TreeItemValueType(m_LastIndex, dfbdr) );

   hitm = pTree->InsertItem(_T("GPMMul - Positive moment, Multiple lane"), m_DfImages.ImageIdx , m_DfImages.SelectedImageIdx , parent);
   m_LastIndex++;
   InitializeItemData(pTree, hitm, m_LastIndex);
   dfbdr = new DistributionFactorDataSetBuilder(DistributionFactorDataSetBuilder::dtGPMMul, pgdf);
   m_TreeItems.insert(TreeItemValueType(m_LastIndex, dfbdr) );

   hitm = pTree->InsertItem(_T("GNMSgl - Negative moment, Single lane"), m_DfImages.ImageIdx , m_DfImages.SelectedImageIdx , parent);
   m_LastIndex++;
   InitializeItemData(pTree, hitm, m_LastIndex);
   dfbdr = new DistributionFactorDataSetBuilder(DistributionFactorDataSetBuilder::dtGNMSgl, pgdf);
   m_TreeItems.insert(TreeItemValueType(m_LastIndex, dfbdr) );

   hitm = pTree->InsertItem(_T("GNMMul - Negative moment, Multiple lane"), m_DfImages.ImageIdx , m_DfImages.SelectedImageIdx , parent);
   m_LastIndex++;
   InitializeItemData(pTree, hitm, m_LastIndex);
   dfbdr = new DistributionFactorDataSetBuilder(DistributionFactorDataSetBuilder::dtGNMMul, pgdf);
   m_TreeItems.insert(TreeItemValueType(m_LastIndex, dfbdr) );

   hitm = pTree->InsertItem(_T("GVSgl - Shear, Single lane"), m_DfImages.ImageIdx , m_DfImages.SelectedImageIdx , parent);
   m_LastIndex++;
   InitializeItemData(pTree, hitm, m_LastIndex);
   dfbdr = new DistributionFactorDataSetBuilder(DistributionFactorDataSetBuilder::dtGVSgl, pgdf);
   m_TreeItems.insert(TreeItemValueType(m_LastIndex, dfbdr) );

   hitm = pTree->InsertItem(_T("GVMul - Shear, Multiple lane"), m_DfImages.ImageIdx , m_DfImages.SelectedImageIdx , parent);
   m_LastIndex++;
   InitializeItemData(pTree, hitm, m_LastIndex);
   dfbdr = new DistributionFactorDataSetBuilder(DistributionFactorDataSetBuilder::dtGVMul, pgdf);
   m_TreeItems.insert(TreeItemValueType(m_LastIndex, dfbdr) );

   hitm = pTree->InsertItem(_T("GDSgl - Deflection, Single lane"), m_DfImages.ImageIdx , m_DfImages.SelectedImageIdx , parent);
   m_LastIndex++;
   InitializeItemData(pTree, hitm, m_LastIndex);
   dfbdr = new DistributionFactorDataSetBuilder(DistributionFactorDataSetBuilder::dtGDSgl, pgdf);
   m_TreeItems.insert(TreeItemValueType(m_LastIndex, dfbdr) );

   hitm = pTree->InsertItem(_T("GDMul - Deflection, Multiple lane"), m_DfImages.ImageIdx , m_DfImages.SelectedImageIdx , parent);
   m_LastIndex++;
   InitializeItemData(pTree, hitm, m_LastIndex);
   dfbdr = new DistributionFactorDataSetBuilder(DistributionFactorDataSetBuilder::dtGDMul, pgdf);
   m_TreeItems.insert(TreeItemValueType(m_LastIndex, dfbdr) );

   hitm = pTree->InsertItem(_T("GTSgl - Rotation, Single lane"), m_DfImages.ImageIdx , m_DfImages.SelectedImageIdx , parent);
   m_LastIndex++;
   InitializeItemData(pTree, hitm, m_LastIndex);
   dfbdr = new DistributionFactorDataSetBuilder(DistributionFactorDataSetBuilder::dtGTSgl, pgdf);
   m_TreeItems.insert(TreeItemValueType(m_LastIndex, dfbdr) );

   hitm = pTree->InsertItem(_T("GTMul - Rotation, Multiple lane"), m_DfImages.ImageIdx , m_DfImages.SelectedImageIdx , parent);
   m_LastIndex++;
   InitializeItemData(pTree, hitm, m_LastIndex);
   dfbdr = new DistributionFactorDataSetBuilder(DistributionFactorDataSetBuilder::dtGTMul, pgdf);
   m_TreeItems.insert(TreeItemValueType(m_LastIndex, dfbdr) );

   hitm = pTree->InsertItem(_T("dtGRSgl - Reaction, Single lane"), m_DfImages.ImageIdx , m_DfImages.SelectedImageIdx , parent);
   m_LastIndex++;
   InitializeItemData(pTree, hitm, m_LastIndex);
   dfbdr = new DistributionFactorDataSetBuilder(DistributionFactorDataSetBuilder::dtGRSgl, pgdf);
   m_TreeItems.insert(TreeItemValueType(m_LastIndex, dfbdr) );

   hitm = pTree->InsertItem(_T("dtGRMul - Reaction, Multiple lane"), m_DfImages.ImageIdx , m_DfImages.SelectedImageIdx , parent);
   m_LastIndex++;
   InitializeItemData(pTree, hitm, m_LastIndex);
   dfbdr = new DistributionFactorDataSetBuilder(DistributionFactorDataSetBuilder::dtGRMul, pgdf);
   m_TreeItems.insert(TreeItemValueType(m_LastIndex, dfbdr) );

   hitm = pTree->InsertItem(_T("dtGFat - Fatigue, all cases"), m_DfImages.ImageIdx , m_DfImages.SelectedImageIdx , parent);
   m_LastIndex++;
   InitializeItemData(pTree, hitm, m_LastIndex);
   dfbdr = new DistributionFactorDataSetBuilder(DistributionFactorDataSetBuilder::dtGFat, pgdf);
   m_TreeItems.insert(TreeItemValueType(m_LastIndex, dfbdr) );
}


void CLoadSelectTreeView::UpdatePoiDependentTree(CLBAMViewerDoc* pVDoc, CTreeCtrl* pTree, HTREEITEM parent, 
                                                 IconTracker &icons, iDataSetBuilderBuilder& builder)
{
   HRESULT hr;

   CComPtr<IPOIs> pois;
   hr = pVDoc->m_pModel->get_POIs(&pois); 

   CollectionIndexType npois;
   hr = pois->get_Count(&npois);
   if (npois != 0)
   {
      for (CollectionIndexType ipoi=0; ipoi<npois; ipoi++)
      {
         CComPtr<IPOI> poi;
         hr = pois->get_Item(ipoi,&poi);
         ATLASSERT(SUCCEEDED(hr));

         PoiIDType poi_id;
         hr = poi->get_ID(&poi_id);

         MemberType poi_mt;
         hr = poi->get_MemberType(&poi_mt);

         MemberIDType poi_mbrid;
         hr = poi->get_MemberID(&poi_mbrid);

         double poi_location;
         hr = poi->get_Location(&poi_location);

         CString descr = GetPoiDescription(poi_id, poi_mt, poi_mbrid, poi_location);

         HTREEITEM hitm = pTree->InsertItem(descr, icons.ImageIdx , icons.SelectedImageIdx , parent);

         m_LastIndex++;
         InitializeItemData(pTree, hitm, m_LastIndex);

         iDataSetBuilder* pbld = builder.Create(poi_id);
         m_TreeItems.insert(TreeItemValueType(m_LastIndex, pbld) );
      }
   }
}

void CLoadSelectTreeView::UpdateSupportInfluence(CLBAMViewerDoc* pVDoc, CTreeCtrl* pTree, HTREEITEM parent)
{
   HRESULT hr;

   CComPtr<IInfluenceLineResponse> influence_response;
   hr = pVDoc->m_pLBAMAnalysisEngine->get_InfluenceLineResponse(&influence_response);
   ATLASSERT(SUCCEEDED(hr));

   // first regular supports
   CComPtr<ISupports> Supports;
   hr = pVDoc->m_pModel->get_Supports(&Supports); // list of Supports in document

   SupportIndexType nSupports;
   hr = Supports->get_Count(&nSupports);
   if (nSupports != 0)
   {
      for (SupportIndexType suppno=0; suppno<nSupports; suppno++)
      {
         CString sn;
         sn.Format(_T("Support %d"), suppno);
         HTREEITEM hitm = pTree->InsertItem(sn, m_InfluenceLineImages.ImageIdx , m_InfluenceLineImages.SelectedImageIdx , parent);

         m_LastIndex++;
         InitializeItemData(pTree, hitm, m_LastIndex);

         // create our builder
         ReactionInfluenceDataSetBuilder* bdr = new ReactionInfluenceDataSetBuilder(suppno, influence_response );
         m_TreeItems.insert(TreeItemValueType(m_LastIndex, bdr) );
      }
   }

   // Next Temporary supports
   CComPtr<ISpans> spans;
   hr = pVDoc->m_pModel->get_Spans(&spans); // list of Spans in document

   SpanIndexType nspans;
   hr = spans->get_Count(&nspans);
   if (nspans != 0)
   {
      for (SpanIndexType spano=0; spano<nspans; spano++)
      {
         CComPtr<ISpan> span;
         hr = spans->get_Item(spano, &span);

         CComPtr<ITemporarySupports> tss;
         hr = span->get_TemporarySupports(&tss); 

         SupportIndexType nts;
         hr = tss->get_Count(&nts);
         for (SupportIndexType tsno=0; tsno<nts; tsno++)
         {
            CComPtr<ITemporarySupport> ts;
            hr = tss->get_Item(tsno, &ts);

            SupportIDType ts_id;
            hr = ts->get_ID(&ts_id);
            CComBSTR estage;

            hr = ts->get_StageRemoved(&estage);
            CString cstg(estage);

            CString sn;
            sn.Format(_T("Temporary Support %d (Removed in %s)"), ts_id, cstg);
            HTREEITEM hitm = pTree->InsertItem(sn, m_InfluenceLineImages.ImageIdx , m_InfluenceLineImages.SelectedImageIdx , parent);

            m_LastIndex++;
            InitializeItemData(pTree, hitm, m_LastIndex);

            // create our builder
            ReactionInfluenceDataSetBuilder* bdr = new ReactionInfluenceDataSetBuilder(ts_id, influence_response );
            m_TreeItems.insert(TreeItemValueType(m_LastIndex, bdr) );
         }
      }
   }
}


void CLoadSelectTreeView::BuildImageList() 
{
	CTreeCtrl& tree = GetTreeCtrl();

   // state images
	m_TreeStateImages.Create(IDB_TREE_STATES, 16, 2, RGB (255,255,255));
   tree.SetImageList(&m_TreeStateImages,LVSIL_STATE);

   // create and load up image list for tree control 
   // load two icons for each library. a normal and a selected
   m_TreeImages.Create(16,16,TRUE,20,10);

   // load names and images into tree control
   tree.SetImageList(&m_TreeImages,LVSIL_NORMAL);

   HICON ico_folder = ::LoadIcon( AfxGetInstanceHandle(), MAKEINTRESOURCE(IDI_FOLDER_ICON) );
   m_FolderImages.ImageIdx = m_TreeImages.Add(ico_folder);
   ASSERT(m_FolderImages.ImageIdx!=-1);

   HICON ico_open_folder = ::LoadIcon(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDI_OPEN_FOLDER_ICON) );
   m_FolderImages.SelectedImageIdx = m_TreeImages.Add(ico_open_folder);
   ASSERT(m_FolderImages.SelectedImageIdx!=-1);

   HICON ico_loadgroup = ::LoadIcon(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDI_LOADGROUP_ICON) );
   m_LoadGroupImages.ImageIdx = m_TreeImages.Add(ico_loadgroup);
   ASSERT(m_LoadGroupImages.ImageIdx!=-1);

   HICON ico_sel_loadgroup = ::LoadIcon(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDI_SELECTED_LOADGROUP_ICON) );
   m_LoadGroupImages.SelectedImageIdx  = m_TreeImages.Add(ico_sel_loadgroup);
   ASSERT(m_LoadGroupImages.SelectedImageIdx !=-1);

   HICON ico_loadcase = ::LoadIcon(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDI_LOADCASE_ICON) );
   m_LoadCaseImages.ImageIdx = m_TreeImages.Add(ico_loadcase);
   ASSERT(m_LoadCaseImages.ImageIdx!=-1);

   HICON ico_sel_loadcase = ::LoadIcon(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDI_SELECTED_LOADCASE_ICON) );
   m_LoadCaseImages.SelectedImageIdx  = m_TreeImages.Add(ico_sel_loadcase);
   ASSERT(m_LoadCaseImages.SelectedImageIdx !=-1);

   HICON ico_loadcombination = ::LoadIcon(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDI_LOADCOMBINATION_ICON) );
   m_LoadCombinationImages.ImageIdx = m_TreeImages.Add(ico_loadcombination);
   ASSERT(m_LoadCombinationImages.ImageIdx!=-1);

   HICON ico_sel_loadcombination = ::LoadIcon(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDI_SELECTED_LOADCOMBINATION_ICON) );
   m_LoadCombinationImages.SelectedImageIdx  = m_TreeImages.Add(ico_sel_loadcombination);
   ASSERT(m_LoadCombinationImages.SelectedImageIdx !=-1);

   HICON ico_vl = ::LoadIcon(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDI_TRUCK_LANE_ICON) );
   m_TruckLaneImages.ImageIdx = m_TreeImages.Add(ico_vl);
   ASSERT(m_TruckLaneImages.ImageIdx!=-1);

   HICON ico_sel_vl = ::LoadIcon(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDI_SELECTED_TRUCK_LANE_ICON) );
   m_TruckLaneImages.SelectedImageIdx  = m_TreeImages.Add(ico_sel_vl);
   ASSERT(m_TruckLaneImages.SelectedImageIdx !=-1);

   HICON ico_etr = ::LoadIcon(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDI_ENVELOPE_TRUCK_ICON) );
   m_EnvelopeTruckImages.ImageIdx = m_TreeImages.Add(ico_etr);
   ASSERT(m_EnvelopeTruckImages.ImageIdx!=-1);

   HICON ico_sel_etr = ::LoadIcon(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDI_SELECTED_ENVELOPE_TRUCK_ICON) );
   m_EnvelopeTruckImages.SelectedImageIdx  = m_TreeImages.Add(ico_sel_etr);
   ASSERT(m_EnvelopeTruckImages.SelectedImageIdx !=-1);

   HICON ico_etrl = ::LoadIcon(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDI_ENVELOPED_TRUCK_LANE_ICON) );
   m_EnvelopeTruckLaneImages.ImageIdx = m_TreeImages.Add(ico_etrl);
   ASSERT(m_EnvelopeTruckLaneImages.ImageIdx!=-1);

   HICON ico_sel_etrl = ::LoadIcon(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDI_SELECTED_ENVELOPED_TRUCK_LANE_ICON) );
   m_EnvelopeTruckLaneImages.SelectedImageIdx  = m_TreeImages.Add(ico_sel_etrl);
   ASSERT(m_EnvelopeTruckLaneImages.SelectedImageIdx !=-1);

   HICON ico_tr = ::LoadIcon(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDI_TRUCK_ICON) );
   m_TruckImages.ImageIdx = m_TreeImages.Add(ico_tr);
   ASSERT(m_TruckImages.ImageIdx!=-1);

   HICON ico_sel_tr = ::LoadIcon(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDI_SELECTED_TRUCK_ICON) );
   m_TruckImages.SelectedImageIdx  = m_TreeImages.Add(ico_sel_tr);
   ASSERT(m_TruckImages.SelectedImageIdx !=-1);

   HICON ico_ln = ::LoadIcon(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDI_LANE_ICON) );
   m_LaneImages.ImageIdx = m_TreeImages.Add(ico_ln);
   ASSERT(m_LaneImages.ImageIdx!=-1);

   HICON ico_sel_ln = ::LoadIcon(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDI_SELECTED_LANE_ICON) );
   m_LaneImages.SelectedImageIdx  = m_TreeImages.Add(ico_sel_ln);
   ASSERT(m_LaneImages.SelectedImageIdx !=-1);

   HICON ico_pd = ::LoadIcon(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDI_PEDESTRIAN_ICON) );
   m_PedestrianImages.ImageIdx = m_TreeImages.Add(ico_pd);
   ASSERT(m_PedestrianImages.ImageIdx!=-1);

   HICON ico_sel_pd = ::LoadIcon(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDI_SELECTED_PEDESTRIAN_ICON) );
   m_PedestrianImages.SelectedImageIdx  = m_TreeImages.Add(ico_sel_pd);
   ASSERT(m_PedestrianImages.SelectedImageIdx !=-1);

   HICON ico_il = ::LoadIcon(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDI_INFLUENCE_LINE_ICON) );
   m_InfluenceLineImages.ImageIdx = m_TreeImages.Add(ico_il);
   ASSERT(m_InfluenceLineImages.ImageIdx!=-1);

   HICON ico_sel_il = ::LoadIcon(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDI_SELECTED_INFLUENCE_LINE_ICON) );
   m_InfluenceLineImages.SelectedImageIdx  = m_TreeImages.Add(ico_sel_il);
   ASSERT(m_InfluenceLineImages.SelectedImageIdx !=-1);

   HICON ico_cf = ::LoadIcon(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDI_CONTRAFLEXURE_ICON) );
   m_ContraflexureImages.ImageIdx = m_TreeImages.Add(ico_cf);
   ASSERT(m_ContraflexureImages.ImageIdx!=-1);

   HICON ico_sel_cf = ::LoadIcon(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDI_SELECTED_CONTRAFLEXURE_ICON) );
   m_ContraflexureImages.SelectedImageIdx  = m_TreeImages.Add(ico_sel_cf);
   ASSERT(m_ContraflexureImages.SelectedImageIdx !=-1);

   HICON ico_ltl = ::LoadIcon(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDI_LIVE_LOAD_TL_MODEL_ICON) );
   m_LiveLoadModelTLImages.ImageIdx = m_TreeImages.Add(ico_ltl);
   ASSERT(m_LiveLoadModelTLImages.ImageIdx!=-1);

   HICON ico_sel_ltl = ::LoadIcon(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDI_SELECTED_LIVE_LOAD_TL_MODEL_ICON) );
   m_LiveLoadModelTLImages.SelectedImageIdx  = m_TreeImages.Add(ico_sel_ltl);
   ASSERT(m_LiveLoadModelTLImages.SelectedImageIdx !=-1);

   HICON ico_lto = ::LoadIcon(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDI_LIVE_LOAD_MODEL_ICON) );
   m_LiveLoadModelTOImages.ImageIdx = m_TreeImages.Add(ico_lto);
   ASSERT(m_LiveLoadModelTOImages.ImageIdx!=-1);

   HICON ico_sel_lto = ::LoadIcon(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDI_SELECTED_LIVE_LOAD_MODEL_ICON) );
   m_LiveLoadModelTOImages.SelectedImageIdx  = m_TreeImages.Add(ico_sel_lto);
   ASSERT(m_LiveLoadModelTOImages.SelectedImageIdx !=-1);

   HICON ico_property = ::LoadIcon(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDI_PROPERTY_ICON) );
   m_PropertyImages.ImageIdx = m_TreeImages.Add(ico_property);
   ASSERT(m_PropertyImages.ImageIdx!=-1);

   HICON ico_sel_property = ::LoadIcon(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDI_SELECTED_PROPERTY_ICON) );
   m_PropertyImages.SelectedImageIdx  = m_TreeImages.Add(ico_sel_property);
   ASSERT(m_PropertyImages.SelectedImageIdx !=-1);

   HICON ico_df = ::LoadIcon(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDI_DF_ICON) );
   m_DfImages.ImageIdx = m_TreeImages.Add(ico_df);
   ASSERT(m_DfImages.ImageIdx!=-1);

   HICON ico_sel_df = ::LoadIcon(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDI_SELECTED_DF_ICON) );
   m_DfImages.SelectedImageIdx  = m_TreeImages.Add(ico_sel_df);
   ASSERT(m_DfImages.SelectedImageIdx !=-1);
}

void CLoadSelectTreeView::OnSelchanged(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;
   // get information about item selected
   LPARAM efsel = pNMTreeView->itemNew.lParam;

	*pResult = 0;
}

void CLoadSelectTreeView::OnLButtonDown(UINT nFlags, CPoint point) 
{
	CTreeCtrl& tree = GetTreeCtrl();

	UINT nHF;
	HTREEITEM hItem;

	BOOL bBase;
	hItem = tree.HitTest(point, &nHF);
	if (hItem) 
   {
		bBase = (nHF & (TVHT_ONITEMBUTTON/*|TVHT_ONITEMINDENT*/));
		if ( !bBase ) 
      {
			bBase = (nHF & TVHT_ONITEMSTATEICON);
         if (bBase)
         {
            long efsel = (long)tree.GetItemData( hItem );
            if (efsel != -1)
            {
               // selection data is in our frame
               CChildFrame* pframe = (CChildFrame*)GetParentFrame( );

               UINT ste = tree.GetItemState(hItem, TVIS_STATEIMAGEMASK) >> 12;
               if (ste==1)
               {
                  // just got checked - add builder
         			tree.SetItemState(hItem, INDEXTOSTATEIMAGEMASK(2), TVIS_STATEIMAGEMASK);

                  iDataSetBuilder* ds = m_TreeItems[efsel];
                  ds->InitializeOnSelect();
                  pframe->AddDataSetBuilder(efsel, ds, true);
               }
               else if (ste==2)
               {
                  // just got unchecked - remove builder
         			tree.SetItemState(hItem,  INDEXTOSTATEIMAGEMASK(1), TVIS_STATEIMAGEMASK);

                  pframe->RemoveDataSetBuilder(efsel, true);
               }
            }
         }
      }
   }
	
	CTreeView::OnLButtonDown(nFlags, point);
}

void CLoadSelectTreeView::OnRButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	
	CTreeView::OnRButtonDown(nFlags, point);
}
