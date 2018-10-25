#ifndef INCLUDED_TXNMGRIMPL_H_
#define INCLUDED_TXNMGRIMPL_H_

#include <WBFLTransactions.h>

class ISupportTransactionsImpl : public ISupportTransactions
{
public:
   STDMETHOD(putref_TransactionMgr)(ITransactionMgr* txnMgr)
   {
//      ATLTRACE("ISupportTransactionsImpl::putref_TransactionMgr (%p)\n",txnMgr);
      m_TxnMgr = txnMgr;
      return S_OK;
   }
   
   ~ISupportTransactionsImpl()
   {
//      ATLTRACE("ISupportTransactionsImpl::~ISupportTransactionsImpl\n");
      if ( m_TxnMgr )
         m_TxnMgr.Release();
   }

protected:
   CComPtr<ITransactionMgr> m_TxnMgr;
};

///////////////////////////////////////////////////////////////////////////////////////////////////
// Default implementation for ITransaction
template <class T,const VARIANT_BOOL bUndoable,const VARIANT_BOOL bRepeatable,const GUID* plibid>
class ATL_NO_VTABLE CTransactionImpl :
	public CComObjectRootEx<CComSingleThreadModel>,
	public ITransaction
{
public:
   CTransactionImpl()
	{
	}

   void Init(T* pTarget,const char* strName)
   {
      m_pTarget = pTarget;
      m_bstrName = strName;
   }

   void FinalRelease()
   {
      USES_CONVERSION;
      ATLTRACE("CTransactionImpl::FinalRelease (%s)\n",OLE2A(m_bstrName));
      m_pTarget = 0;
   }

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CTransactionImpl)
	COM_INTERFACE_ENTRY(ITransaction)
END_COM_MAP()

private:
   CComBSTR m_bstrName;

protected:
   T* m_pTarget;

// ITransaction
public:
   STDMETHOD(Execute)()
   {
      return E_NOTIMPL;
   }

	STDMETHOD(Undo)()
   {
      return E_NOTIMPL;
   }

   STDMETHOD(get_Name)(/*[out, retval]*/ BSTR *pVal)
   {
      *pVal = m_bstrName.Copy();
      return S_OK;
   }

	STDMETHOD(get_IsUndoable)(/*[out, retval]*/ VARIANT_BOOL *pVal)
   {
      *pVal = bUndoable;
      return S_OK;
   }

	STDMETHOD(get_IsRepeatable)(/*[out, retval]*/ VARIANT_BOOL *pVal)
   {
      *pVal = bRepeatable;
      return S_OK;
   }
};

///////////////////////////////////////////////////////////////////////////////////////////////////
// Transaction for editing a COM object
template <class T,class InterfaceType,const VARIANT_BOOL bUndoable,const VARIANT_BOOL bRepeatable,const GUID* plibid>
class ATL_NO_VTABLE CEditObjectTransaction:
public CTransactionImpl<T,bUndoable,bRepeatable,plibid>
{
public:
   typedef HRESULT (*PutPropFunc)(T* pThis,InterfaceType* obj);

   void Init(T* pTarget,const char* strName,PutPropFunc putFunc,InterfaceType* oldObj,InterfaceType* newObj)
   {
      CTransactionImpl<T,bUndoable,bRepeatable,plibid>::Init(pTarget,strName);
      m_PutFunc = putFunc;
      m_NewObj = newObj;
      m_OldObj = oldObj;
   }

   STDMETHOD(Execute)()
   {
      return m_PutFunc(m_pTarget,m_NewObj);
   }

	STDMETHOD(Undo)()
   {
      return m_PutFunc(m_pTarget,m_OldObj);
   }

protected:
   PutPropFunc m_PutFunc;
   CComPtr<InterfaceType> m_NewObj;
   CComPtr<InterfaceType> m_OldObj;
};

