///////////////////////////////////////////////////////////////////////
// Material - Analytical and Product modeling of civil engineering materials
// Copyright © 1999-2017  Washington State Department of Transportation
//                        Bridge and Structures Office
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
// Transportation, Bridge and Structures Office, P.O. Box  47340, 
// Olympia, WA 98503, USA or e-mail Bridge_Support@wsdot.wa.gov
///////////////////////////////////////////////////////////////////////

#ifndef INCLUDED_MATERIAL_METAL_H_
#define INCLUDED_MATERIAL_METAL_H_
#pragma once

// SYSTEM INCLUDES
//
#include <set>
#include <Material\MaterialExp.h>

// LOCAL INCLUDES
//

// FORWARD DECLARATIONS
//
class MATCLASS matMetalListener;

// MISCELLANEOUS
//

/*****************************************************************************
CLASS 
   matMetal

   Base class for metallic material product models.


DESCRIPTION
   Base class for metallic material product models.

LOG
   rab : 11.17.1997 : Created file
*****************************************************************************/

class MATCLASS matMetal
{
public:
   // GROUP: LIFECYCLE

   //------------------------------------------------------------------------
   // Constructor. Initializes the object with the supplied parameters.
   matMetal(const std::_tstring& name,
            Float64 density,
            Float64 modE,
            Float64 yieldStress,
            Float64 ultStrain,
            Float64 ultStress,
            Float64 ruptureStrain,
            Float64 ruptureStress);

   //------------------------------------------------------------------------
   // Constructor.  Creates an elastic-perfectly plastic material.
   matMetal(const std::_tstring& name,
            Float64 density,
            Float64 modE,
            Float64 yieldStress);

   //------------------------------------------------------------------------
   // Destructor
   virtual ~matMetal();

   // GROUP: OPERATORS
   // GROUP: OPERATIONS

   //------------------------------------------------------------------------
   void RegisterListener(matMetalListener* pListener);

   //------------------------------------------------------------------------
   void UnregisterListener(matMetalListener* pListener);

   //------------------------------------------------------------------------
   virtual matMetal* CreateClone(bool bRegisterListeners = false) const;

   //------------------------------------------------------------------------
   // Clients of this class should call this method prior to making
   // wholesale changes to prevent unnecessary updates.  This call
   // disables the notification mechanism.  This call must be paired with
   // a call to EndDamage().
   void BeginDamage();

   //------------------------------------------------------------------------
   // Clients of this class should call this method after making
   // wholesale.  This call enables the notification mechanism. 
   // This call must be paired with a call to BeginDamage().
   void EndDamage();

   // GROUP: ACCESS

   //------------------------------------------------------------------------
   void SetName(const std::_tstring& name);

   //------------------------------------------------------------------------
   std::_tstring GetName() const;

   //------------------------------------------------------------------------
   void SetDensity(Float64 density);

   //------------------------------------------------------------------------
   Float64 GetDensity() const;

   //------------------------------------------------------------------------
   void SetE(Float64 modE);

   //------------------------------------------------------------------------
   Float64 GetE() const;

   //------------------------------------------------------------------------
   void SetYieldStress(Float64 yieldStress);

   //------------------------------------------------------------------------
   Float64 GetYieldStress() const;

   //------------------------------------------------------------------------
   Float64 GetYieldStrain() const;

   //------------------------------------------------------------------------
   void SetUltStrain(Float64 ultStrain);

   //------------------------------------------------------------------------
   Float64 GetUltStrain() const;

   //------------------------------------------------------------------------
   void SetUltStress(Float64 ultStress);

   //------------------------------------------------------------------------
   Float64 GetUltStress() const;

   //------------------------------------------------------------------------
   void SetRuptureStrain(Float64 ruptureStrain);

   //------------------------------------------------------------------------
   Float64 GetRuptureStrain() const;

   //------------------------------------------------------------------------
   void SetRuptureStress(Float64 ruptureStress);

   //------------------------------------------------------------------------
   Float64 GetRuptureStress() const;

   // GROUP: INQUIRY

   //------------------------------------------------------------------------
   // Returns the number of listeners registered with this object.
   CollectionIndexType ListenerCount() const;

   //------------------------------------------------------------------------
   // Returns true if in the damaged state.
   bool IsDamaged() const;

   // GROUP: DEBUG
#if defined _DEBUG
   //------------------------------------------------------------------------
   // Returns <b>true</b> if the class is in a valid state, otherwise returns
   // <b>false</b>.
   virtual bool AssertValid() const;

   //------------------------------------------------------------------------
   // Dumps the contents of the class to the given stream.
   virtual void Dump(dbgDumpContext& os) const;
#endif // _DEBUG

#if defined _UNITTEST
   //------------------------------------------------------------------------
   // Self-diagnostic test function.  Returns <b>true</b> if the test passes,
   // otherwise return <b>false</b>.
   static bool TestMe(dbgLog& rlog);
#endif // _UNITTEST

protected:
   // GROUP: DATA MEMBERS
   // GROUP: LIFECYCLE

   //------------------------------------------------------------------------
   // Copy constructor
   matMetal(const matMetal& rOther);

   // GROUP: OPERATORS

   //------------------------------------------------------------------------
   // Assignment operator
   matMetal& operator = (const matMetal& rOther);

   // GROUP: OPERATIONS
   //------------------------------------------------------------------------
   void MakeCopy(const matMetal& rOther);

   //------------------------------------------------------------------------
   void MakeAssignment(const matMetal& rOther);

   //------------------------------------------------------------------------
   void NotifyAllListeners();

   // GROUP: ACCESS
   // GROUP: INQUIRY

private:
   // GROUP: DATA MEMBERS
   std::_tstring m_Name;
   Float64 m_Density;
   Float64 m_ModE;
   Float64 m_YieldStress;
   Float64 m_UltStrain;
   Float64 m_UltStress;
   Float64 m_RuptureStrain;
   Float64 m_RuptureStress;

   bool m_bIsDamaged;
   std::set<matMetalListener*, std::less<matMetalListener*>, std::allocator<matMetalListener*> > m_Listeners;

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

#endif // INCLUDED_MATERIAL_METAL_H_
