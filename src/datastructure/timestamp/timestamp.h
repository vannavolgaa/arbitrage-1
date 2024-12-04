#pragma once
#include <iostream>

class NegativeEpochTimestamp: public std::exception 
{public: const char * what() const throw();};

class NegativeYearFraction: public std::exception 
{public: const char * what() const throw();};

enum EpochTimestampType
{
    SECONDS = 1, 
    MILLISECONDS = 1000, 
    MICROSECONDS = 1000000, 
    NANOSECONDS = 1000000000 
};

enum DayCountConvention {ACT360, ACT365, ACT364};

struct EpochTimestamp
{
    long long tmsp; 
    EpochTimestampType type_; 
    EpochTimestamp(const long long& timestamp, const EpochTimestampType& type);
    ~EpochTimestamp();
};


struct TimeDelta
{
    long long d; 
    long long h; 
    long long m; 
    long long s; 
    long long ms; 
    long long mcs;
    long long ns;
    TimeDelta(
        const long long& days = 0, 
        const long long& hours = 0, 
        const long long& minutes = 0, 
        const long long& seconds = 0, 
        const long long& milliseconds = 0, 
        const long long& microseconds = 0, 
        const long long& nanoseconds = 0);
    ~TimeDelta();
    double get_total_seconds();
    double get_total_milliseconds();
    double get_total_microseconds();
    double get_total_nanoseconds();
}; 

EpochTimestamp convert_timestamp(EpochTimestamp timestamp, EpochTimestampType type);

EpochTimestamp apply_timedelta(EpochTimestamp timestamp, TimeDelta timedelta); 

TimeDelta get_time_delta(
    EpochTimestamp start_timestamp, 
    EpochTimestamp end_timestamp, 
    EpochTimestampType delta_type);

double get_year_fraction(
    EpochTimestamp start_timestamp, 
    EpochTimestamp end_timestamp, 
    DayCountConvention convention); 