///////////////////////////////////////////////////////////////////////////////////////////////////
// Transaction for editing a simple value
template <class T,class ValueType,const VARIANT_BOOL bUndoable,const VARIANT_BOOL bRepeatable,const GUID* plibid>
class ATL_NO_VTABLE CEditValueTransaction:
public CTransactionImpl<T,bUndoable,bRepeatable,plibid>
{
public:
   typedef HRESULT (*PutPropFunc)(T* pThis,ValueType newVal);

void Init(T* pTarget,const char* strName,PutPropFunc putFunc,ValueType oldVal,ValueType newVal)
   {
      CTransactionImpl<T,bUndoable,bRepeatable,plibid>::Init(pTarget,strName);
      m_PutFunc = putFunc;
      m_NewVal = newVal;
      m_OldVal = oldVal;
   }

   STDMETHOD(Execute)()
   {
      return m_PutFunc(m_pTarget,m_NewVal);
   }

	STDMETHOD(Undo)()
   {
      return m_PutFunc(m_pTarget,m_OldVal);
   }

protected:
   PutPropFunc m_PutFunc;
   ValueType m_NewVal;
   ValueType m_OldVal;
};

///////////////////////////////////////////////////////////////////////////////////////////////////
// Transaction for editing 2 simple values
template <class T,class ValueType1,class ValueType2,const VARIANT_BOOL bUndoable,const VARIANT_BOOL bRepeatable,const GUID* plibid>
class ATL_NO_VTABLE CEditValueTransaction2:
public CTransactionImpl<T,bUndoable,bRepeatable,plibid>
{
public:
   typedef HRESULT (*PutPropFunc)(T* pThis,ValueType1 newVal1,ValueType2 newVal2);

void Init(T* pTarget,const char* strName,PutPropFunc putFunc,ValueType1 oldVal1,ValueType1 newVal1,ValueType2 oldVal2,ValueType2 newVal2)
   {
      CTransactionImpl<T,bUndoable,bRepeatable,plibid>::Init(pTarget,strName);
      m_PutFunc = putFunc;
      m_NewVal1 = newVal1;
      m_OldVal1 = oldVal1;
      m_NewVal2 = newVal2;
      m_OldVal2 = oldVal2;
   }

   STDMETHOD(Execute)()
   {
      return m_PutFunc(m_pTarget,m_NewVal1,m_NewVal2);
   }

	STDMETHOD(Undo)()
   {
      return m_PutFunc(m_pTarget,m_OldVal1,m_OldVal2);
   }

protected:
   PutPropFunc m_PutFunc;
   ValueType1 m_NewVal1, m_OldVal1;
   ValueType2 m_NewVal2, m_OldVal2;
};

///////////////////////////////////////////////////////////////////////////////////////////////////
// Transaction for editing 3 simple values
template <class T,class ValueType1,class ValueType2,class ValueType3,const VARIANT_BOOL bUndoable,const VARIANT_BOOL bRepeatable,const GUID* plibid>
class ATL_NO_VTABLE CEditValueTransaction3:
public CTransactionImpl<T,bUndoable,bRepeatable,plibid>
{
public:
   typedef HRESULT (*PutPropFunc)(T* pThis,ValueType1 newVal1,ValueType2 newVal2,ValueType3 newVal3);

void Init(T* pTarget,const char* strName,PutPropFunc putFunc,ValueType1 oldVal1,ValueType1 newVal1,ValueType2 oldVal2,ValueType2 newVal2,ValueType3 oldVal3,ValueType3 newVal3)
   {
      CTransactionImpl<T,bUndoable,bRepeatable,plibid>::Init(pTarget,strName);
      m_PutFunc = putFunc;
      m_NewVal1 = newVal1;
      m_OldVal1 = oldVal1;
      m_NewVal2 = newVal2;
      m_OldVal2 = oldVal2;
      m_NewVal3 = newVal3;
      m_OldVal3 = oldVal3;
   }

   STDMETHOD(Execute)()
   {
      return m_PutFunc(m_pTarget,m_NewVal1,m_NewVal2,m_NewVal3);
   }

	STDMETHOD(Undo)()
   {
      return m_PutFunc(m_pTarget,m_OldVal1,m_OldVal2,m_OldVal3);
   }

protected:
   PutPropFunc m_PutFunc;
   ValueType1 m_NewVal1, m_OldVal1;
   ValueType2 m_NewVal2, m_OldVal2;
   ValueType3 m_NewVal3, m_OldVal3;
};

