#ifndef __TOTALFEE_HPP__
#define __TOTALFEE_HPP__

#include <chrono>
#include "TableSwitchingLogic.hpp"
#include "FeeTable.hpp"

class TotalFee{
    protected:
        time_t entering_time;   // 入庫時間
        time_t leaving_time;    // 出庫時間
        int total_fee;              // 総額

        time_t current_time;    // 計算時間
        int current_fee;        // 現在料金テーブルの総額料金 

        int calc_total_fee();   // 総額料金を計算する。

    public:
        TotalFee(time_t entering_time, time_t leaving_time);
        int get_total_fee();    // 総額料金を返す。
};


#endif /*__TOTALFEE_HPP__*/