// LBAMResponseDumper.cpp : Implementation of CLBAMResponseDumper
#include "stdafx.h"
#include "LBAMDumper.h"
#include "LBAMResponseDumper.h"

#include <fstream>

#include "ModelDumper.h"
#include "LoadGroupDumper.h"
#include "LiveLoadDumper.h"
#include "LoadCombinationDumper.h"
#include "DumperUtils.h"

#include <iostream>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


std::string MakeTempFilename()
{
   char temp_path[ _MAX_PATH ];
   char temp_file[ _MAX_PATH ];

   if ( ::GetTempPath( _MAX_PATH, temp_path ) == 0 )
      strcpy_s(temp_path,_MAX_PATH,"C:\\"); // Couldn't establish a temp path, just use the root drive.

   // This creates a file called "temp_file".TMP
   if ( ::GetTempFileName( temp_path, "tmp", 0, temp_file ) == 0 )
   {
      // We could not get a temp name, so just use this default
      // (Use a tmp extension so it is in the same format as the one
      //  the OS would have created for us)
      strcpy_s( temp_file, _MAX_PATH, "report.tmp" );
   }

   return std::string(temp_file);
}

/////////////////////////////////////////////////////////////////////////////
// CLBAMResponseDumper

CLBAMResponseDumper::CLBAMResponseDumper():
m_DumpModel(VARIANT_TRUE),
m_DumpLoadGroups(VARIANT_TRUE),
m_DumpInfluenceLines(VARIANT_TRUE),
m_DumpContraflexure(VARIANT_TRUE),
m_DumpEnvelopedVehicularResponse(VARIANT_TRUE),
m_LiveLoadModelResponse(VARIANT_TRUE),
m_LoadCaseResponse(VARIANT_TRUE),
m_LoadCombinationResponse(VARIANT_TRUE)
{
}


