// ModuleSetup.cpp : COM type library GUID definitions and module-wide test setup/teardown.
//
// The WBFLRCCapacity/WBFLGeometry/WBFLTools/WBFLUnitServer _i.c files define the CLSID/IID GUID
// constants used throughout this project. They must be compiled into exactly one translation
// unit (matching the pattern used by the legacy RCCapacityTest console app, where they were
// included directly in the file containing main()).
//
// This DLL is loaded into a foreign host process (e.g. testhost.exe under Visual Studio Test
// Explorer / vstest.console), which has no knowledge of WBFL's COM classes: they are normally
// activated either via traditional (machine-wide, admin-required) registry registration, or via
// a regfree-COM manifest embedded in a controlling EXE (as the legacy RCCapacityTest.exe console
// app does). Neither applies to a DLL hosted inside an arbitrary test-runner process. Instead,
// this file registers the small set of CLSIDs this test project actually uses (including
// transitive dependencies from other WBFL DLLs, e.g. CLSID_UnitServer) under
// HKEY_CURRENT_USER\Software\Classes\CLSID, which requires no elevation and is torn down again in
// TEST_MODULE_CLEANUP, so it leaves no permanent trace on the machine.

#include "pch.h"
#include "CppUnitTest.h"

#include <initguid.h>
#include <WBFLRCCapacity_i.c>
#include <WBFLGeometry_i.c>
#include <WBFLTools_i.c>
#include <WBFLUnitServer_i.c>

#include <string>
#include <vector>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace
{
   // Every CLSID a ported test in this project instantiates, and which DLL implements it
   // (including WBFL coclasses that other coclasses depend on internally, e.g. RCBeam's
   // FinalConstruct CoCreateInstance's CLSID_UnitServer from WBFLUnitServer.dll). Add an entry
   // here whenever a newly-ported test needs a coclass that isn't already registered.
   struct ComClassEntry
   {
      const CLSID* clsid;
      const wchar_t* name;
      const wchar_t* dllName;
   };

   const ComClassEntry g_classesToRegister[] = {
      { &CLSID_RCSolution, L"RCSolution", L"WBFLRCCapacity.dll" },
      { &CLSID_RCBeam, L"RCBeam", L"WBFLRCCapacity.dll" },
      { &CLSID_RebarModel, L"RebarModel", L"WBFLRCCapacity.dll" },
      { &CLSID_PSPowerFormula, L"PSPowerFormula", L"WBFLRCCapacity.dll" },
      { &CLSID_UnconfinedConcrete, L"UnconfinedConcrete", L"WBFLRCCapacity.dll" },
      { &CLSID_UHPConcrete, L"UHPConcrete", L"WBFLRCCapacity.dll" },
      { &CLSID_RCBeam2, L"RCBeam2", L"WBFLRCCapacity.dll" },
      { &CLSID_RCBeam2Ex, L"RCBeam2Ex", L"WBFLRCCapacity.dll" },
      { &CLSID_RoundColumn, L"RoundColumn", L"WBFLRCCapacity.dll" },
      { &CLSID_UnitServer, L"UnitServer", L"WBFLUnitServer.dll" },
      { &CLSID_Point2d, L"Point2d", L"WBFLGeometry.dll" },
      { &CLSID_Point2dCollection, L"Point2dCollection", L"WBFLGeometry.dll" },
      { &CLSID_Rect, L"Rect", L"WBFLGeometry.dll" },
      { &CLSID_PrecastBeam, L"PrecastBeam", L"WBFLGeometry.dll" },
      { &CLSID_Rect2d, L"Rect2d", L"WBFLGeometry.dll" },
      { &CLSID_DblArray, L"DblArray", L"WBFLTools.dll" },
      { &CLSID_NLSolver, L"NLSolver", L"WBFLRCCapacity.dll" },
      { &CLSID_PCISolver, L"PCISolver", L"WBFLRCCapacity.dll" },
      { &CLSID_LRFDSolver, L"LRFDSolver", L"WBFLRCCapacity.dll" },
      { &CLSID_LRFDSolver2, L"LRFDSolver2", L"WBFLRCCapacity.dll" },
      { &CLSID_LFDSolver, L"LFDSolver", L"WBFLRCCapacity.dll" },
      { &CLSID_MixedSolver, L"MixedSolver", L"WBFLRCCapacity.dll" },
      { &CLSID_GeneralSection, L"GeneralSection", L"WBFLRCCapacity.dll" },
      { &CLSID_GeneralSectionSolver, L"GeneralSectionSolver", L"WBFLRCCapacity.dll" },
      { &CLSID_CrackedSectionSolver, L"CrackedSectionSolver", L"WBFLRCCapacity.dll" },
      { &CLSID_Circle, L"Circle", L"WBFLGeometry.dll" },
      { &CLSID_Point3d, L"Point3d", L"WBFLGeometry.dll" },
      { &CLSID_Plane3d, L"Plane3d", L"WBFLGeometry.dll" },
      { &CLSID_Point2d, L"Point2d", L"WBFLGeometry.dll" },
      { &CLSID_Line2d, L"Line2d", L"WBFLGeometry.dll" },
      { &CLSID_GeomUtil, L"GeomUtil", L"WBFLGeometry.dll" },
      { &CLSID_UnkArray, L"UnkArray", L"WBFLTools.dll" },
      { &CLSID_WBFLErrorLog, L"WBFLErrorLog", L"WBFLTools.dll" },
      { &CLSID_CompositeSectionEx, L"CompositeSectionEx", L"WBFLGeometry.dll" },
      { &CLSID_MomentCurvatureSolver, L"MomentCurvatureSolver", L"WBFLRCCapacity.dll" },
      { &CLSID_MomentCapacitySolver, L"MomentCapacitySolver", L"WBFLRCCapacity.dll" },
      { &CLSID_GenericShape, L"GenericShape", L"WBFLGeometry.dll" },
      { &CLSID_Vector2d, L"Vector2d", L"WBFLGeometry.dll" },
      { &CLSID_NUBeam, L"NUBeam", L"WBFLGeometry.dll" },
      { &CLSID_Size2d, L"Size2d", L"WBFLGeometry.dll" },
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
   ::CoInitialize(nullptr);

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
