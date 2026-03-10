#ifndef INCLUDED_LBAMTRUCKDISPLAYOBJECT_H_
#define INCLUDED_LBAMTRUCKDISPLAYOBJECT_H_

#include "LBAMTruckDrawStrategy.h"
#include "LBAMTruckEvents.h"

class CLBAMTruckDisplayImpl : 
   public CCmdTarget,
   public iLBAMTruckDrawStrategy, 
   public iLBAMTruckEvents, 
   public WBFL::DManip::iDrawPointStrategy, 
   public WBFL::DManip::iDisplayObjectEvents,
   public WBFL::DManip::iDragData
{
public:
   CLBAMTruckDisplayImpl();
   ~CLBAMTruckDisplayImpl();

   DECLARE_INTERFACE_MAP()

   void SetColor(COLORREF color) override;

   void Init(std::shared_ptr<WBFL::DManip::iPointDisplayObject> pDO, ILBAMModel* model, LiveLoadModelType modelType, VehicleIndexType vehicleIndex, ILiveLoadConfiguration* placement) override;
   void GetLiveLoadConfiguration(ILiveLoadConfiguration** dispObj) override;
	void GetRoadwayElevation(double *pVal) override;
	void SetRoadwayElevation(std::shared_ptr<WBFL::DManip::iPointDisplayObject> pDO, double newVal) override;

   void Draw(std::shared_ptr<const WBFL::DManip::iPointDisplayObject> pDO, CDC* pDC) const override;
   void DrawDragImage(std::shared_ptr<const WBFL::DManip::iPointDisplayObject> pDO, CDC* pDC, std::shared_ptr<const WBFL::DManip::iCoordinateMap> map, const POINT& dragStart, const POINT& cpdragPoint) const override;
   void DrawHighlight(std::shared_ptr<const WBFL::DManip::iPointDisplayObject> pDO, CDC* pDC, bool bHighlite) const override;
   WBFL::Geometry::Rect2d GetBoundingBox(std::shared_ptr<const WBFL::DManip::iPointDisplayObject> pDO) const override;

   // iDisplayObjectEvents Implementation
   void OnChanged(std::shared_ptr<WBFL::DManip::iDisplayObject> pDO) override;
   void OnDragMoved(std::shared_ptr<WBFL::DManip::iDisplayObject> pDO, const WBFL::Geometry::Size2d& offset) override;
   bool OnLButtonDblClk(std::shared_ptr<WBFL::DManip::iDisplayObject> pDO, UINT nFlags, const POINT& point) override;
   bool OnLButtonDown(std::shared_ptr<WBFL::DManip::iDisplayObject> pDO, UINT nFlags, const POINT& point) override;
   bool OnLButtonUp(std::shared_ptr<WBFL::DManip::iDisplayObject> pDO, UINT nFlags, const POINT& point) override;
   bool OnRButtonDblClk(std::shared_ptr<WBFL::DManip::iDisplayObject> pDO, UINT nFlags, const POINT& point) override;
   bool OnRButtonDown(std::shared_ptr<WBFL::DManip::iDisplayObject> pDO, UINT nFlags, const POINT& point) override;
   bool OnRButtonUp(std::shared_ptr<WBFL::DManip::iDisplayObject> pDO, UINT nFlags, const POINT& point) override;
   bool OnMouseMove(std::shared_ptr<WBFL::DManip::iDisplayObject> pDO, UINT nFlags, const POINT& point) override;
   bool OnMouseWheel(std::shared_ptr<WBFL::DManip::iDisplayObject> pDO, UINT nFlags, short zDelta, const POINT& point) override;
   void OnMoved(std::shared_ptr<WBFL::DManip::iDisplayObject> pDO) override;
   void OnCopied(std::shared_ptr<WBFL::DManip::iDisplayObject> pDO) override;
   bool OnKeyDown(std::shared_ptr<WBFL::DManip::iDisplayObject> pDO, UINT nChar, UINT nRepCnt, UINT nFlags) override;
   bool OnContextMenu(std::shared_ptr<WBFL::DManip::iDisplayObject> pDO, CWnd* pWnd, const POINT& point) override;
   void OnSelect(std::shared_ptr<WBFL::DManip::iDisplayObject> pDO) override;
   void OnUnselect(std::shared_ptr<WBFL::DManip::iDisplayObject> pDO) override;

   // iDragData Implementation
   UINT Format() override;
   bool PrepareForDrag(std::shared_ptr<WBFL::DManip::iDisplayObject> pDO, std::shared_ptr<WBFL::DManip::iDragDataSink> pSink) override;
   void OnDrop(std::shared_ptr<WBFL::DManip::iDisplayObject> pDO, std::shared_ptr<WBFL::DManip::iDragDataSource> pSource) override;

   BEGIN_INTERFACE_PART(LiveLoadEvents,ILiveLoadConfigurationEvents)
      STDMETHOD_(HRESULT,OnLiveLoadConfigurationChanged)(ILiveLoadConfiguration* placement);
   END_INTERFACE_PART(LiveLoadEvents)

	DECLARE_MESSAGE_MAP()

   DECLARE_DISPATCH_MAP()

    // Note from George Shepherd: ClassWizard looks for these comments:
    // Generated OLE dispatch map functions
    //{{AFX_DISPATCH(AClassWithAutomation)
    //}}AFX_DISPATCH
 

   // pop dialog to edit truck position
   void EditTruckPosition();

public:

   void EditTruck();
   static UINT ms_Format;

public:
   void Draw(std::shared_ptr<const WBFL::DManip::iPointDisplayObject> pDO,CDC* pDC,COLORREF color, const WBFL::Geometry::Point2d& loc) const;
   COLORREF m_Color;

   CComPtr<ILiveLoadConfiguration> m_Placement;
   DWORD                           m_PlacementCookie;

   CComPtr<IVehicularLoad>          m_VehicularLoad;
   double                           m_RoadwayElevation;

   // dirty flag and Compute function
   mutable bool m_Dirty;
   void Compute(std::shared_ptr<const WBFL::DManip::iPointDisplayObject> pDO) const;

   // cached truck parameters
   void CacheTruckParameters() const;
   void UpdateTruckPosition(std::shared_ptr<const WBFL::DManip::iPointDisplayObject> pDO, double location) const;
   mutable std::vector<double> m_AxleLocations;  // axle locations relative to first axle
   mutable std::vector<BOOL>   m_ActiveAxles;
   mutable double              m_WheelDiameter;
   mutable double              m_CabHeight;
   mutable double              m_TrailerHeight;

};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.




#endif // INCLUDED_TRUCKDISPLAYOBJECT_H_