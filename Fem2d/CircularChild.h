///////////////////////////////////////////////////////////////////////
// Fem2D - Two-dimensional Beam Analysis Engine
// Copyright © 1999-2020  Washington State Department of Transportation
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
// CCircularChild.h : Declaration of the CCCircularChild

#ifndef __CCircularChild_H_
#define __CCircularChild_H_
#pragma once

// Template class used for fixing memory leak problem from circular references
// between a parent and a child. Refer to Brice's article "Circular Reference
// Problems with Parent/Children/Child Object Models Part I" for a complete
// discussion.

/////////////////////////////////////////////////////////////////////////////
// CCircularChild
template <class ParentType, class ThreadingModelType>
class  CCircularChild :
	public CComObjectRootEx<ThreadingModelType>
{
public:
   CCircularChild():
   m_pParent(0)
	{
	}

   // DON'T Forget to call InitParent!!!!!!!!!!!!!
   // Probably best way to do this is to expose another type of Init function on 
   // your derived class. This way it will be in client's faces.
   void InitParent( ParentType* pParent)
   {
      ATLASSERT( m_pParent == 0 ); // Init got called twice?
      ATLASSERT( pParent != 0 );
      m_pParent = pParent;
   }

   ULONG OuterAddRef()
   {
      ULONG ulReturn = CComObjectRootEx<ThreadingModelType>::OuterAddRef();
//      ATLTRACE(_T("++++AddRef()  %s::%p refcount=%d\n"),"CCircularChild",this,m_dwRef);
      if ( ulReturn == 2 )
         AddStrongRef();
      return ulReturn;
   }

   ULONG OuterRelease()
   {
      ULONG ulReturn = CComObjectRootEx<ThreadingModelType>::OuterRelease();
//      ATLTRACE(_T("~~~~Release()  %s::%p refcount=%d\n"),"CCircularChild",this,m_dwRef);
      if ( ulReturn == 1 )
         ReleaseStrongRef();
      return ulReturn;
   }

   ULONG InternalAddRef()
   { 
      ULONG ulReturn = CComObjectRootEx<ThreadingModelType>::InternalAddRef();
//      ATLTRACE(_T("++++AddRef()  %s::%p refcount=%d\n"),"CCircularChild",this,m_dwRef);
      if ( ulReturn == 2 )
         AddStrongRef();
      return ulReturn;
   } 

   ULONG InternalRelease()
   {
      ULONG ulReturn = CComObjectRootEx<ThreadingModelType>::InternalRelease();
//      ATLTRACE(_T("~~~~Release()  %s::%p refcount=%d\n"),"CCircularChild",this,m_dwRef);
      if ( ulReturn == 1 )
         ReleaseStrongRef();
      return ulReturn;
   }

protected:
   ParentType* GetParent()
   {
      ATLASSERT( m_pParent != 0 ); // Init not called?
      return m_pParent;
   }

private:
   ParentType* m_pParent; // Weak reference
   CComPtr<ParentType> m_pParentStrong; // Strong reference

   void AddStrongRef()
   {
      ATLASSERT( m_pParent != 0 ); // Init not called?
      ATLASSERT( m_pParentStrong == 0 );

      m_pParent->QueryInterface(&m_pParentStrong);

//      ATLTRACE(_T("CCircularChild Adding Strong Ref to Parent\n"));
      ATLASSERT( m_pParentStrong != 0 );

   }

   void ReleaseStrongRef()
   {
      ATLASSERT( m_pParent != 0 ); // Init not called?
      ATLASSERT( m_pParentStrong != 0 );

//      ATLTRACE(_T("CCircularChild Releasing Strong Ref to Parent\n"));
      m_pParentStrong.Release();

//      ATLASSERT( m_pParentStrong == 0 );
   }
};

#endif // CCircularChild
