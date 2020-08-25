///////////////////////////////////////////////////////////////////////
// Stability
// Copyright © 1999-2020  Washington State Department of Transportation
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

#include <Stability\StabilityLib.h>
#include <Stability\HaulingStabilityReporter.h>
#include <Stability\ReportingConstants.h>
#include <EAF\EAFApp.h>
#include <array>

#include <WBFLGenericBridgeTools\GeneralSectionDetailsTable.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



stbHaulingStabilityReporter::stbHaulingStabilityReporter()
{
}

void stbHaulingStabilityReporter::BuildSpecCheckChapter(const stbIGirder* pGirder,const stbIHaulingStabilityProblem* pStabilityProblem,const stbHaulingCheckArtifact* pArtifact,rptChapter* pChapter,LPCTSTR lpszLocColumnLabel,Float64 offset)
{
   rptParagraph* pPara = new rptParagraph(rptStyleManager::GetHeadingStyle());
   *pChapter << pPara;
   *pPara << _T("Check for Hauling to Bridge Site [5.5.4.3]") << rptNewLine;

   pPara = new rptParagraph;
   *pChapter << pPara;

   CEAFApp* pApp = EAFGetApp();
   const unitmgtIndirectMeasure* pDisplayUnits = pApp->GetDisplayUnits();

   INIT_SCALAR_PROTOTYPE(rptRcScalar, scalar, pDisplayUnits->Scalar);
   INIT_UV_PROTOTYPE( rptStressUnitValue,   stress,       pDisplayUnits->Stress, true);
   INIT_UV_PROTOTYPE( rptLengthUnitValue,  location,  pDisplayUnits->SpanLength,   false);
   INIT_UV_PROTOTYPE( rptSqrtPressureValue, tension_coeff, pDisplayUnits->SqrtPressure, false);
   INIT_UV_PROTOTYPE( rptForceUnitValue, force, pDisplayUnits->GeneralForce, false);

   const stbHaulingResults& results = pArtifact->GetHaulingResults();
   const stbHaulingCriteria& criteria = pArtifact->GetCriteria();

   CComPtr<ISegment> segment;
   pGirder->GetSegment(&segment);

   rptCDRatio cdRatio;

   LPCTSTR strCorner[] = {_T("Top Left"),_T("Top Right"),_T("Bottom Left"),_T("Bottom Right")};
   LPCTSTR strFace[] = { _T("Top"), _T("Bottom") };

   stbTypes::WindType windLoadType;
   Float64 windLoad;
   pStabilityProblem->GetWindLoading(&windLoadType,&windLoad);
   IndexType nWindCases = IsZero(windLoad) ? 0 : 1;
   IndexType nCFCases   = IsZero(pStabilityProblem->GetVelocity()) ? 0 : 1;
   LPCTSTR strWindDir[] = { _T("Left"), _T("Right") };
   LPCTSTR strCF = (pStabilityProblem->GetCentrifugalForceType() == stbTypes::Adverse ? _T("Adverse") : _T("Favorable"));

   bool bLabelWind   = (0 < nWindCases   ? true : false);
   bool bIsCF        = (0 < nCFCases     ? true : false);

   bool bLambda = (lrfdVersionMgr::SeventhEditionWith2016Interims <= lrfdVersionMgr::GetVersion() ? true : false);

   stbTypes::HaulingImpact impactUsage = pStabilityProblem->GetImpactUsage();

   for ( int s = 0; s < 2; s++ )
   {
      stbTypes::HaulingSlope slope = (stbTypes::HaulingSlope)s;

      bool bImpactForThisSlope = (impactUsage == stbTypes::Both || (impactUsage == stbTypes::NormalCrown && slope == stbTypes::CrownSlope) || (impactUsage == stbTypes::MaxSuper && slope == stbTypes::Superelevation) ? true : false);

      LPCTSTR strImpact[3];
      stbTypes::ImpactDirection impactDir[3];
      Float64 impactFactor[3];
      IndexType impactIndex[3];

      Float64 ImpactUp, ImpactDown;
      pStabilityProblem->GetImpact(&ImpactUp,&ImpactDown);
      IndexType nImpactCases = 0;
      strImpact[nImpactCases] = _T("No impact");
      impactDir[nImpactCases] = stbTypes::NoImpact;
      impactFactor[nImpactCases] = 1.0;
      impactIndex[stbTypes::NoImpact] = nImpactCases;

      if (!IsZero(ImpactUp) && bImpactForThisSlope)
      {
         nImpactCases++;
         strImpact[nImpactCases] = _T("Impact Up");
         impactDir[nImpactCases] = stbTypes::ImpactUp;
         impactFactor[nImpactCases] = 1.0 - ImpactUp;
         impactIndex[stbTypes::ImpactUp] = nImpactCases;
      }

      if (!IsZero(ImpactDown) && bImpactForThisSlope)
      {
         nImpactCases++;
         strImpact[nImpactCases] = _T("Impact Down");
         impactDir[nImpactCases] = stbTypes::ImpactDown;
         impactFactor[nImpactCases] = 1.0 + ImpactDown;
         impactIndex[stbTypes::ImpactDown] = nImpactCases;
      }

      bool bLabelImpact = (0 < nImpactCases ? true : false);

      stress.ShowUnitTag(true);

      pPara = new rptParagraph(rptStyleManager::GetHeadingStyle());
      *pChapter << pPara;
      if ( slope == stbTypes::CrownSlope )
      {
         *pPara << _T("Stresses and Factor of Safety against Cracking for Hauling at Normal Crown Slope") << rptNewLine;
      }
      else
      {
         *pPara << _T("Stresses and Factor of Safety against Cracking for Hauling at Maximum Superelevation") << rptNewLine;

         if (pStabilityProblem->GetCentrifugalForceType() == stbTypes::Favorable && !IsZero(pStabilityProblem->GetVelocity()))
         {
            // From PCI....
            // Typically, centrifugal force is ignored in the analysis of transporting rigs on curves, simulating a stopped vehicle on a 
            // superelevated surface or a transporting rig in a superelevation transition outside of the curve. However, where the transporting 
            // rig is turning on a surface with superelevation sloping away from the turning direction, the centrifugal force can add to the overturning moment.
            *pPara << color(Red) << _T("Favorable centrifugal force will appear to improve girder stability. Relying of the centrifugal force is not recommended.") << color(Black) << rptNewLine;
         }
      }

      pPara = new rptParagraph;
      *pChapter << pPara;

      bool bRotationalInstability = false;
      bool bRolloverInstability = false;
      for (IndexType impactCase = 0; impactCase <= nImpactCases; impactCase++)
      {
         if (IsZero(results.Wwind))
         {
            if (!results.bRotationalStability[slope][impactDir[impactCase]][stbTypes::Left])
            {
               bRotationalInstability = true;
               if (0 < nImpactCases)
               {
                  *pPara << color(Red) << _T("WARNING: Rotational instability for the ") << strImpact[impactCase] << _T(" case.") << color(Black) << rptNewLine;
               }
               else
               {
                  *pPara << color(Red) << _T("WARNING: Rotational instability.") << color(Black) << rptNewLine;
               }
            }

            if (!results.bRolloverStability[slope][impactDir[impactCase]][stbTypes::Left])
            {
               bRolloverInstability = true;
               if (0 < nImpactCases)
               {
                  *pPara << color(Red) << _T("WARNING: Rollover instability occurs for the ") << strImpact[impactCase] << _T(" case.") << color(Black) << rptNewLine;
               }
               else
               {
                  *pPara << color(Red) << _T("WARNING: Rollover instability.") << color(Black) << rptNewLine;
               }
            }
         }
         else
         {
            for (int w = 0; w < 2; w++)
            {
               stbTypes::WindDirection wind = (stbTypes::WindDirection)w;
               if (!results.bRotationalStability[slope][impactDir[impactCase]][wind])
               {
                  bRotationalInstability = true;
                  if (0 < nImpactCases)
                  {
                     *pPara << color(Red) << _T("WARNING: Rotational instability for the ") << strImpact[impactCase] << _T(" case with wind towards the ") << strWindDir[wind] << _T(".") << color(Black) << rptNewLine;
                  }
                  else
                  {
                     *pPara << color(Red) << _T("WARNING: Rotational instability with wind towards the ") << strWindDir[wind] << _T(".") << color(Black) << rptNewLine;
                  }
               }

               if (!results.bRolloverStability[slope][impactDir[impactCase]][wind])
               {
                  bRolloverInstability = true;
                  if (0 < nImpactCases)
                  {
                     *pPara << color(Red) << _T("WARNING: Rollover instability occurs for the ") << strImpact[impactCase] << _T(" case with wind towards the ") << strWindDir[wind] << _T(".") << color(Black) << rptNewLine;
                  }
                  else
                  {
                     *pPara << color(Red) << _T("WARNING: Rollover instability occurs with wind towards the ") << strWindDir[wind] << _T(".") << color(Black) << rptNewLine;
                  }
               }
            }
         }
      }

      if (bRotationalInstability || bRolloverInstability)
      {
         // results are useless... get the heck outta here
         continue; // next slope
      }

      *pPara << _T("Compression stress limit (general) = -") << criteria.CompressionCoefficient_GlobalStress << RPT_FC << _T(" = ") << stress.SetValue(criteria.AllowableCompression_GlobalStress) << rptNewLine;
      *pPara << _T("Compression stress limit (with lateral bending) = -") << criteria.CompressionCoefficient_PeakStress << RPT_FC << _T(" = ") << stress.SetValue(criteria.AllowableCompression_PeakStress) << rptNewLine;

      *pPara << _T("Tension stress limit = ") << tension_coeff.SetValue(criteria.TensionCoefficient[slope]);
      if ( bLambda )
      {
         *pPara << symbol(lambda);
      }
      *pPara << symbol(ROOT) << RPT_FC;
      if ( criteria.bMaxTension[slope] )
      {
         *pPara << _T(" but not more than ") << stress.SetValue(criteria.MaxTension[slope]);
      }
      *pPara << _T(" = " ) << stress.SetValue(criteria.AllowableTension[slope]) << rptNewLine;

      if ( segment )
      {
         *pPara << _T("Tension stress limit = ") << tension_coeff.SetValue(criteria.TensionCoefficientWithRebar[slope]);
         if ( bLambda )
         {
            *pPara << symbol(lambda);
         }
         *pPara << symbol(ROOT) << RPT_FC;
         *pPara << _T(" if bonded reinforcement sufficient to resist the tensile force in the concrete is provided = ") << stress.SetValue(criteria.AllowableTensionWithRebar[slope]) << rptNewLine;
      }
      else
      {
         *pPara << _T("Tensile stress limit with bonded reinforcement sufficient to resist tension force in concrete was not evaluated") << rptNewLine;
      }

      *pPara << _T("Minimum factor of safety against cracking = ") << scalar.SetValue(criteria.MinFScr) << rptNewLine;
      
      Float64 fcReqd = pArtifact->RequiredFcCompression(slope);
      *pPara << RPT_FC << _T(" required for compression stress = ");
      if ( 0 < fcReqd )
      {
         *pPara << stress.SetValue(fcReqd) << rptNewLine;
      }
      else
      {
         *pPara << symbol(infinity) << rptNewLine;
      }

      fcReqd = pArtifact->RequiredFcTension(slope);
      *pPara << RPT_FC << _T(" required for tensile stress = ");
      if ( fcReqd < 0 )
      {
         ATLASSERT(fcReqd == -99999);
         *pPara << _T("Regardless of the concrete strength, the stress requirements will not be satisfied.") << rptNewLine;
      }
      else
      {
         *pPara << stress.SetValue(fcReqd) << rptNewLine;
      }

      if ( segment )
      {
         fcReqd = pArtifact->RequiredFcTensionWithRebar(slope);
         *pPara << RPT_FC << _T(" required for tensile stress with bonded reinforcement sufficient to resist the tensile force in the concrete = ");
         if ( fcReqd < 0 )
         {
            ATLASSERT(fcReqd == -99999);
            *pPara << _T("Regardless of the concrete strength, the stress requirements will not be satisfied.") << rptNewLine;
         }
         else
         {
            *pPara << stress.SetValue(fcReqd) << rptNewLine;
         }
      }

      *pPara << _T("The tensile stress case with the minimum C/D ratio governs") << rptNewLine;

      stress.ShowUnitTag(false);

      ColumnIndexType nColumns = 11;
      ColumnIndexType nColSpan = 2;
      if ( bLabelImpact )
      {
         nColumns += 3;
         nColSpan++;
      }

      if ( bLabelWind )
      {
         nColumns += 3;
         nColSpan++;
      }

      rptRcTable* pStressTable = rptStyleManager::CreateDefaultTable(nColumns,_T(""));
      *pPara << pStressTable << rptNewLine;

      pPara = new rptParagraph(rptStyleManager::GetFootnoteStyle());
      *pChapter << pPara;
      *pPara << _T("* = upper row is stress with lateral bending, lower row is stress without lateral bending") << rptNewLine;

      ColumnIndexType col = 0;
      pStressTable->SetRowSpan(0, col, 2);

      if (lpszLocColumnLabel)
      {
         (*pStressTable)(0, col++) << COLHDR(rptRcStringLiteral(lpszLocColumnLabel), rptLengthUnitTag, pDisplayUnits->SpanLength);
      }
      else
      {
         (*pStressTable)(0, col++) << COLHDR(_T("Dist from left") << rptNewLine << _T("end of girder"), rptLengthUnitTag, pDisplayUnits->SpanLength);
      }

      pStressTable->SetColumnSpan(0, col, nColSpan);
      (*pStressTable)(0, col) << _T("Maximum Stress");
      (*pStressTable)(1, col++) << COLHDR(RPT_STRESS(_T("")), rptStressUnitTag, pDisplayUnits->Stress);
      (*pStressTable)(1, col++) << _T("Location");
      if (bLabelImpact)
      {
         (*pStressTable)(1, col++) << _T("Impact") << rptNewLine << _T("Direction");
      }
      if (bLabelWind)
      {
         (*pStressTable)(1, col++) << _T("Wind") << rptNewLine << _T("Direction");
      }

      pStressTable->SetRowSpan(0, col, 2);
      (*pStressTable)(0, col++) << COLHDR(RPT_STRESS(_T("Limit")), rptStressUnitTag, pDisplayUnits->Stress);

      pStressTable->SetRowSpan(0, col, 2);
      (*pStressTable)(0, col++) << _T("Tension") << rptNewLine << _T("Status") << rptNewLine << _T("(C/D)");

      pStressTable->SetColumnSpan(0, col, nColSpan);
      (*pStressTable)(0, col) << _T("Minimum Stress *");
      (*pStressTable)(1, col++) << COLHDR(RPT_STRESS(_T("")), rptStressUnitTag, pDisplayUnits->Stress);
      (*pStressTable)(1, col++) << _T("Location");
      if (bLabelImpact)
      {
         (*pStressTable)(1, col++) << _T("Impact") << rptNewLine << _T("Direction");
      }
      if (bLabelWind)
      {
         (*pStressTable)(1, col++) << _T("Wind") << rptNewLine << _T("Direction");
      }

      pStressTable->SetRowSpan(0, col, 2);
      (*pStressTable)(0, col++) << _T("Compression") << rptNewLine << _T("Status") << rptNewLine << _T("(C/D)");

      pStressTable->SetColumnSpan(0, col, nColSpan);
      (*pStressTable)(0, col) << _T("Cracking");

      (*pStressTable)(1, col++) << _T("Location");
      if (bLabelImpact)
      {
         (*pStressTable)(1, col++) << _T("Impact") << rptNewLine << _T("Direction");
      }
      if (bLabelWind)
      {
         (*pStressTable)(1, col++) << _T("Wind") << rptNewLine << _T("Direction");
      }
      (*pStressTable)(1, col++) << FS_CR;

      pStressTable->SetRowSpan(0, col, 2);
      (*pStressTable)(0, col++) << _T("FS") << rptNewLine << _T("Status");

      pStressTable->SetNumberOfHeaderRows(2);

      RowIndexType row = pStressTable->GetNumberOfHeaderRows();
      for( const auto& sectionResult : results.vSectionResults)
      {
         col = 0;

         const stbIAnalysisPoint* pAnalysisPoint = pStabilityProblem->GetAnalysisPoint(sectionResult.AnalysisPointIndex);
         (*pStressTable)(row,col++) << rptRcStringLiteral(pAnalysisPoint->AsString(pDisplayUnits->SpanLength,offset,false));

         stbTypes::ImpactDirection impact;
         stbTypes::WindDirection wind;
         stbTypes::Corner corner;
         Float64 fAllow;
         bool bPassed;
         Float64 cd;
         pArtifact->GetControllingTensionCase(slope,sectionResult,&impact,&wind,&corner,&fAllow,&bPassed,&cd);

         Float64 f = sectionResult.f[slope][impact][wind][corner];

         (*pStressTable)(row,col++) << stress.SetValue(f);
         (*pStressTable)(row,col++) << strCorner[corner];
         if ( bLabelImpact )
         {
            (*pStressTable)(row,col++) << strImpact[impactIndex[impact]];
         }
         if ( bLabelWind )
         {
            (*pStressTable)(row,col++) << strWindDir[wind];
         }

         if ( f < 0 )
         {
            (*pStressTable)(row,col++) << _T("-");
         }
         else
         {
            (*pStressTable)(row,col++) << stress.SetValue(fAllow);
         }

         if ( bPassed )
         {
            (*pStressTable)(row,col++) << CD_PASS_SINGLE_LINE(cdRatio,cd);
         }
         else
         {
            (*pStressTable)(row,col++) << CD_FAIL_SINGLE_LINE(cdRatio,cd);
         }

         // compression status
         ColumnIndexType col_at_start = col;
         for (int i = 0; i < 2; i++)
         {
            col = col_at_start;

            LPCTSTR strLocation;
            if (i == 0)
            {
               pArtifact->GetControllingPeakCompressionCase(slope, sectionResult, &impact, &wind, &corner, &fAllow, &bPassed, &cd);
               f = sectionResult.f[slope][impact][wind][corner];
               strLocation = strCorner[corner];
            }
            else
            {
               pArtifact->GetControllingGlobalCompressionCase(slope, sectionResult, &impact, &corner, &fAllow, &bPassed, &cd);
               f = sectionResult.fDirect[slope][impact][corner];
               strLocation = strFace[GetFace(corner)];
            }

            if (i == 1) (*pStressTable)(row, col) << rptNewLine;
            (*pStressTable)(row, col++) << stress.SetValue(f);

            if (i == 1) (*pStressTable)(row, col) << rptNewLine;
            (*pStressTable)(row, col++) << strLocation;

            if (bLabelImpact)
            {
               if (i == 1) (*pStressTable)(row, col) << rptNewLine;
               (*pStressTable)(row, col++) << strImpact[impactIndex[impact]];
            }

            if (bLabelWind)
            {
               if (i == 1) (*pStressTable)(row, col) << rptNewLine;
               (*pStressTable)(row, col++) << strWindDir[wind];
            }

            if (i == 1) (*pStressTable)(row, col) << rptNewLine;
            if (bPassed)
            {
               (*pStressTable)(row, col++) << CD_PASS_SINGLE_LINE(cdRatio, cd);
            }
            else
            {
               (*pStressTable)(row, col++) << CD_FAIL_SINGLE_LINE(cdRatio, cd);
            }
         }

         // FS cracking
         Float64 FScr = sectionResult.FScrMin[slope];
         (*pStressTable)(row, col++) << strCorner[sectionResult.FScrCorner[slope]];
         if (bLabelImpact)
         {
            (*pStressTable)(row, col++) << strImpact[impactIndex[sectionResult.FScrImpactDirection[slope]]];
         }
         if (bLabelWind)
         {
            (*pStressTable)(row, col++) << strWindDir[sectionResult.FScrWindDirection[slope]];
         }

         (*pStressTable)(row, col++) << scalar.SetValue(FScr);

         if (FScr <= criteria.MinFScr)
         {
            (*pStressTable)(row, col++) << RPT_FAIL;
         }
         else
         {
            (*pStressTable)(row, col++) << RPT_PASS;
         }

         row++;
      }

      pPara = new rptParagraph;
      *pChapter << pPara;

      rptRcTable* pTable = rptStyleManager::CreateTableNoHeading(2,_T("Factor of Safety Against Failure"));
      *pPara << pTable << rptNewLine;

      row = pTable->GetNumberOfHeaderRows();
      (*pTable)(row,0) << _T("Factor of Safety Against Failure (") << Sub2(_T("FS"),_T("f")) << _T(")");
      if (results.MinAdjFsFailure[slope] == Float64_Max)
      {
         (*pTable)(row, 1) << symbol(infinity);
      }
      else
      {
         (*pTable)(row, 1) << scalar.SetValue(results.MinAdjFsFailure[slope]);
      }
      if (bLabelImpact)
      {
         (*pTable)(row, 1) << rptNewLine << strImpact[impactIndex[results.FSfImpactDirection[slope]]];
      }
      if (bLabelWind)
      {
         (*pTable)(row, 1) << rptNewLine << _T("Wind ") << strWindDir[results.FSfWindDirection[slope]];
      }
      row++;

      (*pTable)(row,0) << _T("Allowable Factor of Safety Against Failure");
      (*pTable)(row,1) << scalar.SetValue(criteria.MinFSf);
      row++;

      (*pTable)(row,0) << _T("Status");
      if ( pArtifact->PassedFailureCheck(slope) )
      {
         (*pTable)(row,1) << RPT_PASS;
      }
      else
      {
         (*pTable)(row,1) << RPT_FAIL;
      }

      pPara = new rptParagraph;
      *pChapter << pPara;

      pTable = rptStyleManager::CreateTableNoHeading(2,_T("Factor of Safety against Rollover"));
      *pPara << pTable << rptNewLine;

      row = pTable->GetNumberOfHeaderRows();
      (*pTable)(row, 0) << _T("Factor of Safety against Rollover (") << FS_R << _T(")");
      (*pTable)(row,1) << scalar.SetValue(results.MinFsRollover[slope]);
      if (bLabelImpact)
      {
         (*pTable)(row, 1) << rptNewLine << strImpact[impactIndex[results.FSroImpactDirection[slope]]];
      }
      if (bLabelWind)
      {
         (*pTable)(row, 1) << rptNewLine << _T("Wind ") << strWindDir[results.FSroWindDirection[slope]];
      }
      row++;

      (*pTable)(row,0) << _T("Minimum Factor of Safety against Rollover");
      (*pTable)(row,1) << scalar.SetValue(criteria.MinFSf);
      row++;

      (*pTable)(row,0) << _T("Status");
      if ( pArtifact->PassedRolloverCheck(slope) )
      {
         (*pTable)(row,1) << RPT_PASS;
      }
      else
      {
         (*pTable)(row,1) << RPT_FAIL;
      }
   } // next slope

   pPara = new rptParagraph(rptStyleManager::GetHeadingStyle());
   *pChapter << pPara;
   *pPara << _T("Hauling Configuration") << rptNewLine;

   pPara = new rptParagraph;
   *pChapter << pPara;

   rptRcTable* pTable = rptStyleManager::CreateTableNoHeading(2,_T("Spacing Between Truck Supports for Hauling"));
   pTable->SetColumnStyle(0,rptStyleManager::GetTableCellStyle(CB_NONE | CJ_LEFT));
   pTable->SetStripeRowColumnStyle(0,rptStyleManager::GetTableStripeRowCellStyle(CB_NONE | CJ_LEFT));
   pTable->SetColumnStyle(1,rptStyleManager::GetTableCellStyle(CB_NONE | CJ_RIGHT));
   pTable->SetStripeRowColumnStyle(1,rptStyleManager::GetTableStripeRowCellStyle(CB_NONE | CJ_RIGHT));
   *pPara << pTable;
   (*pTable)(0,0) << _T("Distance Between Supports");
   (*pTable)(1,0) << _T("Max. Allowable Distance Between Supports");
   (*pTable)(2,0) << _T("Status");

   Float64 span_length  = results.Ls;
   Float64 allowable_span_length = criteria.MaxClearSpan;

   (*pTable)(0,1) << location.SetValue(span_length);
   (*pTable)(1,1) << location.SetValue(allowable_span_length);

   if ( IsLE(span_length,allowable_span_length) )
   {
      (*pTable)(2,1) << RPT_PASS;
   }
   else
   {
      (*pTable)(2,1) << RPT_FAIL;
   }

   pTable = rptStyleManager::CreateTableNoHeading(2,_T("Girder Support Configuration"));
   pTable->SetColumnStyle(0,rptStyleManager::GetTableCellStyle(CB_NONE | CJ_LEFT));
   pTable->SetStripeRowColumnStyle(0,rptStyleManager::GetTableStripeRowCellStyle(CB_NONE | CJ_LEFT));
   pTable->SetColumnStyle(1,rptStyleManager::GetTableCellStyle(CB_NONE | CJ_RIGHT));
   pTable->SetStripeRowColumnStyle(1,rptStyleManager::GetTableStripeRowCellStyle(CB_NONE | CJ_RIGHT));
   *pPara << pTable;

   (*pTable)(0,0) << _T("Leading Overhang (closest to cab of truck)");
   (*pTable)(1,0) << _T("Max. Allowable Leading Overhang");
   (*pTable)(2,0) << _T("Status");
   Float64 oh  = results.Lr;
   Float64 all_oh = criteria.MaxLeadingOverhang;
   (*pTable)(0,1) << location.SetValue(oh);
   (*pTable)(1,1) << location.SetValue(all_oh);
   if ( IsLE(oh,all_oh) )
   {
      (*pTable)(2,1) << RPT_PASS;
   }
   else
   {
      (*pTable)(2,1) << RPT_FAIL;
   }

   // Max Girder Weight
   pTable = rptStyleManager::CreateTableNoHeading(2,_T("Maximum Girder Weight"));
   pTable->SetColumnStyle(0,rptStyleManager::GetTableCellStyle(CB_NONE | CJ_LEFT));
   pTable->SetStripeRowColumnStyle(0,rptStyleManager::GetTableStripeRowCellStyle(CB_NONE | CJ_LEFT));
   pTable->SetColumnStyle(1,rptStyleManager::GetTableCellStyle(CB_NONE | CJ_RIGHT));
   pTable->SetStripeRowColumnStyle(1,rptStyleManager::GetTableStripeRowCellStyle(CB_NONE | CJ_RIGHT));
   *pPara << pTable;
   (*pTable)(0,0) << _T("Girder Weight");
   (*pTable)(1,0) << _T("Maximum Weight");
   (*pTable)(2,0) << _T("Status");
   Float64 wgt  = results.Wg;
   Float64 maxwgt = criteria.MaxGirderWeight;
   force.ShowUnitTag(true);
   (*pTable)(0,1) << force.SetValue(wgt);
   (*pTable)(1,1) << force.SetValue(maxwgt);
   if ( IsLE(wgt,maxwgt) )
   {
      (*pTable)(2,1) << RPT_PASS;
   }
   else
   {
      (*pTable)(2,1) << RPT_FAIL;
   }
}

