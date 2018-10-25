// ModelDumper.h: interface for the CModelDumper class.
//
//////////////////////////////////////////////////////////////////////
#include <ostream>
#include <WBFLLBAM.h>

#include "DumperUtils.h"


#if !defined(AFX_MODELDUMPER_H__8E36C2E3_7DC6_4A3A_BD81_7F27E8B4F8D2__INCLUDED_)
#define AFX_MODELDUMPER_H__8E36C2E3_7DC6_4A3A_BD81_7F27E8B4F8D2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CModelDumper  
{
public:
	CModelDumper( CDumperUtil* util);
	virtual ~CModelDumper();
   CDumperUtil*                 m_Util;

   void DumpModel(std::_tostream& os, ILBAMModel* model);

private:
	CModelDumper();
   void DumpSegmentData(std::_tostream& os, IFilteredSegmentCollection* segments);
   void DumpSSMData(std::_tostream& os, ILBAMModel* model);
   void DumpPOIData(std::_tostream& os, ILBAMModel* model);
   void DumpPointLoadData(std::_tostream& os, ILBAMModel* model);
   void DumpTempSupportData(std::_tostream& os, ILBAMModel* model);
   void DumpSupportData(std::_tostream& os, ILBAMModel* model);

};

#endif // !defined(AFX_MODELDUMPER_H__8E36C2E3_7DC6_4A3A_BD81_7F27E8B4F8D2__INCLUDED_)
