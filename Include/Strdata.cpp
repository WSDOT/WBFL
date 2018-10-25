#include <StrData.h>
#include <WBFLCore.h>
#include <tchar.h>
#include <comdef.h>

static const VARTYPE vartype[] = { VT_I2,
                                   VT_UI2,
                                   VT_I4, 
                                   VT_UI4,
                                   VT_R8,
                                   VT_BSTR,
                                   VT_BSTR,
                                   VT_BSTR,
                                   VT_BSTR,
                                   VT_BSTR,
                                   VT_BOOL };

#define get_vartype(x) vartype[x]

template <class T>
StrStorageDataMap<T>::StrStorageDataMap(LPCTSTR desc,LPCTSTR root,double version)
{
   m_Root.m_Name = root;
   m_Root.m_Description = desc;
   m_Root.m_Version = version;
   m_Root.m_DataType = StrStorageData<T>::Unit;
   m_Root.m_SDT = SDT_NODE;
   m_Root.m_pData = 0;
   m_pCurrent = &m_Root;
}

template <class T>
StrStorageDataMap<T>::StrStorageDataMap(const StrStorageDataMap* pOther)
{
   if ( pOther )
   {
      m_Root = pOther->m_Root;
   }
   m_pCurrent = &m_Root;
}

template <class T>
void StrStorageDataMap<T>::BeginUnit(LPCTSTR desc,LPCTSTR unit,double version)
{
   StrStorageData<T> node;
   node.m_Name = unit;
   node.m_Description = desc;
   node.m_Version = version;
   node.m_DataType = StrStorageData<T>::Unit;
   node.m_SDT = SDT_NODE;
   node.m_pData = 0;
   m_Root.m_Children.push_back( node );
   m_Prev.push( m_pCurrent );
   m_pCurrent = &m_Root.m_Children[m_Root.m_Children.size()-1];
}

template <class T>
void StrStorageDataMap<T>::Property(LPCTSTR propName,StrDataType sdt,void* ptr)
{
   StrStorageData<T> prop;
   prop.m_Name = propName;
   prop.m_DataType = StrStorageData<T>::Prop;
   prop.m_SDT = sdt;
   prop.m_pData = ptr;
   m_pCurrent->m_Children.push_back( prop );
}

template <class T>
void StrStorageDataMap<T>::Callback(typename StrStorageData<T>::CallbackProc pfn,T* obj)
{
   StrStorageData<T> prop;
   prop.m_DataType = StrStorageData<T>::Callback;
   prop.m_pData = 0;
   prop.m_pObj = obj;
   prop.m_pfn = pfn;
   m_pCurrent->m_Children.push_back( prop );
}

template <class T>
void StrStorageDataMap<T>::EndUnit()
{
   m_pCurrent = m_Prev.top();
   m_Prev.pop();
}

template <class T>
double StrStorageDataMap<T>::GetVersion()
{
   return m_pCurrent->m_Version;
}

template <class T>
HRESULT StrStorageDataMap<T>::Save( IStructuredSave* pSave,IProgress* pProgress)
{
   CHECK( m_pCurrent = &m_Root );
   CHECK( m_Prev.empty() );
   return Save( pSave, &m_Root, pProgress );
}

