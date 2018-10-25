#ifndef INCLUDED_TEMPORARYSUPPORTDRAWSTRATEGY_H_
#define INCLUDED_TEMPORARYSUPPORTDRAWSTRATEGY_H_

interface iTemporarySupportDrawStrategy : public IUnknown
{
   STDMETHOD_(void,SetTemporarySupport)(ITemporarySupport* jnt, IDType supportID) PURE;
};

#endif // INCLUDED_TEMPORARYSUPPORTDRAWSTRATEGY_H_