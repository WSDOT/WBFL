#ifndef INCLUDED_POINTLOADEVENTS_H_
#define INCLUDED_POINTLOADEVENTS_H_

interface iPointLoadEvents
{
   virtual void InitFromLoad(IFem2dPointLoad* load) = 0;
};

#endif // INCLUDED_POINTLOADEVENTS_H_