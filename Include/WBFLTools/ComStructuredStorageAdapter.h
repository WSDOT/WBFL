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

// Header-only by design: these classes only forward calls through an already-
// obtained COM interface pointer (pure vtable dispatch), so there's nothing to
// compile/export - keeping them header-only means callers (e.g. LBAMAnalysis)
// don't need a link-time ProjectReference to WBFLTools.vcxproj just to use this
// adapter, which was previously breaking standalone (non-WBFL.sln) builds of
// projects that pulled it in transitively (VS's implicit single-project solution
// wrapper couldn't resolve the new project's platform config).

#include <System\IStructuredSave.h>
#include <System\IStructuredLoad.h>
#include <System\XStructuredSave.h>
#include <System\XStructuredLoad.h>
#include <System\Exception.h>
#include <atlbase.h>
#include <atlcomcli.h>
#include <WBFLTools.h>

/// Adapts a COM IStructuredSave2 pointer to the native WBFL::System::IStructuredSave
/// interface, so callers that only have a native IStructuredSave-consuming API (e.g.
/// WBFL::FEA2D::Model::Save) can still be driven by a COM caller (e.g. the Fem2d and
/// LBAM COM facades, which must keep accepting IStructuredSave2* from their own frozen
/// public interfaces). Non-owning: the wrapped COM pointer's lifetime is the caller's
/// responsibility, matching how it's already handed in by every existing call site.
class ComStructuredSaveAdapter : public WBFL::System::IStructuredSave
{
public:
   explicit ComStructuredSaveAdapter(IStructuredSave2* psave) : m_psave(psave) {}
   virtual ~ComStructuredSaveAdapter() = default;

   virtual void BeginUnit(LPCTSTR name, Float64 version = 0) override
   {
      HRESULT hr = m_psave->BeginUnit(CComBSTR(name), version);
      if (FAILED(hr)) ThrowOnFailure(hr);
   }

   virtual void EndUnit() override
   {
      HRESULT hr = m_psave->EndUnit();
      if (FAILED(hr)) ThrowOnFailure(hr);
   }

   virtual Float64 GetVersion() override
   {
      Float64 v;
      HRESULT hr = m_psave->get_Version(&v);
      if (FAILED(hr)) ThrowOnFailure(hr);
      return v;
   }

   virtual Float64 GetTopVersion() override
   {
      Float64 v;
      HRESULT hr = m_psave->get_TopVersion(&v);
      if (FAILED(hr)) ThrowOnFailure(hr);
      return v;
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

private:
   CComPtr<IStructuredSave2> m_psave;

   void PutVariantProperty(LPCTSTR name, const VARIANT& v)
   {
      HRESULT hr = m_psave->put_Property(CComBSTR(name), v);
      if (FAILED(hr)) ThrowOnFailure(hr);
   }

   [[noreturn]] void ThrowOnFailure(HRESULT hr) const
   {
      UNREFERENCED_PARAMETER(hr);
      THROW(WBFL::System::XStructuredSave, BadWrite);
   }
};

/// Adapts a COM IStructuredLoad2 pointer to the native WBFL::System::IStructuredLoad
/// interface. See ComStructuredSaveAdapter for the rationale. Non-owning.
///
/// IStructuredLoad2 has no COM equivalent for GetParentVersion/GetParentUnit/
/// GetStateDump/GetUnit - these throw WBFL::System::XStructuredLoad(UserDefined,...)
/// if called. WBFL::FEA2D::Model's persistence code never calls them.
class ComStructuredLoadAdapter : public WBFL::System::IStructuredLoad
{
public:
   explicit ComStructuredLoadAdapter(IStructuredLoad2* pload) : m_pload(pload) {}
   virtual ~ComStructuredLoadAdapter() = default;

   virtual bool BeginUnit(LPCTSTR name) override
   {
      HRESULT hr = m_pload->BeginUnit(CComBSTR(name));
      if (FAILED(hr)) ThrowOnFailure(hr);
      return true;
   }

   virtual bool EndUnit() override
   {
      VARIANT_BOOL eb;
      HRESULT hr = m_pload->EndUnit(&eb);
      if (FAILED(hr)) ThrowOnFailure(hr);
      return eb == VARIANT_TRUE;
   }

