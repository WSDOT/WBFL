#pragma once

interface iPointLoadDrawStrategy
{
   virtual void SetLoad(WBFL::FEA2D::PointLoad* load) = 0;
   virtual void SetColor(COLORREF color) = 0;
};

