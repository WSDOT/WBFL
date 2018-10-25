///////////////////////////////////////////////////////////////////////
// BridgeGeometry
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

// UniformSpacingLayoutLineFactory.cpp : Implementation of CUniformSpacingLayoutLineFactory

#include "stdafx.h"
#include "UniformSpacingLayoutLineFactory.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



// CUniformSpacingLayoutLineFactory
STDMETHODIMP CUniformSpacingLayoutLineFactory::Create(IBridgeGeometry* pBridge,IPathCollection* pPaths)
{
   CHECK_IN(pBridge);
   CHECK_IN(pPaths);

   if ( m_LayoutLineID == INVALID_ID )
   {
      ATLASSERT(false);
      return E_INVALIDARG;
   }

   CComPtr<IAlignment> alignment;
   if ( FAILED(pBridge->get_Alignment(m_AlignmentID,&alignment)) )
      return Error(IDS_E_ID,IID_IUniformSpacingLayoutLineFactory,BRIDGEGEOMETRY_E_ID);


   // The pier geometry must be computed to create the layout lines
   // Update the bridge geometry now
   if ( FAILED(pBridge->UpdateGeometry()) )
      return E_FAIL;


   CollectionIndexType nStartSpaces, nEndSpaces;
   m_StartSpacing->get_Count(&nStartSpaces);
   m_EndSpacing->get_Count(&nEndSpaces);
   if ( nStartSpaces != nEndSpaces )
      return E_INVALIDARG;

   // Do the work here... piers must already be defined in bridge

   CComPtr<ICogoModel> cogoModel;
   pBridge->get_CogoModel(&cogoModel);
   CComPtr<ICogoEngine> cogoEngine;
   cogoModel->get_Engine(&cogoEngine);

   CComPtr<ILocate2> locate;
   cogoEngine->get_Locate(&locate);

   // Work between piers
   for ( PierIDType pierID = m_StartPierID; pierID < m_EndPierID; pierID += m_PierIDInc )
   {
      // Get Pier Lines
      PierIDType nextPierID = pierID + m_PierIDInc;
      CComPtr<IPierLine> prevPierLine, nextPierLine;
      if ( FAILED(pBridge->FindPierLine(pierID,&prevPierLine)) )
         return Error(IDS_E_ID,IID_IUniformSpacingLayoutLineFactory,BRIDGEGEOMETRY_E_ID);

      if ( FAILED(pBridge->FindPierLine(nextPierID,&nextPierLine)) )
         return Error(IDS_E_ID,IID_IUniformSpacingLayoutLineFactory,BRIDGEGEOMETRY_E_ID);

      CComPtr<IDirection> prevDirection, nextDirection;
      GetDirection(prevPierLine,&prevDirection);
      GetDirection(nextPierLine,&nextDirection);

      // Intersect alignment with pier lines
      CComPtr<IPoint2d> pntAlignmentStart, pntAlignmentEnd;
      PierAlignmentIntersect(prevPierLine,alignment,&pntAlignmentStart);
      PierAlignmentIntersect(nextPierLine,alignment,&pntAlignmentEnd);

      // Locate Start and End point of layout lines
      CComPtr<IPoint2d> pntStart, pntEnd;
      locate->ByDistDir(pntAlignmentStart,m_StartOffset,CComVariant(prevDirection),0.0,&pntStart);
      locate->ByDistDir(pntAlignmentEnd,  m_EndOffset,  CComVariant(nextDirection),0.0,&pntEnd);

      // Create first layout line
      CComPtr<ILineSegment2d> layoutLine;
      layoutLine.CoCreateInstance(CLSID_LineSegment2d);
      layoutLine->ThroughPoints(pntStart,pntEnd);
      CComPtr<IPath> path;
      path.CoCreateInstance(CLSID_Path);
      path->AddEx(layoutLine);
      pPaths->AddEx(m_LayoutLineID,path);

      m_LayoutLineID += m_LayoutLineIDInc;

      layoutLine.Release();
      path.Release();
      pntStart.Release();
      pntEnd.Release();

      // Loop over spaces and create the other layout lines
      Float64 startOffset = m_StartOffset;
      Float64 endOffset   = m_EndOffset;
      for ( CollectionIndexType spaceIdx = 0; spaceIdx < nStartSpaces; spaceIdx++ )
      {
         Float64 startSpacing, endSpacing;
         m_StartSpacing->get_Item(spaceIdx,&startSpacing);
         m_EndSpacing->get_Item(spaceIdx,&endSpacing);
      
         startOffset -= startSpacing;
         endOffset   -= endSpacing;

         locate->ByDistDir(pntAlignmentStart,startOffset,CComVariant(prevDirection),0.0,&pntStart);
         locate->ByDistDir(pntAlignmentEnd,  endOffset,  CComVariant(nextDirection),0.0,&pntEnd);

         layoutLine.CoCreateInstance(CLSID_LineSegment2d);
         layoutLine->ThroughPoints(pntStart,pntEnd);
         path.CoCreateInstance(CLSID_Path);
         path->AddEx(layoutLine);
         pPaths->AddEx(m_LayoutLineID,path);

         m_LayoutLineID += m_LayoutLineIDInc;

         layoutLine.Release();
         path.Release();
         pntStart.Release();
         pntEnd.Release();
      }
   }

   return S_OK;
}

