// ModelDumper.h: interface for the CModelDumper class.
//
//////////////////////////////////////////////////////////////////////
#include <ostream>
#include <WBFLLBAM.h>

#include "DumperUtils.h"

#pragma once

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

