///////////////////////////////////////////////////////////////////////
// RC - Reinforced Concrete Section Capacity Analysis Library
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

#include <ReinforcedConcrete\ReinfConcLib.h>


#include <ReinforcedConcrete\CapacityProblem.h>

#include <ReinforcedConcrete\ConcreteElement.h>
#include <ReinforcedConcrete\ReinforcementElement.h>
#include <Material\Concrete.h>
#include <Material\Metal.h>
#include <Material\PsStrand.h>
#include <Material\PsStrandCurve.h>
#include <Material\YieldStressStrainCurve.h>
#include <Material\LinearStressStrainCurve.h>
#include <GeomModel\Properties.h>
#include <Units\SysUnits.h>

#include <Lrfd\ConcreteUtil.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/****************************************************************************
CLASS
   rcaXRcCapProbError
****************************************************************************/

////////////////////////// PUBLIC     ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
rcaXRcCapProbError::rcaXRcCapProbError(Reason reason, LPCTSTR file, Int16 line) :
sysXBase(file, line),
m_Reason(reason)
{
   Init();
}

rcaXRcCapProbError::rcaXRcCapProbError(const rcaXRcCapProbError& rOther) :
sysXBase(rOther)
{
   Init();
   MakeCopy(rOther);
}

rcaXRcCapProbError::~rcaXRcCapProbError()
{
   Clean();
}

//======================== OPERATORS  =======================================
rcaXRcCapProbError& rcaXRcCapProbError::operator= (const rcaXRcCapProbError& rOther)
{
   if( this != &rOther )
   {
      MakeAssignment(rOther);
   }

   return *this;
}

//======================== OPERATIONS =======================================

void rcaXRcCapProbError::Throw() const 
{ 
   throw static_cast<rcaXRcCapProbError>(*this); 
}

// rcaXRcCapProbError::Reason
Int32 rcaXRcCapProbError::GetReason() const
{
   return m_Reason;
}

rcaXRcCapProbError::Reason rcaXRcCapProbError::GetReasonCode() const
{
   return m_Reason;
}

void rcaXRcCapProbError::GetErrorMessage(std::_tstring* pMsg,Int32 reserved) const
{
   switch (m_Reason)
   {
   case MaterialNotFound:
      *pMsg = _T("Material not found");
      break;
   case ElementNotFound:
      *pMsg = _T("Element not found");
      break;
   case InvalidProblemRep:
      *pMsg = _T("The problem representation is invalid");
      break;
   default:
      CHECK(0);
      *pMsg = _T("Unknown Error Message - Bad Reason Type");
   }
}


//======================== ACCESS     =======================================
//======================== INQUIRY    =======================================
//======================== DEBUG      =======================================
#if defined _DEBUG
bool rcaXRcCapProbError::AssertValid() const
{
   return true;
}

void rcaXRcCapProbError::Dump(dbgDumpContext& os) const
{
   os<<"Dump for rcaXRcCapProbError"<<endl;
}
#endif // _DEBUG

////////////////////////// PROTECTED  ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
//======================== OPERATORS  =======================================
//======================== OPERATIONS =======================================
void rcaXRcCapProbError::MakeCopy(const rcaXRcCapProbError& rOther)
{
   m_Reason = rOther.m_Reason;
}

void rcaXRcCapProbError::MakeAssignment(const rcaXRcCapProbError& rOther)
{
   Clean();
   Init();

   sysXBase::MakeAssignment( rOther );
   MakeCopy( rOther );
}

//======================== ACCESS     =======================================
//======================== INQUIRY    =======================================

////////////////////////// PRIVATE    ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
//======================== OPERATORS  =======================================
//======================== OPERATIONS =======================================
void rcaXRcCapProbError::Init()
{
   // Add initialization code here...
}

void rcaXRcCapProbError::Clean()
{
   // Add cleanup code here...
}

//======================== ACCESS     =======================================
//======================== INQUERY    =======================================



/****************************************************************************
CLASS
   rcaCapacityProblem
****************************************************************************/

const Float64 rcaCapacityProblem::PositionTolerance=1.0e-5;


////////////////////////// PUBLIC     ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
rcaCapacityProblem::rcaCapacityProblem():
m_MaxCompressiveStrain(-0.003),
m_CbOffset(0.0),
m_BaseConcrete(0)
{
   Init();
}

rcaCapacityProblem::rcaCapacityProblem(const rcaCapacityProblem& rOther)
{
   Init();
   MakeCopy(rOther);
}

rcaCapacityProblem::~rcaCapacityProblem()
{
   Clean();
}

//======================== OPERATORS  =======================================
rcaCapacityProblem& rcaCapacityProblem::operator= (const rcaCapacityProblem& rOther)
{
   if( this != &rOther )
   {
      MakeAssignment(rOther);
   }

   return *this;
}

//======================== OPERATIONS =======================================

CollectionIndexType rcaCapacityProblem::AddConcrete(const matConcrete& concrete)
{
   // clone and own concrete material
   ConcretePtr pconc(concrete.CreateClone());
   m_ConcreteContainer.push_back(pconc);
   return m_ConcreteContainer.size()-1;
}

const matConcrete& rcaCapacityProblem::GetConcrete(CollectionIndexType key) const
{
   CHECK(0 <= key && key < m_ConcreteContainer.size());
   return *(m_ConcreteContainer[key]);
}

