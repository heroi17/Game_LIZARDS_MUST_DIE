#pragma once
#ifndef PhysTimeObj
#define PhysTimeObj
struct TimeObject {
private:
	double Time_in_second;
public:
	TimeObject(double Time_in_second = 0.): Time_in_second(Time_in_second){}
	double get_time_in_second() const { return Time_in_second; }
	double get_time_in_msecond() const { return Time_in_second*1000; }
	double get_time_in_mksecond() const { return Time_in_second*1000000; }
};
#endif /* PhysTimeObj */