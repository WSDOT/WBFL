///////////////////////////////////////////////////////////////////////
// EngTools - Library of miscellaneous engineering tools
// Copyright © 1999-2023  Washington State Department of Transportation
//                        Bridge and Structures Office
//
// This library is a part of the Washington Bridge Foundation Libraries
// and was developed as part of the Alternate Route Project
//
// This library is free software; you can redistribute it and/or modify it under
// the terms of the Alternate Route Library Open Source License as published by 
// the Washington State Department of Transportation, Bridge and Structures Office.
//
// This program is distributed in the hope that it will be useful, but is distributed 
// AS IS, WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY 
// or FITNESS FOR A PARTICULAR PURPOSE. See the Alternate Route Library Open Source 
// License for more details.
//
// You should have received a copy of the Alternate Route Library Open Source License 
// along with this program; if not, write to the Washington State Department of 
// Transportation, Bridge and Structures Office, P.O. Box  47340, 
// Olympia, WA 98503, USA or e-mail Bridge_Support@wsdot.wa.gov
///////////////////////////////////////////////////////////////////////
#pragma once

#include <EngTools\EngToolsLib.h>
#include <EngTools\BearingLoads.h>
#include <Units\Convert.h>
#include <MathEx.h>

//This is a test

using namespace WBFL::EngTools;


void BearingLoads::SetDeadLoad(Float64 DL)
{
    m_dead_load = DL;
}
void BearingLoads::SetLiveLoad(Float64 LL)
{
    m_live_load = LL;
}
void BearingLoads::SetRotationX(Float64 rx)
{
    m_rotation_x = rx;
}
void BearingLoads::SetRotationY(Float64 ry)
{
    m_rotation_y = ry;
}
void BearingLoads::SetStaticRotation(Float64 rst)
{
    m_static_rotation = rst;
}
void BearingLoads::SetCyclicRotation(Float64 rcy)
{
    m_cyclic_rotation = rcy;
}
void BearingLoads::SetShearDeformation(Float64 shear_def)
{
    m_shear_deformation = shear_def;
}
void BearingLoads::SetFixedTranslationX(BearingLoads::FixedTranslationX fx)
{
    m_fixed_translation_x = fx;
}
void BearingLoads::SetFixedTranslationY(BearingLoads::FixedTranslationY fy)
{
    m_fixed_translation_y = fy;
}



Float64 BearingLoads::GetDeadLoad() const
{
    return m_dead_load;
}
Float64 BearingLoads::GetLiveLoad() const
{
    return m_live_load;
}
Float64 BearingLoads::GetTotalLoad() const
{
    return m_dead_load + m_live_load;
}
Float64 BearingLoads::GetRotationX() const
{
    return m_rotation_x;
}
Float64 BearingLoads::GetRotationY() const
{
    return m_rotation_y;
}
Float64 BearingLoads::GetStaticRotation() const
{
    return m_static_rotation;
}
Float64 BearingLoads::GetCyclicRotation() const
{
    return m_cyclic_rotation;
}
Float64 BearingLoads::GetShearDeformation() const
{
    return m_shear_deformation;
}

BearingLoads::FixedTranslationX BearingLoads::GetFixedTranslationX() const
{
    return m_fixed_translation_x;
}
BearingLoads::FixedTranslationY BearingLoads::GetFixedTranslationY() const
{
    return m_fixed_translation_y;
}

Float64 BearingLoads::GetEffectiveKFactorX() const
{
    if (m_fixed_translation_x == FixedTranslationX::Yes)
    {
        return 1.0;
    }
    else
    {
        return 2.0;
    }
}
Float64 BearingLoads::GetEffectiveKFactorY() const
{
    if (m_fixed_translation_y == FixedTranslationY::Yes)
    {
        return 1.0;
    }
    else
    {
        return 2.0;
    }
}












