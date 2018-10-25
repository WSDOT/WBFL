#ifndef INCLUDED_JOINTDRAWSTRATEGY_H_
#define INCLUDED_JOINTDRAWSTRATEGY_H_

interface iJointDrawStrategy : public IUnknown
{
   STDMETHOD_(void,SetJoint)(IFem2dJoint* jnt) PURE;
};

#endif // INCLUDED_JOINTDRAWSTRATEGY_H_