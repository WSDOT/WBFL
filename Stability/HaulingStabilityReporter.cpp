///////////////////////////////////////////////////////////////////////
// Stability
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

#include <Stability\StabilityLib.h>
#include <Stability\HaulingStabilityReporter.h>

#include <EAF\EAFApp.h>

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
   *pPara << _T("Check for Hauling to Bridge Site [5.5.4.3][5.9.4.1]") << rptNewLine;

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

   stbTypes::WindType windLoadType;
   Float64 windLoad;
   pStabilityProblem->GetWindLoading(&windLoadType,&windLoad);
   IndexType nWindCases = IsZero(windLoad) ? 0 : 1;
   IndexType nCFCases   = IsZero(pStabilityProblem->GetVelocity()) ? 0 : 1;
   LPCTSTR strWindDir[] = {_T("Left"), _T("Right")};
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
         *pPara << _T("Stresses and Factor of Safety Against Cracking for Hauling at Normal Crown Slope") << rptNewLine;
      }
      else
      {
         *pPara << _T("Stresses and Factor of Safety Against Cracking for Hauling at Maximum Superelevation") << rptNewLine;
      }

      pPara = new rptParagraph;
      *pChapter << pPara;

      *pPara << _T("Maximum allowable concrete compressive stress = -") << criteria.CompressionCoefficient << RPT_FC << _T(" = ") << stress.SetValue(criteria.AllowableCompression) << rptNewLine;

      *pPara << _T("Maximum allowable concrete tensile stress = ") << tension_coeff.SetValue(criteria.TensionCoefficient[slope]);
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
         *pPara << _T("Maximum allowable concrete tensile stress = ") << tension_coeff.SetValue(criteria.TensionCoefficientWithRebar[slope]);
         if ( bLambda )
         {
            *pPara << symbol(lambda);
         }
         *pPara << symbol(ROOT) << RPT_FC;
         *pPara << _T(" if bonded reinforcement sufficient to resist the tensile force in the concrete is provided = ") << stress.SetValue(criteria.AllowableTensionWithRebar[slope]) << rptNewLine;
      }
      else
      {
         *pPara << _T("Allowable tensile stress with bonded reinforcement sufficient to resist tension force in concrete was not evaluated") << rptNewLine;
      }

      *pPara << _T("Allowable factor of safety against cracking = ") << scalar.SetValue(criteria.MinFScr) << rptNewLine;
      
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

      ColumnIndexType nColumns = 10;
      ColumnIndexType nColSpan = 2;
      if ( bLabelImpact )
      {
         nColumns += 2;
         nColSpan++;
      }

      if ( bLabelWind )
      {
         nColumns += 2;
         nColSpan++;
      }

      rptRcTable* pStressTable = rptStyleManager::CreateDefaultTable(nColumns,_T(""));
      *pPara << pStressTable << rptNewLine;

      ColumnIndexType col1 = 0;
      ColumnIndexType col2 = 0;
      pStressTable->SetRowSpan(0,col1,2);
      pStressTable->SetRowSpan(1,col2++,SKIP_CELL);
      if ( lpszLocColumnLabel )
      {
         (*pStressTable)(0,col1++) << COLHDR(rptRcStringLiteral(lpszLocColumnLabel),rptLengthUnitTag,pDisplayUnits->SpanLength);
      }
      else
      {
         (*pStressTable)(0,col1++) << COLHDR(_T("Dist from left") << rptNewLine << _T("end of girder"), rptLengthUnitTag, pDisplayUnits->SpanLength );
      }

      pStressTable->SetColumnSpan(0,col1,nColSpan);
      (*pStressTable)(0,col1++) << _T("Maximum Stress");
      (*pStressTable)(1,col2++) << COLHDR(RPT_STRESS(_T("")), rptStressUnitTag, pDisplayUnits->Stress );
      (*pStressTable)(1,col2++) << _T("Location");
      if ( bLabelImpact )
      {
         (*pStressTable)(1,col2++) << _T("Impact") << rptNewLine << _T("Direction");
      }
      if ( bLabelWind )
      {
         (*pStressTable)(1,col2++) << _T("Wind") << rptNewLine << _T("Direction");
      }

      pStressTable->SetRowSpan(0,col1,2);
      pStressTable->SetRowSpan(1,col2++,SKIP_CELL);
      (*pStressTable)(0,col1++) << COLHDR(RPT_STRESS(_T("Allow")), rptStressUnitTag, pDisplayUnits->Stress );

      pStressTable->SetRowSpan(0,col1,2);
      pStressTable->SetRowSpan(1,col2++,SKIP_CELL);
      (*pStressTable)(0,col1++) << _T("Tension") << rptNewLine << _T("Status") << rptNewLine << _T("(C/D)");

      pStressTable->SetColumnSpan(0,col1,nColSpan);
      (*pStressTable)(0,col1++) << _T("Minimum Stress");
      (*pStressTable)(1,col2++) << COLHDR(RPT_STRESS(_T("")), rptStressUnitTag, pDisplayUnits->Stress );
      (*pStressTable)(1,col2++) << _T("Location");
      if ( bLabelImpact )
      {
         (*pStressTable)(1,col2++) << _T("Impact") << rptNewLine << _T("Direction");
      }
      if ( bLabelWind )
      {
         (*pStressTable)(1,col2++) << _T("Wind") << rptNewLine << _T("Direction");
      }

      pStressTable->SetRowSpan(0,col1,2);
      pStressTable->SetRowSpan(1,col2++,SKIP_CELL);
      (*pStressTable)(0,col1++) << _T("Compression") << rptNewLine << _T("Status") << rptNewLine << _T("(C/D)");

      pStressTable->SetRowSpan(0,col1,2);
      pStressTable->SetRowSpan(1,col2++,SKIP_CELL);
      (*pStressTable)(0,col1++) << Sub2(_T("FS"),_T("cr"));

      pStressTable->SetRowSpan(0,col1,2);
      pStressTable->SetRowSpan(1,col2++,SKIP_CELL);
      (*pStressTable)(0,col1++) << _T("FS") << rptNewLine << _T("Status");

      pStressTable->SetNumberOfHeaderRows(2);
      for ( ColumnIndexType i = col1; i < pStressTable->GetNumberOfColumns(); i++ )
      {
         pStressTable->SetColumnSpan(0,i,SKIP_CELL);
      }

      RowIndexType row = pStressTable->GetNumberOfHeaderRows();
      for( const auto& sectionResult : results.vSectionResults)
      {
         ColumnIndexType col = 0;

         const stbIAnalysisPoint* pAnalysisPoint = pStabilityProblem->GetAnalysisPoint(sectionResult.AnalysisPointIndex);
         (*pStressTable)(row,col++) << rptRcStringLiteral(pAnalysisPoint->AsString(pDisplayUnits->SpanLength,offset,false));

         stbTypes::ImpactDirection impact;
         stbTypes::WindDirection wind;
         stbTypes::Corner corner;
         Float64 fAllow;
         bool bPassed;
         Float64 cd;
         pArtifact->GetControllingTensionCase(slope,sectionResult,&impact,&wind,&corner,&fAllow,&bPassed,&cd);

#if defined MATCH_OLD_ANALYSIS
         Float64 f;
         if ( slope == stbTypes::CrownSlope )
         {
            f = sectionResult.fDirect[slope][impact][wind][corner];
         }
         else
         {
            f = sectionResult.f[slope][impact][wind][corner];
         }
#else
         Float64 f = sectionResult.f[slope][impact][wind][corner];
#endif

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
            (*pStressTable)(row,col++) << CD_PASS(cdRatio,cd);
         }
         else
         {
            (*pStressTable)(row,col++) << CD_FAIL(cdRatio,cd);
         }

         // compression status
         pArtifact->GetControllingCompressionCase(slope,sectionResult,&impact,&wind,&corner,&fAllow,&bPassed,&cd);

#if defined MATCH_OLD_ANALYSIS
         if ( slope == stbTypes::CrownSlope )
         {
            f = sectionResult.fDirect[slope][impact][wind][corner];
         }
         else
         {
            f = sectionResult.f[slope][impact][wind][corner];
         }
#else
         f = sectionResult.f[slope][impact][wind][corner];
#endif
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

         if ( bPassed )
         {
            (*pStressTable)(row,col++) << CD_PASS(cdRatio,cd);
         }
         else
         {
            (*pStressTable)(row,col++) << CD_FAIL(cdRatio,cd);
         }

         Float64 FScr = sectionResult.FScrMin[slope];
         (*pStressTable)(row,col++) << scalar.SetValue(FScr);

         if ( FScr <= criteria.MinFScr )
         {
            (*pStressTable)(row,col++) << RPT_FAIL;
         }
         else
         {
            (*pStressTable)(row,col++) << RPT_PASS;
         }

         row++;
      }

      pPara = new rptParagraph;
      *pChapter << pPara;

      rptRcTable* pTable = rptStyleManager::CreateTableNoHeading(2,_T("Factor of Safety Against Failure"));
      *pPara << pTable << rptNewLine;

      row = pTable->GetNumberOfHeaderRows();
      (*pTable)(row,0) << _T("Factor of Safety Against Failure (") << Sub2(_T("FS"),_T("f")) << _T(")");
      (*pTable)(row,1) << scalar.SetValue(results.MinAdjFsFailure[slope]);
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

      pTable = rptStyleManager::CreateTableNoHeading(2,_T("Factor of Safety Against Rollover"));
      *pPara << pTable << rptNewLine;

      row = pTable->GetNumberOfHeaderRows();
      (*pTable)(row,0) << _T("Factor of Safety Against Rollover (") << Sub2(_T("FS"),_T("r")) << _T(")");
      (*pTable)(row,1) << scalar.SetValue(results.MinFsRollover[slope]);
      row++;

      (*pTable)(row,0) << _T("Allowable Factor of Safety Against Rollover");
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
   (*pTable)(1,0) << _T("Maximum Allowable Weight");
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

