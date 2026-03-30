#include<iostream>
#include"room.h"

double room::get_price(){
    return price;
}
room_type room::get_type(){
    return type;
}
room_status room::get_status(){
    return status;
}
int room::get_num(){
    return room_num;
}
vector<int> room::get_guest(){
    return guest_in_house;
}
void room::add_guest(int ID){
    status=stayed;
    guest_in_house.push_back(ID);
}
void room::reserve_guest(int ID){
    status=reserved;
    guest_in_house.push_back(ID);
}
void room::clear_guest(){
    status=no_guest;
    guest_in_house.clear();
}
room::room(){
    type=single;
    status=no_guest;
    room_num=0;
}