CollectionIndexType rcaCapacityProblem::GetNumConcretes() const
{
   return m_ConcreteContainer.size();
}

void rcaCapacityProblem::SetBaseConcreteMaterial(CollectionIndexType concreteIdx)
{
   CHECK(0 <= concreteIdx && concreteIdx < m_ConcreteContainer.size());
   m_BaseConcrete = concreteIdx;
}

CollectionIndexType rcaCapacityProblem::GetBaseConcreteMaterial() const
{
   return m_BaseConcrete;
}

CollectionIndexType rcaCapacityProblem::AddMildSteel(const matMetal& steel)
{
   std::shared_ptr<matYieldStressStrainCurve> pcurv(DoCreateMildSteelMaterialModel(steel));
   CollectionIndexType key = GetNextAvailableKey();
   m_MsCurveContainer.insert(MatCurveEntry(key,pcurv));

   return key;
}

StrandIndexType rcaCapacityProblem::AddStrand(const matPsStrand& strand)
{
   std::shared_ptr<matYieldStressStrainCurve> pcurv(DoCreateStrandMaterialModel(strand));
   StrandIndexType key = GetNextAvailableKey();
   m_PsCurveContainer.insert(MatCurveEntry(key,pcurv));

   return key;
}


bool rcaCapacityProblem::RemoveMaterial(StrandIndexType key)
{
   // go through all of the material containers 
   // mild steel
   MatCurveIterator miter = m_MsCurveContainer.find(key);
   if ( miter != m_MsCurveContainer.end() )
   {
      m_MsCurveContainer.erase(miter);
      return true;
   }

   // strands
   miter = m_PsCurveContainer.find(key);
   if ( miter != m_PsCurveContainer.end() )
   {
      m_PsCurveContainer.erase(miter);
      return true;
   }

   // not found for key
   return false;
}

CollectionIndexType rcaCapacityProblem::MildSteelMaterialCount() const
{
   return m_MsCurveContainer.size();
}

CollectionIndexType rcaCapacityProblem::StrandMaterialCount() const
{
   return m_PsCurveContainer.size();
}

CollectionIndexType rcaCapacityProblem::MaterialCount() const
{
   return MildSteelMaterialCount() + StrandMaterialCount();
}

CollectionIndexType rcaCapacityProblem::AddConcreteElement(const gmIShape& shape, CollectionIndexType concreteKey, Float64 nFactor)
{
   OnGeometryChange();

   ConcElementPtr pelm(new rcaConcreteElement(shape, concreteKey, nFactor, *this));
   CollectionIndexType key = GetNextAvailableKey();
   ConcElementEntry entry(key,pelm);
   std::pair<ConcElementContainer::iterator,bool> retval = m_ConcElementContainer.insert( entry );
   return key;
}

CollectionIndexType rcaCapacityProblem::AddConcreteElement(const gmIShape& shape, CollectionIndexType concreteKey)
{
   OnGeometryChange();

   ConcElementPtr pelm(new rcaConcreteElement(shape, concreteKey, *this));
   CollectionIndexType key = GetNextAvailableKey();
   ConcElementEntry entry(key,pelm);
   std::pair<ConcElementContainer::iterator,bool> retval = m_ConcElementContainer.insert( entry );
   return key;
}

CollectionIndexType rcaCapacityProblem::AddReinforcementElement(const gmIShape& shape, CollectionIndexType matId, 
                                                    Float64 initStrain)
{
   OnGeometryChange();

   // look in strand materials
   MatCurveIterator citer = m_PsCurveContainer.find(matId);
   if ( citer != m_PsCurveContainer.end() )
   {
      const matYieldStressStrainCurve* pCurve = (*citer).second.get();

      // found the material - add the element
      ReinfElementPtr pelm(new rcaReinforcementElement(shape, *pCurve, *this, initStrain));
      CollectionIndexType key = GetNextAvailableKey();
      m_ReinfElementContainer.insert(ReinfElementEntry(key,pelm));
      return key;
   }

   // look in mild steel materials
   citer = m_MsCurveContainer.find(matId);
   if ( citer != m_MsCurveContainer.end() )
   {
      const matYieldStressStrainCurve* pCurve = (*citer).second.get();

      // found the material - add the element
      ReinfElementPtr pelm(new rcaReinforcementElement(shape, *pCurve, *this, initStrain));
      CollectionIndexType key = GetNextAvailableKey();
      m_ReinfElementContainer.insert(ReinfElementEntry(key,pelm));
      return key;
   }

   // could not find material
   rcaXRcCapProbError ex(rcaXRcCapProbError::MaterialNotFound,_T(__FILE__),__LINE__);
   ex.Throw();
   return 0;  // should never get here, but compiler needs it
}

bool rcaCapacityProblem::DestroyElement(CollectionIndexType id)
{
   OnGeometryChange();

   // check in reinforcement
   ReinfElementIterator riter = m_ReinfElementContainer.find(id);
   if ( riter != m_ReinfElementContainer.end() )
   {
      m_ReinfElementContainer.erase(riter);
      return true;
   }

   // check in concrete
   ConcElementIterator citer = m_ConcElementContainer.find(id);
   if ( citer != m_ConcElementContainer.end() )
   {
      m_ConcElementContainer.erase(citer);
      return true;
   }
   return false;
}

CollectionIndexType rcaCapacityProblem::ConcreteElementCount() const
{
   return m_ConcElementContainer.size();
}

