// LBAMDumperDo.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <WBFLTools.h>
#include <WBFLLBAM.h>
#include <WBFLLBAMAnalysis.h>
#include <WBFLLBAMLiveLoader.h>
#include <WBFLLBAMLoadCombiner.h>

#include "..\LBAMDumper.h"
#include "..\LBAMDumper_i.c"

#include "WBFLLBAMAnalysisUtility_i.c"
#include "WBFLLBAM_i.c"
#include "WBFLTools_i.c"
#include <WBFLLBAMLiveLoader_i.c>


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CComModule _Module;

int main(int argc, char* argv[])
{
   int st = 0;
   ::CoInitialize(NULL);
   try
   {
      HRESULT hr;

      if (argc<3)
      {
         std::cout<<"Error - Command line must be of form:"<<std::endl
                  <<"  LBAMDump <inputLBAMXmlFileName> <outputFileName> <optionalDetailsOutputFileName>"<<std::endl
                  <<"Program Terminated"<<std::endl;
         throw st = -1;
      }

      CComPtr<ILBAMModel> model;

      // create an empty model
      model.CoCreateInstance(CLSID_LBAMModel);

      // set up analysis engines
      CComPtr<ILBAMAnalysisEngine> engine;
      hr = engine.CoCreateInstance(CLSID_LBAMAnalysisEngine);
      ATLASSERT(SUCCEEDED(hr));

   //   hr = m_pLBAMAnalysisEngine->Initialize(m_pModel, atForce);
   //   ATLASSERT(SUCCEEDED(hr));
      CComPtr<IEnvelopedVehicularResponse> envelopedVehicularResponse;
   #if defined _USE_ORIGINAL_LIVELOADER
      envelopedVehicularResponse.CoCreateInstance(CLSID_BruteForceVehicularResponse);
   #else
      envelopedVehicularResponse.CoCreateInstance(CLSID_BruteForceVehicularResponse2);
   #endif

      // initialize the engine with default values (NULL), except for the vehicular response enveloper
      engine->InitializeEx(model,atForce,
                           NULL, // load group response
                           NULL, // unit load response
                           NULL, // influence line response
                           NULL, // analysis pois
                           NULL, // basic vehicular response
                           NULL, // live load model response
                           envelopedVehicularResponse,
                           NULL, // load case response
                           NULL, // load combination response
                           NULL, // concurrent load combination response
                           NULL, // live load negative moment response
                           NULL); // contraflexure response

      CComPtr<IStructuredLoad2> pLoad;
      pLoad.CoCreateInstance(CLSID_StructuredLoad2);

      CComPtr<IStructuredStorage2> pSS;
      model->QueryInterface(&pSS);

      hr = pLoad->Open(CComBSTR(argv[1]));
      if (FAILED(hr))
      {
         std::cout<<"Error Opening File - Probably doesn't exist";
         return FALSE;
      }

      hr = pSS->Load(pLoad);
      if (FAILED(hr))
      {
         std::cout<<"An Error occurred while reading the XML file containing the LBAM model - perhaps it is not a valid LBAM file?"<<std::endl;
         throw st = -6;
      }

      pLoad->Close();



      // finally create our model dumper and procede to dump out results
      CComPtr<ILBAMResponseDumper> dumper;
      hr = dumper.CoCreateInstance(CLSID_LBAMResponseDumper);
      if (FAILED(hr))
      {
         std::cout<<"An Error occurred in CoCreateInstance(CLSID_LBAMResponseDumper). It is probably not registered on this system"<<std::endl;
         throw st = -9;
      }

      CComBSTR details;
      if  (argc>3)
      {
         details = argv[3];
      }

      // settings (not avialable from the command line, but useful for debugging
      hr = dumper->put_DumpLoadCombinationResponse(VARIANT_TRUE);
      hr = dumper->put_DumpLoadCaseResponse(VARIANT_TRUE);
      hr = dumper->put_DumpLiveLoadModelResponse(VARIANT_TRUE);
      hr = dumper->put_DumpEnvelopedVehicularResponse(VARIANT_TRUE);
      hr = dumper->put_DumpContraflexure(VARIANT_TRUE);
      hr = dumper->put_DumpInfluenceLines(VARIANT_TRUE);
      hr = dumper->put_DumpLoadGroupResponse(VARIANT_TRUE);
      hr = dumper->put_DumpModel(VARIANT_TRUE);

      hr = dumper->Dump(engine, CComBSTR(argv[2]), details);
      if (FAILED(hr))
      {
         std::cout<<"An Error occurred while dumping the response - check out the dump file (if it exists) for more info."<<std::endl;
         throw st = -10;
      }
   }
   catch(int i)
   {
      std::cout<<"Program Terminated. st = "<< i <<std::endl;
   }
   catch(...)
   {
      std::cout<<"An Unknown Error occurred"<<std::endl;
   }

   ::CoUninitialize();
	return st;
}

