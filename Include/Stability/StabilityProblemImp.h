///////////////////////////////////////////////////////////////////////
// Stability
// Copyright © 1999-2022  Washington State Department of Transportation
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

#pragma once

#include <Stability/StabilityExp.h>
#include <Stability/StabilityTypes.h>
#include <Stability/StabilityProblem.h>
#include <Materials/SimpleConcrete.h>
#include <set>
#include <array>

namespace WBFL
{
   namespace Stability
   {
      /// Effective prestress parameters
      struct STABILITYCLASS Fpe
      {
         Float64 X; ///< Location where the effective prestress is defined
         Float64 fpe; ///< The effective prestress force
         Float64 Xps; ///< Horizontal location from the CL of the girder to the prestress force
         Float64 Yps; ///< Vertical location from the top of the girder at a location along the girder to the prestress force

         /// Compares effective prestress parameters based on location (Fpe::X)
         bool operator<(const Fpe& other) const
         {
            return X < other.X;
         }

         /// Returns true if the objects are equal
         bool operator==(const Fpe& other) const
         {
            if (!IsEqual(X, other.X))
               return false;

            if (!IsEqual(fpe, other.fpe))
               return false;

            if (!IsEqual(Xps, other.Xps))
               return false;

            if (!IsEqual(Yps, other.Yps))
               return false;

            return true;
         }
      };

      /// Defines points on the perimeter of the girder section where stresses are computed and evaluated for a girder section.
      struct STABILITYCLASS StressPoints
      {
         std::array<Point, 2> pntTL; ///< Top left point. Array indicies are [Section].
         std::array<Point, 2> pntTR; ///< Top right point. Array indicies are [Section].
         std::array<Point, 2> pntBL; ///< Bottom left point. Array indicies are [Section].
         std::array<Point, 2> pntBR; ///< Bottom right point. Array indicies are [Section].

         /// Returns true if the objects are equal
         bool operator==(const StressPoints& other) const
         {
            for (int i = 0; i < 2; i++)
            {
               if (pntTL[i] != other.pntTL[i])
               {
                  return false;
               }

               if (pntTR[i] != other.pntTR[i])
               {
                  return false;
               }

               if (pntBL[i] != other.pntBL[i])
               {
                  return false;
               }

               if (pntBR[i] != other.pntBR[i])
               {
                  return false;
               }
            }
            return true;
         }

         /// Returns true if the objects are not equal
         bool operator!=(const StressPoints& other) const
         {
            return !operator==(other);
         }
      };

      /// Defines section properties of a girder section. 
      ///
      /// Girders are defined by a sequence of sections with prismatic or linearly varying properties.
      struct STABILITYCLASS SectionProperties
      {
         std::array<Float64, 2> Ag; ///< Area of girder. Array indicies are [Section].
         std::array<Float64, 2> Ixx; ///< X-axis moment of inertia. Array indicies are [Section].
         std::array<Float64, 2> Iyy; ///< Y-axis moment of inertia. Array indicies are [Section].
         std::array<Float64, 2> Ixy; ///< Product of inertia. Array indicies are [Section].
         std::array<Float64, 2> Ytop; ///< center of mass (centroid) from top of girder. Array indicies are [Section].
         std::array<Float64, 2> Xleft; ///< center of mass from roll center. Array indicies are [Section].
         std::array<Float64, 2> Hg; ///< Height of the girder. Array indicies are [Section].
         std::array<Float64, 2> Wtf; ///< Top flange width. Array indicies are [Section].
         std::array<Float64, 2> Wbf; ///< Bottom flange width. Array indicies are [Section].
         Float64 L; ///< Distance over which these properties apply

         std::shared_ptr<StressPoints> m_pStressPoints; ///< Stress points for this girder section

         /// Returns true if the objects are equal
         bool operator==(const SectionProperties& other) const
         {
            if (!IsEqual(L, other.L))
               return false;

            for (int i = 0; i < 2; i++)
            {
               if (!IsEqual(Ag[i], other.Ag[i]))
                  return false;

               if (!IsEqual(Ixx[i], other.Ixx[i]))
                  return false;

               if (!IsEqual(Iyy[i], other.Iyy[i]))
                  return false;

               if (!IsEqual(Ixy[i], other.Ixy[i]))
                  return false;

               if (!IsEqual(Ytop[i], other.Ytop[i]))
                  return false;

               if (!IsEqual(Xleft[i], other.Xleft[i]))
                  return false;

               if (!IsEqual(Hg[i], other.Hg[i]))
                  return false;

               if (!IsEqual(Wtf[i], other.Wtf[i]))
                  return false;

               if (!IsEqual(Wbf[i], other.Wbf[i]))
                  return false;
            }

            if ((m_pStressPoints == nullptr && other.m_pStressPoints != nullptr) ||
               (m_pStressPoints != nullptr && other.m_pStressPoints == nullptr))
            {
               return false;
            }
            else if (m_pStressPoints != nullptr)
            {
               if (*m_pStressPoints != *other.m_pStressPoints)
               {
                  return false;
               }
            }

            return true;
         }
      };

      /// Defines a prestressed girder for analysis
      class STABILITYCLASS Girder : public IGirder
      {
      public:
         Girder();
         virtual ~Girder();

         bool operator==(const Girder& other) const; ///< Returns true if the objects are equal
         bool operator!=(const Girder& other) const;  ///< Returns true if the objects are not equal

         /// Associates this girder with a girder Segment model
         void SetSegment(ISegment* pSegment);

         virtual void GetSegment(ISegment** ppSegment) const override;

         /// Clears all sections and stress points
         void ClearSections();

         /// Adds a prismatic section to the girder. Returns the section index. 
         IndexType AddSection(Float64 Length, Float64 Ag, Float64 Ixx, Float64 Iyy, Float64 Ixy, Float64 Xleft, Float64 Ytop, Float64 Hg, Float64 Wtf, Float64 Wbf);

         /// Adds a linear variation section to the girder. Returns the section index. 
         IndexType AddSection(Float64 Length, Float64 Ag, Float64 Ixx, Float64 Iyy, Float64 Ixy, Float64 Xleft, Float64 Ytop, Float64 Hg, Float64 Wtf, Float64 Wbf, Float64 Ag2, Float64 Ixx2, Float64 Iyy2, Float64 Ixy2, Float64 Xcg2, Float64 Ycg2, Float64 Hg2, Float64 Wtf2, Float64 Wbf2);

         /// Changes the section properties for a section. Properties are applied to both ends of the section.
         void SetSectionProperties(IndexType sectIdx, Float64 Length, Float64 Ag, Float64 Ixx, Float64 Iyy, Float64 Ixy, Float64 Xleft, Float64 Ytop, Float64 Hg, Float64 Wtf, Float64 Wbf);