CollectionIndexType rcaCapacityProblem::ReinforcementElementCount() const
{
   return m_ReinfElementContainer.size();
}

CollectionIndexType rcaCapacityProblem::ElementCount() const
{
   return ConcreteElementCount() + ReinforcementElementCount();
}

void rcaCapacityProblem::SetNeutralAxisLocation(const gpLine2d& line)
{
   m_NeutralAxisLocation = line;
   OnNeutralAxisChanged();
}

void rcaCapacityProblem::GetNeutralAxisLocation(gpLine2d* line) const
{
   *line = m_NeutralAxisLocation;
}

Float64 rcaCapacityProblem::GetCompressionBlockBoundary() const
{
   return m_CbOffset;
}

void rcaCapacityProblem::SetMaxCompressiveStrain(Float64 strain)
{
   CHECK(strain<=0);
   m_MaxCompressiveStrain = strain;
}

Float64 rcaCapacityProblem::GetMaxCompressiveStrain() const
{
   return m_MaxCompressiveStrain;
}

void rcaCapacityProblem::GetCompressionBlockBoundary(gpLine2d* line) const
{
   *line = m_NeutralAxisLocation.Parallel(m_CbOffset, gpLine2d::Left);
}

Float64 rcaCapacityProblem::GetStrain( const gpPoint2d& p ) const
{
   return m_BeamStrain.GetAxialStrain(p);
}

Float64 rcaCapacityProblem::GetStrain( Float64 x, Float64 y) const
{
   return m_BeamStrain.GetAxialStrain(x,y);
}

Float64 rcaCapacityProblem::GetStrain( CollectionIndexType id ) const
{
   gmProperties props;
   bool found = false;
   // don't know if element is in reinforcement or concrete
   // check reinforcement first
   ConstReinfElementIterator riter = m_ReinfElementContainer.find(id);
   if ( riter != m_ReinfElementContainer.end() )
   {
      const ReinfElementPtr& rept = (*riter).second;
      rept->GetShape().GetProperties(&props);
      found = true;
   }

   if (!found)
   {
      // check in concrete
      ConstConcElementIterator citer = m_ConcElementContainer.find(id);
      if ( citer != m_ConcElementContainer.end() )
      {
         const ConcElementPtr& cept = (*citer).second;
         cept->GetShape().GetProperties(&props);
         found = true;
      }
   }

   if (found)
      return GetStrain(props.Centroid());


   // could not find material
   rcaXRcCapProbError ex(rcaXRcCapProbError::ElementNotFound,_T(__FILE__),__LINE__);
   ex.Throw();
   return 0;  // should never get here, but compiler needs it
}

void rcaCapacityProblem::GetSectionForcesEx(Float64* pFz,
                                            Float64* pMx,
                                            Float64* pMy,
                                            Float64* pcompRes, gpPoint2d* pcompLoc,
                                            Float64* ptensRes, gpPoint2d* ptensLoc) const
{
   gpPoint2d pc = GetPlasticCentroid();
   Float64 gfz, gmx, gmy;
   GetGlobalSectionForcesEx(&gfz, &gmx, &gmy, pcompRes, pcompLoc, ptensRes, ptensLoc);

   *pFz = gfz;
   *pMx = gmx + gfz*(pc.Y());
   *pMy = gmy - gfz*(pc.X());
}

void rcaCapacityProblem::GetSectionForcesEx(rcaSectionForceDetails* pDetails) const
{
   pDetails->ReinforcementForceDetails.clear();

   GetSectionForcesEx( &pDetails->Fz,
                       &pDetails->Mx,
                       &pDetails->My,
                       &pDetails->CompForce,
                       &pDetails->LocCompForce,
                       &pDetails->TensForce,
                       &pDetails->LocTensForce);

   pDetails->Beta1 = GetBeta1();
   pDetails->CompArea = GetCompressionArea();
   pDetails->EffCompArea = GetEffectiveCompressionArea();
   pDetails->NeutralAxis = m_NeutralAxisLocation;
   pDetails->PlasticCentroid = GetPlasticCentroid();

   GetCompressiveCapacity(&pDetails->Pc,&pDetails->Mxc,&pDetails->Myc);
   GetTensileCapacity(&pDetails->Pt,&pDetails->Mxt,&pDetails->Myt);

   // iterate over reinforcement elements
   ConstReinfElementIterator riter;
   for (riter =  m_ReinfElementContainer.begin(); 
        riter != m_ReinfElementContainer.end();
        riter++)
   {
      const ReinfElementPtr& rept = (*riter).second;
      rcaReinforcementForceDetails rfd;

      const gmIShape& shape = rept->GetShape();
      const gmIShapeEx* pex;
      // cast to gmIShapeEx for efficiency
      pex = dynamic_cast<const gmIShapeEx*>(&shape);
      if (pex!=0)
      {
         pex->GetArea(&(rfd.Ab), &(rfd.LocBar));
      }
      else
      {
      gmProperties props;
      shape.GetProperties( &props );
      rfd.Ab = props.Area();
      rfd.LocBar = props.Centroid();
      }

      rfd.InitialStrain = rept->GetInitialStrain();
      rfd.ConcreteStrain =  GetStrain( rfd.LocBar );
      rfd.BarStrain = rfd.InitialStrain + rfd.ConcreteStrain;

      const matYieldStressStrainCurve& sscurve = rept->GetStressStrainCurve();
      sscurve.GetStress(rfd.BarStrain,&rfd.BarStress);

      rfd.BarForce = rfd.BarStress * rfd.Ab;

      pDetails->ReinforcementForceDetails.push_back(rfd);
   }
}

