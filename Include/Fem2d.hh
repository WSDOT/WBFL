///////////////////////////////////////////////////////////////////////
// Fem2D - Two-dimensional Beam Analysis Engine
// Copyright © 1999-2020  Washington State Department of Transportation
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
#ifndef INCLUDED_FEM2D_HH_
#define INCLUDED_FEM2D_HH_

// Help Context IDs
#define IDH_WbflFem2d                           	  101

#define IDH_Fem2dAccessType                      		  52
#define IDH_Fem2dMbrReleaseType                  		  53
#define IDH_Fem2dMbrEndType					   		     54
#define IDH_Fem2dJointReleaseType				   		  55
#define IDH_Fem2dLoadOrientation				   		  56
#define IDH_Fem2dLoadDirection				   	    	  57
#define IDH_Fem2dMbrFaceType					   		     58
#define IDH_Fem2dJointDOF                              59
#define IDH_Fem2dMbrDOF                                60

#define IDH_IFem2dModelEvents					   		  109
#define IDH_IFem2dModelEvents_OnModelChanged	   			  110
#define IDH_IFem2dModelEvents_OnLoadingChanged	   		  111
#define IDH_IFem2dJoint							   		  112
#define IDH_IFem2dJoint_ID						   		  113
#define IDH_IFem2dJoint_X						   		  114
#define IDH_IFem2dJoint_Y						   		  115
#define IDH_IFem2dJoint_IsDofReleased			   		  116
#define IDH_IFem2dJoint_IsSupport				   		  117
#define IDH_IFem2dJoint_Support					   		  118
#define IDH_IFem2dJoint_Free						   		  119
#define IDH_IFem2dJoint_ReleaseDof				   		  120
#define IDH_IFem2dJointCollection				   		  121
#define IDH_IFem2dJointCollection_Item			   		  122
#define IDH_IFem2dJointCollection_Count			   		  123
#define IDH_IFem2dJointCollection_Find			   		  124
#define IDH_IFem2dJointCollection_Create			   		  125
#define IDH_IFem2dJointCollection_Remove			   		  126
#define IDH_IFem2dJointCollection_Clear			   		  127
#define IDH_IFem2dMember							   		  128
#define IDH_IFem2dMember_ID						   		  129
#define IDH_IFem2dMember_StartJoint				   		  130
#define IDH_IFem2dMember_EndJoint				   		  131
#define IDH_IFem2dMember_IsReleased				   		  132
#define IDH_IFem2dMember_ReleaseEnd				   		  133
#define IDH_IFem2dMember_EA						   		  134
#define IDH_IFem2dMember_EI						   		  135
#define IDH_IFem2dMember_Length					   		  136
#define IDH_IFem2dMemberCollection				   		  137
#define IDH_IFem2dMemberCollection_Item			   		  138
#define IDH_IFem2dMemberCollection_Count			   		  139
#define IDH_IFem2dMemberCollection_Find			   		  140
#define IDH_IFem2dMemberCollection_Create		   		  141
#define IDH_IFem2dMemberCollection_Remove		   		  142
#define IDH_IFem2dMemberCollection_Clear			   		  143
#define IDH_IFem2dJointLoad						   		  144
#define IDH_IFem2dJointLoad_ID                      		  145
#define IDH_IFem2dJointLoad_JointID				   		  146
#define IDH_IFem2dJointLoad_Fx					   		  147
#define IDH_IFem2dJointLoad_Fy					   		  148
#define IDH_IFem2dJointLoad_Mz					   		  149
#define IDH_IFem2dJointLoad_SetForce				   		  150
#define IDH_IFem2dJointLoad_GetForce				   		  151
#define IDH_IFem2dJointLoad_Loading				   		  152
#define IDH_IFem2dJointLoadCollection			   		  153
#define IDH_IFem2dJointLoadCollection_ID			   		  154
#define IDH_IFem2dJointLoadCollection_Item		   		  155
#define IDH_IFem2dJointLoadCollection_Count		   		  156
#define IDH_IFem2dJointLoadCollection_Find		   		  157
#define IDH_IFem2dJointLoadCollection_Create		   		  158
#define IDH_IFem2dJointLoadCollection_Remove		   		  159
#define IDH_IFem2dJointLoadCollection_Clear		   		  160
#define IDH_IFem2dJointDeflection				   		  161
#define IDH_IFem2dJointDeflection_ID			   		  162
#define IDH_IFem2dJointDeflection_JointID		   		  163
#define IDH_IFem2dJointDeflection_Dx			   		  164
#define IDH_IFem2dJointDeflection_Dy			   		  165
#define IDH_IFem2dJointDeflection_Rz			   		  166
#define IDH_IFem2dJointDeflection_SetDeflection 		  167
#define IDH_IFem2dJointDeflection_GetDeflection 		  168
#define IDH_IFem2dJointDeflection_Loading		   		  169
#define IDH_IFem2dJointDeflectionCollection	   		  170
#define IDH_IFem2dJointDeflectionCollection_Item  		  171
#define IDH_IFem2dJointDeflectionCollection_Count 		  172
#define IDH_IFem2dJointDeflectionCollection_Find  		  173
#define IDH_IFem2dJointDeflectionCollection_Create 	  174
#define IDH_IFem2dJointDeflectionCollection_Remove 	  175
#define IDH_IFem2dJointDeflectionCollection_Clear  	  176
#define IDH_IFem2dPointLoad								  177
#define IDH_IFem2dPointLoad_ID							  178
#define IDH_IFem2dPointLoad_MemberID                 	  179
#define IDH_IFem2dPointLoad_Orientation					  180
#define IDH_IFem2dPointLoad_Fx							  181
#define IDH_IFem2dPointLoad_Fy							  182
#define IDH_IFem2dPointLoad_Mz							  183
#define IDH_IFem2dPointLoad_SetForce						  184
#define IDH_IFem2dPointLoad_GetForce						  185
#define IDH_IFem2dPointLoad_Location						  186
#define IDH_IFem2dPointLoad_Loading						  187
#define IDH_IFem2dPointLoadCollection			   		  188
#define IDH_IFem2dPointLoadCollection_ID			   		  189
#define IDH_IFem2dPointLoadCollection_Item		   		  190
#define IDH_IFem2dPointLoadCollection_Count		   		  191
#define IDH_IFem2dPointLoadCollection_Find		   		  192
#define IDH_IFem2dPointLoadCollection_Create		   		  193
#define IDH_IFem2dPointLoadCollection_Remove		   		  194
#define IDH_IFem2dPointLoadCollection_Clear		   		  195
#define IDH_IFem2dDistributedLoad				   		  196
#define IDH_IFem2dDistributedLoad_ID				   		  197
#define IDH_IFem2dDistributedLoad_MemberID		   		  198
#define IDH_IFem2dDistributedLoad_Orientation	   		  199
#define IDH_IFem2dDistributedLoad_Direction		   		  200
#define IDH_IFem2dDistributedLoad_StartLocation	   		  201
#define IDH_IFem2dDistributedLoad_EndLocation	   		  202
#define IDH_IFem2dDistributedLoad_WStart			   		  203
#define IDH_IFem2dDistributedLoad_WEnd			   		  204
#define IDH_IFem2dDistributedLoad_Loading		   		  205
#define IDH_IFem2dDistributedLoadCollection			   	  206
#define IDH_IFem2dDistributedLoadCollection_ID			  207
#define IDH_IFem2dDistributedLoadCollection_Item		   	  208
#define IDH_IFem2dDistributedLoadCollection_Count		  209
#define IDH_IFem2dDistributedLoadCollection_Find		   	  210
#define IDH_IFem2dDistributedLoadCollection_Create		  211
#define IDH_IFem2dDistributedLoadCollection_Remove		  212
#define IDH_IFem2dDistributedLoadCollection_Clear		  213
#define IDH_IFem2dMemberStrain					  		  214
#define IDH_IFem2dMemberStrain_ID				  		  215
#define IDH_IFem2dMemberStrain_MemberID		      		  216
#define IDH_IFem2dMemberStrain_AxialStrain		  		  217
#define IDH_IFem2dMemberStrain_CurvatureStrain	  		  218
#define IDH_IFem2dMemberStrain_Loading			  		  219
#define IDH_IFem2dMemberStrain_StartLocation         220
#define IDH_IFem2dMemberStrain_EndLocation            221
#define IDH_IFem2dMemberStrainCollection			   		  222
#define IDH_IFem2dMemberStrainCollection_ID			   	  223
#define IDH_IFem2dMemberStrainCollection_Item		   	  224
#define IDH_IFem2dMemberStrainCollection_Count		   	  225
#define IDH_IFem2dMemberStrainCollection_Find		   	  226
#define IDH_IFem2dMemberStrainCollection_Create		   	  227
#define IDH_IFem2dMemberStrainCollection_Remove		   	  228
#define IDH_IFem2dMemberStrainCollection_Clear		   	  229
#define IDH_IFem2dLoading						  		  230
#define IDH_IFem2dLoading_ID						  		  231
#define IDH_IFem2dLoading_JointLoads				  		  232
#define IDH_IFem2dLoading_DistributedLoads		  		  233
#define IDH_IFem2dLoading_JointDeflections		  		  234
#define IDH_IFem2dLoading_PointLoads				  		  235
#define IDH_IFem2dLoading_MemberStrains			  		  236
#define IDH_IFem2dLoadingCollection			   			  237
#define IDH_IFem2dLoadingCollection_ID			   		  238
#define IDH_IFem2dLoadingCollection_Item		   			  239
#define IDH_IFem2dLoadingCollection_Count		   		  240
#define IDH_IFem2dLoadingCollection_Find		   			  241
#define IDH_IFem2dLoadingCollection_Create		   		  242
#define IDH_IFem2dLoadingCollection_Remove		   		  243
#define IDH_IFem2dLoadingCollection_Clear		   		  244
#define IDH_IFem2dPOI							   		  245
#define IDH_IFem2dPOI_MemberID					   		  246
#define IDH_IFem2dPOI_ID					           		  247
#define IDH_IFem2dPOI_Location					   		  248
#define IDH_IFem2dPOICollection			   				  249
#define IDH_IFem2dPOICollection_ID			   			  250
#define IDH_IFem2dPOICollection_Item		   				  251
#define IDH_IFem2dPOICollection_Count		   			  252
#define IDH_IFem2dPOICollection_Find		   				  253
#define IDH_IFem2dPOICollection_Create		   			  254
#define IDH_IFem2dPOICollection_Remove		   			  255
#define IDH_IFem2dPOICollection_Clear		   			  256
#define IDH_IFem2dModel							   		  257
#define IDH_IFem2dModel_Joints						   	  258
#define IDH_IFem2dModel_Members					   		  259
#define IDH_IFem2dModel_Loadings					   		  260
#define IDH_IFem2dModel_POIs						   		  261
#define IDH_IFem2dModel_ComputeJointDeflections	   	  262
#define IDH_IFem2dModel_ComputeMemberDeflections	   	  263
#define IDH_IFem2dModel_ComputePOIDeflections	   		  264
#define IDH_IFem2dModel_ComputeReactions			   		  265
#define IDH_IFem2dModel_ComputeMemberForces		   		  266
#define IDH_IFem2dModel_ComputePOIForces			   		  267
#define IDH_IFem2dModel_Clear						   	  268
#define IDH_IFem2dJoint_IsDofSupported			   		  269
#define IDH_IFem2dJoint_Members                            270
#define IDH_IINTEGERCOLLECTION_ITEM                   271
#define IDH_IINTEGERCOLLECTION_COUNT                  272
#define IDH_IINTEGERCOLLECTION_ITEMAT                 273
#define IDH_IFem2dModelResults_ComputeMemberDeflections  274
#define IDH_IFem2dModelResults_ComputePOIDeflections	  275
#define IDH_IFem2dModelResults_ComputeReactions			  276
#define IDH_IFem2dModelResults_ComputeMemberForces		  277
#define IDH_IFem2dModelResults_ComputePOIForces			  278
#define IDH_IFem2dModelResults                             279
#define IDH_IFem2dModelResults_ComputeJointDeflections   280
#define IDH_IFem2dModelResultsForScriptingClients          281
#define IDH_IFem2dModel_Results                            282
#define IDH_IFem2dModel_StructuredStorage                  283
#define IDH_IFem2dModelResults_ComputeMemberForcesEx       284
#define IDH_IFem2dModelResultsEx                           285

