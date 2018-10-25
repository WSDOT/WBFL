
#pragma once

#include <EAF\EAFExp.h>

interface IProgress;

/*****************************************************************************
CLASS 
   CEAFAutoProgress

   Auto-pointer like class for the IProgress interface.


DESCRIPTION
   Auto-pointer like class for the IProgress interface.
   Code that creates progress windows must destroy them.  When exceptions
   are throw, the destroy code is often never called.  This class encapsulates
   the destroy code and is automatically called as the stack unwinds.

   You must create the progress window using the CreateProgressWindow
   on this class, instead of the IProgress pointer, to have the auto destory
   work properly.

EXAMPLE
   pgsAutoProgress ap(pProgress);
   ap.CreateWindow(PW_ALL,1000);
   // Don't do this  pProgress->CreateWindow(PW_ALL,1000);
   // Don't do this either pProgress->DestroyWindow


COPYRIGHT
   Copyright © 1997-1998
   Washington State Department Of Transportation
   All Rights Reserved

LOG
   rab : 12.02.1998 : Created file
*****************************************************************************/

class EAFCLASS CEAFAutoProgress
{
public:
   //------------------------------------------------------------------------
   // Default constructor
   CEAFAutoProgress(IProgress* pProgress,UINT nDelay = 100);

   //------------------------------------------------------------------------
   // Destructor
   ~CEAFAutoProgress();

   HRESULT CreateProgressWindow(DWORD dwMask,UINT nDelay);
   HRESULT Continue();

private:
   IProgress* m_pProgress; // weak reference
   bool m_bCreated;

   // Prevent accidental copying and assignment
   CEAFAutoProgress(const CEAFAutoProgress&);
   CEAFAutoProgress& operator=(const CEAFAutoProgress&);
};
