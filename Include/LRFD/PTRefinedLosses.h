///////////////////////////////////////////////////////////////////////
// LRFD - Utility library to support equations, methods, and procedures
//        from the AASHTO LRFD Bridge Design Specification
// Copyright © 1999-2013  Washington State Department of Transportation
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

#ifndef INCLUDED_LRFD_PTREFINEDLOSSES_H_
#define INCLUDED_LRFD_PTREFINEDLOSSES_H_
#pragma once

// SYSTEM INCLUDES
//

// PROJECT INCLUDES
//
#include <Lrfd\LrfdExp.h>
#include <Lrfd\PsStrand.h>
#include <Lrfd\VersionMgrListener.h>

// LOCAL INCLUDES
//

// FORWARD DECLARATIONS
//

// MISCELLANEOUS
//

/*****************************************************************************
CLASS 
   lrfdPTRefinedLosses

   Utility class for computing losses using the LRFD Refined Estimate
   Method for post-tension memebers.


DESCRIPTION
   Utility class for computing losses using the LRFD Refined Estimate
   Method. Encapsulates Articles 5.9.5.2.3 and 5.9.5.4.


COPYRIGHT
   Copyright (c) 1997-2003
   Washington State Department Of Transportation
   All Rights Reserved

LOG
   rab : 05.06.2003 : Created file
*****************************************************************************/

class LRFDCLASS lrfdPTRefinedLosses : public lrfdVersionMgrListener
{
public:

   // GROUP: LIFECYCLE

   //------------------------------------------------------------------------
   // Default constructor.
   // Strand type = LowRelaxation
   // Relative Humidity = 70%
   // Ep = 197000 MPa
   // Eci = 25000 MPa
   // fpu = 1860 MPa
   // fpj = 0.80*fpu
   // fpy = 0.90*fpu
   // Time to prestress transfer = 1 day
   // Aps = 1mm^2
   // A = 1mm^2
   // I = 1mm^4
   // e = 0 mm
   // Mg = 0 N-m
   // Mdl = 0 N-m
   lrfdPTRefinedLosses();

   //------------------------------------------------------------------------
   // Constructor.  Initializes the object with the give values.
   // fpy is initialized to 0.85fpu for StressRelieved strands and
   // 0.90fpu for LowRelaxation strands.
   lrfdPTRefinedLosses(matPsStrand::Grade gr,
                matPsStrand::Type type,
				    Float64 fpj,    // Actual jacking stress
                Float64 Ag,     // area of girder
                Float64 Ig,     // moment of inertia of girder
                Float64 Ybg,    // centroid of girder measured from bottom
                Float64 Ic,     // moment of inertia of composite
                Float64 Ybc,    // centroid of composite measured from bottom
                Float64 e,      // eccentricity of ps strands
                Float64 Aps,    // area of ps strands
                Float64 Mdlg,   // Dead load moment of girder only
                Float64 Madlg,  // Additional dead load on girder
                Float64 Msidl,  // Superimposed dead loads
                Float64 rh,     // Relative humidity [0,100]
                Float64 Eci,    // Modulus of elasticity of concrete at transfer
                Float64 dfFR,   // Friction losses
                Float64 Fcgp,
                Float64 dfES);

   //------------------------------------------------------------------------
   // Copy c'tor
   lrfdPTRefinedLosses(const lrfdPTRefinedLosses& rOther);

   //------------------------------------------------------------------------
   // Destructor
   ~lrfdPTRefinedLosses();

   // GROUP: OPERATORS

   //------------------------------------------------------------------------
   // Assignment operator
   lrfdPTRefinedLosses& operator=(const lrfdPTRefinedLosses& rOther);

   // GROUP: OPERATIONS

   //------------------------------------------------------------------------
   // Called by lrfdVersion when ever the code version or unit system changes
   void OnUpdate();

   //------------------------------------------------------------------------
   Float64 ShrinkageLosses() const;

   //------------------------------------------------------------------------
   Float64 CreepLosses() const;

   //------------------------------------------------------------------------
   Float64 RelaxationLossesAfterXfer() const;

   //------------------------------------------------------------------------
   Float64 FinalLosses() const;

   //------------------------------------------------------------------------
   Float64 GetDeltaFcdp() const;

   //------------------------------------------------------------------------
   Float64 GetFpy() const;

