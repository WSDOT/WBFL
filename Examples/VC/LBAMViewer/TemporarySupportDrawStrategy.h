#ifndef INCLUDED_TEMPORARYSUPPORTDRAWSTRATEGY_H_
#define INCLUDED_TEMPORARYSUPPORTDRAWSTRATEGY_H_

interface iTemporarySupportDrawStrategy
{
   virtual void SetTemporarySupport(ITemporarySupport* jnt, IDType supportID) = 0;
};

#endif // INCLUDED_TEMPORARYSUPPORTDRAWSTRATEGY_H_