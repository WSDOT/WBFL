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
#include <EngTools\Bearing.h>
#include <Units\Convert.h>
#include <MathEx.h>

using namespace WBFL::EngTools;


void Bearing::SetLength(Float64 l)
{
    m_length = l;
}
void Bearing::SetWidth(Float64 w)
{
    m_width = w;
}
void Bearing::SetShearModulusMinimum(Float64 Gmin)
{
    m_shear_modulus_min = Gmin;
}
void Bearing::SetShearModulusMaximum(Float64 Gmax)
{
    m_shear_modulus_max = Gmax;
}
void Bearing::SetIntermediateLayerThickness(Float64 layer)
{
    m_intermediate_layer_thickness = layer;
}
void Bearing::SetCoverThickness(Float64 cover)
{
    m_cover_thickness = cover;
}
void Bearing::SetSteelShimThickness(Float64 shim)
{
    m_steel_shim_thickness = shim;
}
void Bearing::SetYieldStrength(Float64 fy)
{
    m_yield_strength = fy;
}
void Bearing::SetFatigueThreshold(Float64 fth)
{
    m_fatigue_threshold = fth;
}
void Bearing::SetNumIntLayers(IndexType n)
{
    m_number_intermediate_layers = n;
}
void Bearing::SetDensitySteel(Float64 ps)
{
    m_density_steel = ps;
}
void Bearing::SetDensityElastomer(Float64 pe)
{
    m_density_elastomer = pe;
}



Float64 Bearing::GetLength() const
{
    return m_length;
}

Float64 Bearing::GetWidth() const
{
    return m_width;
}
Float64 Bearing::GetShearModulusMinimum() const
{
    return m_shear_modulus_min;
}
Float64 Bearing::GetShearModulusMaximum() const
{
    return m_shear_modulus_max;
}
Float64 Bearing::GetIntermediateLayerThickness() const
{
    return m_intermediate_layer_thickness;
}
Float64 Bearing::GetCoverThickness() const
{
    return m_cover_thickness;
}
Float64 Bearing::GetSteelShimThickness() const
{
    return m_steel_shim_thickness;
}
Float64 Bearing::GetYieldStrength() const
{
    return m_yield_strength;
}
Float64 Bearing::GetFatigueThreshold() const
{
    return m_fatigue_threshold;
}
IndexType Bearing::GetNumIntLayers() const
{
    return m_number_intermediate_layers;
}
double Bearing::GetDensitySteel() const
{
    return m_density_steel;
}
double Bearing::GetDensityElastomer() const
{
    return m_density_elastomer;
}

//Calculated Bearing properties
Float64 Bearing::GetArea() const
{
    return m_length * m_width;
}
Float64 Bearing::GetShapeFactor() const
{
    return GetArea() / (2 * m_intermediate_layer_thickness * (m_length + m_width));
}
Float64 Bearing::GetTotalElastomerThickness() const
{
    auto ttotal = m_cover_thickness * 2 + m_number_intermediate_layers * m_intermediate_layer_thickness;
    return ttotal;
}
Float64 Bearing::GetTotalSteelShimThickness() const
{
    return m_steel_shim_thickness * GetTotalSteelShims();
}
IndexType Bearing::GetTotalSteelShims() const
{
    return m_number_intermediate_layers + 1;
}



