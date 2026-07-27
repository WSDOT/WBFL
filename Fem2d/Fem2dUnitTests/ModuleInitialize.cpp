///////////////////////////////////////////////////////////////////////
// Fem2D - Two-dimensional Beam Analysis Engine
// Copyright © 1999-2026  Washington State Department of Transportation
//                        Bridge and Structures Office
///////////////////////////////////////////////////////////////////////
// ModuleInitialize.cpp
//
// This DLL is loaded into a foreign host process (e.g. testhost.exe under
// Visual Studio Test Explorer / vstest.console), which has no knowledge of
// WBFL's COM classes: they are normally activated either via traditional
// (machine-wide, admin-required) registry registration, or via a regfree-COM
// manifest embedded in a controlling EXE. Neither applies to a DLL hosted
// inside an arbitrary test-runner process. Instead, this file registers the
// small set of CLSIDs this test project actually uses under
// HKEY_CURRENT_USER\Software\Classes\CLSID, which requires no elevation and
// is torn down again in TEST_MODULE_CLEANUP, so it leaves no permanent trace
// on the machine. Mirrors RCCapacity\RCCapacityUnitTests\ModuleSetup.cpp.
#include "pch.h"

#include <string>
#include <vector>

namespace
{
   // Every CLSID this project's tests instantiate via CoCreateInstance, and
   // which DLL implements it. Add an entry here whenever a newly-ported test
   // needs a coclass that isn't already registered.
   struct ComClassEntry
   {
      const CLSID* clsid;
      const wchar_t* name;
      const wchar_t* dllName;
   };

   const ComClassEntry g_classesToRegister[] = {
      { &CLSID_Fem2dModel,      L"Fem2dModel",      L"WBFLFem2d.dll" },
      { &CLSID_StructuredSave2, L"StructuredSave2",  L"WBFLTools.dll" },
      { &CLSID_StructuredLoad2, L"StructuredLoad2",  L"WBFLTools.dll" },
      { &CLSID_IDArray,         L"IDArray",          L"WBFLTools.dll" }, // CJoint::get_Members' internal CoCreateInstance
   };

   std::vector<std::wstring> g_registeredClsidKeys;

   void RegisterComClass(const CLSID& clsid, const std::wstring& dllPath)
   {
      wchar_t clsidStr[64];
      ::StringFromGUID2(clsid, clsidStr, 64);

      std::wstring clsidKeyPath = L"Software\\Classes\\CLSID\\" + std::wstring(clsidStr);
      std::wstring inprocKeyPath = clsidKeyPath + L"\\InprocServer32";

      HKEY hInprocKey = nullptr;
      LONG result = ::RegCreateKeyExW(HKEY_CURRENT_USER, inprocKeyPath.c_str(), 0, nullptr, 0, KEY_WRITE, nullptr, &hInprocKey, nullptr);
      Assert::AreEqual((LONG)ERROR_SUCCESS, result, (L"Failed to create registry key for " + clsidKeyPath).c_str());

      ::RegSetValueExW(hInprocKey, nullptr, 0, REG_SZ, reinterpret_cast<const BYTE*>(dllPath.c_str()), static_cast<DWORD>((dllPath.size() + 1) * sizeof(wchar_t)));

      const wchar_t threadingModel[] = L"Apartment";
      ::RegSetValueExW(hInprocKey, L"ThreadingModel", 0, REG_SZ, reinterpret_cast<const BYTE*>(threadingModel), sizeof(threadingModel));

      ::RegCloseKey(hInprocKey);

      g_registeredClsidKeys.push_back(clsidKeyPath);
   }
}

TEST_MODULE_INITIALIZE(ModuleInitialize)
{
   // MTA (not CoInitialize's STA): this test host thread never pumps messages,
   // and CModel's Apartment-threaded COM object uses connection points
   // (AtlAdvise), which need a real message pump to service cross-apartment
   // calls if the calling thread is itself an STA. Staying MTA lets COM host
   // the object in its own internally-managed STA instead, avoiding a deadlock.
   ::CoInitializeEx(nullptr, COINIT_MULTITHREADED);

   HMODULE hModule = nullptr;
   ::GetModuleHandleExW(GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS, reinterpret_cast<LPCWSTR>(&ModuleInitialize), &hModule);

   wchar_t modulePath[MAX_PATH];
   ::GetModuleFileNameW(hModule, modulePath, MAX_PATH);

   std::wstring dir(modulePath);
   dir = dir.substr(0, dir.find_last_of(L'\\')); // ...\RegFreeCOM\x64\Debug

   for (const auto& entry : g_classesToRegister)
   {
      RegisterComClass(*entry.clsid, dir + L"\\" + entry.dllName);
   }
}

TEST_MODULE_CLEANUP(ModuleCleanup)
{
   for (const auto& clsidKeyPath : g_registeredClsidKeys)
   {
      ::RegDeleteTreeW(HKEY_CURRENT_USER, clsidKeyPath.c_str());
   }

   ::CoUninitialize();
}
