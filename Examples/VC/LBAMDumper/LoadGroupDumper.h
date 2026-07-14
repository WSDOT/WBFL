// LoadGroupDumper.h: interface for the CLoadGroupDumper class.
//
//////////////////////////////////////////////////////////////////////

#pragma once

class CDumperUtil;

class CLoadGroupDumper  
{
public:
	CLoadGroupDumper(ILBAMAnalysisEngine* engine, CDumperUtil* util);
	virtual ~CLoadGroupDumper();

   void DumpAnalysisPOIs(std::_tostream& os);
   void DumpLoadGroupResponse(std::_tostream& os);
   void DumpInfluenceLines(std::_tostream& os);
   void DumpContraflexureResponse(std::_tostream& os);

private:
   void DumpAPOIs(std::_tostream& os);
   void DumpPOIDistributionFactors(std::_tostream& os);
   void DumpPOIStressPoints(std::_tostream& os);

   void DumpLoadGroupForces(std::_tostream& os, BSTR lgName, StageIndexType istage, ResultsSummationType summ);
   void DumpLoadGroupDeflections(std::_tostream& os, BSTR lgName, StageIndexType istage, ResultsSummationType summ);
   void DumpLoadGroupStresses(std::_tostream& os, BSTR lgName, StageIndexType istage, ResultsSummationType summ);

   void DumpForceInfluenceLines(std::_tostream& os, StageIndexType ist, ForceEffectType feType);
   void DumpDeflectionInfluenceLines(std::_tostream& os, StageIndexType ist, ForceEffectType feType);

   CComPtr<ILBAMAnalysisEngine> m_Engine;
   CDumperUtil*                 m_Util;
};

