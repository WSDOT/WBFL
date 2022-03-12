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


#ifndef INCLUDED_WBFLATLEXT_H_
#define INCLUDED_WBFLATLEXT_H_

#pragma once

// _Copy class for use with Enumerators. VB Collections use IEnumVARIANT's. Because of this
// Collection objects that use STL have vectors of VARIANTS. When implementing a C++-friendly
// enumerator, we need to access the collection of VARIANTS but return an interface pointer.
// This custom copy class does just that. It is modeled after _CopyInterface
template <class T>
class _CopyVariantToInterface
{
   public:
      static HRESULT copy(T** iTarget,const VARIANT* vSrc)
      {
         if (vSrc == nullptr)
         {
            return E_INVALIDARG;
         }

         if (iTarget == nullptr)
         {
            return E_POINTER;
         }

         if (*iTarget != nullptr)
         {
            (*iTarget)->Release();
         }

         if (vSrc->vt == VT_DISPATCH)
         {
            vSrc->pdispVal->QueryInterface(iTarget);
         }
         else if (vSrc->vt == VT_UNKNOWN)
         {
            vSrc->punkVal->QueryInterface(iTarget);
         }
         else
         {
            return E_INVALIDARG;
         }

         return S_OK;
      }

      static void init(T**) {}
      static void destroy(T** p) { if (*p) (*p)->Release(); }
};

// Macros for testing function arguements
#define CHECK_IN(_ptr_)     if ( _ptr_ == nullptr ) return E_INVALIDARG
#define CHECK_INOUT(_ptr_)  if ( _ptr_ == nullptr || (*_ptr_) == nullptr ) return E_INVALIDARG
#define CHECK_RETVAL(_ptr_) if ( _ptr_ == nullptr ) return E_POINTER
#define CHECK_RETOBJ(_ptr_) if ( _ptr_ == nullptr ) return E_POINTER; if ( *_ptr_ ) (*_ptr_) = 0
#define CHECK_RETSTRING(_ptr_) CHECK_RETVAL(_ptr_)

// Base class for tracing reference counts
// Example
//    Comment out first line when you want tracing
//    Comment out second line to turn off tracing
//    ie. The first or the second line has to be commented out, but not both or neither
//
//    class ATL_NO_VTABLE CMyClass : 
//	      //public CComObjectRootEx<CComSingleThreadModel>,
//       public CComRefCountTracer<CMyClass,CComObjectRootEx<CComSingleThreadModel> >,
//       ...

#include <typeinfo>
template <class C,class T>
class CComRefCountTracer : public T
{
public:
   ~CComRefCountTracer()
   {
      const type_info& t = typeid((C*)this);
      ATLTRACE("Destructor called for %s\n",t.name());
   }

   void FinalRelease()
   {
      const type_info& t = typeid((C*)this);
      ATLTRACE("FinalRelease() called for %s\n",t.name());

      T::FinalRelease();
   }

   ULONG OuterAddRef()  
   {  
      ULONG ulReturn = T::OuterAddRef();  
      const type_info& t = typeid((C*)this);
      ATLTRACE("%d+ %s::%p\n",m_dwRef,t.name(),this);  
      return ulReturn;  
   }  

   ULONG OuterRelease()  
   {  
      ULONG ulReturn = T::OuterRelease();  
      const type_info& t = typeid((C*)this);
      ATLTRACE("%d- %s::%p\n",m_dwRef,t.name(),this);
      return ulReturn;  
   } 

   ULONG InternalAddRef() 
   { 
      ULONG ulReturn = T::InternalAddRef(); 
      const type_info& t = typeid((C*)this);
      ATLTRACE("%d+ %s::%p\n",m_dwRef,t.name(),this);  
      return ulReturn; 
   } 

   ULONG InternalRelease() 
   { 
      ULONG ulReturn = T::InternalRelease(); 
      const type_info& t = typeid((C*)this);
      ATLTRACE("%d- %s::%p\n",m_dwRef,t.name(),this);
      return ulReturn; 
   } 
};