void rcaCapacityProblem::GetSectionForces(Float64* pFz,
                                          Float64* pMx,
                                          Float64* pMy) const
{
   Float64 compRes, tensRes;
   gpPoint2d compLoc, tensLoc;
   GetSectionForcesEx(pFz, pMx, pMy, &compRes, &compLoc, &tensRes, &tensLoc);
}

void rcaCapacityProblem::GetTensileCapacity(Float64* pPt,Float64* pMxt,Float64* pMyt) const
{
   // Pure axial tension is defined as all reinforcement has yielded.  If the
   // section is non-symmetrical there will be corresponding moments.
   // See pg 402 of MacGregor
   // Pt = Sum(fyi*Asi)
   // Mxt = Sum(fyi*Asi*(cg.Y()-pc.Y()))
   // Myt = Sum(fyi*Asi*(cg.X()-pc.X()))
   // where fyi = yield stress of rebar i,
   //       Asi = area of bar i,
   //       pc  = plastic centroid
   //       cg  = center of gravity of rebar i

   gpPoint2d pc = GetPlasticCentroid(); // This is the plastic centroid for
                                        // compressive forces. The plastic
                                        // centroid for pure tension will be different
                                        // for unsymetric rebar layouts.  In this case
                                        // corresponding moments will occur.

   Float64 Pt  = 0;
   Float64 Mxt = 0;
   Float64 Myt = 0;
   for ( ConstReinfElementIterator iter = m_ReinfElementContainer.begin();
         iter != m_ReinfElementContainer.end();
         iter++ )
   {
      const ReinfElementPtr& rept = (*iter).second;
      const matYieldStressStrainCurve& mc = rept->GetStressStrainCurve();

      Float64 fy = mc.GetTensYieldStress();

      const gmIShape& shape = rept->GetShape();
      gmProperties prop;
      shape.GetProperties( &prop );
      Float64 Aps = prop.Area();
      gpPoint2d cg = prop.Centroid();

      Float64 p = fy*Aps;
      Float64 mxt = p*(cg.Y() - pc.Y());
      Float64 myt = p*(cg.X() - pc.X());

      Pt  += p;
      Mxt += mxt;
      Myt += myt;
   }


   *pPt  = Pt;
   *pMxt = Mxt;
   *pMyt = Myt;
}

void rcaCapacityProblem::GetCompressiveCapacity(Float64* pPc,Float64* pMxc,Float64* pMyc) const
{
   // save off strain function and compression block offset. Them set them for
   // uniform strain conditions.
   Float64 save_cb = m_CbOffset;
   etBiaxialBeamStrain save_bs = m_BeamStrain;

   Float64 Pc, Mxc, Myc;
   try
   {
      gpPoint2d pc = GetPlasticCentroid();

      m_CbOffset = -Float64_Max/4;  // all concrete elements in compression
      m_BeamStrain.SetStrainPlane(m_MaxCompressiveStrain); // constant compressive strain in steel

      Float64 gfz, gmx, gmy;
      GetGlobalSectionForces(&gfz, &gmx, &gmy);

      Pc = gfz;
      Mxc = gmx + gfz*(0 - pc.Y()); // Subtract from zero because this forces are relative to the global origin at (0,0)
      Myc = gmy - gfz*(0 - pc.X()); 
   }
   catch(...)
   {
      // restore compression block and beam strain
      m_CbOffset   = save_cb;
      m_BeamStrain = save_bs;

      throw;
   }

   // restore compression block and beam strain
   m_CbOffset   = save_cb;
   m_BeamStrain = save_bs;

   *pPc  = Pc;
   *pMxc = Mxc;
   *pMyc = Myc;
}

gpPoint2d rcaCapacityProblem::GetPlasticCentroid() const
{
   // only recalculate if geometry change has occured
   if (m_PcHasChanged)
   {
      if ( ConcreteElementCount() == 0 || GetConcreteArea() <= 0 )
      {
         m_PlasticCentroid = GetBoundingBox().Center();
         return m_PlasticCentroid;
      }

      // save off strain function and compression block offset. Them set them for
      // uniform strain conditions.
      Float64 save_cb = m_CbOffset;
      etBiaxialBeamStrain save_bs = m_BeamStrain;

      gpRect2d box = this->GetBoundingBox(); 
      m_CbOffset = box.Bottom() - 10.;  // all concrete elements in compression
      m_BeamStrain.SetStrainPlane(m_MaxCompressiveStrain); // constant compressive strain in steel

      Float64 gfz, gmx, gmy;
      GetGlobalSectionForces(&gfz, &gmx, &gmy);

      // restore compression block and beam strain
      m_CbOffset   = save_cb;
      m_BeamStrain = save_bs;

      // plastic centroid is where moments are zero.
      m_PlasticCentroid.X() = -gmy/gfz;
      m_PlasticCentroid.Y() =  gmx/gfz;

      // cache pc
      m_PcHasChanged = false;
   }

   return m_PlasticCentroid;
}


Float64 rcaCapacityProblem::GetCompressionArea() const
{
   return m_CompArea;
}

