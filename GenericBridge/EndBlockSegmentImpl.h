///////////////////////////////////////////////////////////////////////
// GenericBridge - Generic Bridge Modeling Framework
// Copyright © 2009  Washington State Department of Transportation
//                   Bridge and Structures Office
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

// TEndBlockSegmentImpl.h : Declaration of the CSegment

#pragma once

#include "stdafx.h"
#include "resource.h"       // main symbols
#include "GenericBridgeCP.h"
#include "Segments.h"
#include <MathEx.h>
#include "WBFLGenericBridge.h"

/////////////////////////////////////////////////////////////////////////////
// TEndBlockSegmentImpl
//                                                             IDeckedSlabBeam
template<class T_IEndBlockSegment, class T_IBeamSection, class T_IBeam, const CLSID* T_CLSID, long T_IDR> class TEndBlockSegmentImpl : 
	public CComObjectRootEx<CComSingleThreadModel>,
//   public CComRefCountTracer<CSegment,CComObjectRootEx<CComSingleThreadModel> >,
	public CComCoClass< TEndBlockSegmentImpl<T_IEndBlockSegment, T_IBeamSection, T_IBeam, T_CLSID, T_IDR>, T_CLSID>,
	public ISupportErrorInfo,
   public CProxyDSegmentEvents< TEndBlockSegmentImpl<T_IEndBlockSegment, T_IBeamSection, T_IBeam, T_CLSID, T_IDR> >,
   public IConnectionPointContainerImpl<TEndBlockSegmentImpl<T_IEndBlockSegment, T_IBeamSection, T_IBeam, T_CLSID, T_IDR> >,
   public IObjectSafetyImpl<TEndBlockSegmentImpl<T_IEndBlockSegment, T_IBeamSection, T_IBeam, T_CLSID, T_IDR>, INTERFACESAFE_FOR_UNTRUSTED_CALLER | INTERFACESAFE_FOR_UNTRUSTED_DATA>,
   public T_IEndBlockSegment,
   public IMaterialEvents,
   public IStructuredStorage2
{
   friend TEndBlockSegmentImpl; // for easy cloning

private:
   Float64 m_Length;
   CComPtr<T_IBeamSection> m_Beam;
   ISegmentMeasure* m_pSegmentMeasure; // weak reference because it is SuperstructureMember
                                       // that implements this interface. Strong reference
                                       // creates a circular reference situation

   Float64 m_Orientation; // orientation of girder... plumb = 0... rotated CW is +... radians

   CComPtr<IMaterial> m_Material;
   DWORD m_dwMaterialCookie;

   // index is EndType
   Float64 m_EndBlockLength[2]; // length of end block from end of girder to transitation


public:
   TEndBlockSegmentImpl()
	{
      m_pSegmentMeasure = 0;
      m_Orientation = 0;
	}

DECLARE_REGISTRY_RESOURCEID(T_IDR)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(TEndBlockSegmentImpl)
	COM_INTERFACE_ENTRY(T_IEndBlockSegment)
	COM_INTERFACE_ENTRY(ISegment)
   COM_INTERFACE_ENTRY(IMaterialEvents)
	COM_INTERFACE_ENTRY(IStructuredStorage2)
   COM_INTERFACE_ENTRY(ISupportErrorInfo)
   COM_INTERFACE_ENTRY_IMPL(IConnectionPointContainer)
   COM_INTERFACE_ENTRY(IObjectSafety)
END_COM_MAP()

BEGIN_CONNECTION_POINT_MAP(TEndBlockSegmentImpl)
	CONNECTION_POINT_ENTRY(IID_ISegmentEvents)
END_CONNECTION_POINT_MAP()

public:
   HRESULT FinalConstruct()
   {
      m_Length = 1.0;

      m_EndBlockLength[etStart]           = 0;
      m_EndBlockLength[etEnd]             = 0;

      return S_OK;
   }

   void FinalRelease()
   {
      m_Beam.Release();

      if ( m_Material )
      {
         InternalAddRef();

         AtlUnadvise(m_Material,IID_IMaterialEvents,m_dwMaterialCookie);
      }
      m_Material.Release();
   }

// ISupportsErrorInfo
   STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid)
   {
	   static const IID* arr[] = 
	   {
		   &IID_ISegment,
         &IID_IStructuredStorage2,
	   };
	   for (int i=0; i < sizeof(arr) / sizeof(arr[0]); i++)
	   {
		   if (InlineIsEqualGUID(*arr[i],riid))
			   return S_OK;
	   }
	   return S_FALSE;
   }

