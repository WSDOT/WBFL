#pragma once

#include <BridgeGeometry\BridgeGeometryExp.h>

class BGCLASS CAlignmentDescription
{
public:
   CAlignmentDescription(void);
   ~CAlignmentDescription(void);

   void SetRefStation(Float64 refStation);
   Float64 GetRefStation() const;
   void SetRefPoint(Float64 x,Float64 y);
   void GetRefPoint(Float64* pX,Float64* pY) const;
   void SetInitialDirection(Float64 dir);
   Float64 GetInitialDirection() const;

protected:
   Float64 m_RefStation;
   Float64 m_X, m_Y;      // ref station is at this coordinate
   Float64 m_Direction;   // East is 0, North is PI/2, etc
};
