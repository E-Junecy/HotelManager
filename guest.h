#pragma once
#include<string>
using namespace std;

//定义入住状态枚举类型
enum checkin_status{
    no_record,
    stay,
    departure,
    booking,
};

//用户个人信息
class guest_info{
private:
    string name;
    int age;
    int ID;
    
public:
    string get_name();
    int get_age();
    int get_ID();
    guest_info();
};

//用户入住信息
class checkin_record{
private:
    int guest_ID;
    checkin_status status;
    int room_number;
    string checkin_time;
    string checkout_time;

public:
    int get_ID();
    checkin_status get_status();
    int get_room_number();
    string get_checkin_time();
    string get_checkout_time();
    void check_in(int guestID,int num,string in_time,string out_time);
    void check_out(string out_time);
    void reserve(int guestID,int num,string in_time,string out_time);
    void change_room(int new_room_num);
    checkin_record();
};