template <class T>
HRESULT StrStorageDataMap<T>::Save( IStructuredSave* pSave, StrStorageData<T>* pData, IProgress* pProgress)
{
   HRESULT hr;

   if ( pData->m_DataType == StrStorageData<T>::Prop )
   {
      VARIANT var;
      ::VariantInit( &var );
      var.vt = get_vartype( pData->m_SDT );
      switch( pData->m_SDT )
      {
      case SDT_I2:
         var.iVal = *(short*)(pData->m_pData);
         hr = pSave->put_Property( pData->m_Name.c_str(), var );
         break;

      case SDT_UI2:
         var.uiVal = *(unsigned short*)(pData->m_pData);
         hr = pSave->put_Property( pData->m_Name.c_str(), var );
         break;

      case SDT_I4:
         var.lVal = *(long*)(pData->m_pData );
         hr = pSave->put_Property( pData->m_Name.c_str(), var );
         break;

      case SDT_UI4:
         var.ulVal = *(unsigned long*)(pData->m_pData );
         hr = pSave->put_Property( pData->m_Name.c_str(), var );
         break;

      case SDT_R8:
         var.dblVal = *(double*)(pData->m_pData );
         hr = pSave->put_Property( pData->m_Name.c_str(), var );
         break;

      case SDT_LPTSTR:
         var.bstrVal = _bstr_t((LPTSTR)pData->m_pData);
         hr = pSave->put_Property( pData->m_Name.c_str(), var );
         break;

      case SDT_LPSTR:
         var.bstrVal = _bstr_t(*(LPSTR*)(pData->m_pData));
         hr = pSave->put_Property( pData->m_Name.c_str(), var );
         break;

      case SDT_LPOLESTR:
         var.bstrVal = _bstr_t((LPOLESTR)(pData->m_pData));
         hr = pSave->put_Property( pData->m_Name.c_str(), var );
         break;

      case SDT_STDSTRING:
         var.bstrVal = _bstr_t( ((std::_tstring*)pData->m_pData)->c_str() );
         hr = pSave->put_Property( pData->m_Name.c_str(), var );
         break;

      case SDT_BSTR:
         var.bstrVal = _bstr_t( *(BSTR*)(pData->m_pData) );
         hr = pSave->put_Property( pData->m_Name.c_str(), var );
         break;

      case SDT_BOOL:
         var.boolVal = *(bool*)(pData->m_pData) ? VARIANT_TRUE : VARIANT_FALSE;
         hr = pSave->put_Property( pData->m_Name.c_str(), var );
         break;

      default:
         // all other kinds not supported
         CHECK(false);
         break;
      }
   ::VariantClear( &var );
   }
   else if ( pData->m_DataType == StrStorageData<T>::Callback )
   {
      hr = (*pData->m_pfn)(pSave,0,pProgress,pData->m_pObj);
   }
   else
   {
      if ( pProgress )
      {
         std::_tstring msg(_T("Saving "));
         msg += pData->m_Description;
         pProgress->UpdateMessage( msg.c_str() );
      }

      hr = pSave->BeginUnit( pData->m_Name.c_str(), pData->m_Version );
      if ( FAILED(hr) )
         return hr;

      std::vector<StrStorageData<T> >::iterator i;
      for ( i = pData->m_Children.begin(); i != pData->m_Children.end(); i++ )
      {
         StrStorageData<T>& child_data = *i;
         hr = Save( pSave, &child_data, pProgress );
         if ( FAILED(hr) )
            return hr;
      }

      hr = pSave->EndUnit();
      if ( FAILED(hr) )
         return hr;
   }

   return hr;
}


template <class T>
HRESULT StrStorageDataMap<T>::Load(IStructuredLoad* pLoad,IProgress* pProgress)
{
   CHECK( m_pCurrent = &m_Root );
   CHECK( m_Prev.empty() );
   return Load( pLoad, &m_Root, pProgress );
}

