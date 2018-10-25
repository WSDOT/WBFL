#ifndef INCLUDED_POINTLOADDRAWSTRATEGY_H_
#define INCLUDED_POINTLOADDRAWSTRATEGY_H_

interface iPointLoadDrawStrategy : public IUnknown
{
   STDMETHOD_(void,SetLoad)(IFem2dPointLoad* load) PURE;
   STDMETHOD_(void,SetColor)(COLORREF color) PURE;
};

#endif // INCLUDED_POINTLOADDRAWSTRATEGY_H_