STDMETHODIMP CUniformSpacingLayoutLineFactory::Reset()
{
   m_AlignmentID = INVALID_ID;
   m_StartPierID = INVALID_ID;
   m_EndPierID   = INVALID_ID;
   m_PierIDInc   = 1;
   m_StartOffset = 0;
   m_EndOffset   = 0;
   m_LayoutLineID = INVALID_ID;
   m_LayoutLineIDInc = 1;

   return S_OK;
}


STDMETHODIMP CUniformSpacingLayoutLineFactory::get_AlignmentID(CogoObjectID* ID)
{
   CHECK_RETVAL(ID);
   *ID = m_AlignmentID;
   return S_OK;
}

STDMETHODIMP CUniformSpacingLayoutLineFactory::put_AlignmentID(CogoObjectID ID)
{
   m_AlignmentID = ID;
   return S_OK;
}

STDMETHODIMP CUniformSpacingLayoutLineFactory::get_StartPierID(PierIDType* pVal)
{
   CHECK_RETVAL(pVal);
   *pVal = m_StartPierID;
   return S_OK;
}

STDMETHODIMP CUniformSpacingLayoutLineFactory::put_StartPierID(PierIDType newVal)
{
   m_StartPierID = newVal;
   return S_OK;
}

STDMETHODIMP CUniformSpacingLayoutLineFactory::get_EndPierID(PierIDType* pVal)
{
   CHECK_RETVAL(pVal);
   *pVal = m_EndPierID;
   return S_OK;
}

STDMETHODIMP CUniformSpacingLayoutLineFactory::put_EndPierID(PierIDType newVal)
{
   m_EndPierID = newVal;
   return S_OK;
}

STDMETHODIMP CUniformSpacingLayoutLineFactory::get_PierIDInc(PierIDType* pVal)
{
   CHECK_RETVAL(pVal);
   *pVal = m_PierIDInc;
   return S_OK;
}

STDMETHODIMP CUniformSpacingLayoutLineFactory::put_PierIDInc(PierIDType newVal)
{
   m_PierIDInc = newVal;
   return S_OK;
}

STDMETHODIMP CUniformSpacingLayoutLineFactory::get_StartSpacingOffset(Float64* pVal)
{
   CHECK_RETVAL(pVal);
   *pVal = m_StartOffset;
   return S_OK;
}

STDMETHODIMP CUniformSpacingLayoutLineFactory::put_StartSpacingOffset(Float64 newVal)
{
   m_StartOffset = newVal;
   return S_OK;
}

STDMETHODIMP CUniformSpacingLayoutLineFactory::get_EndSpacingOffset(Float64* pVal)
{
   CHECK_RETVAL(pVal);
   *pVal = m_EndOffset;
   return S_OK;
}

STDMETHODIMP CUniformSpacingLayoutLineFactory::put_EndSpacingOffset(Float64 newVal)
{
   m_EndOffset = newVal;
   return S_OK;
}

STDMETHODIMP CUniformSpacingLayoutLineFactory::get_StartSpacing(IDblArray** pVal)
{
   CHECK_RETOBJ(pVal);
   m_StartSpacing.CopyTo(pVal);
   return S_OK;
}

STDMETHODIMP CUniformSpacingLayoutLineFactory::put_StartSpacing(IDblArray* newVal)
{
   CHECK_IN(newVal);
   m_StartSpacing = newVal;
   return S_OK;
}

STDMETHODIMP CUniformSpacingLayoutLineFactory::get_EndSpacing(IDblArray** pVal)
{
   CHECK_RETOBJ(pVal);
   m_EndSpacing.CopyTo(pVal);
   return S_OK;
}

STDMETHODIMP CUniformSpacingLayoutLineFactory::put_EndSpacing(IDblArray* newVal)
{
   CHECK_IN(newVal);
   m_EndSpacing = newVal;
   return S_OK;
}

STDMETHODIMP CUniformSpacingLayoutLineFactory::put_LayoutLineID(LineIDType ID)
{
   m_LayoutLineID = ID;
   return S_OK;
}

STDMETHODIMP CUniformSpacingLayoutLineFactory::get_LayoutLineID(LineIDType* ID)
{
   CHECK_RETVAL(ID);
   *ID = m_LayoutLineID;
   return S_OK;
}

STDMETHODIMP CUniformSpacingLayoutLineFactory::put_LayoutLineIDInc(LineIDType inc)
{
   m_LayoutLineIDInc = inc;
   return S_OK;
}

STDMETHODIMP CUniformSpacingLayoutLineFactory::get_LayoutLineIDInc(LineIDType* inc)
{
   CHECK_RETVAL(inc);
   *inc = m_LayoutLineIDInc;
   return S_OK;
}
