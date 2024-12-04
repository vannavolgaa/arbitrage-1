#include "fx_assets.h"

/** 
* @file fx_assets.h
* @brief This file defined all the existing fx assets used in Arbitrage. 
*/

/** 
 * @struct FXAsset
 * @brief Base struct for all fx assets.
 * 
 * @see FX 
 */
/**
 * @var std::unique_ptr<FX> FXAsset::fx_ptr
 * @brief The FX risk factor pointer
 * @see FX
 */

FXAsset::FXAsset(
    std::unique_ptr<FX> fx_risk_factor): 
    fx_ptr(std::move(fx_risk_factor)){};
FXAsset::~FXAsset(){}; 

/** 
 * @struct FXSpot
 * @brief Definition of an fx spot asset.
 * 
 * @see FXAsset 
 */

FXSpot::FXSpot(std::unique_ptr<FX> fx_risk_factor): 
    FXAsset(std::move(fx_risk_factor)){};
FXSpot::~FXSpot(){}; 
