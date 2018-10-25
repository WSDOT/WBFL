#ifndef INCLUDED_FINDREPLACEALL_H_
#define INCLUDED_FINDREPLACEALL_H_

inline bool find_replace_all(std::string* ptarget, const std::string& find, const std::string& replace)
{
   bool ret=false;
   std::string::size_type spos=0;
   std::string::size_type epos;
   
   while ( (epos=ptarget->find(find,spos)) != std::string::npos)
   {
      ret=true;
      ptarget->replace(epos,find.size(),replace);
      spos = epos+1;
   }

   return ret;
}

#endif