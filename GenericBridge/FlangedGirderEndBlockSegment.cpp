///////////////////////////////////////////////////////////////////////
// GenericBridge - Generic Bridge Modeling Framework
// Copyright © 1999-2023  Washington State Department of Transportation
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

// FlangedGirderEndBlockSegment.cpp : Implementation of CFlangedGirderEndBlockSegment
#include "stdafx.h"
#include "WBFLGenericBridge.h"
#include "FlangedGirderEndBlockSegment.h"
#include <MathEx.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFlangedGirderEndBlockSegment
HRESULT CFlangedGirderEndBlockSegment::FinalConstruct()
{
   m_EndBlockLength[etStart]           = 0;
   m_EndBlockLength[etEnd]             = 0;
   m_EndBlockTransitionLength[etStart] = 0;
   m_EndBlockTransitionLength[etEnd]   = 0;
   m_EndBlockWidth[etStart]            = 0;
   m_EndBlockWidth[etEnd]              = 0;

   return S_OK;
}

void CFlangedGirderEndBlockSegment::FinalRelease()
{
   m_Shapes.clear();
}

STDMETHODIMP CFlangedGirderEndBlockSegment::InterfaceSupportsErrorInfo(REFIID riid)
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
// ISuperstructureMemberSegment implementation
STDMETHODIMP CFlangedGirderEndBlockSegment::get_Section(StageIndexType stageIdx,Float64 Xs, SectionBias sectionBias, SectionCoordinateSystemType coordinateSystem,ISection** ppSection)
{
   CHECK_RETOBJ(ppSection);

   if (m_Shapes.size() == 0 )
   {
      *ppSection = 0;
      return S_OK;
   }

   CComPtr<IShape> primaryShape;
   HRESULT hr = get_PrimaryShape(Xs,sectionBias,coordinateSystem,&primaryShape);
   ATLASSERT(SUCCEEDED(hr));
   if ( FAILED(hr) )
      return hr;


   // create our section object
   CComPtr<ICompositeSectionEx> section;
   section.CoCreateInstance(CLSID_CompositeSectionEx);

   section->QueryInterface(IID_ISection,(void**)ppSection);
   ATLASSERT(*ppSection != nullptr);

   // add the primary shape
   Float64 Efg = 0;
   m_Shapes.front().FGMaterial->get_E(stageIdx,&Efg);
   
   Float64 Ebg = 0;
   if (m_Shapes.front().BGMaterial)
   {
      m_Shapes.front().BGMaterial->get_E(stageIdx, &Ebg);
   }

   Float64 Dfg = 0;
   m_Shapes.front().FGMaterial->get_Density(stageIdx,&Dfg);
   
   Float64 Dbg = 0;
   if (m_Shapes.front().BGMaterial)
   {
      m_Shapes.front().BGMaterial->get_Density(stageIdx, &Dbg);
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
      if (shapeData.FGMaterial)
      {
         shapeData.FGMaterial->get_E(stageIdx, &Efg);
      }

      Float64 Ebg;
      if (shapeData.BGMaterial)
      {
         shapeData.BGMaterial->get_E(stageIdx, &Ebg);
      }

      Float64 Dfg = 0;
      if (shapeData.FGMaterial)
      {
         shapeData.FGMaterial->get_Density(stageIdx, &Dfg);
      }

      Float64 Dbg = 0;
      if (shapeData.BGMaterial)
      {
         shapeData.BGMaterial->get_Density(stageIdx, &Dbg);
      }

      CComPtr<IShape> shape;
      shapeData.Shape->Clone(&shape);

      section->AddSection(shape,Efg,Ebg,Dfg,Dbg,VARIANT_TRUE);
   }

   return S_OK;
}


