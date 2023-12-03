#include "FeeTable.hpp"

// 特に何もしない
FeeTable::FeeTable(){};
//特に何もしない
FeeTable::~FeeTable(){};

int FeeTable::get_max_value(){
    return this->max_value;
}

int FeeTable::get_time_step(){
    return this->time_step;
}

int FeeTable::get_time_step_value(){
    return this->time_step_value;
}

WeekdayDaytimeFeeTable::WeekdayDaytimeFeeTable(){
    this->max_value = 1800;      // 900 yen
    this->time_step = 20*60;    // 20 min
    this->time_step_value = 200;   // 200 yen
}

WeekdayNighttimeFeeTable::WeekdayNighttimeFeeTable(){
    this->max_value = 300;      // 300 yen
    this->time_step = 60*60;    // 60 min
    this->time_step_value = 100;   // 200 yen
}

HolidayFeeTable::HolidayFeeTable(){
    this->max_value = 2000;
    this->time_step = 60*60;
    this->time_step_value = 200;
}

ExtraDayFeeTable::ExtraDayFeeTable(){
    this->max_value = 2000;
    this->time_step = 60*60;
    this->time_step_value = 200;
}
