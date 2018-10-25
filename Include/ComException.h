///////////////////////////////////////////////////////////////////////
// WBFL - Washington Bridge Foundation Libraries
// Copyright © 2003  Washington State Department of Transportation
//                   Bridge and Structures Office
//
// This library is a part of the Washington Bridge Foundation Libraries
// and was developed as part of the Alternate Route Project
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the Alternate Route Library Open Source License as 
// published by the Washington State Department of Transportation,
// Bridge and Structures Office.
//
// This program is distributed in the hope that it will be useful,
// but is distributed AS IS, WITHOUT ANY WARRANTY; without even the
// implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR 
// PURPOSE.  See the Alternate Route Library Open Source License for more details.
//
// You should have received a copy of the Alternate Route Library Open Source License
// along with this program; if not, write to the Washington State
// Department of Transportation, Bridge and Structures Office,
// 4500 3rd Ave SE, P.O. Box 47340, Olympia, WA 98503, USA or e-mail
// Bridge_Support@wsdot.wa.gov
///////////////////////////////////////////////////////////////////////


#ifndef INCLUDED_COMEXCEPTION_H_
#define INCLUDED_COMEXCEPTION_H_

// SYSTEM INCLUDES
//
#include <string>
#include <comdef.h>

// LOCAL INCLUDES
//

// FORWARD DECLARATIONS
//

// MISCELLANEOUS
//
#undef THROW_MSG
#undef THROW_IDS
#define THROW_MSG(msg,hr,helpid) throw CComException(_T(__FILE__), __LINE__, msg, hr, helpid );
#define THROW_IDS(msgID,hr,helpid) throw CComException(_T(__FILE__),__LINE__, msgID, hr, helpid);

/*****************************************************************************
CLASS 
   CComException

   Base class for wbfl com exceptions.


DESCRIPTION
   Base class for wbfl exceptions.
   This class works with ATL to provide a handy way to use C++ exception handling in 
   your ATL COM objects. It provides the information you need  to easily set up IErrorInfo 
   after the exception is caught.

   As with any C++ exceptions: DO NOT THROW ACROSS COM INTERFACE BOUNDARIES !!!
   Clients other than C++ do'nt know how to deal with them.


COPYRIGHT
   Copyright (c) 2000
   Washington State Department Of Transportation
   All Rights Reserved

LOG
   rdp : 11.03.1997 : Created file
*****************************************************************************/

class CComException
{
public:
   // GROUP: LIFECYCLE

   //------------------------------------------------------------------------
   // Constructor.  Supply the file and line number where the 
   // exception occured and a message.
   CComException(const TCHAR* file, long line, BSTR msg, HRESULT hr, DWORD helpid) :
   m_File( file ),
   m_Line( line ),
   m_HR(hr),
   m_HelpID(helpid),
   m_Msg(msg)
   {
   }

   CComException(const TCHAR* file, long line, const char* msg, HRESULT hr, DWORD helpid) :
   m_File( file ),
   m_Line( line ),
   m_HR(hr),
   m_HelpID(helpid),
   m_Msg(msg)
   {
   }

   CComException(const TCHAR* file, long line, UINT msgID,             HRESULT hr, DWORD helpid) :
   m_File( file ),
   m_Line( line ),
   m_HR(hr),
   m_HelpID(helpid)
   {
      // extract message from string table
      TCHAR str[256];
      int st = ::LoadString( _Module.GetModuleInstance(), msgID, str, 256);
      ATLASSERT(st!=0);
      m_Msg = CComBSTR(str);
   }

   //------------------------------------------------------------------------
   // Copy constructor
   CComException(const CComException& rOther)
   {
      MakeCopy(rOther);
   }

   //------------------------------------------------------------------------
   // Destructor
   virtual ~CComException()
   {}

   // GROUP: OPERATORS

   // GROUP: OPERATIONS
   // GROUP: ACCESS

   //------------------------------------------------------------------------
   // Returns a reason code for the exception.  
   virtual HRESULT GetHresult() const throw()
   {
      return m_HR;
   }


   //------------------------------------------------------------------------
   // Returns a Help ID for the Exception
   virtual DWORD GetHelpID() const throw()
   {
      return m_HelpID;
   }

   //------------------------------------------------------------------------
   // get an error message
   virtual const CComBSTR& GetErrorMessage() const throw()
   {
      return m_Msg;
   }

   //------------------------------------------------------------------------
   // Returns the name of the file where the exception was originally thrown.
   const TCHAR* GetFile() const throw()
   {
      return m_File.c_str();
   }

   //------------------------------------------------------------------------
   // Returns the line number from where the exceptino was originally thrown.
   long GetLine() const throw()
   {
      return m_Line;
   }

   //------------------------------------------------------------------------
   // Add more information to the error message
   void AppendToMessage(BSTR msg)
   {
      CComBSTR app(msg);
      m_Msg += app;
   }

