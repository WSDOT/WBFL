
#pragma once

#include <EAF\EAFExp.h>
#include <WBFLCore.h>

/*****************************************************************************
CLASS 
   CEAFAutoProgress

   Auto-pointer like class for the IProgress interface.


DESCRIPTION
   Auto-pointer like class for the IProgress interface.
   Code that creates progress windows must destroy them.  When exceptions
   are throw, the destroy code is often never called.  This class encapsulates
   the destroy code and is automatically called as the stack unwinds.

EXAMPLE
   EAFAutoProgress ap(pProgress);
   // Don't call CreateWindow or DestroyWindow on the IProgress interface
*****************************************************************************/

class EAFCLASS CEAFAutoProgress
{
public:
   //------------------------------------------------------------------------
   // Default constructor
   CEAFAutoProgress(IProgress* pProgress,UINT nDelay = 500,DWORD dwMask = PW_ALL | PW_NOGAUGE | PW_NOCANCEL);

   //------------------------------------------------------------------------
   // Destructor
   ~CEAFAutoProgress();

   HRESULT Continue();

private:
   IProgress* m_pProgress; // weak reference
   bool m_bCreated;

   HRESULT CreateProgressWindow(DWORD dwMask,UINT nDelay);

   // Prevent accidental copying and assignment
   CEAFAutoProgress(const CEAFAutoProgress&);
   CEAFAutoProgress& operator=(const CEAFAutoProgress&);
};
