#include "timestamp.h"

/** 
* @file timestamp.h
* @brief This file defined the epoch timestamp and time delta objects used within Arbitrage. 
*/

/** 
 * @enum EpochTimestampType
 * @brief Enumeration of all defined epoch timestamp type.
 */
/**
 * @var EpochTimestampType EpochTimestampType::SECONDS
 * @brief Epoch timestamp in seconds.
 */
/**
 * @var EpochTimestampType EpochTimestampType::MILLISECONDS
 * @brief Epoch timestamp in milliseconds.
 */
/**
 * @var EpochTimestampType EpochTimestampType::MICROSECONDS
 * @brief Epoch timestamp in miroseconds.
 */
/**
 * @var EpochTimestampType EpochTimestampType::NANOSECONDS
 * @brief Epoch timestamp in nanoseconds.
 */

/** 
 * @enum DayCountConvention
 * @brief Enumeration of all defined day count convention.
 */
/**
 * @var DayCountConvention DayCountConvention::ACT365
 * @brief Actual days difference by 365 days/year base.
 */
/**
 * @var DayCountConvention DayCountConvention::ACT364
 * @brief Actual days difference by 364 days/year base.
 */
/**
 * @var DayCountConvention DayCountConvention::ACT360
 * @brief Actual days difference by 360 days/year base.
 */

/** 
 * @class NegativeEpochTimestamp
 * @brief Definition of negative timestamp error.
 */
/** 
 * @brief Definition of what() virtual std::exception function.
 * @return The explication of the error.
 */
const char * NegativeEpochTimestamp::what() const throw(){
    return "A timestamp value cannot be negative.";
};

/** 
 * @class NegativeYearFraction
 * @brief Definition of negative year fraction error.
 */
/** 
 * @brief Definition of what() virtual std::exception function.
 * @return The explication of the error.
 */
const char * NegativeYearFraction::what() const throw(){
    return "A year fraction cannot be negative.";
};

/** 
 * @struct EpochTimestamp
 * @brief Definition of an epoch timestamp.
 * @see EpochTimestampType 
 */
/**
 * @var long long EpochTimestamp::tmsp
 * @brief The epoch timestamp value.
 */
/**
 * @var EpochTimestampType EpochTimestamp::type_
 * @brief The epoch timestamp type. 
 */
/**
 * @brief The EpochTimestamp constructor. 
 * @param timestamp The epoch timestamp value.
 * @param type The epoch timestamp type.
 * @throws Throw NegativeEpochTimestamp if the epoch 
 * timestamp value is negative.
 * @see EpochTimestampType
 * @see NegativeEpochTimestamp
 */
EpochTimestamp::EpochTimestamp(
    const long long& timestamp, 
    const EpochTimestampType& type): 
    tmsp(timestamp), type_(type)
{
    if (tmsp<0){throw NegativeEpochTimestamp();}
};
EpochTimestamp::~EpochTimestamp(){}; 

/** 
 * @struct TimeDelta
 * @brief Definition of a time difference.
 */
/**
 * @var long long TimeDelta::d
 * @brief The epoch timestamp value.
 */
/**
 * @var long long TimeDelta::h
 * @brief The epoch timestamp type. 
 */
/**
 * @var long long TimeDelta::m
 * @brief The epoch timestamp value.
 */
/**
 * @var long long TimeDelta::s
 * @brief The epoch timestamp type. 
 */
/**
 * @var long long TimeDelta::ms
 * @brief The epoch timestamp value.
 */
/**
 * @var long long TimeDelta::mcs
 * @brief The epoch timestamp type. 
 */
/**
 * @var long long TimeDelta::ns
 * @brief The epoch timestamp type. 
 */
/**
 * @brief TimeDelta constructor. 
 * @param days The number of days to account in time difference.
 * @param hours The number of hours to account in time difference. 
 * @param minutes The number of minutes to account in time difference. 
 * @param seconds The number of seconds to account in time difference. 
 * @param milliseconds The number of milliseconds to account in time difference. 
 * @param microseconds The number of microseconds to account in time difference.
 * @param nanoseconds The number of nanoseconds to account in time difference. 
 */
