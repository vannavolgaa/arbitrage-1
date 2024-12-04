#pragma once
#include <iostream>
#include "../datastructure/assets/assets.h"
#include "../datastructure/instruments/fixedincome/fixedincome.h"
#include "../datastructure/riskfactors/riskfactors.h"

struct InterestRateAsset : Asset
{
    std::unique_ptr<InterestRate> ir_ptr;
    InterestRateAsset(std::unique_ptr<InterestRate> ir_risk_factor);
    virtual ~InterestRateAsset();
};

struct InterestRateZCBond : InterestRateAsset
{
    std::unique_ptr<ZeroCoupondBond> zc_bond_;
    InterestRateZCBond(
        std::unique_ptr<InterestRate> ir_risk_factor, 
        std::unique_ptr<ZeroCoupondBond> zc_bond);
    ~InterestRateZCBond();
};

