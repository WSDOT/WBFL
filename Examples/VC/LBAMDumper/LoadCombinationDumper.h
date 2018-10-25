// LoadCombinationDumper.h: interface for the CLoadCombinationDumper class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_LOADCOMBINATIONDUMPER_H__48A404A7_304C_4ADD_82A6_1AFF323B181D__INCLUDED_)
#define AFX_LOADCOMBINATIONDUMPER_H__48A404A7_304C_4ADD_82A6_1AFF323B181D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

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

#endif // !defined(AFX_LOADCOMBINATIONDUMPER_H__48A404A7_304C_4ADD_82A6_1AFF323B181D__INCLUDED_)
