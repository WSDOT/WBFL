///////////////////////////////////////////////////////////////////////
// GenericBridge - Generic Bridge Modeling Framework
// Copyright © 1999-2018  Washington State Department of Transportation
//                        Bridge and Structures Office
//
// This library is a part of the Washington Bridge Foundation Libraries
// and was developed as part of the Alternate Route Project
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the Alternate Route Library Open Source License as 
// published by the Washington State Department of Transportation,
// Bridge and Structures Office.
//
// This program is distributed in the hope that it will be useful,
// but is distributed AS IS, WITHOUT ANY WARRANTY; without even the
// implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR 
// PURPOSE.  See the Alternate Route Library Open Source License for more details.
//
// You should have received a copy of the Alternate Route Library Open Source License
// along with this program; if not, write to the Washington State
// Department of Transportation, Bridge and Structures Office,
// P.O. Box 47340, Olympia, WA 98503, USA or e-mail
// Bridge_Support@wsdot.wa.gov
///////////////////////////////////////////////////////////////////////

// ThickenedFlangeBulbTeeSegment.cpp : Implementation of CThickenedFlangeBulbTeeSegment
#include "stdafx.h"
#include "WBFLGenericBridge.h"
#include "ThickenedFlangeBulbTeeSegment.h"
#include <MathEx.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CThickenedFlangeBulbTeeSegment
HRESULT CThickenedFlangeBulbTeeSegment::FinalConstruct()
{
   m_pGirderLine = nullptr;
   m_Orientation = 0;
   m_HaunchDepth[0] = 0;
   m_HaunchDepth[1] = 0;
   m_HaunchDepth[2] = 0;
   m_Fillet = 0;

   return S_OK;
}

void CThickenedFlangeBulbTeeSegment::FinalRelease()
{
   m_pGirderLine = nullptr;
   m_Shapes.clear();
}