         /// Changes the section properties for a section. Properties are specified for both ends of the section.
         void SetSectionProperties(IndexType sectIdx, Float64 Length, Float64 Ag, Float64 Ixx, Float64 Iyy, Float64 Ixy, Float64 Xleft, Float64 Yt, Float64 Hg, Float64 Wtf, Float64 Wbf, Float64 Ag2, Float64 Ixx2, Float64 Iyy2, Float64 Ixy2, Float64 Xcg2, Float64 Yt2, Float64 Hg2, Float64 Wtf2, Float64 Wbf2);

         /// Assigns stress point values to a section. Stress points are applied to both ends of the section.
         void SetStressPoints(IndexType sectIdx, const Point& pntTL, const Point& pntTR, const Point& pntBL, const Point& pntBR);

         /// Assigns stress point values to a section. Stress points are specified for both ends of the section.
         void SetStressPoints(IndexType sectIdx, const Point& pntTL, const Point& pntTR, const Point& pntBL, const Point& pntBR, const Point& pntTL2, const Point& pntTR2, const Point& pntBL2, const Point& pntBR2);

         /// Removes all point loads from the model.
         void ClearPointLoads();

         /// Adds a point load to the model.
         void AddPointLoad(
            Float64 X, ///< Location from the left end of the girder.
            Float64 P ///< Magnitude of the load.
         );

         virtual IndexType GetSectionCount() const override;
         virtual Float64 GetSectionLength(IndexType sectIdx) const override;
         virtual void GetSectionProperties(IndexType sectIdx, Section section, Float64* pAg, Float64* pIxx, Float64* pIyy, Float64* pIxy, Float64* pXleft, Float64* pYtop, Float64* pHg, Float64* pWtop, Float64* pWbot) const override;
         virtual void GetSectionProperties(Float64 X, Float64* pAg, Float64* pIxx, Float64* pIyy, Float64* pIxy, Float64* pXleft, Float64* pYtop, Float64* pHg, Float64* pWtop, Float64* pWbot) const override;
         virtual void GetStressPoints(IndexType sectIdx, Section section, Point* pTL, Point* pTR, Point* pBL, Point* pBR) const override;
         virtual void GetStressPoints(Float64 X, Point* pTL, Point* pTR, Point* pBL, Point* pBR) const override;

         virtual Float64 GetGirderLength() const override;

         /// Adds a collection of point loads to the model.
         void SetAdditionalLoads(
            const std::vector<std::pair<Float64, Float64>>& vLoads ///< The first parameter of the pair is the location of the load from the left end of the girder, the second parameter is the magnitude of the point load.
         );
         virtual std::vector<std::pair<Float64, Float64>> GetAdditionalLoads() const override;

         /// Sets the drag coefficient.
         void SetDragCoefficient(Float64 Cd);
         virtual Float64 GetDragCoefficient() const override;

         /// Sets the precamber.
         void SetPrecamber(Float64 precamber);
         virtual Float64 GetPrecamber() const override;

      private:
         ISegment* m_pSegment{ nullptr }; // weak refernce
         std::vector<SectionProperties> m_vSectionProperties;

         std::vector<std::pair<Float64, Float64>> m_vPointLoads; // additional point loads (used for items precast with the girder such as internal diaphragms)
                                                                 // first parameter is location from left end of girder, second parameter is the load magnitude. Positive loads are up

         Float64 m_exb{ 0.0 }; // eccentricty of overhang bracket appurtenance loading
         Float64 m_Wb{ 0.0 }; // magnitude of overhang bracket appurtenance loading

         Float64 m_DragCoefficient{ 2.2 }; // default for I-Beams

         Float64 m_Precamber{ 0.0 };

         void GetStressPoints(const SectionProperties& props, Section section, Point* pTL, Point* pTR, Point* pBL, Point* pBR) const;
         void UpdateLength() const;
         mutable bool m_bLengthNeedsUpdate{ true };
         mutable Float64 m_L{ 0.0 };
      };

      /// Basic implementation for the IStabilityProblem interface
      class STABILITYCLASS StabilityProblemImp
      {
      public:
         StabilityProblemImp();
         StabilityProblemImp(const StabilityProblemImp& other);
         virtual ~StabilityProblemImp();

         StabilityProblemImp& operator=(const StabilityProblemImp& other);

         bool operator==(const StabilityProblemImp& other) const; ///< Returns true if the objects are equal
         bool operator!=(const StabilityProblemImp& other) const; ///< Returns true if the objects are not equal

         // Effective prestress for can vary along the girder
         // Define Fpe at different locations along the girder. Fpe will be linerally interpolated between locations.
         // If Fpe is requested before the first or after the last defined point, the first/last values will be used
         // For constant Fpe, define a Fpe at a single location

         /// Names of the effective prestress elements
         std::vector<LPCTSTR> GetPrestressNames() const;

         /// Number of effective prestress parameters for a prestress element
         IndexType GetFpeCount(LPCTSTR strName) const;

         /// Clears all effective prestress parameters
         void ClearFpe();

         /// Adds effective prestress parameters for a prestress element
         void AddFpe(
            LPCTSTR strName, ///< prestress element name
            Float64 X, ///< Location from left end of girder
            Float64 Fpe, ///< Effective prestress
            Float64 Xps, ///< Horizontal location in section coordinates
            Float64 Yps ///< Vertical location in section coordinates
         );

         /// Changes previously defined the effective prestress parameters
         // \return false if strName is invalid
         bool SetFpe(
            LPCTSTR strName, ///< prestress element name
            IndexType fpeIdx, ///< index of effective prestress parameters
            Float64 X, ///< Location from left end of girder
            Float64 Fpe, ///< Effective prestress
            Float64 Xps, ///< Horizontal location in section coordinates
            Float64 Yps ///< Vertical location in section coordinates
         );

         /// Gets effective prestress parameters
         /// \return false if strName is invalid
         bool GetFpe(
            LPCTSTR strName, ///< [in] prestress element name
            IndexType fpeIdx, ///< [in]  index of effective prestress parameters
            Float64* pX, ///< [out] Location from left end of girder
            Float64* pFpe, ///< [out] Effective prestress
            Float64* pXps, ///< [out] Horizontal location in section coordinates
            Float64* pYps ///< [out] Vertical location in section coordinates
         ) const;

         // Prestress transfer length... 
         // Linearly interpolates Fpe from zero at the ends of the girder to its full value
         // over this length

         /// Indicates if effective prestress force is adjusted for the prestress transfer length.
         void AdjustForXferLength(bool bAdjust);

         /// Indicates if effective prestress force is adjusted for the prestress transfer length.
         bool AdjustForXferLength() const;

         /// Prestress transfer length used to linearly interpolate Fpe from zero at the ends of the girder to its full value.
         void SetXferLength(Float64 xferLength, Float64 Lg);

         /// Prestress transfer length used to linearly interpolate Fpe from zero at the ends of the girder to its full value.
         Float64 GetXferLength() const;

         /// Sets the natural camber in the girder
         void SetCamber(Float64 camber);

         /// Sets lateral camber. Lateral camber is prestress induced lateral deflection, not to be confused with sweep.
         void SetLateralCamber(Float64 camber);

