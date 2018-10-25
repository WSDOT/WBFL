#ifndef INCLUDED_REINFORCEDCONCRETE_IDIALOGUNITPERSISTENCE_H_
#define INCLUDED_REINFORCEDCONCRETE_IDIALOGUNITPERSISTENCE_H_

// SYSTEM INCLUDES
//

// PROJECT INCLUDES
//

// LOCAL INCLUDES
//

// FORWARD DECLARATIONS
//

// MISCELLANEOUS
//

/*****************************************************************************
CLASS 
   uicIDialogUnitPersistence

   This class defines the interface to provide storage of unit information
   for dialog widgets such as CUnitControlT.


DESCRIPTION
   This class provides a Persistence interface for dialog widgets that need
   to store and retrieve unit information.


COPYRIGHT
   Copyright (c) 1997
   Washington State Department Of Transportation
   All Rights Reserved

LOG
   rdp : 03.20.1998 : Created file
*****************************************************************************/

class  uicIDialogUnitPersistence
{
public:
   // GROUP: LIFECYCLE
   virtual ~uicIDialogUnitPersistence() {}
   // GROUP: OPERATORS
   // GROUP: OPERATIONS

   //------------------------------------------------------------------------
   // Save off the units for the dialog prior to destruction of the dialog
   // widget
   virtual void SetLastUnit(int dlg,int ctrl,const std::string& unit)=0;

   //------------------------------------------------------------------------
   // Get the last used units for the dialog widget. Returns an empty string
   // if it fails to retrieve a default.
   virtual std::string  GetLastUnit(int dlg,int ctrl)=0;

   // GROUP: ACCESS
   // GROUP: INQUIRY
   // GROUP: DEBUG

protected:
   // GROUP: DATA MEMBERS
   // GROUP: LIFECYCLE
   // GROUP: OPERATORS
   // GROUP: OPERATIONS
   // GROUP: ACCESS
   // GROUP: INQUIRY

private:
   // GROUP: DATA MEMBERS
   // GROUP: LIFECYCLE

   // GROUP: OPERATORS
   // GROUP: OPERATIONS
   // GROUP: ACCESS
   // GROUP: INQUIRY
};

// INLINE METHODS
//

// EXTERNAL REFERENCES
//

#endif // INCLUDED_REINFORCEDCONCRETE_IDIALOGUNITPERSISTENCE_H_
