///////////////////////////////////////////////////////////////////////
// EAF - Extensible Application Framework
// Copyright © 1999-2025  Washington State Department of Transportation
//                        Bridge and Structures Office
//
// This library is a part of the Washington Bridge Foundation Libraries
// and was developed as part of the Alternate Route Project
//
// This library is free software; you can redistribute it and/or modify it under
// the terms of the Alternate Route Library Open Source License as published by 
// the Washington State Department of Transportation, Bridge and Structures Office.
//
// This program is distributed in the hope that it will be useful, but is distributed 
// AS IS, WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY 
// or FITNESS FOR A PARTICULAR PURPOSE. See the Alternate Route Library Open Source 
// License for more details.
//
// You should have received a copy of the Alternate Route Library Open Source License 
// along with this program; if not, write to the Washington State Department of 
// Transportation, Bridge and Structures Office, P.O. Box  47340, 
// Olympia, WA 98503, USA or e-mail Bridge_Support@wsdot.wa.gov
///////////////////////////////////////////////////////////////////////

#pragma once

#include <EAF/Agent.h>

#if defined _DEBUG
namespace WBFL
{
   namespace EAF
   {
      template <class T>
      class IFacePtr
      {
      public:
         IFacePtr() = default;
         explicit IFacePtr(std::shared_ptr<T> p) : m_ptr(p) {}
         explicit IFacePtr(T* lp) : m_ptr(lp) {}
         IFacePtr(const IFacePtr<T>& p) : m_ptr(p.m_ptr) {}
         ~IFacePtr()
         {
            // if this assert fires, the interfaced is never used
            ASSERT(m_bUsed);
         }
         IFacePtr& operator=(const IFacePtr& p) { if (this != p) { m_ptr = p.m_ptr; m_bUsed = p.m_bUsed; } return *this; }
         bool IsUsed() const { return m_bUsed; }
         IFacePtr& operator=(std::nullptr_t) { m_ptr.reset(); m_bUsed = true; return *this; }
         T* get() { m_bUsed = true; return m_ptr.get(); }
         T& operator*() { m_bUsed = true; return m_ptr; }
         //operator T* () const noexcept { m_bUsed = true; return m_ptr.get(); } // prevent conversion to raw pointer
         T* operator->() const noexcept { m_bUsed = true; return m_ptr.get(); }
         operator std::shared_ptr<T>() { m_bUsed = true; return m_ptr; } // convert to a shared pointer
         operator std::weak_ptr<T>() { m_bUsed = true; return m_ptr; } // convert to a weak pointer
         bool operator==(const IFacePtr& p) const { m_bUsed = true; return m_ptr == p.m_ptr; } // comparison with other points
         bool operator!=(const IFacePtr& p) const { m_bUsed = true; return m_ptr != p.m_ptr; }
         bool operator==(std::nullptr_t) const { m_bUsed = true; return m_ptr == nullptr; } // comparison to nullptr
         bool operator!=(std::nullptr_t) const { m_bUsed = true; return m_ptr != nullptr; }
         explicit operator bool() const { m_bUsed = true; return m_ptr != nullptr; } // conversion to boolean
         
         // convert from type T to type U if U is derived from T
         template <typename U,typename = std::enable_if_t<std::is_convertible<T*,U*>::value>>
         operator std::shared_ptr<U>() { m_bUsed = true; return std::static_pointer_cast<U>(m_ptr); }

      private:
         std::shared_ptr<T> m_ptr;
         mutable bool m_bUsed = false;
      };
   };
};

#define GET_IFACE(_i_,_ptr_) ASSERT(m_pBroker!=nullptr); auto _ptr_ = WBFL::EAF::IFacePtr<_i_>(m_pBroker->GetInterface<_i_>(IID_##_i_))
#define GET_IFACE_(_ns_,_i_,_ptr_) ASSERT(m_pBroker!=nullptr); auto _ptr_ = WBFL::EAF::IFacePtr<_ns_::_i_>(m_pBroker->GetInterface<_ns_::_i_>(##_ns_::IID_##_i_))
#define GET_IFACE_NOCHECK(_i_,_ptr_) ASSERT(m_pBroker!=nullptr); auto _ptr_ = m_pBroker->GetInterface<_i_>(IID_##_i_)
#define GET_IFACE2(_b_,_i_,_ptr_) auto _ptr_ = WBFL::EAF::IFacePtr<_i_>(_b_->GetInterface<_i_>(IID_##_i_))
#define GET_IFACE2_(_ns_,_b_,_i_,_ptr_) auto _ptr_ = WBFL::EAF::IFacePtr<_ns_::_i_>(_b_->GetInterface<_ns_::_i_>(##_ns_::IID_##_i_))
#define GET_IFACE2_NOCHECK(_b_,_i_,_ptr_) auto _ptr_ = _b_->GetInterface<_i_>(IID_##_i_)
#define ASSIGN_IFACE(_i_,_ptr_) ASSERT(m_pBroker!=nullptr); _ptr_ = m_pBroker->GetInterface<_i_>( IID_##_i_)
#define ASSIGN_IFACE2(_b_,_i_,_ptr_) _ptr_ = _b_->GetInterface<_i_>( IID_##_i_)

#else

#define GET_IFACE(_i_,_ptr_) ASSERT(m_pBroker!=nullptr); auto _ptr_ = std::shared_ptr<_i_>(m_pBroker->GetInterface<_i_>(IID_##_i_))
#define GET_IFACE_(_ns_,_i_,_ptr_) ASSERT(m_pBroker!=nullptr); auto _ptr_ = std::shared_ptr<_ns_::_i_>(m_pBroker->GetInterface<_ns_::_i_>(##_ns_::IID_##_i_))
#define GET_IFACE_NOCHECK(_i_,_ptr_) ASSERT(m_pBroker!=nullptr); auto _ptr_ = m_pBroker->GetInterface<_i_>(IID_##_i_)
#define GET_IFACE2(_b_,_i_,_ptr_) auto _ptr_ = std::shared_ptr<_i_>(_b_->GetInterface<_i_>(IID_##_i_))
#define GET_IFACE2_(_ns_,_b_,_i_,_ptr_) auto _ptr_ = std::shared_ptr<_ns_::_i_>(_b_->GetInterface<_ns_::_i_>(##_ns_::IID_##_i_))
#define GET_IFACE2_NOCHECK(_b_,_i_,_ptr_) auto _ptr_ = _b_->GetInterface<_i_>(IID_##_i_)
#define ASSIGN_IFACE(_i_,_ptr_) ASSERT(m_pBroker!=nullptr); _ptr_ = m_pBroker->GetInterface<_i_>( IID_##_i_)
#define ASSIGN_IFACE2(_b_,_i_,_ptr_) _ptr_ = _b_->GetInterface<_i_>( IID_##_i_)

#endif

#define REGISTER_INTERFACE(iface) m_pBroker->RegisterInterface(IID_##iface,std::dynamic_pointer_cast<WBFL::EAF::Agent>(shared_from_this()))

#define REGISTER_EVENT_SINK(iface) m_pBroker->RegisterEventSink<iface>(std::dynamic_pointer_cast<iface>(shared_from_this()))
#define UNREGISTER_EVENT_SINK(iface,cookie) m_pBroker->UnregisterEventSink<iface>(cookie)
