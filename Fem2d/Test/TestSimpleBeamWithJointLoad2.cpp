///////////////////////////////////////////////////////////////////////
// Fem2D - Two-dimensional Beam Analysis Engine
// Copyright © 1999-2017  Washington State Department of Transportation
//                        Bridge and Structures Office
//
// This library is a part of the Washington Bridge Foundation Libraries
// and was developed as part of the Alternate Route Project
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the Alternate Route Library Open Source License as 
// published by the Washington State Department of Transportation,
// Bridge and Structures Office.
//
// This program is distributed in the hope that it will be useful,
// but is distributed AS IS, WITHOUT ANY WARRANTY; without even the
// implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR 
// PURPOSE.  See the Alternate Route Library Open Source License for more details.
//
// You should have received a copy of the Alternate Route Library Open Source License
// along with this program; if not, write to the Washington State
// Department of Transportation, Bridge and Structures Office,
// P.O. Box 47340, Olympia, WA 98503, USA or e-mail
// Bridge_Support@wsdot.wa.gov
///////////////////////////////////////////////////////////////////////
// TestSimpleBeamWithJointLoad.cpp: implementation of the CTestSimpleBeamWithJointLoad class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "TestSimpleBeamWithJointLoad.h"
#include <MathEx.h>
#include <iostream> 

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//////////////////////////////////////////////////////////////////////
// File broken in half due to compiler limits
//////////////////////////////////////////////////////////////////////
void CTestSimpleBeamWithJointLoad::Test2(CComPtr<IFem2dModel>& pmodel,
                                          CComPtr<IFem2dJoint>& pJoint0,
                                          CComPtr<IFem2dJoint>& pJoint4,
                                          CComPtr<IFem2dJoint>& pJoint8,
                                          CComPtr<IFem2dMember>& pMember1,
                                          CComPtr<IFem2dMember>& pMember2,
                                          CComPtr<IFem2dJointLoad>& pJointLoad,
                                          CComQIPtr<IFem2dModelResults>& presults,
                                          CComQIPtr<IFem2dModelResultsEx>& presultsex)
{

//////////////////////////////////////////////////////////////////////////////////
// ================================================================================
// next let's rotate the model 135 degrees clockwise
   TRY_TEST_MC(pJoint4->put_X(-2.8284271));
   TRY_TEST_HR(pJoint4->put_Y(2.8284271));
   TRY_TEST_MC(pJoint8->put_X(-5.6568542));
   TRY_TEST_HR(pJoint8->put_Y(5.6568542));

   Float64 l;
   Float64 dx, dy, rz;
   Float64 fx, fy, mz;
   Float64 sfx, sfy, smz, efx, efy, emz;
   Float64 sdx, sdy, srz, edx, edy, erz;

   pMember1->get_Length(&l);
   TRY_TEST_B(IsEqual(l, 4.0));
   pMember2->get_Length(&l);
   TRY_TEST_B(IsEqual(l, 4.0));

   // change orientation of point load to be normal to rotated structure
   TRY_TEST_HR(pJointLoad->put_Fx(2.8284271));
   TRY_TEST_LC(pJointLoad->put_Fy(2.8284271));

   // get joint Deflections
   TRY_TEST_HR(presults->ComputeJointDeflections(0, 0, &dx, &dy, &rz));
   TRY_TEST_B( IsEqual(dx, 0.0) );
   TRY_TEST_B( IsEqual(dy, 0.0) );
   TRY_TEST_B( IsEqual(rz, -2.2857142857143) );
   TRY_TEST_HR(presults->ComputeJointDeflections(0, 4, &dx, &dy, &rz));
   TRY_TEST_B( IsEqual(dx,  4.30998419) );
   TRY_TEST_B( IsEqual(dy,  4.30998419));
   TRY_TEST_B( IsEqual(rz, 0.0) );
   TRY_TEST_HR(presults->ComputeJointDeflections(0, 8, &dx, &dy, &rz));
   TRY_TEST_B( IsEqual(dx, 0.0) );
   TRY_TEST_B( IsEqual(dy, 0.0) );
   TRY_TEST_B( IsEqual(rz, 2.2857142857143) );

   // get member end forces
   TRY_TEST_HR(presults->ComputeMemberForces(0, 1, &sfx, &sfy, &smz, &efx, &efy, &emz));
   TRY_TEST_B( IsEqual(sfx, 0.0) );
   TRY_TEST_B( IsEqual(sfy, 2.0));
   TRY_TEST_B( IsEqual(smz, 0.0));
   TRY_TEST_B( IsEqual(efx, 0.0));
   TRY_TEST_B( IsEqual(efy, -2.0));
   TRY_TEST_B( IsEqual(emz, 8.0));
   TRY_TEST_HR(presults->ComputeMemberForces(0, 2, &sfx, &sfy, &smz, &efx, &efy, &emz));
   TRY_TEST_B( IsEqual(sfx,  0.0) );
   TRY_TEST_B( IsEqual(sfy, -2.0));
   TRY_TEST_B( IsEqual(smz, -8.0));
   TRY_TEST_B( IsEqual(efx,  0.0));
   TRY_TEST_B( IsEqual(efy,  2.0));
   TRY_TEST_B( IsEqual(emz,  0.0));

   TRY_TEST_HR(presultsex->ComputeMemberForcesEx(0, 1, lotMember, &sfx, &sfy, &smz, &efx, &efy, &emz));
   TRY_TEST_B( IsEqual(sfx, 0.0) );
   TRY_TEST_B( IsEqual(sfy, 2.0));
   TRY_TEST_B( IsEqual(smz, 0.0));
   TRY_TEST_B( IsEqual(efx, 0.0));
   TRY_TEST_B( IsEqual(efy, -2.0));
   TRY_TEST_B( IsEqual(emz, 8.0));
   TRY_TEST_HR(presultsex->ComputeMemberForcesEx(0, 2, lotMember, &sfx, &sfy, &smz, &efx, &efy, &emz));
   TRY_TEST_B( IsEqual(sfx,  0.0) );
   TRY_TEST_B( IsEqual(sfy, -2.0));
   TRY_TEST_B( IsEqual(smz, -8.0));
   TRY_TEST_B( IsEqual(efx,  0.0));
   TRY_TEST_B( IsEqual(efy,  2.0));
   TRY_TEST_B( IsEqual(emz,  0.0));

   TRY_TEST_HR(presultsex->ComputeMemberForcesEx(0, 1, lotGlobal, &sfx, &sfy, &smz, &efx, &efy, &emz));
   TRY_TEST_B( IsEqual(sfx, -1.41421356));
   TRY_TEST_B( IsEqual(sfy, -1.41421356));
   TRY_TEST_B( IsEqual(smz,  0.0));
   TRY_TEST_B( IsEqual(efx,  1.41421355));
   TRY_TEST_B( IsEqual(efy,  1.41421355));
   TRY_TEST_B( IsEqual(emz, 8.0));
   TRY_TEST_HR(presultsex->ComputeMemberForcesEx(0, 2, lotGlobal, &sfx, &sfy, &smz, &efx, &efy, &emz));
   TRY_TEST_B( IsEqual(sfx,  1.41421355) );
   TRY_TEST_B( IsEqual(sfy,  1.41421355));
   TRY_TEST_B( IsEqual(smz, -8.0));
   TRY_TEST_B( IsEqual(efx, -1.41421356));
   TRY_TEST_B( IsEqual(efy, -1.41421356));
   TRY_TEST_B( IsEqual(emz,  0.0));

   TRY_TEST_HR(presults->ComputeReactions(0, 0, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,  -1.41421356));
   TRY_TEST_B( IsEqual(fy,  -1.41421356));
   TRY_TEST_B( IsEqual(mz,  0.0));
   TRY_TEST_HR(presults->ComputeReactions(0, 4, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,  0.0));
   TRY_TEST_B( IsEqual(fy,  0.0));
   TRY_TEST_B( IsEqual(mz,  0.0));
   TRY_TEST_HR(presults->ComputeReactions(0, 8, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,  -1.41421356));
   TRY_TEST_B( IsEqual(fy,  -1.41421356));
   TRY_TEST_B( IsEqual(mz,  0.0));

   // get merber end forces
   TRY_TEST_HR(presults->ComputeMemberDeflections(0, 1, &sdx, &sdy, &srz, &edx, &edy, &erz));
   TRY_TEST_B( IsEqual(sdx,   0.0) );
   TRY_TEST_B( IsEqual(sdy,   0.0));
   TRY_TEST_B( IsEqual(srz, -2.2857142857143));
   TRY_TEST_B( IsEqual(edx,   0.0));
   TRY_TEST_B( IsEqual(edy, -6.0952380952381));
   TRY_TEST_B( IsEqual(erz,   0.0));
   TRY_TEST_HR(presults->ComputeMemberDeflections(0, 2, &sdx, &sdy, &srz, &edx, &edy, &erz));
   TRY_TEST_B( IsEqual(sdx,   0.0) );
   TRY_TEST_B( IsEqual(sdy,  -6.0952380952381));
   TRY_TEST_B( IsEqual(srz,   0.0));
   TRY_TEST_B( IsEqual(edx,   0.0));
   TRY_TEST_B( IsEqual(edy,   0.0));
   TRY_TEST_B( IsEqual(erz,   2.2857142857143));

   // look at Deflections
   TRY_TEST_HR(presults->ComputePOIDeflections(0, 10,  lotMember, &dx, &dy, &rz));
   TRY_TEST_B( IsEqual(dx, 0.0) );
   TRY_TEST_B( IsEqual(dy, 0.0) );
   TRY_TEST_B( IsEqual(rz, -2.2857142857143) );
   TRY_TEST_HR(presults->ComputePOIDeflections(0, 15,  lotMember, &dx, &dy, &rz));
   TRY_TEST_B( IsEqual(dx, 0.0) );
   TRY_TEST_B( IsEqual(dy, -4.1904761904762));
   TRY_TEST_B( IsEqual(rz, -1.71428) );
   TRY_TEST_HR(presults->ComputePOIDeflections(0, 12,  lotMember, &dx, &dy, &rz));
   TRY_TEST_B( IsEqual(dx, 0.0) );
   TRY_TEST_B( IsEqual(dy, -6.0952380952381));
   TRY_TEST_B( IsEqual(rz, 0.0) );
   TRY_TEST_HR(presults->ComputePOIDeflections(0, 20,  lotMember, &dx, &dy, &rz));
   TRY_TEST_B( IsEqual(dx, 0.0) );
   TRY_TEST_B( IsEqual(dy, -6.0952380952381));
   TRY_TEST_B( IsEqual(rz, 0.0) );
   TRY_TEST_HR(presults->ComputePOIDeflections(0, 25,  lotMember, &dx, &dy, &rz));
   TRY_TEST_B( IsEqual(dx, 0.0) );
   TRY_TEST_B( IsEqual(dy, -4.1904761904762));
   TRY_TEST_B( IsEqual(rz, 1.71428) );
   TRY_TEST_HR(presults->ComputePOIDeflections(0, 22,  lotMember, &dx, &dy, &rz));
   TRY_TEST_B( IsEqual(dx, 0.0) );
   TRY_TEST_B( IsEqual(dy, 0.0) );
   TRY_TEST_B( IsEqual(rz, 2.2857142857143) );

   TRY_TEST_HR(presults->ComputePOIDeflections(0, 10,  lotGlobal, &dx, &dy, &rz));
   TRY_TEST_B( IsEqual(dx, 0.0) );
   TRY_TEST_B( IsEqual(dy, 0.0) );
   TRY_TEST_B( IsEqual(rz, -2.2857142857143) );
   TRY_TEST_HR(presults->ComputePOIDeflections(0, 15,  lotGlobal, &dx, &dy, &rz));
   TRY_TEST_B( IsEqual(dx, 2.9631141) );
   TRY_TEST_B( IsEqual(dy, 2.9631141));
   TRY_TEST_B( IsEqual(rz, -1.71428) );
   TRY_TEST_HR(presults->ComputePOIDeflections(0, 12,  lotGlobal, &dx, &dy, &rz));
   TRY_TEST_B( IsEqual(dx, 4.3099842) );
   TRY_TEST_B( IsEqual(dy, 4.3099842));
   TRY_TEST_B( IsEqual(rz, 0.0) );
   TRY_TEST_HR(presults->ComputePOIDeflections(0, 20,  lotGlobal, &dx, &dy, &rz));
   TRY_TEST_B( IsEqual(dx, 4.3099842) );
   TRY_TEST_B( IsEqual(dy, 4.3099842));
   TRY_TEST_B( IsEqual(rz, 0.0) );
   TRY_TEST_HR(presults->ComputePOIDeflections(0, 25,  lotGlobal, &dx, &dy, &rz));
   TRY_TEST_B( IsEqual(dx, 2.9631141) );
   TRY_TEST_B( IsEqual(dy, 2.9631141));
   TRY_TEST_B( IsEqual(rz, 1.71428) );
   TRY_TEST_HR(presults->ComputePOIDeflections(0, 22,  lotGlobal, &dx, &dy, &rz));
   TRY_TEST_B( IsEqual(dx, 0.0) );
   TRY_TEST_B( IsEqual(dy, 0.0) );
   TRY_TEST_B( IsEqual(rz, 2.2857142857143) );

   // next look at poi forces at both faces and orientations
   TRY_TEST_HR(presults->ComputePOIForces(0, 10, mftLeft, lotGlobal, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,  1.41421355));
   TRY_TEST_B( IsEqual(fy,  1.41421355));
   TRY_TEST_B( IsEqual(mz,  0.0));
   TRY_TEST_HR(presults->ComputePOIForces(0, 10, mftRight, lotGlobal, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx, -1.41421355));
   TRY_TEST_B( IsEqual(fy, -1.41421355));
   TRY_TEST_B( IsEqual(mz,  0.0));
   TRY_TEST_HR(presults->ComputePOIForces(0, 10, mftLeft, lotMember, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,  0.0));
   TRY_TEST_B( IsEqual(fy, -2.0));
   TRY_TEST_B( IsEqual(mz,  0.0));
   TRY_TEST_HR(presults->ComputePOIForces(0, 10, mftRight, lotMember, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,  0.0));
   TRY_TEST_B( IsEqual(fy,  2.0));
   TRY_TEST_B( IsEqual(mz,  0.0));

   TRY_TEST_HR(presults->ComputePOIForces(0, 15, mftLeft, lotGlobal, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,   1.41421355));
   TRY_TEST_B( IsEqual(fy,   1.41421355));
   TRY_TEST_B( IsEqual(mz,   4.0));
   TRY_TEST_HR(presults->ComputePOIForces(0, 15, mftRight, lotGlobal, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,  -1.41421355));
   TRY_TEST_B( IsEqual(fy,  -1.41421355));
   TRY_TEST_B( IsEqual(mz,  -4.0));
   TRY_TEST_HR(presults->ComputePOIForces(0, 15, mftLeft, lotMember, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,  0.0));
   TRY_TEST_B( IsEqual(fy, -2.0));
   TRY_TEST_B( IsEqual(mz,  4.0));
   TRY_TEST_HR(presults->ComputePOIForces(0, 15, mftRight, lotMember, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,  0.0));
   TRY_TEST_B( IsEqual(fy,  2.0));
   TRY_TEST_B( IsEqual(mz, -4.0));

   TRY_TEST_HR(presults->ComputePOIForces(0, 12, mftLeft, lotGlobal, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,   1.41421355));
   TRY_TEST_B( IsEqual(fy,   1.41421355));
   TRY_TEST_B( IsEqual(mz,   8.0));
   TRY_TEST_HR(presults->ComputePOIForces(0, 12, mftRight, lotGlobal, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,  -1.41421355));
   TRY_TEST_B( IsEqual(fy,  -1.41421355));
   TRY_TEST_B( IsEqual(mz,  -8.0));
   TRY_TEST_HR(presults->ComputePOIForces(0, 12, mftLeft, lotMember, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,  0.0));
   TRY_TEST_B( IsEqual(fy, -2.0));
   TRY_TEST_B( IsEqual(mz,  8.0));
   TRY_TEST_HR(presults->ComputePOIForces(0, 12, mftRight, lotMember, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,  0.0));
   TRY_TEST_B( IsEqual(fy,  2.0));
   TRY_TEST_B( IsEqual(mz, -8.0));

   TRY_TEST_HR(presults->ComputePOIForces(0, 20, mftLeft, lotGlobal, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx, -1.41421355));
   TRY_TEST_B( IsEqual(fy, -1.41421355));
   TRY_TEST_B( IsEqual(mz,  8.0));
   TRY_TEST_HR(presults->ComputePOIForces(0, 20, mftRight, lotGlobal, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,   1.41421355));
   TRY_TEST_B( IsEqual(fy,   1.41421355));
   TRY_TEST_B( IsEqual(mz,  -8.0));
   TRY_TEST_HR(presults->ComputePOIForces(0, 20, mftLeft, lotMember, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,  0.0));
   TRY_TEST_B( IsEqual(fy,  2.0));
   TRY_TEST_B( IsEqual(mz,  8.0));
   TRY_TEST_HR(presults->ComputePOIForces(0, 20, mftRight, lotMember, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,   0.0));
   TRY_TEST_B( IsEqual(fy,  -2.0));
   TRY_TEST_B( IsEqual(mz,  -8.0));

   TRY_TEST_HR(presults->ComputePOIForces(0, 25, mftLeft, lotGlobal, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,  -1.41421355));
   TRY_TEST_B( IsEqual(fy,  -1.41421355));
   TRY_TEST_B( IsEqual(mz,   4.0));
   TRY_TEST_HR(presults->ComputePOIForces(0, 25, mftRight, lotGlobal, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,   1.41421355));
   TRY_TEST_B( IsEqual(fy,   1.41421355));
   TRY_TEST_B( IsEqual(mz,  -4.0));
   TRY_TEST_HR(presults->ComputePOIForces(0, 25, mftLeft, lotMember, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,  0.0));
   TRY_TEST_B( IsEqual(fy,  2.0));
   TRY_TEST_B( IsEqual(mz,  4.0));
   TRY_TEST_HR(presults->ComputePOIForces(0, 25, mftRight, lotMember, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,  0.0));
   TRY_TEST_B( IsEqual(fy, -2.0));
   TRY_TEST_B( IsEqual(mz, -4.0));

//////////////////////////////////////////////////////////////////////////////////
// ================================================================================
// Rotate the model 225 degrees clockwise
   TRY_TEST_HR(pJoint4->put_X(-2.8284271));
   TRY_TEST_MC(pJoint4->put_Y(-2.8284271));
   TRY_TEST_HR(pJoint8->put_X(-5.6568542));
   TRY_TEST_MC(pJoint8->put_Y(-5.6568542));

   pMember1->get_Length(&l);
   TRY_TEST_B(IsEqual(l, 4.0));
   pMember2->get_Length(&l);
   TRY_TEST_B(IsEqual(l, 4.0));

   // change orientation of point load to be normal to rotated structure
   TRY_TEST_LC(pJointLoad->put_Fx(-2.8284271));
   TRY_TEST_HR(pJointLoad->put_Fy(2.8284271));

   // get joint Deflections
   TRY_TEST_HR(presults->ComputeJointDeflections(0, 0, &dx, &dy, &rz));
   TRY_TEST_B( IsEqual(dx, 0.0) );
   TRY_TEST_B( IsEqual(dy, 0.0) );
   TRY_TEST_B( IsEqual(rz, -2.2857142857143) );
   TRY_TEST_HR(presults->ComputeJointDeflections(0, 4, &dx, &dy, &rz));
   TRY_TEST_B( IsEqual(dx, -4.30998419) );
   TRY_TEST_B( IsEqual(dy,  4.30998419));
   TRY_TEST_B( IsEqual(rz, 0.0) );
   TRY_TEST_HR(presults->ComputeJointDeflections(0, 8, &dx, &dy, &rz));
   TRY_TEST_B( IsEqual(dx, 0.0) );
   TRY_TEST_B( IsEqual(dy, 0.0) );
   TRY_TEST_B( IsEqual(rz, 2.2857142857143) );

   // get member end forces
   TRY_TEST_HR(presults->ComputeMemberForces(0, 1, &sfx, &sfy, &smz, &efx, &efy, &emz));
   TRY_TEST_B( IsEqual(sfx, 0.0) );
   TRY_TEST_B( IsEqual(sfy, 2.0));
   TRY_TEST_B( IsEqual(smz, 0.0));
   TRY_TEST_B( IsEqual(efx, 0.0));
   TRY_TEST_B( IsEqual(efy, -2.0));
   TRY_TEST_B( IsEqual(emz, 8.0));
   TRY_TEST_HR(presults->ComputeMemberForces(0, 2, &sfx, &sfy, &smz, &efx, &efy, &emz));
   TRY_TEST_B( IsEqual(sfx,  0.0) );
   TRY_TEST_B( IsEqual(sfy, -2.0));
   TRY_TEST_B( IsEqual(smz, -8.0));
   TRY_TEST_B( IsEqual(efx,  0.0));
   TRY_TEST_B( IsEqual(efy,  2.0));
   TRY_TEST_B( IsEqual(emz,  0.0));

   TRY_TEST_HR(presultsex->ComputeMemberForcesEx(0, 1, lotMember, &sfx, &sfy, &smz, &efx, &efy, &emz));
   TRY_TEST_B( IsEqual(sfx, 0.0) );
   TRY_TEST_B( IsEqual(sfy, 2.0));
   TRY_TEST_B( IsEqual(smz, 0.0));
   TRY_TEST_B( IsEqual(efx, 0.0));
   TRY_TEST_B( IsEqual(efy, -2.0));
   TRY_TEST_B( IsEqual(emz, 8.0));
   TRY_TEST_HR(presultsex->ComputeMemberForcesEx(0, 2, lotMember, &sfx, &sfy, &smz, &efx, &efy, &emz));
   TRY_TEST_B( IsEqual(sfx,  0.0) );
   TRY_TEST_B( IsEqual(sfy, -2.0));
   TRY_TEST_B( IsEqual(smz, -8.0));
   TRY_TEST_B( IsEqual(efx,  0.0));
   TRY_TEST_B( IsEqual(efy,  2.0));
   TRY_TEST_B( IsEqual(emz,  0.0));

   TRY_TEST_HR(presultsex->ComputeMemberForcesEx(0, 1, lotGlobal, &sfx, &sfy, &smz, &efx, &efy, &emz));
   TRY_TEST_B( IsEqual(sfx,  1.41421356));
   TRY_TEST_B( IsEqual(sfy, -1.41421356));
   TRY_TEST_B( IsEqual(smz,  0.0));
   TRY_TEST_B( IsEqual(efx, -1.41421355));
   TRY_TEST_B( IsEqual(efy,  1.41421355));
   TRY_TEST_B( IsEqual(emz, 8.0));
   TRY_TEST_HR(presultsex->ComputeMemberForcesEx(0, 2, lotGlobal, &sfx, &sfy, &smz, &efx, &efy, &emz));
   TRY_TEST_B( IsEqual(sfx, -1.41421355) );
   TRY_TEST_B( IsEqual(sfy,  1.41421355));
   TRY_TEST_B( IsEqual(smz, -8.0));
   TRY_TEST_B( IsEqual(efx,  1.41421356));
   TRY_TEST_B( IsEqual(efy, -1.41421356));
   TRY_TEST_B( IsEqual(emz,  0.0));

   TRY_TEST_HR(presults->ComputeReactions(0, 0, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,   1.41421356));
   TRY_TEST_B( IsEqual(fy,  -1.41421356));
   TRY_TEST_B( IsEqual(mz,  0.0));
   TRY_TEST_HR(presults->ComputeReactions(0, 4, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,  0.0));
   TRY_TEST_B( IsEqual(fy,  0.0));
   TRY_TEST_B( IsEqual(mz,  0.0));
   TRY_TEST_HR(presults->ComputeReactions(0, 8, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,   1.41421356));
   TRY_TEST_B( IsEqual(fy,  -1.41421356));
   TRY_TEST_B( IsEqual(mz,  0.0));

   // get merber end forces
   TRY_TEST_HR(presults->ComputeMemberDeflections(0, 1, &sdx, &sdy, &srz, &edx, &edy, &erz));
   TRY_TEST_B( IsEqual(sdx,   0.0) );
   TRY_TEST_B( IsEqual(sdy,   0.0));
   TRY_TEST_B( IsEqual(srz, -2.2857142857143));
   TRY_TEST_B( IsEqual(edx,   0.0));
   TRY_TEST_B( IsEqual(edy, -6.0952380952381));
   TRY_TEST_B( IsEqual(erz,   0.0));
   TRY_TEST_HR(presults->ComputeMemberDeflections(0, 2, &sdx, &sdy, &srz, &edx, &edy, &erz));
   TRY_TEST_B( IsEqual(sdx,   0.0) );
   TRY_TEST_B( IsEqual(sdy,  -6.0952380952381));
   TRY_TEST_B( IsEqual(srz,   0.0));
   TRY_TEST_B( IsEqual(edx,   0.0));
   TRY_TEST_B( IsEqual(edy,   0.0));
   TRY_TEST_B( IsEqual(erz,   2.2857142857143));

   // look at Deflections
   TRY_TEST_HR(presults->ComputePOIDeflections(0, 10,  lotMember, &dx, &dy, &rz));
   TRY_TEST_B( IsEqual(dx, 0.0) );
   TRY_TEST_B( IsEqual(dy, 0.0) );
   TRY_TEST_B( IsEqual(rz, -2.2857142857143) );
   TRY_TEST_HR(presults->ComputePOIDeflections(0, 15,  lotMember, &dx, &dy, &rz));
   TRY_TEST_B( IsEqual(dx, 0.0) );
   TRY_TEST_B( IsEqual(dy, -4.1904761904762));
   TRY_TEST_B( IsEqual(rz, -1.71428) );
   TRY_TEST_HR(presults->ComputePOIDeflections(0, 12,  lotMember, &dx, &dy, &rz));
   TRY_TEST_B( IsEqual(dx, 0.0) );
   TRY_TEST_B( IsEqual(dy, -6.0952380952381));
   TRY_TEST_B( IsEqual(rz, 0.0) );
   TRY_TEST_HR(presults->ComputePOIDeflections(0, 20,  lotMember, &dx, &dy, &rz));
   TRY_TEST_B( IsEqual(dx, 0.0) );
   TRY_TEST_B( IsEqual(dy, -6.0952380952381));
   TRY_TEST_B( IsEqual(rz, 0.0) );
   TRY_TEST_HR(presults->ComputePOIDeflections(0, 25,  lotMember, &dx, &dy, &rz));
   TRY_TEST_B( IsEqual(dx, 0.0) );
   TRY_TEST_B( IsEqual(dy, -4.1904761904762));
   TRY_TEST_B( IsEqual(rz, 1.71428) );
   TRY_TEST_HR(presults->ComputePOIDeflections(0, 22,  lotMember, &dx, &dy, &rz));
   TRY_TEST_B( IsEqual(dx, 0.0) );
   TRY_TEST_B( IsEqual(dy, 0.0) );
   TRY_TEST_B( IsEqual(rz, 2.2857142857143) );

   TRY_TEST_HR(presults->ComputePOIDeflections(0, 10,  lotGlobal, &dx, &dy, &rz));
   TRY_TEST_B( IsEqual(dx, 0.0) );
   TRY_TEST_B( IsEqual(dy, 0.0) );
   TRY_TEST_B( IsEqual(rz, -2.2857142857143) );
   TRY_TEST_HR(presults->ComputePOIDeflections(0, 15,  lotGlobal, &dx, &dy, &rz));
   TRY_TEST_B( IsEqual(dx,-2.9631141) );
   TRY_TEST_B( IsEqual(dy, 2.9631141));
   TRY_TEST_B( IsEqual(rz, -1.71428) );
   TRY_TEST_HR(presults->ComputePOIDeflections(0, 12,  lotGlobal, &dx, &dy, &rz));
   TRY_TEST_B( IsEqual(dx,-4.3099842) );
   TRY_TEST_B( IsEqual(dy, 4.3099842));
   TRY_TEST_B( IsEqual(rz, 0.0) );
   TRY_TEST_HR(presults->ComputePOIDeflections(0, 20,  lotGlobal, &dx, &dy, &rz));
   TRY_TEST_B( IsEqual(dx,-4.3099842) );
   TRY_TEST_B( IsEqual(dy, 4.3099842));
   TRY_TEST_B( IsEqual(rz, 0.0) );
   TRY_TEST_HR(presults->ComputePOIDeflections(0, 25,  lotGlobal, &dx, &dy, &rz));
   TRY_TEST_B( IsEqual(dx,-2.9631141) );
   TRY_TEST_B( IsEqual(dy, 2.9631141));
   TRY_TEST_B( IsEqual(rz, 1.71428) );
   TRY_TEST_HR(presults->ComputePOIDeflections(0, 22,  lotGlobal, &dx, &dy, &rz));
   TRY_TEST_B( IsEqual(dx, 0.0) );
   TRY_TEST_B( IsEqual(dy, 0.0) );
   TRY_TEST_B( IsEqual(rz, 2.2857142857143) );

   // next look at poi forces at both faces and orientations
   TRY_TEST_HR(presults->ComputePOIForces(0, 10, mftLeft, lotGlobal, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx, -1.41421355));
   TRY_TEST_B( IsEqual(fy,  1.41421355));
   TRY_TEST_B( IsEqual(mz,  0.0));
   TRY_TEST_HR(presults->ComputePOIForces(0, 10, mftRight, lotGlobal, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,  1.41421355));
   TRY_TEST_B( IsEqual(fy, -1.41421355));
   TRY_TEST_B( IsEqual(mz,  0.0));
   TRY_TEST_HR(presults->ComputePOIForces(0, 10, mftLeft, lotMember, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,  0.0));
   TRY_TEST_B( IsEqual(fy, -2.0));
   TRY_TEST_B( IsEqual(mz,  0.0));
   TRY_TEST_HR(presults->ComputePOIForces(0, 10, mftRight, lotMember, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,  0.0));
   TRY_TEST_B( IsEqual(fy,  2.0));
   TRY_TEST_B( IsEqual(mz,  0.0));

   TRY_TEST_HR(presults->ComputePOIForces(0, 15, mftLeft, lotGlobal, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,  -1.41421355));
   TRY_TEST_B( IsEqual(fy,   1.41421355));
   TRY_TEST_B( IsEqual(mz,   4.0));
   TRY_TEST_HR(presults->ComputePOIForces(0, 15, mftRight, lotGlobal, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,   1.41421355));
   TRY_TEST_B( IsEqual(fy,  -1.41421355));
   TRY_TEST_B( IsEqual(mz,  -4.0));
   TRY_TEST_HR(presults->ComputePOIForces(0, 15, mftLeft, lotMember, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,  0.0));
   TRY_TEST_B( IsEqual(fy, -2.0));
   TRY_TEST_B( IsEqual(mz,  4.0));
   TRY_TEST_HR(presults->ComputePOIForces(0, 15, mftRight, lotMember, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,  0.0));
   TRY_TEST_B( IsEqual(fy,  2.0));
   TRY_TEST_B( IsEqual(mz, -4.0));

   TRY_TEST_HR(presults->ComputePOIForces(0, 12, mftLeft, lotGlobal, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,  -1.41421355));
   TRY_TEST_B( IsEqual(fy,   1.41421355));
   TRY_TEST_B( IsEqual(mz,   8.0));
   TRY_TEST_HR(presults->ComputePOIForces(0, 12, mftRight, lotGlobal, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,   1.41421355));
   TRY_TEST_B( IsEqual(fy,  -1.41421355));
   TRY_TEST_B( IsEqual(mz,  -8.0));
   TRY_TEST_HR(presults->ComputePOIForces(0, 12, mftLeft, lotMember, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,  0.0));
   TRY_TEST_B( IsEqual(fy, -2.0));
   TRY_TEST_B( IsEqual(mz,  8.0));
   TRY_TEST_HR(presults->ComputePOIForces(0, 12, mftRight, lotMember, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,  0.0));
   TRY_TEST_B( IsEqual(fy,  2.0));
   TRY_TEST_B( IsEqual(mz, -8.0));

   TRY_TEST_HR(presults->ComputePOIForces(0, 20, mftLeft, lotGlobal, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,  1.41421355));
   TRY_TEST_B( IsEqual(fy, -1.41421355));
   TRY_TEST_B( IsEqual(mz,  8.0));
   TRY_TEST_HR(presults->ComputePOIForces(0, 20, mftRight, lotGlobal, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,  -1.41421355));
   TRY_TEST_B( IsEqual(fy,   1.41421355));
   TRY_TEST_B( IsEqual(mz,  -8.0));
   TRY_TEST_HR(presults->ComputePOIForces(0, 20, mftLeft, lotMember, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,  0.0));
   TRY_TEST_B( IsEqual(fy,  2.0));
   TRY_TEST_B( IsEqual(mz,  8.0));
   TRY_TEST_HR(presults->ComputePOIForces(0, 20, mftRight, lotMember, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,   0.0));
   TRY_TEST_B( IsEqual(fy,  -2.0));
   TRY_TEST_B( IsEqual(mz,  -8.0));

   TRY_TEST_HR(presults->ComputePOIForces(0, 25, mftLeft, lotGlobal, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,   1.41421355));
   TRY_TEST_B( IsEqual(fy,  -1.41421355));
   TRY_TEST_B( IsEqual(mz,   4.0));
   TRY_TEST_HR(presults->ComputePOIForces(0, 25, mftRight, lotGlobal, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,  -1.41421355));
   TRY_TEST_B( IsEqual(fy,   1.41421355));
   TRY_TEST_B( IsEqual(mz,  -4.0));
   TRY_TEST_HR(presults->ComputePOIForces(0, 25, mftLeft, lotMember, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,  0.0));
   TRY_TEST_B( IsEqual(fy,  2.0));
   TRY_TEST_B( IsEqual(mz,  4.0));
   TRY_TEST_HR(presults->ComputePOIForces(0, 25, mftRight, lotMember, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,  0.0));
   TRY_TEST_B( IsEqual(fy, -2.0));
   TRY_TEST_B( IsEqual(mz, -4.0));

//////////////////////////////////////////////////////////////////////////////////
// ================================================================================
// Rotate the model -45 degrees clockwise
   TRY_TEST_MC(pJoint4->put_X(2.8284271));
   TRY_TEST_HR(pJoint4->put_Y(-2.8284271));
   TRY_TEST_MC(pJoint8->put_X(5.6568542));
   TRY_TEST_HR(pJoint8->put_Y(-5.6568542));

   pMember1->get_Length(&l);
   TRY_TEST_B(IsEqual(l, 4.0));
   pMember2->get_Length(&l);
   TRY_TEST_B(IsEqual(l, 4.0));

   // change orientation of point load to be normal to rotated structure
   TRY_TEST_HR(pJointLoad->put_Fx(-2.8284271));
   TRY_TEST_LC(pJointLoad->put_Fy(-2.8284271));

// the following is commented out due to compiler limitations

   // get joint Deflections
   TRY_TEST_HR(presults->ComputeJointDeflections(0, 0, &dx, &dy, &rz));
   TRY_TEST_B( IsEqual(dx, 0.0) );
   TRY_TEST_B( IsEqual(dy, 0.0) );
   TRY_TEST_B( IsEqual(rz, -2.2857142857143) );
   TRY_TEST_HR(presults->ComputeJointDeflections(0, 4, &dx, &dy, &rz));
   TRY_TEST_B( IsEqual(dx, -4.30998419) );
   TRY_TEST_B( IsEqual(dy, -4.30998419));
   TRY_TEST_B( IsEqual(rz, 0.0) );
   TRY_TEST_HR(presults->ComputeJointDeflections(0, 8, &dx, &dy, &rz));
   TRY_TEST_B( IsEqual(dx, 0.0) );
   TRY_TEST_B( IsEqual(dy, 0.0) );
   TRY_TEST_B( IsEqual(rz, 2.2857142857143) );

   // get member end forces
   TRY_TEST_HR(presults->ComputeMemberForces(0, 1, &sfx, &sfy, &smz, &efx, &efy, &emz));
   TRY_TEST_B( IsEqual(sfx, 0.0) );
   TRY_TEST_B( IsEqual(sfy, 2.0));
   TRY_TEST_B( IsEqual(smz, 0.0));
   TRY_TEST_B( IsEqual(efx, 0.0));
   TRY_TEST_B( IsEqual(efy, -2.0));
   TRY_TEST_B( IsEqual(emz, 8.0));
   TRY_TEST_HR(presults->ComputeMemberForces(0, 2, &sfx, &sfy, &smz, &efx, &efy, &emz));
   TRY_TEST_B( IsEqual(sfx,  0.0) );
   TRY_TEST_B( IsEqual(sfy, -2.0));
   TRY_TEST_B( IsEqual(smz, -8.0));
   TRY_TEST_B( IsEqual(efx,  0.0));
   TRY_TEST_B( IsEqual(efy,  2.0));
   TRY_TEST_B( IsEqual(emz,  0.0));

   TRY_TEST_HR(presultsex->ComputeMemberForcesEx(0, 1, lotMember, &sfx, &sfy, &smz, &efx, &efy, &emz));
   TRY_TEST_B( IsEqual(sfx, 0.0) );
   TRY_TEST_B( IsEqual(sfy, 2.0));
   TRY_TEST_B( IsEqual(smz, 0.0));
   TRY_TEST_B( IsEqual(efx, 0.0));
   TRY_TEST_B( IsEqual(efy, -2.0));
   TRY_TEST_B( IsEqual(emz, 8.0));
   TRY_TEST_HR(presultsex->ComputeMemberForcesEx(0, 2, lotMember, &sfx, &sfy, &smz, &efx, &efy, &emz));
   TRY_TEST_B( IsEqual(sfx,  0.0) );
   TRY_TEST_B( IsEqual(sfy, -2.0));
   TRY_TEST_B( IsEqual(smz, -8.0));
   TRY_TEST_B( IsEqual(efx,  0.0));
   TRY_TEST_B( IsEqual(efy,  2.0));
   TRY_TEST_B( IsEqual(emz,  0.0));

   TRY_TEST_HR(presultsex->ComputeMemberForcesEx(0, 1, lotGlobal, &sfx, &sfy, &smz, &efx, &efy, &emz));
   TRY_TEST_B( IsEqual(sfx,  1.41421356));
   TRY_TEST_B( IsEqual(sfy,  1.41421356));
   TRY_TEST_B( IsEqual(smz,  0.0));
   TRY_TEST_B( IsEqual(efx, -1.41421355));
   TRY_TEST_B( IsEqual(efy, -1.41421355));
   TRY_TEST_B( IsEqual(emz, 8.0));
   TRY_TEST_HR(presultsex->ComputeMemberForcesEx(0, 2, lotGlobal, &sfx, &sfy, &smz, &efx, &efy, &emz));
   TRY_TEST_B( IsEqual(sfx, -1.41421355) );
   TRY_TEST_B( IsEqual(sfy, -1.41421355));
   TRY_TEST_B( IsEqual(smz, -8.0));
   TRY_TEST_B( IsEqual(efx,  1.41421356));
   TRY_TEST_B( IsEqual(efy,  1.41421356));
   TRY_TEST_B( IsEqual(emz,  0.0));

   TRY_TEST_HR(presults->ComputeReactions(0, 0, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,  1.41421356));
   TRY_TEST_B( IsEqual(fy,  1.41421356));
   TRY_TEST_B( IsEqual(mz,  0.0));
   TRY_TEST_HR(presults->ComputeReactions(0, 4, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,  0.0));
   TRY_TEST_B( IsEqual(fy,  0.0));
   TRY_TEST_B( IsEqual(mz,  0.0));
   TRY_TEST_HR(presults->ComputeReactions(0, 8, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,  1.41421356));
   TRY_TEST_B( IsEqual(fy,  1.41421356));
   TRY_TEST_B( IsEqual(mz,  0.0));

   // get merber end forces
   TRY_TEST_HR(presults->ComputeMemberDeflections(0, 1, &sdx, &sdy, &srz, &edx, &edy, &erz));
   TRY_TEST_B( IsEqual(sdx,   0.0) );
   TRY_TEST_B( IsEqual(sdy,   0.0));
   TRY_TEST_B( IsEqual(srz, -2.2857142857143));
   TRY_TEST_B( IsEqual(edx,   0.0));
   TRY_TEST_B( IsEqual(edy, -6.0952380952381));
   TRY_TEST_B( IsEqual(erz,   0.0));
   TRY_TEST_HR(presults->ComputeMemberDeflections(0, 2, &sdx, &sdy, &srz, &edx, &edy, &erz));
   TRY_TEST_B( IsEqual(sdx,   0.0) );
   TRY_TEST_B( IsEqual(sdy,  -6.0952380952381));
   TRY_TEST_B( IsEqual(srz,   0.0));
   TRY_TEST_B( IsEqual(edx,   0.0));
   TRY_TEST_B( IsEqual(edy,   0.0));
   TRY_TEST_B( IsEqual(erz,   2.2857142857143));

   // look at Deflections
   TRY_TEST_HR(presults->ComputePOIDeflections(0, 10,  lotMember, &dx, &dy, &rz));
   TRY_TEST_B( IsEqual(dx, 0.0) );
   TRY_TEST_B( IsEqual(dy, 0.0) );
   TRY_TEST_B( IsEqual(rz, -2.2857142857143) );
   TRY_TEST_HR(presults->ComputePOIDeflections(0, 15,  lotMember, &dx, &dy, &rz));
   TRY_TEST_B( IsEqual(dx, 0.0) );
   TRY_TEST_B( IsEqual(dy, -4.1904761904762));
   TRY_TEST_B( IsEqual(rz, -1.71428) );
   TRY_TEST_HR(presults->ComputePOIDeflections(0, 12,  lotMember, &dx, &dy, &rz));
   TRY_TEST_B( IsEqual(dx, 0.0) );
   TRY_TEST_B( IsEqual(dy, -6.0952380952381));
   TRY_TEST_B( IsEqual(rz, 0.0) );
   TRY_TEST_HR(presults->ComputePOIDeflections(0, 20,  lotMember, &dx, &dy, &rz));
   TRY_TEST_B( IsEqual(dx, 0.0) );
   TRY_TEST_B( IsEqual(dy, -6.0952380952381));
   TRY_TEST_B( IsEqual(rz, 0.0) );
   TRY_TEST_HR(presults->ComputePOIDeflections(0, 25,  lotMember, &dx, &dy, &rz));
   TRY_TEST_B( IsEqual(dx, 0.0) );
   TRY_TEST_B( IsEqual(dy, -4.1904761904762));
   TRY_TEST_B( IsEqual(rz, 1.71428) );
   TRY_TEST_HR(presults->ComputePOIDeflections(0, 22,  lotMember, &dx, &dy, &rz));
   TRY_TEST_B( IsEqual(dx, 0.0) );
   TRY_TEST_B( IsEqual(dy, 0.0) );
   TRY_TEST_B( IsEqual(rz, 2.2857142857143) );

   TRY_TEST_HR(presults->ComputePOIDeflections(0, 10,  lotGlobal, &dx, &dy, &rz));
   TRY_TEST_B( IsEqual(dx, 0.0) );
   TRY_TEST_B( IsEqual(dy, 0.0) );
   TRY_TEST_B( IsEqual(rz, -2.2857142857143) );
   TRY_TEST_HR(presults->ComputePOIDeflections(0, 15,  lotGlobal, &dx, &dy, &rz));
   TRY_TEST_B( IsEqual(dx,-2.9631141) );
   TRY_TEST_B( IsEqual(dy,-2.9631141));
   TRY_TEST_B( IsEqual(rz, -1.71428) );
   TRY_TEST_HR(presults->ComputePOIDeflections(0, 12,  lotGlobal, &dx, &dy, &rz));
   TRY_TEST_B( IsEqual(dx,-4.3099842) );
   TRY_TEST_B( IsEqual(dy,-4.3099842));
   TRY_TEST_B( IsEqual(rz, 0.0) );
   TRY_TEST_HR(presults->ComputePOIDeflections(0, 20,  lotGlobal, &dx, &dy, &rz));
   TRY_TEST_B( IsEqual(dx,-4.3099842) );
   TRY_TEST_B( IsEqual(dy,-4.3099842));
   TRY_TEST_B( IsEqual(rz, 0.0) );
   TRY_TEST_HR(presults->ComputePOIDeflections(0, 25,  lotGlobal, &dx, &dy, &rz));
   TRY_TEST_B( IsEqual(dx,-2.9631141) );
   TRY_TEST_B( IsEqual(dy,-2.9631141));
   TRY_TEST_B( IsEqual(rz, 1.71428) );
   TRY_TEST_HR(presults->ComputePOIDeflections(0, 22,  lotGlobal, &dx, &dy, &rz));
   TRY_TEST_B( IsEqual(dx, 0.0) );
   TRY_TEST_B( IsEqual(dy, 0.0) );
   TRY_TEST_B( IsEqual(rz, 2.2857142857143) );

   // next look at poi forces at both faces and orientations
   TRY_TEST_HR(presults->ComputePOIForces(0, 10, mftLeft, lotGlobal, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx, -1.41421355));
   TRY_TEST_B( IsEqual(fy, -1.41421355));
   TRY_TEST_B( IsEqual(mz,  0.0));
   TRY_TEST_HR(presults->ComputePOIForces(0, 10, mftRight, lotGlobal, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,  1.41421355));
   TRY_TEST_B( IsEqual(fy,  1.41421355));
   TRY_TEST_B( IsEqual(mz,  0.0));
   TRY_TEST_HR(presults->ComputePOIForces(0, 10, mftLeft, lotMember, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,  0.0));
   TRY_TEST_B( IsEqual(fy, -2.0));
   TRY_TEST_B( IsEqual(mz,  0.0));
   TRY_TEST_HR(presults->ComputePOIForces(0, 10, mftRight, lotMember, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,  0.0));
   TRY_TEST_B( IsEqual(fy,  2.0));
   TRY_TEST_B( IsEqual(mz,  0.0));

   TRY_TEST_HR(presults->ComputePOIForces(0, 15, mftLeft, lotGlobal, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx, -1.41421355));
   TRY_TEST_B( IsEqual(fy, -1.41421355));
   TRY_TEST_B( IsEqual(mz,  4.0));
   TRY_TEST_HR(presults->ComputePOIForces(0, 15, mftRight, lotGlobal, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,  1.41421355));
   TRY_TEST_B( IsEqual(fy,  1.41421355));
   TRY_TEST_B( IsEqual(mz, -4.0));
   TRY_TEST_HR(presults->ComputePOIForces(0, 15, mftLeft, lotMember, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,  0.0));
   TRY_TEST_B( IsEqual(fy, -2.0));
   TRY_TEST_B( IsEqual(mz,  4.0));
   TRY_TEST_HR(presults->ComputePOIForces(0, 15, mftRight, lotMember, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,  0.0));
   TRY_TEST_B( IsEqual(fy,  2.0));
   TRY_TEST_B( IsEqual(mz, -4.0));

   TRY_TEST_HR(presults->ComputePOIForces(0, 12, mftLeft, lotGlobal, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,  -1.41421355));
   TRY_TEST_B( IsEqual(fy,  -1.41421355));
   TRY_TEST_B( IsEqual(mz,   8.0));
   TRY_TEST_HR(presults->ComputePOIForces(0, 12, mftRight, lotGlobal, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,   1.41421355));
   TRY_TEST_B( IsEqual(fy,   1.41421355));
   TRY_TEST_B( IsEqual(mz,  -8.0));
   TRY_TEST_HR(presults->ComputePOIForces(0, 12, mftLeft, lotMember, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,  0.0));
   TRY_TEST_B( IsEqual(fy, -2.0));
   TRY_TEST_B( IsEqual(mz,  8.0));
   TRY_TEST_HR(presults->ComputePOIForces(0, 12, mftRight, lotMember, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,  0.0));
   TRY_TEST_B( IsEqual(fy,  2.0));
   TRY_TEST_B( IsEqual(mz, -8.0));

   TRY_TEST_HR(presults->ComputePOIForces(0, 20, mftLeft, lotGlobal, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,  1.41421355));
   TRY_TEST_B( IsEqual(fy,  1.41421355));
   TRY_TEST_B( IsEqual(mz,  8.0));
   TRY_TEST_HR(presults->ComputePOIForces(0, 20, mftRight, lotGlobal, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,  -1.41421355));
   TRY_TEST_B( IsEqual(fy,  -1.41421355));
   TRY_TEST_B( IsEqual(mz,  -8.0));
   TRY_TEST_HR(presults->ComputePOIForces(0, 20, mftLeft, lotMember, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,  0.0));
   TRY_TEST_B( IsEqual(fy,  2.0));
   TRY_TEST_B( IsEqual(mz,  8.0));
   TRY_TEST_HR(presults->ComputePOIForces(0, 20, mftRight, lotMember, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,   0.0));
   TRY_TEST_B( IsEqual(fy,  -2.0));
   TRY_TEST_B( IsEqual(mz,  -8.0));

   TRY_TEST_HR(presults->ComputePOIForces(0, 25, mftLeft, lotGlobal, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,   1.41421355));
   TRY_TEST_B( IsEqual(fy,   1.41421355));
   TRY_TEST_B( IsEqual(mz,   4.0));
   TRY_TEST_HR(presults->ComputePOIForces(0, 25, mftRight, lotGlobal, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,  -1.41421355));
   TRY_TEST_B( IsEqual(fy,  -1.41421355));
   TRY_TEST_B( IsEqual(mz,  -4.0));
   TRY_TEST_HR(presults->ComputePOIForces(0, 25, mftLeft, lotMember, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,  0.0));
   TRY_TEST_B( IsEqual(fy,  2.0));
   TRY_TEST_B( IsEqual(mz,  4.0));
   TRY_TEST_HR(presults->ComputePOIForces(0, 25, mftRight, lotMember, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,  0.0));
   TRY_TEST_B( IsEqual(fy, -2.0));
   TRY_TEST_B( IsEqual(mz, -4.0));

   ReleaseModel(pmodel);
}



