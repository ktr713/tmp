#include <iostream>

#include "TotalFee.hpp"
#include "TableSwitchingLogic.hpp"
#include "FeeTable.hpp"

TotalFee::TotalFee(time_t entering_time, time_t leaving_time){
    this->entering_time = entering_time;
    this->leaving_time = leaving_time;

    this->current_time = entering_time;
    this->total_fee = 0;
    this->current_fee = 0;
}

int TotalFee::get_total_fee(){
    this->calc_total_fee();
    return this->total_fee;
}

int TotalFee::calc_total_fee(){
    TableSwitchingLogic table_switchi_logic;
    FeeTable fee_table = table_switchi_logic.get_fee_table(this->entering_time);

    while(true){
        // 基本処理：料金加算→時間更新→出庫判定
        this->current_fee = std::min(this->current_fee + fee_table.get_time_step_value(),fee_table.get_max_value());   // 単位時間当たりの料金加算。ただし最大値は越えない。
        this->current_time += fee_table.get_time_step();    // 単位時間更新

        // 出庫判定：インクリメントしてから判定する→単位時間内の料金は必ず支払う
        if(this->current_time >= this->leaving_time){
            this->total_fee += this->current_fee;
            break;
        }

        // テーブル更新判定 : 次回テーブル料金が異なる場合
        if( 1 == table_switchi_logic.is_transition_next_table(this->current_time - fee_table.get_time_step(), fee_table)){
            fee_table = table_switchi_logic.get_fee_table(this->current_time);  // テーブル更新
            this->total_fee += this->current_fee;
            this->current_fee = 0;
        }

        // 最大料金超過判定：最大料金を超過しており，かつ超過した単位時間以内にテーブル料金を更新しない場合。
        // 次回料金計算開始時間にカレントタイムをセットし，テーブルを更新する。
        if(this->current_fee >= fee_table.get_max_value()){
            this->current_time = table_switchi_logic.get_next_table_time(this->current_time - fee_table.get_time_step(), fee_table);    // テーブル更新時間に更新

            // ここで出庫時間を越えた場合，breakする(しておかないと)
            if(this->current_time >= this->leaving_time){
                this->total_fee += this->current_fee;
                break;
            }
            fee_table = table_switchi_logic.get_fee_table(this->current_time);  // テーブル更新
            this->total_fee += this->current_fee;
            this->current_fee = 0;
        }
    }
    return RETURN_OK;
}