         /// Returns true if lateral offset of the CG from the roll axis and lateral camber are to be considered in the analysis.
         /// The roll axis is assumed to be the vertical centerline of the girder.
         /// Lateral offset of the CG generally occurs for asymmetric sections.
         void IncludeLateralRollAxisOffset(bool bInclude);

         /// Concrete definition
         void SetConcrete(const WBFL::Materials::SimpleConcrete& concrete);

         /// Concrete definition
         virtual const WBFL::Materials::SimpleConcrete& GetConcrete() const;

         /// Concrete definition
         virtual WBFL::Materials::SimpleConcrete& GetConcrete();

         /// Reinforcing steel yield strength
         void SetRebarYieldStrength(Float64 fy);

         /// Reinforcing steel yield strength
         virtual Float64 GetRebarYieldStrength() const;

         /// Sets the support locations
         void SetSupportLocations(
            Float64 Ll, ///< Support location from left end of the girder
            Float64 Lr ///< Support location from the right end of the girder
         );

         /// Elevation of the roll axis from the center of mass
         void SetYRollAxis(Float64 Yra);

         /// Sweep tolerance (length per length)
         void SetSweepTolerance(Float64 sweepTolerance);

         /// A constant that is added to the sweep.
         void SetSweepGrowth(Float64 sweepGrowth);

         /// Lateral support placement tolerance
         void SetSupportPlacementTolerance(Float64 spt);

         /// Impact factor, up and down (fraction 0.2 = 20%)
         void SetImpact(Float64 up, Float64 down);

         /// Returns effective prestress force parameters
         /// \param[in] strName name of the prestressing time
         /// \param[in] X location along the girder
         /// \param[out] pFpe effective prestress
         /// \param[out] pXps horizontal location from the CL of the girder to the prestress force
         /// \param[out] pYps vertical location from the top of the girder at a location along the girder to the prestress force
         bool GetFpe(LPCTSTR strName, Float64 X, Float64* pFpe, Float64* pXps, Float64* pYps) const;

         /// Returns the camber. This is the natural camber. Do not include formed camber (precamber).
         Float64 GetCamber() const;

         /// Sets the camber multiplier used to magnify camber
         void SetCamberMultiplier(Float64 m);

         /// Returns the camber multiplier used to magnify camber
         Float64 GetCamberMultiplier() const;

         /// Returns the lateral camber, often due to asymmetric prestressing or prestressing of an asymmetric section.
         Float64 GetLateralCamber() const;

         /// Returns true if lateral offset of the CG from the roll axis and lateral camber are to be considered in the analysis.
         /// The roll axis is assumed to be the vertical centerline of the girder.
         /// Lateral offset of the CG generally occurs for asymmetric sections.   
         bool IncludeLateralRollAxisOffset() const;

         /// Gets the support locations.
         void GetSupportLocations(Float64* pLeft, Float64* pRight) const;

         /// Returns the location of the roll axis measured from the center of mass.
         Float64 GetYRollAxis() const;

         /// Returns the sweep tolerance.
         Float64 GetSweepTolerance() const;

         /// Returns the sweep growth value
         Float64 GetSweepGrowth() const;

         /// Returns the lateral support placement tolerance.
         Float64 GetSupportPlacementTolerance() const;

         /// Get the impact factors
         void GetImpact(Float64* pIMup, Float64* pIMdown) const;

         /// Gets the wind loading parameters
         virtual void GetWindLoading(WindType* pType, Float64* pLoad) const;

         /// Sets the wind loading parameters.
         void SetWindLoading(WindType type, Float64 load);


         ///  Sets the appurtenance loading and eccentricty
         void SetAppurtenanceLoading(
            Float64 ex, ///< Eccentricty of the loading. Positive values are in the same direction as girder sweep
            Float64 W ///< Magnitude of loading uniformly distributed along the length of the girder.
         );

         ///  Gets the loading and eccentricity of appurtenances
         void GetAppurtenanceLoading(Float64* pex, Float64* pW) const;

         /// Clears all analysis points
         void ClearAnalysisPoints();

         /// Adds an analysis point
         void AddAnalysisPoint(std::unique_ptr<IAnalysisPoint>&& pAnalysisPoint);

         /// Gets the analysis points
         const std::vector<std::unique_ptr<IAnalysisPoint>>& GetAnalysisPoints() const;

         /// Gets the analysis points
         virtual const std::unique_ptr<IAnalysisPoint>& GetAnalysisPoint(IndexType idx) const;

      private:
         std::vector<std::unique_ptr<IAnalysisPoint>> m_vAnalysisPoints; // locations where moments, stresses, etc. are computed
         bool CompareAnalysisPoints(const StabilityProblemImp& other) const;

         bool m_bAdjustForXferLength{ false };
         Float64 m_XferLength{ 0.0 };
         Float64 m_Lg{ 0.0 }; // length of girder

         // this is not the most efficient data structure because we will be doing
         // lookups by name. however, we don't want the names sorted.
         // since this vector wont be more than 3 to 6 items in length, sequential
         // searching is so bad
         std::vector<std::pair<std::_tstring, std::set<Fpe>>> m_vFpe;
         IndexType FindFpe(LPCTSTR strName) const; // returns the index into m_vFpe

         Float64 m_Camber{ 0.0 };
         Float64 m_CamberMultiplier{ 1.0 };

         bool m_bIncludeRollAxisLateralOffset{ false };
         Float64 m_LateralCamber{ 0.0 };

         WBFL::Materials::SimpleConcrete m_Concrete;

         Float64 m_fy{ 0.0 }; // reinforcement yield strength

         Float64 m_Ll{ 0.0 }; // location of left support, measured from the left end of the girder
         Float64 m_Lr{ 0.0 }; // location of right support, measured from the right end of the girder

         Float64 m_SweepTolerance{ 0.0 };
         Float64 m_SweepGrowth{ 0.0 };
         Float64 m_SupportPlacementTolerance{ 0.0 };

         Float64 m_Yra{ 0.0 }; // location of the roll axis, measured from the top of the girder

         Float64 m_ImpactUp{ 0.0 };
         Float64 m_ImpactDown{ 0.0 };

         WindType m_WindLoadType{ WindType::Speed };
         Float64 m_WindLoad{ 0.0 }; // velocity or pressure, depending on m_WindLoadType

         // eccentricity and weight per unit length of appurtenances
         Float64 m_eb{ 0.0 };
         Float64 m_Wb{ 0.0 };
      };

      /// Defines the parameters of a lifting stability analysis problem
      class STABILITYCLASS LiftingStabilityProblem : public ILiftingStabilityProblem
      {
      public:
         LiftingStabilityProblem();
         LiftingStabilityProblem(const LiftingStabilityProblem& other) = default;
         virtual ~LiftingStabilityProblem();

         LiftingStabilityProblem& operator=(const LiftingStabilityProblem& other) = default;
         bool operator==(const LiftingStabilityProblem& other) const; ///< Returns true if the objects are equal
         bool operator!=(const LiftingStabilityProblem& other) const; ///< Returns true if the objects are not equal

