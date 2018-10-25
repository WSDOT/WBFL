#ifndef INCLUDED_LIBRARYHINTS_H_
#define INCLUDED_LIBRARYHINTS_H_

// This file contains all the hints sent by the library editor when
// it edits or renames enties

// entries are made to be or'ed together
namespace LibraryHints
{
   const int EntryRenamed = 2;
   const int EntryEdited  = 4;
};

#endif // INCLUDED_LIBRARYHINTS_H_