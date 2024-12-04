#pragma once
#include <iostream>
#include <vector>
#include "../datastructure/timestamp/timestamp.h"
#include "../datastructure/instruments/instruments.h"

class WeightMismatchStructuredOption: public std::exception 
{public: const char * what() const throw();};

enum OptionType {CALL = 1, PUT = -1};

enum ExerciseType {AMERICAN, EUROPEAN,BERMUDAN};

enum BarrierType 
{
    UP_AND_IN, 
    UP_AND_OUT, 
    DOWN_AND_IN, 
    DOWN_AND_OUT, 
    DOUBLE_KNOCK_IN, 
    DOUBLE_KNOCK_OUT 
};


struct Option : Instrument
{
    float K; 
    OptionType type_; 
    std::unique_ptr<EpochTimestamp> expiry_ptr; 
    Option(
        std::unique_ptr<EpochTimestamp> expiry, 
        OptionType type, 
        float strike);
    virtual ~Option();
};

struct StructuredOption : Instrument
{
    std::vector<double> weights_;
    std::vector<std::unique_ptr<Option>> option_ptrs;
    StructuredOption(
        std::vector<std::unique_ptr<Option>> options, 
        std::vector<double> weights);
    ~StructuredOption();
};

struct EuropeanVanillaOption : Option
{
    EuropeanVanillaOption(
        std::unique_ptr<EpochTimestamp> expiry, 
        OptionType type, 
        float strike);
    ~EuropeanVanillaOption();
}; 

struct AmericanVanillaOption : Option
{
    AmericanVanillaOption(
        std::unique_ptr<EpochTimestamp> expiry, 
        OptionType type, 
        float strike);
    ~AmericanVanillaOption();
}; 

