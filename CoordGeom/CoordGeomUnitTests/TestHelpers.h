#pragma once

#include "pch.h"

std::shared_ptr<WBFL::COGO::Alignment> CreateStraightAlignment(Float64 refStation, Float64 x, Float64 y, Float64 direction);
std::shared_ptr<WBFL::COGO::BridgeFramingGeometry> CreateBridgeGeometry(Float64 refStation, Float64 x, Float64 y, Float64 direction,const std::vector<std::tuple<IDType, Float64, std::_tstring, WBFL::COGO::ConnectionGeometry, WBFL::COGO::ConnectionGeometry>>& piers, bool bContinuousGirders);
std::shared_ptr<WBFL::COGO::BridgeFramingGeometry> CreateBridgeGeometry(const std::vector<std::tuple<IDType, Float64, std::_tstring, WBFL::COGO::ConnectionGeometry, WBFL::COGO::ConnectionGeometry>>& piers, bool bContinuousGirders);
