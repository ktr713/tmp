#ifndef __FEETABLE_HPP__
#define __FEETABLE_HPP__

class FeeTable{
    protected:
        int time_step;
        int time_step_value;
        int max_value;

    public:
        FeeTable();
        virtual ~FeeTable();
        virtual int  get_time_step();
        virtual int get_time_step_value();
        virtual int get_max_value();
};

class WeekdayDaytimeFeeTable : public FeeTable{
    public:
        WeekdayDaytimeFeeTable();
};

class WeekdayNighttimeFeeTable : public FeeTable{
    public:
        WeekdayNighttimeFeeTable();
};

class HolidayFeeTable : public FeeTable{
    public:
        HolidayFeeTable();
};

class ExtraDayFeeTable : public FeeTable{
    public:
        ExtraDayFeeTable();
};

#endif /*__FEETABLE_HPP__*/