Float64 rcaCapacityProblem::GetEffectiveCompressionArea() const
{
   return m_EffCompArea;
}

gpRect2d rcaCapacityProblem::GetBoundingBox() const
{
   // cycle through all concrete, rebar and strands to determine the bounding box
   gpRect2d sum_box;
   bool first=false;

   // iterate over concrete elements
   for (ConstConcElementIterator citer=m_ConcElementContainer.begin(); 
        citer!=m_ConcElementContainer.end(); citer++)
   {
      const ConcElementPtr& cept = (*citer).second;

      if (first)
      {
         sum_box = cept->GetShape().GetBoundingBox();
         first=false;
      }
      else
         sum_box.Union(cept->GetShape().GetBoundingBox());
   }

   // iterate over reinforcement elements
   for (ConstReinfElementIterator riter=m_ReinfElementContainer.begin(); 
        riter!=m_ReinfElementContainer.end(); riter++)
   {
      const ReinfElementPtr& rept = (*riter).second;
      if (first)
      {
         sum_box = rept->GetShape().GetBoundingBox();
         first=false;
      }
      else
         sum_box.Union(rept->GetShape().GetBoundingBox());
   }
   return sum_box;
}

void rcaCapacityProblem::Draw(HDC hDC, const grlibPointMapper& mapper) const
{
   // iterate over concrete elements
   for (ConstConcElementIterator citer=m_ConcElementContainer.begin(); 
        citer!=m_ConcElementContainer.end(); citer++)
   {
      const ConcElementPtr& cept = (*citer).second;
      cept->GetShape().Draw(hDC,mapper);
   }

   // iterate over reinforcement elements
   for (ConstReinfElementIterator riter=m_ReinfElementContainer.begin(); 
        riter!=m_ReinfElementContainer.end(); riter++)
   {
      const ReinfElementPtr& rept = (*riter).second;
      rept->GetShape().Draw(hDC,mapper);
   }
}

//======================== ACCESS     =======================================
//======================== INQUIRY    =======================================
//======================== DEBUG      =======================================
#if defined _DEBUG
bool rcaCapacityProblem::AssertValid() const
{
   if ( m_ConcreteContainer.size() == 0 )
      return false;

   if ( m_MsCurveContainer.size() == 0 && m_PsCurveContainer.size() == 0 )
      return false;

   ConstMatCurveIterator ms_iter;
   for ( ms_iter = m_MsCurveContainer.begin(); ms_iter != m_MsCurveContainer.end(); ms_iter++)
   {
      if ( !(*ms_iter).second->AssertValid() )
         return false;
   }

   ConstMatCurveIterator ps_iter;
   for ( ps_iter = m_PsCurveContainer.begin(); ps_iter != m_PsCurveContainer.end(); ps_iter++)
   {
      if ( !(*ps_iter).second->AssertValid() )
         return false;
   }

   if ( m_ConcElementContainer.size() == 0 )
      return false;

   ConstConcElementIterator conc_iter;
   for ( conc_iter = m_ConcElementContainer.begin(); conc_iter != m_ConcElementContainer.end(); conc_iter++ )
   {
      if ( !(*conc_iter).second->AssertValid() )
         return false;
   }

   if ( m_ReinfElementContainer.size() == 0 )
      return false;

   ConstReinfElementIterator reinf_iter;
   for ( reinf_iter = m_ReinfElementContainer.begin(); reinf_iter != m_ReinfElementContainer.end(); reinf_iter++ )
   {
      if ( !(*reinf_iter).second->AssertValid() )
         return false;
   }

   return true;
}

void rcaCapacityProblem::Dump(dbgDumpContext& os) const
{
   os << "Dump for rcaCapacityProblem" << endl;
   os << "===========================" << endl;
   os << endl;
   os << endl;

   os << "Concrete" << endl;
   Int32 i = 0;
   for (ConstConcreteIterator citer=m_ConcreteContainer.begin(); 
        citer!=m_ConcreteContainer.end(); citer++)
   {
      os << "ID = "<< i << endl;
      (*citer)->Dump( os );
      i++;
   }
   os << endl;
   os << endl;

   if ( m_MsCurveContainer.size() != 0 )
   {
      os << "Mild Steel Curves" << endl;
      ConstMatCurveIterator ms_iter;
      for ( ms_iter = m_MsCurveContainer.begin(); ms_iter != m_MsCurveContainer.end(); ms_iter++)
      {
         os << "ID = " << (*ms_iter).first << endl;
         (*ms_iter).second->Dump( os );
      }
   }
   os << endl;
   os << endl;


   if ( m_PsCurveContainer.size() != 0 )
   {
      ConstMatCurveIterator ps_iter;
      for ( ps_iter = m_PsCurveContainer.begin(); ps_iter != m_PsCurveContainer.end(); ps_iter++)
      {
         os << "ID = " << (*ps_iter).first << endl;
         (*ps_iter).second->Dump( os );
      }
   }
   os << endl;
   os << endl;

   if ( m_ConcElementContainer.size() != 0 )
   {
      os << "Concrete Elements" << endl;
      os << "-----------------" << endl;
      os << "Count = " << m_ConcElementContainer.size() << endl;
      ConstConcElementIterator conc_iter;
      for ( conc_iter = m_ConcElementContainer.begin(); conc_iter != m_ConcElementContainer.end(); conc_iter++ )
      {
         os << "ID = " << (*conc_iter).first << endl;
         (*conc_iter).second->Dump( os );
      }
   }

   if ( m_ReinfElementContainer.size() != 0 )
   {
      os << "Reinforcement Elements" << endl;
      os << "----------------------" << endl;
      os << "Count = " << m_ReinfElementContainer.size() << endl;
      ConstReinfElementIterator reinf_iter;
      for ( reinf_iter = m_ReinfElementContainer.begin(); reinf_iter != m_ReinfElementContainer.end(); reinf_iter++ )
      {
         os << "ID = " << (*reinf_iter).first << endl;
         (*reinf_iter).second->Dump( os );
      }

      os << endl << "Rebar Dump" << endl;

      os << "Initial Strain, cgX, cgY" << endl;
      for ( reinf_iter = m_ReinfElementContainer.begin(); reinf_iter != m_ReinfElementContainer.end(); reinf_iter++ )
      {
         rcaReinforcementElement* pElement = (*reinf_iter).second.get();

         gmProperties props;
         pElement->GetShape().GetProperties( &props );

         os << pElement->GetInitialStrain() << "," 
            << props.Centroid().X() << "," << props.Centroid().Y() << endl;
      }
   }
}
#endif // _DEBUG

