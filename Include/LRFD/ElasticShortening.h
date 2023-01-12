///////////////////////////////////////////////////////////////////////
// LRFD - Utility library to support equations, methods, and procedures
//        from the AASHTO LRFD Bridge Design Specification
// Copyright © 1999-2023  Washington State Department of Transportation
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

#ifndef INCLUDED_LRFD_ELASTICSHORTENING_H_
#define INCLUDED_LRFD_ELASTICSHORTENING_H_

// SYSTEM INCLUDES
//

// PROJECT INCLUDES
//
#if !defined INCLUDED_LRFD_LRFDEXP_H_
#include <Lrfd\LrfdExp.h>
#endif

#include <Lrfd\PsStrand.h>
#include <GeomModel/Primitives.h>

// LOCAL INCLUDES
//

// FORWARD DECLARATIONS
//

// MISCELLANEOUS
//

/*****************************************************************************
CLASS 
   lrfdElasticShortening

   Utility class for elastic shortening losses.


DESCRIPTION
   Utility class for elastic shortening losses.  Implements Artlce 5.9.5.2.3a
   of the LRFD Bridge Design Specification.

LOG
   rab : 04.01.1999 : Created file
*****************************************************************************/

class LRFDCLASS lrfdElasticShortening
{
public:

   // Method to compute Fcgp: Use iterative (beam theory) method, or assume that
   // stress in strands after transfer is 0.7*Fpu (TxDOT 2013 research).
   enum FcgpComputationMethod {fcgpIterative, fcgp07Fpu };

   // GROUP: LIFECYCLE

   //------------------------------------------------------------------------
   // Default constructor.
   // Strand type = LowRelaxation
   // Ep = 197000 MPa
   // Eci = 25000 MPa
   // P = 0 kN
   // A = 1mm^2
   // I = 1mm^4
   // e = 0 mm
   // Mg = 0 N-m
   lrfdElasticShortening();

   //------------------------------------------------------------------------
   // Constructor.
   lrfdElasticShortening(Float64 fpjPerm,   // jacking stress
                         Float64 fpjTemp,   // jacking stress
                         Float64 dfpR1Perm, // initial relaxation
                         Float64 dfpR1Temp, // initial relaxation
                         Float64 ApsPerm,   // Area of permanent prestressing steel 
                         Float64 ApsTemp,   // Area of temporary prestressing steel
                         bool    bGrossProperties, // true if using gross section properties
                         Float64 Ag,    // area of girder
                         Float64 Ixx,    // moment of inertia of girder
                         Float64 Iyy,
                         Float64 Ixy,
                         const WBFL::Geometry::Point2d& ePerm, // eccentricity of permanent ps strands
                         const WBFL::Geometry::Point2d& eTemp, // eccentricity of temporary ps strands
                         Float64 Mdlg,  // Dead load moment of girder only
                         Float64 K,     // coefficient for post-tension members (N-1)/(2N)
                         Float64 Eci,   // Modulus of elasticity of concrete at transfer
                         Float64 Ep,    // Modulus of elasticity of prestressing steel
                         FcgpComputationMethod method);

   //------------------------------------------------------------------------
   // Copy c'tor
   lrfdElasticShortening(const lrfdElasticShortening& rOther);

   //------------------------------------------------------------------------
   // Destructor
   ~lrfdElasticShortening();

   // GROUP: OPERATORS

   //------------------------------------------------------------------------
   // Assignment operator
   lrfdElasticShortening& operator=(const lrfdElasticShortening& rOther);

   // GROUP: OPERATIONS

   //------------------------------------------------------------------------
   Float64 TemporaryStrand_ElasticShorteningLosses() const;
   Float64 PermanentStrand_ElasticShorteningLosses() const;

   //------------------------------------------------------------------------
   Float64 P() const;

   //------------------------------------------------------------------------
   Float64 TemporaryStrand_Fcgp() const;
   Float64 PermanentStrand_Fcgp() const;

   // GROUP: ACCESS

