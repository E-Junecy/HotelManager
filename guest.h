#pragma once
#include<string>
using namespace std;

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
    int status;//0：不存在，1：入住，2：退房，3：预订
    int room_number;
    string checkin_time;
    string checkout_time;

public:
    int get_ID();
    int get_status();
    int get_room_number();
    string get_checkin_time();
    string get_checkout_time();
    void check_in(int guestID,int num,string in_time,string out_time);
    void check_out();
    void reserve(int guestID,int num,string in_time,string out_time);
    checkin_record();
};