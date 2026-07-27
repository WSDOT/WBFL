///////////////////////////////////////////////////////////////////////
// Fem2D - Two-dimensional Beam Analysis Engine
// Copyright � 1999-2026  Washington State Department of Transportation
//                        Bridge and Structures Office
///////////////////////////////////////////////////////////////////////
// Fem2dTestUtil.h
//
// Shared test infrastructure for the Fem2dUnitTests suite. This is the
// CppUnitTestFramework analogue of the legacy Fem2d\Test\TestHarness.h/.cpp:
// - CFem2dTestEventSink implements IFem2dModelEvents and records whether
//   OnModelChanged/OnLoadingChanged fired, exactly like CTestHarness did.
// - Fem2dModelFixture creates a Fem2dModel via CoCreateInstance, advises
//   the sink, and tears both down automatically (RAII replacement for
//   CTestHarness::CreateModel()/ReleaseModel()).
// - ASSERT_HR/ASSERT_EQ/ASSERT_TRUE/ASSERT_MC/ASSERT_LC are the
//   CppUnitTestFramework equivalents of the old TRY_TEST/TRY_TEST_HR/
//   TRY_TEST_B/TRY_TEST_MC/TRY_TEST_LC macros (see WBFLTest.h and
//   Fem2d\Test\TestHarness.h), preserving the same semantics: TRY_TEST(x,y)
//   compared x==y, so ASSERT_EQ does the same rather than relying on
//   Assert::AreEqual's type-specific overloads (several of the COM enum
//   types used here have no ToString<T> specialization).

#pragma once

class ATL_NO_VTABLE CFem2dTestEventSink :
   public CComObjectRootEx<CComSingleThreadModel>,
   public IFem2dModelEvents
{
public:
   CFem2dTestEventSink() : m_bModelChangedState(false), m_bLoadingChangedState(false), m_dwCookie(0) {}

BEGIN_COM_MAP(CFem2dTestEventSink)
   COM_INTERFACE_ENTRY(IFem2dModelEvents)
END_COM_MAP()

   STDMETHOD(OnModelChanged)() override { m_bModelChangedState = true; return S_OK; }
   STDMETHOD(OnLoadingChanged)(LoadCaseIDType Loading) override { m_bLoadingChangedState = true; return S_OK; }

   bool PassedModelChangedTest() { bool b = m_bModelChangedState; m_bModelChangedState = false; return b; }
   bool PassedLoadingChangedTest() { bool b = m_bLoadingChangedState; m_bLoadingChangedState = false; return b; }

   bool m_bModelChangedState;
   bool m_bLoadingChangedState;
   DWORD m_dwCookie;
};

// Creates a fresh IFem2dModel via CoCreateInstance(CLSID_Fem2dModel) and advises
// a CFem2dTestEventSink to it, mirroring CTestHarness::CreateModel(). Both the
// model and the sink are released automatically when the fixture goes out of scope.
class Fem2dModelFixture
{
public:
   Fem2dModelFixture();
   ~Fem2dModelFixture();

   Fem2dModelFixture(const Fem2dModelFixture&) = delete;
   Fem2dModelFixture& operator=(const Fem2dModelFixture&) = delete;

   bool PassedModelChangedTest();
   bool PassedLoadingChangedTest();

   CComPtr<IFem2dModel> Model;

private:
   CComObject<CFem2dTestEventSink>* m_pSink;
};

// ASSERT_EQ(actual,expected) mirrors the legacy TRY_TEST(x,y) macro: it compares
// with operator== rather than Assert::AreEqual, since several COM enum/typedef
// types used throughout these tests (Fem2dJointReleaseType, VARIANT_BOOL, HRESULT
// error codes, etc.) don't have a CppUnitTestFramework ToString<T> specialization.
#define ASSERT_EQ(actual, expected) Assert::IsTrue((actual) == (expected), L#actual L" != " L#expected)

// ASSERT_HR(x) mirrors TRY_TEST_HR(x): the HRESULT-returning expression must be S_OK.
#define ASSERT_HR(expr) ASSERT_EQ((HRESULT)(expr), S_OK)

// ASSERT_TRUE(x) mirrors TRY_TEST_B(x): x (typically an IsEqual(...) comparison) must be true.
#define ASSERT_TRUE(expr) Assert::IsTrue((expr), L#expr)

// ASSERT_MC(fixture,expr) mirrors TRY_TEST_MC(x): expr must return S_OK AND must fire
// IFem2dModelEvents::OnModelChanged on fixture.
#define ASSERT_MC(fixture, expr) \
   do { ASSERT_HR(expr); Assert::IsTrue((fixture).PassedModelChangedTest(), L"Expected OnModelChanged event: " L#expr); } while (0)

// ASSERT_LC(fixture,expr) mirrors TRY_TEST_LC(x): expr must return S_OK AND must fire
// IFem2dModelEvents::OnLoadingChanged on fixture.
#define ASSERT_LC(fixture, expr) \
   do { ASSERT_HR(expr); Assert::IsTrue((fixture).PassedLoadingChangedTest(), L"Expected OnLoadingChanged event: " L#expr); } while (0)