   //------------------------------------------------------------------------
   void    TemporaryStrand_Fpj(Float64 fpj);
   Float64 TemporaryStrand_Fpj() const;
   void    PermanentStrand_Fpj(Float64 fpj);
   Float64 PermanentStrand_Fpj() const;

   void    TemporaryStrand_InitialRelaxationLoss(Float64 dfpR1);
   Float64 TemporaryStrand_InitialRelaxationLoss() const;
   void    PermanentStrand_InitialRelaxationLoss(Float64 dfpR1);
   Float64 PermanentStrand_InitialRelaxationLoss() const;

   void    TemporaryStrand_Aps(Float64 Aps);
   Float64 TemporaryStrand_Aps() const;
   void    PermanentStrand_Aps(Float64 Aps);
   Float64 PermanentStrand_Aps() const;

   void    TemporaryStrand_Eccentricty(const WBFL::Geometry::Point2d& e);
   const WBFL::Geometry::Point2d& TemporaryStrand_Eccentricty() const;
   void    PermanentStrand_Eccentricty(const WBFL::Geometry::Point2d& e);
   const WBFL::Geometry::Point2d& PermanentStrand_Eccentricty() const;

   void GrossProperties(bool bGrossProperties);
   bool GrossProperties() const;

   void SetProperties(Float64 A, Float64 Ixx, Float64 Iyy, Float64 Ixy);
   void GetProperties(Float64* pA, Float64* pIxx, Float64* pIyy, Float64* pIxy) const;

   void    GdrMoment(Float64 Mdlg);
   Float64 GdrMoment() const;

   void    Eci(Float64 Eci);
   Float64 Eci() const;

   void    Ep(Float64 Ep);
   Float64 Ep() const;

   void    Coefficient(Float64 K);
   Float64 Coefficient() const;

   void    lrfdElasticShortening::SetFcgpComputationMethod(FcgpComputationMethod m);
   FcgpComputationMethod lrfdElasticShortening::GetFcgpComputationMethod() const;

   // GROUP: INQUIRY

protected:
   // GROUP: DATA MEMBERS
   mutable bool m_bUpdate;
   void Update() const;

   // GROUP: LIFECYCLE
   // GROUP: OPERATORS
   // GROUP: OPERATIONS

   //------------------------------------------------------------------------
   void MakeAssignment( const lrfdElasticShortening& rOther );

   // GROUP: ACCESS
   // GROUP: INQUIRY

private:
   // GROUP: DATA MEMBERS
   Float64 m_ApsPerm;
   Float64 m_ApsTemp;
   WBFL::Geometry::Point2d m_ePerm;
   WBFL::Geometry::Point2d m_eTemp;

   Float64 m_FpjPerm;   // Jacking stress
   Float64 m_FpjTemp;   // Jacking stress

   Float64 m_dFpR1Perm; // Initial relaxation losses
   Float64 m_dFpR1Temp; // Initial relaxation losses

   bool m_bGrossProperties;
   Float64 m_Ag;    // Area of the girder
   Float64 m_Ixx;    // Moment of inertia of the girder
   Float64 m_Iyy;
   Float64 m_Ixy;
   Float64 m_Mdlg;  // Dead load moment of girder
   Float64 m_Eci;
   Float64 m_Ep;
   Float64 m_K; // Coefficient used for Post-tensioned members (N-1)/(2N)
   FcgpComputationMethod m_FcgpMethod;

   mutable Float64 m_P;     // prestress force
   mutable Float64 m_dfESPerm; // Elastic shortening losses
   mutable Float64 m_dfESTemp; // Elastic shortening losses
   mutable Float64 m_FcgpPerm; // Stress at cg;
   mutable Float64 m_FcgpTemp; // Stress at cg;

   // GROUP: LIFECYCLE
   // GROUP: OPERATORS
   // GROUP: OPERATIONS

   //------------------------------------------------------------------------
   void MakeCopy( const lrfdElasticShortening& rOther );

   // GROUP: ACCESS
   // GROUP: INQUIRY
};