         /// Number of effective prestress parameters for a prestress element
         IndexType GetFpeCount(LPCTSTR strName) const { return m_Imp.GetFpeCount(strName); }

         /// Clears all effective prestress parameters
         void ClearFpe() { m_Imp.ClearFpe(); }

         /// Adds effective prestress parameters for a prestress element
         /// \param strName prestress element name
         /// \param X Location from left end of girder
         /// \param Fpe Effective prestress
         /// \param Xps Horizontal location in section coordinates
         /// \param Yps Vertical location in section coordinates
         void AddFpe(LPCTSTR strName, Float64 X, Float64 Fpe, Float64 Xps, Float64 Yps) { m_Imp.AddFpe(strName, X, Fpe, Xps, Yps); }

         /// Changes previously defined the effective prestress parameters
         /// \param strName prestress element name
         /// \param fpeIdx index of effective prestress parameters
         /// \param X Location from left end of girder
         /// \param Fpe Effective prestress
         /// \param Xps Horizontal location in section coordinates
         /// \param Yps Vertical location in section coordinates
         /// \return false if strName is invalid
         bool SetFpe(LPCTSTR strName, IndexType fpeIdx, Float64 X, Float64 Fpe, Float64 Xps, Float64 Yps) { return m_Imp.SetFpe(strName, fpeIdx, X, Fpe, Xps, Yps); }

         /// Gets effective prestress parameters
         /// \return false if strName is invalid
         /// \param[in] strName prestress element name
         /// \param[in] fpeIdx index of effective prestress parameters
         /// \param[out] pX Location from left end of girder
         /// \param[out] pFpe Effective prestress
         /// \param[out] pXps Horizontal location in section coordinates
         /// \param[out] pYps Vertical location in section coordinates
         bool GetFpe(LPCTSTR strName, IndexType fpeIdx, Float64* pX, Float64* pFpe, Float64* pXps, Float64* pYps) const { return m_Imp.GetFpe(strName, fpeIdx, pX, pFpe, pXps, pYps); }

         /// Indicates if effective prestress force is adjusted for the prestress transfer length.
         bool AdjustForXferLength() const { return m_Imp.AdjustForXferLength(); }
         /// Indicates if effective prestress force is adjusted for the prestress transfer length.
         void AdjustForXferLength(bool bAdjust) { m_Imp.AdjustForXferLength(bAdjust); }

         /// Prestress transfer length used to linearly interpolate Fpe from zero at the ends of the girder to its full value.
         void SetXferLength(Float64 xferLength, Float64 Lg) { m_Imp.SetXferLength(xferLength, Lg); }
         /// Prestress transfer length used to linearly interpolate Fpe from zero at the ends of the girder to its full value.
         Float64 GetXferLength() const { return m_Imp.GetXferLength(); }

         /// Sets the natural camber in the girder
         void SetCamber(Float64 camber) { m_Imp.SetCamber(camber); }
         /// Sets the camber multiplier used to magnify camber
         void SetCamberMultiplier(Float64 m) { m_Imp.SetCamberMultiplier(m); }
         /// Returns the camber multiplier used to magnify camber
         Float64 GetCamberMultiplier() const { return m_Imp.GetCamberMultiplier(); }

         /// Sets lateral camber. Lateral camber is prestress induced lateral deflection, not to be confused with sweep.
         void SetLateralCamber(Float64 camber) { m_Imp.SetLateralCamber(camber); }

         /// Returns true if lateral offset of the CG from the roll axis and lateral camber are to be considered in the analysis.
         /// The roll axis is assumed to be the vertical centerline of the girder.
         /// Lateral offset of the CG generally occurs for asymmetric sections.   
         void IncludeLateralRollAxisOffset(bool bInclude) { m_Imp.IncludeLateralRollAxisOffset(bInclude); }

         /// Concrete definition
         void SetConcrete(const WBFL::Materials::SimpleConcrete& concrete) { m_Imp.SetConcrete(concrete); }
         
         /// Concrete definition
         const WBFL::Materials::SimpleConcrete& GetConcrete() const { return m_Imp.GetConcrete(); }
         
         /// Concrete definition
         WBFL::Materials::SimpleConcrete& GetConcrete() { return m_Imp.GetConcrete(); }

         /// Reinforcing steel yield strength
         virtual Float64 GetRebarYieldStrength() const override { return m_Imp.GetRebarYieldStrength(); }
         /// Reinforcing steel yield strength
         void SetRebarYieldStrength(Float64 fy) { m_Imp.SetRebarYieldStrength(fy); }

         /// Sets the support locations
         void SetSupportLocations(
            Float64 Ll, ///< Support location from left end of the girder
            Float64 Lr ///< Support location from the right end of the girder
         ) {
            m_Imp.SetSupportLocations(Ll, Lr);
         }

         /// Elevation of the roll axis from the center of mass
         void SetYRollAxis(Float64 Yra) { m_Imp.SetYRollAxis(Yra); }

         /// Sweep tolerance (length per length)
         void SetSweepTolerance(Float64 sweepTolerance) { m_Imp.SetSweepTolerance(sweepTolerance); }

         /// Lateral support placement tolerance
         void SetSupportPlacementTolerance(Float64 spt) { m_Imp.SetSupportPlacementTolerance(spt); }

         /// Impact factor, up and down (fraction 0.2 = 20%)
         void SetImpact(Float64 up, Float64 down) { m_Imp.SetImpact(up, down); }

         /// Names of the effective prestress elements
         virtual std::vector<LPCTSTR> GetPrestressNames() const override { return m_Imp.GetPrestressNames(); }

         /// Gets effective prestress parameters
         /// \return false if strName is invalid
         /// \param[in] strName prestress element name
         /// \param[in] X Location from left end of girder
         /// \param[out] pFpe Effective prestress
         /// \param[out] pXps Horizontal location in section coordinates
         /// \param[out] pYps Vertical location in section coordinates
         virtual bool GetFpe(LPCTSTR strName, Float64 X, Float64* pFpe, Float64* pXps, Float64* pYps) const override { return m_Imp.GetFpe(strName, X, pFpe, pXps, pYps); }

         /// Returns the camber. This is the natural camber. Do not include formed camber (precamber).
         virtual Float64 GetCamber() const override { return m_Imp.GetCamber(); }

         /// Returns the lateral camber, often due to asymmetric prestressing or prestressing of an asymmetric section.
         virtual Float64 GetLateralCamber() const override { return m_Imp.GetLateralCamber(); }

         /// Returns true if lateral offset of the CG from the roll axis and lateral camber are to be considered in the analysis.
         /// The roll axis is assumed to be the vertical centerline of the girder.
         /// Lateral offset of the CG generally occurs for asymmetric sections.   
         virtual bool IncludeLateralRollAxisOffset() const override { return m_Imp.IncludeLateralRollAxisOffset(); }

