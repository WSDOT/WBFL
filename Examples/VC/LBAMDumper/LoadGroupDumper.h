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

   void DumpAnalysisPOIs(std::ostream& os);
   void DumpLoadGroupResponse(std::ostream& os);
   void DumpInfluenceLines(std::ostream& os);
   void DumpContraflexureResponse(std::ostream& os);

private:
   void DumpAPOIs(std::ostream& os);
   void DumpPOIDistributionFactors(std::ostream& os);
   void DumpPOIStressPoints(std::ostream& os);

   void DumpLoadGroupForces(std::ostream& os, BSTR lgName, long istage, ResultsSummationType summ);
   void DumpLoadGroupDeflections(std::ostream& os, BSTR lgName, long istage, ResultsSummationType summ);
   void DumpLoadGroupStresses(std::ostream& os, BSTR lgName, long istage, ResultsSummationType summ);

   void DumpForceInfluenceLines(std::ostream& os, long ist, ForceEffectType feType);
   void DumpDeflectionInfluenceLines(std::ostream& os, long ist, ForceEffectType feType);

   CComPtr<ILBAMAnalysisEngine> m_Engine;
   CDumperUtil*                 m_Util;
};

#endif // !defined(AFX_LOADGROUPDUMPER_H__0843B1BD_9861_4ACE_BF8C_BCA37796EEDB__INCLUDED_)