TimeDelta::TimeDelta(
    const long long& days, 
    const long long& hours, 
    const long long& minutes, 
    const long long& seconds, 
    const long long& milliseconds, 
    const long long& microseconds, 
    const long long& nanoseconds): 
    d(days), h(hours), m(minutes), s(seconds), 
    ms(milliseconds), mcs(microseconds),
    ns(nanoseconds){};
TimeDelta::~TimeDelta(){}; 
/**
 * @brief Calculates the total time delta in seconds. 
 * @return The total number of seconds. 
 */

double TimeDelta::get_total_seconds()
{
    long long day_s = d*24*60*60; 
    long long hour_s = h*60*60; 
    long long min_s = m*60; 
    long long micros_s = round(mcs/EpochTimestampType::MICROSECONDS); 
    long long millis_s = round(ms/EpochTimestampType::MILLISECONDS); 
    long long nanos_s = round(ns/EpochTimestampType::NANOSECONDS); 
    return s+day_s+hour_s+min_s+micros_s+millis_s+nanos_s;
}
/**
 * @brief Calculates the total time delta in milliseconds. 
 * @return The total number of milliseconds. 
 */
double TimeDelta::get_total_milliseconds()
{
    long long day_s = d*24*60*60; 
    long long hour_s = h*60*60; 
    long long min_s = m*60; 
    long long total_seconds = s+day_s+hour_s+min_s;
    long long micros_ms = round(mcs*EpochTimestampType::MILLISECONDS/
    EpochTimestampType::MICROSECONDS); 
    long long nanos_ms = round(ns*EpochTimestampType::MILLISECONDS/
    EpochTimestampType::NANOSECONDS); 
    return total_seconds*1000 + ms + micros_ms + nanos_ms;
}
/**
 * @brief Calculates the total time delta in microseconds. 
 * @return The total number of microseconds. 
 */
double TimeDelta::get_total_microseconds()
{
    long long day_s = d*24*60*60; 
    long long hour_s = h*60*60; 
    long long min_s = m*60; 
    long long total_seconds = s+day_s+hour_s+min_s;
    long long total_milliseconds = total_seconds*1000+ms;
    long long nanos_ms = round(ns*EpochTimestampType::MICROSECONDS/
    EpochTimestampType::NANOSECONDS); 
    return total_milliseconds*1000+mcs+nanos_ms;
}
/**
 * @brief Calculates the total time delta in nanoseconds. 
 * @return The total number of nanoseconds. 
 */
double TimeDelta::get_total_nanoseconds()
{
    long long day_s = d*24*60*60; 
    long long hour_s = h*60*60; 
    long long min_s = m*60; 
    long long total_seconds = s+day_s+hour_s+min_s;
    long long total_milliseconds = total_seconds*1000+ms;
    long long total_microseconds = total_milliseconds*1000+mcs;
    return total_microseconds*1000+ns;
}

/** 
 *  @brief This function convert a epoch timestamp into a new epoch timestamp 
 *  with a specific type.
 *  @param timestamp Initial epoch timestamp to be converted.
 *  @param type Epoch timestamp type to convert into.
 *  @see EpochTimestamp
 *  @see EpochTimestampType
 *  @result the new epoch timestamp with the chosen epoch timestamp type.
 */
EpochTimestamp convert_timestamp(EpochTimestamp timestamp, EpochTimestampType type)
{
    long long type1 = type;
    long long type2 = timestamp.type_;
    double factor = type1/type2;
    long long new_tmsp = round(factor*timestamp.tmsp);
    return EpochTimestamp(new_tmsp, type);
};

/** 
 *  @brief This function gives the new epoch timestamp with respect 
 *  to the time difference object TimeDelta.
 *  @param timestamp Initial epoch timestamp. 
 *  @param timedelta The time delta object. 
 *  @throws NegativeEpochTimestamp if timedelta value is too important.
 *  @see EpochTimestamp
 *  @see TimeDelta
 *  @result the new epoch timestamp with the chosen epoch timestamp type.
 */
