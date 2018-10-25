///////////////////////////////////////////////////////////////////////
// Material - Analytical and Product modeling of civil engineering materials
// Copyright © 1999-2018  Washington State Department of Transportation
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

#ifndef INCLUDED_MATERIAL_CONCRETE_H_
#define INCLUDED_MATERIAL_CONCRETE_H_
#pragma once

// SYSTEM INCLUDES
//
#include <set>
#include <Material\MaterialExp.h>

// LOCAL INCLUDES
//

// FORWARD DECLARATIONS
//
class MATCLASS matConcreteListener;

// MISCELLANEOUS
//

/*****************************************************************************
CLASS 
   matConcrete

   Base class for Portland Cement concrete material product models.


DESCRIPTION
   Base class for Portland Cement concrete material product models.

LOG
   rab : 11.17.1997 : Created file
*****************************************************************************/

class MATCLASS matConcrete
{
public:
   enum Type { Normal, AllLightweight,SandLightweight };

   // GROUP: LIFECYCLE

   //------------------------------------------------------------------------
   // Default constructor.  Sets name to "Unknown" and density, fc, and 
   // modulus of elasticity to zero.
   matConcrete();

   //------------------------------------------------------------------------
   // Constructor.
   matConcrete(const std::_tstring& name,Float64 fc,Float64 density,Float64 modE);

   //------------------------------------------------------------------------
   // Copy constructor
   matConcrete(const matConcrete& rOther);

   // GROUP: OPERATORS
   //------------------------------------------------------------------------
   // Assignment operator
   matConcrete& operator = (const matConcrete& rOther);

   bool operator==(const matConcrete& rOther) const;
   bool operator!=(const matConcrete& rOther) const;

   //------------------------------------------------------------------------
   // Destructor
   virtual ~matConcrete();

   // GROUP: OPERATORS
   void SetType(Type type);
   Type GetType() const;

   void SetAggSplittingStrength(Float64 ft);
   Float64 GetAggSplittingStrength() const;
   bool HasAggSplittingStrength() const;
   void HasAggSplittingStrength(bool bHasFct);

   static std::_tstring GetTypeName(Type type,bool bFull);
   static Type GetTypeFromName(LPCTSTR strName);

   // GROUP: OPERATIONS

   //------------------------------------------------------------------------
   // Registers a concrete material listener with this object.  Listeners
   // are notified via the matConcreteListener interface whenever this 
   // object is modified.
   void RegisterListener(matConcreteListener* pListener);

   //------------------------------------------------------------------------
   // Unregisters a listener from this object.  The listener will no longer
   // receive event notifications from this object.  If the supplied
   // listener was not previously registered with this object, this method
   // does nothing.  If pListener is 0, all listeners are unregistered.
   void UnregisterListener(matConcreteListener* pListener);

   //------------------------------------------------------------------------
   virtual matConcrete* CreateClone(bool bRegisterListeners = false) const;

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
   void SetFc(Float64 fc);

   //------------------------------------------------------------------------
   Float64 GetFc() const;

   //------------------------------------------------------------------------
   void SetDensity(Float64 density);

   //------------------------------------------------------------------------
   Float64 GetDensity() const;

   //------------------------------------------------------------------------
   void SetE(Float64 modE);

   //------------------------------------------------------------------------
   Float64 GetE() const;

   //------------------------------------------------------------------------
   void SetMaxAggregateSize(Float64 size);

   //------------------------------------------------------------------------
   Float64 GetMaxAggregateSize() const;

   void SetLambda(Float64 lambda);
   Float64 GetLambda() const;

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

   // GROUP: OPERATIONS
   //------------------------------------------------------------------------
   void MakeCopy(const matConcrete& rOther);

   //------------------------------------------------------------------------
   virtual void MakeAssignment(const matConcrete& rOther);

   //------------------------------------------------------------------------
   // Must be called from subclass CreateClone methods.
   void RegisterListenersWithOther(matConcrete* pOther) const;

   //------------------------------------------------------------------------
   // Notifies all listeners through the OnConcreteChanged() callback.
   void NotifyAllListeners();

   // GROUP: ACCESS
   // GROUP: INQUIRY

private:
   // GROUP: DATA MEMBERS
   Type        m_Type;
   Float64     m_Fct;
   bool        m_bHasFct;
   std::_tstring m_Name;
   Float64     m_Fc;
   Float64     m_Density;
   Float64     m_ModE;
   Float64     m_MaxAggregateSize;
   Float64     m_Lambda;

   bool m_bIsDamaged;
   std::set<matConcreteListener*,std::less<matConcreteListener*>, std::allocator<matConcreteListener*> > m_Listeners;

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

#endif // INCLUDED_MATERIAL_CONCRETE_H_
