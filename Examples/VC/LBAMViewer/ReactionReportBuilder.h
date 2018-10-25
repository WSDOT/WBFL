#ifndef INCLUDED_ReactionReportBuilder_H_
#define INCLUDED_ReactionReportBuilder_H_

#include "stdAfx.h"

class iReactionReportBuilder
{
public:
   // build report for reactions - uses CEdit returns
   virtual void BuildReactionReport(IIDArray* supportlist, BSTR currStg,
                                    CLBAMViewerDoc::ResponseType curr_rt, ResultsSummationType summ_type,
                                    std::_tostream& pos)=0;
};

#endif