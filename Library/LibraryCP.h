///////////////////////////////////////////////////////////////////////
// Library - Framework for libraries
// Copyright © 1999-2013  Washington State Department of Transportation
//                        Bridge and Structures Office
//
// This library is a part of the Washington Bridge Foundation Libraries
// and was developed as part of the Alternate Route Project
//
// This library is free software; you can redistribute it and/or modify it under
// the terms of the Alternate Route Library Open Source License as published by 
// the Washington State Department of Transportation, Bridge and Structures Office.
//
// This program is distributed in the hope that it will be useful, but is distributed 
// AS IS, WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY 
// or FITNESS FOR A PARTICULAR PURPOSE. See the Alternate Route Library Open Source 
// License for more details.
//
// You should have received a copy of the Alternate Route Library Open Source License 
// along with this program; if not, write to the Washington State Department of 
// Transportation, Bridge and Structures Office, P.O. Box  47340, 
// Olympia, WA 98503, USA or e-mail Bridge_Support@wsdot.wa.gov
///////////////////////////////////////////////////////////////////////

#ifndef _LIBRARYCP_H_
#define _LIBRARYCP_H_


template <class T>
class CProxyDLibraryEvents : public IConnectionPointImpl<T, &IID_ILibraryEvents, CComDynamicUnkArray>
{
	//Warning this class may be recreated by the wizard.
public:
	VOID Fire_OnNameChanged(BSTR oldName, BSTR newName)
	{
		T* pT = static_cast<T*>(this);
		int nConnectionIndex;
		int nConnections = m_vec.GetSize();
		
		for (nConnectionIndex = 0; nConnectionIndex < nConnections; nConnectionIndex++)
		{
			pT->Lock();
			CComPtr<IUnknown> sp = m_vec.GetAt(nConnectionIndex);
			pT->Unlock();
         CComQIPtr<ILibraryEvents> events(sp);
         if ( events )
            events->OnNameChanged(oldName,newName);
		}
	}
	VOID Fire_OnLibraryChanged(ILibrary * lib)
	{
		T* pT = static_cast<T*>(this);
		int nConnectionIndex;
		int nConnections = m_vec.GetSize();
		
		for (nConnectionIndex = 0; nConnectionIndex < nConnections; nConnectionIndex++)
		{
			pT->Lock();
			CComPtr<IUnknown> sp = m_vec.GetAt(nConnectionIndex);
			pT->Unlock();
         CComQIPtr<ILibraryEvents> events(sp);
         if ( events )
            events->OnLibraryChanged(lib);
		}
	}
	VOID Fire_OnEntryNameChanged(ILibrary * lib, BSTR oldName, BSTR newName)
	{
		T* pT = static_cast<T*>(this);
		int nConnectionIndex;
		int nConnections = m_vec.GetSize();
		
		for (nConnectionIndex = 0; nConnectionIndex < nConnections; nConnectionIndex++)
		{
			pT->Lock();
			CComPtr<IUnknown> sp = m_vec.GetAt(nConnectionIndex);
			pT->Unlock();
         CComQIPtr<ILibraryEvents> events(sp);
         if ( events )
            events->OnEntryNameChanged(lib,oldName,newName);
		}
	}
	VOID Fire_OnEntryChanged(ILibrary * lib, ILibraryEntry * entry)
	{
		T* pT = static_cast<T*>(this);
		int nConnectionIndex;
		int nConnections = m_vec.GetSize();
		
		for (nConnectionIndex = 0; nConnectionIndex < nConnections; nConnectionIndex++)
		{
			pT->Lock();
			CComPtr<IUnknown> sp = m_vec.GetAt(nConnectionIndex);
			pT->Unlock();
         CComQIPtr<ILibraryEvents> events(sp);
         if ( events )
            events->OnEntryChanged(lib,entry);
		}
	}
};




