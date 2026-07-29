///////////////////////////////////////////////////////////////////////
// COGOTest - Test Driver for Coordinate Geometry Library
// Copyright � 1999-2026  Washington State Department of Transportation
//                        Bridge and Structures Office
///////////////////////////////////////////////////////////////////////
// CogoTestUtil.cpp
#include "pch.h"

bool TestIObjectSafety(REFCLSID rclsid, REFIID riid, DWORD dwSupportedOptions)
{
   CComPtr<IObjectSafety> safety;
   safety.CoCreateInstance(rclsid);

   if (safety == nullptr)
      return false;

   DWORD dwSupported, dwEnabled;
   safety->GetInterfaceSafetyOptions(riid, &dwSupported, &dwEnabled);
   return dwSupported == dwSupportedOptions;
}
