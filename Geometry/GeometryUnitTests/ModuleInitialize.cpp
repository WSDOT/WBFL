// ModuleInitialize.cpp : module-wide test setup/teardown.
//
// This DLL is loaded into a foreign host process (e.g. testhost.exe under Visual
// Studio Test Explorer / vstest.console), which has no knowledge of WBFL's COM
// classes: they are normally activated either via traditional (machine-wide,
// admin-required) registry registration, or via a regfree-COM manifest embedded
// in a controlling EXE (as the legacy GeometryTest.exe console app does). Neither
// applies to a DLL hosted inside an arbitrary test-runner process. Instead, this
// file registers the small set of CLSIDs this test project actually uses
// (including transitive dependencies from other WBFL DLLs) under
// HKEY_CURRENT_USER\Software\Classes\CLSID, which requires no elevation and is
// torn down again in TEST_MODULE_CLEANUP, so it leaves no permanent trace on the
// machine.
//
// GeometryTest's ported tests have no connection-point event sinks, so this uses
// plain STA CoInitialize, following RCCapacityUnitTests\ModuleSetup.cpp /
// CogoUnitTests\ModuleInitialize.cpp rather than Fem2dUnitTests's MTA variant.

#include "pch.h"

#include <string>
#include <vector>

namespace
{
   // Every CLSID a ported test in this project instantiates. All from WBFLGeometry.dll
   // unless noted. Add an entry here whenever a newly-ported test needs a coclass that
   // isn't already registered.
   struct ComClassEntry
   {
      const CLSID* clsid;
      const wchar_t* name;
      const wchar_t* dllName;
   };

   const ComClassEntry g_classesToRegister[] = {
      { &CLSID_Size2d,             L"Size2d",             L"WBFLGeometry.dll" },
      { &CLSID_Point2d,            L"Point2d",            L"WBFLGeometry.dll" },
      { &CLSID_Rect2d,             L"Rect2d",             L"WBFLGeometry.dll" },
      { &CLSID_Point2dCollection,  L"Point2dCollection",  L"WBFLGeometry.dll" },
      { &CLSID_Vector2d,           L"Vector2d",           L"WBFLGeometry.dll" },
      { &CLSID_LineSegment2d,      L"LineSegment2d",      L"WBFLGeometry.dll" },
      { &CLSID_Line2d,             L"Line2d",             L"WBFLGeometry.dll" },
      { &CLSID_Size3d,             L"Size3d",             L"WBFLGeometry.dll" },
      { &CLSID_Vector3d,           L"Vector3d",           L"WBFLGeometry.dll" },
      { &CLSID_Point3d,            L"Point3d",            L"WBFLGeometry.dll" },
      { &CLSID_Point3dCollection,  L"Point3dCollection",  L"WBFLGeometry.dll" },
      { &CLSID_Plane3d,            L"Plane3d",            L"WBFLGeometry.dll" },
      { &CLSID_LineSegment3d,      L"LineSegment3d",      L"WBFLGeometry.dll" },
      { &CLSID_CoordinateXform2d,  L"CoordinateXform2d",  L"WBFLGeometry.dll" },
      { &CLSID_CoordinateXform3d,  L"CoordinateXform3d",  L"WBFLGeometry.dll" },
      { &CLSID_GeomUtil,           L"GeomUtil",           L"WBFLGeometry.dll" },
      { &CLSID_ShapeProperties,    L"ShapeProperties",    L"WBFLGeometry.dll" },
      { &CLSID_GenericShape,       L"GenericShape",       L"WBFLGeometry.dll" },
      { &CLSID_CompositeShapeItem, L"CompositeShapeItem", L"WBFLGeometry.dll" },
      { &CLSID_CompositeShape,     L"CompositeShape",     L"WBFLGeometry.dll" },
      { &CLSID_PolyShape,          L"PolyShape",          L"WBFLGeometry.dll" },
      { &CLSID_Circle,             L"Circle",             L"WBFLGeometry.dll" },
      { &CLSID_Rect,               L"Rect",               L"WBFLGeometry.dll" },
      { &CLSID_CircularSegment,    L"CircularSegment",    L"WBFLGeometry.dll" },
      { &CLSID_Triangle,           L"Triangle",           L"WBFLGeometry.dll" },
      { &CLSID_BulbTee,            L"BulbTee",            L"WBFLGeometry.dll" },
      { &CLSID_BulbTee2,           L"BulbTee2",           L"WBFLGeometry.dll" },
      { &CLSID_PrecastBeam,        L"PrecastBeam",        L"WBFLGeometry.dll" },
      { &CLSID_PrecastBeam2,       L"PrecastBeam2",       L"WBFLGeometry.dll" },
      { &CLSID_NUBeam,             L"NUBeam",             L"WBFLGeometry.dll" },
      { &CLSID_UBeam,              L"UBeam",              L"WBFLGeometry.dll" },
      { &CLSID_UBeam2,             L"UBeam2",             L"WBFLGeometry.dll" },
      { &CLSID_MultiWeb,           L"MultiWeb",           L"WBFLGeometry.dll" },
      { &CLSID_MultiWeb2,          L"MultiWeb2",          L"WBFLGeometry.dll" },
      { &CLSID_PlateGirder,        L"PlateGirder",        L"WBFLGeometry.dll" },
      { &CLSID_TrafficBarrier,     L"TrafficBarrier",     L"WBFLGeometry.dll" },
      { &CLSID_VoidedSlab,         L"VoidedSlab",         L"WBFLGeometry.dll" },
      { &CLSID_VoidedSlab2,        L"VoidedSlab2",        L"WBFLGeometry.dll" },
      { &CLSID_BoxBeam,            L"BoxBeam",            L"WBFLGeometry.dll" },
      { &CLSID_DeckedSlabBeam,     L"DeckedSlabBeam",     L"WBFLGeometry.dll" },
      { &CLSID_NUDeckedIBeam,      L"NUDeckedIBeam",      L"WBFLGeometry.dll" },
      { &CLSID_PCIDeckedIBeam,     L"PCIDeckedIBeam",     L"WBFLGeometry.dll" },
      { &CLSID_BeamShapeFactory,   L"BeamShapeFactory",   L"WBFLGeometry.dll" },
      { &CLSID_MassProperties,     L"MassProperties",     L"WBFLGeometry.dll" },
      { &CLSID_ElasticProperties,  L"ElasticProperties",  L"WBFLGeometry.dll" },
      { &CLSID_CompositeBeam,      L"CompositeBeam",      L"WBFLGeometry.dll" },
      { &CLSID_CompositeSectionEx, L"CompositeSectionEx", L"WBFLGeometry.dll" },
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
