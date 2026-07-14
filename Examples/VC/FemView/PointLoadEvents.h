#pragma once

interface iPointLoadEvents
{
   virtual void InitFromLoad(IFem2dPointLoad* load) = 0;
};

