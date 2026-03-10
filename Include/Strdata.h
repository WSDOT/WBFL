#ifndef INCLUDED_STRDATA_H_
#define INCLUDED_STRDATA_H_

#include <vector>
#include <stack>
#include <memory>

interface IProgress;
interface IStructuredSave;
interface IStructuredLoad;

enum StrDataType
{
   SDT_NODE             = -1,
   SDT_I2               =  0,
   SDT_UI2              =  1,
   SDT_I4               =  2,
   SDT_UI4              =  3,
   SDT_R8               =  4,
   SDT_LPTSTR           =  5,
   SDT_LPSTR            =  6,
   SDT_LPOLESTR         =  7,
   SDT_STDSTRING        =  8,
   SDT_BSTR             =  9,
   SDT_BOOL             = 10
};



template <class T>
HRESULT CallbackProc(IStructuredSave*,IStructuredLoad*, std::shared_ptr<IEAFProgress>,T* obj);

template <class T>
   struct StrStorageData
   {
      typedef typename HRESULT (*CallbackProc)(IStructuredSave*,IStructuredLoad*, std::shared_ptr<IEAFProgress>,T*);

      StrStorageData():
      m_Version(-1),
      m_DataType(Prop),
      m_SDT(SDT_I2),
      m_pData(0),
      m_pObj(0), 
      m_pfn(0)
      {
      }

      ~StrStorageData()
      {
      }

      StrStorageData(const StrStorageData& rOther)
      {
         m_Name        = rOther.m_Name;
         m_Description = rOther.m_Description;
         m_Version     = rOther.m_Version;
         m_DataType    = rOther.m_DataType;
         m_SDT         = rOther.m_SDT;
         m_pData       = rOther.m_pData;
         m_pObj        = rOther.m_pObj;
         m_pfn         = rOther.m_pfn;
         m_Children    = rOther.m_Children;
      }

      StrStorageData& operator=(const StrStorageData& rOther)
      {
         m_Name        = rOther.m_Name;
         m_Description = rOther.m_Description;
         m_Version     = rOther.m_Version;
         m_DataType    = rOther.m_DataType;
         m_SDT         = rOther.m_SDT;
         m_pData       = rOther.m_pData;
         m_pObj        = rOther.m_pObj;
         m_pfn         = rOther.m_pfn;
         m_Children    = rOther.m_Children;

         return *this;
      }

      std::_tstring m_Name;
      std::_tstring m_Description;
      double m_Version;
      enum DataType { Unit, Prop, Callback } m_DataType;
      StrDataType m_SDT;
      void* m_pData;
      T* m_pObj;
      CallbackProc m_pfn;
      std::vector<StrStorageData<T> > m_Children;
   };

template <class T>
class StrStorageDataMap
{
public:
   StrStorageDataMap(const StrStorageDataMap* pOther);
   StrStorageDataMap(LPCTSTR desc,LPCTSTR root,double version);
   void BeginUnit(LPCTSTR desc,LPCTSTR unit,double version);
   void Property(LPCTSTR prop,StrDataType vt,void* ptr);
   void Callback(typename StrStorageData<T>::CallbackProc pfn,T* obj);
   void EndUnit();
   double GetVersion();

   HRESULT Save(IStructuredSave* pSave, std::shared_ptr<IEAFProgress> pProgress);
   HRESULT Load(IStructuredLoad* pLoad, std::shared_ptr<IEAFProgress> pProgress);

private:

   StrStorageData<T> m_Root;
   StrStorageData<T>* m_pCurrent;
   std::stack<StrStorageData<T>*> m_Prev;

   HRESULT Save( IStructuredSave* pSave, StrStorageData<T>* pData, std::shared_ptr<IEAFProgress> pProgress);
   HRESULT Load(IStructuredLoad* pSave, StrStorageData<T>* pData, std::shared_ptr<IEAFProgress> pProgress);
};

#define DECLARE_STRSTORAGEMAP(cls) \
   std::unique_ptr<StrStorageDataMap<cls> > _strstgmap; \
   bool _LoadMap();

#endif // INCLUDED_STRDATA_H_