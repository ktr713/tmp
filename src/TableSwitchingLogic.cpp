#include "TableSwitchingLogic.hpp"

TableSwitchingLogic::TableSwitchingLogic(){};
TableSwitchingLogic::~TableSwitchingLogic(){};


FeeTable TableSwitchingLogic::get_fee_table(time_t current_time){
    int table_id = this->is_table_id(current_time);
    FeeTable fee_table = WeekdayDaytimeFeeTable();
    switch(table_id){
        case weekday_daytime_id:
            return fee_table = WeekdayDaytimeFeeTable();
            break;
        
        case weekday_nighttime_id:
            return fee_table = WeekdayNighttimeFeeTable();
            break;
        
        case holiday_id:
            return fee_table = HolidayFeeTable();
            break;
        
        case extra_day_id:
            return fee_table = ExtraDayFeeTable();
            break;
        
        default:
            return fee_table;
            break;
    }
}

time_t TableSwitchingLogic::get_next_table_time(time_t current_time, FeeTable fee_table){
    time_t judge_time = current_time;
    while(true){
        judge_time += fee_table.get_time_step();
        if(0 == this->is_same_table(current_time, judge_time)){
            break;
        }
    }

    judge_time -= fee_table.get_time_step();

    for(int i = 0; i < fee_table.get_time_step(); i+= 60){
        judge_time += 60;
        if(0 == this->is_same_table(current_time, judge_time)){
            break;
        }
    }

    return judge_time;
}

int TableSwitchingLogic::is_transition_next_table(time_t current_time, FeeTable fee_table){
    if(1 == this->is_same_table(current_time, current_time + fee_table.get_time_step())){
        return RETURN_NG;
    }else{
        return RETURN_OK;
    }
}

int TableSwitchingLogic::is_table_id(time_t current_time){
    if(this->is_extraday(current_time)){
        return extra_day_id;
    }

    if(this->is_holiday(current_time)){
        return holiday_id;
    }

    if(this->is_weekday(current_time)){
        if(this->is_daytime(current_time)){
            return weekday_daytime_id;
        }
        else if(this->is_nighttime(current_time)){
            return weekday_nighttime_id;
        }
    }
    else{
        return RETURN_NG;
    }

    return RETURN_NG;
}

int TableSwitchingLogic::is_same_table(time_t first_time, time_t second_time){
    int first_id = this->is_table_id(first_time);
    int second_id = this->is_table_id(second_time);

    if(first_id == second_id){
        return RETURN_OK;
    }
    else{
        return RETURN_NG;
    }
}

int TableSwitchingLogic::is_weekday(time_t current_time){
    struct tm * time_info = localtime(&current_time);

    if(time_info->tm_wday  == 0 || time_info->tm_wday == 6){
        return RETURN_NG;
    }
    else if(time_info->tm_wday == 1 || time_info->tm_wday == 2 || time_info->tm_wday == 3 || time_info->tm_wday == 4 || time_info->tm_wday == 5 ){
        return RETURN_OK;
    }
    else{
        return -1;
    }
}

int TableSwitchingLogic::is_holiday(time_t current_time){
    struct tm * time_info = localtime(&current_time);

    if(time_info->tm_wday  == 0 || time_info->tm_wday == 6){
        return RETURN_OK;
    }
    else if(time_info->tm_wday == 1 || time_info->tm_wday == 2 || time_info->tm_wday == 3 || time_info->tm_wday == 4 || time_info->tm_wday == 5 ){
        return RETURN_NG;
    }
    else{
        return -1;
    }
}

int TableSwitchingLogic::is_daytime(time_t current_time){
    struct tm * time_info = localtime(&current_time);
    if(time_info->tm_hour >= 7 && time_info->tm_hour <= 21){
        return RETURN_OK;
    }
    else if(time_info->tm_hour <= 6 || time_info->tm_hour >= 22){
        return RETURN_NG;
    }
    else{
        return -1;
    }
}

int TableSwitchingLogic::is_nighttime(time_t current_time){
    struct tm * time_info = localtime(&current_time);
    if(time_info->tm_hour >= 7 && time_info->tm_hour <= 21){
        return RETURN_NG;
    }
    else if(time_info->tm_hour <= 6 || time_info->tm_hour >= 22){
        return RETURN_OK;
    }
    else{
        return -1;
    }
}

int TableSwitchingLogic::is_extraday(time_t current_time){
    struct tm * time_info = localtime(&current_time);

    if(time_info->tm_mon == 0){
        if( time_info->tm_mday == 1 || time_info->tm_mday == 2 || time_info->tm_mday == 3){
            return RETURN_OK;
        }
        else{
            return RETURN_NG;
        }
    }else if(time_info->tm_mon == 11){
        if(time_info->tm_mday == 31){
            return RETURN_OK;
        }
        else{
            return RETURN_NG;
        }
    }
    else if(time_info->tm_mon == 7){
        if( time_info->tm_mday == 13 || time_info->tm_mday == 14 || time_info->tm_mday == 14){
            return RETURN_OK;
        }
        else{
            return RETURN_NG;
        }
    }

    return RETURN_NG;
}