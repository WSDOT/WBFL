// LoadGroupDumper.h: interface for the CLoadGroupDumper class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_LOADGROUPDUMPER_H__0843B1BD_9861_4ACE_BF8C_BCA37796EEDB__INCLUDED_)
#define AFX_LOADGROUPDUMPER_H__0843B1BD_9861_4ACE_BF8C_BCA37796EEDB__INCLUDED_



#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

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

#endif // !defined(AFX_LOADGROUPDUMPER_H__0843B1BD_9861_4ACE_BF8C_BCA37796EEDB__INCLUDED_)
