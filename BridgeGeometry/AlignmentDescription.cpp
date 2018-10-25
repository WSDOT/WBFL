#include "StdAfx.h"
#include <BridgeGeometry\AlignmentDescription.h>

CAlignmentDescription::CAlignmentDescription(void)
{
   m_RefStation = 0.0;
   m_X = 0.0;
   m_Y = 0.0;
   m_Direction = 0.0;
}

CAlignmentDescription::~CAlignmentDescription(void)
{
}

void CAlignmentDescription::SetRefStation(Float64 refStation)
{
   m_RefStation = refStation;
}

Float64 CAlignmentDescription::GetRefStation() const
{
   return m_RefStation;
}

void CAlignmentDescription::SetRefPoint(Float64 x,Float64 y)
{
   m_X = x;
   m_Y = y;
}

void CAlignmentDescription::GetRefPoint(Float64* pX,Float64* pY) const
{
   *pX = m_X;
   *pY = m_Y;
}

void CAlignmentDescription::SetInitialDirection(Float64 dir)
{
   m_Direction = dir;
}

Float64 CAlignmentDescription::GetInitialDirection() const
{
   return m_Direction;
}