void stbHaulingStabilityReporter::BuildDetailsChapter(const stbIGirder* pGirder,const stbIHaulingStabilityProblem* pStabilityProblem,const stbHaulingResults* pResults,rptChapter* pChapter, LPCTSTR lpszLocColumnLabel,Float64 offset, bool bReportTensileForceDetails)
{
   CEAFApp* pApp = EAFGetApp();
   const unitmgtIndirectMeasure* pDisplayUnits = pApp->GetDisplayUnits();

   CComPtr<ISegment> segment;
   pGirder->GetSegment(&segment);

   std::array<std::_tstring, 4> strFlange = { _T("Top Left"),_T("Top Right"),_T("Bottom Left"),_T("Bottom Right") };
   std::array<std::_tstring, 2> strTiltRotation = { _T("counter clockwise"), _T("clockwise") };
   std::array<std::_tstring, 2> strTiltDirection = { _T("left"), _T("right") };

   std::array<LPCTSTR, 3> strImpact;
   std::array<stbTypes::ImpactDirection, 3> impactDir;
   std::array<Float64, 3> impactFactor = { -1,-1,-1 };
   std::array<IndexType, 3> impactIndex = { INVALID_INDEX,INVALID_INDEX,INVALID_INDEX };

   Float64 ImpactUp, ImpactDown;
   pStabilityProblem->GetImpact(&ImpactUp,&ImpactDown);
   IndexType nImpactCases = 0;
   strImpact[nImpactCases] = _T("No impact");
   impactDir[nImpactCases] = stbTypes::NoImpact;
   impactFactor[nImpactCases] = 1.0;
   impactIndex[stbTypes::NoImpact] = nImpactCases;

   if (!IsZero(ImpactUp))
   {
      nImpactCases++;
      strImpact[nImpactCases] = _T("Impact Up");
      impactDir[nImpactCases] = stbTypes::ImpactUp;
      impactFactor[nImpactCases] = 1.0 - ImpactUp;
      impactIndex[stbTypes::ImpactUp] = nImpactCases;
   }

   if (!IsZero(ImpactDown))
   {
      nImpactCases++;
      strImpact[nImpactCases] = _T("Impact Down");
      impactDir[nImpactCases] = stbTypes::ImpactDown;
      impactFactor[nImpactCases] = 1.0 + ImpactDown;
      impactIndex[stbTypes::ImpactDown] = nImpactCases;
   }

   stbTypes::WindType windLoadType;
   Float64 windLoad;
   pStabilityProblem->GetWindLoading(&windLoadType,&windLoad);
   IndexType nWindCases = IsZero(windLoad) ? 0 : 1;
   IndexType nCFCases   = IsZero(pStabilityProblem->GetVelocity()) ? 0 : 1;
   std::array<LPCTSTR, 2> strWindDir = {_T("Left"), _T("Right")};
   std::array<LPCTSTR, 2> strWindDirEx = { _T("Increases Rotation"), _T("Decreases Rotation") }; // note that this is opposite lifting
   LPCTSTR strCF = (pStabilityProblem->GetCentrifugalForceType() == stbTypes::Adverse ? _T("Adverse (towards left)") : _T("Favorable (towards right)"));

   bool bLabelImpact = (0 < nImpactCases ? true : false);
   bool bLabelWind   = (0 < nWindCases   ? true : false);
   bool bIsCF        = (0 < nCFCases     ? true : false);


   // If epxs = 0, lateral camber = 0, Ixy = 0, and Xleft = Max(Wtf,Wbf)/2, then use a simple formatting
   // otherwise do the full formatting
   bool bSimpleFormat = false;

   // this is the first check to see if epxs and lateral camber meet the criteria for simple formatting
   // we have to deal with the section propertes later
   bool bSimpleFormatTest1 = (!pStabilityProblem->IncludeLateralRollAxisOffset() || (pStabilityProblem->IncludeLateralRollAxisOffset() && IsZero(pStabilityProblem->GetLateralCamber())));

   Float64 Ag, Ixx, Iyy, Ixy, Xcg, Ycg, Hg, Wtop, Wbot;
   pGirder->GetSectionProperties(0, stbTypes::Start, &Ag, &Ixx, &Iyy, &Ixy, &Xcg, &Ycg, &Hg, &Wtop, &Wbot);
   if (bSimpleFormatTest1)
   {
      // we might be able to use simple formatting... check the section properties
      if (IsZero(Ixy) && IsEqual(Xcg, Max(Wtop, Wbot) / 2))
      {
         // we can use simple formatting
         bSimpleFormat = true;
      }
   }

   INIT_SCALAR_PROTOTYPE(rptRcScalar, scalar, pDisplayUnits->Scalar);
   INIT_UV_PROTOTYPE( rptForceUnitValue,   force,       pDisplayUnits->GeneralForce, true);
   INIT_UV_PROTOTYPE( rptLengthUnitValue,  longLength,  pDisplayUnits->SpanLength,   true);
   INIT_UV_PROTOTYPE( rptLengthUnitValue,  shortLength, pDisplayUnits->ComponentDim, true);
   INIT_UV_PROTOTYPE(rptMomentUnitValue, moment, pDisplayUnits->Moment, false);
   INIT_UV_PROTOTYPE(rptMomentUnitValue, ot_moment, pDisplayUnits->SmallMoment, true);
   INIT_UV_PROTOTYPE( rptStressUnitValue,  stress,      pDisplayUnits->Stress,       true);
   INIT_UV_PROTOTYPE( rptStressUnitValue,  modE,        pDisplayUnits->ModE,         true);
   INIT_UV_PROTOTYPE( rptAngleUnitValue,   tiltAngle,   pDisplayUnits->RadAngle,     true);
   INIT_UV_PROTOTYPE( rptAngleUnitValue,   crackAngle,  pDisplayUnits->RadAngle,     false);
   INIT_UV_PROTOTYPE( rptAngleUnitValue,   angle,       pDisplayUnits->Angle,        true);
   INIT_UV_PROTOTYPE( rptAreaUnitValue,    area,        pDisplayUnits->Area,         false);
   INIT_UV_PROTOTYPE( rptLength4UnitValue, inertia,     pDisplayUnits->MomentOfInertia, false);
   INIT_UV_PROTOTYPE( rptPressureUnitValue, pressure,   pDisplayUnits->WindPressure, true);
   INIT_UV_PROTOTYPE( rptMomentPerAngleUnitValue,   rotational_stiffness, pDisplayUnits->MomentPerAngle, true);
   INIT_UV_PROTOTYPE( rptVelocityUnitValue, velocity, pDisplayUnits->Velocity, true);

   rptParagraph* pPara = new rptParagraph(rptStyleManager::GetHeadingStyle());
   *pChapter << pPara;
   pPara->SetName(_T("Hauling Analysis Details"));
   *pPara << _T("Hauling Analysis Details") << rptNewLine;
   *pPara << _T("Hauling to Bridge Site [5.5.4.3]") << rptNewLine;

   pPara = new rptParagraph(rptStyleManager::GetSubheadingStyle());
   *pChapter << pPara;
   *pPara << _T("General Parameters") << rptNewLine;
   pPara = new rptParagraph;
   *pChapter << pPara;

   *pPara << _T("Girder Length, ") << Sub2(_T("L"),_T("g")) << _T(" = ") << longLength.SetValue(pGirder->GetGirderLength()) << rptNewLine;
   *pPara << _T("Girder Weight, ") << Sub2(_T("W"),_T("g")) << _T(" = ") << force.SetValue(pResults->Wg) << rptNewLine;

   Float64 Ll,Lr;
   pStabilityProblem->GetSupportLocations(&Ll,&Lr);
   *pPara << _T("Trailing support overhang, ") << Sub2(_T("L"),_T("t")) << _T(" = ") << longLength.SetValue(Ll) << rptNewLine;
   *pPara << _T("Leading support overhang, ")  << Sub2(_T("L"),_T("l")) << _T(" = ") << longLength.SetValue(Lr) << rptNewLine;
   *pPara << _T("Clear span between bunk points, ") << Sub2(_T("L"),_T("s")) << _T(" = ") << longLength.SetValue(pResults->Ls) << rptNewLine;

   *pPara << _T("Height of roll axis above roadway, ") << H_RC << _T(" = ") << shortLength.SetValue(pStabilityProblem->GetHeightOfRollAxisAboveRoadway()) << rptNewLine;
   *pPara << _T("Location of Roll Axis below top of girder, ") << Sub2(_T("y"),_T("rc")) << _T(" = ") << shortLength.SetValue(-pStabilityProblem->GetYRollAxis()) << rptNewLine;
   *pPara << _T("Truck Rotational Stiffness, ") << K_THETA << _T(" = ") << rotational_stiffness.SetValue(pStabilityProblem->GetTruckRotationalStiffness()) << rptNewLine;
   *pPara << _T("Wheel line spacing (C-C distance between tires), ") << Sub2(_T("W"),_T("cc")) << _T(" = ") << shortLength.SetValue(pStabilityProblem->GetWheelLineSpacing()) << rptNewLine;

   CString slope_unit(pApp->GetUnitsMode() == eafTypes::umSI ? _T("m/m") : _T("ft/ft"));

   *pPara << _T("Normal Crown Slope ") << symbol(alpha) << _T(" = ") << pStabilityProblem->GetCrownSlope() << _T(" ") << slope_unit << rptNewLine;
   *pPara << _T("Maximum Superelevation ") << symbol(alpha) << _T(" = ") << pStabilityProblem->GetSuperelevation() << _T(" ") << slope_unit << rptNewLine;

   Float64 impactUp, impactDown;
   pStabilityProblem->GetImpact(&impactUp,&impactDown);
   *pPara << _T("Upward Impact = ") << 100*impactUp << _T("%") << rptNewLine;
   *pPara << _T("Downward Impact = ") << 100*impactDown << _T("%") << rptNewLine;

   stbTypes::HaulingImpact impactUsage = pStabilityProblem->GetImpactUsage();
   switch(impactUsage)
   {
   case stbTypes::NormalCrown:
      *pPara << _T("Impact applied only to crown slope analysis") << rptNewLine;
      break;
   case stbTypes::MaxSuper:
      *pPara << _T("Impact applied only to superelevation analysis") << rptNewLine;
      break;
   case stbTypes::Both:
      *pPara << _T("Impact applied to crown slope and superelevation analysis") << rptNewLine;
      break;
   default:
      ATLASSERT(false); // is there a new type?
   }

   if ( pApp->GetUnitsMode() == eafTypes::umUS )
   {
      Float64 sweepTolerance = pStabilityProblem->GetSweepTolerance();
      INT x = (INT)::RoundOff((1.0/(sweepTolerance*120.0)),1.0);
      *pPara << _T("Sweep Tolerance, ") << Sub2(_T("t"),_T("sweep")) << _T(" = ") << Super(_T("1")) << _T("/") << Sub(x) << _T(" in per 10 ft");
   }
   else
   {
      *pPara << _T("Sweep Tolerance, ") << Sub2(_T("t"),_T("sweep")) << _T(" = ") << 1000*pStabilityProblem->GetSweepTolerance() << _T("mm/m");
   }
   Float64 sweepGrowth = pStabilityProblem->GetSweepGrowth();
   if (!IsZero(sweepGrowth))
   {
      *pPara << _T(" + ") << shortLength.SetValue(sweepGrowth);
   }
   *pPara << rptNewLine; // finishes sweep tolerance line
   *pPara << _T("Bunking Tolerance, ") << E_BUNK << _T(" = ") << shortLength.SetValue(pStabilityProblem->GetSupportPlacementTolerance()) << rptNewLine;

   const matConcreteEx& concrete = pStabilityProblem->GetConcrete();
   *pPara << RPT_FC << _T(" = ") << stress.SetValue(concrete.GetFc()) << rptNewLine;
   *pPara << Sub2(_T("E"),_T("c")) << _T(" = Modulus of Elasticity = ") << modE.SetValue(concrete.GetE()) << rptNewLine;
   *pPara << RPT_STRESS(_T("r")) << _T(" = Modulus of Rupture = ") << stress.SetValue(concrete.GetFlexureFr()) << rptNewLine;

   IndexType nSections = pGirder->GetSectionCount();
   bool bPrismaticBeam = false;
   if ( nSections == 1 )
   {
      Float64 Ag1,Ixx1,Iyy1,Ixy1,Xcg1,Ycg1,Hg1,Wtop1,Wbot1;
      pGirder->GetSectionProperties(0,stbTypes::Start,&Ag1,&Ixx1,&Iyy1,&Ixy1,&Xcg1,&Ycg1,&Hg1,&Wtop1,&Wbot1);
      Float64 Ag2,Ixx2,Iyy2,Ixy2,Xcg2,Ycg2,Hg2,Wtop2,Wbot2;
      pGirder->GetSectionProperties(0,stbTypes::End,&Ag2,&Ixx2,&Iyy2,&Ixy2,&Xcg2,&Ycg2,&Hg2,&Wtop2,&Wbot2);
      if ( IsEqual(Ag1,Ag2) && IsEqual(Ixx1,Ixx2) && IsEqual(Iyy1,Iyy2) && IsEqual(Ixy1,Ixy2) && IsEqual(Xcg1,Xcg2) && IsEqual(Ycg1,Ycg2) && IsEqual(Hg1,Hg2) && IsEqual(Wtop1,Wtop2) && IsEqual(Wbot1,Wbot2) )
      {
         bPrismaticBeam = true;

         pPara = new rptParagraph(rptStyleManager::GetSubheadingStyle());
         *pChapter << pPara;
         *pPara << _T("Section Properties") << rptNewLine;
         pPara = new rptParagraph;
         *pChapter << pPara;

         area.ShowUnitTag(true);
         inertia.ShowUnitTag(true);
         shortLength.ShowUnitTag(true);

         *pPara << Sub2(_T("A"),_T("g")) << _T(" = ") << area.SetValue(Ag1) << rptNewLine;
         *pPara << Sub2(_T("I"),_T("xx")) << _T(" = ") << inertia.SetValue(Ixx1) << rptNewLine;
         *pPara << Sub2(_T("I"), _T("yy")) << _T(" = ") << inertia.SetValue(Iyy1) << rptNewLine;
         *pPara << Sub2(_T("I"), _T("xy")) << _T(" = ") << inertia.SetValue(Ixy1) << rptNewLine;
         if (pStabilityProblem->IncludeLateralRollAxisOffset())
         {
            *pPara << Sub2(_T("X"), _T("left")) << _T(" = ") << shortLength.SetValue(Xcg1) << rptNewLine;
         }
         *pPara << Sub2(_T("Y"), _T("top")) << _T(" = ") << shortLength.SetValue(-Ycg1) << rptNewLine;
         *pPara << Sub2(_T("H"),_T("g")) << _T(" = ") << shortLength.SetValue(Hg1) << rptNewLine;
         *pPara << Sub2(_T("W"),_T("top")) << _T(" = ") << shortLength.SetValue(Wtop1) << rptNewLine;
         *pPara << Sub2(_T("W"),_T("bot")) << _T(" = ") << shortLength.SetValue(Wbot1) << rptNewLine;

         if (!bSimpleFormat)
         {
            pPara = new rptParagraph(rptStyleManager::GetSubheadingStyle());
            *pChapter << pPara;
            *pPara << _T("Stress Points") << rptNewLine;
            pPara = new rptParagraph;
            *pChapter << pPara;

            gpPoint2d pntTL, pntTR, pntBL, pntBR;
            pGirder->GetStressPoints(0, stbTypes::Start, &pntTL, &pntTR, &pntBL, &pntBR);
            *pPara << _T("Top Left") << rptNewLine;
            *pPara << _T("X = ") << shortLength.SetValue(pntTL.X()) << rptNewLine;
            *pPara << _T("Y = ") << shortLength.SetValue(pntTL.Y()) << rptNewLine << rptNewLine;

            *pPara << _T("Top Right") << rptNewLine;
            *pPara << _T("X = ") << shortLength.SetValue(pntTR.X()) << rptNewLine;
            *pPara << _T("Y = ") << shortLength.SetValue(pntTR.Y()) << rptNewLine << rptNewLine;

            *pPara << _T("Bottom Left") << rptNewLine;
            *pPara << _T("X = ") << shortLength.SetValue(pntBL.X()) << rptNewLine;
            *pPara << _T("Y = ") << shortLength.SetValue(pntBL.Y()) << rptNewLine << rptNewLine;

            *pPara << _T("Bottom Right") << rptNewLine;
            *pPara << _T("X = ") << shortLength.SetValue(pntBR.X()) << rptNewLine;
            *pPara << _T("Y = ") << shortLength.SetValue(pntBR.Y()) << rptNewLine << rptNewLine;
         }
      }
   }

   if ( !bPrismaticBeam )
   {
      ColumnIndexType nCol = 17;
      if (pStabilityProblem->IncludeLateralRollAxisOffset())
      {
         nCol += 2;
      }
      rptRcTable* pSectPropTable = rptStyleManager::CreateDefaultTable(nCol, _T("Section Properties"));
      *pPara << pSectPropTable << rptNewLine;
      ColumnIndexType col = 0;
      pSectPropTable->SetNumberOfHeaderRows(2);

      pSectPropTable->SetRowSpan(0, 0, 2);
      (*pSectPropTable)(0, col++) << COLHDR(_T("Section") << rptNewLine << _T("Length"), rptLengthUnitTag, pDisplayUnits->SpanLength);

      ColumnIndexType nColSpan = 8;
      if (pStabilityProblem->IncludeLateralRollAxisOffset())
      {
         nColSpan++;
      }
      pSectPropTable->SetColumnSpan(0, col, nColSpan);
      (*pSectPropTable)(0, col) << _T("Start of Section");
      (*pSectPropTable)(1, col++) << COLHDR(Sub2(_T("A"), _T("g")), rptAreaUnitTag, pDisplayUnits->Area);
      (*pSectPropTable)(1, col++) << COLHDR(Sub2(_T("I"), _T("xx")), rptLength4UnitTag, pDisplayUnits->MomentOfInertia);
      (*pSectPropTable)(1, col++) << COLHDR(Sub2(_T("I"), _T("yy")), rptLength4UnitTag, pDisplayUnits->MomentOfInertia);
      (*pSectPropTable)(1, col++) << COLHDR(Sub2(_T("I"), _T("xy")), rptLength4UnitTag, pDisplayUnits->MomentOfInertia);
      if (pStabilityProblem->IncludeLateralRollAxisOffset())
      {
         (*pSectPropTable)(1, col++) << COLHDR(Sub2(_T("X"), _T("left")), rptLengthUnitTag, pDisplayUnits->ComponentDim);
      }
      (*pSectPropTable)(1, col++) << COLHDR(Sub2(_T("Y"), _T("top")), rptLengthUnitTag, pDisplayUnits->ComponentDim);
      (*pSectPropTable)(1, col++) << COLHDR(Sub2(_T("H"), _T("g")), rptLengthUnitTag, pDisplayUnits->ComponentDim);
      (*pSectPropTable)(1, col++) << COLHDR(Sub2(_T("W"), _T("top")), rptLengthUnitTag, pDisplayUnits->ComponentDim);
      (*pSectPropTable)(1, col++) << COLHDR(Sub2(_T("W"), _T("bot")), rptLengthUnitTag, pDisplayUnits->ComponentDim);

      pSectPropTable->SetColumnSpan(0, col, nColSpan);
      (*pSectPropTable)(0, col) << _T("End of Section");
      (*pSectPropTable)(1, col++) << COLHDR(Sub2(_T("A"), _T("g")), rptAreaUnitTag, pDisplayUnits->Area);
      (*pSectPropTable)(1, col++) << COLHDR(Sub2(_T("I"), _T("xx")), rptLength4UnitTag, pDisplayUnits->MomentOfInertia);
      (*pSectPropTable)(1, col++) << COLHDR(Sub2(_T("I"), _T("yy")), rptLength4UnitTag, pDisplayUnits->MomentOfInertia);
      (*pSectPropTable)(1, col++) << COLHDR(Sub2(_T("I"), _T("xy")), rptLength4UnitTag, pDisplayUnits->MomentOfInertia);
      if (pStabilityProblem->IncludeLateralRollAxisOffset())
      {
         (*pSectPropTable)(1, col++) << COLHDR(Sub2(_T("X"), _T("left")), rptLengthUnitTag, pDisplayUnits->ComponentDim);
      }
      (*pSectPropTable)(1, col++) << COLHDR(Sub2(_T("Y"), _T("top")), rptLengthUnitTag, pDisplayUnits->ComponentDim);
      (*pSectPropTable)(1, col++) << COLHDR(Sub2(_T("H"), _T("g")), rptLengthUnitTag, pDisplayUnits->ComponentDim);
      (*pSectPropTable)(1, col++) << COLHDR(Sub2(_T("W"), _T("top")), rptLengthUnitTag, pDisplayUnits->ComponentDim);
      (*pSectPropTable)(1, col++) << COLHDR(Sub2(_T("W"), _T("bot")), rptLengthUnitTag, pDisplayUnits->ComponentDim);

      rptRcTable* pStressPointTable = nullptr;
      if (!bSimpleFormat)
      {
         pStressPointTable = rptStyleManager::CreateDefaultTable(17, _T("Stress Points"));
         *pPara << pStressPointTable << rptNewLine;

         pStressPointTable->SetNumberOfHeaderRows(3);
         col = 0;
         pStressPointTable->SetRowSpan(0, col, 3);
         (*pStressPointTable)(0, col++) << COLHDR(_T("Section") << rptNewLine << _T("Length"), rptLengthUnitTag, pDisplayUnits->SpanLength);

         pStressPointTable->SetColumnSpan(0, col, 8);
         (*pStressPointTable)(0, col) << _T("Start of Section");

         pStressPointTable->SetColumnSpan(1, col, 2);
         (*pStressPointTable)(1, col) << _T("Top Left");
         (*pStressPointTable)(2, col++) << COLHDR(_T("X"), rptLengthUnitTag, pDisplayUnits->ComponentDim);
         (*pStressPointTable)(2, col++) << COLHDR(_T("Y"), rptLengthUnitTag, pDisplayUnits->ComponentDim);

         pStressPointTable->SetColumnSpan(1, col, 2);
         (*pStressPointTable)(1, col) << _T("Top Right");
         (*pStressPointTable)(2, col++) << COLHDR(_T("X"), rptLengthUnitTag, pDisplayUnits->ComponentDim);
         (*pStressPointTable)(2, col++) << COLHDR(_T("Y"), rptLengthUnitTag, pDisplayUnits->ComponentDim);

         pStressPointTable->SetColumnSpan(1, col, 2);
         (*pStressPointTable)(1, col) << _T("Bottom Left");
         (*pStressPointTable)(2, col++) << COLHDR(_T("X"), rptLengthUnitTag, pDisplayUnits->ComponentDim);
         (*pStressPointTable)(2, col++) << COLHDR(_T("Y"), rptLengthUnitTag, pDisplayUnits->ComponentDim);

         pStressPointTable->SetColumnSpan(1, col, 2);
         (*pStressPointTable)(1, col) << _T("Bottom Right");
         (*pStressPointTable)(2, col++) << COLHDR(_T("X"), rptLengthUnitTag, pDisplayUnits->ComponentDim);
         (*pStressPointTable)(2, col++) << COLHDR(_T("Y"), rptLengthUnitTag, pDisplayUnits->ComponentDim);

         pStressPointTable->SetColumnSpan(0, col, 8);
         (*pStressPointTable)(0, col) << _T("End of Section");

         pStressPointTable->SetColumnSpan(1, col, 2);
         (*pStressPointTable)(1, col) << _T("Top Left");
         (*pStressPointTable)(2, col++) << COLHDR(_T("X"), rptLengthUnitTag, pDisplayUnits->ComponentDim);
         (*pStressPointTable)(2, col++) << COLHDR(_T("Y"), rptLengthUnitTag, pDisplayUnits->ComponentDim);

         pStressPointTable->SetColumnSpan(1, col, 2);
         (*pStressPointTable)(1, col) << _T("Top Right");
         (*pStressPointTable)(2, col++) << COLHDR(_T("X"), rptLengthUnitTag, pDisplayUnits->ComponentDim);
         (*pStressPointTable)(2, col++) << COLHDR(_T("Y"), rptLengthUnitTag, pDisplayUnits->ComponentDim);

         pStressPointTable->SetColumnSpan(1, col, 2);
         (*pStressPointTable)(1, col) << _T("Bottom Left");
         (*pStressPointTable)(2, col++) << COLHDR(_T("X"), rptLengthUnitTag, pDisplayUnits->ComponentDim);
         (*pStressPointTable)(2, col++) << COLHDR(_T("Y"), rptLengthUnitTag, pDisplayUnits->ComponentDim);

         pStressPointTable->SetColumnSpan(1, col, 2);
         (*pStressPointTable)(1, col) << _T("Bottom Right");
         (*pStressPointTable)(2, col++) << COLHDR(_T("X"), rptLengthUnitTag, pDisplayUnits->ComponentDim);
         (*pStressPointTable)(2, col++) << COLHDR(_T("Y"), rptLengthUnitTag, pDisplayUnits->ComponentDim);
      }

      RowIndexType row = pSectPropTable->GetNumberOfHeaderRows();
      longLength.ShowUnitTag(false);
      shortLength.ShowUnitTag(false);
      for (IndexType sectIdx = 0; sectIdx < nSections; sectIdx++, row++)
      {
         col = 0;
         Float64 L = pGirder->GetSectionLength(sectIdx);
         (*pSectPropTable)(row, col++) << longLength.SetValue(L);

         Float64 Ag, Ixx, Iyy, Ixy, Xleft, Ytop, Hg, Wtop, Wbot;
         pGirder->GetSectionProperties(sectIdx, stbTypes::Start, &Ag, &Ixx, &Iyy, &Ixy, &Xleft, &Ytop, &Hg, &Wtop, &Wbot);
         (*pSectPropTable)(row, col++) << area.SetValue(Ag);
         (*pSectPropTable)(row, col++) << inertia.SetValue(Ixx);
         (*pSectPropTable)(row, col++) << inertia.SetValue(Iyy);
         (*pSectPropTable)(row, col++) << inertia.SetValue(Ixy);
         if (pStabilityProblem->IncludeLateralRollAxisOffset())
         {
            (*pSectPropTable)(row, col++) << shortLength.SetValue(Xleft);
         }
         (*pSectPropTable)(row, col++) << shortLength.SetValue(-Ytop);
         (*pSectPropTable)(row, col++) << shortLength.SetValue(Hg);
         (*pSectPropTable)(row, col++) << shortLength.SetValue(Wtop);
         (*pSectPropTable)(row, col++) << shortLength.SetValue(Wbot);

         pGirder->GetSectionProperties(sectIdx, stbTypes::End, &Ag, &Ixx, &Iyy, &Ixy, &Xleft, &Ytop, &Hg, &Wtop, &Wbot);
         (*pSectPropTable)(row, col++) << area.SetValue(Ag);
         (*pSectPropTable)(row, col++) << inertia.SetValue(Ixx);
         (*pSectPropTable)(row, col++) << inertia.SetValue(Iyy);
         (*pSectPropTable)(row, col++) << inertia.SetValue(Ixy);
         if (pStabilityProblem->IncludeLateralRollAxisOffset())
         {
            (*pSectPropTable)(row, col++) << shortLength.SetValue(Xleft);
         }
         (*pSectPropTable)(row, col++) << shortLength.SetValue(-Ytop);
         (*pSectPropTable)(row, col++) << shortLength.SetValue(Hg);
         (*pSectPropTable)(row, col++) << shortLength.SetValue(Wtop);
         (*pSectPropTable)(row, col++) << shortLength.SetValue(Wbot);

         if (!bSimpleFormat)
         {
            col = 0;
            row++;
            (*pStressPointTable)(row, col++) << longLength.SetValue(L);

            gpPoint2d pntTL, pntTR, pntBL, pntBR;
            pGirder->GetStressPoints(sectIdx, stbTypes::Start, &pntTL, &pntTR, &pntBL, &pntBR);
            (*pStressPointTable)(row, col++) << shortLength.SetValue(pntTL.X());
            (*pStressPointTable)(row, col++) << shortLength.SetValue(pntTL.Y());
            (*pStressPointTable)(row, col++) << shortLength.SetValue(pntTR.X());
            (*pStressPointTable)(row, col++) << shortLength.SetValue(pntTR.Y());
            (*pStressPointTable)(row, col++) << shortLength.SetValue(pntBL.X());
            (*pStressPointTable)(row, col++) << shortLength.SetValue(pntBL.Y());
            (*pStressPointTable)(row, col++) << shortLength.SetValue(pntBR.X());
            (*pStressPointTable)(row, col++) << shortLength.SetValue(pntBR.Y());

            pGirder->GetStressPoints(sectIdx, stbTypes::End, &pntTL, &pntTR, &pntBL, &pntBR);
            (*pStressPointTable)(row, col++) << shortLength.SetValue(pntTL.X());
            (*pStressPointTable)(row, col++) << shortLength.SetValue(pntTL.Y());
            (*pStressPointTable)(row, col++) << shortLength.SetValue(pntTR.X());
            (*pStressPointTable)(row, col++) << shortLength.SetValue(pntTR.Y());
            (*pStressPointTable)(row, col++) << shortLength.SetValue(pntBL.X());
            (*pStressPointTable)(row, col++) << shortLength.SetValue(pntBL.Y());
            (*pStressPointTable)(row, col++) << shortLength.SetValue(pntBR.X());
            (*pStressPointTable)(row, col++) << shortLength.SetValue(pntBR.Y());
         }
      }

      *pPara << rptNewLine;
   }

   longLength.ShowUnitTag(true);
   shortLength.ShowUnitTag(true);
 

   *pPara << rptNewLine;

   // Vertical location of center of gravity
   pPara = new rptParagraph(rptStyleManager::GetSubheadingStyle());
   *pChapter << pPara;
   *pPara << _T("Vertical Location of Center of Gravity") << rptNewLine;
   pPara = new rptParagraph;
   *pChapter << pPara;

   *pPara << _T("Offset Factor, ") << FO << _T(" = [(") << Sub2(_T("L"),_T("g")) << _T(" - ") << Sub2(_T("L"),_T("t")) << _T(" - ") << Sub2(_T("L"),_T("l")) << _T(")") << _T("/") << Sub2(_T("L"),_T("g")) << _T("]") << Super(_T("2")) << _T(" - 1/3 = ") << scalar.SetValue(pResults->OffsetFactor) << rptNewLine;

   Float64 camber = pStabilityProblem->GetCamber();
   Float64 precamber = pGirder->GetPrecamber();
   *pPara << _T("Camber Multipler, m = ") << pStabilityProblem->GetCamberMultiplier() << rptNewLine;
   *pPara << _T("Camber, ") << Sub2(symbol(DELTA), _T("camber")) << _T(" = ") << shortLength.SetValue(camber) << rptNewLine;
   *pPara << _T("Precamber, ") << Sub2(symbol(DELTA), _T("precamber")) << _T(" = ") << shortLength.SetValue(precamber) << rptNewLine;
   *pPara << _T("Location of center of gravity above roll axis, ") << YR << _T(" = ") << Sub2(_T("y"),_T("rc")) << _T(" - ") << Sub2(_T("Y"),_T("top")) << _T(" + ") << FO << _T("((m)") << Sub2(symbol(DELTA),_T("camber")) << _T(" + ") << Sub2(symbol(DELTA), _T("precamber")) << _T(") = ") << shortLength.SetValue(pResults->Dra[stbTypes::NoImpact]) << rptNewLine;

   *pPara << rptNewLine;

   // Lateral Deflection Parameters
   pPara = new rptParagraph(rptStyleManager::GetSubheadingStyle());
   *pChapter << pPara;
   *pPara << _T("Lateral Deflection Parameters") << rptNewLine;
   pPara = new rptParagraph;
   *pChapter << pPara;
   if (pStabilityProblem->IncludeLateralRollAxisOffset())
   {
      *pPara << _T("Lateral camber, ") << Sub2(symbol(DELTA), _T("lc")) << _T(" = ") << shortLength.SetValue(pStabilityProblem->GetLateralCamber()) << rptNewLine;
      if (pResults->XcgMethod == stbTypes::Exact)
      {
         Float64 Ag1, Ixx1, Iyy1, Ixy1, Xcg1, Ycg1, Hg1, Wtop1, Wbot1;
         pGirder->GetSectionProperties(0, stbTypes::Start, &Ag1, &Ixx1, &Iyy1, &Ixy1, &Xcg1, &Ycg1, &Hg1, &Wtop1, &Wbot1);
         if (Wbot1 < Wtop1)
         {
            *pPara << _T("Eccentricity of CG from roll axis, ") << Sub2(_T("e"), _T("cg")) << _T(" = ") << _T("|") << Sub2(_T("X"), _T("left")) << _T(" - ") << Sub2(_T("W"), _T("top")) << _T("/2| = ") << shortLength.SetValue(pResults->Xleft) << rptNewLine;
         }
         else
         {
            *pPara << _T("Eccentricity of CG from roll axis, ") << Sub2(_T("e"), _T("cg")) << _T(" = ") << _T("|") << Sub2(_T("X"), _T("left")) << _T(" - ") << Sub2(_T("W"), _T("bot")) << _T("/2| = ") << shortLength.SetValue(pResults->Xleft) << rptNewLine;
         }
      }
      else
      {
         *pPara << _T("Eccentricity of CG from roll axis, ") << Sub2(_T("e"), _T("cg")) << _T(" = ") << symbol(SUM) << _T("(0.5(") << Sub2(_T("A"), _T("g i")) << Super2(Sub2(_T("X"), _T("left")), _T("i")) << _T(" + ") << Sub2(_T("A"), _T("g i+1")) << Super2(Sub2(_T("X"), _T("left")), _T("i+1")) << _T("))") << Sub2(_T("w"), _T("c")) << _T(")(Section Length)") << _T(")/") << Sub2(_T("W"), _T("g")) << _T(" = ") << shortLength.SetValue(pResults->Xleft) << rptNewLine;
      }
   }
   *pPara << _T("Lateral Sweep, ") << D_SWEEP << _T(" = ") << Sub2(_T("L"), _T("g")) << Sub2(_T("t"), _T("sweep"));
   if (!IsZero(sweepGrowth))
   {
      *pPara << _T(" + ") << shortLength.SetValue(sweepGrowth);
   }
   *pPara << _T(" = ") << shortLength.SetValue(pResults->LateralSweep) << rptNewLine;

   *pPara << _T("Initial lateral eccentricity of center of gravity of girder due to lateral sweep and eccentricity of bunking devices from centerline of girder, ") << rptNewLine;
   if (pStabilityProblem->IncludeLateralRollAxisOffset())
   {
      *pPara << EI << _T(" = ") << FO << _T("(") << D_SWEEP << _T(" + ") << Sub2(symbol(DELTA),_T("lc")) << _T(")") << _T(" + ") << E_BUNK << _T(" + ") << Sub2(_T("e"), _T("cg")) << _T(" = ") << shortLength.SetValue(pResults->EccLateralSweep[stbTypes::NoImpact]) << rptNewLine;
   }
   else
   {
      *pPara << EI << _T(" = ") << FO << D_SWEEP << _T(" + ") << E_BUNK << _T(" = ") << shortLength.SetValue(pResults->EccLateralSweep[stbTypes::NoImpact]) << rptNewLine;
   }
   *pPara << rptNewLine;

   *pPara << _T("Lateral Deflection of center of gravity due to total girder weight applied to weak axis, ") << ZO << rptNewLine;
   if ( pResults->ZoMethod == stbTypes::Exact )
   {
      if (bSimpleFormat)
      {
         *pPara << ZO << _T(" = (") << Sub2(_T("(IM)W"), _T("g")) << _T("/12E") << Sub2(_T("I"), _T("yy")) << Sub2(_T("L"), _T("g")) << Super(_T("2")) << _T(")(")
            << Sub2(_T("L"), _T("s")) << Super(_T("5")) << _T("/10") << _T(" - ")
            << Super2(_T("a"), _T("2")) << Sub2(_T("L"), _T("s")) << Super(_T("3")) << _T(" + ")
            << _T("3") << Super2(_T("a"), _T("4")) << Sub2(_T("L"), _T("s")) << _T(" + ")
            << _T("6") << Super2(_T("a"), _T("5")) << _T("/5") << _T(")") << rptNewLine;
      }
      else
      {
         *pPara << ZO << _T(" = (") << Sub2(_T("(IM)W"), _T("g")) << Sub2(_T("I"), _T("xx")) << _T("/(12E(") << Sub2(_T("I"), _T("xx")) << Sub2(_T("I"), _T("yy")) << _T("-") << Super2(Sub2(_T("I"), _T("xy")), _T("2")) << _T(")") << Sub2(_T("L"), _T("g")) << Super(_T("2")) << _T(")(")
            << Sub2(_T("L"), _T("s")) << Super(_T("5")) << _T("/10") << _T(" - ")
            << Super2(_T("a"), _T("2")) << Sub2(_T("L"), _T("s")) << Super(_T("3")) << _T(" + ")
            << _T("3") << Super2(_T("a"), _T("4")) << Sub2(_T("L"), _T("s")) << _T(" + ")
            << _T("6") << Super2(_T("a"), _T("5")) << _T("/5") << _T(")") << rptNewLine;
      }
   }

   for ( IndexType impactCase = 0; impactCase <= nImpactCases; impactCase++ )
   {
      if (0 < impactCase)
      {
         *pPara  << _T(", ");
      }
      *pPara << ZO << _T(" = ") << shortLength.SetValue(pResults->Zo[impactDir[impactCase]]) << _T(" (") << strImpact[impactCase] << _T(")");
   }
   *pPara << rptNewLine;

   // Wind Load Parameters
   pPara = new rptParagraph(rptStyleManager::GetSubheadingStyle());
   *pChapter << pPara;
   *pPara << _T("Wind Load Parameters") << rptNewLine;
   pPara = new rptParagraph;
   *pChapter << pPara;
   if ( windLoadType == stbTypes::Speed )
   {
      *pPara << _T("Wind Speed, V = ") << velocity.SetValue(windLoad) << rptNewLine;
      *pPara << _T("Pressure exposure and elevation coefficient, ") << Sub2(_T("K"),_T("z")) << _T(" = 1.0 for Service I (LRFD 3.8.1.2)") << rptNewLine;
      *pPara << _T("Gust effect factor, G = 1.0 for Service I (LRFD 3.8.1.2)") << rptNewLine;
      *pPara << _T("Drag Coefficient, ") << Sub2(_T("C"),_T("d")) << _T(" = ") << scalar.SetValue(pGirder->GetDragCoefficient()) << rptNewLine;
      *pPara << _T("Wind Pressure, ") << Sub2(_T("P"),_T("z")) << _T(" = ") << W_WIND << _T(" = 2.56x") << Super2(_T("10"),_T("-6")) << Super2(_T("V"),_T("2")) << Sub2(_T("K"),_T("z")) << _T("G") << Sub2(_T("C"),_T("d")) << _T(" = ") << pressure.SetValue(pResults->WindPressure) << rptNewLine;
   }
   else
   {
      *pPara << _T("Lateral wind pressure, ") << W_WIND << _T(" = ") << pressure.SetValue(pResults->WindPressure) << rptNewLine;
   }
   *pPara << _T("Total Wind Load, ") << W_WIND << _T(" = ") << force.SetValue(pResults->Wwind) << rptNewLine;
   *pPara << _T("Location of resultant wind force above roll axis, ") << W_WIND << rptNewLine;
   *pPara << Y_WIND << _T(" = ") << Sub2(_T("y"),_T("rc")) << _T(" - ") << Sub2(_T("H"),_T("g")) << _T("/2 + ") << FO << _T("((m)") << Sub2(symbol(DELTA),_T("camber")) << _T(" + ") << Sub2(symbol(DELTA),_T("precamber")) << _T(") = ") << shortLength.SetValue(pResults->Ywind[stbTypes::NoImpact]) << rptNewLine;

   *pPara << rptNewLine;

   *pPara << _T("Lateral Deflection due to wind applied toward the left, ") << Z_WIND << rptNewLine;
   *pPara << Z_WIND << _T(" = ") << W_WIND << ZO << _T("/[") << Sub2(_T("(IM)W"), _T("g")) << _T("]") << rptNewLine;
  
   for (IndexType impactCase = 0; impactCase <= nImpactCases; impactCase++)
   {
      if (0 < impactCase)
      {
         *pPara << _T(", ");
      }
      *pPara << Z_WIND << _T(" = ") << shortLength.SetValue(pResults->ZoWind[impactDir[impactCase]]) << _T(" (") << strImpact[impactCase] << _T(")");
   }
   *pPara << rptNewLine;

   *pPara << _T("Overturning moment due to wind applied toward the left, ") << Sub2(_T("M"), _T("otwind")) << _T(" = ") << ot_moment.SetValue(pResults->MotWind) << rptNewLine;
   
   // Centrifugal Force Parameters
   pPara = new rptParagraph(rptStyleManager::GetSubheadingStyle());
   *pChapter << pPara;
   *pPara << _T("Centrifugal Force Parameters") << rptNewLine;
   pPara = new rptParagraph;
   *pChapter << pPara;
   *pPara << _T("Turning radius, R = ") << longLength.SetValue(pStabilityProblem->GetTurningRadius()) << rptNewLine;
   *pPara << _T("Velocity, V = ") << velocity.SetValue(pStabilityProblem->GetVelocity()) << rptNewLine;
   *pPara << _T("Centrigual Force, ") << W_CF << _T(" = (") << Sub2(_T("W"),_T("g")) << Super2(_T("V"),_T("2")) << _T(")/(gR) = ") << force.SetValue(pResults->Wcf) << rptNewLine;
   *pPara << _T("Centrigural force is ") << strCF << rptNewLine;
   *pPara << _T("Location of resultant centrifugal force above roll axis, ") << Y_CF << _T(" = ") << YR << _T(" = ") << shortLength.SetValue(pResults->Dra[stbTypes::NoImpact]) << rptNewLine;
   *pPara << _T("Lateral Deflection due to centrifugal force, ") << Sub2(_T("z"),_T("cf")) << _T(" = ") << W_CF << ZO << _T("/") << Sub2(_T("W"),_T("g")) << _T(" = ") << shortLength.SetValue(pResults->ZoCF) << rptNewLine;
   *pPara << _T("Overturning moment due to centrigural force, ") << Sub2(_T("M"), _T("otcf")) << _T(" = ") << W_CF << Y_CF << _T(" = ") << ot_moment.SetValue(pResults->MotCF) << rptNewLine;
   *pPara << rptNewLine;

   auto vNames = pStabilityProblem->GetPrestressNames();

   // nColumns
   // 1 for location
   // 2/4 for stress (top & bottom for simple format otherwise all 4 corners)
   // 2/3 * number of prestress types (2 for Fpe and Yps, 3 for Fpe, Xps, and Yps)
   ColumnIndexType nColumns = 1 + (bSimpleFormat ? 2 : 4) + (bSimpleFormat ? 2 : 3)*vNames.size();
   rptRcTable* pPrestressTable = rptStyleManager::CreateDefaultTable(nColumns, _T("Stress due to Effective Prestress"));
   *pPara << pPrestressTable << rptNewLine;

   ColumnIndexType col = 0;
   pPrestressTable->SetNumberOfHeaderRows(2);
   pPrestressTable->SetRowSpan(0, col, 2);
   if (lpszLocColumnLabel)
   {
      (*pPrestressTable)(0, col++) << COLHDR(rptRcStringLiteral(lpszLocColumnLabel), rptLengthUnitTag, pDisplayUnits->SpanLength);
   }
   else
   {
      (*pPrestressTable)(0, col++) << COLHDR(_T("Dist from") << rptNewLine << _T("left end"), rptLengthUnitTag, pDisplayUnits->SpanLength);
   }

   for (const auto strName : vNames)
   {
      ColumnIndexType nColSpan = (bSimpleFormat ? 2 : 3);
      pPrestressTable->SetColumnSpan(0, col, nColSpan);
      (*pPrestressTable)(0, col) << strName;
      (*pPrestressTable)(1, col++) << COLHDR(Sub2(_T("F"), _T("pe")), rptForceUnitTag, pDisplayUnits->GeneralForce);
      if (bSimpleFormat)
      {
         (*pPrestressTable)(1, col++) << COLHDR(Sub2(_T("e"), _T("ps")), rptLengthUnitTag, pDisplayUnits->ComponentDim);
      }
      else
      {
         (*pPrestressTable)(1, col++) << COLHDR(Sub2(_T("e"), _T("psx")), rptLengthUnitTag, pDisplayUnits->ComponentDim);
         (*pPrestressTable)(1, col++) << COLHDR(Sub2(_T("e"), _T("psy")), rptLengthUnitTag, pDisplayUnits->ComponentDim);
      }
   }

   ColumnIndexType nColSpan = (bSimpleFormat ? 2 : 4);
   pPrestressTable->SetColumnSpan(0, col, nColSpan);
   (*pPrestressTable)(0, col) << RPT_STRESS(_T("ps"));

   if (bSimpleFormat)
   {
      (*pPrestressTable)(1, col++) << COLHDR(_T("Top"), rptStressUnitTag, pDisplayUnits->Stress);
      (*pPrestressTable)(1, col++) << COLHDR(_T("Bottom"), rptStressUnitTag, pDisplayUnits->Stress);
   }
   else
   {
      (*pPrestressTable)(1, col++) << COLHDR(_T("Top Left"), rptStressUnitTag, pDisplayUnits->Stress);
      (*pPrestressTable)(1, col++) << COLHDR(_T("Top Right"), rptStressUnitTag, pDisplayUnits->Stress);
      (*pPrestressTable)(1, col++) << COLHDR(_T("Bottom Left"), rptStressUnitTag, pDisplayUnits->Stress);
      (*pPrestressTable)(1, col++) << COLHDR(_T("Bottom Right"), rptStressUnitTag, pDisplayUnits->Stress);
   }

   longLength.ShowUnitTag(false);
   shortLength.ShowUnitTag(false);
   force.ShowUnitTag(false);
   stress.ShowUnitTag(false);
   area.ShowUnitTag(false);

   RowIndexType row = pPrestressTable->GetNumberOfHeaderRows();
   for (const auto& sectionResult : pResults->vSectionResults)
   {
      col = 0;

      const stbIAnalysisPoint* pAnalysisPoint = pStabilityProblem->GetAnalysisPoint(sectionResult.AnalysisPointIndex);

      (*pPrestressTable)(row, col++) << rptRcStringLiteral(pAnalysisPoint->AsString(pDisplayUnits->SpanLength, offset, false));

      Float64 Ag, Ixx, Iyy, Ixy, Xleft, Ytop, Hg, Wtop, Wbot;
      pGirder->GetSectionProperties(pAnalysisPoint->GetLocation(), &Ag, &Ixx, &Iyy, &Ixy, &Xleft, &Ytop, &Hg, &Wtop, &Wbot);

      for (const auto strName : vNames)
      {
         Float64 Fpe, Xps, Yps;
         pStabilityProblem->GetFpe(strName, pAnalysisPoint->GetLocation(), &Fpe, &Xps, &Yps);
         (*pPrestressTable)(row, col++) << force.SetValue(Fpe);
         if (!bSimpleFormat)
         {
            (*pPrestressTable)(row, col++) << shortLength.SetValue(Xleft - Xps);
         }
         (*pPrestressTable)(row, col++) << shortLength.SetValue(Ytop - Yps);
      }

      if (bSimpleFormat)
      {
         ATLASSERT(IsEqual(sectionResult.fps[stbTypes::TopLeft], sectionResult.fps[stbTypes::TopRight],0.001));
         ATLASSERT(IsEqual(sectionResult.fps[stbTypes::BottomLeft], sectionResult.fps[stbTypes::BottomRight], 0.001));
         (*pPrestressTable)(row, col++) << stress.SetValue(sectionResult.fps[stbTypes::TopLeft]);
         (*pPrestressTable)(row, col++) << stress.SetValue(sectionResult.fps[stbTypes::BottomLeft]);
      }
      else
      {
         (*pPrestressTable)(row, col++) << stress.SetValue(sectionResult.fps[stbTypes::TopLeft]);
         (*pPrestressTable)(row, col++) << stress.SetValue(sectionResult.fps[stbTypes::TopRight]);
         (*pPrestressTable)(row, col++) << stress.SetValue(sectionResult.fps[stbTypes::BottomLeft]);
         (*pPrestressTable)(row, col++) << stress.SetValue(sectionResult.fps[stbTypes::BottomRight]);
      }

      row++;
   }

   *pPara << Sub2(_T("F"), _T("pe")) << _T(" = effective prestress force") << rptNewLine;
   if (bSimpleFormat)
   {
      *pPara << Sub2(_T("e"), _T("ps")) << _T(" = eccentricity of the prestress force. Positive values are for ") << Sub2(_T("F"), _T("pe")) << _T(" below the centroidal axis") << rptNewLine;
      *pPara << RPT_STRESS(_T("ps")) << _T(" = ") << _T("stress due to prestressing") << rptNewLine;
      *pPara << _T("Top ") << RPT_STRESS(_T("ps")) << _T(" = -") << Sub2(_T("F"), _T("pe")) << _T("(1/") << Sub2(_T("A"), _T("g")) << _T(" - ") << Sub2(_T("e"), _T("ps")) << Sub2(_T("Y"), _T("top")) << _T("/") << Sub2(_T("I"), _T("x")) << _T(")") << rptNewLine;
      *pPara << _T("Bottom ") << RPT_STRESS(_T("ps")) << _T(" = -") << Sub2(_T("F"), _T("pe")) << _T("(1/") << Sub2(_T("A"), _T("g")) << _T(" + ") << Sub2(_T("e"), _T("ps")) << _T("(") << Sub2(_T("H"), _T("g")) << _T(" - ") << Sub2(_T("Y"), _T("top")) << _T(")/") << Sub2(_T("I"), _T("x")) << _T(")") << rptNewLine;
   }
   else
   {
      *pPara << Sub2(_T("e"), _T("psx")) << _T(" = eccentricity of the prestress force. Positive values are for ") << Sub2(_T("F"), _T("pe")) << _T(" to the left of the centroidal axis") << rptNewLine;
      *pPara << Sub2(_T("e"), _T("psy")) << _T(" = eccentricity of the prestress force. Positive values are for ") << Sub2(_T("F"), _T("pe")) << _T(" below the centroidal axis") << rptNewLine;
      *pPara << Sub2(_T("M"), _T("psx")) << _T(" = ") << Sub2(_T("F"), _T("pe")) << Sub2(_T("e"), _T("psy")) << rptNewLine;
      *pPara << Sub2(_T("M"), _T("psy")) << _T(" = ") << Sub2(_T("F"), _T("pe")) << Sub2(_T("e"), _T("psx")) << rptNewLine;
      *pPara << RPT_STRESS(_T("ps")) << _T("(x,y) = ")
         << _T("(") << Sub2(_T("M"), _T("psy")) << Sub2(_T("I"), _T("xx")) << _T("+") << Sub2(_T("M"), _T("psx")) << Sub2(_T("I"), _T("xy")) << _T(")(x)/(") << Sub2(_T("I"), _T("xx")) << Sub2(_T("I"), _T("yy")) << _T(" - ") << Super2(Sub2(_T("I"), _T("xy")), _T("2")) << _T(")")
         << _T(" - ")
         << _T("(") << Sub2(_T("M"), _T("psx")) << Sub2(_T("I"), _T("yy")) << _T("+") << Sub2(_T("M"), _T("psy")) << Sub2(_T("I"), _T("xy")) << _T(")(y)/(") << Sub2(_T("I"), _T("xx")) << Sub2(_T("I"), _T("yy")) << _T(" - ") << Super2(Sub2(_T("I"), _T("xy")), _T("2")) << _T(")")
         << _T(" - ")
         << Sub2(_T("F"), _T("pe")) << _T("/") << Sub2(_T("A"), _T("g")) << rptNewLine;
   }

   rptRcTable* pStressTable = rptStyleManager::CreateDefaultTable(bSimpleFormat ? 14 : 16, _T("Stress due to External Loads"));
   *pPara << pStressTable << rptNewLine;

   col = 0;
   pStressTable->SetNumberOfHeaderRows(2);
   pStressTable->SetRowSpan(0, col, 2);
   if (lpszLocColumnLabel)
   {
      (*pStressTable)(0, col++) << COLHDR(rptRcStringLiteral(lpszLocColumnLabel), rptLengthUnitTag, pDisplayUnits->SpanLength);
   }
   else
   {
      (*pStressTable)(0, col++) << COLHDR(_T("Dist from") << rptNewLine << _T("left end"), rptLengthUnitTag, pDisplayUnits->SpanLength);
   }

   pStressTable->SetRowSpan(0, col, 2);
   (*pStressTable)(0, col++) << COLHDR(Sub2(_T("M"), _T("girder")), rptMomentUnitTag, pDisplayUnits->Moment);

   nColSpan = (bSimpleFormat ? 2 : 4);
   pStressTable->SetColumnSpan(0, col, nColSpan);
   (*pStressTable)(0, col) << RPT_STRESS(_T("g"));
   if (bSimpleFormat)
   {
      (*pStressTable)(1, col++) << COLHDR(_T("Top"), rptStressUnitTag, pDisplayUnits->Stress);
      (*pStressTable)(1, col++) << COLHDR(_T("Bottom"), rptStressUnitTag, pDisplayUnits->Stress);
   }
   else
   {
      (*pStressTable)(1, col++) << COLHDR(_T("Top Left"), rptStressUnitTag, pDisplayUnits->Stress);
      (*pStressTable)(1, col++) << COLHDR(_T("Top Right"), rptStressUnitTag, pDisplayUnits->Stress);
      (*pStressTable)(1, col++) << COLHDR(_T("Bottom Left"), rptStressUnitTag, pDisplayUnits->Stress);
      (*pStressTable)(1, col++) << COLHDR(_T("Bottom Right"), rptStressUnitTag, pDisplayUnits->Stress);
   }

   pStressTable->SetRowSpan(0, col, 2);
   (*pStressTable)(0, col++) << COLHDR(Sub2(_T("M"), _T("wind")), rptMomentUnitTag, pDisplayUnits->Moment);

   pStressTable->SetColumnSpan(0, col, 4);
   (*pStressTable)(0, col) << RPT_STRESS(_T("w"));
   (*pStressTable)(1, col++) << COLHDR(_T("Top Left"), rptStressUnitTag, pDisplayUnits->Stress);
   (*pStressTable)(1, col++) << COLHDR(_T("Top Right"), rptStressUnitTag, pDisplayUnits->Stress);
   (*pStressTable)(1, col++) << COLHDR(_T("Bottom Left"), rptStressUnitTag, pDisplayUnits->Stress);
   (*pStressTable)(1, col++) << COLHDR(_T("Bottom Right"), rptStressUnitTag, pDisplayUnits->Stress);

   pStressTable->SetRowSpan(0, col, 2);
   (*pStressTable)(0, col++) << COLHDR(Sub2(_T("M"), _T("cf")), rptMomentUnitTag, pDisplayUnits->Moment);

   pStressTable->SetColumnSpan(0, col, 4);
   (*pStressTable)(0, col) << RPT_STRESS(_T("cf"));
   (*pStressTable)(1, col++) << COLHDR(_T("Top Left"), rptStressUnitTag, pDisplayUnits->Stress);
   (*pStressTable)(1, col++) << COLHDR(_T("Top Right"), rptStressUnitTag, pDisplayUnits->Stress);
   (*pStressTable)(1, col++) << COLHDR(_T("Bottom Left"), rptStressUnitTag, pDisplayUnits->Stress);
   (*pStressTable)(1, col++) << COLHDR(_T("Bottom Right"), rptStressUnitTag, pDisplayUnits->Stress);

   longLength.ShowUnitTag(false);
   shortLength.ShowUnitTag(false);
   force.ShowUnitTag(false);
   stress.ShowUnitTag(false);
   area.ShowUnitTag(false);

   row = pStressTable->GetNumberOfHeaderRows();
   for (const auto& sectionResult : pResults->vSectionResults)
   {
      col = 0;

      const stbIAnalysisPoint* pAnalysisPoint = pStabilityProblem->GetAnalysisPoint(sectionResult.AnalysisPointIndex);

      (*pStressTable)(row, col++) << rptRcStringLiteral(pAnalysisPoint->AsString(pDisplayUnits->SpanLength, offset, false));

      (*pStressTable)(row, col++) << moment.SetValue(sectionResult.Mg);

      if (bSimpleFormat)
      {
         ATLASSERT(IsEqual(sectionResult.fg[stbTypes::TopLeft], sectionResult.fg[stbTypes::TopRight]));
         ATLASSERT(IsEqual(sectionResult.fg[stbTypes::BottomLeft], sectionResult.fg[stbTypes::BottomRight]));
         (*pStressTable)(row, col++) << stress.SetValue(sectionResult.fg[stbTypes::TopLeft]);
         (*pStressTable)(row, col++) << stress.SetValue(sectionResult.fg[stbTypes::BottomLeft]);
      }
      else
      {
         (*pStressTable)(row, col++) << stress.SetValue(sectionResult.fg[stbTypes::TopLeft]);
         (*pStressTable)(row, col++) << stress.SetValue(sectionResult.fg[stbTypes::TopRight]);
         (*pStressTable)(row, col++) << stress.SetValue(sectionResult.fg[stbTypes::BottomLeft]);
         (*pStressTable)(row, col++) << stress.SetValue(sectionResult.fg[stbTypes::BottomRight]);
      }

      (*pStressTable)(row, col++) << moment.SetValue(sectionResult.Mw);

      (*pStressTable)(row, col++) << stress.SetValue(sectionResult.fw[stbTypes::TopLeft]);
      (*pStressTable)(row, col++) << stress.SetValue(sectionResult.fw[stbTypes::TopRight]);
      (*pStressTable)(row, col++) << stress.SetValue(sectionResult.fw[stbTypes::BottomLeft]);
      (*pStressTable)(row, col++) << stress.SetValue(sectionResult.fw[stbTypes::BottomRight]);

      (*pStressTable)(row, col++) << moment.SetValue(sectionResult.Mcf);

      (*pStressTable)(row, col++) << stress.SetValue(sectionResult.fcf[stbTypes::TopLeft]);
      (*pStressTable)(row, col++) << stress.SetValue(sectionResult.fcf[stbTypes::TopRight]);
      (*pStressTable)(row, col++) << stress.SetValue(sectionResult.fcf[stbTypes::BottomLeft]);
      (*pStressTable)(row, col++) << stress.SetValue(sectionResult.fcf[stbTypes::BottomRight]);

      row++;
   }

   *pPara << RPT_STRESS(_T("g")) << _T(" = ") << _T("stress due to girder self weight applied without tilt or impact") << rptNewLine;
   if (bSimpleFormat)
   {
      *pPara << _T("Top ") << RPT_STRESS(_T("g")) << _T(" = -") << Sub2(_T("M"), _T("girder")) << Sub2(_T("Y"), _T("top")) << _T("/") << Sub2(_T("I"), _T("xx")) << rptNewLine;
      *pPara << _T("Bottom ") << RPT_STRESS(_T("g")) << _T(" = ") << Sub2(_T("M"), _T("girder")) << _T("(") << Sub2(_T("H"), _T("g")) << _T(" - ") << Sub2(_T("Y"), _T("top")) << _T(")/") << Sub2(_T("I"), _T("xx")) << rptNewLine;
   }
   else
   {
      *pPara << RPT_STRESS(_T("g")) << _T("(x,y)") << _T(" = ")
         << Sub2(_T("M"), _T("girder")) << Sub2(_T("I"), _T("xy")) << _T("(x)/(") << Sub2(_T("I"), _T("xx")) << Sub2(_T("I"), _T("yy")) << _T(" - ") << Super2(Sub2(_T("I"), _T("xy")), _T("2")) << _T(")")
         << _T(" - ")
         << Sub2(_T("M"), _T("girder")) << Sub2(_T("I"), _T("yy")) << _T("(y)/(") << Sub2(_T("I"), _T("xx")) << Sub2(_T("I"), _T("yy")) << _T(" - ") << Super2(Sub2(_T("I"), _T("xy")), _T("2")) << _T(")") << rptNewLine;
   }

   *pPara << RPT_STRESS(_T("w")) << _T(" = ") << _T("stress due to wind toward the left") << rptNewLine;
   if (bSimpleFormat)
   {
      *pPara << _T("Top Left ") << RPT_STRESS(_T("w")) << _T(" = ") << Sub2(_T("M"), _T("wind")) << Sub2(_T("W"), _T("top")) << _T("/(2") << Sub2(_T("I"), _T("yy")) << _T(")") << rptNewLine;
      *pPara << _T("Top Right ") << RPT_STRESS(_T("w")) << _T(" = -") << Sub2(_T("M"), _T("wind")) << Sub2(_T("W"), _T("top")) << _T("/(2") << Sub2(_T("I"), _T("yy")) << _T(")") << rptNewLine;
      *pPara << _T("Bottom Left ") << RPT_STRESS(_T("w")) << _T(" = ") << Sub2(_T("M"), _T("wind")) << Sub2(_T("W"), _T("bot")) << _T("/(2") << Sub2(_T("I"), _T("yy")) << _T(")") << rptNewLine;
      *pPara << _T("Bottom Right ") << RPT_STRESS(_T("w")) << _T(" = -") << Sub2(_T("M"), _T("wind")) << Sub2(_T("W"), _T("bot")) << _T("/(2") << Sub2(_T("I"), _T("yy")) << _T(")") << rptNewLine;
   }
   else
   {
      *pPara << RPT_STRESS(_T("w")) << _T("(x,y)") << _T(" = ")
         << Sub2(_T("M"), _T("wind")) << Sub2(_T("I"), _T("xy")) << _T("(x)/(") << Sub2(_T("I"), _T("xx")) << Sub2(_T("I"), _T("yy")) << _T(" - ") << Super2(Sub2(_T("I"), _T("xy")), _T("2")) << _T(")")
         << _T(" - ")
         << Sub2(_T("M"), _T("wind")) << Sub2(_T("I"), _T("yy")) << _T("(y)/(") << Sub2(_T("I"), _T("xx")) << Sub2(_T("I"), _T("yy")) << _T(" - ") << Super2(Sub2(_T("I"), _T("xy")), _T("2")) << _T(")") << rptNewLine;
   }

   *pPara << RPT_STRESS(_T("cf")) << _T(" = ") << _T("stress due to centrifugal force toward the right") << rptNewLine;
   if (bSimpleFormat)
   {
      *pPara << _T("Top Left ") << RPT_STRESS(_T("cf")) << _T(" = -") << Sub2(_T("M"), _T("cf")) << Sub2(_T("W"), _T("top")) << _T("/(2") << Sub2(_T("I"), _T("yy")) << _T(")") << rptNewLine;
      *pPara << _T("Top Right ") << RPT_STRESS(_T("cf")) << _T(" = ") << Sub2(_T("M"), _T("cf")) << Sub2(_T("W"), _T("top")) << _T("/(2") << Sub2(_T("I"), _T("yy")) << _T(")") << rptNewLine;
      *pPara << _T("Bottom Left ") << RPT_STRESS(_T("cf")) << _T(" = -") << Sub2(_T("M"), _T("cf")) << Sub2(_T("W"), _T("bot")) << _T("/(2") << Sub2(_T("I"), _T("yy")) << _T(")") << rptNewLine;
      *pPara << _T("Bottom Right ") << RPT_STRESS(_T("cf")) << _T(" = ") << Sub2(_T("M"), _T("cf")) << Sub2(_T("W"), _T("bot")) << _T("/(2") << Sub2(_T("I"), _T("yy")) << _T(")") << rptNewLine;
   }
   else
   {
      *pPara << RPT_STRESS(_T("cf")) << _T("(x,y)") << _T(" = ")
         << Sub2(_T("M"), _T("cf")) << Sub2(_T("I"), _T("xy")) << _T("(x)/(") << Sub2(_T("I"), _T("xx")) << Sub2(_T("I"), _T("yy")) << _T(" - ") << Super2(Sub2(_T("I"), _T("xy")), _T("2")) << _T(")")
         << _T(" - ")
         << Sub2(_T("M"), _T("cf")) << Sub2(_T("I"), _T("yy")) << _T("(y)/(") << Sub2(_T("I"), _T("xx")) << Sub2(_T("I"), _T("yy")) << _T(" - ") << Super2(Sub2(_T("I"), _T("xy")), _T("2")) << _T(")") << rptNewLine;
   }

   std::array<LPCTSTR, 2> strSlope = { _T("Normal Crown Slope"),_T("Maximum Superelevation") };
   for (int s = 0; s < 2; s++)
   {
      stbTypes::HaulingSlope slope = (stbTypes::HaulingSlope)s;

      // redo impact labeling because now it is based on the analysis slope type
      bool bImpactForThisSlope = (impactUsage == stbTypes::Both || (impactUsage == stbTypes::NormalCrown && slope == stbTypes::CrownSlope) || (impactUsage == stbTypes::MaxSuper && slope == stbTypes::Superelevation) ? true : false);

      std::array<LPCTSTR, 3> strImpact;
      std::array<stbTypes::ImpactDirection, 3> impactDir;
      std::array<Float64, 3> impactFactor = { -1,-1,-1 };
      std::array<IndexType, 3> impactIndex = { INVALID_INDEX,INVALID_INDEX < INVALID_INDEX };

      Float64 ImpactUp, ImpactDown;
      pStabilityProblem->GetImpact(&ImpactUp, &ImpactDown);
      IndexType nImpactCases = 0;

      strImpact[nImpactCases] = _T("No impact");
      impactDir[nImpactCases] = stbTypes::NoImpact;
      impactFactor[nImpactCases] = 1.0;
      impactIndex[stbTypes::NoImpact] = nImpactCases;

      if (!IsZero(ImpactUp) && bImpactForThisSlope)
      {
         nImpactCases++;
         strImpact[nImpactCases] = _T("Impact Up");
         impactDir[nImpactCases] = stbTypes::ImpactUp;
         impactFactor[nImpactCases] = 1.0 - ImpactUp;
         impactIndex[stbTypes::ImpactUp] = nImpactCases;
      }

      if (!IsZero(ImpactDown) && bImpactForThisSlope)
      {
         nImpactCases++;
         strImpact[nImpactCases] = _T("Impact Down");
         impactDir[nImpactCases] = stbTypes::ImpactDown;
         impactFactor[nImpactCases] = 1.0 + ImpactDown;
         impactIndex[stbTypes::ImpactDown] = nImpactCases;
      }

      bool bLabelImpact = (0 < nImpactCases ? true : false);

      for (IndexType impactCase = 0; impactCase <= nImpactCases; impactCase++)
      {
         stbTypes::ImpactDirection impact = (stbTypes::ImpactDirection)impactCase;
         for (IndexType windCase = 0; windCase <= nWindCases; windCase++)
         {
            stbTypes::WindDirection wind = (stbTypes::WindDirection)windCase;

            CString strTitle;

            if (bLabelImpact && !bLabelWind)
            {
               // more than one impact case but no wind
               strTitle.Format(_T("Analysis at %s - %s"), strSlope[slope], strImpact[impactCase]);
            }
            else if (!bLabelImpact && bLabelWind)
            {
               // only one impact case and wind cases
               strTitle.Format(_T("Analysis at %s - Wind towards the %s (%s)"), strSlope[slope], strWindDir[wind], strWindDirEx[wind]);
            }
            else if (bLabelImpact && bLabelWind)
            {
               // more than one impact case and wind cases
               strTitle.Format(_T("Analysis at %s - %s, Wind towards the %s (%s)"), strSlope[slope], strImpact[impactCase], strWindDir[wind], strWindDirEx[wind]);
            }
            else
            {
               strTitle.Format(_T("Analysis at %s"), strSlope[slope]);
            }

            pPara = new rptParagraph(rptStyleManager::GetHeadingStyle());
            *pChapter << pPara;
            pPara->SetName(strTitle);
            *pPara << strTitle << rptNewLine;

            pPara = new rptParagraph;
            *pChapter << pPara;

            *pPara << _T("IM = ") << scalar.SetValue(impactFactor[impactCase]) << rptNewLine;
            *pPara << rptNewLine;


            std::_tstring strWindSign(wind == stbTypes::Left ? _T("+") : _T("-"));
            std::_tstring strOppWindSign(wind == stbTypes::Left ? _T("-") : _T("+"));
            std::_tstring strCFSign(pStabilityProblem->GetCentrifugalForceType() == stbTypes::Favorable ? _T("-") : _T("+"));
            std::_tstring strOppCFSign(pStabilityProblem->GetCentrifugalForceType() == stbTypes::Favorable ? _T("+") : _T("-"));

            // Overturning Moment
            *pPara << _T("Overturning Moment") << rptNewLine;
            Float64 Mot = (wind == stbTypes::Left ? 1 : -1)*pResults->MotWind;
            *pPara << M_OT << _T(" = ");
            if (slope == stbTypes::Superelevation)
            {
               Mot += (pStabilityProblem->GetCentrifugalForceType() == stbTypes::Favorable ? -1 : 1)*pResults->MotCF;
               if (wind == stbTypes::Right)
               {
                  *pPara << _T("-");
               }
               *pPara << Sub2(_T("M"), _T("otwind")) << _T(" ") << strCFSign.c_str() << _T(" ") << Sub2(_T("M"), _T("otcf"));
            }
            else
            {
               if (wind == stbTypes::Right)
               {
                  *pPara << _T("-");
               }
               *pPara << Sub2(_T("M"), _T("otwind"));
            }
            *pPara << _T(" = ") << ot_moment.SetValue(Mot) << rptNewLine;

            *pPara << rptNewLine;

            // Equilibrium Tilt Angle
            *pPara << _T("Equilibrium Tilt Angle") << rptNewLine;

            *pPara << THETA_EQ << _T(" = ((IM)") << Sub2(_T("W"), _T("g")) << _T("(") << EI << _T(" ") << strWindSign.c_str() << _T(" ") << Z_WIND;
            if (slope == stbTypes::Superelevation)
            {
               *pPara << _T(" ") << strCFSign.c_str() << _T(" ") << Z_CF;
            }
            *pPara << _T(")") << _T(" + ") << M_OT << _T(" + ") << K_THETA << symbol(alpha) << _T(")");
            *pPara << _T(" / [") << K_THETA << _T(" - ") << Sub2(_T("(IM)W"), _T("g")) << _T("(") << YR << _T(" + (IM)") << ZO << _T(")] = ");
            *pPara << tiltAngle.SetValue(pResults->ThetaEq[slope][impactDir[impactCase]][wind]) << rptNewLine;
            *pPara << _T("Assumed direction of tilt is ") << strTiltRotation[pResults->AssumedTiltDirection] << _T(" (top of girder tilt towards the ") << strTiltDirection[pResults->AssumedTiltDirection] << _T(").") << rptNewLine;

            if (!pResults->bRotationalStability[slope][impactDir[impactCase]][wind])
            {
               *pPara << color(Red) << _T("WARNING: Rotational instability due to excessive rotation.") << color(Black) << rptNewLine;
               continue;
            }

            if (pResults->ThetaEq[slope][impactDir[impactCase]][wind] < 0)
            {
               *pPara << _T("NOTE: lateral loading is sufficient to cause the girder to reverse rotational direction.") << rptNewLine;
            }

            *pPara << rptNewLine;

            rptRcTable* pTotalStressTable = rptStyleManager::CreateDefaultTable(13, _T("Stresses"));
            (*pPara) << pTotalStressTable << rptNewLine;
            (*pPara) << RPT_STRESS(_T("direct")) << _T(" = ") << RPT_STRESS(_T("ps")) << _T(" + (IM)") << RPT_STRESS(_T("g")) << rptNewLine;
            (*pPara) << RPT_STRESS(_T("tilt")) << _T(" = stress induced by girder rotation") << rptNewLine;
            (*pPara) << _T("Top Left ") << RPT_STRESS(_T("tilt")) << _T(" = (IM)") << Sub2(_T("M"), _T("girder")) << THETA_EQ << Sub2(_T("W"), _T("top")) << _T("/(2") << Sub2(_T("I"), _T("yy")) << _T(")") << rptNewLine;
            (*pPara) << _T("Top Right ") << RPT_STRESS(_T("tilt")) << _T(" = -(IM)") << Sub2(_T("M"), _T("girder")) << THETA_EQ << Sub2(_T("W"), _T("top")) << _T("/(2") << Sub2(_T("I"), _T("yy")) << _T(")") << rptNewLine;
            (*pPara) << _T("Bottom Left ") << RPT_STRESS(_T("tilt")) << _T(" = (IM)") << Sub2(_T("M"), _T("girder")) << THETA_EQ << Sub2(_T("W"), _T("bot")) << _T("/(2") << Sub2(_T("I"), _T("yy")) << _T(")") << rptNewLine;
            (*pPara) << _T("Bottom Right ") << RPT_STRESS(_T("tilt")) << _T(" = -(IM)") << Sub2(_T("M"), _T("girder")) << THETA_EQ << Sub2(_T("W"), _T("bot")) << _T("/(2") << Sub2(_T("I"), _T("yy")) << _T(")") << rptNewLine;
            (*pPara) << RPT_STRESS(_T("total")) << _T(" = ") << RPT_STRESS(_T("direct")) << _T(" + ") << RPT_STRESS(_T("tilt")) << _T(" ") << strWindSign.c_str() << _T(" ") << RPT_STRESS(_T("w"));
            if (slope == stbTypes::Superelevation)
            {
               (*pPara) << _T(" ") << strOppCFSign.c_str() << _T(" ") << RPT_STRESS(_T("cf"));
            }
            (*pPara) << rptNewLine;

            col = 0;
            pTotalStressTable->SetNumberOfHeaderRows(2);
            pTotalStressTable->SetRowSpan(0, col, 2);
            if (lpszLocColumnLabel)
            {
               (*pTotalStressTable)(0, col++) << COLHDR(rptRcStringLiteral(lpszLocColumnLabel), rptLengthUnitTag, pDisplayUnits->SpanLength);
            }
            else
            {
               (*pTotalStressTable)(0, col++) << COLHDR(_T("Dist from") << rptNewLine << _T("left end"), rptLengthUnitTag, pDisplayUnits->SpanLength);
            }

            pTotalStressTable->SetColumnSpan(0, col, 4);
            (*pTotalStressTable)(0, col) << RPT_STRESS(_T("direct"));
            (*pTotalStressTable)(1, col++) << COLHDR(_T("Top Left"), rptStressUnitTag, pDisplayUnits->Stress);
            (*pTotalStressTable)(1, col++) << COLHDR(_T("Top Right"), rptStressUnitTag, pDisplayUnits->Stress);
            (*pTotalStressTable)(1, col++) << COLHDR(_T("Bottom Left"), rptStressUnitTag, pDisplayUnits->Stress);
            (*pTotalStressTable)(1, col++) << COLHDR(_T("Bottom Right"), rptStressUnitTag, pDisplayUnits->Stress);

            pTotalStressTable->SetColumnSpan(0, col, 4);
            (*pTotalStressTable)(0, col) << RPT_STRESS(_T("tilt"));
            (*pTotalStressTable)(1, col++) << COLHDR(_T("Top Left"), rptStressUnitTag, pDisplayUnits->Stress);
            (*pTotalStressTable)(1, col++) << COLHDR(_T("Top Right"), rptStressUnitTag, pDisplayUnits->Stress);
            (*pTotalStressTable)(1, col++) << COLHDR(_T("Bottom Left"), rptStressUnitTag, pDisplayUnits->Stress);
            (*pTotalStressTable)(1, col++) << COLHDR(_T("Bottom Right"), rptStressUnitTag, pDisplayUnits->Stress);

            pTotalStressTable->SetColumnSpan(0, col, 4);
            (*pTotalStressTable)(0, col) << RPT_STRESS(_T("total"));
            (*pTotalStressTable)(1, col++) << COLHDR(_T("Top Left"), rptStressUnitTag, pDisplayUnits->Stress);
            (*pTotalStressTable)(1, col++) << COLHDR(_T("Top Right"), rptStressUnitTag, pDisplayUnits->Stress);
            (*pTotalStressTable)(1, col++) << COLHDR(_T("Bottom Left"), rptStressUnitTag, pDisplayUnits->Stress);
            (*pTotalStressTable)(1, col++) << COLHDR(_T("Bottom Right"), rptStressUnitTag, pDisplayUnits->Stress);

            ///////////////////////////////////////////////////////////////////////
            // Cracking
            ///////////////////////////////////////////////////////////////////////

            pPara = new rptParagraph(rptStyleManager::GetSubheadingStyle());
            *pChapter << pPara;
            *pPara << _T("Factor of Safety against Cracking") << rptNewLine;
            pPara = new rptParagraph;
            *pChapter << pPara;

            (*pPara) << M_CR << _T(" = Cracking Moment") << rptNewLine;
            if (bSimpleFormat)
            {
               std::_tstring strLeftSign(pResults->ThetaEq[impactDir[impactCase]][wind] < 0 ? _T("") : _T("-"));
               std::_tstring strRightSign(pResults->ThetaEq[impactDir[impactCase]][wind] < 0 ? _T("-") : _T(""));
               (*pPara) << _T("Top Left ") << Sub2(_T("M"), _T("cr")) << _T(" = ") << strLeftSign << _T("(") << RPT_STRESS(_T("r")) << _T(" - ") << RPT_STRESS(_T("direct")) << _T(" ") << strOppWindSign.c_str() << _T(" ") << RPT_STRESS(_T("w"));
               if (slope == stbTypes::Superelevation)
               {
                  (*pPara) << _T(" ") << strOppCFSign.c_str() << _T(" ") << RPT_STRESS(_T("cf"));
               }
               (*pPara) << _T(")2") << Sub2(_T("I"), _T("yy")) << _T("/") << Sub2(_T("W"), _T("top")) << rptNewLine;

               (*pPara) << _T("Top Right ") << Sub2(_T("M"), _T("cr")) << _T(" = ") << strRightSign << _T("(") << RPT_STRESS(_T("r")) << _T(" - ") << RPT_STRESS(_T("direct")) << _T(" ") << strOppWindSign.c_str() << _T(" ") << RPT_STRESS(_T("w"));
               if (slope == stbTypes::Superelevation)
               {
                  (*pPara) << _T(" ") << strOppCFSign.c_str() << _T(" ") << RPT_STRESS(_T("cf"));
               }
               (*pPara) << _T(")2") << Sub2(_T("I"), _T("yy")) << _T("/") << Sub2(_T("W"), _T("top")) << rptNewLine;

               (*pPara) << _T("Bottom Left ") << Sub2(_T("M"), _T("cr")) << _T(" = ") << strLeftSign << _T("(") << RPT_STRESS(_T("r")) << _T(" - ") << RPT_STRESS(_T("direct")) << _T(" ") << strOppWindSign.c_str() << _T(" ") << RPT_STRESS(_T("w"));
               if (slope == stbTypes::Superelevation)
               {
                  (*pPara) << _T(" ") << strOppCFSign.c_str() << _T(" ") << RPT_STRESS(_T("cf"));
               }
               (*pPara) << _T(")2") << Sub2(_T("I"), _T("yy")) << _T("/") << Sub2(_T("W"), _T("bot")) << rptNewLine;

               (*pPara) << _T("Bottom Right ") << Sub2(_T("M"), _T("cr")) << _T(" = ") << strRightSign << _T("(") << RPT_STRESS(_T("r")) << _T(" - ") << RPT_STRESS(_T("direct")) << _T(" ") << strOppWindSign.c_str() << _T(" ") << RPT_STRESS(_T("w"));
               if (slope == stbTypes::Superelevation)
               {
                  (*pPara) << _T(" ") << strOppCFSign.c_str() << _T(" ") << RPT_STRESS(_T("cf"));
               }
               (*pPara) << _T(")2") << Sub2(_T("I"), _T("yy")) << _T("/") << Sub2(_T("W"), _T("bot")) << rptNewLine;
            }
            else
            {
               (*pPara) << M_CR << _T(" = ") << _T("(") << RPT_STRESS(_T("r")) << _T(" - ") << RPT_STRESS(_T("direct")) << _T(" ") << strOppWindSign.c_str() << _T(" ") << RPT_STRESS(_T("w"));
               if (slope == stbTypes::Superelevation)
               {
                  (*pPara) << _T(" ") << strOppCFSign.c_str() << _T(" ") << RPT_STRESS(_T("cf"));
               }
               (*pPara) << _T(")")
                  << _T("(") << Sub2(_T("I"), _T("xx")) << Sub2(_T("I"), _T("yy")) << _T(" - ") << Super2(Sub2(_T("I"), _T("xy")), _T("2")) << _T(")")
                  << _T("(") << Sub2(_T("I"), _T("xx")) << _T("(x)") << _T(" - ") << Sub2(_T("I"), _T("xy")) << _T("(y)") << _T(")") << rptNewLine;
            }
            (*pPara) << _T("Cracked Flange, indicates the flange that is first to crack") << rptNewLine;
            (*pPara) << THETA_CRACK << _T(" = tilt angle at cracking") << rptNewLine;
            (*pPara) << THETA_CRACK << _T(" = ") << M_CR << _T("/[(IM)") << Sub2(_T("M"), _T("girder")) << _T("]") << rptNewLine;
            (*pPara) << _T("-0.4 radian") << _T(" ") << symbol(LTE) << _T(" ") << THETA_CRACK << _T(" ") << symbol(LTE) << _T(" ") << _T("0.4 radian") << rptNewLine;
            *pPara << _T("Assumed direction of tilt is ") << strTiltRotation[pResults->AssumedTiltDirection] << _T(" (top of girder tilt towards the ") << strTiltDirection[pResults->AssumedTiltDirection] << _T(").") << rptNewLine;

            (*pPara) << FS_CR << _T(" = Factor of Safety against Cracking") << rptNewLine;
            (*pPara) << FS_CR << _T(" = [") << K_THETA << _T("(") << THETA_CRACK << _T(" - ") << symbol(alpha) << _T(")]");
            (*pPara) << _T(" / {");
            (*pPara) << Sub2(_T("(IM)W"), _T("g")) << _T("[(") << YR << _T(" + (IM)") << ZO << _T(")") << THETA_CRACK << _T(" + ") << EI << _T(" + ");
            if (slope == stbTypes::Superelevation)
            {
               (*pPara) << _T("(") << Z_WIND << _T(" ") << strCFSign.c_str() << _T(" ") << Z_CF << _T(")");
            }
            else
            {
               (*pPara) << Z_WIND;
            }
            (*pPara) << _T("]") << _T(" + ") << M_OT << _T("}") << rptNewLine;

#if defined SHOW_FULL_CRACKING_TABLE
            rptRcTable* pFullCrackingTable = rptStyleManager::CreateDefaultTable(13, _T("Factor of Safety against Cracking"));
            (*pPara) << pFullCrackingTable << rptNewLine;
#endif
            rptRcTable* pCrackingTable = rptStyleManager::CreateDefaultTable(5, _T("Factor of Safety against Cracking Summary"));
            (*pPara) << pCrackingTable << rptNewLine;

#if defined SHOW_FULL_CRACKING_TABLE
            col = 0;
            pFullCrackingTable->SetNumberOfHeaderRows(2);
            pFullCrackingTable->SetRowSpan(0, col, 2);
            if (lpszLocColumnLabel)
            {
               (*pFullCrackingTable)(0, col++) << COLHDR(rptRcStringLiteral(lpszLocColumnLabel), rptLengthUnitTag, pDisplayUnits->SpanLength);
            }
            else
            {
               (*pFullCrackingTable)(0, col++) << COLHDR(_T("Dist from") << rptNewLine << _T("left end"), rptLengthUnitTag, pDisplayUnits->SpanLength);
            }

            pFullCrackingTable->SetColumnSpan(0, col, 3);
            (*pFullCrackingTable)(0, col) << _T("Top Left");
            (*pFullCrackingTable)(1, col++) << COLHDR(M_CR, rptMomentUnitTag, pDisplayUnits->Moment);
            (*pFullCrackingTable)(1, col++) << COLHDR(THETA_CRACK, rptAngleUnitTag, pDisplayUnits->RadAngle);
            (*pFullCrackingTable)(1, col++) << FS_CR;

            pFullCrackingTable->SetColumnSpan(0, col, 3);
            (*pFullCrackingTable)(0, col) << _T("Top Right");
            (*pFullCrackingTable)(1, col++) << COLHDR(M_CR, rptMomentUnitTag, pDisplayUnits->Moment);
            (*pFullCrackingTable)(1, col++) << COLHDR(THETA_CRACK, rptAngleUnitTag, pDisplayUnits->RadAngle);
            (*pFullCrackingTable)(1, col++) << FS_CR;

            pFullCrackingTable->SetColumnSpan(0, col, 3);
            (*pFullCrackingTable)(0, col) << _T("Bottom Left");
            (*pFullCrackingTable)(1, col++) << COLHDR(M_CR, rptMomentUnitTag, pDisplayUnits->Moment);
            (*pFullCrackingTable)(1, col++) << COLHDR(THETA_CRACK, rptAngleUnitTag, pDisplayUnits->RadAngle);
            (*pFullCrackingTable)(1, col++) << FS_CR;

            pFullCrackingTable->SetColumnSpan(0, col, 3);
            (*pFullCrackingTable)(0, col) << _T("Bottom Right");
            (*pFullCrackingTable)(1, col++) << COLHDR(M_CR, rptMomentUnitTag, pDisplayUnits->Moment);
            (*pFullCrackingTable)(1, col++) << COLHDR(THETA_CRACK, rptAngleUnitTag, pDisplayUnits->RadAngle);
            (*pFullCrackingTable)(1, col++) << FS_CR;
#endif

            col = 0;
            if (lpszLocColumnLabel)
            {
               (*pCrackingTable)(0, col++) << COLHDR(rptRcStringLiteral(lpszLocColumnLabel), rptLengthUnitTag, pDisplayUnits->SpanLength);
            }
            else
            {
               (*pCrackingTable)(0, col++) << COLHDR(_T("Dist from") << rptNewLine << _T("left end"), rptLengthUnitTag, pDisplayUnits->SpanLength);
            }
            (*pCrackingTable)(0, col++) << COLHDR(M_CR, rptMomentUnitTag, pDisplayUnits->Moment);
            (*pCrackingTable)(0, col++) << _T("Cracked Flange");
            (*pCrackingTable)(0, col++) << COLHDR(THETA_CRACK, rptAngleUnitTag, pDisplayUnits->RadAngle);
            (*pCrackingTable)(0, col++) << FS_CR;


#if !defined REBAR_FOR_DIRECT_TENSION
            rptRcTable* pRebarTable = nullptr;
            if (segment)
            {
               std::_tstring strTitle(_T("Bonded reinforcement requirements [") + std::_tstring(LrfdCw8th(_T("C5.9.4.1.2"), _T("C5.9.2.3.1b"))) + std::_tstring(_T("]")));
               ColumnIndexType nColumns = (bSimpleFormat ? 8 : 19);
               if (bReportTensileForceDetails)
               {
                  nColumns++;
               }
               pRebarTable = rptStyleManager::CreateDefaultTable(nColumns, strTitle);

               col = 0;
               if (lpszLocColumnLabel)
               {
                  (*pRebarTable)(0, col++) << COLHDR(rptRcStringLiteral(lpszLocColumnLabel), rptLengthUnitTag, pDisplayUnits->SpanLength);
               }
               else
               {
                  (*pRebarTable)(0, col++) << COLHDR(_T("Dist from") << rptNewLine << _T("left end"), rptLengthUnitTag, pDisplayUnits->SpanLength);
               }
               (*pRebarTable)(0, col++) << COLHDR(Sub2(_T("Y"), _T("na")), rptLengthUnitTag, pDisplayUnits->ComponentDim);

               if (bSimpleFormat)
               {
                  (*pRebarTable)(0, col++) << COLHDR(RPT_STRESS(_T("t")), rptStressUnitTag, pDisplayUnits->Stress);
                  (*pRebarTable)(0, col++) << COLHDR(RPT_STRESS(_T("b")), rptStressUnitTag, pDisplayUnits->Stress);
               }
               else
               {
                  pRebarTable->SetNumberOfHeaderRows(2);
                  col = 0;

                  // location
                  pRebarTable->SetRowSpan(0, col++, 2);

                  // Yna
                  pRebarTable->SetRowSpan(0, col++, 2);

                  pRebarTable->SetRowSpan(0, col, 2);
                  (*pRebarTable)(0, col++) << _T("Slope NA");

                  pRebarTable->SetColumnSpan(0, col, 3);
                  (*pRebarTable)(0, col) << _T("Top Left");
                  (*pRebarTable)(1, col++) << COLHDR(Sub2(_T("x"), _T("tl")), rptLengthUnitTag, pDisplayUnits->ComponentDim);
                  (*pRebarTable)(1, col++) << COLHDR(Sub2(_T("y"), _T("tl")), rptLengthUnitTag, pDisplayUnits->ComponentDim);
                  (*pRebarTable)(1, col++) << COLHDR(RPT_STRESS(_T("tl")), rptStressUnitTag, pDisplayUnits->Stress);

                  pRebarTable->SetColumnSpan(0, col, 3);
                  (*pRebarTable)(0, col) << _T("Top Right");
                  (*pRebarTable)(1, col++) << COLHDR(Sub2(_T("x"), _T("tr")), rptLengthUnitTag, pDisplayUnits->ComponentDim);
                  (*pRebarTable)(1, col++) << COLHDR(Sub2(_T("y"), _T("tr")), rptLengthUnitTag, pDisplayUnits->ComponentDim);
                  (*pRebarTable)(1, col++) << COLHDR(RPT_STRESS(_T("tr")), rptStressUnitTag, pDisplayUnits->Stress);

                  pRebarTable->SetColumnSpan(0, col, 3);
                  (*pRebarTable)(0, col) << _T("Bottom Left");
                  (*pRebarTable)(1, col++) << COLHDR(Sub2(_T("x"), _T("bl")), rptLengthUnitTag, pDisplayUnits->ComponentDim);
                  (*pRebarTable)(1, col++) << COLHDR(Sub2(_T("y"), _T("bl")), rptLengthUnitTag, pDisplayUnits->ComponentDim);
                  (*pRebarTable)(1, col++) << COLHDR(RPT_STRESS(_T("bl")), rptStressUnitTag, pDisplayUnits->Stress);

                  pRebarTable->SetColumnSpan(0, col, 3);
                  (*pRebarTable)(0, col) << _T("Bottom Right");
                  (*pRebarTable)(1, col++) << COLHDR(Sub2(_T("x"), _T("br")), rptLengthUnitTag, pDisplayUnits->ComponentDim);
                  (*pRebarTable)(1, col++) << COLHDR(Sub2(_T("y"), _T("br")), rptLengthUnitTag, pDisplayUnits->ComponentDim);
                  (*pRebarTable)(1, col++) << COLHDR(RPT_STRESS(_T("br")), rptStressUnitTag, pDisplayUnits->Stress);

                  ColumnIndexType colOffset = 0;
                  if (bReportTensileForceDetails)
                  {
                     pRebarTable->SetRowSpan(0, col + colOffset, 2); colOffset++; // Tension Force Details
                  }
                  pRebarTable->SetRowSpan(0, col + colOffset, 2); colOffset++; // At
                  pRebarTable->SetRowSpan(0, col + colOffset, 2); colOffset++; // T
                  pRebarTable->SetRowSpan(0, col + colOffset, 2); colOffset++; // As Provided
                  pRebarTable->SetRowSpan(0, col + colOffset, 2); colOffset++; // As Required
               }

               if (bReportTensileForceDetails)
               {
                  (*pRebarTable)(0, col++) << _T("Tension Force Details");
               }

               (*pRebarTable)(0, col++) << COLHDR(Sub2(_T("A"), _T("t")), rptAreaUnitTag, pDisplayUnits->Area);
               (*pRebarTable)(0, col++) << COLHDR(_T("T"), rptForceUnitTag, pDisplayUnits->GeneralForce);
               (*pRebarTable)(0, col++) << COLHDR(Sub2(_T("A"), _T("s")) << rptNewLine << _T("Provided") << Super(_T("*")), rptAreaUnitTag, pDisplayUnits->Area);
               (*pRebarTable)(0, col++) << COLHDR(Sub2(_T("A"), _T("s")) << rptNewLine << _T("Required") << Super(_T("**")), rptAreaUnitTag, pDisplayUnits->Area);
            }
#endif


            RowIndexType srow = pTotalStressTable->GetNumberOfHeaderRows();
#if defined SHOW_FULL_CRACKING_TABLE
            RowIndexType fcrow = pFullCrackingTable->GetNumberOfHeaderRows();
#endif
            RowIndexType crow = pCrackingTable->GetNumberOfHeaderRows();

#if !defined REBAR_FOR_DIRECT_TENSION
            RowIndexType rrow = (pRebarTable ? pRebarTable->GetNumberOfHeaderRows() : 0);
#endif 

            for (const auto& sectionResult : pResults->vSectionResults)
            {
               col = 0;

               const stbIAnalysisPoint* pAnalysisPoint = pStabilityProblem->GetAnalysisPoint(sectionResult.AnalysisPointIndex);
               (*pTotalStressTable)(srow, col++) << rptRcStringLiteral(pAnalysisPoint->AsString(pDisplayUnits->SpanLength, offset, false));

               (*pTotalStressTable)(srow, col++) << stress.SetValue(sectionResult.fDirect[slope][impactDir[impactCase]][stbTypes::TopLeft]);
               (*pTotalStressTable)(srow, col++) << stress.SetValue(sectionResult.fDirect[slope][impactDir[impactCase]][stbTypes::TopRight]);
               (*pTotalStressTable)(srow, col++) << stress.SetValue(sectionResult.fDirect[slope][impactDir[impactCase]][stbTypes::BottomLeft]);
               (*pTotalStressTable)(srow, col++) << stress.SetValue(sectionResult.fDirect[slope][impactDir[impactCase]][stbTypes::BottomRight]);

               (*pTotalStressTable)(srow, col++) << stress.SetValue(sectionResult.fTilt[slope][impactDir[impactCase]][wind][stbTypes::TopLeft]);
               (*pTotalStressTable)(srow, col++) << stress.SetValue(sectionResult.fTilt[slope][impactDir[impactCase]][wind][stbTypes::TopRight]);
               (*pTotalStressTable)(srow, col++) << stress.SetValue(sectionResult.fTilt[slope][impactDir[impactCase]][wind][stbTypes::BottomLeft]);
               (*pTotalStressTable)(srow, col++) << stress.SetValue(sectionResult.fTilt[slope][impactDir[impactCase]][wind][stbTypes::BottomRight]);

               (*pTotalStressTable)(srow, col++) << stress.SetValue(sectionResult.f[slope][impactDir[impactCase]][wind][stbTypes::TopLeft]);
               (*pTotalStressTable)(srow, col++) << stress.SetValue(sectionResult.f[slope][impactDir[impactCase]][wind][stbTypes::TopRight]);
               (*pTotalStressTable)(srow, col++) << stress.SetValue(sectionResult.f[slope][impactDir[impactCase]][wind][stbTypes::BottomLeft]);
               (*pTotalStressTable)(srow, col++) << stress.SetValue(sectionResult.f[slope][impactDir[impactCase]][wind][stbTypes::BottomRight]);

               srow++;

#if defined SHOW_FULL_CRACKING_TABLE
               col = 0;
               (*pFullCrackingTable)(fcrow, col++) << rptRcStringLiteral(pAnalysisPoint->AsString(pDisplayUnits->SpanLength, offset, false));
               for (int c = 0; c < 4; c++)
               {
                  stbTypes::Corner corner = (stbTypes::Corner)c;
                  (*pFullCrackingTable)(fcrow, col++) << moment.SetValue(sectionResult.Mcr[slope][impactDir[impactCase]][wind][corner]);
                  (*pFullCrackingTable)(fcrow, col++) << crackAngle.SetValue(sectionResult.ThetaCrack[slope][impactDir[impactCase]][wind][corner]);
                  if (sectionResult.FScr[slope][impactDir[impactCase]][wind][corner] == Float64_Max)
                  {
                     (*pFullCrackingTable)(fcrow, col++) << symbol(infinity);
                  }
                  else
                  {
                     (*pFullCrackingTable)(fcrow, col++) << scalar.SetValue(sectionResult.FScr[slope][impactDir[impactCase]][wind][corner]);
                  }
               }

               fcrow++;
#endif

               col = 0;
               (*pCrackingTable)(crow, col++) << rptRcStringLiteral(pAnalysisPoint->AsString(pDisplayUnits->SpanLength, offset, false));
               stbTypes::Corner corner = (stbTypes::Corner)MinIndex(sectionResult.FScr[slope][impactDir[impactCase]][wind][stbTypes::TopLeft],
                  sectionResult.FScr[slope][impactDir[impactCase]][wind][stbTypes::TopRight],
                  sectionResult.FScr[slope][impactDir[impactCase]][wind][stbTypes::BottomLeft],
                  sectionResult.FScr[slope][impactDir[impactCase]][wind][stbTypes::BottomRight]);
               (*pCrackingTable)(crow, col++) << moment.SetValue(sectionResult.Mcr[slope][impactDir[impactCase]][wind][corner]);
               (*pCrackingTable)(crow, col++) << strFlange[corner];
               (*pCrackingTable)(crow, col++) << crackAngle.SetValue(sectionResult.ThetaCrack[slope][impactDir[impactCase]][wind][corner]);
               if (sectionResult.FScr[slope][impactDir[impactCase]][wind][corner] == Float64_Max)
               {
                  (*pCrackingTable)(crow, col++) << symbol(infinity);
               }
               else
               {
                  (*pCrackingTable)(crow, col++) << scalar.SetValue(sectionResult.FScr[slope][impactDir[impactCase]][wind][corner]);
               }

               crow++;

#if !defined REBAR_FOR_DIRECT_TENSION
               if (segment)
               {
                  col = 0;
                  (*pRebarTable)(rrow, col++) << rptRcStringLiteral(pAnalysisPoint->AsString(pDisplayUnits->SpanLength, offset, false));
                  (*pRebarTable)(rrow, col++) << shortLength.SetValue(sectionResult.altTensionRequirements[slope][impactDir[impactCase]][wind].Yna);
                  if (bSimpleFormat)
                  {
                     (*pRebarTable)(rrow, col++) << stress.SetValue(sectionResult.altTensionRequirements[slope][impactDir[impactCase]][wind].pntTopLeft.Z());
                     (*pRebarTable)(rrow, col++) << stress.SetValue(sectionResult.altTensionRequirements[slope][impactDir[impactCase]][wind].pntBottomLeft.Z());
                  }
                  else
                  {
                     (*pRebarTable)(rrow, col++) << scalar.SetValue(sectionResult.altTensionRequirements[slope][impactDir[impactCase]][wind].NAslope);

                     (*pRebarTable)(rrow, col++) << shortLength.SetValue(sectionResult.altTensionRequirements[slope][impactDir[impactCase]][wind].pntTopLeft.X());
                     (*pRebarTable)(rrow, col++) << shortLength.SetValue(sectionResult.altTensionRequirements[slope][impactDir[impactCase]][wind].pntTopLeft.Y());
                     (*pRebarTable)(rrow, col++) << stress.SetValue(sectionResult.altTensionRequirements[slope][impactDir[impactCase]][wind].pntTopLeft.Z());

                     (*pRebarTable)(rrow, col++) << shortLength.SetValue(sectionResult.altTensionRequirements[slope][impactDir[impactCase]][wind].pntTopRight.X());
                     (*pRebarTable)(rrow, col++) << shortLength.SetValue(sectionResult.altTensionRequirements[slope][impactDir[impactCase]][wind].pntTopRight.Y());
                     (*pRebarTable)(rrow, col++) << stress.SetValue(sectionResult.altTensionRequirements[slope][impactDir[impactCase]][wind].pntTopRight.Z());

                     (*pRebarTable)(rrow, col++) << shortLength.SetValue(sectionResult.altTensionRequirements[slope][impactDir[impactCase]][wind].pntBottomLeft.X());
                     (*pRebarTable)(rrow, col++) << shortLength.SetValue(sectionResult.altTensionRequirements[slope][impactDir[impactCase]][wind].pntBottomLeft.Y());
                     (*pRebarTable)(rrow, col++) << stress.SetValue(sectionResult.altTensionRequirements[slope][impactDir[impactCase]][wind].pntBottomLeft.Z());

                     (*pRebarTable)(rrow, col++) << shortLength.SetValue(sectionResult.altTensionRequirements[slope][impactDir[impactCase]][wind].pntBottomRight.X());
                     (*pRebarTable)(rrow, col++) << shortLength.SetValue(sectionResult.altTensionRequirements[slope][impactDir[impactCase]][wind].pntBottomRight.Y());
                     (*pRebarTable)(rrow, col++) << stress.SetValue(sectionResult.altTensionRequirements[slope][impactDir[impactCase]][wind].pntBottomRight.Z());
                  }

                  if (bReportTensileForceDetails)
                  {
                     if (sectionResult.altTensionRequirements[slope][impactDir[impactCase]][wind].tensionForceSolution)
                     {
                        rptRcTable* pDetailsTable = CreateGeneralSectionDetailsTable(sectionResult.altTensionRequirements[slope][impactDir[impactCase]][wind].tensionForceSolution, sectionResult.altTensionRequirements[slope][impactDir[impactCase]][wind].Ytg, pDisplayUnits);
                        (*pRebarTable)(rrow, col++) << pDetailsTable;
                     }
                     else
                     {
                        (*pRebarTable)(rrow, col++) << _T("-");
                     }
                  }

                  (*pRebarTable)(rrow, col++) << area.SetValue(sectionResult.altTensionRequirements[slope][impactDir[impactCase]][wind].AreaTension);
                  (*pRebarTable)(rrow, col++) << force.SetValue(sectionResult.altTensionRequirements[slope][impactDir[impactCase]][wind].T);
                  (*pRebarTable)(rrow, col++) << area.SetValue(sectionResult.altTensionRequirements[slope][impactDir[impactCase]][wind].AsProvided);
                  if (sectionResult.altTensionRequirements[slope][impactDir[impactCase]][wind].AsRequired < 0)
                  {
                     (*pRebarTable)(rrow, col++) << _T("-");
                  }
                  else
                  {
                     (*pRebarTable)(rrow, col++) << area.SetValue(sectionResult.altTensionRequirements[slope][impactDir[impactCase]][wind].AsRequired);
                  }

                  rrow++;
               } // section
#endif // REBAR_FOR_DIRECT_TENSION
            } // next section

            ///////////////////////////////////////////////////////////////////////
            // Failure
            ///////////////////////////////////////////////////////////////////////

            Float64 alpha = (slope == stbTypes::Superelevation ? pStabilityProblem->GetSuperelevation() : pStabilityProblem->GetCrownSlope());

            pPara = new rptParagraph(rptStyleManager::GetSubheadingStyle());
            *pChapter << pPara;
            *pPara << _T("Factor of Safety Against Failure") << rptNewLine;
            pPara = new rptParagraph;
            *pChapter << pPara;

            *pPara << THETA_FAILURE << _T(" = ") << symbol(alpha);
            if (pResults->ThetaRollover[slope][impactDir[impactCase]][wind] < alpha)
            {
               *pPara << _T(" - ");
            }
            else
            {
               *pPara << _T(" + ");
            }
            *pPara << symbol(ROOT) << _T("{") << Super2(symbol(alpha), _T("2"));
            if (pResults->ThetaRollover[slope][impactDir[impactCase]][wind] < alpha)
            {
               *pPara << _T(" - ");
            }
            else
            {
               *pPara << _T(" + ");
            }
            *pPara << _T("[");
            if (slope == stbTypes::Superelevation)
            {
               *pPara << _T("(");
               if (wind == stbTypes::Right)
               {
                  *pPara << _T(" - ");
               }
               *pPara << Z_WIND << _T(" ") << strCFSign.c_str() << _T(" ") << Z_CF << _T(")");
            }
            else
            {
               if (wind == stbTypes::Right)
               {
                  *pPara << _T(" - ");
               }
               *pPara << Z_WIND;
            }
            *pPara << _T(" + ") << EI << _T(" + ") << M_OT << _T("/") << _T("((IM)") << Sub2(_T("W"), _T("g")) << _T(")") << _T(" + ((IM)") << ZO << _T(" + ") << YR;
            if (pResults->ThetaRollover[slope][impactDir[impactCase]][wind] < alpha)
            {
               *pPara << _T(" - ");
            }
            else
            {
               *pPara << _T(" + ");
            }
            *pPara << _T("2.5");
            if (slope == stbTypes::Superelevation)
            {
               *pPara << _T("(");
               if (wind == stbTypes::Right)
               {
                  *pPara << _T(" - ");
               }
               *pPara << Z_WIND << _T(" ") << strCFSign.c_str() << _T(" ") << Z_CF << _T(")");
            }
            else
            {
               if (wind == stbTypes::Right)
               {
                  *pPara << _T(" - ");
               }
               *pPara << Z_WIND;
            }
            *pPara << _T(")") << symbol(alpha) << _T("]/(2.5(IM)") << ZO << _T(")}") << rptNewLine;

            if (pResults->ThetaRollover[slope][impactDir[impactCase]][wind] < alpha)
            {
               *pPara << _T("-0.4 radians ") << symbol(LTE) << _T(" ") << THETA_FAILURE << rptNewLine;
            }
            else
            {
               *pPara << THETA_FAILURE << _T(" ") << symbol(LTE) << _T(" 0.4 radians") << rptNewLine;
            }

            *pPara << THETA_FAILURE << _T(" = ") << tiltAngle.SetValue(pResults->ThetaMax[slope][impactDir[impactCase]][wind]) << rptNewLine;
            *pPara << _T("Assumed direction of tilt is ") << strTiltRotation[pResults->AssumedTiltDirection] << _T(" (top of girder tilt towards the ") << strTiltDirection[pResults->AssumedTiltDirection] << _T(").") << rptNewLine;

            *pPara << Sub2(_T("FS"), _T("f")) << _T(" = Factor of Safety Against Failure = [") << K_THETA << _T("(") << THETA_FAILURE << _T(" - ") << symbol(alpha) << _T(")]");
            *pPara << _T("/{(IM)") << Sub2(_T("W"), _T("g")) << _T("[((IM)") << ZO << THETA_FAILURE << _T(" + ");
            if (slope == stbTypes::Superelevation)
            {
               *pPara << _T("(");
               if (wind == stbTypes::Right)
               {
                  *pPara << _T("-");
               }
               *pPara << Z_WIND << _T(" ") << strCFSign.c_str() << _T(" ") << Z_CF << _T(")");
            }
            else
            {
               if (wind == stbTypes::Right)
               {
                  *pPara << _T("-");
               }
               *pPara << Z_WIND;
            }
            *pPara << _T(")") << _T("(1 + 2.5|") << THETA_FAILURE << _T("|) + ") << YR << THETA_FAILURE << _T(" + ") << EI << _T("]") << _T(" + ") << M_OT << _T("}") << rptNewLine;


            *pPara << Sub2(_T("FS"), _T("f")) << _T(" = ");
            if (pResults->FsFailure[slope][impactDir[impactCase]][wind] == Float64_Max)
            {
               *pPara << symbol(infinity) << rptNewLine;
            }
            else
            {
               *pPara << scalar.SetValue(pResults->FsFailure[slope][impactDir[impactCase]][wind]) << rptNewLine;
            }
            *pPara << _T("If ") << Sub2(_T("FS"), _T("f")) << _T(" is less than ") << Sub2(_T("FS"), _T("cr")) << _T(" then ") << Sub2(_T("FS"), _T("f")) << _T(" = ") << Sub2(_T("FS"), _T("cr")) << _T(". ");
            *pPara << Sub2(_T("FS"), _T("f")) << _T(" = ");
            if (pResults->FsFailure[slope][impactDir[impactCase]][wind] == Float64_Max)
            {
               *pPara << symbol(infinity);
            }
            else
            {
               *pPara << scalar.SetValue(pResults->FsFailure[slope][impactDir[impactCase]][wind]);
            }
            *pPara << _T(", ") << Sub2(_T("FS"), _T("cr")) << _T(" = ");
            if (pResults->MinFScr[slope] == Float64_Max)
            {
               *pPara << symbol(infinity);
            }
            else
            {
               *pPara << scalar.SetValue(pResults->MinFScr[slope]);
            }
            *pPara << _T(", therefore ") << Sub2(_T("FS"), _T("f")) << _T(" = ");
            if (pResults->AdjFsFailure[slope][impactDir[impactCase]][wind] == Float64_Max)
            {
               *pPara << symbol(infinity) << rptNewLine;
            }
            else
            {
               *pPara << scalar.SetValue(pResults->AdjFsFailure[slope][impactDir[impactCase]][wind]) << rptNewLine;
            }
            *pPara << rptNewLine;

            ///////////////////////////////////////////////////////////////////////
            // Rollover
            ///////////////////////////////////////////////////////////////////////

            pPara = new rptParagraph(rptStyleManager::GetSubheadingStyle());
            *pChapter << pPara;
            *pPara << _T("Factor of Safety against Rollover") << rptNewLine;
            pPara = new rptParagraph;
            *pChapter << pPara;

            shortLength.ShowUnitTag(true);
            *pPara << Z_MAX << _T(" = ") << Sub2(_T("W"), _T("cc")) << _T("/2 = ") << shortLength.SetValue(pStabilityProblem->GetWheelLineSpacing() / 2) << rptNewLine;
            shortLength.ShowUnitTag(false);
            *pPara << THETA_ROLLOVER << _T(" = tilt angle at roll over") << rptNewLine;
            if ((slope == stbTypes::NormalCrown && !IsZero(pResults->Wwind)) ||
               (slope == stbTypes::Superelevation && !IsZero(pResults->Wwind + pResults->Wcf))
               )
            {
               if (pResults->bRolloverStability[slope][impactDir[impactCase]][wind])
               {
                  *pPara << THETA_ROLLOVER << _T(" = [");
                  if (pResults->ThetaEq[slope][impactDir[impactCase]][wind] < 0)
                  {
                     *pPara << symbol(alpha) << _T("-");
                  }
                  *pPara << Sub2(_T("(IM)W"), _T("g")) << _T("(") << Z_MAX;
                  if (pResults->ThetaEq[slope][impactDir[impactCase]][wind] < 0)
                  {
                     *pPara << _T(" + ");
                  }
                  else
                  {
                     *pPara << _T(" - ");
                  }
                  *pPara << H_RC << symbol(alpha) << _T(") ") << strOppWindSign.c_str() << _T(" ") << W_WIND << _T("(") << H_RC;
                  if (pResults->ThetaEq[slope][impactDir[impactCase]][wind] < 0)
                  {
                     *pPara << _T(" - ");
                  }
                  else
                  {
                     *pPara << _T(" + ");
                  }
                  *pPara << Z_MAX << symbol(alpha) << _T(")");
                  if (slope == stbTypes::Superelevation)
                  {
                     *pPara << _T(" ") << strOppCFSign.c_str() << _T(" ") << W_CF << _T("(") << H_RC;
                     if (pResults->ThetaEq[slope][impactDir[impactCase]][wind] < 0)
                     {
                        *pPara << _T(" - ");
                     }
                     else
                     {
                        *pPara << _T(" + ");
                     }
                     *pPara << Z_MAX << symbol(alpha) << _T(")");
                  }
                  *pPara << _T("]") << _T("/") << K_THETA << _T(" + ") << symbol(alpha) << rptNewLine;
                  *pPara << THETA_ROLLOVER << _T(" = ") << tiltAngle.SetValue(pResults->ThetaRollover[slope][impactDir[impactCase]][wind]) << rptNewLine;
                  *pPara << _T("Assumed direction of tilt is ") << strTiltRotation[pResults->AssumedTiltDirection] << _T(" (top of girder tilt towards the ") << strTiltDirection[pResults->AssumedTiltDirection] << _T(").") << rptNewLine;;
                  *pPara << rptNewLine;
               }
               else
               {
                  *pPara << _T("Rollover instability.") << rptNewLine;
               }
            }
            else
            {
               ATLASSERT(0 <= pResults->ThetaEq[slope][impactDir[impactCase]][wind]); // no lateral loads, theta_eq always > 0
               if (pResults->bRolloverStability[slope][impactDir[impactCase]][wind])
               {
                  *pPara << THETA_ROLLOVER << _T(" = [");
                  *pPara << Sub2(_T("(IM)W"), _T("g")) << _T("(") << Z_MAX << _T(" - ") << H_RC << symbol(alpha) << _T(") ") << strOppWindSign.c_str() << _T(" ") << W_WIND << _T("(") << H_RC << _T(" + ") << Z_MAX << symbol(alpha) << _T(")");
                  if (slope == stbTypes::Superelevation)
                  {
                     *pPara << _T(" ") << strOppCFSign.c_str() << _T(" ") << W_CF << _T("(") << H_RC << _T(" + ") << Z_MAX << symbol(alpha) << _T(")");
                  }
                  *pPara << _T("]") << _T("/") << K_THETA << _T(" + ") << symbol(alpha) << rptNewLine;
                  *pPara << THETA_ROLLOVER << _T(" = ") << tiltAngle.SetValue(pResults->ThetaRollover[slope][impactDir[impactCase]][wind]) << rptNewLine;
                  *pPara << _T("Assumed direction of tilt is ") << strTiltRotation[pResults->AssumedTiltDirection] << _T(" (top of girder tilt towards the ") << strTiltDirection[pResults->AssumedTiltDirection] << _T(").") << rptNewLine;;
               }
               else
               {
                  *pPara << _T("Rollover instability.") << rptNewLine;
               }
            }

            *pPara << FS_R << _T(" = Factor of Safety against Rollover") << rptNewLine;
            if (pResults->bRolloverStability[slope][impactDir[impactCase]][wind])
            {
               *pPara << FS_R << _T(" = [");
               *pPara << K_THETA << _T("(") << THETA_ROLLOVER << _T(" - ") << symbol(alpha) << _T(")]");
               *pPara << _T("/{");
               *pPara << Sub2(_T("(IM)W"), _T("g")) << _T("[((IM)") << ZO << THETA_ROLLOVER << _T(" + ");

               if (slope == stbTypes::Superelevation)
               {
                  *pPara << _T("(");
                  if (wind == stbTypes::Right)
                  {
                     *pPara << _T("-");
                  }
                  *pPara << Z_WIND << _T(" ") << strCFSign.c_str() << _T(" ") << Z_CF << _T(")");
               }
               else
               {
                  if (wind == stbTypes::Right)
                  {
                     *pPara << _T("-");
                  }
                  *pPara << Z_WIND;
               }
               *pPara << _T(")") << _T("(1 + 2.5|") << THETA_ROLLOVER << _T("|) ") << _T(" + ") << YR << THETA_ROLLOVER << _T(" + ") << EI << _T("]") << _T(" + ") << M_OT << _T("}") << rptNewLine;

               *pPara << FS_R << _T(" = ");
               if (pResults->FsRollover[slope][impactDir[impactCase]][wind] == Float64_Max)
               {
                  *pPara << symbol(infinity) << rptNewLine;
               }
               else
               {
                  *pPara << scalar.SetValue(pResults->FsRollover[slope][impactDir[impactCase]][wind]) << rptNewLine;
               }
               *pPara << rptNewLine;
            }
            else
            {
               ATLASSERT(IsZero(pResults->FsRollover[slope][impactDir[impactCase]][wind]));
               *pPara << FS_R << _T(" = ") << scalar.SetValue(pResults->FsRollover[slope][impactDir[impactCase]][wind]) << rptNewLine;
            }


#if !defined REBAR_FOR_DIRECT_TENSION
            if (segment)
            {
               (*pPara) << pRebarTable << rptNewLine;
               (*pPara) << _T("The neutral axis is defined by its location with respect to the top center of the girder (") << Sub2(_T("Y"), _T("na")) << _T(")");
               if (!bSimpleFormat)
               {
                  (*pPara) << _T(" and its slope(Slope NA)");
               }
               (*pPara) << rptNewLine;
               (*pPara) << Super(_T("*")) << _T(" to be considered sufficient, reinforcement must be fully developed and lie within the tension area of the section") << rptNewLine;
               (*pPara) << _T("** minimum area of sufficiently bonded reinforcement needed to use the alternative tensile stress limit") << rptNewLine;

               *pPara << rptNewLine;
            }
#endif
         } // next wind direction


#if defined REBAR_FOR_DIRECT_TENSION
         if (segment)
         {
            rptRcTable* pRebarTable = nullptr;
            std::_tstring strTitle(_T("Bonded reinforcement requirements [") + std::_tstring(LrfdCw8th(_T("C5.9.4.1.2"), _T("C5.9.2.3.1b"))) + std::_tstring(_T("]")));
            ColumnIndexType nColumns = (bSimpleFormat ? 8 : 19);
            if (bReportTensileForceDetails)
            {
               nColumns++;
            }
            pRebarTable = rptStyleManager::CreateDefaultTable(nColumns, strTitle);
            (*pPara) << pRebarTable << rptNewLine;
            (*pPara) << _T("The neutral axis is defined by its location with respect to the top center of the girder (") << Sub2(_T("Y"), _T("na")) << _T(")");
            if (!bSimpleFormat)
            {
               (*pPara) << _T(" and its slope(Slope NA)");
            }
            (*pPara) << rptNewLine;
            (*pPara) << Super(_T("*")) << _T(" to be considered sufficient, reinforcement must be fully developed and lie within the tension area of the section") << rptNewLine;
            (*pPara) << _T("** minimum area of sufficiently bonded reinforcement needed to use the alternative tensile stress limit") << rptNewLine;

            if (bReportTensileForceDetails)
            {
               *pPara << rptNewLine;
               (*pPara) << _T("Tension Force, T = ") << symbol(SUM) << Sub2(_T("T"), _T("i")) << _T(" = ") << symbol(SUM) << _T("(") << Sub2(_T("A"), _T("i")) << _T(")(") << Sub2(_T("f"), _T("i")) << _T(")") << rptNewLine;
            }

            *pPara << rptNewLine;

            col = 0;
            if (lpszLocColumnLabel)
            {
               (*pRebarTable)(0, col++) << COLHDR(rptRcStringLiteral(lpszLocColumnLabel), rptLengthUnitTag, pDisplayUnits->SpanLength);
            }
            else
            {
               (*pRebarTable)(0, col++) << COLHDR(_T("Dist from") << rptNewLine << _T("left end"), rptLengthUnitTag, pDisplayUnits->SpanLength);
            }
            (*pRebarTable)(0, col++) << COLHDR(Sub2(_T("Y"), _T("na")), rptLengthUnitTag, pDisplayUnits->ComponentDim);

            if (bSimpleFormat)
            {
               (*pRebarTable)(0, col++) << COLHDR(RPT_STRESS(_T("t")), rptStressUnitTag, pDisplayUnits->Stress);
               (*pRebarTable)(0, col++) << COLHDR(RPT_STRESS(_T("b")), rptStressUnitTag, pDisplayUnits->Stress);
            }
            else
            {
               pRebarTable->SetNumberOfHeaderRows(2);
               col = 0;

               // location
               pRebarTable->SetRowSpan(0, col++, 2);

               // Yna
               pRebarTable->SetRowSpan(0, col++, 2);

               pRebarTable->SetRowSpan(0, col, 2);
               (*pRebarTable)(0, col++) << _T("Slope NA");

               pRebarTable->SetColumnSpan(0, col, 3);
               (*pRebarTable)(0, col) << _T("Top Left");
               (*pRebarTable)(1, col++) << COLHDR(Sub2(_T("x"), _T("tl")), rptLengthUnitTag, pDisplayUnits->ComponentDim);
               (*pRebarTable)(1, col++) << COLHDR(Sub2(_T("y"), _T("tl")), rptLengthUnitTag, pDisplayUnits->ComponentDim);
               (*pRebarTable)(1, col++) << COLHDR(RPT_STRESS(_T("tl")), rptStressUnitTag, pDisplayUnits->Stress);

               pRebarTable->SetColumnSpan(0, col, 3);
               (*pRebarTable)(0, col) << _T("Top Right");
               (*pRebarTable)(1, col++) << COLHDR(Sub2(_T("x"), _T("tr")), rptLengthUnitTag, pDisplayUnits->ComponentDim);
               (*pRebarTable)(1, col++) << COLHDR(Sub2(_T("y"), _T("tr")), rptLengthUnitTag, pDisplayUnits->ComponentDim);
               (*pRebarTable)(1, col++) << COLHDR(RPT_STRESS(_T("tr")), rptStressUnitTag, pDisplayUnits->Stress);

               pRebarTable->SetColumnSpan(0, col, 3);
               (*pRebarTable)(0, col) << _T("Bottom Left");
               (*pRebarTable)(1, col++) << COLHDR(Sub2(_T("x"), _T("bl")), rptLengthUnitTag, pDisplayUnits->ComponentDim);
               (*pRebarTable)(1, col++) << COLHDR(Sub2(_T("y"), _T("bl")), rptLengthUnitTag, pDisplayUnits->ComponentDim);
               (*pRebarTable)(1, col++) << COLHDR(RPT_STRESS(_T("bl")), rptStressUnitTag, pDisplayUnits->Stress);

               pRebarTable->SetColumnSpan(0, col, 3);
               (*pRebarTable)(0, col) << _T("Bottom Right");
               (*pRebarTable)(1, col++) << COLHDR(Sub2(_T("x"), _T("br")), rptLengthUnitTag, pDisplayUnits->ComponentDim);
               (*pRebarTable)(1, col++) << COLHDR(Sub2(_T("y"), _T("br")), rptLengthUnitTag, pDisplayUnits->ComponentDim);
               (*pRebarTable)(1, col++) << COLHDR(RPT_STRESS(_T("br")), rptStressUnitTag, pDisplayUnits->Stress);

               ColumnIndexType colOffset = 0;
               if (bReportTensileForceDetails)
               {
                  pRebarTable->SetRowSpan(0, col + colOffset, 2); colOffset++; // Tension Force Details
               }

               pRebarTable->SetRowSpan(0, col + colOffset, 2); colOffset++; // At
               pRebarTable->SetRowSpan(0, col + colOffset, 2); colOffset++; // T
               pRebarTable->SetRowSpan(0, col + colOffset, 2); colOffset++; // As Provided
               pRebarTable->SetRowSpan(0, col + colOffset, 2); colOffset++; // As Required
            }

            if (bReportTensileForceDetails)
            {
               (*pRebarTable)(0, col++) << _T("Tension Force Details");
            }

            (*pRebarTable)(0, col++) << COLHDR(Sub2(_T("A"), _T("t")), rptAreaUnitTag, pDisplayUnits->Area);
            (*pRebarTable)(0, col++) << COLHDR(_T("T"), rptForceUnitTag, pDisplayUnits->GeneralForce);
            (*pRebarTable)(0, col++) << COLHDR(Sub2(_T("A"), _T("s")) << rptNewLine << _T("Provided") << Super(_T("*")), rptAreaUnitTag, pDisplayUnits->Area);
            (*pRebarTable)(0, col++) << COLHDR(Sub2(_T("A"), _T("s")) << rptNewLine << _T("Required") << Super(_T("**")), rptAreaUnitTag, pDisplayUnits->Area);

            RowIndexType rrow = pRebarTable->GetNumberOfHeaderRows();
            for (const auto& sectionResult : pResults->vSectionResults)
            {
               col = 0;
               const stbIAnalysisPoint* pAnalysisPoint = pStabilityProblem->GetAnalysisPoint(sectionResult.AnalysisPointIndex);
               (*pRebarTable)(rrow, col++) << rptRcStringLiteral(pAnalysisPoint->AsString(pDisplayUnits->SpanLength, offset, false));
               (*pRebarTable)(rrow, col++) << shortLength.SetValue(sectionResult.altTensionRequirements[slope][impactDir[impactCase]].Yna);
               if (bSimpleFormat)
               {
                  (*pRebarTable)(rrow, col++) << stress.SetValue(sectionResult.altTensionRequirements[slope][impactDir[impactCase]].pntTopLeft.Z());
                  (*pRebarTable)(rrow, col++) << stress.SetValue(sectionResult.altTensionRequirements[slope][impactDir[impactCase]].pntBottomLeft.Z());
               }
               else
               {
                  (*pRebarTable)(rrow, col++) << scalar.SetValue(sectionResult.altTensionRequirements[slope][impactDir[impactCase]].NAslope);

                  (*pRebarTable)(rrow, col++) << shortLength.SetValue(sectionResult.altTensionRequirements[slope][impactDir[impactCase]].pntTopLeft.X());
                  (*pRebarTable)(rrow, col++) << shortLength.SetValue(sectionResult.altTensionRequirements[slope][impactDir[impactCase]].pntTopLeft.Y());
                  (*pRebarTable)(rrow, col++) << stress.SetValue(sectionResult.altTensionRequirements[slope][impactDir[impactCase]].pntTopLeft.Z());

                  (*pRebarTable)(rrow, col++) << shortLength.SetValue(sectionResult.altTensionRequirements[slope][impactDir[impactCase]].pntTopRight.X());
                  (*pRebarTable)(rrow, col++) << shortLength.SetValue(sectionResult.altTensionRequirements[slope][impactDir[impactCase]].pntTopRight.Y());
                  (*pRebarTable)(rrow, col++) << stress.SetValue(sectionResult.altTensionRequirements[slope][impactDir[impactCase]].pntTopRight.Z());

                  (*pRebarTable)(rrow, col++) << shortLength.SetValue(sectionResult.altTensionRequirements[slope][impactDir[impactCase]].pntBottomLeft.X());
                  (*pRebarTable)(rrow, col++) << shortLength.SetValue(sectionResult.altTensionRequirements[slope][impactDir[impactCase]].pntBottomLeft.Y());
                  (*pRebarTable)(rrow, col++) << stress.SetValue(sectionResult.altTensionRequirements[slope][impactDir[impactCase]].pntBottomLeft.Z());

                  (*pRebarTable)(rrow, col++) << shortLength.SetValue(sectionResult.altTensionRequirements[slope][impactDir[impactCase]].pntBottomRight.X());
                  (*pRebarTable)(rrow, col++) << shortLength.SetValue(sectionResult.altTensionRequirements[slope][impactDir[impactCase]].pntBottomRight.Y());
                  (*pRebarTable)(rrow, col++) << stress.SetValue(sectionResult.altTensionRequirements[slope][impactDir[impactCase]].pntBottomRight.Z());
               }

               if (bReportTensileForceDetails)
               {
                  if (sectionResult.altTensionRequirements[slope][impactDir[impactCase]].tensionForceSolution)
                  {
                     rptRcTable* pDetailsTable = CreateGeneralSectionDetailsTable(sectionResult.altTensionRequirements[slope][impactDir[impactCase]].tensionForceSolution, sectionResult.altTensionRequirements[slope][impactDir[impactCase]].Ytg, bSimpleFormat, pDisplayUnits);
                     (*pRebarTable)(rrow, col++) << pDetailsTable;
                  }
                  else
                  {
                     (*pRebarTable)(rrow, col++) << _T("-");
                  }
               }

               (*pRebarTable)(rrow, col++) << area.SetValue(sectionResult.altTensionRequirements[slope][impactDir[impactCase]].AreaTension);
               (*pRebarTable)(rrow, col++) << force.SetValue(sectionResult.altTensionRequirements[slope][impactDir[impactCase]].T);
               (*pRebarTable)(rrow, col++) << area.SetValue(sectionResult.altTensionRequirements[slope][impactDir[impactCase]].AsProvided);
               if (sectionResult.altTensionRequirements[slope][impactDir[impactCase]].AsRequired < 0)
               {
                  (*pRebarTable)(rrow, col++) << _T("-");
               }
               else
               {
                  (*pRebarTable)(rrow, col++) << area.SetValue(sectionResult.altTensionRequirements[slope][impactDir[impactCase]].AsRequired);
               }

               rrow++;
            }
         }
#endif // REBAR_FOR_DIRECT_TENSION
      } // next impact direction

      if (pResults->IsStable())
      {
         pPara = new rptParagraph(rptStyleManager::GetSubheadingStyle());
         *pChapter << pPara;
         *pPara << _T("Controlling Factors of Safety") << rptNewLine;
         pPara = new rptParagraph;
         *pChapter << pPara;

         CString strTitle;

         if (bLabelImpact && !bLabelWind)
         {
            // more than one impact case but no wind
            strTitle.Format(_T("%s"), strImpact[impactIndex[pResults->FScrImpactDirection[slope]]]);
         }
         else if (!bLabelImpact && bLabelWind)
         {
            // only one impact case and wind cases
            strTitle.Format(_T("Wind towards the %s"), strWindDir[pResults->FScrWindDirection[slope]]);
         }
         else if (bLabelImpact && bLabelWind)
         {
            // more than one impact case and wind cases
            strTitle.Format(_T("%s, Wind towards the %s"), strImpact[impactIndex[pResults->FScrImpactDirection[slope]]], strWindDir[pResults->FScrWindDirection[slope]]);
         }
         else
         {
            strTitle = _T("");
         }

         longLength.ShowUnitTag(true);
         *pPara << _T("The minimum factor of safety against cracking, ") << rptRcStringLiteral(pStabilityProblem->GetAnalysisPoint(pResults->vSectionResults[pResults->FScrAnalysisPointIndex[slope]].AnalysisPointIndex)->AsString(pDisplayUnits->SpanLength, offset, true)) << _T(" ");

         *pPara << strFlange[pResults->vSectionResults[pResults->FScrAnalysisPointIndex[slope]].FScrCorner[slope]] << _T(" flange tip");
         if (strTitle.IsEmpty())
         {
            *pPara << rptNewLine;
         }
         else
         {
            *pPara << _T(" with ") << strTitle << rptNewLine;
         }
         *pPara << FS_CR << _T(" Min = ");
         if (pResults->MinFScr[slope] == Float64_Max)
         {
            *pPara << symbol(infinity) << rptNewLine;
         }
         else
         {
            *pPara << scalar.SetValue(pResults->MinFScr[slope]) << rptNewLine;
         }

         *pPara << rptNewLine;

         *pPara << _T("The minimum factor of safety against failure, ") << strTitle << rptNewLine;
         *pPara << FS_F << _T(" Min = ");
         if (pResults->MinAdjFsFailure[slope] == Float64_Max)
         {
            *pPara << symbol(infinity) << rptNewLine;
         }
         else
         {
            *pPara << scalar.SetValue(pResults->MinAdjFsFailure[slope]) << rptNewLine;
         }

         *pPara << rptNewLine;

         *pPara << _T("The minimum Factor of Safety against Rollover, ") << strTitle << rptNewLine;
         *pPara << FS_R << _T(" Min = ");
         if (pResults->MinFsRollover[slope] == Float64_Max)
         {
            *pPara << symbol(infinity) << rptNewLine;
         }
         else
         {
            *pPara << scalar.SetValue(pResults->MinFsRollover[slope]) << rptNewLine;
         }
      }
   } // next slope type
}
