#include "option.h"
#include "../toolbox/tools.h"

/** 
* @file options.h
* @brief This file defines all the option instruments used in Arbitrage. 
*/

/** 
 * @enum OptionType
 * @brief Enumeration of both existing option types.
 */
/**
 * @var OptionType OptionType::CALL
 * @brief Call option. 
 */
/**
 * @var OptionType OptionType::PUT
 * @brief Put option. 
 */

/** 
 * @enum ExerciseType
 * @brief Enumeration of the three existing exercise types.
 */
/**
 * @var ExerciseType ExerciseType::EUROPEAN
 * @brief Exercise possible only at maturity of the option. 
 */
/**
 * @var ExerciseType ExerciseType::AMERICAN
 * @brief Exercise possible anytime before or at expiry of the option. 
 */
/**
 * @var ExerciseType ExerciseType::BERMUDAN
 * @brief Exercise possible only at some defined dates before or at expiry of the option. 
 */

/** 
 * @enum BarrierType
 * @brief Enumeration of existing option barrier types.
 */
/**
 * @var BarrierType BarrierType::UP_AND_IN
 * @brief The option is alive when barrier up is touched.
 */
/**
 * @var BarrierType BarrierType::UP_AND_OUT
 * @brief The option is dead when barrier up is touched.
 */
/**
 * @var BarrierType BarrierType::DOWN_AND_IN
 * @brief The option is alive when barrier down is touched.
 */
/**
 * @var BarrierType BarrierType::DOWN_AND_OUT
 * @brief The option is dead when barrier down is touched.
 */
/**
 * @var BarrierType BarrierType::DOUBLE_KNOCK_IN
 * @brief The option is alive when barrier down or up are touched.
 */
/**
 * @var BarrierType BarrierType::DOUBLE_KNOCK_OUT
 * @brief The option is dead when barrier down or up are touched.
 */


/** 
 * @class WeightMismatchStructuredOption
 * @brief Definition of the mismatch in number of weights/options error.
 */
/** 
 * @brief Definition of what() virtual std::exception function.
 * @return The explication of the error.
 */
const char * WeightMismatchStructuredOption::what() const throw(){
    return "The number of weights and the number of options must be the same \
    in order to construct a Structured Option";
};

/** 
 * @struct Option
 * @brief Definition of an option instrument: an instrument to buy or sell something 
 * at a predetermined price for delivery at a specified time in the future only if 
 * the value of the underlying price is above (for a call type) or under (for a put type)
 * the option's strike value.
 */
/**
 * @var std::unique_ptr<EpochTimestamp> Option::expiry_ptr
 * @brief the epoch timestamp pointer refering to the option's expiry.
 * @see EpochTimestamp
 */
/**
 * @var OptionType Option::type_
 * @brief The option's type. 
 */
/**
 * @var double Option::K
 * @brief The option's strike value. 
 */
/** 
* @brief Option constructor
* @param expiry the epoch timestamp pointer refering to the option's expiry.
* @param type The option's type. 
* @param strike The option's strike value. 
* @see EpochTimestamp
* @see OptionType
*/
Option::Option(
    std::unique_ptr<EpochTimestamp> expiry, 
    OptionType type, 
    float strike): 
    K(strike), type_(type),
    expiry_ptr(std::move(expiry)){};
Option::~Option(){}; 

/** 
 * @struct EuropeanVanillaOption
 * @brief Vanilla option payoff with exercise only at maturity. 
 */
/** 
* @brief EuropeanVanillaOption constructor
* @param expiry the epoch timestamp pointer refering to the option's expiry.
* @param type The option's type.
* @param strike The option's strike value.
* @see EpochTimestamp
* @see OptionType
*/
EuropeanVanillaOption::EuropeanVanillaOption(
    std::unique_ptr<EpochTimestamp> expiry, 
    OptionType type, 
    float strike): 
    Option(std::move(expiry), type, strike)
    {};
EuropeanVanillaOption::~EuropeanVanillaOption(){}; 

/** 
 * @struct AmericanVanillaOption
 * @brief Vanilla option payoff with exercise any time before or at maturity. 
 */
/** 
* @brief AmericanVanillaOption constructor
* @param expiry the epoch timestamp pointer refering to the option's expiry.
* @param type The option's type.
* @param strike The option's strike value.
* @see EpochTimestamp
* @see OptionType
*/
AmericanVanillaOption::AmericanVanillaOption(
    std::unique_ptr<EpochTimestamp> expiry, 
    OptionType type, 
    float strike): 
    Option(std::move(expiry), type, strike)
    {};
AmericanVanillaOption::~AmericanVanillaOption(){}; 

/** 
 * @struct StructuredOption
 * @brief Definition of a structured option instrument: an instrument holding several options 
 * with respective weights. 
 * @see Option
 */
/**
 * @var std::vector<double> StructuredOption::weights_
 * @brief The vector of weights corresponding to the quantity of each option instruments within 
 * the structured option instrument. 
 */
/**
 * @var std::vector<std::unique_ptr<Option>> StructuredOption::option_ptrs
 * @brief The vector of option instrument pointers composing the structured option instrument.
 * @see Option
 */
/** 
* @brief StructuredOption constructor
* @param options The vector of option instrument pointers composing the strutured option instrument.
* @param weights The vector of weights corresponding to the quantity of each option instrument within 
* the strutured option instrument. 
* @throws WeightMismatchStructuredOption
* @see Option
* @see WeightMismatchStructuredOption
*/
StructuredOption::StructuredOption(
    std::vector<std::unique_ptr<Option>> options, 
    std::vector<double> weights): 
    weights_(weights), 
    option_ptrs(vectorized_std::move(options))
{
    if (weights.size()!=option_ptrs.size())
    {throw WeightMismatchStructuredOption();}

};
StructuredOption::~StructuredOption(){}; 