   //------------------------------------------------------------------------
   Float64 GetEp() const;

   // GROUP: ACCESS
   //------------------------------------------------------------------------
   void SetStrandType(matPsStrand::Type type);
   matPsStrand::Type GetStrandType() const;
   void SetStrandGrade(matPsStrand::Grade gr);
   matPsStrand::Grade GetStrandGrade() const;
   void SetFpj(Float64 fpj);
   Float64 GetFpj() const;
   void SetAg(Float64 Ag);
   Float64 GetAg() const;
   void SetIg(Float64 Ig);
   Float64 GetIg() const;
   void SetYbg(Float64 Ybg);
   Float64 GetYbg() const;
   void SetIc(Float64 Ic);
   Float64 GetIc() const;
   void SetYbc(Float64 Ybc);
   Float64 GetYbc() const;
   void SetEcc(Float64 e);
   Float64 GetEcc() const;
   void SetAreaPT(Float64 Aps);
   Float64 GetAreaPT() const;
   void SetGdrMoment(Float64 Mdlg);
   Float64 GetGdrMoment() const;
   void SetAddlGdrMoment(Float64 Madlg);
   Float64 GetAddlGdrMoment() const;
   void SetSidlMoment(Float64 Msidl);
   Float64 GetSidlMoment() const;
   void SetRelativeHumidity(Float64 rh);
   Float64 GetRelativeHumidity() const;
   void SetEci(Float64 Eci);
   Float64 GetEci() const;
   void SetN(Float64 n);
   Float64 GetN() const;
   void SetFR(Float64 fr);
   Float64 GetFR() const;
   void SetFcgp(Float64 f);
   Float64 GetFcgp() const;
   void SetES(Float64 es);
   Float64 GetES() const;

   // GROUP: INQUIRY
   // GROUP: DEBUG
   #if defined _UNITTEST
   static bool TestMe(dbgLog& rlog);
   #endif // _UNITTEST

protected:
   // GROUP: DATA MEMBERS
   // GROUP: LIFECYCLE
   // GROUP: OPERATORS
   // GROUP: OPERATIONS

   //------------------------------------------------------------------------
   void MakeAssignment( const lrfdPTRefinedLosses& rOther );

   // GROUP: ACCESS
   // GROUP: INQUIRY

private:
   // GROUP: DATA MEMBERS
   matPsStrand::Type m_Type;
   matPsStrand::Grade m_Grade;
   Float64 m_Ag;    // Area of the girder
   Float64 m_Ig;    // Moment of inertia of the girder
   Float64 m_Ybg;   // Centroid of girder measured from bottom
   Float64 m_Ic;    // Moment of inertia of composite
   Float64 m_Ybc;   // Centroid of composite measured from bottom
   Float64 m_e;     // Eccenricity of prestress force
   Float64 m_Aps;   // Area of ps strands
   Float64 m_Mdlg;  // Dead load moment of girder
   Float64 m_Madlg; // Additional dead load moment on girder section
   Float64 m_Msidl; // Superimposed dead loads
   Float64 m_Rh;
   Float64 m_Eci;

   Float64 m_dfFR; // friction losses
   Float64 m_Fcgp;
   Float64 m_dfES;

   Float64 m_Ep;
   Float64 m_Fpu;
   Float64 m_Fpj;
   Float64 m_Fpy;


   mutable Float64 m_DeltaFcdp;

   mutable Float64 m_dfSR;
   mutable Float64 m_dfCR;
   mutable Float64 m_dfR2;

   mutable bool    m_IsDirty;

   // GROUP: LIFECYCLE
   // GROUP: OPERATORS
   // GROUP: OPERATIONS
   //------------------------------------------------------------------------
   void Init();

   //------------------------------------------------------------------------
   void MakeCopy( const lrfdPTRefinedLosses& rOther );

   //------------------------------------------------------------------------
   void UpdateLosses() const;

   //------------------------------------------------------------------------
   void UpdateInitialLosses() const;
   
   //------------------------------------------------------------------------
   void UpdateLongTermLosses() const;

   // GROUP: ACCESS
   // GROUP: INQUIRY
};