STDMETHODIMP CFlangedGirderEndBlockSegment::get_PrimaryShape(Float64 Xs, SectionBias sectionBias, SectionCoordinateSystemType coordinateSystem, IShape** ppShape)
{
   CHECK_RETOBJ(ppShape);

   if (m_Shapes.size() == 0 )
   {
      *ppShape = 0;
      return S_OK;
   }

   CComPtr<IShape> newShape;

   // check for cached shapes
   int zone = GetSectionZone(Xs, sectionBias);
   if (zone == START_ENDBLOCK_ZONE && m_EndBlockShape[etStart])
   {
      m_EndBlockShape[etStart]->Clone(&newShape);
   }
   else if (zone == END_ENDBLOCK_ZONE && m_EndBlockShape[etEnd])
   {
      m_EndBlockShape[etEnd]->Clone(&newShape);
   }
   else if (zone == PRIMARY_ZONE && m_PrimaryShape)
   {
      m_PrimaryShape->Clone(&newShape);
   }
   else if(zone == START_TRANSITION_ZONE || zone == END_TRANSITION_ZONE)
   {
      EndType endType = (zone == START_TRANSITION_ZONE ? etStart : etEnd);
      auto found = m_TransitionShape[endType].find(Xs);
      if (found != m_TransitionShape[endType].end())
      {
         found->second->Clone(&newShape);
      }
   }

   if (newShape == nullptr)
   {
      CComQIPtr<IFlangedEndBlockSection> flanged_end_block_section(m_Shapes.front().Shape);
      ATLASSERT(flanged_end_block_section); // if this is nullptr... how did it get in the system????

      Float64 Wt, Wb;
      GetEndBlockWidth(Xs, sectionBias, &Wt, &Wb);
      CComPtr<IFlangedEndBlockSection> end_block_section;
      flanged_end_block_section->CreateEndBlockSection(Wt, Wb, &end_block_section);

      // position shape in girder coordiantes
      CComPtr<IPoint2d> pnt;
      pnt.CoCreateInstance(CLSID_Point2d);
      pnt->Move(0, 0);
      CComQIPtr<IXYPosition> position(end_block_section);
      position->put_LocatorPoint(lpTopCenter, pnt);

      // save a copy of the end block shape so we don't have to create it every time it is requested
      end_block_section.QueryInterface(&newShape);
      if (zone == START_ENDBLOCK_ZONE)
      {
         newShape->Clone(&m_EndBlockShape[etStart]);
      }
      else if (zone == END_ENDBLOCK_ZONE)
      {
         newShape->Clone(&m_EndBlockShape[etEnd]);
      }
      else if (zone == PRIMARY_ZONE)
      {
         newShape->Clone(&m_PrimaryShape);
      }
      else
      {
         ATLASSERT(zone == START_TRANSITION_ZONE || zone == END_TRANSITION_ZONE);
         EndType endType = (zone == START_TRANSITION_ZONE ? etStart : etEnd);
         CComPtr<IShape> transShape;
         newShape->Clone(&transShape);
         m_TransitionShape[endType].emplace_hint(m_TransitionShape[endType].end(), Xs, transShape);
      }
   }


   if (coordinateSystem == cstBridge)
   {
      // position the shape bridge coordinates
      CComPtr<IPoint2d> pntTopCenter;
      GB_GetSectionLocation(this, Xs, &pntTopCenter);

      CComQIPtr<IXYPosition> position(newShape);
      position->put_LocatorPoint(lpTopCenter, pntTopCenter);
   }

   *ppShape = newShape;
   (*ppShape)->AddRef();
   return S_OK;
}