         /// Gets the support locations.
         virtual void GetSupportLocations(Float64* pLeft, Float64* pRight) const  override { m_Imp.GetSupportLocations(pLeft, pRight); }

         /// Returns the location of the roll axis measured from the center of mass.
         virtual Float64 GetYRollAxis() const override { return m_Imp.GetYRollAxis(); }

         /// Returns the sweep tolerance.
         virtual Float64 GetSweepTolerance() const  override { return m_Imp.GetSweepTolerance(); }

         /// Returns the lateral support placement tolerance.
         virtual Float64 GetSupportPlacementTolerance() const  override { return m_Imp.GetSupportPlacementTolerance(); }

         /// Get the impact factors
         virtual void GetImpact(Float64* pIMup, Float64* pIMdown) const  override { m_Imp.GetImpact(pIMup, pIMdown); }

         /// Gets the wind loading parameters
         virtual void GetWindLoading(WindType* pType, Float64* pLoad) const  override { m_Imp.GetWindLoading(pType, pLoad); }

         /// Sets the wind loading parameters.
         void SetWindLoading(WindType type, Float64 load) { m_Imp.SetWindLoading(type, load); }

         ///  Gets the parameters for appurtenance loading such as overhang brackets attached to the girder
         virtual void GetAppurtenanceLoading(Float64* pex, Float64* pW) const override { m_Imp.GetAppurtenanceLoading(pex, pW); }

         ///  Sets the appurtenance loading and eccentricty
         void SetAppurtenanceLoading(Float64 ex, Float64 W) { m_Imp.SetAppurtenanceLoading(ex, W);}

         /// Sets the lifting cable angle
         void SetLiftAngle(Float64 liftAngle);

         /// Returns the lifting cable angle.
         virtual Float64 GetLiftAngle() const override;

         /// Sets the sweep growth value
         void SetSweepGrowth(Float64 sweepGrowth) { m_Imp.SetSweepGrowth(sweepGrowth); }

         /// Returns the sweep growth value
         virtual Float64 GetSweepGrowth() const override { return m_Imp.GetSweepGrowth(); }


         /// Clears all analysis points
         void ClearAnalysisPoints() { m_Imp.ClearAnalysisPoints(); }

         /// Adds an analysis point
         void AddAnalysisPoint(std::unique_ptr<IAnalysisPoint>&& pAnalysisPoint) { m_Imp.AddAnalysisPoint(std::move(pAnalysisPoint)); }

         /// Gets the analysis points
         virtual const std::vector<std::unique_ptr<IAnalysisPoint>>& GetAnalysisPoints() const  override { return m_Imp.GetAnalysisPoints(); }

         /// Gets an analysis point
         virtual const std::unique_ptr<IAnalysisPoint>& GetAnalysisPoint(IndexType idx) const  override { return m_Imp.GetAnalysisPoint(idx); }

      private:
         StabilityProblemImp m_Imp;
         Float64 m_LiftAngle{ PI_OVER_2 };
      };

      /// Defines the parameters of a hauling stability analysis problem
      class STABILITYCLASS HaulingStabilityProblem : public IHaulingStabilityProblem
      {
      public:
         HaulingStabilityProblem();
         HaulingStabilityProblem(const HaulingStabilityProblem& other) = default;
         virtual ~HaulingStabilityProblem();

         HaulingStabilityProblem& operator=(const HaulingStabilityProblem& other) = default;

         bool operator==(const HaulingStabilityProblem& other) const; ///< Returns true if the objects are equal
         bool operator!=(const HaulingStabilityProblem& other) const; ///< Returns true if the objects are not equal

         /// Number of effective prestress parameters for a prestress element
         IndexType GetFpeCount(LPCTSTR strName) const { return m_Imp.GetFpeCount(strName); }

         /// Clears all effective prestress parameters
         void ClearFpe() { m_Imp.ClearFpe(); }

         /// Adds effective prestress parameters for a prestress element
         /// \param strName prestress element name
         /// \param X Location from left end of girder
         /// \param Fpe Effective prestress
         /// \param Xps Horizontal location in section coordinates
         /// \param Yps Vertical location in section coordinates
         void AddFpe(LPCTSTR strName, Float64 X, Float64 Fpe, Float64 Xps, Float64 Yps) { m_Imp.AddFpe(strName, X, Fpe, Xps, Yps); }

         /// Changes previously defined the effective prestress parameters
         /// \param strName prestress element name
         /// \param fpeIdx index of effective prestress parameters
         /// \param X Location from left end of girder
         /// \param Fpe Effective prestress
         /// \param Xps Horizontal location in section coordinates
         /// \param Yps Vertical location in section coordinates
         /// \return false if strName is invalid
         bool SetFpe(LPCTSTR strName, IndexType fpeIdx, Float64 X, Float64 Fpe, Float64 Xps, Float64 Yps) { return m_Imp.SetFpe(strName, fpeIdx, X, Fpe, Xps, Yps); }

         /// Gets effective prestress parameters
         /// \return false if strName is invalid
         /// \param[in] strName prestress element name
         /// \param[in] fpeIdx index of effective prestress parameters
         /// \param[out] pX Location from left end of girder
         /// \param[out] pFpe Effective prestress
         /// \param[out] pXps Horizontal location in section coordinates
         /// \param[out] pYps Vertical location in section coordinates
         bool GetFpe(LPCTSTR strName, IndexType fpeIdx, Float64* pX, Float64* pFpe, Float64* pXps, Float64* pYps) const { return m_Imp.GetFpe(strName, fpeIdx, pX, pFpe, pXps, pYps); }

         /// Indicates if effective prestress force is adjusted for the prestress transfer length.
         bool AdjustForXferLength() const { return m_Imp.AdjustForXferLength(); }
         /// Indicates if effective prestress force is adjusted for the prestress transfer length.
         void AdjustForXferLength(bool bAdjust) { m_Imp.AdjustForXferLength(bAdjust); }

         /// Prestress transfer length used to linearly interpolate Fpe from zero at the ends of the girder to its full value.
         void SetXferLength(Float64 xferLength, Float64 Lg) { m_Imp.SetXferLength(xferLength, Lg); }
         /// Prestress transfer length used to linearly interpolate Fpe from zero at the ends of the girder to its full value.
         Float64 GetXferLength() const { return m_Imp.GetXferLength(); }

         /// Sets the natural camber in the girder
         void SetCamber(Float64 camber) { m_Imp.SetCamber(camber); }
         /// Sets the camber multiplier used to magnify camber
         void SetCamberMultiplier(Float64 m) { m_Imp.SetCamberMultiplier(m); }
         /// Returns the camber multiplier used to magnify camber
         Float64 GetCamberMultiplier() const { return m_Imp.GetCamberMultiplier(); }

         /// Sets lateral camber. Lateral camber is prestress induced lateral deflection, not to be confused with sweep.
         void SetLateralCamber(Float64 camber) { m_Imp.SetLateralCamber(camber); }