///////////////////////////////////////////////////////////////////////////////////////////////////
// Transaction for editing 4 simple values
template <class T,class ValueType1,class ValueType2,class ValueType3,class ValueType4,const VARIANT_BOOL bUndoable,const VARIANT_BOOL bRepeatable,const GUID* plibid>
class ATL_NO_VTABLE CEditValueTransaction4:
public CTransactionImpl<T,bUndoable,bRepeatable,plibid>
{
public:
   typedef HRESULT (*PutPropFunc)(T* pThis,ValueType1 newVal1,ValueType2 newVal2,ValueType3 newVal3,ValueType4 newVal4);

void Init(T* pTarget,const char* strName,PutPropFunc putFunc,ValueType1 oldVal1,ValueType1 newVal1,ValueType2 oldVal2,ValueType2 newVal2,ValueType3 oldVal3,ValueType3 newVal3,ValueType4 oldVal4,ValueType4 newVal4)
   {
      CTransactionImpl<T,bUndoable,bRepeatable,plibid>::Init(pTarget,strName);
      m_PutFunc = putFunc;
      m_NewVal1 = newVal1;
      m_OldVal1 = oldVal1;
      m_NewVal2 = newVal2;
      m_OldVal2 = oldVal2;
      m_NewVal3 = newVal3;
      m_OldVal3 = oldVal3;
      m_NewVal4 = newVal4;
      m_OldVal4 = oldVal4;
   }

   STDMETHOD(Execute)()
   {
      return m_PutFunc(m_pTarget,m_NewVal1,m_NewVal2,m_NewVal3,m_NewVal4);
   }

	STDMETHOD(Undo)()
   {
      return m_PutFunc(m_pTarget,m_OldVal1,m_OldVal2,m_OldVal3,m_OldVal4);
   }

protected:
   PutPropFunc m_PutFunc;
   ValueType1 m_NewVal1, m_OldVal1;
   ValueType2 m_NewVal2, m_OldVal2;
   ValueType3 m_NewVal3, m_OldVal3;
   ValueType4 m_NewVal4, m_OldVal4;
};

///////////////////////////////////////////////////////////////////////////////////////////////////
// Transaction for editing a simple indexed value
template <class T,class IndexType,class ValueType,const VARIANT_BOOL bUndoable,const VARIANT_BOOL bRepeatable,const GUID* plibid>
class ATL_NO_VTABLE CEditIndexedValueTransaction:
public CTransactionImpl<T,bUndoable,bRepeatable,plibid>
{
public:
   typedef HRESULT (*PutPropFunc)(T* pThis,IndexType index,ValueType newVal);

void Init(T* pTarget,const char* strName,PutPropFunc putFunc,ValueType oldVal,IndexType index,ValueType newVal)
   {
      CTransactionImpl<T,bUndoable,bRepeatable,plibid>::Init(pTarget,strName);
      m_PutFunc = putFunc;
      m_NewVal = newVal;
      m_OldVal = oldVal;
      m_Index = index;
   }

   STDMETHOD(Execute)()
   {
      return m_PutFunc(m_pTarget,m_Index,m_NewVal);
   }

	STDMETHOD(Undo)()
   {
      return m_PutFunc(m_pTarget,m_Index,m_OldVal);
   }

protected:
   PutPropFunc m_PutFunc;
   ValueType m_NewVal;
   ValueType m_OldVal;
   IndexType m_Index;
};

///////////////////////////////////////////////////////////////////////////////////////////////////
// Transaction for Actions that have reciprical actions for undo

// Action transaction with no data members
template <class T,const VARIANT_BOOL bUndoable,const VARIANT_BOOL bRepeatable,const GUID* plibid>
class ATL_NO_VTABLE CActionTransaction:
public CTransactionImpl<T,bUndoable,bRepeatable,plibid>
{
public:
   typedef HRESULT (*ActionFunc)(T* pThis);

void Init(T* pTarget,const char* strName,ActionFunc doFunc,ActionFunc undoFunc)
   {
      CTransactionImpl<T,bUndoable,bRepeatable,plibid>::Init(pTarget,strName);
      m_DoFunc = doFunc;
      m_UndoFunc = undoFunc;
   }

   STDMETHOD(Execute)()
   {
      return m_DoFunc(m_pTarget);
   }

	STDMETHOD(Undo)()
   {
      return m_UndoFunc(m_pTarget);
   }

protected:
   ActionFunc m_DoFunc;
   ActionFunc m_UndoFunc;
};

