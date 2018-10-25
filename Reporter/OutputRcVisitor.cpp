///////////////////////////////////////////////////////////////////////
// Reporter - Report Creation and Representation Library
// Copyright © 1999-2015  Washington State Department of Transportation
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

#include <Reporter\ReporterLib.h>
#include <Reporter\OutputRcVisitor.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


/****************************************************************************
CLASS
   rptOutputRcVisitor
****************************************************************************/


////////////////////////// PUBLIC     ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
rptOutputRcVisitor::rptOutputRcVisitor(std::_tostream* pMyOstream)
{
   m_pOstream = pMyOstream;
}


rptOutputRcVisitor::~rptOutputRcVisitor()
{
}

//======================== OPERATORS  =======================================




//======================== OPERATIONS =======================================

//======================== ACCESS     =======================================
//======================== INQUIRY    =======================================

////////////////////////// PROTECTED  ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
//======================== OPERATORS  =======================================
//======================== OPERATIONS =======================================

Uint8 rptOutputRcVisitor::GetRomanForGreek(rptRcSymbol::SymbolType sym)
{

   Uint8 symlet='0';

   switch (sym)
   { 
   case rptRcSymbol::alpha:
      symlet='a';
      break;
   case rptRcSymbol::ALPHA:
      symlet='A';
      break;
   case rptRcSymbol::beta:
      symlet='b';
      break;
   case rptRcSymbol::BETA:
      symlet='B';
      break;
   case rptRcSymbol::chi:
      symlet='c';
      break;
   case rptRcSymbol::CHI:
      symlet='C';
      break;
   case rptRcSymbol::delta:
      symlet='d';
      break;
   case rptRcSymbol::DELTA:
      symlet='D';
      break;
   case rptRcSymbol::epsilon:
      symlet='e';
      break;
   case rptRcSymbol::EPSILON:
      symlet='E';
      break;
   case rptRcSymbol::eta:
      symlet='h';
      break;
   case rptRcSymbol::ETA:
      symlet='H';
      break;
   case rptRcSymbol::gamma:
      symlet='g';
      break;
   case rptRcSymbol::GAMMA:
      symlet='G';
      break;
   case rptRcSymbol::kappa:
      symlet=107;
      break;
   case rptRcSymbol::KAPPA:
      symlet=75;
      break;
   case rptRcSymbol::lambda:
      symlet=108;
      break;
   case rptRcSymbol::LAMBDA:
      symlet=76;
      break;
   case rptRcSymbol::mu:
      symlet=109;
      break;
   case rptRcSymbol::MU:
      symlet=77;
      break;
   case rptRcSymbol::nu:
      symlet='n';
      break;
   case rptRcSymbol::NU:
      symlet='n';
      break;
   case rptRcSymbol::varphi:
      symlet=0x6A;
      break;
   case rptRcSymbol::phi:
      symlet='f';
      break;
   case rptRcSymbol::PHI:
      symlet='F';
      break;
   case rptRcSymbol::rho:
      symlet='r';
      break;
   case rptRcSymbol::RHO:
      symlet='R';
      break;
   case rptRcSymbol::omega:
      symlet='w';
      break;
   case rptRcSymbol::OMEGA:
      symlet='W';
      break;
   case rptRcSymbol::pi:
      symlet='p';
      break;
   case rptRcSymbol::PI:
      symlet='P';
      break;
   case rptRcSymbol::psi:
      symlet='y';
      break;
   case rptRcSymbol::PSI:
      symlet='Y';
      break;
   case rptRcSymbol::sigma:
      symlet='s';
      break;
   case rptRcSymbol::SIGMA:
      symlet='S';
      break;
   case rptRcSymbol::theta:
      symlet='q';
      break;
   case rptRcSymbol::THETA:
      symlet='Q';
      break;
   case rptRcSymbol::QED:
      symlet=92;
      break;   
   case rptRcSymbol::INFINITY:
      symlet=165;
      break;  
   case rptRcSymbol::DEGREES:
      symlet=176;
      break;  
   case rptRcSymbol::OMICRON:
      symlet=181;
      break;  
   case rptRcSymbol::PARTIAL:
      symlet=182;
      break;  
   case rptRcSymbol::DOT:
      symlet=183;
      break;  
   case rptRcSymbol::DIAMOND:
      symlet=224;
      break;  
   case rptRcSymbol::FUNCTION:
      symlet=166;
      break;  
   case rptRcSymbol::PRODUCT:
      symlet=213;
      break;  
   case rptRcSymbol::SUM:
      symlet=229;
      break;  
   case rptRcSymbol::INTEGRAL:
      symlet=242;
      break;  
   case rptRcSymbol::ROOT:
      symlet=214;
      break;  
   case rptRcSymbol::TIMES:
      symlet=180;
      break;  
   case rptRcSymbol::DIVIDE:
      symlet=184;
      break;  
   case rptRcSymbol::LTE:
      symlet=163;
      break;  
   case rptRcSymbol::GTE:
      symlet=179;
      break;  
   case rptRcSymbol::NE:
      symlet=185;
      break;  
   case rptRcSymbol::EXACTLY:
      symlet=186;
      break;  
   case rptRcSymbol::PLUS_MINUS:
      symlet=177;
      break;  
   case rptRcSymbol::ABOUT_EQUAL:
      symlet=64;
      break;   
   case rptRcSymbol::APPROXIMATELY:
      symlet=187;
      break;  
   case rptRcSymbol::ELLIPSES:
      symlet=188;
      break;  
   case rptRcSymbol::VERTICAL_BAR:
      symlet=189;
      break;  
   case rptRcSymbol::HORIZONTAL_BAR:
      symlet=190;
      break;  
   case rptRcSymbol::ENTER:
      symlet=191;
      break;  
   case rptRcSymbol::EMPTY_SET:
      symlet=198;
      break;
   case rptRcSymbol::REGISTER:
      symlet=210;
      break;  
   case rptRcSymbol::COPYRIGHT:
      symlet=211;
      break;  
   case rptRcSymbol::TRADEMARK:
      symlet=212;
      break;  
   case rptRcSymbol::LEFT_RIGHT_SINGLE_ARROW:
      symlet=171;
      break;  
   case rptRcSymbol::LEFT_SINGLE_ARROW:
      symlet=172;
      break;  
   case rptRcSymbol::UP_SINGLE_ARROW:
      symlet=173;
      break;  
   case rptRcSymbol::RIGHT_SINGLE_ARROW:
      symlet=174;
      break;  
   case rptRcSymbol::DOWN_SINGLE_ARROW:
      symlet=175;
      break;  
   case rptRcSymbol::LEFT_RIGHT_DOUBLE_ARROW:
      symlet=219;
      break;  
   case rptRcSymbol::LEFT_DOUBLE_ARROW:
      symlet=220;
      break;  
   case rptRcSymbol::UP_DOUBLE_ARROW:
      symlet=221;
      break;  
   case rptRcSymbol::RIGHT_DOUBLE_ARROW:
      symlet=222;
      break;  
   case rptRcSymbol::DOWN_DOUBLE_ARROW:
      symlet=223;
      break;  
   case rptRcSymbol::NORMAL:
      symlet=94;
      break;  

   default:
      CHECKX(0,_T("Error - Bad Symbol Type"));
   }

   return symlet;
}

//======================== ACCESS     =======================================
//======================== INQUIRY    =======================================

////////////////////////// PRIVATE    ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
//======================== OPERATORS  =======================================
//======================== OPERATIONS =======================================
//======================== ACCESS     =======================================
//======================== INQUERY    =======================================