#define IDH_E_MEMBER_HAS_SAME_JOINTS				  500
#define IDH_E_MEMBER_JOINT_NOT_EXISTS				  501
#define IDH_E_MEMBER_WITH_ID_ALREADY_EXISTS		  	  502
#define IDH_E_JOINT_WITH_ID_ALREADY_EXISTS			  503
#define IDH_E_STIFFNESS_MUST_BE_POSITIVE			  504
#define IDH_E_JOINT_LOAD_WITH_ID_ALREADY_EXISTS	  	  505
#define IDH_E_POINT_LOAD_WITH_ID_ALREADY_EXISTS	  	  506
#define IDH_E_LOADING_WITH_ID_ALREADY_EXISTS	      507
#define IDH_E_INVALID_POINT_LOAD_LOCATION	          508
#define IDH_E_INVALID_POI_LOCATION	                  509
#define IDH_E_POI_WITH_ID_ALREADY_EXISTS			  510
#define IDH_E_POINT_LOAD_OFF_GIRDER_END			  	  511
#define IDH_E_FRACTIONAL_VALUE_OUT_OF_RANGE		  	  512
#define IDH_E_ZERO_LENGTH_MEMBER		              513
#define IDH_E_JOINT_EQUILIBRIUM_NOT_SATISFIED         514
#define IDH_E_MEMBER_EQUILIBRIUM_NOT_SATISFIED        515
#define IDH_E_POI_REFERENCES_MEMBER_NOT_EXISTS        516
#define IDH_E_POI_FRACTIONAL_OUT_OF_RANGE             517
#define IDH_E_POI_LOCATED_OFF_MEMBER_END              518
#define IDH_E_JOINT_NOT_FOUND                         519
#define IDH_E_LOADING_NOT_FOUND                       520
#define IDH_E_MEMBER_NOT_FOUND                        521
#define IDH_E_POI_NOT_FOUND                           522
#define IDH_E_SOLVING_GLOBAL_STIFFNESS                523
#define IDH_E_INVALID_GLOBAL_DOF                      524
#define IDH_E_INVALID_CONDENSED_DOF                   525
#define IDH_E_JOINT_LOAD_REF_JOINT_NOT_EXISTS         526
#define IDH_E_POINT_LOAD_REF_MEMBER_NOT_EXISTS        527
#define IDH_E_JOINT_DISP_WITH_ID_ALREADY_EXISTS	  	  528
#define IDH_E_JOINT_DISP_REF_JOINT_NOT_EXISTS         529
#define IDH_E_JOINT_DISP_TO_FIXED_DOF_ONLY            530
#define IDH_E_MATRIX_BACK_SUBSTITUTION                531
#define IDH_E_MATRIX_FACTORING                        532
#define IDH_E_DIST_LOAD_OFF_GIRDER_END		          533
#define IDH_E_DIST_LOAD_B_BEFORE_A    		          534
#define IDH_E_DIST_LOAD_REF_MEMBER_NOT_EXISTS         535
#define IDH_E_INVALID_DIST_LOAD_LOCATION              536
#define IDH_E_DIST_LOAD_WITH_ID_ALREADY_EXISTS	      537
#define IDH_E_INVALID_LOAD_ORIENTATION        	      538
#define IDH_E_MEMBER_STRAIN_WITH_ID_ALREADY_EXISTS    539
#define IDH_E_LOGIC_ERROR                             540
#define IDH_IINTEGERCOLLECTION                        541
#define IDH_E_MODEL_HAS_NO_JOINTS                     542
#define IDH_E_MODEL_HAS_NO_MEMBERS                    543
#define IDH_E_STRAIN_LOAD_OFF_GIRDER_END		          544

#endif //  INCLUDED_FEM2D_HH_