STDMETHODIMP CLBAMResponseDumper::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_ILBAMResponseDumper
	};
	for (int i=0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

STDMETHODIMP CLBAMResponseDumper::Dump(ILBAMAnalysisEngine* engine, BSTR fileName, BSTR detailsFileName)
{
   USES_CONVERSION;
   HRESULT hrr = S_OK;

   CHECK_IN(engine);
   CHECK_IN(fileName);

   CHRException hr;
   std::ofstream os;
   std::ofstream cos;
   try
   {
      // first open our main output file
      os.open( W2A(fileName) );

      if (!os.is_open())
      {
         // problem opening report file
         ATLASSERT(0);
         return E_INVALIDARG;
      }

      bool do_details = false;

      // Open Detailed configuration file, if name not blank
      if (detailsFileName != NULL)
      {
         std::string curr_file(W2A(detailsFileName));

         if (curr_file.size() > 0)
         {
            cos.open( curr_file.c_str() );

            if (!cos.is_open())
            {
               // problem opening concurrent report file
               ATLASSERT(0);
               return E_INVALIDARG;
            }

            do_details = true;

            cos<<"Concurrent Responses and Detailed Reponse Configurations" <<std::endl;
            cos<<"Master Dump File Name is "<< W2A(fileName)<<std::endl;
            cos<<"=================================================================================================="<<std::endl<<std::endl;
         }
      }

      os<<"Dump of LBAM model and results" << std::endl << std::endl;

      CComPtr<ILBAMModel> model;
      hr = engine->get_Model(&model);

      CDumperUtil util(engine, do_details);

      // model description
      if (m_DumpModel!=VARIANT_FALSE)
      {
         std::cout<<"Model Description"<<std::endl;
         CModelDumper mdumper(&util);
         mdumper.DumpModel(os, model);
      }


      // dump analysis pois no matter what since this is our roadmap
      CLoadGroupDumper lg_dumper(engine, &util);
      lg_dumper.DumpAnalysisPOIs(os);

      // load group response
      if (m_DumpLoadGroups!=VARIANT_FALSE)
      {
         std::cout<<"LoadGroup Response"<<std::endl;
         lg_dumper.DumpLoadGroupResponse(os);
      }

      // influence lines
      if (m_DumpInfluenceLines!=VARIANT_FALSE)
      {
         std::cout<<"Influence Line Response"<<std::endl;
         lg_dumper.DumpInfluenceLines(os);
      }

      // contraflexure response
      if (m_DumpContraflexure!=VARIANT_FALSE)
      {
         lg_dumper.DumpContraflexureResponse(os);
      }

      // live loads
      CLiveLoadDumper ll_dumper(engine, &util);
      if (m_DumpEnvelopedVehicularResponse!=VARIANT_FALSE)
      {
         std::cout<<"Enveloped Vehicular Response"<<std::endl;
         ll_dumper.DumpEnvelopedVehicularResponse(os, cos);
      }
      
      if (m_LiveLoadModelResponse!=VARIANT_FALSE)
      {
         std::cout<<"Live Load Model Response"<<std::endl;
         ll_dumper.DumpLiveLoadModelResponse(os, cos);
      }

      // load cases and combinations
      CLoadCombinationDumper lc_dumper(engine, &util);
      if (m_LoadCaseResponse!=VARIANT_FALSE)
      {
         std::cout<<"Load Case Response"<<std::endl;
         lc_dumper.DumpLoadCaseResponse(os);
      }

      if (m_LoadCombinationResponse!=VARIANT_FALSE)
      {
         std::cout<<"Load Combination Response"<<std::endl;
         lc_dumper.DumpLoadCombinationResponse(os, cos);
      }
      
      std::cout<<"Done"<<std::endl;

      os<<std::endl<<"Normal Dump Completion" << std::endl << std::endl;

   }
   catch(HRESULT& hr)
   {
      hrr = hr;
   }
   catch(...)
   {
      hrr = E_FAIL;
   }

	return hrr;
}

STDMETHODIMP CLBAMResponseDumper::get_DumpModel(VARIANT_BOOL *pVal)
{
	*pVal = m_DumpModel;
	return S_OK;
}

STDMETHODIMP CLBAMResponseDumper::put_DumpModel(VARIANT_BOOL newVal)
{
	m_DumpModel = newVal;
	return S_OK;
}

STDMETHODIMP CLBAMResponseDumper::get_DumpLoadGroupResponse(VARIANT_BOOL *pVal)
{
	*pVal = m_DumpLoadGroups;
	return S_OK;
}

STDMETHODIMP CLBAMResponseDumper::put_DumpLoadGroupResponse(VARIANT_BOOL newVal)
{
	m_DumpLoadGroups = newVal;
	return S_OK;
}

STDMETHODIMP CLBAMResponseDumper::get_DumpInfluenceLines(VARIANT_BOOL *pVal)
{
	*pVal = m_DumpInfluenceLines;
	return S_OK;
}

STDMETHODIMP CLBAMResponseDumper::put_DumpInfluenceLines(VARIANT_BOOL newVal)
{
	m_DumpInfluenceLines = newVal;
	return S_OK;
}

STDMETHODIMP CLBAMResponseDumper::get_DumpContraflexure(VARIANT_BOOL *pVal)
{
	*pVal = m_DumpContraflexure;
	return S_OK;
}

STDMETHODIMP CLBAMResponseDumper::put_DumpContraflexure(VARIANT_BOOL newVal)
{
	m_DumpContraflexure = newVal;
	return S_OK;
}

STDMETHODIMP CLBAMResponseDumper::get_DumpEnvelopedVehicularResponse(VARIANT_BOOL *pVal)
{
	*pVal = m_DumpEnvelopedVehicularResponse;

	return S_OK;
}

STDMETHODIMP CLBAMResponseDumper::put_DumpEnvelopedVehicularResponse(VARIANT_BOOL newVal)
{
	m_DumpEnvelopedVehicularResponse = newVal;

	return S_OK;
}

STDMETHODIMP CLBAMResponseDumper::get_DumpLiveLoadModelResponse(VARIANT_BOOL *pVal)
{
	*pVal = m_LiveLoadModelResponse;

	return S_OK;
}

STDMETHODIMP CLBAMResponseDumper::put_DumpLiveLoadModelResponse(VARIANT_BOOL newVal)
{
	m_LiveLoadModelResponse = newVal;

	return S_OK;
}

STDMETHODIMP CLBAMResponseDumper::get_DumpLoadCaseResponse(VARIANT_BOOL *pVal)
{
	*pVal = m_LoadCaseResponse;

	return S_OK;
}

STDMETHODIMP CLBAMResponseDumper::put_DumpLoadCaseResponse(VARIANT_BOOL newVal)
{
	m_LoadCaseResponse = newVal;

	return S_OK;
}

STDMETHODIMP CLBAMResponseDumper::get_DumpLoadCombinationResponse(VARIANT_BOOL *pVal)
{
	*pVal = m_LoadCombinationResponse;

	return S_OK;
}

STDMETHODIMP CLBAMResponseDumper::put_DumpLoadCombinationResponse(VARIANT_BOOL newVal)
{
	m_LoadCombinationResponse = newVal;

	return S_OK;
}
