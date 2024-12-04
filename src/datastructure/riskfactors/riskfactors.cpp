#include "riskfactors.h"

/** 
* @file riskfactors.h
* @brief This file defines all the risk factors that can be used in Arbitrage. 
*/

/** 
* @struct Currency
* @brief Definition of a currency.  
*/
/**
 * @var std::string& Currency::code_
 * @brief The code defining the currency .
 */

/** 
* @brief Currency constructor
* @param code a code defining the currency 
*/
Currency::Currency(const std::string& code): code_(code){};
Currency::~Currency(){}; 

/** 
* @struct RiskFactor
* @brief Definition of the risk factor base class from which any risk factor must inherit.  
* 
* The risk factor references to a specific market and is linked to a currency. 
* @see Currency
*/
/**
 * @var std::string& RiskFactor::id_
 * @brief The risk factor id .
 */
/**
 * @var std::unique_ptr<Currency> RiskFactor::base_ccy_ptr
 * @brief The risk factor base currency pointer.
 */

/** 
* @brief Risk factor constructor
* @param id The risk factor id.
* @param base_currency The risk factor base currency pointer.
* @see Currency
*/
RiskFactor::RiskFactor(
    std::string id,
    std::unique_ptr<Currency> base_currency): 
    id_(id), base_ccy_ptr(std::move(base_currency)){};
RiskFactor::~RiskFactor(){}; 

/** 
* @struct InterestRate
* @brief Definition of an interest rate risk factor. 
*/

/** 
* @brief Interest rate risk factor constructor
* @param base_currency the interest rate base currency pointer
* @see Currency
* @see RiskFactor
*/
InterestRate::InterestRate(std::unique_ptr<Currency> base_currency):
    RiskFactor(get_id(), std::move(base_currency)){};
/** 
* @brief function to get the interest rate risk factror id 
* @return the base currency code 
* @see Currency
*/
std::string InterestRate::get_id()
{
    return base_ccy_ptr->code_ ;
};
InterestRate::~InterestRate(){}; 

/** 
* @struct FX
* @brief Definition of an foreign exchange risk factor 
*/
/**
 * @var std::unique_ptr<Currency> FX::counter_ccy_ptr
 * @brief The fx risk factor counter currency pointer.
 */

/** 
* @brief Foreign exchange risk factor constructor
* @param base_currency the base currency pointer
* @param counter_currency the counter currency pointer 
* @see Currency
* @see RiskFactor
*/
FX::FX(
    std::unique_ptr<Currency> base_currency, 
    std::unique_ptr<Currency> counter_currency): 
    counter_ccy_ptr(std::move(counter_currency)), 
    RiskFactor(get_id(), std::move(base_currency)){};
/** 
* @brief function to get the foreign exchange risk factror id 
* @return the concatenation between the base currency code 
* and the counter currency code
* @see Currency
*/
std::string FX::get_id()
{
    return base_ccy_ptr->code_ + counter_ccy_ptr->code_;
};
FX::~FX(){}; 

/** 
* @struct Crypto 
* @brief Definition of an cryptocurrency risk factor 
*/
/**
 * @var std::unique_ptr<Currency> Crypto::counter_ccy_ptr
 * @brief The crypto risk factor counter currency pointer.
 */

/** 
* @brief Cryptocurrency risk factor constructor
* @param base_currency the base currency pointer
* @param counter_currency the counter currency pointer
* @see Currency
*/
Crypto::Crypto(
    std::unique_ptr<Currency> base_currency, 
    std::unique_ptr<Currency> counter_currency): 
    counter_ccy_ptr(std::move(counter_currency)), 
    RiskFactor(get_id(), std::move(base_currency)){};
/** 
* @brief function to get the cryptocurrency risk factror id 
* @return the concatenation between the base currency code 
* and the counter currency code
* @see Currency
*/
std::string Crypto::get_id()
{
    return base_ccy_ptr->code_ + counter_ccy_ptr->code_;
};
Crypto::~Crypto(){}; 


