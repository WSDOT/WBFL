
#if !defined INCLUDED_UTILITYUTILS_H_
#define INCLUDED_UTILITYUTILS_H_

#include "ComException.h"

// macros to help error processing
// short-hand version if consistent naming conventions are used
#define THROW_LBAMAU(errNam) { ATLASSERT(0); throw CComException(__FILE__,__LINE__, IDS_E_##errNam, LBAMU_E_##errNam, IDH_E_##errNam);}
#define THROW_LBAMAU_MSG(errNam, msg) { ATLASSERT(0); throw CComException(__FILE__,__LINE__, msg, LBAMU_E_##errNam, IDH_E_##errNam);}

inline CComBSTR GetHelpFile()
{
   return CComBSTR("WBFLLBAM.chm");
}

#endif 