// MakeDocMap.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "MakeDocMap.h"
#include <System\Tokenizer.h>
#include <fstream>
#include <map>

#include <boost/algorithm/string/trim.hpp>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// The one and only application object

CWinApp theApp;

using namespace std;

// This utility reads the .HH and .ALI files and creates a .DM file
// .HH files have the help topic IDs as
// #define IDH_MY_HELP_TOPIC  200
//
// .ALI files have map the #define name to a help topic
// IDC_MY_HELP_TOPIC=\subfolder\mytopic.html
//
// The DM file (documentation map) is loaded at runtime
// and maps a topic id to a topic
// 200=\subfolder\mytopic.html
//
// To use this application, just make the folder where the HH and ALI files are located
// the current directory and then run the application with the documentation set name
// as the only argument
//
// MakeDocMap.exe PGSuper
//
// The application will look for PGSuper.hh and PGSuper.ali in the current folder
// and will create PGSuper.dm

//std::map<std::_tstring,UINT>::iterator my_find(std::map<std::_tstring,UINT>::iterator& begin,std::map<std::_tstring,UINT>::iterator& end,std::_tstring& value)
//{
//   for ( ; begin != end; begin++ )
//   {
//      std::_tstring key = begin->first;
//      if ( key == value )
//      {
//         return begin;
//      }
//   }
//
//   return end;
//}

int _tmain(int argc, TCHAR* argv[], TCHAR* envp[])
{
	int nRetCode = 0;

	// initialize MFC and print and error on failure
	if (!AfxWinInit(::GetModuleHandle(nullptr), nullptr, ::GetCommandLine(), 0))
	{
		// TODO: change error code to suit your needs
		_tprintf(_T("Fatal Error: MFC initialization failed\n"));
		nRetCode = 1;
	}
	else
	{
		// TODO: code your application's behavior here.
	}

   USES_CONVERSION;

   CString strHHFile;
   strHHFile.Format(_T("%s.hh"),argv[1]);

   CString strALIFile;
   strALIFile.Format(_T("%s.ali"),argv[1]);

   CString strDMFile;
   strDMFile.Format(_T("%s.dm"),argv[1]);

   std::_tifstream ifHH(strHHFile);
   std::map<std::_tstring,UINT> m_HIDMap;

   // Read the .hh file and create a map of the #define and help ID numbers
   TCHAR buffer[256];
   if ( !ifHH.bad() && ifHH.is_open() )
   {
      while (!ifHH.eof())
      {
         bool bFoundDefine = false;;
         std::_tstring strIDH;
         UINT nID;

         memset(buffer,0,sizeof(buffer));

         ifHH.getline(buffer,256);
         LPCTSTR delims[] = {_T(" "),_T("\t"), 0};
         WBFL::System::Tokenizer tokenizer(delims);
         tokenizer.push_back(buffer);
         WBFL::System::Tokenizer::iterator iter(tokenizer.begin());
         WBFL::System::Tokenizer::iterator end(tokenizer.end());

         while( iter != end )
         {
            if ( !bFoundDefine )
            {
               if ( *iter == std::_tstring(_T("#define")) )
               {
                  bFoundDefine = true;
               }
            }
            else if ( strIDH.empty() )
            {
               strIDH = *iter;
               boost::trim(strIDH);
            }
            else
            {
               WBFL::System::Tokenizer::ParseULong(iter->c_str(),(unsigned long*)&nID);

               m_HIDMap.insert(std::make_pair(strIDH,nID));
            }

            iter++;
         }
      }
   }
   else
   {
      std::_tcout << _T("Error readiing ") << strHHFile << std::endl;
   }

   // Read the alias file and create a map of the Help IDs and the help topic URLs
   std::_tifstream ifALI(strALIFile);
   std::map<std::_tstring,std::_tstring> m_ALIMap;
   if ( !ifALI.bad() && ifALI.is_open() )
   {
      while (!ifALI.eof())
      {
         memset(buffer,0,sizeof(buffer));
         ifALI.getline(buffer,256);
         CString str(buffer);
         if ( !str.IsEmpty() )
         {
            int pos = str.Find(_T("="));
            CString token = str.Left(pos);
            token.Trim();

            std::_tstring strToken(token.GetBuffer());
            CString value = str.Mid(pos+1);
            value.Trim();
            std::_tstring strValue(value.GetBuffer());
            m_ALIMap.insert(std::make_pair(strToken,strValue));
         }
      }
   }
   else
   {
      std::_tcout << _T("Error readiing ") << strALIFile << std::endl;
   }

   // Write out the documentation map file
   // ID=URL
   std::_tofstream ofDM(strDMFile);
   std::map<std::_tstring,std::_tstring>::iterator iter(m_ALIMap.begin());
   std::map<std::_tstring,std::_tstring>::iterator end(m_ALIMap.end());
   for ( ; iter != end; iter++ )
   {
      std::_tstring token(iter->first);
      std::map<std::_tstring,UINT>::iterator found(m_HIDMap.find(token));
      if ( found == m_HIDMap.end() )
      {
         std::_tcout << token.c_str() << _T(" not found") << std::endl;
      }
      else
      {
         UINT nID = found->second;
         std::_tstring strLocation(iter->second);
         ofDM << nID << _T("=") << strLocation.c_str() << std::endl;
         m_HIDMap.erase(found);
      }
   }

   std::_tcout << _T("There are ") << (m_HIDMap.size()) << _T(" unmapped help IDs") << std::endl;
   std::map<std::_tstring,UINT>::iterator hidIter(m_HIDMap.begin());
   std::map<std::_tstring,UINT>::iterator hidIterEnd(m_HIDMap.end());
   for ( ; hidIter != hidIterEnd; hidIter++ )
   {
      std::_tcout << hidIter->first.c_str() << _T(" = ") << hidIter->second << std::endl;
   }


	return nRetCode;
}