   virtual Float64 GetVersion() override
   {
      Float64 v;
      HRESULT hr = m_pload->get_Version(&v);
      if (FAILED(hr)) ThrowOnFailure(hr);
      return v;
   }

   virtual Float64 GetParentVersion() override
   {
      THROW(WBFL::System::XStructuredLoad, UserDefined);
   }

   virtual std::_tstring GetParentUnit() override
   {
      THROW(WBFL::System::XStructuredLoad, UserDefined);
   }

   virtual Float64 GetTopVersion() override
   {
      Float64 v;
      HRESULT hr = m_pload->get_TopVersion(&v);
      if (FAILED(hr)) ThrowOnFailure(hr);
      return v;
   }

   virtual bool Property(LPCTSTR name, std::_tstring* pvalue) override
   {
      CComVariant v;
      GetVariantProperty(name, VT_BSTR, &v);
      *pvalue = v.bstrVal != nullptr ? std::_tstring(v.bstrVal) : std::_tstring();
      return true;
   }

   virtual bool Property(LPCTSTR name, Float64* pvalue) override
   {
      CComVariant v;
      GetVariantProperty(name, VT_R8, &v);
      *pvalue = v.dblVal;
      return true;
   }

   virtual bool Property(LPCTSTR name, Int16* pvalue) override
   {
      CComVariant v;
      GetVariantProperty(name, VT_I2, &v);
      *pvalue = v.iVal;
      return true;
   }

   virtual bool Property(LPCTSTR name, Uint16* pvalue) override
   {
      CComVariant v;
      GetVariantProperty(name, VT_UI2, &v);
      *pvalue = v.uiVal;
      return true;
   }

   virtual bool Property(LPCTSTR name, Int32* pvalue) override
   {
      CComVariant v;
      GetVariantProperty(name, VT_I4, &v);
      *pvalue = v.lVal;
      return true;
   }

   virtual bool Property(LPCTSTR name, Uint32* pvalue) override
   {
      CComVariant v;
      GetVariantProperty(name, VT_UI4, &v);
      *pvalue = v.ulVal;
      return true;
   }

   virtual bool Property(LPCTSTR name, Int64* pvalue) override
   {
      CComVariant v;
      GetVariantProperty(name, VT_I8, &v);
      *pvalue = v.llVal;
      return true;
   }

   virtual bool Property(LPCTSTR name, Uint64* pvalue) override
   {
      CComVariant v;
      GetVariantProperty(name, VT_UI8, &v);
      *pvalue = v.ullVal;
      return true;
   }

   virtual bool Property(LPCTSTR name, LONG* pvalue) override
   {
      CComVariant v;
      GetVariantProperty(name, VT_I4, &v);
      *pvalue = v.lVal;
      return true;
   }

   virtual bool Property(LPCTSTR name, ULONG* pvalue) override
   {
      CComVariant v;
      GetVariantProperty(name, VT_UI4, &v);
      *pvalue = v.ulVal;
      return true;
   }

   virtual bool Property(LPCTSTR name, bool* pvalue) override
   {
      CComVariant v;
      GetVariantProperty(name, VT_BOOL, &v);
      *pvalue = (v.boolVal == VARIANT_TRUE);
      return true;
   }

   virtual bool Eof() const override
   {
      VARIANT_BOOL eb;
      HRESULT hr = m_pload->EndOfStorage(&eb);
      if (FAILED(hr)) ThrowOnFailure(hr);
      return eb == VARIANT_TRUE;
   }

   virtual std::_tstring GetStateDump() const override
   {
      return std::_tstring(_T("(COM-backed IStructuredLoad2 - no state dump available)"));
   }

   virtual std::_tstring GetUnit() const override
   {
      THROW(WBFL::System::XStructuredLoad, UserDefined);
   }

private:
   CComPtr<IStructuredLoad2> m_pload;

   bool GetVariantProperty(LPCTSTR name, VARTYPE vt, VARIANT* pv) const
   {
      VariantInit(pv);
      pv->vt = vt;
      HRESULT hr = m_pload->get_Property(CComBSTR(name), pv);
      if (FAILED(hr)) ThrowOnFailure(hr);
      return true;
   }

   [[noreturn]] void ThrowOnFailure(HRESULT hr) const
   {
      UNREFERENCED_PARAMETER(hr);
      THROW(WBFL::System::XStructuredLoad, BadRead);
   }
};
