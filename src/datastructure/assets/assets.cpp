#include "assets.h"
#include "../toolbox/tools.h"

/** 
* @file assets.h
* @brief This file defined the base asset classes, including baskets, used in Arbitrage. 
*/

/** 
 * @class MismatchWeightedBasket
 * @brief Definition of the mismatch error if the number of weights/asset is not equal.
 * It applied only when basket type if set to weighted.
 * 
 */
/** 
 * @brief Definition of what() virtual std::exception function.
 * @return The explication of the error.
 */
const char * MismatchWeightedBasket::what() const throw(){
    return "The number of weights and the number of assets must be the same \
    in order to construct a basket.";
};

/** 
 * @struct Asset
 * @brief Base struct from which all assets must inherit.
 * 
 * An asset maps an instrument and its related risk factor. 
 * For example, a future bitcoin/us dollar asset mapped the crypto risk factor 
 * BTCUSD to a future instrument as defined in Arbitrage. 
 * 
 * @see Instrument 
 * @see RiskFactor
 */

Asset::Asset(){};
Asset::~Asset(){}; 

/** 
 * @struct Basket
 * @brief Base struct from which all baskets must inherit.
 * 
 * A basket is the combinaison of a set of different assets.
 * 
 * @see Asset 
 */
/**
 * @var std::vector<double> Basket::weights_
 * @brief The vector of weights corresponding to the quantity of each asset within the basket.
 */
/**
 * @var std::vector<std::unique_ptr<Asset>> Basket::asset_ptrs
 * @brief The vector of asset pointers composing the basket.
 */

/** 
* @brief Basket constructor
* @param assets The vector of asset pointers composing the basket.
* @see Asset
*/
Basket::Basket(std::vector<std::unique_ptr<Asset>> assets): 
    asset_ptrs(vectorized_std::move(assets)){};
Basket::~Basket(){}; 

/** 
 * @struct WeightedBasket
 * @brief Base struct from which all weighted baskets must inherit.
 * 
 * A weighted basket is the combinaison of a set of different assets 
 * based on respective weights.
 * 
 * @see Basket 
 */
/**
 * @var std::vector<double> WeightedBasket::weights_
 * @brief The vector of weights corresponding to the quantity of each asset within the basket.
 */
/** 
* @brief WeightedBasket constructor
* @param weights The vector of weights corresponding to the quantity of each asset within the basket.
* @param assets The vector of asset pointers composing the basket.
* @throws MismatchWeightedBasket
* @see Basket
*/
WeightedBasket::WeightedBasket(
    std::vector<double> weights, 
    std::vector<std::unique_ptr<Asset>> assets): 
    Basket(vectorized_std::move(assets)), weights_(weights)
{
    if (weights_.size()!=asset_ptrs.size())
    {throw MismatchWeightedBasket();}
}; 
WeightedBasket::~WeightedBasket(){};

template <typename T>
std::vector<std::unique_ptr<Asset>> convert_specific_assets_to_base_assets(
    std::vector<std::unique_ptr<T>> specific_assets)
{
    std::vector<std::unique_ptr<Asset>> assets;
    for (auto& asset : specific_assets) 
    {
        assets.push_back(std::move(asset));
    }
    return assets;
};