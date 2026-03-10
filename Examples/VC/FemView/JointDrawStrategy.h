#ifndef INCLUDED_JOINTDRAWSTRATEGY_H_
#define INCLUDED_JOINTDRAWSTRATEGY_H_

interface iJointDrawStrategy
{
   virtual void SetJoint(IFem2dJoint* jnt) = 0;
};

#endif // INCLUDED_JOINTDRAWSTRATEGY_H_