STDMETHODIMP CFlangedGirderEndBlockSegment::GetVolumeAndSurfaceArea(Float64* pVolume, Float64* pSurfaceArea)
{
   CHECK_RETVAL(pVolume);
   CHECK_RETVAL(pSurfaceArea);

   if (m_bUpdateVolumeAndSurfaceArea)
   {
      if (m_Shapes.size() == 0)
      {
         m_Volume = 0;
         m_SurfaceArea = 0;
      }
      else
      {
         Float64 L;
         get_Length(&L);
         std::vector<std::pair<Float64, SectionBias>> vCuts;

         vCuts.emplace_back(0.0, sbRight); // start of beam

         // left end block
         if (!IsZero(m_EndBlockLength[etStart]))
         {
            vCuts.emplace_back(m_EndBlockLength[etStart], sbLeft);
         }

         // left end block transition
         if (IsZero(m_EndBlockTransitionLength[etStart]) && !IsZero(m_EndBlockLength[etStart]))
         {
            // this is an end block, but no transition so there is an abrupt change in section
            vCuts.emplace_back(m_EndBlockLength[etStart] + m_EndBlockTransitionLength[etStart], sbLeft);
            vCuts.emplace_back(m_EndBlockLength[etStart] + m_EndBlockTransitionLength[etStart], sbRight);
         }
         else if (!IsZero(m_EndBlockTransitionLength[etStart]))
         {
            // there is a smooth transition
            vCuts.emplace_back(m_EndBlockLength[etStart] + m_EndBlockTransitionLength[etStart], sbLeft);
         }


         // right end block transition
         if (IsZero(m_EndBlockTransitionLength[etEnd]) && !IsZero(m_EndBlockLength[etEnd]))
         {
            // this is an end block, but no transition so there is an abrupt change in section
            vCuts.emplace_back(L - (m_EndBlockLength[etEnd] + m_EndBlockTransitionLength[etEnd]), sbRight);
            vCuts.emplace_back(L - (m_EndBlockLength[etEnd] + m_EndBlockTransitionLength[etEnd]), sbLeft);
         }
         else if (!IsZero(m_EndBlockTransitionLength[etEnd]))
         {
            // there is a smooth transition
            vCuts.emplace_back(L - (m_EndBlockLength[etEnd] + m_EndBlockTransitionLength[etEnd]), sbLeft);
         }

         // right end block
         if (!IsZero(m_EndBlockLength[etEnd]))
         {
            vCuts.emplace_back(L - m_EndBlockLength[etEnd], sbLeft);
         }

         // end of beam
         vCuts.emplace_back(L, sbLeft);

         auto iter(vCuts.begin());
         CComPtr<IShape> shape;
         get_PrimaryShape(iter->first, iter->second, cstGirder, &shape);
         Float64 prev_perimeter;
         shape->get_Perimeter(&prev_perimeter);
         CComPtr<IShapeProperties> shapeProps;
         shape->get_ShapeProperties(&shapeProps);
         Float64 start_area;
         shapeProps->get_Area(&start_area);
         Float64 prev_area = start_area;

         Float64 prevX = iter->first;

         Float64 V = 0;
         Float64 S = 0;

         iter++;
         auto end(vCuts.end());
         for (; iter != end; iter++)
         {
            Float64 X = iter->first;
            SectionBias bias = iter->second;

            shape.Release();
            get_PrimaryShape(X, bias, cstGirder, &shape);
            Float64 perimeter;
            shape->get_Perimeter(&perimeter);

            shapeProps.Release();
            shape->get_ShapeProperties(&shapeProps);
            Float64 area;
            shapeProps->get_Area(&area);

            Float64 dx = X - prevX;

            Float64 avg_perimeter = (prev_perimeter + perimeter)/* / 2*/; // save the divide by 2 for outside the loop
            Float64 avg_area = (prev_area + area) /* / 2*/; // save the divide by 2 for outside the loop

            S += avg_perimeter*dx;
            V += avg_area*dx;

            prev_perimeter = perimeter;
            prev_area = area;
            prevX = X;
         }

         // divide by 2 now
         S /= 2;
         V /= 2;

         Float64 end_area;
         shapeProps->get_Area(&end_area);
         S += start_area + end_area;

         m_Volume = V;
         m_SurfaceArea = S;
      }

      m_bUpdateVolumeAndSurfaceArea = false;
   }

   *pVolume = m_Volume;
   *pSurfaceArea = m_SurfaceArea;
   return S_OK;
}

STDMETHODIMP CFlangedGirderEndBlockSegment::get_InternalSurfaceAreaOfVoids(Float64* pSurfaceArea)
{
   CHECK_RETVAL(pSurfaceArea);
   *pSurfaceArea = 0;
   return S_OK;
}

