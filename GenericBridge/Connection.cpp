///////////////////////////////////////////////////////////////////////
// GenericBridge - Generic Bridge Modeling Framework
// Copyright © 1999-2011  Washington State Department of Transportation
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

// Connection.cpp : Implementation of CConnection
#include "stdafx.h"
#include "WBFLGenericBridge.h"
#include "Connection.h"
#include <MathEx.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CConnection
HRESULT CConnection::FinalConstruct()
{
   return S_OK;
}

void CConnection::FinalRelease()
{
}

STDMETHODIMP CConnection::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_IConnection,
      &IID_IStructuredStorage2,
	};
	for (int i=0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}


STDMETHODIMP CConnection::Clone(IConnection** clone)
{
   CHECK_RETOBJ(clone);

   CComObject<CConnection>* pClone;
   CComObject<CConnection>::CreateInstance(&pClone);

   (*clone) = pClone;
   (*clone)->AddRef();

   (*clone)->put_BearingOffset(m_BearingOffset);
   (*clone)->put_EndDistance(m_EndDistance);
   (*clone)->put_BearingOffsetMeasurementType(m_BearingOffsetMeasurementType);
   (*clone)->put_EndDistanceMeasurementType(m_EndDistanceMeasurementType);
   (*clone)->put_EndDistanceMeasurementLocation(m_EndDistanceMeasurementLocation);
   (*clone)->put_SupportWidth(m_SupportWidth);

   return S_OK;
}

STDMETHODIMP CConnection::get_BearingOffset(Float64* brgOffset)
{
   CHECK_RETVAL(brgOffset);
   *brgOffset = m_BearingOffset;
   return S_OK;
}

STDMETHODIMP CConnection::put_BearingOffset(Float64 brgOffset)
{
   if ( IsEqual(m_BearingOffset,brgOffset) )
      return S_OK;

   m_BearingOffset = brgOffset;
#pragma Reminder("UPDATE: Fire Event")

   return S_OK;
}

STDMETHODIMP CConnection::get_EndDistance(Float64* endDist)
{
   CHECK_RETVAL(endDist);
   *endDist = m_EndDistance;
   return S_OK;
}

STDMETHODIMP CConnection::put_EndDistance(Float64 endDistance)
{
   if ( IsEqual(m_EndDistance,endDistance) )
      return S_OK;

   m_EndDistance = endDistance;
#pragma Reminder("UPDATE: Fire Event")

   return S_OK;
}

STDMETHODIMP CConnection::get_BearingOffsetMeasurementType(MeasurementType* measure)
{
   CHECK_RETVAL(measure);
   *measure = m_BearingOffsetMeasurementType;
   return S_OK;
}

STDMETHODIMP CConnection::put_BearingOffsetMeasurementType(MeasurementType measure)
{
   if ( m_BearingOffsetMeasurementType == measure )
      return S_OK;

   m_BearingOffsetMeasurementType = measure;
#pragma Reminder("UPDATE: Fire Event")

   return S_OK;
}

STDMETHODIMP CConnection::get_EndDistanceMeasurementType(MeasurementType* measure)
{
   CHECK_RETVAL(measure);
   *measure = m_EndDistanceMeasurementType;
   return S_OK;
}

STDMETHODIMP CConnection::put_EndDistanceMeasurementType(MeasurementType measure)
{
   if ( m_EndDistanceMeasurementType == measure )
      return S_OK;

   m_EndDistanceMeasurementType = measure;
#pragma Reminder("UPDATE: Fire Event")

   return S_OK;
}

STDMETHODIMP CConnection::get_EndDistanceMeasurementLocation(MeasurementLocation* measure)
{
   CHECK_RETVAL(measure);
   *measure = m_EndDistanceMeasurementLocation;
   return S_OK;
}

STDMETHODIMP CConnection::put_EndDistanceMeasurementLocation(MeasurementLocation measure)
{
   if ( m_EndDistanceMeasurementLocation == measure )
      return S_OK;

   m_EndDistanceMeasurementLocation = measure;
#pragma Reminder("UPDATE: Fire Event")

   return S_OK;
}

STDMETHODIMP CConnection::get_SupportWidth(Float64* supportWidth)
{
   CHECK_RETVAL(supportWidth);
   *supportWidth = m_SupportWidth;
   return S_OK;
}

STDMETHODIMP CConnection::put_SupportWidth(Float64 supportWidth)
{
   if ( IsEqual(m_SupportWidth,supportWidth) )
      return S_OK;

   m_SupportWidth = supportWidth;
#pragma Reminder("UPDATE: Fire Event")

   return S_OK;
}

/////////////////////////////////////////////////////
// IStructuredStorage2 implementation
STDMETHODIMP CConnection::Load(IStructuredLoad2* load)
{
   CHECK_IN(load);

   CComVariant var;
   load->BeginUnit(CComBSTR("Connection"));

   Float64 version;
   load->get_Version(&version);

   load->get_Property(CComBSTR("BearingOffset"),&var);
   m_BearingOffset = var.dblVal;

   load->get_Property(CComBSTR("EndDistance"),&var);
   m_EndDistance = var.dblVal;

   load->get_Property(CComBSTR("BearingOffsetMeasurement"),&var);
   m_BearingOffsetMeasurementType = (MeasurementType)(var.lVal);

   load->get_Property(CComBSTR("EndDistanceMeasurement"),&var);
   m_EndDistanceMeasurementType = (MeasurementType)(var.lVal);

   if (version >= 2.0)
   {
      load->get_Property(CComBSTR("EndDistanceMeasurementLocation"),&var);
      m_EndDistanceMeasurementLocation = (MeasurementLocation)(var.lVal);
   }

   VARIANT_BOOL bEnd;
   load->EndUnit(&bEnd);

   return S_OK;
}

STDMETHODIMP CConnection::Save(IStructuredSave2* save)
{
   CHECK_IN(save);

   save->BeginUnit(CComBSTR("Connection"),2.0);
   save->put_Property(CComBSTR("BearingOffset"),CComVariant(m_BearingOffset));
   save->put_Property(CComBSTR("EndDistance"),CComVariant(m_EndDistance));
   save->put_Property(CComBSTR("BearingOffsetMeasurement"),CComVariant(m_BearingOffsetMeasurementType));
   save->put_Property(CComBSTR("EndDistanceMeasurement"),CComVariant(m_EndDistanceMeasurementType));
   save->put_Property(CComBSTR("EndDistanceMeasurementLocation"),CComVariant(m_EndDistanceMeasurementLocation));

   save->EndUnit();

   return S_OK;
}