template <class T>
class CProxyDLibraryMgrEvents : public IConnectionPointImpl<T, &IID_ILibraryMgrEvents, CComDynamicUnkArray>
{
	//Warning this class may be recreated by the wizard.
public:
	VOID Fire_OnNameChanged(BSTR oldName, BSTR newName)
	{
		T* pT = static_cast<T*>(this);
		int nConnectionIndex;
		int nConnections = m_vec.GetSize();
		
		for (nConnectionIndex = 0; nConnectionIndex < nConnections; nConnectionIndex++)
		{
			pT->Lock();
			CComPtr<IUnknown> sp = m_vec.GetAt(nConnectionIndex);
			pT->Unlock();
         CComQIPtr<ILibraryMgrEvents> events(sp);
         if ( events )
            events->OnNameChanged(oldName,newName);
		}
	}
	VOID Fire_OnChanged(ILibraryMgr * libMgr)
	{
		T* pT = static_cast<T*>(this);
		int nConnectionIndex;
		int nConnections = m_vec.GetSize();
		
		for (nConnectionIndex = 0; nConnectionIndex < nConnections; nConnectionIndex++)
		{
			pT->Lock();
			CComPtr<IUnknown> sp = m_vec.GetAt(nConnectionIndex);
			pT->Unlock();
         CComQIPtr<ILibraryMgrEvents> events(sp);
         if ( events )
            events->OnChanged(libMgr);
		}
	}
	VOID Fire_OnLibraryNameChanged(BSTR oldName, BSTR newName)
	{
		T* pT = static_cast<T*>(this);
		int nConnectionIndex;
		int nConnections = m_vec.GetSize();
		
		for (nConnectionIndex = 0; nConnectionIndex < nConnections; nConnectionIndex++)
		{
			pT->Lock();
			CComPtr<IUnknown> sp = m_vec.GetAt(nConnectionIndex);
			pT->Unlock();
         CComQIPtr<ILibraryMgrEvents> events(sp);
         if ( events )
            events->OnLibraryNameChanged(oldName,newName);
		}
	}
	VOID Fire_OnLibraryChanged(ILibrary * lib)
	{
		T* pT = static_cast<T*>(this);
		int nConnectionIndex;
		int nConnections = m_vec.GetSize();
		
		for (nConnectionIndex = 0; nConnectionIndex < nConnections; nConnectionIndex++)
		{
			pT->Lock();
			CComPtr<IUnknown> sp = m_vec.GetAt(nConnectionIndex);
			pT->Unlock();
         CComQIPtr<ILibraryMgrEvents> events(sp);
         if ( events )
            events->OnLibraryChanged(lib);
		}
	}
	VOID Fire_OnEntryNameChanged(ILibrary * lib, BSTR oldName, BSTR newName)
	{
		T* pT = static_cast<T*>(this);
		int nConnectionIndex;
		int nConnections = m_vec.GetSize();
		
		for (nConnectionIndex = 0; nConnectionIndex < nConnections; nConnectionIndex++)
		{
			pT->Lock();
			CComPtr<IUnknown> sp = m_vec.GetAt(nConnectionIndex);
			pT->Unlock();
         CComQIPtr<ILibraryMgrEvents> events(sp);
         if ( events )
            events->OnEntryNameChanged(lib,oldName,newName);
		}
	}
	VOID Fire_OnEntryChanged(ILibrary * lib, ILibraryEntry * entry)
	{
		T* pT = static_cast<T*>(this);
		int nConnectionIndex;
		int nConnections = m_vec.GetSize();
		
		for (nConnectionIndex = 0; nConnectionIndex < nConnections; nConnectionIndex++)
		{
			pT->Lock();
			CComPtr<IUnknown> sp = m_vec.GetAt(nConnectionIndex);
			pT->Unlock();
         CComQIPtr<ILibraryMgrEvents> events(sp);
         if ( events )
            events->OnEntryChanged(lib,entry);
		}
	}
};
#endif