STDMETHODIMP CFlangedGirderEndBlockSegment::get_Profile(VARIANT_BOOL bIncludeClosure,IShape** ppShape)
{
   CHECK_RETOBJ(ppShape);
   CComPtr<IRect2d> rect;

   // it is assumed that the first shape is the main shape in the section and all
   // other shapes are inside of it
   m_Shapes[0].Shape->get_BoundingBox(&rect);

   Float64 h;
   rect->get_Height(&h);

   Float64 l;
   Float64 brgOffset, endDist;
   if (bIncludeClosure == VARIANT_TRUE)
   {
      m_Impl.m_pGirderLine->get_LayoutLength(&l);
      brgOffset = 0;
      endDist = 0;
   }
   else
   {
      m_Impl.m_pGirderLine->get_GirderLength(&l);
      m_Impl.m_pGirderLine->get_BearingOffset(etStart, &brgOffset);
      m_Impl.m_pGirderLine->get_EndDistance(etStart, &endDist);
   }

   CComPtr<IShape> shape;
   if (IsZero(m_Impl.m_Precamber))
   {
      CComPtr<IRectangle> profile;
      profile.CoCreateInstance(CLSID_Rect);
      profile->put_Height(h);
      profile->put_Width(l);

      profile.QueryInterface(&shape);
   }
   else
   {
      CComPtr<IPolyShape> profile;
      profile.CoCreateInstance(CLSID_PolyShape);
      profile->AddPoint(0, 0);

      Float64 Ls;
      m_Impl.m_pGirderLine->get_GirderLength(&Ls);
      for (int i = 0; i < 11; i++)
      {
         Float64 x = i*Ls / 10;
         Float64 y = m_Impl.ComputePrecamber(x,Ls);
         if (bIncludeClosure == VARIANT_TRUE)
         {
            x += (brgOffset - endDist);
         }
         profile->AddPoint(x, y);
      }

      profile->AddPoint(l, 0);

      for (int i = 0; i < 11; i++)
      {
         Float64 x = Ls - i*Ls / 10;
         Float64 y = m_Impl.ComputePrecamber(x,Ls) + h;
         if (bIncludeClosure == VARIANT_TRUE)
         {
            x += (brgOffset - endDist);
         }
         profile->AddPoint(x, y);
      }

      profile->AddPoint(0, h);

      profile.QueryInterface(&shape);
   }

   // CL Pier/Top Shape is at (0,0)
   //
   // CL Pier   End of segment
   // |         |       CL Bearing
   // | (0,0)   |       |
   // *         +-------+---------------\  
   // |         |       .               /
   // |         +-------+---------------\  
   //
   //          Elevation View

   CComQIPtr<IXYPosition> position(shape);
   CComPtr<IPoint2d> topLeft;
   position->get_LocatorPoint(lpTopLeft,&topLeft);
   if (0 < m_Impl.m_Precamber)
   {
      topLeft->Move(brgOffset - endDist, m_Impl.m_Precamber);
   }
   else
   {
      topLeft->Move(brgOffset - endDist, 0);
   }
   position->put_LocatorPoint(lpTopLeft,topLeft);

   shape->QueryInterface(ppShape);

   return S_OK;
}

////////////////////////////////////////////////////////////////////
// IFlangedGirderEndBlockSegment implementation

STDMETHODIMP CFlangedGirderEndBlockSegment::AddShape(IShape* pShape,IMaterial* pFGMaterial,IMaterial* pBGMaterial)
{
   CHECK_IN(pShape);

   if ( m_Shapes.size() == 0 )
   {
      CComQIPtr<IFlangedEndBlockSection> flanged_end_block_section(pShape);
      if (flanged_end_block_section == nullptr )
      {
         ATLASSERT(false); // first shape to be added must support the IFlangedEndBlockSection interface
         return E_INVALIDARG;
      }
   }

   ShapeData shapeData;
   shapeData.Shape = pShape;
   shapeData.FGMaterial = pFGMaterial;
   shapeData.BGMaterial = pBGMaterial;

   m_Shapes.push_back(shapeData);

   m_bUpdateVolumeAndSurfaceArea = true;
   m_Volume = -1;
   m_SurfaceArea = -1;

   m_EndBlockShape[etStart].Release();
   m_EndBlockShape[etEnd].Release();
   m_PrimaryShape.Release();
   m_TransitionShape[etStart].clear();
   m_TransitionShape[etEnd].clear();

   return S_OK;
}