EpochTimestamp apply_timedelta(EpochTimestamp timestamp, TimeDelta timedelta)
{
    switch(timestamp.type_){
        case EpochTimestampType::SECONDS: 
        {
            long long new_tmsp = timestamp.tmsp+timedelta.get_total_seconds();
            return EpochTimestamp(new_tmsp, EpochTimestampType::SECONDS);
        }
        case EpochTimestampType::MILLISECONDS: 
        {
            long long new_tmsp = timestamp.tmsp+timedelta.get_total_milliseconds();
            return EpochTimestamp(new_tmsp, EpochTimestampType::MILLISECONDS);
        }
        case EpochTimestampType::MICROSECONDS: 
        {
            long long new_tmsp = timestamp.tmsp+timedelta.get_total_microseconds();
            return EpochTimestamp(new_tmsp, EpochTimestampType::MICROSECONDS);
        }
        case EpochTimestampType::NANOSECONDS: 
        {
            long long new_tmsp = timestamp.tmsp+timedelta.get_total_nanoseconds();
            return EpochTimestamp(new_tmsp, EpochTimestampType::NANOSECONDS);
        }
    }
};

/** 
 *  @brief This function compute the time delta from two epoch timestamps.
 *  @param start_timestamp Start epoch timestamp.
 *  @param end_timestamp End epoch timestamp.
 *  @param delta_type The epoch timestamp type in which epoch timestamp must 
 *  be converted into.
 *  @see EpochTimestamp
 *  @see EpochTimestampType
 *  @result The time delta object corresponding to the time difference 
 *  between the end timestamp and the start timestamp.
 */
TimeDelta get_time_delta(
    EpochTimestamp start_timestamp, 
    EpochTimestamp end_timestamp, 
    EpochTimestampType delta_type)
{
    EpochTimestamp new_start_timestamp = convert_timestamp(
        start_timestamp, 
        delta_type);
    EpochTimestamp new_end_timestamp = convert_timestamp(
        end_timestamp, 
        delta_type);
    long long delta = new_end_timestamp.tmsp - new_start_timestamp.tmsp; 
    switch(delta_type){
        case EpochTimestampType::SECONDS: 
        {
            return TimeDelta(0,0,0,delta);
        }
        case EpochTimestampType::MILLISECONDS: 
        {
            return TimeDelta(0,0,0,0,delta,0,0);
        }
        case EpochTimestampType::MICROSECONDS: 
        {
            return TimeDelta(0,0,0,0,0,delta,0);
        }
        case EpochTimestampType::NANOSECONDS: 
        {
            return TimeDelta(0,0,0,0,0,0,delta);
        }
    }
};

/** 
 *  @brief This function calculates the year fraction between two dates 
 *  based on a day count convention. 
 *  @param start_timestamp Start epoch timestamp.
 *  @param end_timestamp End epoch timestamp.
 *  @param convention The day count convention.
 *  @throws NegativeYearFraction
 *  @see EpochTimestamp
 *  @see DayCountConvention
 *  @see NegativeYearFraction
 *  @result The year fraction.
 */
double get_year_fraction(
    EpochTimestamp start_timestamp, 
    EpochTimestamp end_timestamp, 
    DayCountConvention convention)
{
    TimeDelta dt = get_time_delta(
        start_timestamp,
        end_timestamp, 
        EpochTimestampType::NANOSECONDS); 
    long long total_ns = dt.get_total_nanoseconds();
    if (total_ns<0){throw NegativeYearFraction();}
    long long day_in_s = 24*60*60;
    long long day_in_ns = day_in_s*EpochTimestampType::NANOSECONDS;
    switch (convention)
    {
    case DayCountConvention::ACT360:{return double(total_ns)/double(360*day_in_ns);}
    case DayCountConvention::ACT365:{return double(total_ns)/double(365*day_in_ns);}
    case DayCountConvention::ACT364:{return double(total_ns)/double(364*day_in_ns);}
    }
};