STDMETHODIMP CThickenedFlangeBulbTeeSegment::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_ISegment,
      &IID_IStructuredStorage2,
	};
	for (int i = 0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

////////////////////////////////////////////////////////////////////////
// ISegment implementation
STDMETHODIMP CThickenedFlangeBulbTeeSegment::putref_SuperstructureMember(ISuperstructureMember* ssMbr)
{
   CHECK_IN(ssMbr);
   m_pSSMbr = ssMbr;
   return S_OK;
}

STDMETHODIMP CThickenedFlangeBulbTeeSegment::get_SuperstructureMember(ISuperstructureMember** ssMbr)
{
   CHECK_RETOBJ(ssMbr);
   if ( m_pSSMbr )
   {
      (*ssMbr) = m_pSSMbr;
      (*ssMbr)->AddRef();
   }
   else
   {
      (*ssMbr) = nullptr;
   }

   return S_OK;
}

STDMETHODIMP CThickenedFlangeBulbTeeSegment::putref_GirderLine(IGirderLine* girderLine)
{
   m_pGirderLine = girderLine;
   return S_OK;
}

STDMETHODIMP CThickenedFlangeBulbTeeSegment::get_GirderLine(IGirderLine** girderLine)
{
   CHECK_RETOBJ(girderLine);
   if ( m_pGirderLine )
   {
      (*girderLine) = m_pGirderLine;
      (*girderLine)->AddRef();
   }
   else
   {
      (*girderLine) = nullptr;
   }

   return S_OK;
}

STDMETHODIMP CThickenedFlangeBulbTeeSegment::putref_PrevSegment(ISegment* segment)
{
   CHECK_IN(segment);
   ISuperstructureMemberSegment* pMySeg = m_pPrevSegment; // weak references so no change in ref count
   m_pPrevSegment = nullptr;
   HRESULT hr = segment->QueryInterface(&m_pPrevSegment); // causes ref count to increment
   if ( FAILED(hr) )
   {
      m_pPrevSegment = pMySeg;
      return hr;
   }
   m_pPrevSegment->Release(); // need to decrement ref count causd by QueryInterface to maintain this as a weak reference
   return S_OK;
}

STDMETHODIMP CThickenedFlangeBulbTeeSegment::get_PrevSegment(ISegment** segment)
{
   CHECK_RETVAL(segment);
   if ( m_pPrevSegment )
   {
      return m_pPrevSegment->QueryInterface(segment);
   }
   else
   {
      *segment = nullptr;
      return E_FAIL;
   }
}

STDMETHODIMP CThickenedFlangeBulbTeeSegment::putref_NextSegment(ISegment* segment)
{
   CHECK_IN(segment);
   ISuperstructureMemberSegment* pMySeg = m_pNextSegment; // weak references so no change in ref count
   m_pNextSegment = nullptr;
   HRESULT hr = segment->QueryInterface(&m_pNextSegment); // causes ref count to increment
   if ( FAILED(hr) )
   {
      m_pNextSegment = pMySeg;
      return hr;
   }
   m_pNextSegment->Release(); // need to decrement ref count causd by QueryInterface to maintain this as a weak reference
   return S_OK;
}

STDMETHODIMP CThickenedFlangeBulbTeeSegment::get_NextSegment(ISegment** segment)
{
   CHECK_RETVAL(segment);
   if ( m_pNextSegment )
   {
      return m_pNextSegment->QueryInterface(segment);
   }
   else
   {
      *segment = nullptr;
      return E_FAIL;
   }
}

STDMETHODIMP CThickenedFlangeBulbTeeSegment::get_Length(Float64 *pVal)
{
   return m_pGirderLine->get_GirderLength(pVal);
}

STDMETHODIMP CThickenedFlangeBulbTeeSegment::get_LayoutLength(Float64 *pVal)
{
   return m_pGirderLine->get_LayoutLength(pVal);
}

STDMETHODIMP CThickenedFlangeBulbTeeSegment::get_Section(StageIndexType stageIdx,Float64 Xs, SectionBias sectionBias,ISection** ppSection)
{
   CHECK_RETOBJ(ppSection);

   if (m_Shapes.size() == 0 )
   {
      *ppSection = 0;
      return S_OK;
   }

   HRESULT hr;
   CComPtr<IShape> primaryShape;
   hr = get_PrimaryShape(Xs,sectionBias,&primaryShape);
   ATLASSERT(SUCCEEDED(hr));
   if ( FAILED(hr) )
   {
      return hr;
   }

   // create our section object
   CComPtr<ICompositeSectionEx> section;
   section.CoCreateInstance(CLSID_CompositeSectionEx);

   section->QueryInterface(IID_ISection,(void**)ppSection);
   ATLASSERT(*ppSection != nullptr);

   // add the primary shape
   Float64 Efg = 0;
   m_Shapes.front().FGMaterial->get_E(stageIdx,&Efg);
   
   Float64 Ebg = 0;
   if ( m_Shapes.front().BGMaterial )
   {
      m_Shapes.front().BGMaterial->get_E(stageIdx,&Ebg);
   }

   Float64 Dfg = 0;
   m_Shapes.front().FGMaterial->get_Density(stageIdx,&Dfg);
   
   Float64 Dbg = 0;
   if ( m_Shapes.front().BGMaterial )
   {
      m_Shapes.front().BGMaterial->get_Density(stageIdx,&Dbg);
   }

   section->AddSection(primaryShape,Efg,Ebg,Dfg,Dbg,VARIANT_TRUE);

   // add all the secondary shapes
   std::vector<ShapeData>::iterator iter(m_Shapes.begin());
   std::vector<ShapeData>::iterator end(m_Shapes.end());
   iter++; // skip the first shape, we already processed it

   for ( ; iter != end; iter++ )
   {
      ShapeData& shapeData = *iter;

      Float64 Efg = 0;
      if ( shapeData.FGMaterial )
      {
         shapeData.FGMaterial->get_E(stageIdx,&Efg);
      }

      Float64 Ebg;
      if ( shapeData.BGMaterial )
      {
         shapeData.BGMaterial->get_E(stageIdx,&Ebg);
      }

      Float64 Dfg = 0;
      if ( shapeData.FGMaterial )
      {
         shapeData.FGMaterial->get_Density(stageIdx,&Dfg);
      }

      Float64 Dbg = 0;
      if ( shapeData.BGMaterial )
      {
         shapeData.BGMaterial->get_Density(stageIdx,&Dbg);
      }

      CComPtr<IShape> shape;
      shapeData.Shape->Clone(&shape);

      section->AddSection(shape,Efg,Ebg,Dfg,Dbg,VARIANT_TRUE);
   }

   return S_OK;
}

STDMETHODIMP CThickenedFlangeBulbTeeSegment::get_PrimaryShape(Float64 Xs, SectionBias sectionBias,IShape** ppShape)
{
   CHECK_RETOBJ(ppShape);

   if (m_Shapes.size() == 0 )
   {
      *ppShape = 0;
      return S_OK;
   }

   CComQIPtr<IBulbTeeSection> beam(m_Shapes.front().Shape);
   ATLASSERT(beam); // if this is nullptr... how did it get in the system????

   // This object reprsents a prismatic shape... all sections are the same
   HRESULT hr = S_OK;

   // get dimensions of beam shape at start and end of segment
   CComPtr<IBulbTee> pcBeam;

   Float64 W1, W2, W3, W4;
   Float64 D1, D2, D3, D4, D5, D6, D7;
   Float64 T1, T2;

   beam->get_Beam(&pcBeam);

   pcBeam->get_W1(&W1);
   pcBeam->get_W2(&W2);
   pcBeam->get_W3(&W3);
   pcBeam->get_W4(&W4);

   pcBeam->get_D1(&D1);
   pcBeam->get_D2(&D2);
   pcBeam->get_D3(&D3);
   pcBeam->get_D4(&D4);
   pcBeam->get_D5(&D5);
   pcBeam->get_D6(&D6);
   pcBeam->get_D7(&D7);

   pcBeam->get_T1(&T1);
   pcBeam->get_T2(&T2);

   // parabolic interpolation of the depth of the top flange thickening

   Float64 D8 = GetFlangeThickening(Xs);

   // create a new shape that is a clone of the original
   CComQIPtr<IShape> shape(beam);
   CComPtr<IShape> newShape;
   hr = shape->Clone(&newShape);

   // set the dimensions
   CComQIPtr<IBulbTeeSection> newFlangedBeam(newShape);
   CComPtr<IBulbTee> newBeam;
   newFlangedBeam->get_Beam(&newBeam);
   newBeam->put_D1(D1 + D8); // thicken the top flange
   newBeam->put_D2(D2);
   newBeam->put_D3(D3);
   newBeam->put_D4(D4);
   newBeam->put_D5(D5);
   newBeam->put_D6(D6);
   newBeam->put_D7(D7);
   newBeam->put_W1(W1);
   newBeam->put_W2(W2);
   newBeam->put_W3(W3);
   newBeam->put_W4(W4);
   newBeam->put_T1(T1);
   newBeam->put_T2(T2);

   // position the shape
   CComPtr<IPoint2d> pntTopCenter;
   GB_GetSectionLocation(this,Xs,&pntTopCenter);

   CComQIPtr<IXYPosition> position(newFlangedBeam);
   position->put_LocatorPoint(lpTopCenter,pntTopCenter);

   *ppShape = newShape;
   (*ppShape)->AddRef();

   return S_OK;
}

STDMETHODIMP CThickenedFlangeBulbTeeSegment::get_Profile(VARIANT_BOOL bIncludeClosure,IShape** ppShape)
{
   CHECK_RETOBJ(ppShape);

   Float64 segLength;
   get_Length(&segLength);

   CComPtr<IPolyShape> shape;
   shape.CoCreateInstance(CLSID_PolyShape);

   shape->AddPoint(segLength,0.0);
   shape->AddPoint(0.0,0.0);

   CComQIPtr<IBulbTeeSection> beam(m_Shapes.front().Shape);
   ATLASSERT(beam); // if this is nullptr... how did it get in the system????

   // get dimensions of beam shape at start and end of segment
   CComPtr<IBulbTee> pcBeam;
   Float64 D1, D2, D3, D4, D5, D6, D7;
   beam->get_Beam(&pcBeam);
   pcBeam->get_D1(&D1);
   pcBeam->get_D2(&D2);
   pcBeam->get_D3(&D3);
   pcBeam->get_D4(&D4);
   pcBeam->get_D5(&D5);
   pcBeam->get_D6(&D6);
   pcBeam->get_D7(&D7);

   Float64 H = D1 + D2 + D3 + D4 + D5 + D6 + D7;

   int nPoints = 21;
   for ( int i = 0; i < nPoints; i++ )
   {
      Float64 distAlongSegment = i*segLength/(nPoints-1);
      Float64 D8 = GetFlangeThickening(distAlongSegment);

      shape->AddPoint(distAlongSegment,H + D8);
   }

   Float64 brgOffset, endDist;
   if ( bIncludeClosure == VARIANT_TRUE )
   {
      brgOffset = 0;
      endDist = 0;
   }
   else
   {
      m_pGirderLine->get_BearingOffset(etStart,&brgOffset);
      m_pGirderLine->get_EndDistance(etStart,&endDist);
   }

   // Shape is to be in girder path coordinates so (0,0) is at the CL Pier and at the elevation of the top of the shape
   //
   // CL Pier   Start of segment
   // |         |       CL Bearing
   // |(0,0)    |       |
   // *         +-------+---------------\  
   // |         |       .               /
   // |         +-------+---------------\  
   //
   //          Elevation View



   CComQIPtr<IXYPosition> position(shape);
   CComPtr<IPoint2d> topLeft;
   position->get_LocatorPoint(lpTopLeft,&topLeft);
   topLeft->Move(brgOffset-endDist,0);
   position->put_LocatorPoint(lpTopLeft,topLeft);

   shape->QueryInterface(ppShape);

   return S_OK;
}

STDMETHODIMP CThickenedFlangeBulbTeeSegment::put_Orientation(Float64 orientation)
{
   m_Orientation = orientation;
   return S_OK;
}

STDMETHODIMP CThickenedFlangeBulbTeeSegment::get_Orientation(Float64* orientation)
{
   CHECK_RETVAL(orientation);
   (*orientation) = m_Orientation;
   return S_OK;
}

STDMETHODIMP CThickenedFlangeBulbTeeSegment::GetHaunchDepth(Float64* pStartVal,Float64* pMidVal,Float64* pEndVal)
{
   CHECK_RETVAL(pStartVal);
   CHECK_RETVAL(pMidVal);
   CHECK_RETVAL(pEndVal);
   *pStartVal = m_HaunchDepth[0];
   *pMidVal   = m_HaunchDepth[1];
   *pEndVal   = m_HaunchDepth[2];
   return S_OK;
}

STDMETHODIMP CThickenedFlangeBulbTeeSegment::SetHaunchDepth(Float64 startVal,Float64 midVal,Float64 endVal)
{
   m_HaunchDepth[0] = startVal;
   m_HaunchDepth[1] = midVal;
   m_HaunchDepth[2] = endVal;
   return S_OK;
}

STDMETHODIMP CThickenedFlangeBulbTeeSegment::ComputeHaunchDepth(Float64 distAlongSegment,Float64* pVal)
{
   CHECK_RETVAL(pVal);
   *pVal = ::GB_GetHaunchDepth(this,distAlongSegment);
   return S_OK;
}

STDMETHODIMP CThickenedFlangeBulbTeeSegment::put_Fillet(Float64 Fillet)
{
   m_Fillet = Fillet;
   return S_OK;
}

STDMETHODIMP CThickenedFlangeBulbTeeSegment::get_Fillet(Float64* Fillet)
{
   CHECK_RETVAL(Fillet);
   (*Fillet) = m_Fillet;
   return S_OK;
}

////////////////////////////////////////////////////////////////////
// IThickenedFlangeBulbTeeSegment implementation
STDMETHODIMP CThickenedFlangeBulbTeeSegment::put_FlangeThickening(Float64 flangeThickening)
{
   m_FlangeThickening = flangeThickening;
   return S_OK;
}

STDMETHODIMP CThickenedFlangeBulbTeeSegment::AddShape(IShape* pShape,IMaterial* pFGMaterial,IMaterial* pBGMaterial)
{
   CHECK_IN(pShape);

   if ( m_Shapes.size() == 0 )
   {
      CComQIPtr<IBulbTeeSection> beam(pShape);
      if ( beam == nullptr )
      {
         ATLASSERT(false); // first shape must be a flanged girder section
         return E_INVALIDARG;
      }
   }

   ShapeData shapeData;
   shapeData.Shape = pShape;
   shapeData.FGMaterial = pFGMaterial;
   shapeData.BGMaterial = pBGMaterial;

   m_Shapes.push_back(shapeData);

   return S_OK;
}

STDMETHODIMP CThickenedFlangeBulbTeeSegment::get_ShapeCount(IndexType* nShapes)
{
   CHECK_RETVAL(nShapes);
   *nShapes = m_Shapes.size();
   return S_OK;
}

STDMETHODIMP CThickenedFlangeBulbTeeSegment::get_ForegroundMaterial(IndexType index,IMaterial* *material)
{
   if ( m_Shapes.size() <= index || index == INVALID_INDEX )
   {
      return E_INVALIDARG;
   }

   CHECK_RETVAL(material);
   (*material) = m_Shapes[index].FGMaterial;

   if ( *material )
   {
      (*material)->AddRef();
   }

   return S_OK;
}

STDMETHODIMP CThickenedFlangeBulbTeeSegment::get_BackgroundMaterial(IndexType index,IMaterial* *material)
{
   if ( m_Shapes.size() <= index || index == INVALID_INDEX )
   {
      return E_INVALIDARG;
   }

   CHECK_RETVAL(material);
   (*material) = m_Shapes[index].BGMaterial;

   if ( *material )
   {
      (*material)->AddRef();
   }

   return S_OK;
}

////////////////////////////////////////////////////////////////////
// IItemData implementation
STDMETHODIMP CThickenedFlangeBulbTeeSegment::AddItemData(BSTR name,IUnknown* data)
{
   return m_ItemDataMgr.AddItemData(name,data);
}

STDMETHODIMP CThickenedFlangeBulbTeeSegment::GetItemData(BSTR name,IUnknown** data)
{
   return m_ItemDataMgr.GetItemData(name,data);
}

STDMETHODIMP CThickenedFlangeBulbTeeSegment::RemoveItemData(BSTR name)
{
   return m_ItemDataMgr.RemoveItemData(name);
}

STDMETHODIMP CThickenedFlangeBulbTeeSegment::GetItemDataCount(CollectionIndexType* count)
{
   return m_ItemDataMgr.GetItemDataCount(count);
}

////////////////////////////////////////////////////////////////////
// IStructuredStorage2 implementation
STDMETHODIMP CThickenedFlangeBulbTeeSegment::Load(IStructuredLoad2* load)
{
   return E_NOTIMPL;
   //CComVariant var;
   //load->BeginUnit(CComBSTR("Segment"));

   //load->get_Property(CComBSTR("Length"),&var);
   //m_Length = var.dblVal;

   //m_Shape.Release();
   //load->get_Property(CComBSTR("Shape"),&var);
   //if ( var.vt == VT_UNKNOWN )
   //   var.punkVal->QueryInterface(&m_Shape);

   //VARIANT_BOOL bEnd;
   //load->EndUnit(&bEnd);
   //return S_OK;
}

STDMETHODIMP CThickenedFlangeBulbTeeSegment::Save(IStructuredSave2* save)
{
   return E_NOTIMPL;
   //save->BeginUnit(CComBSTR("Segment"),1.0);

   //save->put_Property(CComBSTR("Length"),CComVariant(m_Length));
   //if ( m_Shape )
   //   save->put_Property(CComBSTR("Shape"),CComVariant(m_Shape));
   //else
   //   save->put_Property(CComBSTR("Shape"),CComVariant(0));

   //save->EndUnit();
   //return S_OK;
}


Float64 CThickenedFlangeBulbTeeSegment::GetFlangeThickening(Float64 distAlongSegment)
{
   // parabolic interpolation of the depth of the top flange thickening
   Float64 segLength;
   get_Length(&segLength);

   Float64 thickening = 4*m_FlangeThickening*distAlongSegment*distAlongSegment/(segLength*segLength) - 4*m_FlangeThickening*distAlongSegment/segLength + m_FlangeThickening;
   return thickening;
}
