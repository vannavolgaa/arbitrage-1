#pragma once
#include <iostream>
#include <vector>
#include "../datastructure/timestamp/timestamp.h"
#include "../datastructure/instruments/instruments.h"

struct ZeroCoupondBond: Instrument
{
    std::unique_ptr<EpochTimestamp> expiry_ptr; 
    ZeroCoupondBond(std::unique_ptr<EpochTimestamp> expiry);
    ~ZeroCoupondBond();
};