         /// Returns true if lateral offset of the CG from the roll axis and lateral camber are to be considered in the analysis.
         /// The roll axis is assumed to be the vertical centerline of the girder.
         /// Lateral offset of the CG generally occurs for asymmetric sections.   
         void IncludeLateralRollAxisOffset(bool bInclude) { m_Imp.IncludeLateralRollAxisOffset(bInclude); }

         /// Concrete definition
         void SetConcrete(const WBFL::Materials::SimpleConcrete& concrete) { m_Imp.SetConcrete(concrete); }
         /// Concrete definition
         const WBFL::Materials::SimpleConcrete& GetConcrete() const { return m_Imp.GetConcrete(); }
         /// Concrete definition
         WBFL::Materials::SimpleConcrete& GetConcrete() { return m_Imp.GetConcrete(); }

         /// Reinforcing steel yield strength
         virtual Float64 GetRebarYieldStrength() const  override { return m_Imp.GetRebarYieldStrength(); }
         /// Reinforcing steel yield strength
         void SetRebarYieldStrength(Float64 fy) { m_Imp.SetRebarYieldStrength(fy); }

         /// Sets the support locations
         void SetSupportLocations(
            Float64 Ll, ///< Support location from left end of the girder
            Float64 Lr ///< Support location from the right end of the girder
         ) {
            m_Imp.SetSupportLocations(Ll, Lr);
         }

         /// Elevation of the roll axis from the center of mass
         void SetYRollAxis(Float64 Yra) { m_Imp.SetYRollAxis(Yra); }

         /// Sweep tolerance (length per length)
         void SetSweepTolerance(Float64 sweepTolerance) { m_Imp.SetSweepTolerance(sweepTolerance); }

         /// Lateral support placement tolerance
         void SetSupportPlacementTolerance(Float64 spt) { m_Imp.SetSupportPlacementTolerance(spt); }

         /// Impact factor, up and down (fraction 0.2 = 20%)
         void SetImpact(Float64 up, Float64 down) { m_Imp.SetImpact(up, down); }

         /// Names of the effective prestress elements
         virtual std::vector<LPCTSTR> GetPrestressNames() const override { return m_Imp.GetPrestressNames(); }

         /// Gets effective prestress parameters
         /// \return false if strName is invalid
         /// \param[in] strName prestress element name
         /// \param[in] X Location from left end of girder
         /// \param[out] pFpe Effective prestress
         /// \param[out] pXps Horizontal location in section coordinates
         /// \param[out] pYps Vertical location in section coordinates
         virtual bool GetFpe(LPCTSTR strName, Float64 X, Float64* pFpe, Float64* pXps, Float64* pYps) const override { return m_Imp.GetFpe(strName, X, pFpe, pXps, pYps); }

         /// Returns the camber. This is the natural camber. Do not include formed camber (precamber).
         virtual Float64 GetCamber() const override { return m_Imp.GetCamber(); }

         /// Returns the lateral camber, often due to asymmetric prestressing or prestressing of an asymmetric section.
         virtual Float64 GetLateralCamber() const override { return m_Imp.GetLateralCamber(); }

         /// Returns true if lateral offset of the CG from the roll axis and lateral camber are to be considered in the analysis.
         /// The roll axis is assumed to be the vertical centerline of the girder.
         /// Lateral offset of the CG generally occurs for asymmetric sections.   
         virtual bool IncludeLateralRollAxisOffset() const override { return m_Imp.IncludeLateralRollAxisOffset(); }

         /// Gets the support locations.
         virtual void GetSupportLocations(Float64* pLeft, Float64* pRight) const  override { m_Imp.GetSupportLocations(pLeft, pRight); }

         /// Returns the location of the roll axis measured from the center of mass.
         virtual Float64 GetYRollAxis() const override { return m_Imp.GetYRollAxis(); }

         /// Returns the sweep tolerance.
         virtual Float64 GetSweepTolerance() const  override { return m_Imp.GetSweepTolerance(); }

         /// Returns the lateral support placement tolerance.
         virtual Float64 GetSupportPlacementTolerance() const  override { return m_Imp.GetSupportPlacementTolerance(); }

         /// Sets the sweep growth value
         void SetSweepGrowth(Float64 sweepGrowth) { m_Imp.SetSweepGrowth(sweepGrowth); }
         /// Returns the sweep growth value
         virtual Float64 GetSweepGrowth() const override { return m_Imp.GetSweepGrowth(); }

         /// Get the impact factors
         virtual void GetImpact(Float64* pIMup, Float64* pIMdown) const override { m_Imp.GetImpact(pIMup, pIMdown); }

         /// Sets how impact is used in the analysis
         void SetImpactUsage(HaulingImpact impactUsage);

         /// Returns how impact is used in the analysis
         virtual HaulingImpact GetImpactUsage() const override;

         /// Gets the wind loading parameters
         virtual void GetWindLoading(WindType* pType, Float64* pLoad) const override { m_Imp.GetWindLoading(pType, pLoad); }

         /// Sets the wind loading parameters.
         void SetWindLoading(WindType type, Float64 load) { m_Imp.SetWindLoading(type, load); }

         /// Gets the parameters for appurtenance loading such as overhang brackets attached to the girder
         virtual void GetAppurtenanceLoading(Float64* pex, Float64* pW) const override { m_Imp.GetAppurtenanceLoading(pex, pW); }

         /// Sets the appurtenance loading and eccentricty
         void SetAppurtenanceLoading(Float64 ex, Float64 W) { m_Imp.SetAppurtenanceLoading(ex, W); }

         /// Sets the truck rotational stiffness (Ktheta)
         void SetRotationalStiffness(Float64 Ktheta);

         /// Returns the truck rotational stiffness (Ktheta)
         virtual Float64 GetRotationalStiffness() const override;

         /// Sets the center-to-center wheel spacing (Wcc)
         void SetSupportWidth(Float64 Wcc);

         /// Returns the center-to-center wheel spacing (Wcc)
         virtual Float64 GetSupportWidth() const override;

         /// Sets the height of the roll axis above the roadway
         void SetHeightOfRollAxis(Float64 Drs);

         /// Returns the height of the roll axis above the roadway
         virtual Float64 GetHeightOfRollAxis() const override;

         /// Sets the normal crown slope (always a positive value)
         void SetSupportSlope(Float64 crown);

         /// Returns the normal crown slope (always a positive value)
         virtual Float64 GetSupportSlope() const override;

         /// Sets the superelevation rate (always a postive value)
         void SetSuperelevation(Float64 superelevation);

         /// Returns the superelevation rate (always a postive value)
         virtual Float64 GetSuperelevation() const override;

         /// Sets the velocity of the truck. Used for computing centrifugal force.
         void SetVelocity(Float64 velocity);
         /// Returns the velocity of the truck. Used for computing centrifugal force.
         virtual Float64 GetVelocity() const override;

         /// Sets the turning radius. Used for computing centrifugal force
         void SetTurningRadius(Float64 r);
         /// Returns the turning radius. Used for computing centrifugal force
         virtual Float64 GetTurningRadius() const override;