   //------------------------------------------------------------------------
   // Add more information to the error message
   void AppendToMessage(const TCHAR* msg)
   {
      CComBSTR app(msg);
      m_Msg += app;
   }


   // GROUP: INQUIRY
   // GROUP: DEBUG

protected:
   // GROUP: DATA MEMBERS
   // GROUP: LIFECYCLE
   // GROUP: OPERATORS
   //------------------------------------------------------------------------
   // Assignment operator
   CComException& operator = (const CComException& rOther)
   {
      if( this != &rOther )
      {
         MakeAssignment(rOther);
      }

      return *this;
   }

   // GROUP: OPERATIONS
   //------------------------------------------------------------------------
   void MakeCopy(const CComException& rOther)
   {
      m_File = rOther.m_File;
      m_Line = rOther.m_Line;
      m_HR   = rOther.m_HR;
      m_Msg  = rOther.m_Msg;
   }

   //------------------------------------------------------------------------
   void MakeAssignment(const CComException& rOther)
   {
      MakeCopy( rOther );
   }

   // GROUP: ACCESS
   // GROUP: INQUIRY

private:
   CComException(); // no default constructor
   // GROUP: DATA MEMBERS
   std::wstring m_File;
   long        m_Line;
   HRESULT     m_HR;
   DWORD       m_HelpID;
   CComBSTR     m_Msg;

   // GROUP: LIFECYCLE
   // GROUP: OPERATORS
   // GROUP: OPERATIONS
   // GROUP: ACCESS
   // GROUP: INQUIRY
};

// EXTERNAL REFERENCES
//

// Some inline free functions that make using CComException easier

// DealWithExceptions should be put at the interface level in ATL class methods that implement
// COM interfaces. To use this, put a try block around any calls that you think might throw C++
// exceptions (including C runtimes). Then have a catch(...) that calls DealWithExceptions. It will
// rethrow the exception and return an appropriate HRESULT.

template< class T>
HRESULT DealWithExceptions(T* psource, const IID& iid)
{
   // try to make sense out of what got thrown
   try
   {
      throw; // throw whatever got thrown last to be caught immediately!
   }
   catch (CComException& re)
   {
      // Local flavor. Somebody puked from way down deep. Build error message and crap out
      CComBSTR msg(re.GetErrorMessage());
      HRESULT hr = re.GetHresult();
      DWORD hid = re.GetHelpID();
      return AtlReportError(T::GetObjectCLSID(), msg,hid, GetHelpFile(), iid, hr);
   }
   catch (_com_error cre)
   {
      // COM Wrapper flavor. Assume that server class has taken care of ERRORINFO
      HRESULT hr = cre.Error();
      return hr;
   }
   catch (HRESULT hr)
   {
      // assume hresult was thrown from call to another COM component that
      // has already set up errorinfo
      return hr;
   }
   catch (...)
   {
      // could make up a custom message here, but we don't know what happened so why try?
      // the main point is not to let the exception out into the com world
      ATLASSERT(0);
      return E_FAIL;
   }
}


inline CComBSTR CreateErrorMsg1S(UINT nid, BSTR bmsg)
{
   TCHAR str[256];
   ::LoadString( _Module.GetModuleInstance(), nid, str, 256);
   TCHAR msg[256];
   int cOut = _stprintf_s( msg, str, bmsg);
   ATLASSERT( cOut < 256 );
   return CComBSTR(msg);
}

inline CComBSTR CreateErrorMsg2S(UINT nid, BSTR bmsg1, BSTR bmsg2)
{
   TCHAR str[256];
   ::LoadString( _Module.GetModuleInstance(), nid, str, 256);
   TCHAR msg[256];
   int cOut = _stprintf_s( msg, str, bmsg1, bmsg2);
   ATLASSERT( cOut < 256 );
   return CComBSTR(msg);
}

inline CComBSTR CreateErrorMsg1L(UINT nid, long someInt)
{
   TCHAR str[256];
   ::LoadString( _Module.GetModuleInstance(), nid, str, 256);
   TCHAR msg[256];
   int cOut = _stprintf_s( msg, str, someInt);
   ATLASSERT( cOut < 256 );
   return CComBSTR(msg);
}

inline CComBSTR CreateErrorMsg2L(UINT nid, long someInt1, long someInt2)
{
   TCHAR str[256];
   ::LoadString( _Module.GetModuleInstance(), nid, str, 256);
   TCHAR msg[256];
   int cOut = _stprintf_s( msg, str, someInt1, someInt2);
   ATLASSERT( cOut < 256 );
   return CComBSTR(msg);
}

inline CComBSTR CreateErrorMsg1D(UINT nid, double someDouble)
{
   TCHAR str[256];
   ::LoadString( _Module.GetModuleInstance(), nid, str, 256);
   TCHAR msg[256];
   int cOut = _stprintf_s( msg, str, someDouble);
   ATLASSERT( cOut < 256 );
   return CComBSTR(msg);
}


#endif // INCLUDED_COMEXCEPTION_H_
