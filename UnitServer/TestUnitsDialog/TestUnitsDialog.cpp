// TestUnitsDialog.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "HelpID.h"
#include <WBFLTest.h>

int main(int argc, char* argv[])
{
   ::CoInitialize(NULL);
   {
      CComPtr<IUnitModeController> umc;
      umc.CoCreateInstance( CLSID_UnitModeController );

      umc->put_UnitMode(umSI);
      
      // Set unit mode to US when the dialog is displayed
      TRY_TEST( umc->ShowSelectionDialog(), S_OK );
      UnitModeType um;
      umc->get_UnitMode(&um);
      TRY_TEST( um, umUS );

      // Press the Help Button to see if the help file is displayed
      TRY_TEST(umc->ShowSelectionDialogEx(CComBSTR("HelpTest.chm"),IDH_HELPTEST),S_OK);
   }
   ::CoUninitialize();
	return 0;
}
