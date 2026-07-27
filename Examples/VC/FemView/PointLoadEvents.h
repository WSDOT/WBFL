#pragma once

interface iPointLoadEvents
{
   virtual void InitFromLoad(WBFL::FEA2D::PointLoad* load) = 0;
};

