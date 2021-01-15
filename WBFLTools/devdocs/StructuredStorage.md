Structured Storage {#WBFL_Tools_StructuredStorage}
========================
The WBFL Tools Structured Storage services provides a convienent method of storing complex data.

Structured Storage arranges data in hierarchical storage units of key-value pairs. Storage units can be versioned to facilitate future changes and backwards compatiblity with previously created storage files.

The following pseudo-code example illustrates how to add structured storage capabilities to your objects.

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
/// NOTE: This should be a fully implemented COM object. Details are omitted for simplicity
class myClass : public IStructuredStorage2
{
public:
   // implementate the IStructuredStorage2 interface
   HRESULT Save(IStructuredSave2* pSave) override;
   HRESULT Load(IStructuredLoad2* pLoad) override;
   
   // value1 and value2 are the original data for this class
   Float64 value1;
   Int32 value2;
   
   // sometime after the class was originally developed, more data was added
   // value3 is the new data
   std::_tstring value3;
};

HRESULT myClass::Save(IStructuredSave2* pSave)
{
   // Create a containing storage unit for this class' data. Call it MyClassData
   // Because we added new data after this class was originally created, use a version number of 2.0
   // As you can imagine, before the class was updated, the version was 1.0
   pSave->BeginUnit(CComBSTR("MyClassData"),2.0);
      // save the original data
      pSave->put_Property(CComBSTR("Value1"),CComVariant(value1));
      pSave->put_Property(CComBSTR("Value2"),CComVariant(value2));

      // save the new data. 
      pSave->put_Property(CComBSTR("Value3"),CComVariant(value3));
   pSave->EndUnit(); // End of MyClassData unit
   return S_OK;
}

HRESULT myClass::Load(IStructuredLoad2* pLoad)
{
   USES_CONVERSION;

   // Start the load process by calling BeginUnit
   pLoad->BeginUnit(CComBSTR("MyClassData"));
   
   // since there have been multiple versions of the MyClassData unit, get the version
   // number so we know what is being loaded
   Float64 version;
   pLoad->get_Version(&version);
   
   CComVariant var;
   pLoad->get_Property(CComBSTR("Value1"),&var);
   value1 = var.dblVal;
         
   pLoad->get_Property(CComBSTR("Value2"),&var);
   value2 = var.lVal;
   
   if(1.0 < version)
   {
      // If version is greater than 1, we have version 2 data.
	  // Read "Value3" from the storage
      pLoad->put_Property(CComBSTR("Value3"),&var);
      value3 = OLE2T(var.bstr);
   } 
   else
   {
      // The storage was created with the original version of this class so the "Value3"
	  // property wasn't storaged. Assign a default to value3.
      value3 = _T("DefaultValue");
   }
   pLoad->EndUnit(); // End of MyClassData unit
   return S_OK;
}

void main()
{
   myClass m1;
   m1.Value1 = 1.0
   m1.Value2 = 2;
   m1.Value3 = "Three";
   
   // Create the storage saver
   CComPtr<IStructuredSave2> saver;
   saver.CoCreateInstance(CLSID_StructuredSave2);
   
   // Open the storage
   saver->Open("MyClassFile.txt");
   
   // Save object m1.
   CComQIPtr<IStructuredStorage2> storage(m1);
   storage->Save(saver);
   
   // close the storage
   saver->Close();
   
   
   //Create the storage loader
   CComPtr<IStructuredLoad2> loader;
   loader.CoCreateInstance(CLSID_StructuredLoad2);
   
   // Open the storage
   loader->Open("MyClassFile.txt");
   
   // Load the object
   myClass m2;
   
   CComQIPtr<IStructuredStorage2> storage(m2);
   storage->Load(loader);
   
   // close the storage
   loader->Close();
   
   ATLASSERT(m1 == m2);
}

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
