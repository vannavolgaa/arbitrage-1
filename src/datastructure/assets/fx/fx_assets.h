#pragma once
#include <iostream>
#include "../datastructure/assets/assets.h"
#include "../datastructure/riskfactors/riskfactors.h"

struct FXAsset : Asset
{
    std::unique_ptr<FX> fx_ptr;
    FXAsset(std::unique_ptr<FX> fx_risk_factor);
    virtual ~FXAsset();
};

struct FXSpot : FXAsset
{
    FXSpot(std::unique_ptr<FX> fx_risk_factor);
    ~FXSpot();
};