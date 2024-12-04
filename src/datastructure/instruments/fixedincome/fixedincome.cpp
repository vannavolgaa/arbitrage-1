#include "fixedincome.h"

/** 
* @file fixedincome.h
* @brief This file defines all the Fixed Income instruments.  
*/

/** 
* @struct ZeroCoupondBond
* @brief Definition of a zero coupond Bond: an instrument that pays 1 unit at expiry.   
*/

/**
 * @var std::unique_ptr<EpochTimestamp>  ZeroCoupondBond::expiry_ptr
 * @brief the epoch timestamp pointer refering to the expiry of the ZC Bond
 * @see EpochTimestamp
 */

/** 
* @brief ZeroCoupondBond constructor
* @param expiry the epoch timestamp pointer refering to the expiry of the ZC Bond
* @see EpochTimestamp
*/
ZeroCoupondBond::ZeroCoupondBond(std::unique_ptr<EpochTimestamp> expiry): 
    expiry_ptr(std::move(expiry)){};
ZeroCoupondBond::~ZeroCoupondBond(){}; 
