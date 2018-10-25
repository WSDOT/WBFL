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

   void DumpLoadCaseResponse(std::ostream& os);
   void DumpLoadCombinationResponse(std::ostream& os, std::ostream& cos);

private:
	CLoadCombinationDumper();

   void DumpLoadCaseForces(std::ostream& os, BSTR lcName, long ist, ResultsSummationType summ);
   void DumpLoadCaseDeflections(std::ostream& os, BSTR lcName, long ist, ResultsSummationType summ);
   void DumpLoadCaseStresses(std::ostream& os, BSTR lcName, long ist, ResultsSummationType summ);

   void DumpLoadCombinationForces(std::ostream& os, std::ostream& cos, const LcParams& params);
   void DumpLoadCombinationDeflections(std::ostream& os, std::ostream& cos, const LcParams& params);
   void DumpLoadCombinationReactions(std::ostream& os, std::ostream& cos, const LcParams& params);
   void DumpLoadCombinationSupportDeflections(std::ostream& os, std::ostream& cos, const LcParams& params);
   void DumpLoadCombinationStresses(std::ostream& os, std::ostream& cos, const LcParams& params);


   void DumpLoadCombinationConfiguration(std::ostream& os, ILoadCombinationResultConfiguration* config);

   CComPtr<ILBAMAnalysisEngine> m_Engine;
   CDumperUtil*                 m_Util;

   CComPtr<ILoadCombinationResponse>           m_LCR;
   CComPtr<IConcurrentLoadCombinationResponse> m_CCR;

   long                         m_LastKey;
};

#endif // !defined(AFX_LOADCOMBINATIONDUMPER_H__48A404A7_304C_4ADD_82A6_1AFF323B181D__INCLUDED_)