#if defined _UNITTEST
bool rcaCapacityProblem::TestMe(dbgLog& rlog)
{
   TESTME_PROLOGUE("rcaCapacityProblem");
   TEST_NOT_IMPLEMENTED("Unit Tests Not Implemented for rcaCapacityProblem");
   TESTME_EPILOG("rcaCapacityProblem");
}
#endif

////////////////////////// PROTECTED  ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
//======================== OPERATORS  =======================================
//======================== OPERATIONS =======================================


void rcaCapacityProblem::OnNeutralAxisChanged()
{
   // get farthest distance to extreme compression fiber
   m_FurthestDistance = DoCalculateFurthestDistance();

   // update strain function
   m_BeamStrain.SetStrainPlane(m_NeutralAxisLocation, m_FurthestDistance, m_MaxCompressiveStrain);

   // determine compression block boundary
   m_CbOffset = DoCalculateCompressionBlockBoundary();

   // determine area on compression side of the neutral axis
   m_CompArea = GetClippedConcreteArea(m_NeutralAxisLocation,gpLine2d::Right);

   // determine effective area of compression block
   gpLine2d cbLine = m_NeutralAxisLocation.Parallel(m_CbOffset,gpLine2d::Left);
   m_EffCompArea = GetClippedConcreteArea(cbLine,gpLine2d::Right);
}

Float64 rcaCapacityProblem::GetFurthestDistance() const 
{
   return m_FurthestDistance;
}


Float64 rcaCapacityProblem::DoCalculateFurthestDistance()
{
   // cycle through all concrete elements and determine furthest distance
   Float64 max_dist = -DBL_MAX;

   ConcElementIterator iter;
   for ( iter  = m_ConcElementContainer.begin(); 
         iter != m_ConcElementContainer.end(); 
         iter++ )
   {
      const rcaConcreteElement* ptr = (*iter).second.get();
      const gmIShape& shape = ptr->GetShape();
      Float64 current_dist = shape.GetFurthestDistance( m_NeutralAxisLocation, gpLine2d::Left );

      max_dist = max( max_dist, current_dist );
   }

   return max_dist;
}


CollectionIndexType rcaCapacityProblem::GetNextAvailableKey()
{
   return ++m_LastKey;
}

matYieldStressStrainCurve* rcaCapacityProblem::DoCreateMildSteelMaterialModel(const matMetal& steel)
{
   return new matLinearStressStrainCurve(steel);
}

matYieldStressStrainCurve* rcaCapacityProblem::DoCreateStrandMaterialModel(const matPsStrand& strand)
{
   return new matPsStrandCurve(strand);
}

void rcaCapacityProblem::OnGeometryChange()
{
   m_PcHasChanged=true;
   m_CsHasChanged=true;
}


Float64 rcaCapacityProblem::GetClippedConcreteArea(const gpLine2d& clipLine, gpLine2d::Side side) const
{
   Float64 area = 0;
   for (ConstConcElementIterator citer = m_ConcElementContainer.begin(); 
        citer!=m_ConcElementContainer.end(); citer++)
   {
      const rcaConcreteElement* ptr = (*citer).second.get();
      area += ptr->GetClippedArea(clipLine, side);
   }

   return area;
}

Float64 rcaCapacityProblem::GetClippedConcreteArea(CollectionIndexType concreteIdx, const gpLine2d& clipLine, gpLine2d::Side side) const
{
   CHECK(0 <= concreteIdx && concreteIdx < m_ConcreteContainer.size());

   Float64 area = 0;
   for (ConstConcElementIterator citer = m_ConcElementContainer.begin(); 
        citer!=m_ConcElementContainer.end(); citer++)
   {
      const rcaConcreteElement* ptr = (*citer).second.get();
      if (ptr->GetConcreteIdx()==concreteIdx)
         area += ptr->GetClippedArea(clipLine, side);
   }

   return area;
}



Float64 rcaCapacityProblem::GetConcreteArea() const
{
   Float64 area = 0.0;
   ConstConcElementIterator citer;
   for (citer =  m_ConcElementContainer.begin(); 
        citer != m_ConcElementContainer.end();
        citer++)
   {
      const rcaConcreteElement* ptr = (*citer).second.get();
      area += ptr->GetArea();
   }

   return area;
}

