#include "future.h"
#include "../toolbox/tools.h"

/** 
* @file futures.h
* @brief This file defines all the future instruments used in Arbitrage. 
*/

/** 
 * @class WeightMismatchStructuredFuture
 * @brief Definition of the mismatch in the number of weights/futures error.
 */
/** 
 * @brief Definition of what() virtual std::exception function.
 * @return The explication of the error.
 */
const char * WeightMismatchStructuredFuture::what() const throw(){
    return "The number of weights and the number of futures must be the same \
    in order to construct a Structured Future";
};

/** 
 * @struct Future
 * @brief Definition of a future instrument: an instrument to buy or sell something 
 * at a predetermined price for delivery at a specified time in the future.
 */
/**
 * @var std::unique_ptr<EpochTimestamp> Future::expiry_ptr
 * @brief the epoch timestamp pointer refering to the future's expiry.
 * @see EpochTimestamp
 */
/**
 * @var bool Future::is_perpetual
 * @brief specified if the future is perpetual or not. When true, expiry is set to the
 * default value 32531558207 epoch timestamps (in seconds).
 */
/** 
* @brief Future constructor (classic future type)
* @param expiry the epoch timestamp pointer refering to the future's expiry.
* @see EpochTimestamp
*/
Future::Future(std::unique_ptr<EpochTimestamp> expiry): 
    expiry_ptr(std::move(expiry)), is_perpetual(false){};
Future::~Future(){}; 

/** 
* @brief Future constructor (perpetual future type)
* @param expiry the epoch timestamp pointer refering to the future's expiry.
* @see EpochTimestamp
*/
Future::Future(): 
    expiry_ptr(std::make_unique<EpochTimestamp>(
        EpochTimestamp(32531558207,EpochTimestampType::SECONDS)
        )), 
    is_perpetual(true){};
Future::~Future(){}; 

/** 
 * @struct VolatilityFuture
 * @brief Definition of a volatility future instrument.
 */
/**
 * @var std::unique_ptr<EpochTimestamp> VolatilityFuture::expiry_ptr
 * @brief the epoch timestamp pointer refering to the volatility future's expiry.
 * @see EpochTimestamp
 */
/** 
* @brief VolatilityFuture constructor
* @param expiry the epoch timestamp pointer refering to the volatility future's expiry.
* @see EpochTimestamp
*/
VolatilityFuture::VolatilityFuture(std::unique_ptr<EpochTimestamp> expiry): 
    expiry_ptr(std::move(expiry)){};
VolatilityFuture::~VolatilityFuture(){}; 

/** 
 * @struct StructuredFuture
 * @brief Definition of a structured future instrument: an instrument holding several futures 
 * with respective weights. 
 * @see Future
 */
/**
 * @var std::vector<double> StructuredFuture::weights_
 * @brief The vector of weights corresponding to the quantity of each future instrument within 
 * the structured future instrument. 
 */
/**
 * @var std::vector<std::unique_ptr<Future>> StructuredFuture::future_ptrs
 * @brief The vector of Future instrument pointers composing the structured future instrument.
 * @see Future
 */
/** 
* @brief StructuredFuture constructor
* @param futures The vector of future instrument pointers composing the structured future instrument.
* @param weights The vector of weights corresponding to the quantity of each future instrument within 
* the structured future instrument. 
* @throws WeightMismatchStructuredFuture
* @see Future
* @see WeightMismatchStructuredFuture
*/
StructuredFuture::StructuredFuture(
    std::vector<std::unique_ptr<Future>> futures, 
    std::vector<double> weights): 
    weights_(weights), 
    future_ptrs(vectorized_std::move(futures))
{
    if (weights.size()!=future_ptrs.size())
    {throw WeightMismatchStructuredFuture();}

};
StructuredFuture::~StructuredFuture(){}; 

/** 
 * @struct FutureSpread
 * @brief Definition of a future spread instrument: a specific case of a structured 
 * future by being long and short two different futures. Thus weights are -1 and 1.
 */
/**
 * @var std::unique_ptr<StructuredFuture> FutureSpread::structured_future_ptr
 * @brief The structured future pointer corresponding to the future spread.
 */
/** 
* @brief FutureSpread constructor
* @param long_future The future instrument in the long position of the future spread.
* @param short_future The future instrument in the short position of the future spread.
* @see Future
*/
FutureSpread::FutureSpread(
    std::unique_ptr<Future> long_future, 
    std::unique_ptr<Future> short_future): 
    structured_future_ptr(set_structured_future(
        std::move(long_future),
        std::move(short_future))){};
/**
 * @brief Get the weights for the future spread instrument. 
 * @return The future spread weights as the instrument defines it.
 */
std::vector<double> FutureSpread::get_weights()
{
    return {1,-1};
};
/**
 * @brief Set the corresponding structure future.
 * @param long_future The future instrument in the long position of the future spread.
 * @param short_future The future instrument in the short position of the future spread.
 * @return The structured future pointer.
 * @see Future
 */
std::unique_ptr<StructuredFuture> FutureSpread::set_structured_future(
    std::unique_ptr<Future> long_future, 
    std::unique_ptr<Future> short_future)
{
    std::vector<std::unique_ptr<Future>> futures = {
        std::move(long_future), 
        std::move(short_future)};
    return std::make_unique<StructuredFuture>(
        StructuredFuture(futures,get_weights()));
};
FutureSpread::~FutureSpread(){}; 
