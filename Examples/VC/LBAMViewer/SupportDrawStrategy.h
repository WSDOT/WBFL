#ifndef INCLUDED_SUPPORTDRAWSTRATEGY_H_
#define INCLUDED_SUPPORTDRAWSTRATEGY_H_

interface iSupportDrawStrategy : public IUnknown
{
   STDMETHOD_(void,SetSupport)(ISupport* jnt, IDType supportID) PURE;
};

#endif // INCLUDED_SUPPORTDRAWSTRATEGY_H_