void rcaCapacityProblem::MakeCopy(const rcaCapacityProblem& rOther)
{
   // heavy duty copy - start with containers.

   // first copy materials and material models.
   // concrete
   for (ConstConcreteIterator citer=rOther.m_ConcreteContainer.begin(); 
        citer!=rOther.m_ConcreteContainer.end(); citer++)
   {
      m_ConcreteContainer.push_back(ConcretePtr((*citer)->CreateClone()));
   }

   // mild steel
   for (ConstMatCurveIterator msiter=rOther.m_MsCurveContainer.begin(); 
        msiter!=rOther.m_MsCurveContainer.end(); msiter++)
   {
      const MatCurvePtr& mcpt = (*msiter).second;
      // need to cast to yield curve. Cast is safe because we know that only
      // yield-derived  curves are let into the container
      matYieldStressStrainCurve* pt = 
         dynamic_cast<matYieldStressStrainCurve*>(mcpt->CreateClone());
      CHECK(pt);
	  std::shared_ptr<matYieldStressStrainCurve> tmp(pt);
      CollectionIndexType key = msiter->first;
      m_MsCurveContainer.insert(MatCurveEntry(key,tmp));
   }

   // strand materials
   for (ConstMatCurveIterator psiter=rOther.m_PsCurveContainer.begin(); 
        psiter!=rOther.m_PsCurveContainer.end(); psiter++)
   {
      const MatCurvePtr& mcpt = (*psiter).second;
      // need to cast to yield curve. Cast is safe because we know that only
      // yield-derived  curves are let into the container
      matYieldStressStrainCurve* pt = 
         dynamic_cast<matYieldStressStrainCurve*>(mcpt->CreateClone());
      CHECK(pt);
      std::shared_ptr<matYieldStressStrainCurve> tmp(pt);
      CollectionIndexType key = (*psiter).first;
      m_MsCurveContainer.insert(MatCurveEntry(key,tmp));
   }

   // concrete elements
   for (ConstConcElementIterator ceiter=rOther.m_ConcElementContainer.begin(); 
        ceiter!=rOther.m_ConcElementContainer.end(); ceiter++)
   {
      // if concrete element has siblings, will need to add a createclone here.
      std::shared_ptr<rcaConcreteElement> tmp(std::make_shared<rcaConcreteElement>(*((*ceiter).second)));
      CollectionIndexType key = (*ceiter).first;
      m_ConcElementContainer.insert(ConcElementEntry(key,tmp));
   }

   // iterate over reinforcement elements
   for (ConstReinfElementIterator riter=m_ReinfElementContainer.begin(); 
        riter!=m_ReinfElementContainer.end(); riter++)
   {
      // if reinf element has siblings, will need to add a createclone here.
	   std::shared_ptr<rcaReinforcementElement> tmp(std::make_shared<rcaReinforcementElement>(*((*riter).second)));
      CollectionIndexType key = (*riter).first;
      m_ReinfElementContainer.insert(ReinfElementEntry(key,tmp));
   }

   // simple data - the easy stuff!
   m_NeutralAxisLocation = rOther.m_NeutralAxisLocation;
   m_FurthestDistance    = rOther.m_FurthestDistance;
   m_LastKey             = rOther.m_LastKey;             
   m_CbOffset            = rOther.m_CbOffset;            
   m_BeamStrain          = rOther.m_BeamStrain;          
   m_PlasticCentroid     = rOther.m_PlasticCentroid;
   m_PcHasChanged        = rOther.m_PcHasChanged;        
   m_CsHasChanged        = rOther.m_CsHasChanged;        

}

void rcaCapacityProblem::MakeAssignment(const rcaCapacityProblem& rOther)
{
   Clean();
   Init();

   MakeCopy( rOther );
}

//======================== ACCESS     =======================================
//======================== INQUIRY    =======================================

////////////////////////// PRIVATE    ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
//======================== OPERATORS  =======================================
//======================== OPERATIONS =======================================

void rcaCapacityProblem::GetGlobalSectionForces(Float64* pFz,
                                                Float64* pMx,
                                                Float64* pMy) const
{
   // Extra parameters for the Extended version of this call
   Float64 compRes, tensRes;
   gpPoint2d compLoc, tensLoc;

   GetGlobalSectionForcesEx(pFz,pMx,pMy,&compRes,&compLoc,&tensRes,&tensLoc);
}