//////////////////////////////////////////////////////////
// Generalized class for cleanly dealing with HRESULT return values.
// Allows one line of code to call and check errors for COM Functions.
//
// ONE CAVEAT: This code MUST be called with a try block somewhere upstream in the call stack.
//             This is because it WILL throw (Huck) when a COM error occurs.
//             the call stack

class CHRException
{
public:
   CHRException():
      m_bAssertOnFailure(true),
   m_Result(S_OK)
   {};

#if defined _DEBUG
   void AssertOnFailure(bool bAssert) { m_bAssertOnFailure = bAssert; }
#endif

   // Throw if assigned to a FAILED HRESULT.
   HRESULT operator=(HRESULT hr)
   {
      m_Result = hr;
      if (FAILED(hr))
      {
#if defined _DEBUG
         if (m_bAssertOnFailure)
         {
            ATLASSERT(false);
         }
#endif
         throw hr;
      }
      else if (hr == S_FALSE)
      {
         // in the lbam, this means cancel
         throw hr;
      }
      return hr;
   }

   // Hand off most recent hr if asked for it
   operator HRESULT()
   {
      return m_Result;
   }

private:
   bool m_bAssertOnFailure;
   HRESULT m_Result; 
};


//////////////////////////////////////////////////////////
// Template functions for setting up and tearing down connection points 
// for the case when there is a circular reference between the subject 
// and the observer.
// Refer to the article  "Circular Reference Problems with Parent/Child 
// Object Models - Part II" by Rick Brice for more information
//
// NOTES:
// Objects (T) using this template class must derive from CComObjectRootEx.
// The methods in this class should always be called in pairs (i.e., don't mix
// them with other Advise/Unadvise's)

template <class T>
inline HRESULT CrAdvise(IUnknown* pUnkCP, T* pT, const IID& iid, LPDWORD pdw )
{
   HRESULT hr;
   IUnknown* piu;
   hr = pT->QueryInterface(IID_IUnknown, (void**)&piu);
   if (FAILED(hr))
      return hr;

   hr = AtlAdvise(pUnkCP, piu, iid, pdw);
   if (FAILED(hr))
      return hr;

   piu->Release();

   // Avoid circular reference. Decrement RefCount in a thread safe way
   pT->InternalRelease();

   return S_OK;
}

template <class T>
inline HRESULT CrUnadvise( IUnknown* pUnkCP, T* pT, const IID& iid, DWORD dw )
{
   // Counteract InternalRelease() in OnBeforeAdd()
   pT->InternalAddRef(); 

   // release connection point
   HRESULT hr;
   hr = AtlUnadvise(pUnkCP, iid, dw);

   return hr;
}

// Useful for assigning a new object in putref property methods for objects with 
// connection points:
//     rpTarget - typically the member to be assigned to (e.g., m_HookPoint)
//     pNewVal  - the new object to be assigned 
//     listener - the class that owns the property to be assigned to
// Example:
//    return CrAssignPointer(m_pStart, newVal, this, DIID_DPoint2dEvents, &m_dwStartCookie);
template <class TC, class TL>
inline HRESULT CrAssignPointer(ATL::CComPtr<TC>& rpTarget, TC* pNewVal, TL* listener, const IID& iidEvents, LPDWORD cookie )
{
   CHECK_IN(pNewVal);

	if (!rpTarget.IsEqualObject(pNewVal))
   {
      HRESULT hr;

      // Connect to the new object first
      DWORD dwCookie;
      hr = CrAdvise(pNewVal,listener,iidEvents,&dwCookie);
      if ( FAILED(hr) )
         return hr;  // failed... don't change anything

      // Disconnect from old object
      // but only if the target is not a null pointer
      // (This could be called for a first time assignment where the target
      // has an initial value of nullptr)
      if ( rpTarget.p != nullptr )
      {
         hr = CrUnadvise(rpTarget, listener, iidEvents, *cookie );
         if ( FAILED(hr) )
         {
            // undo the connection to the new object
            CrUnadvise(pNewVal, listener, iidEvents, dwCookie );
            return hr;
         }
      }

      // Connection and disconnection went well...
      // do the pointer and cookie assignment
      rpTarget = pNewVal;
      *cookie = dwCookie;
   }

   return S_OK;
}



#endif // INCLUDED_WBFLATLEXT_H_