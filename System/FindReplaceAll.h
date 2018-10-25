#ifndef INCLUDED_FINDREPLACEALL_H_
#define INCLUDED_FINDREPLACEALL_H_

inline bool find_replace_all(std::_tstring* ptarget, const std::_tstring& find, const std::_tstring& replace)
{
   bool ret=false;
   std::_tstring::size_type spos=0;
   std::_tstring::size_type epos;
   
   while ( (epos=ptarget->find(find,spos)) != std::_tstring::npos)
   {
      ret=true;
      ptarget->replace(epos,find.size(),replace);
      spos = epos+1;
   }

   return ret;
}

#endif