STDMETHODIMP CFlangedGirderEndBlockSegment::get_ShapeCount(IndexType* nShapes)
{
   CHECK_RETVAL(nShapes);
   *nShapes = m_Shapes.size();
   return S_OK;
}

STDMETHODIMP CFlangedGirderEndBlockSegment::get_ForegroundMaterial(IndexType index,IMaterial* *material)
{
   if ( m_Shapes.size() <= index || index == INVALID_INDEX )
      return E_INVALIDARG;

   CHECK_RETVAL(material);
   (*material) = m_Shapes[index].FGMaterial;

   if ( *material )
      (*material)->AddRef();

   return S_OK;
}

STDMETHODIMP CFlangedGirderEndBlockSegment::get_BackgroundMaterial(IndexType index,IMaterial* *material)
{
   if ( m_Shapes.size() <= index || index == INVALID_INDEX )
      return E_INVALIDARG;

   CHECK_RETVAL(material);
   (*material) = m_Shapes[index].BGMaterial;

   if ( *material )
      (*material)->AddRef();

   return S_OK;
}

STDMETHODIMP CFlangedGirderEndBlockSegment::put_EndBlockLength(/*[in]*/EndType endType,/*[in]*/ Float64 length)
{
   m_EndBlockLength[endType] = length;
   return S_OK;
}

STDMETHODIMP CFlangedGirderEndBlockSegment::get_EndBlockLength(/*[in]*/EndType endType,/*[out,retval]*/ Float64* pLength)
{
   *pLength = m_EndBlockLength[endType];
   return S_OK;
}

STDMETHODIMP CFlangedGirderEndBlockSegment::put_EndBlockTransitionLength(/*[in]*/EndType endType,/*[in]*/ Float64 length)
{
   m_EndBlockTransitionLength[endType] = length;
   return S_OK;
}

STDMETHODIMP CFlangedGirderEndBlockSegment::get_EndBlockTransitionLength(/*[in]*/EndType endType,/*[out,retval]*/ Float64* pLength)
{
   *pLength = m_EndBlockTransitionLength[endType];
   return S_OK;
}

STDMETHODIMP CFlangedGirderEndBlockSegment::put_EndBlockWidth(/*[in]*/EndType endType,/*[in]*/ Float64 width)
{
   m_EndBlockWidth[endType] = width;
   return S_OK;
}

STDMETHODIMP CFlangedGirderEndBlockSegment::get_EndBlockWidth(/*[in]*/EndType endType,/*[out,retval]*/ Float64* pWidth)
{
   *pWidth = m_EndBlockWidth[endType];
   return S_OK;
}

////////////////////////////////////////////////////////////////////
// IItemData implementation
STDMETHODIMP CFlangedGirderEndBlockSegment::AddItemData(BSTR name,IUnknown* data)
{
   return m_ItemDataMgr.AddItemData(name,data);
}

STDMETHODIMP CFlangedGirderEndBlockSegment::GetItemData(BSTR name,IUnknown** data)
{
   return m_ItemDataMgr.GetItemData(name,data);
}

STDMETHODIMP CFlangedGirderEndBlockSegment::RemoveItemData(BSTR name)
{
   return m_ItemDataMgr.RemoveItemData(name);
}

STDMETHODIMP CFlangedGirderEndBlockSegment::GetItemDataCount(CollectionIndexType* count)
{
   return m_ItemDataMgr.GetItemDataCount(count);
}

////////////////////////////////////////////////////////////////////
// IStructuredStorage2 implementation
STDMETHODIMP CFlangedGirderEndBlockSegment::Load(IStructuredLoad2* load)
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

STDMETHODIMP CFlangedGirderEndBlockSegment::Save(IStructuredSave2* save)
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