// INLINE METHODS
//
inline void lrfdPTRefinedLosses::SetStrandType(matPsStrand::Type type) { m_Type = type; m_IsDirty = true; }
inline matPsStrand::Type lrfdPTRefinedLosses::GetStrandType() const { return m_Type; }
inline void lrfdPTRefinedLosses::SetStrandGrade(matPsStrand::Grade gr) { m_Grade = gr; m_IsDirty = true; }
inline matPsStrand::Grade lrfdPTRefinedLosses::GetStrandGrade() const { return m_Grade; }
inline void lrfdPTRefinedLosses::SetFpj(Float64 fpj) { m_Fpj = fpj; m_IsDirty = true; }
inline Float64 lrfdPTRefinedLosses::GetFpj() const { return m_Fpj; }
inline void lrfdPTRefinedLosses::SetAg(Float64 Ag) { m_Ag = Ag; m_IsDirty = true; }
inline Float64 lrfdPTRefinedLosses::GetAg() const { return m_Ag; }
inline void lrfdPTRefinedLosses::SetIg(Float64 Ig) { m_Ig = Ig; m_IsDirty = true; }
inline Float64 lrfdPTRefinedLosses::GetIg() const { return m_Ig; }
inline void lrfdPTRefinedLosses::SetYbg(Float64 Ybg) { m_Ybg = Ybg; m_IsDirty = true; }
inline Float64 lrfdPTRefinedLosses::GetYbg() const { return m_Ybg; }
inline void lrfdPTRefinedLosses::SetIc(Float64 Ic) { m_Ic = Ic; m_IsDirty = true; }
inline Float64 lrfdPTRefinedLosses::GetIc() const { return m_Ic; }
inline void lrfdPTRefinedLosses::SetYbc(Float64 Ybc) { m_Ybc = Ybc; m_IsDirty = true; }
inline Float64 lrfdPTRefinedLosses::GetYbc() const { return m_Ybc; }
inline void lrfdPTRefinedLosses::SetEcc(Float64 e) { m_e = e; m_IsDirty = true; }
inline Float64 lrfdPTRefinedLosses::GetEcc() const { return m_e; }
inline void lrfdPTRefinedLosses::SetAreaPT(Float64 Aps) { m_Aps = Aps; m_IsDirty = true; }
inline Float64 lrfdPTRefinedLosses::GetAreaPT() const { return m_Aps; }
inline void lrfdPTRefinedLosses::SetGdrMoment(Float64 Mdlg) { m_Mdlg = Mdlg; m_IsDirty = true; }
inline Float64 lrfdPTRefinedLosses::GetGdrMoment() const { return m_Mdlg; }
inline void lrfdPTRefinedLosses::SetAddlGdrMoment(Float64 Madlg) { m_Madlg = Madlg; m_IsDirty = true; }
inline Float64 lrfdPTRefinedLosses::GetAddlGdrMoment() const { return m_Madlg; }
inline void lrfdPTRefinedLosses::SetSidlMoment(Float64 Msidl) { m_Msidl = Msidl; m_IsDirty = true; }
inline Float64 lrfdPTRefinedLosses::GetSidlMoment() const { return m_Msidl; }
inline void lrfdPTRefinedLosses::SetRelativeHumidity(Float64 rh) { m_Rh = rh; m_IsDirty = true; }
inline Float64 lrfdPTRefinedLosses::GetRelativeHumidity() const { return m_Rh; }
inline void lrfdPTRefinedLosses::SetEci(Float64 Eci) { m_Eci = Eci; m_IsDirty = true; }
inline Float64 lrfdPTRefinedLosses::GetEci() const { return m_Eci; }
inline void lrfdPTRefinedLosses::SetFR(Float64 fr) { m_dfFR = fr; m_IsDirty = true; }
inline Float64 lrfdPTRefinedLosses::GetFR() const { return m_dfFR; }
inline void lrfdPTRefinedLosses::SetFcgp(Float64 f) { m_Fcgp = f; m_IsDirty = true; }
inline Float64 lrfdPTRefinedLosses::GetFcgp() const { return m_Fcgp; }
inline void lrfdPTRefinedLosses::SetES(Float64 es) { m_dfES = es; m_IsDirty = true; }
inline Float64 lrfdPTRefinedLosses::GetES() const { return m_dfES; }

// EXTERNAL REFERENCES
//

#endif // INCLUDED_LRFD_PTREFINEDLOSSES_H_
