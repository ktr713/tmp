#include <chrono>
#include <iostream>
#include "TotalFee.hpp"

int main(){
    time_t entering_time;
    time_t leaving_time;

    std::cout << "test start" << std::endl;

    struct tm time_info_morning = {};
    struct tm time_info_noon = {};
    struct tm time_info_evening = {};
    struct tm time_info_night = {};

    time_info_morning.tm_year = 2023 - 1900;
    time_info_morning.tm_mon = 12 - 1;
    time_info_morning.tm_mday = 1;
    time_info_morning.tm_hour = 7;
    time_info_morning.tm_min = 0;

    time_info_noon.tm_year = 2023 - 1900;
    time_info_noon.tm_mon = 12 - 1;
    time_info_noon.tm_mday = 1;
    time_info_noon.tm_hour = 9;
    time_info_noon.tm_min = 0;
    
    time_info_evening.tm_year = 2023 - 1900;
    time_info_evening.tm_mon = 12 - 1;
    time_info_evening.tm_mday = 1;
    time_info_evening.tm_hour = 21;
    time_info_evening.tm_min = 0;

    time_info_night.tm_year = 2023 - 1900 ;
    time_info_night.tm_mon = 12 - 1;
    time_info_night.tm_mday = 1;
    time_info_night.tm_hour = 23;
    time_info_night.tm_min = 59;

    std::cout << " ====================" << std::endl;
    std::cout << " >> first test : ";
    entering_time = mktime(&time_info_morning);
    leaving_time = mktime(&time_info_noon);
    std::cout << asctime(localtime(&entering_time)) << " ~ " << asctime(localtime(&leaving_time)) << std::endl;

    TotalFee total_fee = TotalFee(entering_time, leaving_time);
    std::cout << "total is " << total_fee.get_total_fee() << std::endl;

    std::cout << " ====================" << std::endl;
    std::cout << " >> second test" << std::endl;
    entering_time = mktime(&time_info_morning);
    leaving_time = mktime(&time_info_evening);
    std::cout << asctime(localtime(&entering_time)) << " ~ " << asctime(localtime(&leaving_time)) << std::endl;

    total_fee = TotalFee(entering_time, leaving_time);
    std::cout << "total is " << total_fee.get_total_fee() << std::endl;

    std::cout << " ====================" << std::endl;
    std::cout << " >> third test" << std::endl;
    entering_time = mktime(&time_info_evening);
    leaving_time = mktime(&time_info_night);
    std::cout << asctime(localtime(&entering_time)) << " ~ " << asctime(localtime(&leaving_time)) << std::endl;

    total_fee = TotalFee(entering_time, leaving_time);
    std::cout << "total is " << total_fee.get_total_fee() << std::endl;

    std::cout << " ====================" << std::endl;
    std::cout << " >> fourth test" << std::endl;
    entering_time = mktime(&time_info_morning);
    leaving_time = mktime(&time_info_night);
    std::cout << asctime(localtime(&entering_time)) << " ~ " << asctime(localtime(&leaving_time)) << std::endl;

    total_fee = TotalFee(entering_time, leaving_time);
    std::cout << "total is " << total_fee.get_total_fee() << std::endl;
}