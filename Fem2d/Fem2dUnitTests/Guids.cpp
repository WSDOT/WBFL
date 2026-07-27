// Guids.cpp
//
// Single translation unit that instantiates the GUID definitions for the
// COM interfaces this suite consumes (IFem2dModel etc. and IStructuredStorage2
// etc.), exactly as F:\ARP\WBFL\Fem2d\Test\Test.cpp does for the legacy harness.
#include "pch.h"

#include <initguid.h>
#include <WBFLFem2d_i.c>
#include <WBFLTools_i.c>
