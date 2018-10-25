///////////////////////////////////////////////////////////////////////
// Fem2D - Two-dimensional Beam Analysis Engine
// Copyright © 1999-2015  Washington State Department of Transportation
//                        Bridge and Structures Office
//
// This library is a part of the Washington Bridge Foundation Libraries
// and was developed as part of the Alternate Route Project
//
// This program is free software=0; you can redistribute it and/or modify
// it under the terms of the Alternate Route Library Open Source License as 
// published by the Washington State Department of Transportation,
// Bridge and Structures Office.
//
// This program is distributed in the hope that it will be useful,
// but is distributed AS IS, WITHOUT ANY WARRANTY=0; without even the
// implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR 
// PURPOSE.  See the Alternate Route Library Open Source License for more details.
//
// You should have received a copy of the Alternate Route Library Open Source License
// along with this program=0; if not, write to the Washington State
// Department of Transportation, Bridge and Structures Office,
// P.O. Box 47340, Olympia, WA 98503, USA or e-mail
// Bridge_Support@wsdot.wa.gov
///////////////////////////////////////////////////////////////////////
// Fem2dCollection.h : 

#ifndef __MODELEVENTS_H_
#define __MODELEVENTS_H_
#pragma once

class ModelEvents
{
public:
   // events fired from parts of the model
   virtual void OnJointChanged(IFem2dJoint*)=0;
   virtual void OnJointAdded(JointIDType)=0;
   virtual void OnJointRemoved(JointIDType )=0;
   virtual void OnJointsCleared()=0;
   virtual void OnMemberChanged(IFem2dMember*)=0;
   virtual void OnMemberAdded(MemberIDType)=0;
   virtual void OnMemberRemoved(MemberIDType )=0;
   virtual void OnMembersCleared()=0;
   virtual void OnJointLoadChanged(IFem2dJointLoad*, LoadCaseIDType loadingID)=0;
   virtual void OnJointLoadAdded(LoadIDType loadID, LoadCaseIDType loadingID)=0;
   virtual void OnJointLoadRemoved(LoadIDType loadID, LoadCaseIDType loadingID )=0;
   virtual void OnJointLoadsCleared(LoadCaseIDType loadingID )=0;
   virtual void OnJointDisplacementChanged(IFem2dJointDisplacement*, LoadCaseIDType loadingID)=0;
   virtual void OnJointDisplacementAdded(LoadIDType loadID, LoadCaseIDType loadingID)=0;
   virtual void OnJointDisplacementRemoved(LoadIDType loadID, LoadCaseIDType loadingID )=0;
   virtual void OnJointDisplacementsCleared(LoadCaseIDType loadingID )=0;
   virtual void OnPointLoadChanged(IFem2dPointLoad*, LoadCaseIDType loadingID)=0;
   virtual void OnPointLoadAdded(LoadIDType loadID, LoadCaseIDType loadingID)=0;
   virtual void OnPointLoadRemoved(LoadIDType loadID, LoadCaseIDType loadingID )=0;
   virtual void OnPointLoadsCleared(LoadCaseIDType loadingID )=0;
   virtual void OnDistributedLoadChanged(IFem2dDistributedLoad*, LoadCaseIDType loadingID)=0;
   virtual void OnDistributedLoadAdded(LoadIDType loadID, LoadCaseIDType loadingID)=0;
   virtual void OnDistributedLoadRemoved(LoadIDType loadID, LoadCaseIDType loadingID )=0;
   virtual void OnDistributedLoadsCleared(LoadCaseIDType loadingID )=0;
   virtual void OnMemberStrainChanged(IFem2dMemberStrain*, LoadCaseIDType loadingID)=0;
   virtual void OnMemberStrainAdded(LoadIDType loadID, LoadCaseIDType loadingID)=0;
   virtual void OnMemberStrainRemoved(LoadIDType loadID, LoadCaseIDType loadingID )=0;
   virtual void OnMemberStrainsCleared(LoadCaseIDType loadingID )=0;
   virtual void OnLoadingAdded(LoadCaseIDType loadingID)=0;
   virtual void OnLoadingRemoved(LoadCaseIDType loadingID )=0;
   virtual void OnLoadingsCleared()=0;
   virtual void OnPOIChanged(IFem2dPOI*)=0;
   virtual void OnPOIAdded(PoiIDType ID)=0;
   virtual void OnPOIRemoved(PoiIDType ID)=0;
   virtual void OnPOIsCleared()=0;
};
#endif 