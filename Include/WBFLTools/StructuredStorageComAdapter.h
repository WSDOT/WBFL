///////////////////////////////////////////////////////////////////////
// System - WBFL low level system services
// Copyright © 1999-2026  Washington State Department of Transportation
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

// Header-only for the same reason as ComStructuredStorageAdapter.h (see that file):
// these classes only forward calls through an already-obtained COM interface pointer,
// so callers (e.g. WBFL::EAF::Broker) don't need a link-time ProjectReference to a
// WBFLTools/psgLib-style .vcxproj just to bridge a COM IStructuredLoad/IStructuredSave
// pointer to the native WBFL::System interface.

#include <System\IStructuredSave.h>
#include <System\IStructuredLoad.h>
#include <atlbase.h>
#include <atlcomcli.h>
#include <WBFLTools.h>

/// Adapts a plain COM ::IStructuredSave pointer (as created via CoCreateInstance(CLSID_StructuredSave),
/// the same interface WBFL::EAF::IAgentPersist::Save received before it was migrated to the native
/// WBFL::System::IStructuredSave interface) to that native interface. Unlike the IStructuredSave2-based
/// ComStructuredSaveAdapter above, this variant's underlying COM interface has a raw-unit-passthrough
/// capability (SaveRawUnit), so PutUnit is a real, working forward rather than a throw. Relocated from
/// PGSuper's psgLib (originally a 1998 "HACK...to get the library manager and the PGSuper project file
/// working together"), generalized so any product's Broker/Agent code can reuse it.
class CStructuredSave : public WBFL::System::IStructuredSave
{
public:
   explicit CStructuredSave(::IStructuredSave* pStrSave) : m_pStrSave(pStrSave) {}
   virtual ~CStructuredSave() = default;

   /// Returns the wrapped COM interface pointer, for callers that still need to delegate into
   /// not-yet-migrated code expecting the plain COM interface directly.
   ::IStructuredSave* GetComInterface() const { return m_pStrSave; }

   virtual void BeginUnit(LPCTSTR name, Float64 version = 0) override
   {
      m_pStrSave->BeginUnit(name, version);
   }

   virtual void EndUnit() override
   {
      m_pStrSave->EndUnit();
   }

   virtual Float64 GetVersion() override
   {
      Float64 version;
      m_pStrSave->get_Version(&version);
      return version;
   }

   virtual Float64 GetTopVersion() override
   {
      Float64 version;
      m_pStrSave->get_TopVersion(&version);
      return version;
   }

   virtual void Property(LPCTSTR name, LPCTSTR value) override { PutVariantProperty(name, CComVariant(value)); }
   virtual void Property(LPCTSTR name, Float64 value) override { PutVariantProperty(name, CComVariant(value)); }
   virtual void Property(LPCTSTR name, Int16 value) override { PutVariantProperty(name, CComVariant(value)); }
   virtual void Property(LPCTSTR name, Uint16 value) override { PutVariantProperty(name, CComVariant(value)); }
   virtual void Property(LPCTSTR name, Int32 value) override { PutVariantProperty(name, CComVariant(value)); }
   virtual void Property(LPCTSTR name, Uint32 value) override { PutVariantProperty(name, CComVariant(value)); }
   virtual void Property(LPCTSTR name, Int64 value) override { PutVariantProperty(name, CComVariant(value)); }
   virtual void Property(LPCTSTR name, Uint64 value) override { PutVariantProperty(name, CComVariant(value)); }
   virtual void Property(LPCTSTR name, LONG value) override { PutVariantProperty(name, CComVariant(value)); }
   virtual void Property(LPCTSTR name, ULONG value) override { PutVariantProperty(name, CComVariant(value)); }
   virtual void Property(LPCTSTR name, bool value) override { PutVariantProperty(name, CComVariant(value)); }

   /// Forwards to the wrapped COM interface's SaveRawUnit - this is what lets the Broker's
   /// missing-agent data-passthrough guarantee keep working once IAgentPersist takes native pointers.
   virtual void PutUnit(LPCTSTR xml) override
   {
      m_pStrSave->SaveRawUnit(xml);
   }

private:
   CComPtr<::IStructuredSave> m_pStrSave;

   void PutVariantProperty(LPCTSTR name, const VARIANT& v)
   {
      m_pStrSave->put_Property(name, v);
   }
};

/// Adapts a plain COM ::IStructuredLoad pointer to the native WBFL::System::IStructuredLoad
/// interface. See CStructuredSave above for the rationale. GetUnit forwards to the wrapped COM
/// interface's LoadRawUnit.
class CStructuredLoad : public WBFL::System::IStructuredLoad
{
public:
   explicit CStructuredLoad(::IStructuredLoad* pStrLoad) : m_pStrLoad(pStrLoad) {}
   virtual ~CStructuredLoad() = default;