// ISegment
public:
   STDMETHOD(putref_SegmentMeasure)(ISegmentMeasure* sm)
   {
      m_pSegmentMeasure = sm;

   #if defined _DEBUG
      // m_pSegmentMeasure is a weak references. This is so because
      // I expect the object implementing sm to also be a superstructure member
      // Assert this is true.
      if ( sm != NULL )
      {
         CComQIPtr<ISuperstructureMember> ssmbr(sm);
         CComQIPtr<ILongitudinalPierDescription> lpd(sm);
         CComQIPtr<ICrossBeam> cb(sm);
         CComQIPtr<IColumn> col(sm);
         ATLASSERT(ssmbr != NULL || lpd != NULL || cb != NULL || col != NULL);
      }
   #endif // _DEBUG

      return S_OK;
   }

   STDMETHOD(get_Length)(Float64 *pVal)
   {
      CHECK_RETVAL(pVal);
      (*pVal) = m_Length;
	   return S_OK;
   }

   STDMETHOD(put_Length)(Float64 length)
   {
      if ( IsEqual(m_Length,length) )
         return S_OK;

      // Validate length
      if ( m_pSegmentMeasure )
      {
         bool bFractional = m_pSegmentMeasure->IsFractional() == S_OK ? true : false;
         if ( bFractional )
         {
            if ( length > 0 )
               return Error(IDS_E_FRACTIONAL_EXPECTED,IID_ISegment,GB_E_FRACTIONAL_EXPECTED);
         }
         else
         {
            if ( length < 0 )
               return Error(IDS_E_ABSOLUTE_EXPECTED,IID_ISegment,GB_E_ABSOLUTE_EXPECTED);
         }
      }

      m_Length = length;
      Fire_OnSegmentChanged(this);
      return S_OK;
   }

   STDMETHOD(get_SegmentLength)(/*[out, retval]*/ Float64 *pVal)
   {
      CHECK_RETVAL(pVal);
      if ( m_Length < 0 )
      {
         // segment length is a fraction of the superstructure member length
         Float64 ssmbrLength = GetSuperstructureMemberLength();
         *pVal = -1*m_Length*ssmbrLength;
      }
      else
      {
         // segment lenght is an absolute value
         *pVal = m_Length;
      }
      return S_OK;
   }

   STDMETHOD(get_Shape)(Float64 distAlongSegment,IShape** ppShape)
   {
      CHECK_RETOBJ(ppShape);

      // This object reprsents a prismatic shape... all sections are the same
      HRESULT hr = S_OK;
      if ( m_Beam )
      {
         // create a new shape that is a clone of the original
         CComQIPtr<IShape> shape(m_Beam);
         CComPtr<IShape> newShape;
         hr = shape->Clone(&newShape);

         // set the dimensions
         CComQIPtr<T_IBeamSection> newSection(newShape);
         CComPtr<T_IBeam> newBeam;
         newSection->get_Beam(&newBeam);

         Float64 length;
         get_SegmentLength(&length);

         // Remove void(s) if in block region
         if ( (m_EndBlockLength[etStart]>0.0 && IsLE(distAlongSegment,m_EndBlockLength[etStart])) || 
              (m_EndBlockLength[etEnd]  >0.0 && IsLE(length - distAlongSegment,m_EndBlockLength[etEnd])) )
         {
            newBeam->put_VoidCount(0);
         }

         newSection.QueryInterface(ppShape);
      }
      else
      {
         (*ppShape) = 0;
      }

      return hr;
   }

   STDMETHOD(putref_Material)(IMaterial* material)
   {
      CHECK_IN(material);

      if ( m_Material.IsEqualObject(material) )
         return S_OK;

      CComPtr<IUnknown> punk;
      QueryInterface(IID_IUnknown,(void**)&punk);

      HRESULT hr;
      DWORD dwCookie;
      if ( material )
      {
         hr = AtlAdvise(material,punk,IID_IMaterialEvents,&dwCookie);
         if ( FAILED(hr) )
            return hr; // can't sink on material... get outta here before anything gets changed

         InternalRelease(); // break circular reference
      }

      // unsink on the older material (if there was one)
      if ( m_Material )
      {
         InternalAddRef();

         hr = AtlUnadvise(m_Material,IID_IMaterialEvents,m_dwMaterialCookie);
         ATLASSERT(SUCCEEDED(hr));
      }

      m_Material = material;

      if ( m_Material )
      {
         m_dwMaterialCookie = dwCookie;
      }

      Fire_OnSegmentChanged(this);
      return S_OK;
   }

   STDMETHOD(get_Material)(IMaterial* *material)
   {
      CHECK_RETVAL(material);

      (*material) = m_Material;

      if ( *material )
         (*material)->AddRef();

      return S_OK;
   }

   STDMETHOD(put_Orientation)(Float64 orientation)
   {
      if ( IsEqual(m_Orientation,orientation) )
         return S_OK;

      m_Orientation = orientation;
      Fire_OnSegmentChanged(this);
      return S_OK;
   }

   STDMETHOD(get_Orientation)(Float64* orientation)
   {
      CHECK_RETVAL(orientation);
      (*orientation) = m_Orientation;
      return S_OK;
   }

   STDMETHOD(Clone)(ISegment* *clone)
   {
      CHECK_RETOBJ(clone);

      CComObject<TEndBlockSegmentImpl>* pClone;
      CComObject<TEndBlockSegmentImpl>::CreateInstance(&pClone);
      (*clone) = pClone;
      (*clone)->AddRef();

      pClone->m_Length = m_Length;
      pClone->m_pSegmentMeasure = m_pSegmentMeasure;
      pClone->m_Orientation = m_Orientation;

      pClone->m_EndBlockLength[etStart]           = m_EndBlockLength[etStart];

      pClone->m_EndBlockLength[etEnd]           = m_EndBlockLength[etEnd];

      if ( m_Beam )
      {
         CComQIPtr<IShape> shape(m_Beam);
         pClone->m_Beam.Release();

         CComPtr<IShape> cloneShape;
         shape->Clone(&cloneShape);

         cloneShape.QueryInterface(&pClone->m_Beam);
      }

      CComPtr<IMaterial> material;
      if ( m_Material )
         m_Material->Clone(&material);

      pClone->putref_Material(material);

      return S_OK;
   }