         /// Sets the type of centrifugal force
         void SetCentrifugalForceType(CFType cfType);
         /// Returns the type of centrifugal force
         virtual CFType GetCentrifugalForceType() const override;


         /// Clears all analysis points
         void ClearAnalysisPoints() { m_Imp.ClearAnalysisPoints(); }

         /// Adds an analysis point
         void AddAnalysisPoint(std::unique_ptr<IAnalysisPoint>&& pAnalysisPoint) { m_Imp.AddAnalysisPoint(std::move(pAnalysisPoint)); }

         /// Gets the analysis points
         virtual const std::vector<std::unique_ptr<IAnalysisPoint>>& GetAnalysisPoints() const { return m_Imp.GetAnalysisPoints(); }

         /// Gets an analysis point
         virtual const std::unique_ptr<IAnalysisPoint>& GetAnalysisPoint(IndexType idx) const override { return m_Imp.GetAnalysisPoint(idx); }

      private:
         StabilityProblemImp m_Imp;

         HaulingImpact m_ImpactUsage{ HaulingImpact::Both };

         Float64 m_Ktheta{ 0.0 }; // Truck rotational stiffness
         Float64 m_Wcc{ 0.0 }; // center-center spacing between truck wheels
         Float64 m_Hrc{ 0.0 }; // height of roll axis above roadway
         Float64 m_CrownSlope{ 0.0 }; // normal crown slope
         Float64 m_Superelevation{ 0.0 }; // maximum superelevation rate

         Float64 m_Velocity{ 0.0 };
         Float64 m_Radius{ Float64_Max };
         CFType m_CFType{ CFType::Favorable };
      };

      /// Defines the parameters of a girder seated at one end stability analysis problem
      class STABILITYCLASS OneEndSeatedStabilityProblem : public IOneEndSeatedStabilityProblem
      {
      public:
         OneEndSeatedStabilityProblem();
         OneEndSeatedStabilityProblem(const OneEndSeatedStabilityProblem& other) = default;
         virtual ~OneEndSeatedStabilityProblem();

         OneEndSeatedStabilityProblem& operator=(const OneEndSeatedStabilityProblem& other) = default;

         bool operator==(const OneEndSeatedStabilityProblem& other) const; ///< Returns true if the objects are equal
         bool operator!=(const OneEndSeatedStabilityProblem& other) const; ///< Returns true if the objects are not equal

         /// Number of effective prestress parameters for a prestress element
         IndexType GetFpeCount(LPCTSTR strName) const { return m_Imp.GetFpeCount(strName); }

         /// Clears all effective prestress parameters
         void ClearFpe() { m_Imp.ClearFpe(); }

         /// Adds effective prestress parameters for a prestress element
         /// \param strName prestress element name
         /// \param X Location from left end of girder
         /// \param Fpe Effective prestress
         /// \param Xps Horizontal location in section coordinates
         /// \param Yps Vertical location in section coordinates
         void AddFpe(LPCTSTR strName, Float64 X, Float64 Fpe, Float64 Xps, Float64 Yps) { m_Imp.AddFpe(strName, X, Fpe, Xps, Yps); }

         /// Changes previously defined the effective prestress parameters
         /// \param strName prestress element name
         /// \param fpeIdx index of effective prestress parameters
         /// \param X Location from left end of girder
         /// \param Fpe Effective prestress
         /// \param Xps Horizontal location in section coordinates
         /// \param Yps Vertical location in section coordinates
         /// \return false if strName is invalid
         bool SetFpe(LPCTSTR strName, IndexType fpeIdx, Float64 X, Float64 Fpe, Float64 Xps, Float64 Yps) { return m_Imp.SetFpe(strName, fpeIdx, X, Fpe, Xps, Yps); }

         /// Gets effective prestress parameters
         /// \return false if strName is invalid
         /// \param[in] strName prestress element name
         /// \param[in] fpeIdx index of effective prestress parameters
         /// \param[out] pX Location from left end of girder
         /// \param[out] pFpe Effective prestress
         /// \param[out] pXps Horizontal location in section coordinates
         /// \param[out] pYps Vertical location in section coordinates
         bool GetFpe(LPCTSTR strName, IndexType fpeIdx, Float64* pX, Float64* pFpe, Float64* pXps, Float64* pYps) const { return m_Imp.GetFpe(strName, fpeIdx, pX, pFpe, pXps, pYps); }

         /// Indicates if effective prestress force is adjusted for the prestress transfer length.
         bool AdjustForXferLength() const { return m_Imp.AdjustForXferLength(); }

         /// Indicates if effective prestress force is adjusted for the prestress transfer length.
         void AdjustForXferLength(bool bAdjust) { m_Imp.AdjustForXferLength(bAdjust); }

         /// Prestress transfer length used to linearly interpolate Fpe from zero at the ends of the girder to its full value.
         void SetXferLength(Float64 xferLength, Float64 Lg) { m_Imp.SetXferLength(xferLength, Lg); }

         /// Prestress transfer length used to linearly interpolate Fpe from zero at the ends of the girder to its full value.
         Float64 GetXferLength() const { return m_Imp.GetXferLength(); }

         /// Sets the natural camber in the girder
         void SetCamber(Float64 camber) { m_Imp.SetCamber(camber); }

         /// Sets the camber multiplier used to magnify camber
         void SetCamberMultiplier(Float64 m) { m_Imp.SetCamberMultiplier(m); }

         /// Returns the camber multiplier used to magnify camber
         Float64 GetCamberMultiplier() const { return m_Imp.GetCamberMultiplier(); }

         /// Sets lateral camber. Lateral camber is prestress induced lateral deflection, not to be confused with sweep.
         void SetLateralCamber(Float64 camber) { m_Imp.SetLateralCamber(camber); }

         /// Returns true if lateral offset of the CG from the roll axis and lateral camber are to be considered in the analysis.
         /// The roll axis is assumed to be the vertical centerline of the girder.
         /// Lateral offset of the CG generally occurs for asymmetric sections.   
         void IncludeLateralRollAxisOffset(bool bInclude) { m_Imp.IncludeLateralRollAxisOffset(bInclude); }

         /// Concrete definition
         void SetConcrete(const WBFL::Materials::SimpleConcrete& concrete) { m_Imp.SetConcrete(concrete); }

         /// Concrete definition
         const WBFL::Materials::SimpleConcrete& GetConcrete() const { return m_Imp.GetConcrete(); }

         /// Concrete definition
         WBFL::Materials::SimpleConcrete& GetConcrete() { return m_Imp.GetConcrete(); }

         /// Reinforcing steel yield strength
         virtual Float64 GetRebarYieldStrength() const  override { return m_Imp.GetRebarYieldStrength(); }

         /// Reinforcing steel yield strength
         void SetRebarYieldStrength(Float64 fy) { m_Imp.SetRebarYieldStrength(fy); }

