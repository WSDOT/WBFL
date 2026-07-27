///////////////////////////////////////////////////////////////////////
// FEA2D - Two-dimensional Finite Element Analysis Engine
// Copyright � 1999-2026  Washington State Department of Transportation
//                        Bridge and Structures Office
///////////////////////////////////////////////////////////////////////
// pch.h
//
// Phase 2 mirror of the Phase 0 Fem2dUnitTests baseline suite (see
// C:\Users\BriceR\.claude\plans\in-wbfl-there-is-cheerful-matsumoto.md).
// Builds WBFL::FEA2D::Model directly - no COM, no ATL, no CoCreateInstance.
// Each test case here corresponds 1:1 to a Fem2dUnitTests test case built
// against the identical input model, verified to the same numeric
// tolerance; where the two suites disagree, that's a real regression in
// the FEA2D port, not a test-authoring difference.

#pragma once

#include "CppUnitTest.h"

#include <FEA2D\Model.h>
#include <FEA2D\XFEA2D.h>
#include <MathEx.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace WBFL::FEA2D;

#include "FEA2DTestUtil.h"