void stbHaulingStabilityReporter::BuildDetailsChapter(const stbIGirder* pGirder,const stbIHaulingStabilityProblem* pStabilityProblem,const stbHaulingResults* pResults,rptChapter* pChapter,LPCTSTR lpszLocColumnLabel,Float64 offset)
{
   CEAFApp* pApp = EAFGetApp();
   const unitmgtIndirectMeasure* pDisplayUnits = pApp->GetDisplayUnits();

   CComPtr<ISegment> segment;
   pGirder->GetSegment(&segment);

   std::_tstring strFlange[] = {_T("Top Left"),_T("Top Right"),_T("Bottom Left"),_T("Bottom Right")};

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
   LPCTSTR strWindDir[] = {_T("Left"), _T("Right")};
   LPCTSTR strCF = (pStabilityProblem->GetCentrifugalForceType() == stbTypes::Adverse ? _T("Adverse") : _T("Favorable"));

   bool bLabelImpact = (0 < nImpactCases ? true : false);
   bool bLabelWind   = (0 < nWindCases   ? true : false);
   bool bIsCF        = (0 < nCFCases     ? true : false);

   rptParagraph* pPara;

   pPara = new rptParagraph;
   (*pChapter) << pPara;

   INIT_SCALAR_PROTOTYPE(rptRcScalar, scalar, pDisplayUnits->Scalar);
   INIT_UV_PROTOTYPE( rptForceUnitValue,   force,       pDisplayUnits->GeneralForce, true);
   INIT_UV_PROTOTYPE( rptLengthUnitValue,  longLength,  pDisplayUnits->SpanLength,   true);
   INIT_UV_PROTOTYPE( rptLengthUnitValue,  shortLength, pDisplayUnits->ComponentDim, true);
   INIT_UV_PROTOTYPE( rptMomentUnitValue,  moment,      pDisplayUnits->Moment,       false);
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

   pPara = new rptParagraph(rptStyleManager::GetHeadingStyle());
   *pChapter << pPara;
   *pPara << _T("Hauling Analysis Details") << rptNewLine;
   *pPara << _T("Hauling to Bridge Site [5.5.4.3][5.9.4.1]") << rptNewLine;

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

   *pPara << _T("Height of roll axis above roadway, ") << Sub2(_T("H"),_T("rc")) << _T(" = ") << shortLength.SetValue(pStabilityProblem->GetHeightOfRollAxisAboveRoadway()) << rptNewLine;
   *pPara << _T("Location of Roll Axis below top of girder, ") << Sub2(_T("y"),_T("rc")) << _T(" = ") << shortLength.SetValue(-pStabilityProblem->GetYRollAxis()) << rptNewLine;
   *pPara << _T("Truck Rotational Stiffness, ") << Sub2(_T("K"),symbol(theta)) << _T(" = ") << rotational_stiffness.SetValue(pStabilityProblem->GetTruckRotationalStiffness()) << rptNewLine;
   *pPara << _T("Wheel line spacing (C-C distance between tires), ") << Sub2(_T("W"),_T("cc")) << _T(" = ") << shortLength.SetValue(pStabilityProblem->GetWheelLineSpacing()) << rptNewLine;
   *pPara << _T("At Normal Crown Slope ") << symbol(alpha) << _T(" = ") << pStabilityProblem->GetCrownSlope() << rptNewLine;
   *pPara << _T("At Maximum Superelevation ") << symbol(alpha) << _T(" = ") << pStabilityProblem->GetSuperelevation() << rptNewLine;

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
      *pPara << _T("Sweep Tolerance, ") << Sub2(_T("t"),_T("sweep")) << _T(" = ") << Super(_T("1")) << _T("/") << Sub(x) << _T(" in per 10 ft") << rptNewLine;
   }
   else
   {
      *pPara << _T("Sweep Tolerance, ") << Sub2(_T("t"),_T("sweep")) << _T(" = ") << 1000*pStabilityProblem->GetSweepTolerance() << _T("mm/m") << rptNewLine;
   }
   *pPara << _T("Bunking Tolerance, ") << Sub2(_T("e"),_T("bunk")) << _T(" = ") << shortLength.SetValue(pStabilityProblem->GetSupportPlacementTolerance()) << rptNewLine;

   const matConcreteEx& concrete = pStabilityProblem->GetConcrete();
   *pPara << RPT_FC << _T(" = ") << stress.SetValue(concrete.GetFc()) << rptNewLine;
   *pPara << Sub2(_T("E"),_T("c")) << _T(" = Modulus of Elasticity = ") << modE.SetValue(concrete.GetE()) << rptNewLine;
   *pPara << RPT_STRESS(_T("r")) << _T(" = Modulus of Rupture = ") << stress.SetValue(concrete.GetFlexureFr()) << rptNewLine;

   IndexType nSections = pGirder->GetSectionCount();
   bool bPrismaticBeam = false;
   if ( nSections == 1 )
   {
      Float64 Ag1,Ix1,Iy1,Yt1,Hg1,Wtop1,Wbot1;
      pGirder->GetSectionProperties(0,stbTypes::Start,&Ag1,&Ix1,&Iy1,&Yt1,&Hg1,&Wtop1,&Wbot1);
      Float64 Ag2,Ix2,Iy2,Yt2,Hg2,Wtop2,Wbot2;
      pGirder->GetSectionProperties(0,stbTypes::End,&Ag2,&Ix2,&Iy2,&Yt2,&Hg2,&Wtop2,&Wbot2);
      if ( IsEqual(Ag1,Ag2) && IsEqual(Ix1,Ix2) && IsEqual(Iy1,Iy2) && IsEqual(Yt1,Yt2) && IsEqual(Hg1,Hg2) && IsEqual(Wtop1,Wtop2) && IsEqual(Wbot1,Wbot2) )
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
         *pPara << Sub2(_T("I"),_T("x")) << _T(" = ") << inertia.SetValue(Ix1) << rptNewLine;
         *pPara << Sub2(_T("I"),_T("y")) << _T(" = ") << inertia.SetValue(Iy1) << rptNewLine;
         *pPara << Sub2(_T("Y"),_T("t")) << _T(" = ") << shortLength.SetValue(-Yt1) << rptNewLine;
         *pPara << Sub2(_T("H"),_T("g")) << _T(" = ") << shortLength.SetValue(Hg1) << rptNewLine;
         *pPara << Sub2(_T("W"),_T("top")) << _T(" = ") << shortLength.SetValue(Wtop1) << rptNewLine;
         *pPara << Sub2(_T("W"),_T("bot")) << _T(" = ") << shortLength.SetValue(Wbot1) << rptNewLine;
      }
   }

   if ( !bPrismaticBeam )
   {
      rptRcTable* pSectPropTable = rptStyleManager::CreateDefaultTable(15,_T("Section Properties"));
      *pPara << pSectPropTable << rptNewLine;
      ColumnIndexType col = 0;
      pSectPropTable->SetNumberOfHeaderRows(2);
      
      pSectPropTable->SetRowSpan(0,0,2);
      pSectPropTable->SetRowSpan(1,0,SKIP_CELL);
      (*pSectPropTable)(0,col++) << COLHDR(_T("Section") << rptNewLine << _T("Length"),rptLengthUnitTag,pDisplayUnits->SpanLength);

      pSectPropTable->SetColumnSpan(0,col,7);
      (*pSectPropTable)(0,col)   << _T("Start of Section");
      pSectPropTable->SetColumnSpan(0,col+1,SKIP_CELL);
      pSectPropTable->SetColumnSpan(0,col+2,SKIP_CELL);
      pSectPropTable->SetColumnSpan(0,col+3,SKIP_CELL);
      pSectPropTable->SetColumnSpan(0,col+4,SKIP_CELL);
      pSectPropTable->SetColumnSpan(0,col+5,SKIP_CELL);
      pSectPropTable->SetColumnSpan(0,col+6,SKIP_CELL);
      (*pSectPropTable)(1,col++) << COLHDR(Sub2(_T("A"),_T("g")), rptAreaUnitTag, pDisplayUnits->Area);
      (*pSectPropTable)(1,col++) << COLHDR(Sub2(_T("I"),_T("x")), rptLength4UnitTag, pDisplayUnits->MomentOfInertia);
      (*pSectPropTable)(1,col++) << COLHDR(Sub2(_T("I"),_T("y")), rptLength4UnitTag, pDisplayUnits->MomentOfInertia);
      (*pSectPropTable)(1,col++) << COLHDR(Sub2(_T("Y"),_T("t")), rptLengthUnitTag, pDisplayUnits->ComponentDim);
      (*pSectPropTable)(1,col++) << COLHDR(Sub2(_T("H"),_T("g")), rptLengthUnitTag, pDisplayUnits->ComponentDim);
      (*pSectPropTable)(1,col++) << COLHDR(Sub2(_T("W"),_T("top")), rptLengthUnitTag, pDisplayUnits->ComponentDim);
      (*pSectPropTable)(1,col++) << COLHDR(Sub2(_T("W"),_T("bot")), rptLengthUnitTag, pDisplayUnits->ComponentDim);

      pSectPropTable->SetColumnSpan(0,col,7);
      (*pSectPropTable)(0,col)   << _T("End of Section");
      pSectPropTable->SetColumnSpan(0,col+1,SKIP_CELL);
      pSectPropTable->SetColumnSpan(0,col+2,SKIP_CELL);
      pSectPropTable->SetColumnSpan(0,col+3,SKIP_CELL);
      pSectPropTable->SetColumnSpan(0,col+4,SKIP_CELL);
      pSectPropTable->SetColumnSpan(0,col+5,SKIP_CELL);
      pSectPropTable->SetColumnSpan(0,col+6,SKIP_CELL);
      (*pSectPropTable)(1,col++) << COLHDR(Sub2(_T("A"),_T("g")), rptAreaUnitTag, pDisplayUnits->Area);
      (*pSectPropTable)(1,col++) << COLHDR(Sub2(_T("I"),_T("x")), rptLength4UnitTag, pDisplayUnits->MomentOfInertia);
      (*pSectPropTable)(1,col++) << COLHDR(Sub2(_T("I"),_T("y")), rptLength4UnitTag, pDisplayUnits->MomentOfInertia);
      (*pSectPropTable)(1,col++) << COLHDR(Sub2(_T("Y"),_T("t")), rptLengthUnitTag, pDisplayUnits->ComponentDim);
      (*pSectPropTable)(1,col++) << COLHDR(Sub2(_T("H"),_T("g")), rptLengthUnitTag, pDisplayUnits->ComponentDim);
      (*pSectPropTable)(1,col++) << COLHDR(Sub2(_T("W"),_T("top")), rptLengthUnitTag, pDisplayUnits->ComponentDim);
      (*pSectPropTable)(1,col++) << COLHDR(Sub2(_T("W"),_T("bot")), rptLengthUnitTag, pDisplayUnits->ComponentDim);

      RowIndexType row = pSectPropTable->GetNumberOfHeaderRows();
      longLength.ShowUnitTag(false);
      shortLength.ShowUnitTag(false);
      for ( IndexType sectIdx = 0; sectIdx < nSections; sectIdx++, row++ )
      {
         col = 0;
         Float64 L = pGirder->GetSectionLength(sectIdx);
         (*pSectPropTable)(row,col++) << longLength.SetValue(L);

         Float64 Ag,Ix,Iy,Yt,Hg,Wtop,Wbot;
         pGirder->GetSectionProperties(sectIdx,stbTypes::Start,&Ag,&Ix,&Iy,&Yt,&Hg,&Wtop,&Wbot);
         (*pSectPropTable)(row,col++) << area.SetValue(Ag);
         (*pSectPropTable)(row,col++) << inertia.SetValue(Ix);
         (*pSectPropTable)(row,col++) << inertia.SetValue(Iy);
         (*pSectPropTable)(row,col++) << shortLength.SetValue(-Yt);
         (*pSectPropTable)(row,col++) << shortLength.SetValue(Hg);
         (*pSectPropTable)(row,col++) << shortLength.SetValue(Wtop);
         (*pSectPropTable)(row,col++) << shortLength.SetValue(Wbot);

         pGirder->GetSectionProperties(sectIdx,stbTypes::End,&Ag,&Ix,&Iy,&Yt,&Hg,&Wtop,&Wbot);
         (*pSectPropTable)(row,col++) << area.SetValue(Ag);
         (*pSectPropTable)(row,col++) << inertia.SetValue(Ix);
         (*pSectPropTable)(row,col++) << inertia.SetValue(Iy);
         (*pSectPropTable)(row,col++) << shortLength.SetValue(-Yt);
         (*pSectPropTable)(row,col++) << shortLength.SetValue(Hg);
         (*pSectPropTable)(row,col++) << shortLength.SetValue(Wtop);
         (*pSectPropTable)(row,col++) << shortLength.SetValue(Wbot);
      }

      *pPara << rptNewLine;
   }

   longLength.ShowUnitTag(true);
   shortLength.ShowUnitTag(true);
   moment.ShowUnitTag(true);
 

   *pPara << rptNewLine;

   // Vertical location of center of gravity
   pPara = new rptParagraph(rptStyleManager::GetSubheadingStyle());
   *pChapter << pPara;
   *pPara << _T("Vertical Location of Center of Gravity") << rptNewLine;
   pPara = new rptParagraph;
   *pChapter << pPara;

   *pPara << _T("Offset Factor, ") << Sub2(_T("F"),_T("o")) << _T(" = [(") << Sub2(_T("L"),_T("g")) << _T(" - 2*Min(") << Sub2(_T("L"),_T("t")) << _T(",") << Sub2(_T("L"),_T("l")) << _T("))") << _T("/") << Sub2(_T("L"),_T("g")) << _T("]") << Super(_T("2")) << _T(" - 1/3 = ") << scalar.SetValue(pResults->OffsetFactor) << rptNewLine;

   bool bDirectCamber;
   Float64 camber;
   pStabilityProblem->GetCamber(&bDirectCamber,&camber);
   if ( bDirectCamber )
   {
      *pPara << _T("Camber, ") << Sub2(symbol(DELTA),_T("camber")) << _T(" = ") << shortLength.SetValue(camber) << rptNewLine;
      *pPara << _T("Camber Multipler, m = ") << pStabilityProblem->GetCamberMultiplier() << rptNewLine;
      *pPara << _T("Location of center of gravity above roll axis, ") << Sub2(_T("y"),_T("r")) << _T(" = ") << Sub2(_T("y"),_T("rc")) << _T(" - ") << Sub2(_T("Y"),_T("t")) << _T(" + ") << Sub2(_T("F"),_T("o")) << _T("(m)") << Sub2(symbol(DELTA),_T("camber")) << _T(" = ") << shortLength.SetValue(pResults->Dra[stbTypes::NoImpact]) << rptNewLine;
   }
   else
   {
      *pPara << _T("Camber offset factor, ") << Sub2(_T("F"),_T("co")) << _T(" = ") << scalar.SetValue(pResults->CamberOffsetFactor) << rptNewLine;
      *pPara << _T("Location of center of gravity above roll axis, ") << Sub2(_T("y"),_T("r")) << _T(" = ") << Sub2(_T("F"),_T("co")) << _T("(") << Sub2(_T("y"),_T("rc")) << _T(" - ") << Sub2(_T("Y"),_T("t")) << _T(") = ") << shortLength.SetValue(pResults->Dra[stbTypes::NoImpact]) << rptNewLine;
   }

   *pPara << rptNewLine;

   // Lateral Deflection Parameters
   pPara = new rptParagraph(rptStyleManager::GetSubheadingStyle());
   *pChapter << pPara;
   *pPara << _T("Lateral Deflection Parameters") << rptNewLine;
   pPara = new rptParagraph;
   *pChapter << pPara;
   *pPara << _T("Lateral Sweep, ") << Sub2(_T("e"),_T("sweep")) << _T(" = ") << Sub2(_T("L"),_T("g")) << Sub2(_T("t"),_T("sweep")) << _T(" = ") << shortLength.SetValue(pResults->LateralSweep) << rptNewLine;

   *pPara << _T("Initial lateral eccentricity of center of gravity of girder due to lateral sweep and eccentricity of bunking devices from centerline of girder, ") << rptNewLine;
   *pPara << Sub2(_T("e"),_T("i")) << _T(" = ") << Sub2(_T("F"),_T("o")) << Sub2(_T("e"),_T("sweep")) << _T(" + " ) << Sub2(_T("e"),_T("bunk")) << _T(" = ") << shortLength.SetValue(pResults->EccLateralSweep[stbTypes::NoImpact]) << rptNewLine;
   *pPara << rptNewLine;
 
   *pPara << _T("Lateral Deflection of center of gravity due to total girder weight applied to weak axis, ") << Sub2(_T("z"),_T("o"));
   if ( pResults->ZoMethod == stbTypes::Exact )
   {
      *pPara << _T(" = (") << Sub2(_T("W"),_T("g")) << _T("/12E") << Sub2(_T("I"),_T("y")) << Sub2(_T("L"),_T("g")) << Super(_T("2")) << _T(")(") 
         << Sub2(_T("L"),_T("s")) << Super(_T("5")) << _T("/10") << _T(" - ")
         << Super2(_T("a"),_T("2")) << Sub2(_T("L"),_T("s")) << Super(_T("3")) << _T(" + ")
         << _T("3") << Super2(_T("a"),_T("4")) << Sub2(_T("L"),_T("s")) << _T(" + ")
         << _T("6") << Super2(_T("a"),_T("5")) << _T("/5") << _T(")");
   }

   for ( IndexType impactCase = 0; impactCase <= nImpactCases; impactCase++ )
   {
      *pPara << _T(" = ") << shortLength.SetValue(pResults->Zo[impactDir[impactCase]]);
      if ( 0 < nImpactCases )
      {
         *pPara << _T(" (") << strImpact[impactCase] << _T(")");
      }
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
      *pPara << _T("Wind Pressure, ") << Sub2(_T("P"),_T("z")) << _T(" = ") << Sub2(_T("w"),_T("wind")) << _T(" = 2.56x") << Super2(_T("10"),_T("-6")) << Super2(_T("V"),_T("2")) << Sub2(_T("K"),_T("z")) << _T("G") << Sub2(_T("C"),_T("d")) << _T(" = ") << pressure.SetValue(pResults->WindPressure) << rptNewLine;
   }
   else
   {
      *pPara << _T("Lateral wind pressure, ") << Sub2(_T("w"),_T("wind")) << _T(" = ") << pressure.SetValue(pResults->WindPressure) << rptNewLine;
   }
   *pPara << _T("Total Wind Load, ") << Sub2(_T("W"),_T("wind")) << _T(" = ") << force.SetValue(pResults->Wwind) << rptNewLine;
   if ( bDirectCamber )
   {
      *pPara << _T("Location of resultant wind force above roll axis, ") << Sub2(_T("y"),_T("wind")) << _T(" = ") << Sub2(_T("H"),_T("g")) << _T("/2 + ") << Sub2(_T("y"),_T("rc")) << _T(" - ") << Sub2(_T("F"),_T("o")) << _T("(m)") << _T("(") << Sub2(symbol(DELTA),_T("camber")) << _T(") = ") << shortLength.SetValue(pResults->Ywind[stbTypes::NoImpact]) << rptNewLine;
   }
   else
   {
      *pPara << _T("Location of resultant wind force above roll axis, ") << Sub2(_T("y"),_T("wind")) << _T(" = ") << Sub2(_T("F"),_T("co")) << _T("(") << Sub2(_T("H"),_T("g")) << _T("/2 + ") << Sub2(_T("y"),_T("rc")) << _T(") = ") << shortLength.SetValue(pResults->Ywind[stbTypes::NoImpact]) << rptNewLine;
   }
   *pPara << rptNewLine;

   *pPara << _T("Lateral Deflection due to wind applied toward the left, ") << Sub2(_T("z"),_T("wind")) << _T(" = ") << Sub2(_T("W"),_T("wind")) << Sub2(_T("z"),_T("o")) << _T("/") << Sub2(_T("W"),_T("g")) << _T(" = ") << shortLength.SetValue(pResults->ZoWind[stbTypes::NoImpact]) << rptNewLine;
   *pPara << rptNewLine;

   *pPara << _T("Lateral eccentricity of Girder Self Weight due to Wind Load towards the left, ") << Sub2(_T("e"),_T("wind")) << _T(" = ") << Sub2(_T("W"),_T("wind")) << Sub2(_T("y"),_T("wind")) << _T("/") << Sub2(_T("W"),_T("g"));
   for (IndexType impactCase = 0; impactCase <= nImpactCases; impactCase++ )
   {
      *pPara << _T(" = ") << shortLength.SetValue(pResults->EccWind[impactDir[impactCase]]);
      if ( 0 < nImpactCases )
      {
         *pPara << _T(" (") << strImpact[impactCase] << _T(")");
      }
   }
   *pPara << rptNewLine;
   *pPara << _T("Overturning moment due to wind applied toward the left, ") << Sub2(_T("M"),_T("otwind")) << _T(" = ") << moment.SetValue(pResults->MotWind) << rptNewLine;
   *pPara << _T("Roll over moment due to wind applied toward the left, ") << Sub2(_T("M"),_T("rowind")) << _T(" = ") << moment.SetValue(pResults->MroWind) << rptNewLine;

   // Centrifugal Force Parameters
   pPara = new rptParagraph(rptStyleManager::GetSubheadingStyle());
   *pChapter << pPara;
   *pPara << _T("Centrifugal Force Parameters") << rptNewLine;
   pPara = new rptParagraph;
   *pChapter << pPara;
   *pPara << _T("Turning radius, R = ") << longLength.SetValue(pStabilityProblem->GetTurningRadius()) << rptNewLine;
   *pPara << _T("Velocity, V = ") << velocity.SetValue(pStabilityProblem->GetVelocity()) << rptNewLine;
   *pPara << _T("Centrigual Force, ") << Sub2(_T("W"),_T("cf")) << _T(" = (") << Sub2(_T("W"),_T("g")) << Super2(_T("V"),_T("2")) << _T(")/(gR) = ") << force.SetValue(pResults->Wcf) << rptNewLine;
   *pPara << _T("Centrigural force is ") << strCF << rptNewLine;
   *pPara << _T("Location of resultant centrifugal force above roll axis, ") << Sub2(_T("y"),_T("cf")) << _T(" = ") << Sub2(_T("y"),_T("r")) << _T(" = ") << shortLength.SetValue(pResults->Dra[stbTypes::NoImpact]) << rptNewLine;
   *pPara << _T("Lateral Deflection due to centrifugal force applied toward the left, ") << Sub2(_T("z"),_T("cf")) << _T(" = ") << Sub2(_T("W"),_T("cf")) << Sub2(_T("z"),_T("o")) << _T("/") << Sub2(_T("W"),_T("g")) << _T(" = ") << shortLength.SetValue(pResults->ZoCF) << rptNewLine;
   *pPara << _T("Overturning moment due to centrigural force, ") << Sub2(_T("M"),_T("otcf")) << _T(" = ") << Sub2(_T("W"),_T("cf")) << Sub2(_T("y"),_T("cf")) << _T(" = ") << moment.SetValue(pResults->MotCF) << rptNewLine;
   *pPara << _T("Roll over moment due to centrigural force, ") << Sub2(_T("M"),_T("rocf")) << _T(" = ") << Sub2(_T("W"),_T("cf")) << _T("(") << Sub2(_T("y"),_T("cf")) << _T(" + ") << Sub2(_T("H"),_T("cr")) << _T(") = ") << moment.SetValue(pResults->MroCF) << rptNewLine;
   *pPara << rptNewLine;

   pPara = new rptParagraph(rptStyleManager::GetSubheadingStyle());
   *pChapter << pPara;
   *pPara << _T("Moments and Stresses") << rptNewLine;

   pPara = new rptParagraph;
   *pChapter << pPara;
   rptRcTable* pLayoutTable = rptStyleManager::CreateLayoutTable(2);
   (*pPara) << pLayoutTable << rptNewLine;

   rptRcTable* pMomentTable = rptStyleManager::CreateDefaultTable(4,_T("Moments"));
   (*pLayoutTable)(0,0) << pMomentTable;

   ColumnIndexType col = 0;
   if ( lpszLocColumnLabel )
   {
      (*pMomentTable)(0,col++) << COLHDR(rptRcStringLiteral(lpszLocColumnLabel),rptLengthUnitTag,pDisplayUnits->SpanLength);
   }
   else
   {
      (*pMomentTable)(0,col++) << COLHDR(_T("Dist from left") << rptNewLine << _T("end of girder"),rptLengthUnitTag,pDisplayUnits->SpanLength);
   }
   (*pMomentTable)(0,col++) << COLHDR(Sub2(_T("M"),_T("girder")), rptMomentUnitTag, pDisplayUnits->Moment);
   (*pMomentTable)(0,col++) << COLHDR(Sub2(_T("M"),_T("wind")), rptMomentUnitTag, pDisplayUnits->Moment);
   (*pMomentTable)(0,col++) << COLHDR(Sub2(_T("M"),_T("cf")), rptMomentUnitTag, pDisplayUnits->Moment);

   rptRcTable* pStressTable = rptStyleManager::CreateDefaultTable(19,_T("Stress"));
   rptParagraph* p = &(*pLayoutTable)(0,1);
   *p << pStressTable << rptNewLine;
   *p << Sub2(_T("F"),_T("pe")) << _T(" = effective prestress force") << rptNewLine;
   *p << Sub2(_T("e"),_T("ps")) << _T(" = eccentricity of the prestress force. Positive values are below the neutral axis") << rptNewLine;
   *p << RPT_STRESS(_T("ps")) << _T(" = ") << _T("stress due to prestressing, ");
   *p << RPT_STRESS(_T("ps")) << _T(" Top = -") << Sub2(_T("F"),_T("pe")) << _T("(1/") << Sub2(_T("A"),_T("g")) << _T(" - ") << Sub2(_T("e"),_T("ps")) << Sub2(_T("Y"),_T("t")) << _T("/") << Sub2(_T("I"),_T("x")) << _T(")");
   *p << _T(", ");
   *p << RPT_STRESS(_T("ps")) << _T(" Bottom = -") << Sub2(_T("F"),_T("pe")) << _T("(1/") << Sub2(_T("A"),_T("g")) << _T(" + ") << Sub2(_T("e"),_T("ps")) << _T("(") << Sub2(_T("H"),_T("g")) << _T(" - ") << Sub2(_T("Y"),_T("t")) << _T(")/") << Sub2(_T("I"),_T("x")) << _T(")") << rptNewLine;
   
   *p << RPT_STRESS(_T("g")) << _T(" = ") << _T("stress due to girder self weight without impact, ");
   *p << RPT_STRESS(_T("g")) << _T(" Top = -") << Sub2(_T("M"),_T("girder")) << Sub2(_T("Y"),_T("t")) << _T("/") << Sub2(_T("I"),_T("x"));
   *p << _T(", ");
   *p << RPT_STRESS(_T("g")) << _T(" Bottom = ") << Sub2(_T("M"),_T("girder")) << _T("(") << Sub2(_T("H"),_T("g")) << _T(" - ") << Sub2(_T("Y"),_T("t")) << _T(")/") << Sub2(_T("I"),_T("x")) << rptNewLine;
   
   *p << RPT_STRESS(_T("w")) << _T(" = ") << _T("stress due to wind toward the left, ");
   *p << RPT_STRESS(_T("w")) << _T(" Top Left = ") << Sub2(_T("M"),_T("wind")) << Sub2(_T("W"),_T("top")) << _T("/(2") << Sub2(_T("I"),_T("y")) << _T(")");
   *p << _T(", ");
   *p << RPT_STRESS(_T("w")) << _T(" Top Right = -") << Sub2(_T("M"),_T("wind")) << Sub2(_T("W"),_T("top")) << _T("/(2") << Sub2(_T("I"),_T("y")) << _T(")");
   *p << _T(", ");
   *p << RPT_STRESS(_T("w")) << _T(" Bottom Left = ") << Sub2(_T("M"),_T("wind")) << Sub2(_T("W"),_T("bot")) << _T("/(2") << Sub2(_T("I"),_T("y")) << _T(")");
   *p << _T(", ");
   *p << RPT_STRESS(_T("w")) << _T(" Bottom Right = -") << Sub2(_T("M"),_T("wind")) << Sub2(_T("W"),_T("bot")) << _T("/(2") << Sub2(_T("I"),_T("y")) << _T(")") << rptNewLine;
   
   *p << RPT_STRESS(_T("cf")) << _T(" = ") << _T("stress due to centrifugal force, ");
   *p << RPT_STRESS(_T("cf")) << _T(" Top Left = ") << Sub2(_T("M"),_T("cf")) << Sub2(_T("W"),_T("top")) << _T("/(2") << Sub2(_T("I"),_T("y")) << _T(")");
   *p << _T(", ");
   *p << RPT_STRESS(_T("cf")) << _T(" Top Right = -") << Sub2(_T("M"),_T("cf")) << Sub2(_T("W"),_T("top")) << _T("/(2") << Sub2(_T("I"),_T("y")) << _T(")");
   *p << _T(", ");
   *p << RPT_STRESS(_T("cf")) << _T(" Bottom Left = ") << Sub2(_T("M"),_T("cf")) << Sub2(_T("W"),_T("bot")) << _T("/(2") << Sub2(_T("I"),_T("y")) << _T(")");
   *p << _T(", ");
   *p << RPT_STRESS(_T("cf")) << _T(" Bottom Right = -") << Sub2(_T("M"),_T("cf")) << Sub2(_T("W"),_T("bot")) << _T("/(2") << Sub2(_T("I"),_T("y")) << _T(")") << rptNewLine;


   col = 0;
   pStressTable->SetNumberOfHeaderRows(2);
   pStressTable->SetRowSpan(0,col,2);
   pStressTable->SetRowSpan(1,col,SKIP_CELL);
   if ( lpszLocColumnLabel )
   {
      (*pStressTable)(0,col++) << COLHDR(rptRcStringLiteral(lpszLocColumnLabel),rptLengthUnitTag,pDisplayUnits->SpanLength);
   }
   else
   {
      (*pStressTable)(0,col++) << COLHDR(_T("Dist from left") << rptNewLine << _T("end of girder"),rptLengthUnitTag,pDisplayUnits->SpanLength);
   }

   pStressTable->SetColumnSpan(0,col,2);
   (*pStressTable)(0,col) << _T("Straight");
   pStressTable->SetColumnSpan(0,col+1,SKIP_CELL);
   (*pStressTable)(1,col++) << COLHDR(Sub2(_T("F"),_T("pe")), rptForceUnitTag,pDisplayUnits->GeneralForce);
   (*pStressTable)(1,col++) << COLHDR(Sub2(_T("e"),_T("ps")), rptLengthUnitTag,pDisplayUnits->ComponentDim);

   pStressTable->SetColumnSpan(0,col,2);
   (*pStressTable)(0,col) << _T("Harped");
   pStressTable->SetColumnSpan(0,col+1,SKIP_CELL);
   (*pStressTable)(1,col++) << COLHDR(Sub2(_T("F"),_T("pe")), rptForceUnitTag,pDisplayUnits->GeneralForce);
   (*pStressTable)(1,col++) << COLHDR(Sub2(_T("e"),_T("ps")), rptLengthUnitTag,pDisplayUnits->ComponentDim);

   pStressTable->SetColumnSpan(0,col,2);
   (*pStressTable)(0,col) << _T("Temporary");
   pStressTable->SetColumnSpan(0,col+1,SKIP_CELL);
   (*pStressTable)(1,col++) << COLHDR(Sub2(_T("F"),_T("pe")), rptForceUnitTag,pDisplayUnits->GeneralForce);
   (*pStressTable)(1,col++) << COLHDR(Sub2(_T("e"),_T("ps")), rptLengthUnitTag,pDisplayUnits->ComponentDim);

   pStressTable->SetColumnSpan(0,col,2);
   (*pStressTable)(0,col) << RPT_STRESS(_T("ps"));
   pStressTable->SetColumnSpan(0,col+1,SKIP_CELL);
   (*pStressTable)(1,col++) << COLHDR(_T("Top"), rptStressUnitTag, pDisplayUnits->Stress);
   (*pStressTable)(1,col++) << COLHDR(_T("Bottom"), rptStressUnitTag, pDisplayUnits->Stress);

   pStressTable->SetColumnSpan(0,col,2);
   (*pStressTable)(0,col) << RPT_STRESS(_T("g"));
   pStressTable->SetColumnSpan(0,col+1,SKIP_CELL);
   (*pStressTable)(1,col++) << COLHDR(_T("Top"), rptStressUnitTag, pDisplayUnits->Stress);
   (*pStressTable)(1,col++) << COLHDR(_T("Bottom"), rptStressUnitTag, pDisplayUnits->Stress);

   pStressTable->SetColumnSpan(0,col,4);
   (*pStressTable)(0,col) << RPT_STRESS(_T("w"));
   pStressTable->SetColumnSpan(0,col+1,SKIP_CELL);
   pStressTable->SetColumnSpan(0,col+2,SKIP_CELL);
   pStressTable->SetColumnSpan(0,col+3,SKIP_CELL);
   (*pStressTable)(1,col++) << COLHDR(_T("Top Left"), rptStressUnitTag, pDisplayUnits->Stress);
   (*pStressTable)(1,col++) << COLHDR(_T("Top Right"), rptStressUnitTag, pDisplayUnits->Stress);
   (*pStressTable)(1,col++) << COLHDR(_T("Bottom Left"), rptStressUnitTag, pDisplayUnits->Stress);
   (*pStressTable)(1,col++) << COLHDR(_T("Bottom Right"), rptStressUnitTag, pDisplayUnits->Stress);

   pStressTable->SetColumnSpan(0,col,4);
   (*pStressTable)(0,col) << RPT_STRESS(_T("cf"));
   pStressTable->SetColumnSpan(0,col+1,SKIP_CELL);
   pStressTable->SetColumnSpan(0,col+2,SKIP_CELL);
   pStressTable->SetColumnSpan(0,col+3,SKIP_CELL);
   (*pStressTable)(1,col++) << COLHDR(_T("Top Left"), rptStressUnitTag, pDisplayUnits->Stress);
   (*pStressTable)(1,col++) << COLHDR(_T("Top Right"), rptStressUnitTag, pDisplayUnits->Stress);
   (*pStressTable)(1,col++) << COLHDR(_T("Bottom Left"), rptStressUnitTag, pDisplayUnits->Stress);
   (*pStressTable)(1,col++) << COLHDR(_T("Bottom Right"), rptStressUnitTag, pDisplayUnits->Stress);


   longLength.ShowUnitTag(false);
   shortLength.ShowUnitTag(false);
   force.ShowUnitTag(false);
   stress.ShowUnitTag(false);
   area.ShowUnitTag(false);
   moment.ShowUnitTag(false);

   RowIndexType mrow = pMomentTable->GetNumberOfHeaderRows();
   RowIndexType srow = pStressTable->GetNumberOfHeaderRows();
   for( const auto& sectionResult : pResults->vSectionResults)
   {
      col = 0;

      const stbIAnalysisPoint* pAnalysisPoint = pStabilityProblem->GetAnalysisPoint(sectionResult.AnalysisPointIndex);
      (*pMomentTable)(mrow,col++) << rptRcStringLiteral(pAnalysisPoint->AsString(pDisplayUnits->SpanLength,offset,false));

      (*pMomentTable)(mrow,col++) << moment.SetValue(sectionResult.Mg);
      (*pMomentTable)(mrow,col++) << moment.SetValue(sectionResult.Mw);
      (*pMomentTable)(mrow,col++) << moment.SetValue(sectionResult.Mcf);
      mrow++;

      col = 0;
      (*pStressTable)(srow,col++) << rptRcStringLiteral(pAnalysisPoint->AsString(pDisplayUnits->SpanLength,offset,false));

      Float64 Ag,Ix,Iy,Yt,Hg,Wtop,Wbot;
      pGirder->GetSectionProperties(pAnalysisPoint->GetLocation(),&Ag,&Ix,&Iy,&Yt,&Hg,&Wtop,&Wbot);
      
      Float64 Fpe,Yps;
      pStabilityProblem->GetFpe(stbTypes::Straight,pAnalysisPoint->GetLocation(),&Fpe,&Yps);
      (*pStressTable)(srow,col++) << force.SetValue(Fpe);
      (*pStressTable)(srow,col++) << shortLength.SetValue(Yt - Yps);
      
      pStabilityProblem->GetFpe(stbTypes::Harped,pAnalysisPoint->GetLocation(),&Fpe,&Yps);
      (*pStressTable)(srow,col++) << force.SetValue(Fpe);
      (*pStressTable)(srow,col++) << shortLength.SetValue(Yt - Yps);
      
      pStabilityProblem->GetFpe(stbTypes::Temporary,pAnalysisPoint->GetLocation(),&Fpe,&Yps);
      (*pStressTable)(srow,col++) << force.SetValue(Fpe);
      (*pStressTable)(srow,col++) << shortLength.SetValue(Yt - Yps);

      (*pStressTable)(srow,col++) << stress.SetValue(sectionResult.fps[stbTypes::Top]);
      (*pStressTable)(srow,col++) << stress.SetValue(sectionResult.fps[stbTypes::Bottom]);

      (*pStressTable)(srow,col++) << stress.SetValue(sectionResult.fg[stbTypes::Top]);
      (*pStressTable)(srow,col++) << stress.SetValue(sectionResult.fg[stbTypes::Bottom]);

      (*pStressTable)(srow,col++) << stress.SetValue(sectionResult.fw[stbTypes::TopLeft]);
      (*pStressTable)(srow,col++) << stress.SetValue(sectionResult.fw[stbTypes::TopRight]);
      (*pStressTable)(srow,col++) << stress.SetValue(sectionResult.fw[stbTypes::BottomLeft]);
      (*pStressTable)(srow,col++) << stress.SetValue(sectionResult.fw[stbTypes::BottomRight]);

      (*pStressTable)(srow,col++) << stress.SetValue(sectionResult.fcf[stbTypes::TopLeft]);
      (*pStressTable)(srow,col++) << stress.SetValue(sectionResult.fcf[stbTypes::TopRight]);
      (*pStressTable)(srow,col++) << stress.SetValue(sectionResult.fcf[stbTypes::BottomLeft]);
      (*pStressTable)(srow,col++) << stress.SetValue(sectionResult.fcf[stbTypes::BottomRight]);

      srow++;
   }

   for ( int s = 0; s < 2; s++ )
   {
      stbTypes::HaulingSlope slope = (stbTypes::HaulingSlope)s;

      // redo impact labeling because now it is based on the analysis slope type
      bool bImpactForThisSlope = (impactUsage == stbTypes::Both || (impactUsage == stbTypes::NormalCrown && slope == stbTypes::CrownSlope) || (impactUsage == stbTypes::MaxSuper && slope == stbTypes::Superelevation) ? true : false);

      LPCTSTR strImpact[3];
      stbTypes::ImpactDirection impactDir[3];
      Float64 impactFactor[3] = { -1,-1,-1 };
      IndexType impactIndex[3] = { INVALID_INDEX,INVALID_INDEX < INVALID_INDEX };

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


      pPara = new rptParagraph(rptStyleManager::GetSubheadingStyle());
      *pChapter << pPara;

      if ( slope == stbTypes::CrownSlope )
      {
         *pPara << _T("Analysis at Normal Crown Slope") << rptNewLine;
      }
      else
      {
         *pPara << _T("Analysis at Maximum Superelevation") << rptNewLine;
      }

      for ( IndexType impactCase = 0; impactCase <= nImpactCases; impactCase++ )
      {
         stbTypes::ImpactDirection impact = (stbTypes::ImpactDirection)impactCase;
         for ( IndexType windCase = 0; windCase <= nWindCases; windCase++ )
         {
            stbTypes::WindDirection wind = (stbTypes::WindDirection)windCase;

            CString strTitle;

            if ( bLabelImpact && !bLabelWind )
            {
               // more than one impact case but no wind
               strTitle.Format(_T("%s"),strImpact[impactCase]);
            }
            else if ( !bLabelImpact && bLabelWind )
            {
               // only one impact case and wind cases
               strTitle.Format(_T("Wind towards the %s"),strWindDir[wind]);
            }
            else if ( bLabelImpact && bLabelWind )
            {
               // more than one impact case and wind cases
               strTitle.Format(_T("%s, Wind towards the %s"),strImpact[impactCase],strWindDir[wind]);
            }
            else
            {
               strTitle = _T("");
            }

            std::_tstring strWindSign(wind == stbTypes::Left ? _T("+") : _T("-"));
            std::_tstring strOppWindSign(wind == stbTypes::Left ? _T("-") : _T("+"));
            std::_tstring strCFSign(pStabilityProblem->GetCentrifugalForceType() == stbTypes::Adverse ? _T("+") : _T("-"));
            std::_tstring strOppCFSign(pStabilityProblem->GetCentrifugalForceType() == stbTypes::Adverse ? _T("-") : _T("+"));

            pPara = new rptParagraph(rptStyleManager::GetSubheadingStyle());
            *pChapter << pPara;
            *pPara << strTitle << rptNewLine;

            pPara = new rptParagraph;
            *pChapter << pPara;

            if ( 0 < nImpactCases )
            {
               *pPara << _T("IM = ") << scalar.SetValue(impactFactor[impactCase]) << rptNewLine;

               *pPara << rptNewLine;
            }


            *pPara << _T("Equilibrium Tilt Angle, ") << Sub2(symbol(theta),_T("eq")) << _T(" = ");
            *pPara << _T("(") << Sub2(_T("K"),symbol(theta)) << symbol(alpha) << _T(" + ");
            if ( 0 < nImpactCases )
            {
               *pPara << _T("(IM)");
            }
            *pPara << Sub2(_T("W"),_T("g")) << _T("(");
            if ( wind == stbTypes::Right )
            {
               *pPara << strWindSign.c_str();
            }
            *pPara << Sub2(_T("z"),_T("wind")) << _T(" ") << strCFSign.c_str() << _T(" ") << Sub2(_T("z"),_T("cf")) << _T(" + ") << Sub2(_T("e"),_T("i")) << _T(") ") << strWindSign.c_str() << _T(" ") << Sub2(_T("M"),_T("otwind"));
            if (slope == stbTypes::MaxSuper)
            {
               *pPara << _T(" ") << strCFSign.c_str() << _T(" ") << Sub2(_T("M"),_T("otcf"));
            }
            *pPara << _T(")");
            *pPara << _T("/");
            *pPara << _T("(") << Sub2(_T("K"),symbol(theta)) << _T(" - ");
            if ( 0 < nImpactCases )
            {
               *pPara << _T("(IM)");
            }
            *pPara << Sub2(_T("W"),_T("g")) << _T("(") << Sub2(_T("y"),_T("r")) << _T(" + ") << Sub2(_T("z"),_T("o")) << _T(")) = ");
            *pPara << tiltAngle.SetValue(pResults->ThetaEq[slope][impactDir[impactCase]][wind]) << rptNewLine;

            *pPara << rptNewLine;

            rptRcTable* pTotalStressTable = rptStyleManager::CreateDefaultTable(13,_T("Stresses"));
            (*pPara) << pTotalStressTable << rptNewLine;
            (*pPara) << RPT_STRESS(_T("direct")) << _T(" = ") << RPT_STRESS(_T("ps")) << _T(" + (IM)(") << RPT_STRESS(_T("g")) << _T(" + ") << RPT_STRESS(_T("h")) << _T(") ") << strWindSign.c_str() << _T(" ") << RPT_STRESS(_T("w")) << rptNewLine;
            (*pPara) << RPT_STRESS(_T("tilt")) << _T(" = stress induced by girder rotation, ");
            (*pPara) << RPT_STRESS(_T("tilt")) << _T(" Top Left = (IM)") << Sub2(_T("M"),_T("girder")) << Sub2(symbol(theta),_T("eq")) << Sub2(_T("W"),_T("top")) << _T("/2") << Sub2(_T("I"),_T("y"));
            (*pPara) << _T(", ");
            (*pPara) << RPT_STRESS(_T("tilt")) << _T(" Top Right = -(IM)") << Sub2(_T("M"),_T("girder")) << Sub2(symbol(theta),_T("eq")) << Sub2(_T("W"),_T("top")) << _T("/2") << Sub2(_T("I"),_T("y"));
            (*pPara) << _T(", ");
            (*pPara) << RPT_STRESS(_T("tilt")) << _T(" Bottom Left = (IM)") << Sub2(_T("M"),_T("girder")) << Sub2(symbol(theta),_T("eq")) << Sub2(_T("W"),_T("bot")) << _T("/2") << Sub2(_T("I"),_T("y"));
            (*pPara) << _T(", ");
            (*pPara) << RPT_STRESS(_T("tilt")) << _T(" Bottom Right = -(IM)") << Sub2(_T("M"),_T("girder")) << Sub2(symbol(theta),_T("eq")) << Sub2(_T("W"),_T("bot")) << _T("/2") << Sub2(_T("I"),_T("y")) << rptNewLine;
            (*pPara) << RPT_STRESS(_T("total")) << _T(" = ") << RPT_STRESS(_T("direct")) << _T(" + ") << RPT_STRESS(_T("tilt")) << rptNewLine;

            col = 0;
            pTotalStressTable->SetNumberOfHeaderRows(2);
            pTotalStressTable->SetRowSpan(0,col,2);
            pTotalStressTable->SetRowSpan(1,col,SKIP_CELL);
            if ( lpszLocColumnLabel )
            {
               (*pTotalStressTable)(0,col++) << COLHDR(rptRcStringLiteral(lpszLocColumnLabel),rptLengthUnitTag,pDisplayUnits->SpanLength);
            }
            else
            {
               (*pTotalStressTable)(0,col++) << COLHDR(_T("Dist from left") << rptNewLine << _T("end of girder"),rptLengthUnitTag,pDisplayUnits->SpanLength);
            }

            pTotalStressTable->SetColumnSpan(0,col,4);
            pTotalStressTable->SetColumnSpan(0,col+1,SKIP_CELL);
            pTotalStressTable->SetColumnSpan(0,col+2,SKIP_CELL);
            pTotalStressTable->SetColumnSpan(0,col+3,SKIP_CELL);
            (*pTotalStressTable)(0,col)   << RPT_STRESS(_T("direct"));
            (*pTotalStressTable)(1,col++) << COLHDR(_T("Top Left"),rptStressUnitTag,pDisplayUnits->Stress);
            (*pTotalStressTable)(1,col++) << COLHDR(_T("Top Right"),rptStressUnitTag,pDisplayUnits->Stress);
            (*pTotalStressTable)(1,col++) << COLHDR(_T("Bottom Left"),rptStressUnitTag,pDisplayUnits->Stress);
            (*pTotalStressTable)(1,col++) << COLHDR(_T("Bottom Right"),rptStressUnitTag,pDisplayUnits->Stress);

            pTotalStressTable->SetColumnSpan(0,col,4);
            pTotalStressTable->SetColumnSpan(0,col+1,SKIP_CELL);
            pTotalStressTable->SetColumnSpan(0,col+2,SKIP_CELL);
            pTotalStressTable->SetColumnSpan(0,col+3,SKIP_CELL);
            (*pTotalStressTable)(0,col)   << RPT_STRESS(_T("tilt"));
            (*pTotalStressTable)(1,col++) << COLHDR(_T("Top Left"),rptStressUnitTag,pDisplayUnits->Stress);
            (*pTotalStressTable)(1,col++) << COLHDR(_T("Top Right"),rptStressUnitTag,pDisplayUnits->Stress);
            (*pTotalStressTable)(1,col++) << COLHDR(_T("Bottom Left"),rptStressUnitTag,pDisplayUnits->Stress);
            (*pTotalStressTable)(1,col++) << COLHDR(_T("Bottom Right"),rptStressUnitTag,pDisplayUnits->Stress);

            pTotalStressTable->SetColumnSpan(0,col,4);
            pTotalStressTable->SetColumnSpan(0,col+1,SKIP_CELL);
            pTotalStressTable->SetColumnSpan(0,col+2,SKIP_CELL);
            pTotalStressTable->SetColumnSpan(0,col+3,SKIP_CELL);
            (*pTotalStressTable)(0,col)   << RPT_STRESS(_T("total"));
            (*pTotalStressTable)(1,col++) << COLHDR(_T("Top Left"),rptStressUnitTag,pDisplayUnits->Stress);
            (*pTotalStressTable)(1,col++) << COLHDR(_T("Top Right"),rptStressUnitTag,pDisplayUnits->Stress);
            (*pTotalStressTable)(1,col++) << COLHDR(_T("Bottom Left"),rptStressUnitTag,pDisplayUnits->Stress);
            (*pTotalStressTable)(1,col++) << COLHDR(_T("Bottom Right"),rptStressUnitTag,pDisplayUnits->Stress);

            rptRcTable* pCrackingTable = rptStyleManager::CreateDefaultTable(5,_T("Factor of Safety Against Cracking"));
            (*pPara) << pCrackingTable << rptNewLine;
            (*pPara) << Sub2(_T("M"),_T("cr")) << _T(" = Cracking Moment = ");
            (*pPara) << Sub2(_T("M"),_T("cr")) << _T(" Top Flange = (") << RPT_STRESS(_T("r")) << _T(" - ") << RPT_STRESS(_T("direct")) << _T(")2") << Sub2(_T("I"),_T("y")) << _T("/") << Sub2(_T("W"),_T("top"));
            (*pPara) << _T(", ");
            (*pPara) << Sub2(_T("M"),_T("cr")) << _T(" Bottom Flange = (") << RPT_STRESS(_T("r")) << _T(" - ") << RPT_STRESS(_T("direct")) << _T(")2") << Sub2(_T("I"),_T("y")) << _T("/") << Sub2(_T("W"),_T("bot")) << rptNewLine;
            (*pPara) << _T("Cracked Flange, indicates the flange that is first to crack") << rptNewLine;
            (*pPara) << Sub2(symbol(theta),_T("cr")) << _T(" = tilt angle at cracking = ") << Sub2(_T("M"),_T("cr")) << _T("/") << Sub2(_T("M"),_T("girder")) << _T(" ") << symbol(LTE) << _T(" 0.4 radians") << rptNewLine;
            (*pPara) << Sub2(_T("FS"),_T("cr")) << _T(" = Factor of Safety Against Cracking = [") << Sub2(_T("K"),symbol(theta)) << _T("(") << Sub2(symbol(theta),_T("cr")) << _T(" - ") << symbol(alpha) << _T(")]");
            (*pPara) << _T("/{");
            if ( 0 < nImpactCases )
            {
               *pPara << _T("(IM)");
            }
            (*pPara) << Sub2(_T("W"),_T("g")) << _T("[(") << Sub2(_T("z"),_T("o")) << _T(" + ") << Sub2(_T("y"),_T("r")) << _T(")") << Sub2(symbol(theta),_T("cr")) << _T(" ") << strWindSign.c_str() << _T(" ") << Sub2(_T("z"),_T("wind")) << _T(" ");
            if ( slope == stbTypes::MaxSuper )
            {
               *pPara << strCFSign.c_str() << _T(" ") << Sub2(_T("z"),_T("cf"));
            }
            *pPara << _T(" + ") << Sub2(_T("e"),_T("i")) << _T("]") << _T(" ") << strWindSign.c_str() << _T(" ") << Sub2(_T("M"),_T("otwind"));
            if ( slope == stbTypes::MaxSuper )
            {
               *pPara << _T(" ") << strCFSign.c_str() << _T(" ") << Sub2(_T("M"),_T("otcf"));
            }
            *pPara << _T("}") << rptNewLine;

            col = 0;
            if ( lpszLocColumnLabel )
            {
               (*pCrackingTable)(0,col++) << COLHDR(rptRcStringLiteral(lpszLocColumnLabel),rptLengthUnitTag,pDisplayUnits->SpanLength);
            }
            else
            {
               (*pCrackingTable)(0,col++) << COLHDR(_T("Dist from left") << rptNewLine << _T("end of girder"),rptLengthUnitTag,pDisplayUnits->SpanLength);
            }
            (*pCrackingTable)(0,col++) << COLHDR(Sub2(_T("M"),_T("cr")),rptMomentUnitTag,pDisplayUnits->Moment);
            (*pCrackingTable)(0,col++) << _T("Cracked Flange");
            (*pCrackingTable)(0,col++) << COLHDR(Sub2(symbol(theta),_T("cr")),rptAngleUnitTag,pDisplayUnits->RadAngle);
            (*pCrackingTable)(0,col++) << Sub2(_T("FS"),_T("cr"));


            rptRcTable* pRebarTable = nullptr;
            if ( segment )
            {
               pRebarTable = rptStyleManager::CreateDefaultTable(7,_T("Bonded reinforcement requirements [C5.9.4.1.2]"));
            
               col = 0;
               if ( lpszLocColumnLabel )
               {
                  (*pRebarTable)(0,col++) << COLHDR(rptRcStringLiteral(lpszLocColumnLabel),rptLengthUnitTag,pDisplayUnits->SpanLength);
               }
               else
               {
                  (*pRebarTable)(0,col++) << COLHDR(_T("Dist from left") << rptNewLine << _T("end of girder"),rptLengthUnitTag,pDisplayUnits->SpanLength);
               }
               (*pRebarTable)(0,col++) << COLHDR(Sub2(_T("Y"),_T("na")), rptLengthUnitTag, pDisplayUnits->ComponentDim);
               (*pRebarTable)(0,col++) << _T("Slope NA");
               (*pRebarTable)(0,col++) << COLHDR(Sub2(_T("A"),_T("t")), rptAreaUnitTag,pDisplayUnits->Area);
               (*pRebarTable)(0,col++) << COLHDR(_T("T"),rptForceUnitTag,pDisplayUnits->GeneralForce);
               (*pRebarTable)(0,col++) << COLHDR(Sub2(_T("A"),_T("s")) << rptNewLine << _T("Provided") << Super(_T("*")), rptAreaUnitTag,pDisplayUnits->Area);
               (*pRebarTable)(0,col++) << COLHDR(Sub2(_T("A"),_T("s")) << rptNewLine << _T("Required") << Super(_T("**")), rptAreaUnitTag,pDisplayUnits->Area);
            }

            
            RowIndexType srow = pTotalStressTable->GetNumberOfHeaderRows();
            RowIndexType crow = pCrackingTable->GetNumberOfHeaderRows();
            RowIndexType rrow = (pRebarTable ? pRebarTable->GetNumberOfHeaderRows() : 0);
            for( const auto& sectionResult : pResults->vSectionResults)
            {
               col = 0;

               const stbIAnalysisPoint* pAnalysisPoint = pStabilityProblem->GetAnalysisPoint(sectionResult.AnalysisPointIndex);
               (*pTotalStressTable)(srow,col++) << rptRcStringLiteral(pAnalysisPoint->AsString(pDisplayUnits->SpanLength,offset,false));

               (*pTotalStressTable)(srow,col++) << stress.SetValue(sectionResult.fDirect[slope][impactDir[impactCase]][wind][stbTypes::TopLeft]);
               (*pTotalStressTable)(srow,col++) << stress.SetValue(sectionResult.fDirect[slope][impactDir[impactCase]][wind][stbTypes::TopRight]);
               (*pTotalStressTable)(srow,col++) << stress.SetValue(sectionResult.fDirect[slope][impactDir[impactCase]][wind][stbTypes::BottomLeft]);
               (*pTotalStressTable)(srow,col++) << stress.SetValue(sectionResult.fDirect[slope][impactDir[impactCase]][wind][stbTypes::BottomRight]);

               (*pTotalStressTable)(srow,col++) << stress.SetValue(sectionResult.fTilt[slope][impactDir[impactCase]][wind][stbTypes::TopLeft]);
               (*pTotalStressTable)(srow,col++) << stress.SetValue(sectionResult.fTilt[slope][impactDir[impactCase]][wind][stbTypes::TopRight]);
               (*pTotalStressTable)(srow,col++) << stress.SetValue(sectionResult.fTilt[slope][impactDir[impactCase]][wind][stbTypes::BottomLeft]);
               (*pTotalStressTable)(srow,col++) << stress.SetValue(sectionResult.fTilt[slope][impactDir[impactCase]][wind][stbTypes::BottomRight]);

               (*pTotalStressTable)(srow,col++) << stress.SetValue(sectionResult.f[slope][impactDir[impactCase]][wind][stbTypes::TopLeft]);
               (*pTotalStressTable)(srow,col++) << stress.SetValue(sectionResult.f[slope][impactDir[impactCase]][wind][stbTypes::TopRight]);
               (*pTotalStressTable)(srow,col++) << stress.SetValue(sectionResult.f[slope][impactDir[impactCase]][wind][stbTypes::BottomLeft]);
               (*pTotalStressTable)(srow,col++) << stress.SetValue(sectionResult.f[slope][impactDir[impactCase]][wind][stbTypes::BottomRight]);

               srow++;

               col = 0;
               (*pCrackingTable)(crow,col++) << rptRcStringLiteral(pAnalysisPoint->AsString(pDisplayUnits->SpanLength,offset,false));
               (*pCrackingTable)(crow,col++) << moment.SetValue(sectionResult.Mcr[slope][impactDir[impactCase]][wind][sectionResult.CrackedFlange[slope][impactDir[impactCase]][wind]]);
               (*pCrackingTable)(crow,col++) << strFlange[sectionResult.CrackedFlange[slope][impactDir[impactCase]][wind]];
               (*pCrackingTable)(crow,col++) << crackAngle.SetValue(sectionResult.ThetaCrack[slope][impactDir[impactCase]][wind][sectionResult.CrackedFlange[slope][impactDir[impactCase]][wind]]);
               (*pCrackingTable)(crow,col++) << scalar.SetValue(sectionResult.FScr[slope][impactDir[impactCase]][wind]);

               crow++;

               if ( segment )
               {
                  col = 0;
                  (*pRebarTable)(rrow,col++) << rptRcStringLiteral(pAnalysisPoint->AsString(pDisplayUnits->SpanLength,offset,false));
                  if ( sectionResult.AsRequired[slope][impactDir[impactCase]][wind] < 0 )
                  {
                     (*pRebarTable)(rrow,col++) << _T("-");
                     (*pRebarTable)(rrow,col++) << _T("-");
                     (*pRebarTable)(rrow,col++) << _T("-");
                     (*pRebarTable)(rrow,col++) << _T("-");
                     (*pRebarTable)(rrow,col++) << _T("-");
                     (*pRebarTable)(rrow,col++) << _T("-");
                  }
                  else
                  {
                     (*pRebarTable)(rrow,col++) << shortLength.SetValue(sectionResult.Yna[slope][impactDir[impactCase]][wind]);
                     (*pRebarTable)(rrow,col++) << scalar.SetValue(sectionResult.NAslope[slope][impactDir[impactCase]][wind]);
                     (*pRebarTable)(rrow,col++) << area.SetValue(sectionResult.AreaTension[slope][impactDir[impactCase]][wind]);
                     (*pRebarTable)(rrow,col++) << force.SetValue(sectionResult.T[slope][impactDir[impactCase]][wind]);
                     (*pRebarTable)(rrow,col++) << area.SetValue(sectionResult.AsProvided[slope][impactDir[impactCase]][wind]);
                     (*pRebarTable)(rrow,col++) << area.SetValue(sectionResult.AsRequired[slope][impactDir[impactCase]][wind]);
                  }
                  
                  rrow++;
               }
            } // next section

            pPara = new rptParagraph(rptStyleManager::GetSubheadingStyle());
            *pChapter << pPara;
            *pPara << _T("Factor of Safety Against Failure") << rptNewLine;
            pPara = new rptParagraph;
            *pChapter << pPara;
            *pPara << Sub2(symbol(theta),_T("max")) << _T(" = ") << symbol(alpha) << _T(" + ") << symbol(ROOT) << _T("{") << Super2(symbol(alpha),_T("2")) << _T("[") << Sub2(_T("e"),_T("i")) << _T(" + ") << Sub2(_T("M"),_T("ot")) << _T("/") << Sub2(_T("W"),_T("g")) << _T(" + (") << Sub2(_T("z"),_T("o")) << _T(" ") << strWindSign.c_str() << _T(" ") << Sub2(_T("z"),_T("wind"));
            if ( slope == stbTypes::MaxSuper )
            {
               *pPara << _T(" ") << strOppCFSign.c_str() << _T(" ") << Sub2(_T("z"),_T("cf"));
            }
            *pPara << _T(" + ") << Sub2(_T("y"),_T("r")) << _T(")") << symbol(alpha) << _T("]/[2.5(") << Sub2(_T("z"),_T("o")) << _T(" ") << strWindSign.c_str() << _T(" ") << Sub2(_T("z"),_T("wind"));
            if ( slope == stbTypes::MaxSuper )
            {
               *pPara << _T(" ") << strOppCFSign.c_str() << _T(" ") << Sub2(_T("z"),_T("cf"));
            }
            *pPara << _T(")]} ") << symbol(LTE) << _T(" 0.4 radians") << rptNewLine;

            *pPara << Sub2(symbol(theta),_T("max")) << _T(" = ") << tiltAngle.SetValue(pResults->ThetaMax[slope][impactDir[impactCase]][wind]) << rptNewLine;
            *pPara << Sub2(_T("FS"),_T("f")) << _T(" = Factor of Safety Against Failure = [") << Sub2(_T("K"),symbol(theta)) << _T("(") << Sub2(symbol(theta),_T("max")) << _T(" - ") << symbol(alpha) << _T(")]");
            *pPara << _T("/{");
            if ( 0 < nImpactCases )
            {
               *pPara << _T("(IM)");
            }
            *pPara << Sub2(_T("W"),_T("g")) << _T("[(") << Sub2(_T("z"),_T("o")) << _T(" ") << strWindSign.c_str() << _T(" ") Sub2(_T("z"),_T("wind"));
            if ( slope == stbTypes::MaxSuper )
            {
               *pPara << _T(" ") << strOppCFSign.c_str() << _T(" ") << Sub2(_T("z"),_T("cf"));
            }
            *pPara << _T(")") << Sub2(symbol(theta),_T("max")) << _T("(1 + 2.5") << Sub2(symbol(theta),_T("max")) << _T(")") << _T(" + ") << Sub2(_T("y"),_T("r")) << Sub2(symbol(theta),_T("max")) << _T(" + ") << Sub2(_T("e"),_T("i")) << _T("]") << _T(" ") << strWindSign.c_str() << _T(" ") << Sub2(_T("M"),_T("otwind"));
            if ( slope == stbTypes::MaxSuper )
            {
               *pPara << _T(" ") << strCFSign.c_str() << _T(" ") << Sub2(_T("M"),_T("otcf"));
            }
            *pPara << _T("}") << rptNewLine;
            *pPara << Sub2(_T("FS"),_T("f")) << _T(" = ") << scalar.SetValue(pResults->FsFailure[slope][impactDir[impactCase]][wind]) << rptNewLine; 
            *pPara << _T("If ") << Sub2(_T("FS"),_T("f")) << _T(" is less than ") << Sub2(_T("FS"),_T("cr")) << _T(" then ") << Sub2(_T("FS"),_T("f")) << _T(" = ") << Sub2(_T("FS"),_T("cr")) << _T(". ");
            *pPara << Sub2(_T("FS"),_T("f")) << _T(" = ") << scalar.SetValue(pResults->FsFailure[slope][impactDir[impactCase]][wind]) << _T(", ") << Sub2(_T("FS"),_T("cr")) << _T(" = ") << scalar.SetValue(pResults->MinFScr[slope]) << _T(", therefore ") << Sub2(_T("FS"),_T("f")) << _T(" = ") << scalar.SetValue(pResults->AdjFsFailure[slope][impactDir[impactCase]][wind]) << rptNewLine; 
            *pPara << rptNewLine;

            pPara = new rptParagraph(rptStyleManager::GetSubheadingStyle());
            *pChapter << pPara;
            *pPara << _T("Factor of Safety Against Rollover") << rptNewLine;
            pPara = new rptParagraph;
            *pChapter << pPara;

            *pPara << Sub2(symbol(theta),_T("ro")) << _T(" = tilt angle at roll over = ");
            *pPara << _T("[");
            if ( 0 < nImpactCases )
            {
               *pPara << _T("(IM)");
            }
            *pPara << Sub2(_T("W"),_T("g")) << _T("(") << Sub2(_T("W"),_T("cc")) << _T("/2") << _T(" - ") << Sub2(_T("H"),_T("rs")) << symbol(alpha) << _T(" - ") << Sub2(_T("e"),_T("bunk")) << _T(") ") << strWindSign.c_str() << _T(" ") << Sub2(_T("M"),_T("rowind"));
            if ( slope == stbTypes::MaxSuper )
            {
               *pPara << _T(" ") << strCFSign.c_str() << _T(" ") << Sub2(_T("M"),_T("rocf"));
            }
            *pPara << _T("]");
            *pPara << _T("/") << Sub2(_T("K"),symbol(theta)) << _T(" + ") << symbol(alpha) << rptNewLine;
            *pPara << Sub2(symbol(theta),_T("ro")) << _T(" = ") << tiltAngle.SetValue(pResults->ThetaRollover[slope][impactDir[impactCase]][wind]) << rptNewLine;
            *pPara << Sub2(_T("FS"),_T("r")) << _T(" = Factor of Safety Against Rollover = [") << Sub2(_T("K"),symbol(theta)) << _T("(") << Sub2(symbol(theta),_T("ro")) << _T(" - ") << symbol(alpha) << _T(")]");
            *pPara << _T("/{");
            if ( 0 < nImpactCases )
            {
               *pPara << _T("(IM)");
            }
            *pPara << Sub2(_T("W"),_T("g")) << _T("[(") << Sub2(_T("z"),_T("o")) <<_T("(1 + 2.5") << Sub2(symbol(theta),_T("ro")) << _T(") + ") << Sub2(_T("y"),_T("r")) << _T(")") << Sub2(symbol(theta),_T("ro")) << _T(" + (");
            if ( wind == stbTypes::Right )
            {
               *pPara << strWindSign.c_str();
            }
            *pPara << _T(" ") << Sub2(_T("z"),_T("wind"));
            if ( slope == stbTypes::MaxSuper )
            {
               *pPara << _T(" ") << strCFSign.c_str() << _T(" ") << Sub2(_T("z"),_T("cf"));
            }
            *pPara << _T(")") << _T("(1 + 2.5") << Sub2(symbol(theta),_T("ro")) << _T(") + ") << Sub2(_T("e"),_T("i")) << _T("]") << _T(" ") << strWindSign.c_str() << _T(" ") << Sub2(_T("M"),_T("rowind"));
            if ( slope == stbTypes::MaxSuper )
            {
               *pPara << _T(" ") << strCFSign.c_str() << _T(" ") << Sub2(_T("M"),_T("rocf"));
            }
            *pPara << _T("}") << rptNewLine;
            *pPara << Sub2(_T("FS"),_T("r")) << _T(" = ") << scalar.SetValue(pResults->FsRollover[slope][impactDir[impactCase]][wind]) << rptNewLine; 
            *pPara << rptNewLine;

            if ( segment )
            {
               (*pPara) << pRebarTable << rptNewLine;
               (*pPara) << _T("The neutral axis is defined by its location with respect to the top center of the girder (") << Sub2(_T("Y"),_T("na")) << _T(") and its slope (Slope NA)") << rptNewLine;
               (*pPara) << Super(_T("*")) << _T(" provided reinforcement must be fully developed and lie within the tension area of the section before they are considered") << rptNewLine;
               (*pPara) << Super(_T("**")) << _T(" required reinforcement is the minimum area of sufficiently bonded reinforcement needed to use the alternative tensile stress limit") << rptNewLine;

               *pPara << rptNewLine;
            }
         } // next wind direction
      } // next impact direction

      pPara = new rptParagraph(rptStyleManager::GetSubheadingStyle());
      *pChapter << pPara;
      *pPara << _T("Controlling Factors of Safety") << rptNewLine;
      pPara = new rptParagraph;
      *pChapter << pPara;

      CString strTitle;

      if ( bLabelImpact && !bLabelWind )
      {
         // more than one impact case but no wind
         strTitle.Format(_T("%s"),strImpact[impactIndex[pResults->FScrImpactDirection[slope]]]);
      }
      else if ( !bLabelImpact && bLabelWind )
      {
         // only one impact case and wind cases
         strTitle.Format(_T("Wind towards the %s"),strWindDir[pResults->FScrWindDirection[slope]]);
      }
      else if ( bLabelImpact && bLabelWind )
      {
         // more than one impact case and wind cases
         strTitle.Format(_T("%s, Wind towards the %s"),strImpact[impactIndex[pResults->FScrImpactDirection[slope]]],strWindDir[pResults->FScrWindDirection[slope]]);
      }
      else
      {
         strTitle = _T("");
      }

      longLength.ShowUnitTag(true);
      *pPara << _T("The minimum factor of safety against cracking, ") << rptRcStringLiteral(pStabilityProblem->GetAnalysisPoint(pResults->vSectionResults[pResults->FScrAnalysisPointIndex[slope]].AnalysisPointIndex)->AsString(pDisplayUnits->SpanLength,offset,true)) << _T(" ");
      
      *pPara << strFlange[pResults->vSectionResults[pResults->FScrAnalysisPointIndex[slope]].CrackedFlange[slope][pResults->FScrImpactDirection[slope]][pResults->FScrWindDirection[slope]]] << _T(" flange tip");
      if (strTitle.IsEmpty() )
      {
         *pPara << rptNewLine;
      }
      else
      {
         *pPara << _T(" with ") << strTitle << rptNewLine;
      }
      *pPara << Sub2(_T("FS"),_T("cr")) << _T(" Min = ") << scalar.SetValue(pResults->MinFScr[slope]) << rptNewLine;

      *pPara << rptNewLine;

      *pPara << _T("The minimum factor of safety against failure, ") << strTitle << rptNewLine;
      *pPara << Sub2(_T("FS"),_T("f")) << _T(" Min = ") << scalar.SetValue(pResults->MinAdjFsFailure[slope]) << rptNewLine;

      *pPara << rptNewLine;

      *pPara << _T("The minimum factor of safety against roll over, ") << strTitle << rptNewLine;
      *pPara << Sub2(_T("FS"),_T("r")) << _T(" Min = ") << scalar.SetValue(pResults->MinFsRollover[slope]) << rptNewLine;
   } // next slope type
}
