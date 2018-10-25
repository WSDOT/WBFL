#ifndef INCLUDED_POINTLOADEVENTS_H_
#define INCLUDED_POINTLOADEVENTS_H_


interface iPointLoadEvents : public IUnknown
{
   STDMETHOD_(void,InitFromLoad)(IFem2dPointLoad* load) PURE;
};

#endif // INCLUDED_POINTLOADEVENTS_H_