// Functions to fulfill local class declaration
public:
   STDMETHOD(putref_BeamSection)(/*[in]*/ T_IBeamSection* pBeamSection)
   {
      CHECK_IN(pBeamSection);

      if ( m_Beam.IsEqualObject(pBeamSection) )
         return S_OK;

      m_Beam = pBeamSection;
      Fire_OnSegmentChanged(this);
      return S_OK;
   }

   STDMETHOD(put_EndBlockLength)(/*[in]*/EndType endType,/*[in]*/ Float64 length)
   {
      m_EndBlockLength[endType] = length;
      Fire_OnSegmentChanged(this);
      return S_OK;
   }

   STDMETHOD(get_EndBlockLength)(/*[in]*/EndType endType,/*[out,retval]*/ Float64* pLength)
   {
      *pLength = m_EndBlockLength[endType];
      return S_OK;
   }


// IMaterialEvents
public:
	STDMETHOD(OnMaterialChanged)(IMaterial* material)
   {
      Fire_OnSegmentChanged(this);
      return S_OK;
   }

// IStructuredStorage2
public:
	STDMETHOD(Load)(/*[in]*/ IStructuredLoad2* load)
   {
      return E_NOTIMPL;
   }

	STDMETHOD(Save)(/*[in]*/ IStructuredSave2* save)
   {
      return E_NOTIMPL;
   }

private:
   Float64 GetSuperstructureMemberLength()
   {
      Float64 length;
      CComQIPtr<ISuperstructureMember> ssmbr(m_pSegmentMeasure);
      ATLASSERT(ssmbr);

      ssmbr->get_Length(&length);
      ATLASSERT( 0 <= length );
      return length;
   }
};