int CFlangedGirderEndBlockSegment::GetSectionZone(Float64 Xs, SectionBias sectionBias)
{
   Float64 segLength;
   get_Length(&segLength);

   // the end blocks for this girder type of a smooth transitions
   // so sectionBias doesn't have any impact

   EndType endType;
   if (Xs < segLength / 2)
   {
      // at the start end...
      endType = etStart;
   }
   else
   {
      endType = etEnd;
      Xs = segLength - Xs; // Xs is now measured from the left end
   }

   Float64 ebWidth = m_EndBlockWidth[endType];
   Float64 ebLength = m_EndBlockLength[endType];
   Float64 ebTransLength = m_EndBlockTransitionLength[endType];

   if (Xs < ebLength)
   {
      // in the end block
      return endType == etStart ? START_ENDBLOCK_ZONE : END_ENDBLOCK_ZONE;
   }
   else if (IsEqual(Xs, ebLength) && IsZero(ebTransLength))
   {
      // we are at the interface between the full end block and the transition
      // and the transition length is zero... this means there is an abrupt section change
      if ((endType == etStart && sectionBias == sbLeft) || (endType == etEnd && sectionBias == sbRight))
      {
         // in the end block
         return endType == etStart ? START_ENDBLOCK_ZONE : END_ENDBLOCK_ZONE;
      }
      else
      {
         ATLASSERT((endType == etStart && sectionBias == sbRight) || (endType == etEnd && sectionBias == sbLeft));
         // after the end block
         return PRIMARY_ZONE;
      }
   }
   else if (::InRange(ebLength, Xs, ebLength + ebTransLength))
   {
      // in the end block transition
      return endType == etStart ? START_TRANSITION_ZONE : END_TRANSITION_ZONE;
   }
   else
   {
      // after the end block
      return PRIMARY_ZONE;
   }
   ATLASSERT(false); // should never get here
}

void CFlangedGirderEndBlockSegment::GetEndBlockWidth(Float64 Xs, SectionBias sectionBias,Float64* pWtop,Float64* pWbot)
{
   Float64 segLength;
   get_Length(&segLength);

   CComQIPtr<IFlangedEndBlockSection> flanged_end_block_section(m_Shapes.front().Shape);
   ATLASSERT(flanged_end_block_section); // if this is nullptr... how did it get in the system????

   // the end blocks for this girder type of a smooth transitions
   // so sectionBias doesn't have any impact

   EndType endType;
   if ( Xs < segLength/2 )
   {
      // at the start end...
      endType = etStart;
   }
   else
   {
      endType = etEnd;
      Xs = segLength - Xs; // Xs is now measured from the left end
   }

   Float64 ebWidth       = m_EndBlockWidth[endType];
   Float64 ebLength      = m_EndBlockLength[endType];
   Float64 ebTransLength = m_EndBlockTransitionLength[endType];

   if ( Xs < ebLength )
   {
      // in the end block
      *pWtop = ebWidth;
      *pWbot = ebWidth;
   }
   else if (IsEqual(Xs, ebLength) && IsZero(ebTransLength))
   {
      // we are at the interface between the full end block and the transition
      // and the transition length is zero... this means there is an abrupt section change
      if ((endType == etStart && sectionBias == sbLeft) || (endType == etEnd && sectionBias == sbRight))
      {
         // in the end block
         *pWtop = ebWidth;
         *pWbot = ebWidth;
      }
      else
      {
         ATLASSERT((endType == etStart && sectionBias == sbRight) || (endType == etEnd && sectionBias == sbLeft));
         // after the end block
         Float64 t1, t2;
         flanged_end_block_section->GetWebWidth(&t1, &t2);
         *pWtop = t1;
         *pWbot = t2;
      }
   }
   else if ( ::InRange(ebLength,Xs,ebLength+ebTransLength) )
   {
      // in the end block transition
      Float64 t1, t2;
      flanged_end_block_section->GetWebWidth(&t1, &t2);
      *pWtop = ::LinInterp(Xs-ebLength,ebWidth,t1,ebTransLength);
      *pWbot = ::LinInterp(Xs-ebLength,ebWidth,t2,ebTransLength);
   }
   else
   {
      // after the end block
      Float64 t1, t2;
      flanged_end_block_section->GetWebWidth(&t1, &t2);
      *pWtop = t1;
      *pWbot = t2;
   }
}
