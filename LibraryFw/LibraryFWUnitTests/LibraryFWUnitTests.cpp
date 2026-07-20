#include "pch.h"
#include "CppUnitTest.h"
#include "TestEntry.h"
#include <System/System.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace WBFL::Library;

namespace LibraryFWUnitTests
{
	TEST_CLASS(LibraryFW)
	{
	public:
		
		TEST_METHOD(Test)
		{
         // create some libraries, fill them with data to save
         using LibType = Library<TestEntry, 0>;
         LibType* psav1 = new LibType(_T("TEST_LIB1"), _T("Test Library 1"));
         TestEntry entry;
         Assert::IsTrue(entry.GetRefCount() == 0);
         Assert::IsTrue(psav1->IsEmpty());
         psav1->AddEntry(entry, _T("Item1"));
         psav1->NewEntry(_T("Item2"));
         psav1->NewEntry(_T("Item3"));
         psav1->CloneEntry(_T("Item3"), _T("Item4"));

         LibType* psav2 = new LibType(_T("TEST_LIB2"), _T("Test Library 2"));
         psav2->NewEntry(_T("Item21"));
         psav2->NewEntry(_T("Item22"));
         psav2->NewEntry(_T("Item23"));

         // add libraries to be saved to a library manager
         LibraryManager saveman;
         saveman.AddLibrary(psav1);
         saveman.AddLibrary(psav2);

         // test some library functions
         Assert::IsTrue(!psav1->IsEmpty());
         Assert::IsTrue(psav1->GetCount() == 4);
         KeyListType list;
         psav1->KeyList(list);
         Assert::IsTrue(list.size() == 4);
         Assert::IsTrue(psav1->GetDisplayName() == _T("Test Library 1"));
         Assert::IsTrue(psav1->GetIdName() == _T("TEST_LIB1"));
         std::_tstring tmp;
         const TestEntry* pmat = psav1->LookupEntry(_T("Item1"));
         Assert::IsNotNull(pmat);
         psav1->GetEntryKey(*pmat, tmp);
         Assert::IsTrue(tmp == _T("Item1"));
         Assert::IsTrue(&saveman == psav1->GetLibraryManager());
         Assert::IsTrue(psav1->IsEntry(_T("Item1")));
         Assert::IsTrue(!psav1->IsEntry(_T("BogusItem")));
         Assert::IsTrue(psav1->RemoveEntry(_T("Item1")) == ILibrary::EntryRemoveOutcome::Referenced);
         pmat->Release();
         Assert::IsTrue(psav1->RemoveEntry(_T("Item1")) == ILibrary::EntryRemoveOutcome::Ok);
         Assert::IsTrue(psav1->GetCount() == 3);
         Assert::IsTrue(psav1->RemoveEntry(_T("BogusItem")) == ILibrary::EntryRemoveOutcome::NotFound);
         Assert::IsTrue(psav1->RenameEntry(_T("Item2"), _T("RenamedItem2")));
         Assert::IsTrue(psav1->IsEntry(_T("RenamedItem2")));
         Assert::IsTrue(!psav1->IsEntry(_T("Item2")));
         psav1->SetDisplayName(_T("Test Library 1 - Renamed"));
         Assert::IsTrue(psav1->GetDisplayName() == _T("Test Library 1 - Renamed"));
         entry.SetName(_T("New Name"));
         entry.SetValue(123.456);
         Assert::IsTrue(psav1->UpdateEntry(entry, _T("Item3")));
         const TestEntry* pmat3 = psav1->LookupEntry(_T("Item3"));
         Assert::IsNotNull(pmat3);
         Assert::IsTrue(pmat3->GetValue() == 123.456);
         Assert::IsTrue(pmat3->GetRefCount() == 1);
         pmat3->Release();

         // save manager and libraries and close stream
         {
            WBFL::System::FileStream os;
            if (!os.open(_T("TestLib.xml"), false)) exit(1);
            WBFL::System::StructuredSaveXml save;
            save.BeginSave(&os);
            saveman.SaveMe(&save);
            save.EndSave();
         }

         // create a new library manager with empty libraries to load
         LibType* pload1 = new LibType(_T("TEST_LIB1"), _T("Test Library 1")); // note id's must match above
         LibType* pload2 = new LibType(_T("TEST_LIB2"), _T("Test Library 2"));
         LibraryManager loadman;
         loadman.AddLibrary(pload1);
         loadman.AddLibrary(pload2);

         // load it up
         try
         {
            // test loading
            WBFL::System::FileStream is;

            if (!is.open(_T("TestLib.xml"), true)) exit(1);
            WBFL::System::StructuredLoadXml load;
            load.BeginLoad(&is);
            loadman.LoadMe(&load);
            load.EndLoad();
         }
         catch (const WBFL::System::XStructuredLoad& rex)
         {
            std::_tcout << rex.GetErrorMessage() << std::endl;
         }
      }

      TEST_METHOD(BackPointerBasic)
      {
         using LibType = Library<TestEntry, 0>;
         auto* pLib = new LibType(_T("BP_LIB1"), _T("BackPointer Lib 1"));
         LibraryManager mgr;
         mgr.AddLibrary(pLib);

         pLib->NewEntry(_T("X"));
         const LibraryEntry* pEntry = pLib->GetEntry(_T("X"));
         Assert::IsNotNull(pEntry);
         Assert::IsNotNull(pEntry->GetLibrary());
         Assert::IsTrue(pEntry->GetLibrary() == static_cast<const ILibrary*>(pLib));
      }

      TEST_METHOD(BackPointerFailsSafeAfterCloneAndLibraryDestruction)
      {
         using LibType = Library<TestEntry, 0>;
         std::unique_ptr<LibraryEntry> clone;
         {
            auto* pLib = new LibType(_T("BP_LIB2"), _T("BackPointer Lib 2"));
            LibraryManager mgr;
            mgr.AddLibrary(pLib);

            pLib->NewEntry(_T("Y"));
            clone = pLib->CreateEntryClone(_T("Y"));
            Assert::IsNotNull(clone.get());
            // still valid while the source library/manager is alive
            Assert::IsNotNull(clone->GetLibrary());
         } // mgr (and pLib) destroyed here - clone outlives its source library

         // must fail safe (nullptr), not dangle, now that the source library is gone
         Assert::IsNull(clone->GetLibrary());
      }

      TEST_METHOD(BackPointerNullIfEntryAddedBeforeLibraryRegistered)
      {
         // documented limitation: weak_from_this() is permanently expired for
         // entries added before the owning Library is itself registered via
         // LibraryManager::AddLibrary()
         using LibType = Library<TestEntry, 0>;
         auto* pLib = new LibType(_T("BP_LIB3"), _T("BackPointer Lib 3"));
         pLib->NewEntry(_T("Pre")); // added BEFORE AddLibrary

         LibraryManager mgr;
         mgr.AddLibrary(pLib);

         pLib->NewEntry(_T("Post")); // added AFTER AddLibrary

         const LibraryEntry* pPre = pLib->GetEntry(_T("Pre"));
         const LibraryEntry* pPost = pLib->GetEntry(_T("Post"));
         Assert::IsNotNull(pPre);
         Assert::IsNotNull(pPost);
         Assert::IsNull(pPre->GetLibrary());
         Assert::IsNotNull(pPost->GetLibrary());
      }

      TEST_METHOD(CopyConstructDoesNotInheritSourceRefCount)
      {
         TestEntry src;
         src.AddRef();
         src.AddRef();
         Assert::IsTrue(src.GetRefCount() == 2);

         TestEntry copy(src);
         Assert::IsTrue(copy.GetRefCount() == 0);   // a copy is not yet referenced by anyone
         Assert::IsTrue(src.GetRefCount() == 2);     // source is unaffected by being copied from

         src.Release();
         src.Release();
      }

      TEST_METHOD(AssignmentLeavesRefCountUnchangedOnBothSides)
      {
         TestEntry a;
         a.AddRef();
         a.AddRef();

         TestEntry b;
         b.AddRef();

         b = a;

         Assert::IsTrue(b.GetRefCount() == 1);   // unchanged by the assignment
         Assert::IsTrue(a.GetRefCount() == 2);   // unchanged by the assignment

         a.Release();
         a.Release();
         b.Release();
      }
	};
}