   /// Returns the wrapped COM interface pointer, for callers that still need to delegate into
   /// not-yet-migrated code expecting the plain COM interface directly.
   ::IStructuredLoad* GetComInterface() const { return m_pStrLoad; }

   virtual bool BeginUnit(LPCTSTR name) override
   {
      return SUCCEEDED(m_pStrLoad->BeginUnit(name));
   }

   virtual bool EndUnit() override
   {
      return SUCCEEDED(m_pStrLoad->EndUnit());
   }

   virtual Float64 GetVersion() override
   {
      Float64 version;
      m_pStrLoad->get_Version(&version);
      return version;
   }

   virtual Float64 GetParentVersion() override
   {
      Float64 version;
      m_pStrLoad->get_ParentVersion(&version);
      return version;
   }

   virtual std::_tstring GetParentUnit() override
   {
      USES_CONVERSION;
      CComBSTR bstr;
      m_pStrLoad->get_ParentUnit(&bstr);
      return OLE2T(bstr);
   }

   virtual Float64 GetTopVersion() override
   {
      Float64 version;
      m_pStrLoad->get_TopVersion(&version);
      return version;
   }

   virtual bool Property(LPCTSTR name, std::_tstring* pvalue) override
   {
      USES_CONVERSION;
      CComVariant var;
      var.vt = VT_BSTR;
      HRESULT hr = m_pStrLoad->get_Property(name, &var);
      *pvalue = var.bstrVal != nullptr ? std::_tstring(OLE2T(var.bstrVal)) : std::_tstring();
      return SUCCEEDED(hr);
   }

   virtual bool Property(LPCTSTR name, Float64* pvalue) override { return GetVariantProperty(name, VT_R8, pvalue, &VARIANT::dblVal); }
   virtual bool Property(LPCTSTR name, Int16* pvalue) override { return GetVariantProperty(name, VT_I2, pvalue, &VARIANT::iVal); }
   virtual bool Property(LPCTSTR name, Uint16* pvalue) override { return GetVariantProperty(name, VT_UI2, pvalue, &VARIANT::uiVal); }
   virtual bool Property(LPCTSTR name, Int32* pvalue) override { return GetVariantProperty(name, VT_I4, pvalue, &VARIANT::lVal); }
   virtual bool Property(LPCTSTR name, Uint32* pvalue) override { return GetVariantProperty(name, VT_UI4, pvalue, &VARIANT::ulVal); }
   virtual bool Property(LPCTSTR name, Int64* pvalue) override { return GetVariantProperty(name, VT_I8, pvalue, &VARIANT::llVal); }
   virtual bool Property(LPCTSTR name, Uint64* pvalue) override { return GetVariantProperty(name, VT_UI8, pvalue, &VARIANT::ullVal); }
   virtual bool Property(LPCTSTR name, LONG* pvalue) override { return GetVariantProperty(name, VT_I4, pvalue, &VARIANT::lVal); }
   virtual bool Property(LPCTSTR name, ULONG* pvalue) override { return GetVariantProperty(name, VT_UI4, pvalue, &VARIANT::ulVal); }

   virtual bool Property(LPCTSTR name, bool* pvalue) override
   {
      CComVariant var;
      var.vt = VT_BOOL;
      HRESULT hr = m_pStrLoad->get_Property(name, &var);
      *pvalue = (var.boolVal == VARIANT_TRUE);
      return SUCCEEDED(hr);
   }

   virtual bool Eof() const override
   {
      return m_pStrLoad->EndOfStorage() == S_OK;
   }

   virtual std::_tstring GetStateDump() const override
   {
      return std::_tstring(_T("State data not available"));
   }

   /// Forwards to the wrapped COM interface's LoadRawUnit - captures the current unit's XML
   /// verbatim so it can be replayed later via PutUnit if this reader can't otherwise consume it.
   virtual std::_tstring GetUnit() const override
   {
      USES_CONVERSION;
      CComBSTR bstrUnit;
      m_pStrLoad->LoadRawUnit(&bstrUnit);
      return std::_tstring(OLE2T(bstrUnit));
   }

private:
   CComPtr<::IStructuredLoad> m_pStrLoad;

   template <typename T, typename M>
   bool GetVariantProperty(LPCTSTR name, VARTYPE vt, T* pvalue, M VARIANT::* member)
   {
      CComVariant var;
      var.vt = vt;
      HRESULT hr = m_pStrLoad->get_Property(name, &var);
      *pvalue = static_cast<T>(var.*member);
      return SUCCEEDED(hr);
   }
};
