#pragma once
#include <iostream>
#include <vector>
#include "../datastructure/timestamp/timestamp.h"
#include "../datastructure/instruments/instruments.h"

class WeightMismatchStructuredFuture: public std::exception 
{public: const char * what() const throw();};

struct Future : Instrument
{
    bool is_perpetual; 
    std::unique_ptr<EpochTimestamp> expiry_ptr; 
    Future();
    Future(std::unique_ptr<EpochTimestamp> expiry);
    ~Future();
};

struct VolatilityFuture : Instrument
{
    std::unique_ptr<EpochTimestamp> expiry_ptr; 
    VolatilityFuture(std::unique_ptr<EpochTimestamp> expiry);
    ~VolatilityFuture();
};

struct StructuredFuture : Instrument
{
    std::vector<double> weights_;
    std::vector<std::unique_ptr<Future>> future_ptrs;
    StructuredFuture(
        std::vector<std::unique_ptr<Future>> futures, 
        std::vector<double> weights);
    ~StructuredFuture();
};

struct FutureSpread : Instrument
{
    std::unique_ptr<StructuredFuture> structured_future_ptr; 
    FutureSpread(
        std::unique_ptr<Future> long_future, 
        std::unique_ptr<Future> short_future);
    ~FutureSpread();
    std::vector<double> get_weights();
    std::unique_ptr<StructuredFuture> set_structured_future(
        std::unique_ptr<Future> long_future, 
        std::unique_ptr<Future> short_future
    );
};