         /// Sets the support locations
         void SetSupportLocations(
            Float64 Ll, ///< Support location from left end of the girder
            Float64 Lr ///< Support location from the right end of the girder
         ) {
            m_Imp.SetSupportLocations(Ll, Lr);
         }

         /// Elevation of the roll axis from the center of mass
         void SetYRollAxis(Float64 Yra) { m_Imp.SetYRollAxis(Yra); }

         /// Sweep tolerance (length per length)
         void SetSweepTolerance(Float64 sweepTolerance) { m_Imp.SetSweepTolerance(sweepTolerance); }

         /// Lateral support placement tolerance
         void SetSupportPlacementTolerance(Float64 spt) { m_Imp.SetSupportPlacementTolerance(spt); }

         /// Impact factor, up and down (fraction 0.2 = 20%)
         void SetImpact(Float64 up, Float64 down) { m_Imp.SetImpact(up, down); }

         /// Names of the effective prestress elements
         virtual std::vector<LPCTSTR> GetPrestressNames() const override { return m_Imp.GetPrestressNames(); }

         /// Gets effective prestress parameters
         /// \return false if strName is invalid
         /// \param[in] strName prestress element name
         /// \param[in] X Location from left end of girder
         /// \param[out] pFpe Effective prestress
         /// \param[out] pXps Horizontal location in section coordinates
         /// \param[out] pYps Vertical location in section coordinates
         virtual bool GetFpe(LPCTSTR strName, Float64 X, Float64* pFpe, Float64* pXps, Float64* pYps) const override { return m_Imp.GetFpe(strName, X, pFpe, pXps, pYps); }

         /// Returns the camber. This is the natural camber. Do not include formed camber (precamber).
         virtual Float64 GetCamber() const override { return m_Imp.GetCamber(); }

         /// Returns the lateral camber, often due to asymmetric prestressing or prestressing of an asymmetric section.
         virtual Float64 GetLateralCamber() const override { return m_Imp.GetLateralCamber(); }

         /// Returns true if lateral offset of the CG from the roll axis and lateral camber are to be considered in the analysis.
         /// The roll axis is assumed to be the vertical centerline of the girder.
         /// Lateral offset of the CG generally occurs for asymmetric sections.   
         virtual bool IncludeLateralRollAxisOffset() const override { return m_Imp.IncludeLateralRollAxisOffset(); }

         /// Gets the support locations.
         virtual void GetSupportLocations(Float64* pLeft, Float64* pRight) const  override { m_Imp.GetSupportLocations(pLeft, pRight); }

         /// Returns the location of the roll axis measured from the center of mass.
         virtual Float64 GetYRollAxis() const override { return m_Imp.GetYRollAxis(); }

         /// Returns the sweep tolerance.
         virtual Float64 GetSweepTolerance() const  override { return m_Imp.GetSweepTolerance(); }

         /// Returns the lateral support placement tolerance.
         virtual Float64 GetSupportPlacementTolerance() const  override { return m_Imp.GetSupportPlacementTolerance(); }

         /// Sets the sweep growth value
         void SetSweepGrowth(Float64 sweepGrowth) { m_Imp.SetSweepGrowth(sweepGrowth); }

         /// Returns the sweep growth value
         virtual Float64 GetSweepGrowth() const override { return m_Imp.GetSweepGrowth(); }

         /// Get the impact factors
         virtual void GetImpact(Float64* pIMup, Float64* pIMdown) const override { m_Imp.GetImpact(pIMup, pIMdown); }

         /// Gets the wind loading parameters
         virtual void GetWindLoading(WindType* pType, Float64* pLoad) const override { m_Imp.GetWindLoading(pType, pLoad); }

         /// Sets the wind loading parameters.
         void SetWindLoading(WindType type, Float64 load) { m_Imp.SetWindLoading(type, load); }

         /// Gets the parameters for appurtenance loading such as overhang brackets attached to the girder
         virtual void GetAppurtenanceLoading(Float64* pex, Float64* pW) const override { m_Imp.GetAppurtenanceLoading(pex, pW); }

         /// Sets the appurtenance loading and eccentricty
         void SetAppurtenanceLoading(Float64 ex, Float64 W) { m_Imp.SetAppurtenanceLoading(ex, W); }

         /// Sets the truck rotational stiffness (Ktheta)
         void SetRotationalStiffness(Float64 Ktheta);

         /// Returns the truck rotational stiffness (Ktheta)
         virtual Float64 GetRotationalStiffness() const override;

         /// Sets the center-to-center wheel spacing (Wcc)
         void SetSupportWidth(Float64 Wcc);

         /// Returns the center-to-center wheel spacing (Wcc)
         virtual Float64 GetSupportWidth() const override;

         /// Sets the height of the roll axis above the roadway
         void SetHeightOfRollAxis(Float64 Drs);

         /// Returns the height of the roll axis above the roadway
         virtual Float64 GetHeightOfRollAxis() const override;

         /// Sets the normal crown slope (always a positive value)
         void SetSupportSlope(Float64 crown);

         /// Returns the normal crown slope (always a positive value)
         virtual Float64 GetSupportSlope() const override;

         /// Sets the end of the girder that is seated
         void SetSeatedEnd(GirderSide end);

         /// Return sthe end of the girder that is seated
         virtual GirderSide GetSeatedEnd() const override;

         void SetYRollLiftEnd(Float64 Yroll);
         virtual Float64 GetYRollLiftEnd() const override;

         void SetLiftPlacementTolerance(Float64 elift);
         virtual Float64 GetLiftPlacementTolerance() const override;

         void SetRotationalStiffnessAdjustmentFactor(Float64 k);
         virtual Float64 GetRotationalStiffnessAdjustmentFactor() const override;

         /// Clears all analysis points
         void ClearAnalysisPoints() { m_Imp.ClearAnalysisPoints(); }

         /// Adds an analysis point
         void AddAnalysisPoint(std::unique_ptr<IAnalysisPoint>&& pAnalysisPoint) { m_Imp.AddAnalysisPoint(std::move(pAnalysisPoint)); }

         /// Gets the analysis points
         virtual const std::vector<std::unique_ptr<IAnalysisPoint>>& GetAnalysisPoints() const { return m_Imp.GetAnalysisPoints(); }

         /// Gets an analysis point
         virtual const std::unique_ptr<IAnalysisPoint>& GetAnalysisPoint(IndexType idx) const override { return m_Imp.GetAnalysisPoint(idx); }

      private:
         StabilityProblemImp m_Imp;

         Float64 m_Ktheta{ 0.0 }; // Truck rotational stiffness
         Float64 m_Wcc{ 0.0 }; // center-center spacing between truck wheels
         Float64 m_Hrc{ 0.0 }; // height of roll axis above roadway
         Float64 m_CrownSlope{ 0.0 }; // normal crown slope
         GirderSide m_SeatedEnd{ GirderSide::Left };
         Float64 m_YrollLiftEnd{ 0.0 };
         Float64 m_elift{ 0.0 };
         Float64 m_Kadjust{ 0.50 };
      };
   }
}