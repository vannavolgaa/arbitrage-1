#pragma once
#include <iostream>
#include "../datastructure/instruments/instruments.h"
#include "../datastructure/riskfactors/riskfactors.h"

class MismatchWeightedBasket:  public std::exception 
{public: const char * what() const throw();};

struct Asset
{
    Asset();
    virtual ~Asset();
};

struct Basket: Asset
{
    std::vector<std::unique_ptr<Asset>> asset_ptrs;
    Basket(std::vector<std::unique_ptr<Asset>> assets);
    ~Basket();
};

struct WeightedBasket: Basket 
{
    std::vector<double> weights_;
    WeightedBasket(
        std::vector<double> weights,
        std::vector<std::unique_ptr<Asset>> assets
    );
    ~WeightedBasket();
};

template <typename T>
std::vector<std::unique_ptr<Asset>> convert_specific_assets_to_base_assets(
    std::vector<std::unique_ptr<T>> specific_assets);