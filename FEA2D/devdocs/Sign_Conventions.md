# Sign Conventions {#WBFL_FEA2D_Sign_Conventions}

## Member Forces

The sign conventions for member force output (`Model::ComputeMemberForces`) are shown below. The forces returned are the externally applied forces required to hold the member in equilibrium.

@image html "Member Sign Conventions.gif"

## POI Forces

POI forces (`Model::ComputePOIForces`) can be requested at either face of the location where the POI cuts the member (`MemberFaceType::Left`/`MemberFaceType::Right`). The forces returned are the externally applied forces required to hold that portion of the member in equilibrium. POI forces can be requested in member-local or global coordinates (`LoadOrientation`).

@image html "POI Sign Conventions.gif"

Note this convention creates a slight discrepancy when a POI is located exactly at the end of a member: one of the two faces doesn't physically exist (for example, the left face at the very start of the member). For consistency, the forces returned for that non-existent face are equal and opposite to the true face at the member end.

## Reaction Forces

Reaction forces (`Model::ComputeReactions`) are always returned in global coordinates - they are the forces applied to the model at the support point.
