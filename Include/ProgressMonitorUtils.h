///////////////////////////////////////////////////////////////////////
// ProgressMonitorUtils.h - Utilities for progress monitoring
// Copyright © 2000  Washington State Department of Transportation
//                   Bridge and Structures Office
//
// This library is a part of the Washington Bridge Foundation Libraries
// and was developed as part of the Alternate Route Project
//
// This library is free software; you can redistribute it and/or modify it under
// the terms of the Alternate Route Library Open Source License as published by 
// the Washington State Department of Transportation, Bridge and Structures Office.
//
// This program is distributed in the hope that it will be useful, but is distributed 
// AS IS, WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY 
// or FITNESS FOR A PARTICULAR PURPOSE. See the Alternate Route Library Open Source 
// License for more details.
//
// You should have received a copy of the Alternate Route Library Open Source License 
// along with this program; if not, write to the Washington State Department of 
// Transportation, Bridge and Structures Office, 4500 3rd Ave SE - P.O. Box  47340, 
// Olympia, WA 98503, USA or e-mail Bridge_Support@wsdot.wa.gov
///////////////////////////////////////////////////////////////////////

#ifndef INCLUDED_PROGRESSMONITORUTILS_H_
#define INCLUDED_PROGRESSMONITORUTILS_H_

// Simple class that calls Hide() in its destructor. Makes showing progress window exception-safe

template <class T>
class CAutoHide
{
public:
   CAutoHide(T* pt):
   m_pT(pt)
   {
      ATLASSERT(pt!=NULL);
   }

   ~CAutoHide()
   {
      HRESULT hr = m_pT->Hide();
      ATLASSERT(SUCCEEDED(hr));
   }

private:
   CAutoHide();

   T* m_pT;
};

typedef CAutoHide<IProgressMonitorWindow> CProgressAutoHide; 


#endif // INCLUDED_PROGRESSMONITORUTILS_H_