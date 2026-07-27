#pragma once

interface iJointDrawStrategy
{
   virtual void SetJoint(WBFL::FEA2D::Joint* jnt) = 0;
};

