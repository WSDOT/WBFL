#pragma once

interface iPointLoadDrawStrategy
{
   virtual void SetLoad(IFem2dPointLoad* load) = 0;
   virtual void SetColor(COLORREF color) = 0;
};