// Action transaction with 1 data member
template <class T,class ValueType,const VARIANT_BOOL bUndoable,const VARIANT_BOOL bRepeatable,const GUID* plibid>
class ATL_NO_VTABLE CActionTransaction1:
public CTransactionImpl<T,bUndoable,bRepeatable,plibid>
{
public:
   typedef HRESULT (*ActionFunc)(T* pThis,ValueType& newVal);

void Init(T* pTarget,const char* strName,ActionFunc doFunc,ActionFunc undoFunc,ValueType& param)
   {
      CTransactionImpl<T,bUndoable,bRepeatable,plibid>::Init(pTarget,strName);
      m_DoFunc = doFunc;
      m_UndoFunc = undoFunc;
      m_Param = param;
   }

   STDMETHOD(Execute)()
   {
      return m_DoFunc(m_pTarget,m_Param);
   }

	STDMETHOD(Undo)()
   {
      return m_UndoFunc(m_pTarget,m_Param);
   }

protected:
   ActionFunc m_DoFunc;
   ActionFunc m_UndoFunc;
   ValueType m_Param;
};

// Action transaction with 2 data members
template <class T,class ValueType1,class ValueType2,const VARIANT_BOOL bUndoable,const VARIANT_BOOL bRepeatable,const GUID* plibid>
class ATL_NO_VTABLE CActionTransaction2:
public CTransactionImpl<T,bUndoable,bRepeatable,plibid>
{
public:
   typedef HRESULT (*ActionFunc)(T* pThis,ValueType1& newVal1,ValueType2& newVal2);

void Init(T* pTarget,const char* strName,ActionFunc doFunc,ActionFunc undoFunc,ValueType1& param1,ValueType2& param2)
   {
      CTransactionImpl<T,bUndoable,bRepeatable,plibid>::Init(pTarget,strName);
      m_DoFunc = doFunc;
      m_UndoFunc = undoFunc;
      m_Param1 = param1;
      m_Param2 = param2;
   }

   STDMETHOD(Execute)()
   {
      return m_DoFunc(m_pTarget,m_Param1,m_Param2);
   }

	STDMETHOD(Undo)()
   {
      return m_UndoFunc(m_pTarget,m_Param1,m_Param2);
   }

protected:
   ActionFunc m_DoFunc;
   ActionFunc m_UndoFunc;
   ValueType1 m_Param1;
   ValueType2 m_Param2;
};

// Action transaction with 3 data members
template <class T,class ValueType1,class ValueType2,class ValueType3,const VARIANT_BOOL bUndoable,const VARIANT_BOOL bRepeatable,const GUID* plibid>
class ATL_NO_VTABLE CActionTransaction3:
public CTransactionImpl<T,bUndoable,bRepeatable,plibid>
{
public:
   typedef HRESULT (*ActionFunc)(T* pThis,ValueType1& newVal1,ValueType2& newVal2,ValueType3& newVal3);

void Init(T* pTarget,const char* strName,ActionFunc doFunc,ActionFunc undoFunc,ValueType1& param1,ValueType2& param2,ValueType3& param3)
   {
      CTransactionImpl<T,bUndoable,bRepeatable,plibid>::Init(pTarget,strName);
      m_DoFunc = doFunc;
      m_UndoFunc = undoFunc;
      m_Param1 = param1;
      m_Param2 = param2;
      m_Param3 = param3;
   }

   STDMETHOD(Execute)()
   {
      return m_DoFunc(m_pTarget,m_Param1,m_Param2,m_Param3);
   }

	STDMETHOD(Undo)()
   {
      return m_UndoFunc(m_pTarget,m_Param1,m_Param2,m_Param3);
   }

protected:
   ActionFunc m_DoFunc;
   ActionFunc m_UndoFunc;
   ValueType1 m_Param1;
   ValueType2 m_Param2;
   ValueType3 m_Param3;
};

#endif //  INCLUDED_TXNMGRIMPL_H_