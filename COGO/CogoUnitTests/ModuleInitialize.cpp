// ModuleInitialize.cpp : module-wide test setup/teardown.
//
// This DLL is loaded into a foreign host process (e.g. testhost.exe under Visual
// Studio Test Explorer / vstest.console), which has no knowledge of WBFL's COM
// classes: they are normally activated either via traditional (machine-wide,
// admin-required) registry registration, or via a regfree-COM manifest embedded
// in a controlling EXE (as the legacy CogoTest.exe console app does). Neither
// applies to a DLL hosted inside an arbitrary test-runner process. Instead, this
// file registers the small set of CLSIDs this test project actually uses
// (including transitive dependencies from other WBFL DLLs) under
// HKEY_CURRENT_USER\Software\Classes\CLSID, which requires no elevation and is
// torn down again in TEST_MODULE_CLEANUP, so it leaves no permanent trace on the
// machine.
//
// CogoTest's ported tests have no connection-point event sinks (unlike Fem2d's),
// so this uses plain STA CoInitialize, following RCCapacityUnitTests\ModuleSetup.cpp
// rather than Fem2dUnitTests\ModuleInitialize.cpp's MTA variant.

#include "pch.h"

#include <string>
#include <vector>

namespace
{
   // Every CLSID a ported test in this project instantiates, and which DLL implements
   // it (including WBFL coclasses that other coclasses depend on internally). Add an
   // entry here whenever a newly-ported test needs a coclass that isn't already
   // registered.
   struct ComClassEntry
   {
      const CLSID* clsid;
      const wchar_t* name;
      const wchar_t* dllName;
   };

   const ComClassEntry g_classesToRegister[] = {
      { &CLSID_Angle,          L"Angle",          L"WBFLCogo.dll" },
      { &CLSID_Direction,      L"Direction",      L"WBFLCogo.dll" },
      { &CLSID_Station,        L"Station",        L"WBFLCogo.dll" },
      { &CLSID_CircularCurve,  L"CircularCurve",  L"WBFLCogo.dll" },
      { &CLSID_CompoundCurve,  L"CompoundCurve",  L"WBFLCogo.dll" },
      { &CLSID_TransitionCurve,L"TransitionCurve",L"WBFLCogo.dll" },
      { &CLSID_VerticalCurve,  L"VerticalCurve",  L"WBFLCogo.dll" },
      { &CLSID_CubicSpline,    L"CubicSpline",    L"WBFLCogo.dll" },
      { &CLSID_Alignment,      L"Alignment",      L"WBFLCogo.dll" },
      { &CLSID_Profile,        L"Profile",        L"WBFLCogo.dll" },
      { &CLSID_ProfilePoint,   L"ProfilePoint",   L"WBFLCogo.dll" },
      { &CLSID_CogoModel,      L"CogoModel",      L"WBFLCogo.dll" },
      { &CLSID_CogoEngine,     L"CogoEngine",     L"WBFLCogo.dll" },
      { &CLSID_PathSegment,    L"PathSegment",    L"WBFLCogo.dll" },
      { &CLSID_ProfileSegment, L"ProfileSegment", L"WBFLCogo.dll" },
      { &CLSID_Surface,        L"Surface",        L"WBFLCogo.dll" },
      { &CLSID_Superelevation, L"Superelevation", L"WBFLCogo.dll" },
      { &CLSID_Widening,       L"Widening",       L"WBFLCogo.dll" },
      { &CLSID_AngleDisplayUnitFormatter,     L"AngleDisplayUnitFormatter",     L"WBFLCogo.dll" },
      { &CLSID_DirectionDisplayUnitFormatter, L"DirectionDisplayUnitFormatter", L"WBFLCogo.dll" },
      { &CLSID_BridgeGeometry, L"BridgeGeometry", L"WBFLCogo.dll" },
      { &CLSID_SinglePierLineFactory,            L"SinglePierLineFactory",            L"WBFLCogo.dll" },
      { &CLSID_AlignmentOffsetLayoutLineFactory, L"AlignmentOffsetLayoutLineFactory", L"WBFLCogo.dll" },
      { &CLSID_SimpleGirderLineFactory,          L"SimpleGirderLineFactory",          L"WBFLCogo.dll" },
      { &CLSID_UniformSpacingLayoutLineFactory,  L"UniformSpacingLayoutLineFactory",  L"WBFLCogo.dll" },
      { &CLSID_EqualSpacingDiaphragmLineFactory, L"EqualSpacingDiaphragmLineFactory", L"WBFLCogo.dll" },
      { &CLSID_SingleDiaphragmLineFactory,       L"SingleDiaphragmLineFactory",       L"WBFLCogo.dll" },
      { &CLSID_ThroughPointDiaphragmLineFactory, L"ThroughPointDiaphragmLineFactory", L"WBFLCogo.dll" },
      { &CLSID_SimpleDeckBoundaryFactory,        L"SimpleDeckBoundaryFactory",        L"WBFLCogo.dll" },
      { &CLSID_DblArray,       L"DblArray",       L"WBFLTools.dll" },
      { &CLSID_Point2d,        L"Point2d",        L"WBFLGeometry.dll" },
      { &CLSID_Point2dCollection, L"Point2dCollection", L"WBFLGeometry.dll" },
      { &CLSID_Size2d,         L"Size2d",         L"WBFLGeometry.dll" },
      { &CLSID_Vector2d,       L"Vector2d",       L"WBFLGeometry.dll" },
      { &CLSID_Line2d,         L"Line2d",         L"WBFLGeometry.dll" },
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
