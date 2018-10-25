// LBAMDumperDo.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <WBFLTools.h>
#include <WBFLLBAM.h>
#include <WBFLLBAMAnalysis.h>
#include <WBFLLBAMLiveLoader.h>
#include <WBFLLBAMLoadCombiner.h>

#include "LBAMDumper.h"
#include "LBAMDumper_i.c"

#include "WBFLLBAMAnalysisUtility_i.c"
#include "WBFLLBAM_i.c"
#include "WBFLTools_i.c"


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

      // create our file loader
      CComPtr<IStructuredLoad2> sload;
      hr = sload.CoCreateInstance(CLSID_StructuredLoad2);
      if (FAILED(hr))
      {
         std::cout<<"An Error occurred in CoCreateInstance(CLSID_StructuredLoad2). WBFLTools is probably not registered on this system"<<std::endl;
         throw st = -2;
      }

      hr = sload->Open(CComBSTR(argv[1]));
      if (FAILED(hr))
      {
         std::cout<<"An Error occurred while opening the XML file containing the LBAM model - perhaps it is not a valid XML/LBAM file?"<<std::endl;
         throw st = -3;
      }

      // open and create lbam model file and initialize our engine
      CComPtr<ILBAMModel> model;
      hr = model.CoCreateInstance(CLSID_LBAMModel);
      if (FAILED(hr))
      {
         std::cout<<"An Error occurred in CoCreateInstance(CLSID_LBAMModel). The LBAM is probably not registered on this system"<<std::endl;
         throw st = -4;
      }

      CComQIPtr<IStructuredStorage2> piss(model);
      if (piss==NULL)
      {
         std::cout<<"An Error during QueryInterface of the LBAM model to IStructuredStorage2 - this should not happen"<<std::endl;
         throw st = -5;
      }

      // finally load up our model
      hr = piss->Load(sload);
      if (FAILED(hr))
      {
         std::cout<<"An Error occurred while reading the XML file containing the LBAM model - perhaps it is not a valid LBAM file?"<<std::endl;
         throw st = -6;
      }

      // create and init the engine needed for analysis
      CComPtr<ILBAMAnalysisEngine> engine;
      hr = engine.CoCreateInstance(CLSID_LBAMAnalysisEngine);
      if (FAILED(hr))
      {
         std::cout<<"An Error occurred in CoCreateInstance(CLSID_LBAMAnalysisEngine). The LBAMAnalysisUtility is probably not registered on this system"<<std::endl;
         throw st = -7;
      }

      hr = engine->Initialize(model, atForce);
      if (FAILED(hr))
      {
         std::cout<<"An Error occurred while initializing the analysis engine"<<std::endl;
         throw st = -8;
      }

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

