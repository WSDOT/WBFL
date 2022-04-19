.\RegFreeCOM\x64\Release\CogoTest.exe
.\RegFreeCOM\x64\Release\CoreTest.exe
.\RegFreeCOM\x64\Release\Fem2dTest.exe
.\RegFreeCOM\x64\Release\GenericBridgeTest.exe
.\RegFreeCOM\x64\Release\GenericBridgeToolsTest.exe
.\RegFreeCOM\x64\Release\GeometryTest.exe
.\RegFreeCOM\x64\Release\LBAMAnalysisTest.exe
.\RegFreeCOM\x64\Release\LBAMLiveLoadTest.exe

%SYSTEMROOT%\System32\regsvr32.exe /s .\RegFreeCOM\x64\Release\BogusCombinationContext.dll
.\RegFreeCOM\x64\Release\LBAMLoadCombinerTest.exe
%SYSTEMROOT%\System32\regsvr32.exe /u /s .\RegFreeCOM\x64\Release\BogusCombinationContext.dll

.\RegFreeCOM\x64\Release\LBAMTest.exe
.\RegFreeCOM\x64\Release\LoadingTest.exe
.\RegFreeCOM\x64\Release\RCCapacityTest.exe
.\RegFreeCOM\x64\Release\ToolsTest.exe
.\RegFreeCOM\x64\Release\UnitServerTest.exe