template <class T>
HRESULT StrStorageDataMap<T>::Load( IStructuredLoad* pLoad, StrStorageData<T>* pData,IProgress* pProgress)
{
   HRESULT hr=S_OK;
   if ( pData->m_DataType == StrStorageData<T>::Prop )
   {
      VARIANT var;
      var.vt = get_vartype(pData->m_SDT);
      switch( pData->m_SDT )
      {
      case SDT_I2:
         hr = pLoad->get_Property( pData->m_Name.c_str(), &var );
         *(short*)(pData->m_pData) = var.iVal;
         break;

      case SDT_UI2:
         hr = pLoad->get_Property( pData->m_Name.c_str(), &var );
         *(short*)(pData->m_pData) = var.uiVal;
         break;

      case SDT_I4:
         hr = pLoad->get_Property( pData->m_Name.c_str(), &var );
         *(long*)(pData->m_pData) = var.lVal;
         break;

      case SDT_UI4:
         hr = pLoad->get_Property( pData->m_Name.c_str(), &var );
         *(unsigned long*)(pData->m_pData) = var.ulVal;
         break;

      case SDT_R8:
         hr = pLoad->get_Property( pData->m_Name.c_str(), &var );
         *(double*)(pData->m_pData) = var.dblVal;
         break;

      case SDT_LPTSTR:
         {
         hr = pLoad->get_Property( pData->m_Name.c_str(), &var );
         _bstr_t bstr(var.bstrVal);
         pData->m_pData = (TCHAR*)new TCHAR[bstr.length()];
         _tcscpy_s((TCHAR*)(pData->m_pData),bstr.length(),bstr);
         }
         break;

      case SDT_LPSTR:
         {
         hr = pLoad->get_Property( pData->m_Name.c_str(), &var );
         _bstr_t bstr(var.bstrVal);
         pData->m_pData = (TCHAR*)new TCHAR[bstr.length()];
         _tcscpy_s((TCHAR*)(pData->m_pData),bstr.length(),bstr);
         }
         break;

      case SDT_LPOLESTR:
         {
         hr = pLoad->get_Property( pData->m_Name.c_str(), &var );
         HRESULT len = ::SysStringLen(var.bstrVal);
         *(LPOLESTR*)(pData->m_pData) = (LPOLESTR)CoTaskMemAlloc(sizeof(OLECHAR)*(len+1));
	   	wcscpy_s(*(LPOLESTR*)(pData->m_pData),len,var.bstrVal);
         (*(LPOLESTR*)(pData->m_pData))[len] = L'\0'; // Null terminator
         }
         break;

      case SDT_STDSTRING:
         {
         hr = pLoad->get_Property( pData->m_Name.c_str(), &var );
         std::_tstring* pStr = new std::_tstring( _bstr_t(var.bstrVal) );
         *(std::_tstring*)(pData->m_pData) = *pStr;
         delete pStr;
         }
         break;

      case SDT_BSTR:
         hr = pLoad->get_Property( pData->m_Name.c_str(), &var );
         *(BSTR*)(pData->m_pData) = var.bstrVal;
         break;

      case SDT_BOOL:
         hr = pLoad->get_Property( pData->m_Name.c_str(), &var );
         *(bool*)(pData->m_pData) = (var.boolVal == VARIANT_TRUE ? true : false );
         break;

      default:
         // all other kinds not supported
         CHECK(false);
         break;
      }
   }
   else if ( pData->m_DataType == StrStorageData<T>::Callback )
   {
      hr = (*pData->m_pfn)(0,pLoad,pProgress,pData->m_pObj);
      if ( FAILED(hr) )
         return hr;
   }
   else
   {
      if ( pProgress )
      {
         std::_tstring msg(_T("Loading "));
         msg += pData->m_Description;
         pProgress->UpdateMessage( msg.c_str() );
      }

      hr = pLoad->BeginUnit( pData->m_Name.c_str() );
      if ( FAILED(hr) )
         return hr;

      // check version
      double file_ver;
      pLoad->get_Version(&file_ver);
      double prog_ver = pData->m_Version;
      if (prog_ver < file_ver)
         return STRLOAD_E_BADVERSION;

      std::vector<StrStorageData<T> >::iterator i;
      for ( i = pData->m_Children.begin(); i != pData->m_Children.end(); i++ )
      {
         StrStorageData<T>& child_data = *i;
         hr = Load( pLoad, &child_data, pProgress );
         if ( FAILED(hr) )
            return hr;
      }
      hr = pLoad->EndUnit();
      if ( FAILED(hr) )
         return hr;
   }

   return hr;
}

#define BEGIN_STRSTORAGEMAP(cls,name,version) \
                                            bool cls::_LoadMap() { \
                                            _strstgmap = std::auto_ptr<StrStorageDataMap<cls> >(new StrStorageDataMap<cls>(TEXT(""),(name),(version)));
#define BEGIN_UNIT(name,desc,version) _strstgmap->BeginUnit((desc),(name),(version));
#define PROPERTY(name,type,var) _strstgmap->Property((name),(type),(void*)(&var));
#define PROP_CALLBACK(fn) _strstgmap->Callback( &(fn), this );
#define END_UNIT _strstgmap->EndUnit();
#define END_STRSTORAGEMAP return true; }


#define STRSTG_LOAD(_hr,_ptr,_prog) _LoadMap(); (_hr) = _strstgmap->Load( (_ptr), (_prog) );
#define STRSTG_SAVE(_hr,_ptr,_prog) _LoadMap(); (_hr) = _strstgmap->Save( (_ptr), (_prog) );