// INLINE METHODS
//
inline void    lrfdElasticShortening::TemporaryStrand_Fpj(Float64 Fpj) { m_FpjTemp = Fpj; m_bUpdate = true; }
inline Float64 lrfdElasticShortening::TemporaryStrand_Fpj() const      { return m_FpjTemp; }
inline void    lrfdElasticShortening::PermanentStrand_Fpj(Float64 Fpj) { m_FpjPerm = Fpj; m_bUpdate = true; }
inline Float64 lrfdElasticShortening::PermanentStrand_Fpj() const      { return m_FpjPerm; }

inline void    lrfdElasticShortening::TemporaryStrand_InitialRelaxationLoss(Float64 dFpR1) { m_dFpR1Temp = dFpR1; m_bUpdate = true; }
inline Float64 lrfdElasticShortening::TemporaryStrand_InitialRelaxationLoss() const        { return m_dFpR1Temp; }
inline void    lrfdElasticShortening::PermanentStrand_InitialRelaxationLoss(Float64 dFpR1) { m_dFpR1Perm = dFpR1; m_bUpdate = true; }
inline Float64 lrfdElasticShortening::PermanentStrand_InitialRelaxationLoss() const        { return m_dFpR1Perm; }

inline void    lrfdElasticShortening::TemporaryStrand_Aps(Float64 Aps) { m_ApsTemp = Aps; m_bUpdate = true; }
inline Float64 lrfdElasticShortening::TemporaryStrand_Aps() const      { return m_ApsTemp; }
inline void    lrfdElasticShortening::PermanentStrand_Aps(Float64 Aps) { m_ApsPerm = Aps; m_bUpdate = true; }
inline Float64 lrfdElasticShortening::PermanentStrand_Aps() const      { return m_ApsPerm; }

inline void lrfdElasticShortening::GrossProperties(bool bGrossProperties) { m_bGrossProperties = bGrossProperties; m_bUpdate = true; }
inline bool lrfdElasticShortening::GrossProperties() const { return m_bGrossProperties; }

inline void    lrfdElasticShortening::TemporaryStrand_Eccentricty(const WBFL::Geometry::Point2d& e) { m_eTemp = e; m_bUpdate = true; }
inline const WBFL::Geometry::Point2d& lrfdElasticShortening::TemporaryStrand_Eccentricty() const    { return m_eTemp; }
inline void    lrfdElasticShortening::PermanentStrand_Eccentricty(const WBFL::Geometry::Point2d& e) { m_ePerm = e; m_bUpdate = true; }
inline const WBFL::Geometry::Point2d& lrfdElasticShortening::PermanentStrand_Eccentricty() const    { return m_ePerm; }

inline void    lrfdElasticShortening::GdrMoment(Float64 Mdlg) { m_Mdlg = Mdlg; m_bUpdate = true; }
inline Float64 lrfdElasticShortening::GdrMoment() const       { return m_Mdlg; }

inline void    lrfdElasticShortening::Eci(Float64 Eci) { m_Eci = Eci; m_bUpdate = true; }
inline Float64 lrfdElasticShortening::Eci() const      { return m_Eci; }

inline void    lrfdElasticShortening::Ep(Float64 Ep) { m_Ep = Ep; m_bUpdate = true; }
inline Float64 lrfdElasticShortening::Ep() const     { return m_Ep; }

inline void    lrfdElasticShortening::Coefficient(Float64 K) { m_K = K; m_bUpdate = true; }
inline Float64 lrfdElasticShortening::Coefficient() const    { return m_K; }

inline void    lrfdElasticShortening::SetFcgpComputationMethod(FcgpComputationMethod m) { m_FcgpMethod = m; m_bUpdate = true; }
inline lrfdElasticShortening::FcgpComputationMethod lrfdElasticShortening::GetFcgpComputationMethod() const    { return m_FcgpMethod; }

// EXTERNAL REFERENCES
//

#endif // INCLUDED_LRFD_ELASTICSHORTENING_H_
