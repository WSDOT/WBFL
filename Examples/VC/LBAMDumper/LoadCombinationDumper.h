// LoadCombinationDumper.h: interface for the CLoadCombinationDumper class.
//
//////////////////////////////////////////////////////////////////////

#pragma once

#include "DumperUtils.h"

struct LcParams;

class CLoadCombinationDumper  
{
public:
	CLoadCombinationDumper(ILBAMAnalysisEngine* engine, CDumperUtil* util);
	virtual ~CLoadCombinationDumper();

   void DumpLoadCaseResponse(std::_tostream& os);
   void DumpLoadCombinationResponse(std::_tostream& os, std::_tostream& cos);

private:
	CLoadCombinationDumper();

   void DumpLoadCaseForces(std::_tostream& os, BSTR lcName, StageIndexType ist, ResultsSummationType summ);
   void DumpLoadCaseDeflections(std::_tostream& os, BSTR lcName, StageIndexType ist, ResultsSummationType summ);
   void DumpLoadCaseStresses(std::_tostream& os, BSTR lcName, StageIndexType ist, ResultsSummationType summ);

   void DumpLoadCombinationForces(std::_tostream& os, std::_tostream& cos, const LcParams& params);
   void DumpLoadCombinationDeflections(std::_tostream& os, std::_tostream& cos, const LcParams& params);
   void DumpLoadCombinationReactions(std::_tostream& os, std::_tostream& cos, const LcParams& params);
   void DumpLoadCombinationSupportDeflections(std::_tostream& os, std::_tostream& cos, const LcParams& params);
   void DumpLoadCombinationStresses(std::_tostream& os, std::_tostream& cos, const LcParams& params);


   void DumpLoadCombinationConfiguration(std::_tostream& os, ILoadCombinationResultConfiguration* config);

   CComPtr<ILBAMAnalysisEngine> m_Engine;
   CDumperUtil*                 m_Util;

   CComPtr<ILoadCombinationResponse>           m_LCR;
   CComPtr<IConcurrentLoadCombinationResponse> m_CCR;

   long                         m_LastKey;
};

