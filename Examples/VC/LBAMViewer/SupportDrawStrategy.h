#ifndef INCLUDED_SUPPORTDRAWSTRATEGY_H_
#define INCLUDED_SUPPORTDRAWSTRATEGY_H_

interface iSupportDrawStrategy
{
   virtual void SetSupport(ISupport* jnt, IDType supportID) = 0;
};

#endif // INCLUDED_SUPPORTDRAWSTRATEGY_H_