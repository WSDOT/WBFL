#ifndef INCLUDED_SUPPORTUNITS_H_
#define INCLUDED_SUPPORTUNITS_H_

#include <WBFLUnitServer.h>

template <const GUID* plibid>
class ATL_NO_VTABLE ISupportDisplayUnitsImpl : public ISupportDisplayUnits
{
public:
   public:
      STDMETHOD(putref_DisplayUnitMgr)(IDisplayUnitMgr* mgr)
      {
         m_DisplayUnitMgr = mgr;
         return S_OK;
      }

      STDMETHOD(get_DisplayUnitMgr)(IDisplayUnitMgr **mgr)
      {
         *mgr = m_DisplayUnitMgr;
         (*mgr)->AddRef();
         return S_OK;
      }

   protected:
      CComPtr<IDisplayUnitMgr> m_DisplayUnitMgr;
};

template <const GUID* plibid>
class ATL_NO_VTABLE ISupportUnitSystemImpl : public ISupportUnitSystem
{
public:
   public:
      STDMETHOD(putref_UnitSystem)(IUnitSystem* unitSystem)
      {
         m_UnitSystem = unitSystem;
         return S_OK;
      }

      STDMETHOD(get_UnitSystem)(IUnitSystem **unitSystem)
      {
         *unitSystem = m_UnitSystem;
         (*unitSystem)->AddRef();
         return S_OK;
      }

   protected:
      CComPtr<IUnitSystem> m_UnitSystem;
};

template <const GUID* plibid>
class ISupportDocUnitSystemImpl : public ISupportDocUnitSystem
{
public:
   public:
      STDMETHOD(putref_UnitSystem)(IDocUnitSystem* unitSystem)
      {
         m_UnitSystem = unitSystem;
         return S_OK;
      }

      STDMETHOD(get_UnitSystem)(IDocUnitSystem **unitSystem)
      {
         *unitSystem = m_UnitSystem;
         (*unitSystem)->AddRef();
         return S_OK;
      }

   protected:
      CComPtr<IDocUnitSystem> m_UnitSystem;
};

#endif // INCLUDED_SUPPORTUNITS_H_