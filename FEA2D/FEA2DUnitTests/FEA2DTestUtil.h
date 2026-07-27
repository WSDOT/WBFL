///////////////////////////////////////////////////////////////////////
// FEA2D - Two-dimensional Finite Element Analysis Engine
// Copyright � 1999-2026  Washington State Department of Transportation
//                        Bridge and Structures Office
///////////////////////////////////////////////////////////////////////
// FEA2DTestUtil.h
//
// Small assertion helpers for the FEA2DUnitTests suite. Unlike
// Fem2dTestUtil.h's ASSERT_HR/ASSERT_MC/ASSERT_LC (which existed to
// unwrap COM HRESULTs and drain the COM event-sink fixture), FEA2D
// reports failures by throwing XFEA2D, and has no event mechanism at all
// (see the design note in Include\FEA2D\Joint.h - that's facade-only
// territory for Phase 4) - so all that's needed here is a plain
// value-equality helper and a "this call must throw XFEA2D with this
// specific ReasonCode" helper.

#pragma once

// value comparison via == rather than Assert::AreEqual, since several
// enum class / ID typedef types here don't have a ToString<T>
// specialization CppUnitTestFramework needs to render a failure message
#define ASSERT_EQ(actual, expected) Assert::IsTrue((actual) == (expected))
#define ASSERT_TRUE(expr) Assert::IsTrue((expr))
#define ASSERT_FALSE(expr) Assert::IsFalse((expr))

// Runs expr (a statement) and asserts it throws WBFL::FEA2D::XFEA2D with
// the given ReasonCode. Fails if expr doesn't throw, or throws the wrong
// ReasonCode.
#define ASSERT_THROWS(expr, reasonCode)                                         \
   do                                                                           \
   {                                                                            \
      bool _fea2d_threw = false;                                                \
      try                                                                       \
      {                                                                         \
         expr;                                                                  \
      }                                                                         \
      catch (const WBFL::FEA2D::XFEA2D& _fea2d_e)                               \
      {                                                                         \
         _fea2d_threw = true;                                                   \
         Assert::IsTrue(_fea2d_e.GetReasonCode() == (reasonCode));              \
      }                                                                         \
      Assert::IsTrue(_fea2d_threw);                                             \
   } while (0)
