
#pragma once

#include <EAF\EAFExp.h>
#include <EAF\EAFProgress.h>

/*****************************************************************************
CLASS 
   WBFL::EAF::AutoProgress

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

namespace WBFL
{
   namespace EAF
   {
      /// @brief Auto-pointer like class for the IEAFProgress interface.
      /// Code that creates progress windows must destroy them. When exceptions
      /// are thrown, the destroy code is often never called. This class encapsulates
      /// the destroy code and is automatically called as the stack unwinds.
      class EAFCLASS AutoProgress
      {
      public:
         AutoProgress(const AutoProgress&) = delete;
         AutoProgress(std::shared_ptr<IEAFProgress> pProgress,UINT nDelay = 500,DWORD dwMask = PW_ALL | PW_NOGAUGE | PW_NOCANCEL);
         ~AutoProgress();

         AutoProgress& operator=(const AutoProgress&) = delete;

         HRESULT Continue();

      private:
         std::shared_ptr<IEAFProgress> m_pProgress;
         bool m_bCreated;

         HRESULT CreateProgressWindow(DWORD dwMask,UINT nDelay);
      };
   };
};
