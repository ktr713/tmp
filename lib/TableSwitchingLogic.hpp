#ifndef __TABLESWITCHINGLOGIC_HPP__
#define __TABLESWITCHINGLOGIC_HPP__

#include <chrono>
#include "DefType.hpp"
#include "FeeTable.hpp"

class TableSwitchingLogic{
    private:
        int is_same_table(time_t first_time, time_t second_time);

        int is_table_id(time_t current_time);

        int is_weekday(time_t current_time);
        int is_holiday(time_t current_time);
        int is_extraday(time_t current_time);
        int is_daytime(time_t current_time);
        int is_nighttime(time_t current_time);

        enum table_id{
            weekday_daytime_id = 1,
            weekday_nighttime_id = 2,
            holiday_id = 3,
            extra_day_id = 4
        };

    public:
        TableSwitchingLogic();
        ~TableSwitchingLogic();
        FeeTable get_fee_table(time_t current_time);
        int is_transition_next_table(time_t current_time, FeeTable current_fee_table);
        time_t get_next_table_time(time_t current_time, FeeTable current_fee_table);
};


#endif