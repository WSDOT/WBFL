///////////////////////////////////////////////////////////////////////
// WBFL - Washington Bridge Foundation Libraries
// Copyright © 2003  Washington State Department of Transportation
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
// 4500 3rd Ave SE, P.O. Box 47340, Olympia, WA 98503, USA or e-mail
// Bridge_Support@wsdot.wa.gov
///////////////////////////////////////////////////////////////////////

#ifndef INCLUDED_ATLMAPCOPY_H_
#define INCLUDED_ATLMAPCOPY_H_

// Atl Copy class for copying variants from an stl map contained in a
// ICollectionOnSTLImpl
template <class ContainerType>
class _CopyMapOfCComVariants
{
   public:
      static HRESULT copy(VARIANT* vDest, const typename ContainerType::value_type* pSource)
      {
//         CComPtr<IUnknown> punk;
//         ((*pSource).second)->QueryInterface(IID_IUnknown,(void**)&punk);
//         CComVariant vSource(punk);
         CComVariant vSource((*pSource).second);
         return ::VariantCopy(vDest,&vSource);
      }

      static void init(typename ContainerType::value_type*) {}
      static void destroy(VARIANT* ) {}
};

// Atl Copy class for copying variants to an interface pointer from a contained in a
// ICollectionOnSTLImpl
template <class InterfaceType, class ContainerType>
class _CopyMapOfCComVariantsToInterface
{
   public:
      static HRESULT copy(InterfaceType** pDest, const typename ContainerType::value_type* pSource)
      {
         CComVariant vSource((*pSource).second);
         vSource.pdispVal->QueryInterface(pDest);
         return S_OK;
      }

      static void init(InterfaceType**) {}
      static void destroy(InterfaceType** p) { if (*p) (*p)->Release(); }
};

template <class ContainerType, class destType>
class _MapCopyUsingStaticCast
{
   public:
      static HRESULT copy(destType** pDest, typename ContainerType::value_type* pSource)
      {
         // have to be able to cast StoredType to ItemType
         destType* pi = static_cast<destType*>(pSource->second);
         if (pi==0)
         {
            ATLASSERT(pi!=0);
            return E_FAIL;
         }
         else
         {
            *pDest = pi;
            (*pDest)->AddRef();
         }

         return S_OK;
      }

      static void init(typename ContainerType::value_type*) {}
      static void destroy(destType**p ) {if (*p) (*p)->Release();}
};


#endif // INCLUDED_ATLMAPCOPY_H_