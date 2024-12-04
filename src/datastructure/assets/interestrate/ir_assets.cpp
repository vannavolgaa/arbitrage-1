#include "ir_assets.h"

/** 
* @file it_assets.h
* @brief This file defined all the existing interest rate assets used in Arbitrage. 
*/

/** 
 * @struct InterestRateAsset
 * @brief Base struct for all interest rate assets.
 * 
 * @see InterestRate 
 */
/**
 * @var std::unique_ptr<FX> InterestRateAsset::ir_ptr
 * @brief The interest rate risk factor pointer.
 * @see InterestRate
 */

InterestRateAsset::InterestRateAsset(
    std::unique_ptr<InterestRate> ir_risk_factor): 
    ir_ptr(std::move(ir_risk_factor)){};
InterestRateAsset::~InterestRateAsset(){}; 

/** 
 * @struct InterestRateZCBond
 * @brief Definition of an interest rate zero coupon bond asset.
 * 
 * @see InterestRateAsset 
 */
/**
 * @var std::unique_ptr<ZeroCoupondBond> InterestRateZCBond::zc_bond_
 * @brief The zero coupon bond instrument.
 * @see ZeroCoupondBond
 */

InterestRateZCBond::InterestRateZCBond(
    std::unique_ptr<InterestRate> ir_risk_factor, 
    std::unique_ptr<ZeroCoupondBond> zc_bond): 
    InterestRateAsset(std::move(ir_risk_factor)), 
    zc_bond_(std::move(zc_bond)){};
InterestRateZCBond::~InterestRateZCBond(){}; 
