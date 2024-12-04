#include "crypto_assets.h"
#include "../toolbox/tools.h"

/** 
* @file crypto_assets.h
* @brief This file defined all the existing crypto assets used in Arbitrage. 
*/

/** 
 * @struct CryptoAsset
 * @brief Base struct for all crypto assets.
 * 
 * @see Crypto 
 */
/**
 * @var std::unique_ptr<Crypto> CryptoAsset::crypto_ptr
 * @brief The crypto risk factor pointer.
 * @see Crypto
 * @see Asset 
 */

/** 
* @brief CryptoAsset constructor
* @see Crypto
*/
CryptoAsset::CryptoAsset(){};
CryptoAsset::~CryptoAsset(){}; 

/** 
* @brief Translates any crypto asset type pointer into crypto asset pointers.
* @see CryptoAsset
* @result The corresponding crypto asset pointers.
*/
template <typename T>
std::vector<std::unique_ptr<CryptoAsset>> convert_specific_crypto_assets_to_crypto_assets(
    std::vector<std::unique_ptr<T>> crypto_assets)
{
    std::vector<std::unique_ptr<CryptoAsset>> assets;
    for (auto& asset : crypto_assets) 
    {
        assets.push_back(std::move(asset));
    }
    return assets;
}

/** 
 * @struct WeightedCryptoBasket
 * @brief Definition of an weighted crypto basket.
 * 
 * @see WeightedBasket 
 */

/** 
* @brief WeightedCryptoBasket constructor
* @param weights  The vector of weights corresponding to the quantity of each crypto asset within the basket.
* @param crypto_assets The vector of crypto asset pointers composing the basket.
* @see Crypto
*/
WeightedCryptoBasket::WeightedCryptoBasket(
    std::vector<double> weights,
    std::vector<std::unique_ptr<CryptoAsset>> crypto_assets): 
    WeightedBasket(weights,convert_specific_assets_to_base_assets(crypto_assets)){};
WeightedCryptoBasket::~WeightedCryptoBasket(){}; 

/** 
 * @struct CryptoSpot
 * @brief Definition of an crypto spot asset.
 * 
 * @see CryptoAsset 
 */
/**
 * @var std::unique_ptr<Crypto> CryptoSpot::crypto_ptr
 * @brief The Crypto risk factor pointer.
 * @see Crypto
 */

/** 
* @brief CryptoSpot constructor
* @param crypto_risk_factor The Crypto risk factor pointer.
* @see Crypto
*/
CryptoSpot::CryptoSpot(std::unique_ptr<Crypto> crypto_risk_factor): 
    crypto_ptr(std::move(crypto_risk_factor)){};
CryptoSpot::~CryptoSpot(){}; 

/** 
 * @struct CryptoFuture
 * @brief Definition of an crypto future asset.
 * 
 * @see CryptoAsset 
 */
 /**
 * @var std::unique_ptr<Future> CryptoFuture::future_ptr
 * @brief The future instrument pointer.
 * @see Future
 */
/**
 * @var std::unique_ptr<Crypto> CryptoFuture::crypto_ptr
 * @brief The crypto risk factor pointer.
 * @see Crypto
 */


/** 
* @brief CryptoFuture constructor
* @param crypto_risk_factor The crypto risk factor pointer.
* @param future The future instrument pointer.
* @see Crypto
* @see Future
*/
CryptoFuture::CryptoFuture(
    std::unique_ptr<Crypto> crypto_risk_factor, 
    std::unique_ptr<Future> future): 
    crypto_ptr(std::move(crypto_risk_factor)), 
    future_ptr(std::move(future)){};
CryptoFuture::~CryptoFuture(){}; 

/** 
 * @struct CryptoVolatilityFuture
 * @brief Definition of an crypto volatility future asset.
 * 
 * @see CryptoAsset 
 */
 /**
 * @var std::unique_ptr<VolatilityFuture> CryptoVolatilityFuture::vol_future_ptr
 * @brief The volatility future instrument pointer.
 * @see VolatilityFuture
 */
