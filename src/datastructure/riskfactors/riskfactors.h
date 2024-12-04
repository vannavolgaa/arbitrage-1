#pragma once
#include <iostream>

struct Currency
{ 
    std::string code_;
    Currency(const std::string& code);
    ~Currency();
};

struct RiskFactor
{ 
    std::string id_;
    std::unique_ptr<Currency> base_ccy_ptr;
    RiskFactor(
        std::string id,
        std::unique_ptr<Currency> base_currency);
    virtual ~RiskFactor();
};

struct InterestRate: RiskFactor 
{
    InterestRate(std::unique_ptr<Currency> base_currency);
    ~InterestRate();
    std::string get_id();
};

struct FX: RiskFactor 
{
    std::unique_ptr<Currency> counter_ccy_ptr;
    FX(
        std::unique_ptr<Currency> base_currency, 
        std::unique_ptr<Currency> counter_currency
    );
    ~FX();
    std::string get_id();
};

struct Crypto: RiskFactor 
{
    std::unique_ptr<Currency> counter_ccy_ptr;
    Crypto(
        std::unique_ptr<Currency> base_currency, 
        std::unique_ptr<Currency> counter_currency
    );
    ~Crypto();
    std::string get_id();
};

