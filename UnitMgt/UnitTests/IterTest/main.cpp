#include <UnitMgt\Library.h>
#include <iostream>

int main(void)
{
   std::ostream os = std::cout;

   unitmgtLibrary my_lib;

   my_lib.AddEntry("SI",unitmgtIndirectMeasure() );
   my_lib.AddEntry("English",unitmgtIndirectMeasure() );
   my_lib.AddEntry("Bob's Favorite",unitmgtIndirectMeasure() );


   os << "Iterator test" << std::endl;
   unitmgtLibraryIter iter(my_lib);
   for ( iter.First(); !iter.IsDone(); iter.Next() )
   {
      os << iter.CurrentKey().c_str() << std::endl;
#if defined _DEBUG
      CHECK( iter.CurrentValue().AssertValid() );
      iter.CurrentValue().Dump( os );
//#endif
   }

   os << std::endl;

   os << "Const Iterator test" << std::endl;
   unitmgtConstLibraryIter const_iter(my_lib);
   for ( const_iter.First(); !const_iter.IsDone(); const_iter.Next() )
   {
      os << const_iter.CurrentKey().c_str() << std::endl;
#if defined _DEBUG
      iter.CurrentValue().Dump( os );
//#endif
   }

   return 1;
}