/**
 * @var std::unique_ptr<Crypto> CryptoVolatilityFuture::crypto_ptr
 * @brief The crypto risk factor pointer.
 * @see Crypto
 */


/** 
* @brief CryptoVolatilityFuture constructor
* @param crypto_risk_factor The crypto risk factor pointer.
* @param vol_future The volatility future instrument pointer.
* @see Crypto
* @see VolatilityFuture
*/
CryptoVolatilityFuture::CryptoVolatilityFuture(
    std::unique_ptr<Crypto> crypto_risk_factor, 
    std::unique_ptr<VolatilityFuture> vol_future): 
    crypto_ptr(std::move(crypto_risk_factor)), 
    vol_future_ptr(std::move(vol_future)){};
CryptoVolatilityFuture::~CryptoVolatilityFuture(){}; 

/** 
 * @struct CryptoOption
 * @brief Definition of an crypto option asset.
 * 
 * @see CryptoAsset 
 */
 /**
 * @var std::unique_ptr<Option> CryptoOption::option_ptr
 * @brief The option future instrument pointer.
 * @see Option
 */
/**
 * @var std::unique_ptr<CryptoAsset> CryptoAsset::underlying_asset_ptr
 * @brief The underlying crypto asset pointer.
 * @see CryptoAsset
 */

/** 
* @brief CryptoOption spot constructor
* @param crypto_risk_factor The crypto risk factor pointer.
* @param option The option instrument pointer.
* @see Crypto
* @see Option
*/
CryptoOption::CryptoOption(
    std::unique_ptr<Crypto> crypto_risk_factor, 
    std::unique_ptr<Option> option): 
    underlying_asset_ptr(std::make_unique<CryptoSpot>(
        CryptoSpot(std::move(crypto_risk_factor)))), 
    option_ptr(std::move(option)){};
CryptoOption::~CryptoOption(){}; 

/** 
* @brief CryptoOption future constructor
* @param crypto_risk_factor The crypto risk factor pointer.
* @param option The option instrument pointer.
* @param future The underlying future instrument pointer.
* @see Crypto
* @see Future
* @see Option
*/
CryptoOption::CryptoOption(
    std::unique_ptr<Crypto> crypto_risk_factor, 
    std::unique_ptr<Option> option, 
    std::unique_ptr<Future> future): 
    underlying_asset_ptr(std::make_unique<CryptoFuture>(
        CryptoFuture(
            std::move(crypto_risk_factor), 
            std::move(future)))), 
    option_ptr(std::move(option)){};
CryptoOption::~CryptoOption(){}; 

/** 
 * @struct CryptoStructuredOption
 * @brief Definition of an crypto structured option asset.
 * 
 * @see CryptoAsset 
 * @see WeightedCryptoBasket 
 */
/** 
* @brief main constructor
* @param weights The weights corresponding to each crypto option.
* @param crypto_options The vector of crypto option pointers.
* @see CryptoOption
*/
CryptoStructuredOption::CryptoStructuredOption(
    std::vector<double> weights,
    std::vector<std::unique_ptr<CryptoOption>> crypto_options): 
    WeightedCryptoBasket(
        weights, 
        convert_specific_crypto_assets_to_crypto_assets(crypto_options)){};
CryptoStructuredOption::~CryptoStructuredOption(){}; 

/** 
 * @struct CryptoStructuredFuture
 * @brief Definition of an crypto structured future asset.
 * 
 * @see CryptoAsset 
 * @see WeightedCryptoBasket 
 */
/** 
* @brief main constructor
* @param weights The weights corresponding to each crypto future.
* @param crypto_futures The vector of crypto future pointers.
* @see CryptoFuture
*/
CryptoStructuredFuture::CryptoStructuredFuture(
    std::vector<double> weights,
    std::vector<std::unique_ptr<CryptoFuture>> crypto_futures): 
    WeightedCryptoBasket(
        weights, 
        convert_specific_crypto_assets_to_crypto_assets(crypto_futures)){};
CryptoStructuredOption::~CryptoStructuredOption(){}; 
    