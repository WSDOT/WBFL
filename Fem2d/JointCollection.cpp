///////////////////////////////////////////////////////////////////////
// Fem2D - Two-dimensional Beam Analysis Engine
// Copyright © 1999-2014  Washington State Department of Transportation
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
// JointCollection.cpp : Implementation of CJointCollection
#include "stdafx.h"
#include "JointCollection.h"
#include "Joint.h"
#include "ModelEvents.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CJointCollection

STDMETHODIMP CJointCollection::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_IFem2dJointCollection
	};
	for (int i=0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

void CJointCollection::OnCreate(IFem2dModel* pParent, ModelEvents* pEvents)
{
   InitParent(pParent); // CCircularChild implementation
   InitCollection(pParent,pEvents);  // to get at C++ event handlers
}


STDMETHODIMP CJointCollection::Create(JointIDType id, Float64 fltX, Float64 fltY, IFem2dJoint **ppJoint)
{
   CHECK_RETOBJ(ppJoint);
   HRESULT hr = E_FAIL;

   // see if a joint with our id already exists
   ContainerIteratorType it( m_coll.find(id) );
   if (it != m_coll.end())
   {
      // exists - return error
      return CComCoClass<CJointCollection, &CLSID_Fem2dJointCollection>::Error(IDS_E_JOINT_WITH_ID_ALREADY_EXISTS, IDH_E_JOINT_WITH_ID_ALREADY_EXISTS, GetHelpFile(),IID_IFem2dJoint, FEM2D_E_JOINT_WITH_ID_ALREADY_EXISTS);
   }
   else
   {
      // create a new joint
      CComObject<CJoint>* pjnt;
      hr = CComObject<CJoint>::CreateInstance( &pjnt );
      if (FAILED(hr))
         return hr;

      *ppJoint = pjnt;
      (*ppJoint)->AddRef(); // for client

      pjnt->OnCreate(m_pModel, m_pEvents, id, fltX, fltY);

      // insert new joint
      std::pair<ContainerIteratorType, bool> st( m_coll.insert(ContainerValueType(id, CComVariant(*ppJoint))) );
      if (!st.second)
      {
         ATLASSERT(false); // insert failed - better check why
         return E_FAIL;
      }


      m_pEvents->OnJointAdded(id);
   }

	return hr;
}

STDMETHODIMP CJointCollection::Remove(CollectionIndexType IDorIndex, Fem2dAccessType AccessMethod, JointIDType* pid)
{
   HRESULT hr = JointCollImpl::Remove(IDorIndex, AccessMethod, pid);
   if (SUCCEEDED(hr))
   {
      // send event up the pipe
      m_pEvents->OnJointRemoved(*pid);
   }

   return hr;
}

STDMETHODIMP CJointCollection::Clear()
{
   if (!m_coll.empty())
   {
      HRESULT hr = JointCollImpl::Clear();
      if (SUCCEEDED(hr))
      {
         // send event up the pipe
         m_pEvents->OnJointsCleared();
      }
      return hr;
   }

   return S_OK;
}