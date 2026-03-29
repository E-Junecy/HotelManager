#include<iostream>
#include"guest.h"

//一长串函数定义
//用户信息相关成员函数定义
string guest_info::get_name(){
    return name;
}
int guest_info::get_age(){
    return age;
}
int guest_info::get_ID(){
    return ID;
}
guest_info::guest_info(){
    name={};
    age=0;
    ID=0;
}

//用户入住信息相关成员函数定义
int checkin_record::get_ID(){
    return guest_ID;
}
int checkin_record::get_status(){
    return status;
}
int checkin_record::get_room_number(){
    return room_number;
}
string checkin_record::get_checkin_time(){
    return checkin_time;
}
string checkin_record::get_checkout_time(){
    return checkout_time;
}
void checkin_record::check_in(int guestID,int num,string in_time,string out_time){
    status=1;
    guest_ID=guestID;
    room_number=num;
    checkin_time=in_time;
    checkout_time=out_time;
}
void checkin_record::check_out(){
    status=2;
}
void checkin_record::reserve(int guestID,int num,string in_time,string out_time){
    status=3;
    guest_ID=guestID;
    room_number=num;
    checkin_time=in_time;
    checkout_time=out_time;
}
checkin_record::checkin_record(){
    status=0;
    guest_ID=0;
    room_number=0;
    checkin_time={};
    checkout_time={};
}