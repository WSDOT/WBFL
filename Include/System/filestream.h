///////////////////////////////////////////////////////////////////////
// System - WBFL low level system services
// Copyright © 1999-2011  Washington State Department of Transportation
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



#ifndef INCLUDED_SYSTEM_FILESTREAM_H_
#define INCLUDED_SYSTEM_FILESTREAM_H_
#pragma once

#include <stdio.h>
#include <atlbase.h>

class FileStream : public IStream
{
public:
	FileStream() 
	{ 
        _ulRefs = 1;
        _hFile = NULL;
        _fRead = true;
	}

	~FileStream() 
	{ 
		::CloseHandle(_hFile);
	}

    HRESULT STDMETHODCALLTYPE QueryInterface(REFIID riid, void ** ppvObject)
    {
        if (riid == IID_IUnknown)
        {
            *ppvObject = static_cast<IUnknown*>(this);
        }
        else if (riid == IID_IStream)
        {
            *ppvObject = static_cast<IStream*>(this);
        }
		else
		{
			return E_NOINTERFACE;
		}
        reinterpret_cast<IUnknown*>(*ppvObject)->AddRef();
        return S_OK;
    }

    ULONG STDMETHODCALLTYPE AddRef( void)
    {
        return InterlockedIncrement(&_ulRefs);
    }

    ULONG STDMETHODCALLTYPE Release( void)
    {
        if (InterlockedDecrement(&_ulRefs) == 0)
        {
            delete this;
            return 0;
        }
        return _ulRefs;
    }

    bool open(LPCTSTR name, bool read = true)
    {
       _fRead = read;
        if (_fRead)
        {
		    _hFile = ::CreateFile(name,GENERIC_READ,FILE_SHARE_READ,NULL,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,NULL);
        }
        else
        {
		    _hFile = ::CreateFile(name,GENERIC_WRITE,FILE_SHARE_READ,NULL,CREATE_ALWAYS,FILE_ATTRIBUTE_NORMAL,NULL);
        }

        return (_hFile == INVALID_HANDLE_VALUE) ? false : true;
    }

    virtual /* [local] */ HRESULT STDMETHODCALLTYPE Read( 
        /* [out] */ void __RPC_FAR *pv,
        /* [in] */ ULONG cb,
        /* [out] */ ULONG __RPC_FAR *pcbRead)
	{	
        if (! _fRead) return E_FAIL;

        DWORD len;
		BOOL rc = ReadFile(
			_hFile,	// handle of file to read 
			pv,	// address of buffer that receives data  
			cb,	// number of bytes to read 
			&len,	// address of number of bytes read 
			NULL 	// address of structure for data 
		   );
        if (pcbRead)
            *pcbRead = len;
        if (! rc)        // ReadFile returns FALSE if there is an error.
            return E_FAIL;
        
        return len > 0 ? S_OK : S_FALSE; 
	}
    
    virtual /* [local] */ HRESULT STDMETHODCALLTYPE Write( 
        /* [size_is][in] */ const void __RPC_FAR *pv,
        /* [in] */ ULONG cb,
        /* [out] */ ULONG __RPC_FAR *pcbWritten)
	{
        if (_fRead) return E_FAIL;

		BOOL rc = WriteFile(
			_hFile,	// handle of file to write 
			pv,	// address of buffer that contains data  
			cb,	// number of bytes to write 
			pcbWritten,	// address of number of bytes written 
			NULL 	// address of structure for overlapped I/O  
		   );

		return (rc) ? S_OK : E_FAIL;
	}

    virtual /* [local] */ HRESULT STDMETHODCALLTYPE Seek( 
        /* [in] */ LARGE_INTEGER dlibMove,
        /* [in] */ DWORD dwOrigin,
        /* [out] */ ULARGE_INTEGER __RPC_FAR *plibNewPosition) { return E_FAIL; }
    
    virtual HRESULT STDMETHODCALLTYPE SetSize( 
        /* [in] */ ULARGE_INTEGER libNewSize) { return E_FAIL; }
    
    virtual /* [local] */ HRESULT STDMETHODCALLTYPE CopyTo( 
        /* [unique][in] */ IStream __RPC_FAR *pstm,
        /* [in] */ ULARGE_INTEGER cb,
        /* [out] */ ULARGE_INTEGER __RPC_FAR *pcbRead,
        /* [out] */ ULARGE_INTEGER __RPC_FAR *pcbWritten) { return E_FAIL; }
    
    virtual HRESULT STDMETHODCALLTYPE Commit( 
        /* [in] */ DWORD grfCommitFlags) { return E_FAIL; }
    
    virtual HRESULT STDMETHODCALLTYPE Revert( void) { return E_FAIL; }
    
    virtual HRESULT STDMETHODCALLTYPE LockRegion( 
        /* [in] */ ULARGE_INTEGER libOffset,
        /* [in] */ ULARGE_INTEGER cb,
        /* [in] */ DWORD dwLockType) { return E_FAIL; }
    
    virtual HRESULT STDMETHODCALLTYPE UnlockRegion( 
        /* [in] */ ULARGE_INTEGER libOffset,
        /* [in] */ ULARGE_INTEGER cb,
        /* [in] */ DWORD dwLockType) { return E_FAIL; }
    
    virtual HRESULT STDMETHODCALLTYPE Stat( 
        /* [out] */ STATSTG __RPC_FAR *pstatstg,
        /* [in] */ DWORD grfStatFlag) { return E_FAIL; }
    
    virtual HRESULT STDMETHODCALLTYPE Clone( 
        /* [out] */ IStream __RPC_FAR *__RPC_FAR *ppstm) { return E_FAIL; }
private:
	HANDLE _hFile;
    bool _fRead;
    LONG _ulRefs;
};

#endif // INCLUDED_SYSTEM_FILESTREAM_H_
