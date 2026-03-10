#ifndef INCLUDED_POINTLOADDRAWSTRATEGY_H_
#define INCLUDED_POINTLOADDRAWSTRATEGY_H_

interface iPointLoadDrawStrategy
{
   virtual void SetLoad(IFem2dPointLoad* load) = 0;
   virtual void SetColor(COLORREF color) = 0;
};

#endif // INCLUDED_POINTLOADDRAWSTRATEGY_H_