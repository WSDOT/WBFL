#ifndef INCLUDED_REINFORCEDCONCRETE_TESTLOGGER_H_
#define INCLUDED_REINFORCEDCONCRETE_TESTLOGGER_H_

// SYSTEM INCLUDES
//
#include <ostream>
#include <string>
#include <vector>
// PROJECT INCLUDES
//

// LOCAL INCLUDES
//

// FORWARD DECLARATIONS
//

// MISCELLANEOUS
//

// Test macros
// have to create these temp ostringstreams because of a locale issue.

#define TESTME_PROLOGUE bool bpf=true; \
                        rlog.os << "Entering "<<__FILE__<<" Line "<<__LINE__<<std::endl;

#define TESTME_EPILOG   rlog.os << "Exiting "<<__FILE__<<" Line "<<__LINE__<<std::endl; \
                        return bpf;

#define TEST_FAIL       {std::ostringstream erro; \
                         erro <<"*** Failed at "<<__FILE__<<" Line "<<__LINE__<<std::endl; \
                         rlog.AddEntryToLog(erro.str(), true); \
                         rlog.os << erro.str(); \
                         bpf = false;}

#define TEST_PASS       {std::ostringstream erro; \
                         erro <<"    Passed at "<<__FILE__<<" Line "<<__LINE__<<std::endl; \
                         rlog.AddEntryToLog(erro.str(), false); \
                         rlog.os << erro.str();}

#define TRY_TEST(pf)    if (! (pf)) \
                           TEST_PASS \
                        else \
                           TEST_FAIL 
                            
/*****************************************************************************
CLASS 
   dbgTestLogger

   Message Logging class for unit testing


DESCRIPTION


COPYRIGHT
   Copyright © 1997-1998
   Washington State Department Of Transportation
   All Rights Reserved

LOG
   rdp : 05.27.1998 : Created file
*****************************************************************************/

class SYSCLASS dbgTestLogger
{
public:
   // GROUP: LIFECYCLE

   //------------------------------------------------------------------------
   // Default constructor - all information gets dumped to screen
   dbgTestLogger();

   //------------------------------------------------------------------------
   // Constructor - specify where information piped to ostream goes to.
   dbgTestLogger(std::ostream& os);

   //------------------------------------------------------------------------
   // Destructor
   virtual ~dbgTestLogger();

   // GROUP: OPERATORS
   // GROUP: OPERATIONS
   //------------------------------------------------------------------------
   // Add an entry to the error log.
   void AddEntryToLog(std::string& msg, bool isError);

   //------------------------------------------------------------------------
   // Get total number of entries in log
   Int32 GetNumEntries() const;

   //------------------------------------------------------------------------
   // Get number of errors in log
   Int32 GetNumErrors() const;

   //------------------------------------------------------------------------
   // Dump only errors in log
   void DumpErrorsInLog(std::ostream& os);

   //------------------------------------------------------------------------
   // Dump all entries in log
   void DumpEntireLog(std::ostream& os);

   // GROUP: ACCESS
   // GROUP: INQUIRY
   //------------------------------------------------------------------------
   // Public access to the dump ostream. Pipe all information that you want
   // to show the status of testing to this.
   std::ostream& os;

protected:
   // GROUP: DATA MEMBERS
   // GROUP: LIFECYCLE
   // GROUP: OPERATORS
   // GROUP: OPERATIONS
   // GROUP: ACCESS
   // GROUP: INQUIRY

private:
   // GROUP: DATA MEMBERS
   //------------------------------------------------------------------------
   // store the error log as a vector of strings
   struct LogEntry
   {
      bool IsError;
      std::string Msg;
   };
   typedef std::vector<LogEntry> EntryVec;
   typedef EntryVec::iterator    EntryVecIterator;
   EntryVec m_ErrorLog;

   Int32    m_NumErrors;

   // GROUP: LIFECYCLE
   //------------------------------------------------------------------------
   // Copy constructor
   dbgTestLogger(const dbgTestLogger& rOther);
   //------------------------------------------------------------------------
   // Assignment operator
   dbgTestLogger& operator = (const dbgTestLogger& rOther);
   // GROUP: OPERATORS
   // GROUP: OPERATIONS
   // GROUP: ACCESS
   // GROUP: INQUIRY

public:
   // GROUP: DEBUG
};

// INLINE METHODS
//

// EXTERNAL REFERENCES
//

#endif // INCLUDED_REINFORCEDCONCRETE_TESTLOGGER_H_
