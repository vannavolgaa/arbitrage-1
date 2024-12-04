#pragma once
#include <iostream>
#include "../datastructure/assets/assets.h"
#include "../datastructure/instruments/option/option.h"
#include "../datastructure/instruments/future/future.h"

struct CryptoAsset : Asset
{
    CryptoAsset();
    ~CryptoAsset();
};

template <typename T>
std::vector<std::unique_ptr<CryptoAsset>> convert_specific_crypto_assets_to_crypto_assets(
    std::vector<std::unique_ptr<T>> crypto_assets);

struct WeightedCryptoBasket : WeightedBasket, CryptoAsset 
{
    WeightedCryptoBasket(
        std::vector<double> weights,
        std::vector<std::unique_ptr<CryptoAsset>> crypto_assets);
    ~WeightedCryptoBasket();
};

struct CryptoSpot : CryptoAsset
{
    std::unique_ptr<Crypto> crypto_ptr;
    CryptoSpot(std::unique_ptr<Crypto> crypto_risk_factor);
    ~CryptoSpot();
};

struct CryptoFuture : CryptoAsset
{
    std::unique_ptr<Future> future_ptr; 
    std::unique_ptr<Crypto> crypto_ptr;
    CryptoFuture(
        std::unique_ptr<Crypto> crypto_risk_factor, 
        std::unique_ptr<Future> future);
    ~CryptoFuture();
};

struct CryptoVolatilityFuture : CryptoAsset
{
    std::unique_ptr<VolatilityFuture> vol_future_ptr; 
    std::unique_ptr<Crypto> crypto_ptr;
    CryptoVolatilityFuture(
        std::unique_ptr<Crypto> crypto_risk_factor, 
        std::unique_ptr<VolatilityFuture> vol_future);
    ~CryptoVolatilityFuture();
};

struct CryptoOption : CryptoAsset
{
    std::unique_ptr<Option> option_ptr; 
    std::unique_ptr<CryptoAsset> underlying_asset_ptr;
    CryptoOption(
        std::unique_ptr<Crypto> crypto_risk_factor, 
        std::unique_ptr<Option> option);
    CryptoOption(
        std::unique_ptr<Crypto> crypto_risk_factor, 
        std::unique_ptr<Option> option, 
        std::unique_ptr<Future> future);
    ~CryptoOption();
};

struct CryptoStructuredOption : WeightedCryptoBasket
{
    CryptoStructuredOption(
        std::vector<double> weights,
        std::vector<std::unique_ptr<CryptoOption>> crypto_options);
    ~CryptoStructuredOption();
};

struct CryptoStructuredFuture : WeightedCryptoBasket
{
    CryptoStructuredFuture(
        std::vector<double> weights,
        std::vector<std::unique_ptr<CryptoFuture>> crypto_futures);
    ~CryptoStructuredFuture();
};