void rcaCapacityProblem::GetGlobalSectionForcesEx(Float64* pFz,
                                                  Float64* pMx,
                                                  Float64* pMy,
                                                  Float64* compRes, gpPoint2d* compLoc,
                                                  Float64* tensRes, gpPoint2d* tensLoc) const
{
   Float64 fz=0,mx=0, my = 0;
   Float64 tensfz=0, tensmx=0, tensmy = 0;  // tensile only
   Float64 compfz=0, compmx=0, compmy = 0;  // compression only
   Float64 efz, emx, emy;
   gpPoint2d cg;

   // iterate over concrete elements
   for (ConstConcElementIterator citer=m_ConcElementContainer.begin(); 
        citer!=m_ConcElementContainer.end(); citer++)
   {
      const rcaConcreteElement* ptr = (*citer).second.get();
      ptr->GetForces(&efz, &emx, &emy, &cg);
      fz += efz;
      Float64 delta_mx = emx + efz*cg.Y();
      Float64 delta_my = emy - efz*cg.X();

      mx += delta_mx;
      my += delta_my;

      // Concrete is always in compression
      // If efx is > zero, it is because the concrete shape represents a hole in
      // the main concrete section.  The resultant forces and moments should reduce
      // the compression resultants for the entire section rather than apply to the
      // tensile resultant.
      compfz += efz;
      compmx += delta_mx;
      compmy += delta_my;
   }

   // iterate over reinforcement elements
   for (ConstReinfElementIterator riter=m_ReinfElementContainer.begin(); 
        riter!=m_ReinfElementContainer.end(); riter++)
   {
      const ReinfElementPtr& rept = (*riter).second;
      rept->GetForces(&efz, &emx, &emy, &cg);

      Float64 delta_mx = emx + efz*(cg.Y());
      Float64 delta_my = emy - efz*(cg.X());

      fz += efz;
      mx += delta_mx;
      my += delta_my;

      if (efz >= 0)
      {
         tensfz += efz;
         tensmx += delta_mx;
         tensmy += delta_my;
      }

      if (efz < 0)
      {
         compfz += efz;
         compmx += delta_mx;
         compmy += delta_my;
      }
   }

   
   *pFz = IsZero(fz) ? 0.0 : fz;
   *pMx = IsZero(mx) ? 0.0 : mx;
   *pMy = IsZero(my) ? 0.0 : my;

   *tensRes = tensfz;
   tensLoc->Move(-tensmy/tensfz, tensmx/tensfz);
   *compRes = compfz;
   compLoc->Move(-compmy/compfz, compmx/compfz);
}

void rcaCapacityProblem::Init()
{
   m_LastKey = 0;
   m_PcHasChanged = true;
   m_CsHasChanged = true;
}

void rcaCapacityProblem::Clean()
{
   m_MsCurveContainer.clear();
   m_PsCurveContainer.clear();
   m_ConcElementContainer.clear();
   m_ReinfElementContainer.clear();
}

//======================== ACCESS     =======================================
//======================== INQUERY    =======================================
#if defined _DEBUG
dbgDumpContext& operator<<(dbgDumpContext& os,const gpPoint2d& p)
{
   os << _T("(") << p.X() << _T(",") << p.Y() << _T(")");
   return os;
}

void rcaSectionForceDetails::Dump(dbgDumpContext& os) const
{
   os << _T("Section Force Details") << endl;
   os << _T("=====================") << endl;
   os << endl;

   os << _T("Section force relative to plastic centroid") << endl;
   os << _T("------------------------------------------") << endl;
   os << _T("Fz = ") << Fz << endl;
   os << _T("Mx = ") << Mx << endl;
   os << _T("My = ") << My << endl;
   os << endl;
   
   os << _T("PlasticCentroid  = ") << PlasticCentroid << endl;
   os << _T("NeutralAxis (PC) = ") << (NeutralAxis.PointOnLineNearest(PlasticCentroid).Y()) << endl;
   os << _T("NeutralAxis (O)  = ") << (NeutralAxis.PointOnLineNearest(gpPoint2d(0,0)).Y()) << endl;
   os << _T("NeutralAxis Slope= ") << NeutralAxis.GetSlope() << endl;
   os << _T("Beta1            = ") << Beta1 << endl;
   os << _T("CompForce        = ") << CompForce << endl;
   os << _T("LocCompForce     = ") << LocCompForce << endl;
   os << _T("TensForce        = ") << TensForce << endl;
   os << _T("LocTensForce     = ") << LocTensForce << endl;
   os << endl;

   os << _T("Pure Compression details") << endl;
   os << _T("------------------------") << endl;
   os << _T("Pc  = ") << Pc  << endl;
   os << _T("Mxc = ") << Mxc << endl;
   os << _T("Myc = ") << Myc << endl;
   os << endl;

   os << _T("Pure Tension details") << endl;
   os << _T("--------------------") << endl;
   os << _T("Pt  = ") << Pt  << endl;
   os << _T("Mxt = ") << Mxt << endl;
   os << _T("Myt = ") << Myt << endl;
   os << endl;

   os << _T("Concrete force details") << endl;
   os << _T("----------------------") << endl;
   os << _T("CompArea    = ") <<    CompArea << endl;
   os << _T("EffCompArea = ") << EffCompArea << endl;
   os << endl;

   os << _T("Reinforcment force details") << endl;
   os << _T("--------------------------") << endl;
   std::vector<rcaReinforcementForceDetails>::const_iterator iter;
   for ( iter = ReinforcementForceDetails.begin(); iter != ReinforcementForceDetails.end(); iter++ )
   {
      const rcaReinforcementForceDetails& rfd = *iter;
      rfd.Dump(os);
      os << endl;
   }
}

void rcaReinforcementForceDetails::Dump(dbgDumpContext& os) const
{
   os << _T("Ab             = ") << Ab << endl;
   os << _T("LocBar         = ") << LocBar << endl;
   os << _T("ConcreteStrain = ") << ConcreteStrain << endl;
   os << _T("InitialStrain  = ") << InitialStrain << endl;
   os << _T("BarStrain      = ") << BarStrain << endl;
   os << _T("BarStress      = ") << BarStress << endl;
   os << _T("BarForce       = ") << BarForce << endl;
}
#endif // _DEBUG