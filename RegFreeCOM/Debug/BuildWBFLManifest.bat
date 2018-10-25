SET MTPATH=c:\program files\microsoft sdks\windows\v6.0a\bin\

REM *** Make a single master manifest for all of WBFL

"%MTPATH%\mt.exe" -manifest WBFLCogo.dll.manifest WBFLCore.dll.manifest WBFLDManip.dll.manifest WBFLDManipTools.dll.manifest WBFLFem2d.dll.manifest WBFLGenericBridge.dll.manifest WBFLGenericBridgeTools.dll.manifest WBFLGeometry.dll.manifest WBFLLBAM.dll.manifest WBFLLBAMAnalysis.dll.manifest WBFLLBAMAnalysisUtility.dll.manifest WBFLLBAMLiveLoader.dll.manifest WBFLLBAMLoadCombiner.dll.manifest WBFLLBAMUtility.dll.manifest WBFLLibrary.dll.manifest WBFLLoading.dll.manifest WBFLRCCapacity.dll.manifest WBFLReportManagerAgent.dll.manifest WBFLSections.dll.manifest WBFLTools.dll.manifest WBFLTransactions.dll.manifest WBFLUnitServer.dll.manifest -out:WBFL.manifest
