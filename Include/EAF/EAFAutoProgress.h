
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
   EAFAutoProgress ap(pProgress);
   // Don't call CreateWindow or DestroyWindow on the IProgress interface
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
