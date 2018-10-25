#ifndef INCLUDED_LBAMTRUCKDISPLAYOBJECT_H_
#define INCLUDED_LBAMTRUCKDISPLAYOBJECT_H_

#include "LBAMTruckDrawStrategy.h"
#include "LBAMTruckEvents.h"

class CLBAMTruckDisplayImpl : public CCmdTarget
{
public:
   CLBAMTruckDisplayImpl();
   ~CLBAMTruckDisplayImpl();

   DECLARE_INTERFACE_MAP()

   BEGIN_INTERFACE_PART(Strategy,iLBAMTruckDrawStrategy)
      STDMETHOD_(void,SetColor)(COLORREF color);
   END_INTERFACE_PART(Strategy)

   BEGIN_INTERFACE_PART(Events,iLBAMTruckEvents)
      STDMETHOD_(void,Init)(iPointDisplayObject* pDO,ILBAMModel* model, LiveLoadModelType modelType, long vehicleIndex, ILiveLoadConfiguration* placement);
      STDMETHOD_(void,GetLiveLoadConfiguration)(ILiveLoadConfiguration** dispObj);
		STDMETHOD_(void,GetRoadwayElevation)(double *pVal);
		STDMETHOD_(void,SetRoadwayElevation)(iPointDisplayObject* pDO, double newVal);
   END_INTERFACE_PART(Events)

   BEGIN_INTERFACE_PART(DrawPointStrategy,iDrawPointStrategy)
      STDMETHOD_(void,Draw)(iPointDisplayObject* pDO,CDC* pDC);
      STDMETHOD_(void,DrawDragImage)(iPointDisplayObject* pDO,CDC* pDC, iCoordinateMap* map, const CPoint& dragStart, const CPoint& cpdragPoint);
      STDMETHOD_(void,DrawHighlite)(iPointDisplayObject* pDO,CDC* pDC,BOOL bHighlite);
      STDMETHOD_(void,GetBoundingBox)(iPointDisplayObject* pDO,IRect2d** box);
   END_INTERFACE_PART(DrawPointStrategy)

   BEGIN_INTERFACE_PART(DisplayObjectEvents,iDisplayObjectEvents)
      STDMETHOD_(void,OnChanged)(iDisplayObject* pDO);
      STDMETHOD_(void,OnDragMoved)(iDisplayObject* pDO,ISize2d* offset);
      STDMETHOD_(void,OnMoved)(iDisplayObject* pDO);
      STDMETHOD_(void,OnCopied)(iDisplayObject* pDO);
      STDMETHOD_(bool,OnLButtonDblClk)(iDisplayObject* pDO,UINT nFlags,CPoint point);
      STDMETHOD_(bool,OnLButtonDown)(iDisplayObject* pDO,UINT nFlags,CPoint point);
      STDMETHOD_(bool,OnRButtonDblClk)(iDisplayObject* pDO,UINT nFlags,CPoint point);
      STDMETHOD_(bool,OnRButtonDown)(iDisplayObject* pDO,UINT nFlags,CPoint point);
      STDMETHOD_(bool,OnRButtonUp)(iDisplayObject* pDO,UINT nFlags,CPoint point);
      STDMETHOD_(bool,OnLButtonUp)(iDisplayObject* pDO,UINT nFlags,CPoint point);
      STDMETHOD_(bool,OnMouseMove)(iDisplayObject* pDO,UINT nFlags,CPoint point);
      STDMETHOD_(bool,OnMouseWheel)(iDisplayObject* pDO,UINT nFlags,short zDelta,CPoint point);
      STDMETHOD_(bool,OnKeyDown)(iDisplayObject* pDO,UINT nChar, UINT nRepCnt, UINT nFlags);
      STDMETHOD_(bool,OnContextMenu)(iDisplayObject* pDO,CWnd* pWnd,CPoint point);
      STDMETHOD_(void,OnSelect)(iDisplayObject* pDO);
      STDMETHOD_(void,OnUnselect)(iDisplayObject* pDO);
   END_INTERFACE_PART(DisplayObjectEvents)

   // iDragData Implementation
   BEGIN_INTERFACE_PART(DragData,iDragData)
      STDMETHOD_(UINT,Format)();
      STDMETHOD_(BOOL,PrepareForDrag)(iDisplayObject* pDO,iDragDataSink* pSink);
      STDMETHOD_(void,OnDrop)(iDisplayObject* pDO,iDragDataSource* pSource);
   END_INTERFACE_PART(DragData)

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
   virtual void Draw(iPointDisplayObject* pDO,CDC* pDC,COLORREF color, IPoint2d* loc);
   COLORREF m_Color;

   CComPtr<ILiveLoadConfiguration> m_Placement;
   DWORD                           m_PlacementCookie;

   CComPtr<IVehicularLoad>          m_VehicularLoad;
   double                           m_RoadwayElevation;

   // dirty flag and Compute function
   bool m_Dirty;
   void Compute(iPointDisplayObject* pDO);

   // cached truck parameters
   void CacheTruckParameters();
   void UpdateTruckPosition(iPointDisplayObject* pDO, double location);
   std::vector<double> m_AxleLocations;  // axle locations relative to first axle
   std::vector<bool>   m_ActiveAxles;
   double              m_WheelDiameter;
   double              m_CabHeight;
   double              m_TrailerHeight;

};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.




#endif // INCLUDED_TRUCKDISPLAYOBJECT_H_