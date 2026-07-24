#include "pch.h"
#include "CppUnitTest.h"
#include <System\Checks.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

TEST_MODULE_INITIALIZE(ModuleInitialize)
{
	// Library's "GetLibraryManager() == nullptr" and RemoveAll() outstanding-reference
	// diagnostics (and any other WARN()-based diagnostic) default to popping up a blocking
	// message box (Diagnostics::bWarnPopup defaults to true). Disable that here so the tests
	// never get stuck waiting on a dialog; the OutputDebugString-based message still fires normally.
	DIAG_WARNPOPUP(false);
}
