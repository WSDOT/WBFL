///////////////////////////////////////////////////////////////////////
// Fem2D - Two-dimensional Beam Analysis Engine
// Copyright © 1999-2026  Washington State Department of Transportation
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
// Fem2dCollection.h :

#pragma once

#include "ComKeyedCollection.h"

// These are collections specific to the Fem2d Package.

// template class specialized for Fem2d (may be useful for general cases later).
//////////////////////////////////////////////////////////

// Collection class for the main Model collections (Joints, Members, POIs).
// Persistence is no longer handled per-collection/per-item - CModel::Load
// rehydrates every collection's m_coll map directly from the freshly
// deserialized WBFL::FEA2D::Model core (see CModel::Load), so this class no
// longer needs a Load()/Save() or a CallOnCreate() bulk-deserialization hook.
class ModelEvents;

template <class T, class ItemType, class StoredType, class EnumType, const IID* piidenum,typename IDType>
class  CModelCollection : public CComKeyedCollection< T, ItemType, StoredType, EnumType, piidenum,IDType>
{
protected:
   // will want to move this out when generalizing this class
   IFem2dModel* m_pModel;
   ModelEvents* m_pEvents; // for sending events back to model
   WBFL::FEA2D::Model* m_pCoreModel; // the FEA2D core Model this collection's items belong to

public:
   void InitCollection(IFem2dModel* pModel, ModelEvents* pEvents, WBFL::FEA2D::Model* pCoreModel)
   {
      ATLASSERT(pModel!=0 );
      ATLASSERT(pEvents!=0 );
      ATLASSERT(pCoreModel!=0 );
      m_pModel  = pModel;
      m_pEvents = pEvents;
      m_pCoreModel = pCoreModel;
   }
};

// Collection class for the IFem2dLoading collections (JointLoads, PointLoads,
// DistributedLoads, MemberStrains, JointDeflections). Each of these mirrors
// one of the five load-type collections owned by a WBFL::FEA2D::Loading.
template <class T, class ItemType, class StoredType, class EnumType, const IID* piidenum,typename LOADIDTYPE>
class  CLoadsCollection : public CComKeyedCollection< T, ItemType, StoredType, EnumType, piidenum,typename LOADIDTYPE>
{
protected:
   // will want to move this out when generalizing this class
   IFem2dModel* m_pModel;
   ModelEvents* m_pEvents; // for sending events back to model
   IFem2dLoading* m_pLoading;
   WBFL::FEA2D::Loading* m_pCoreLoading; // the FEA2D core Loading this collection's items belong to

public:
   void InitCollection(IFem2dModel* pModel, ModelEvents* pEvents, IFem2dLoading* pLoading, WBFL::FEA2D::Loading* pCoreLoading)
   {
      ATLASSERT(pModel!=0 && pLoading!=0 && pCoreLoading!=0);

      m_pModel = pModel;
      m_pEvents = pEvents;
      m_pLoading = pLoading;
      m_pCoreLoading = pCoreLoading;
   }
};

