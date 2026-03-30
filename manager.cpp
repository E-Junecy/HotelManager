#include<iostream>
#include"manager.h"

bool manager::add_room(room class_room){
    for(vector<room>::iterator it=hotel_room.begin();it!=hotel_room.end();it++){
       int tem=it->get_num();
       int room_num=class_room.get_num();
       if(room_num==tem)return false;
    }
    hotel_room.push_back(class_room);
    return true;
}
bool manager::delete_room(int room_num){
    for(vector<room>::iterator it=hotel_room.begin();it!=hotel_room.end();it++){
        int num=it->get_num();
        if(num==room_num){
            room_status status=it->get_status();
            if(status==no_guest){
                hotel_room.erase(it);
                return true;
            }
            else return false;
        }
    }
    return false;
}

vector<int> manager::get_empty_room(){
    vector<int> empty_room;
    for(vector<room>::iterator it=hotel_room.begin();it!=hotel_room.end();it++){
        room_status status=it->get_status();
        if(status==no_guest){
            empty_room.push_back(it->get_num());
        }
    }
    return empty_room;
}
vector<int> manager::get_empty_room(room_type type){
    vector<int> empty_room;
    for(vector<room>::iterator it=hotel_room.begin();it!=hotel_room.end();it++){
        room_status status=it->get_status();
        if(status==no_guest){
            if(it->get_type()==type){
                empty_room.push_back(it->get_num());
            }
        }
    }
    return empty_room;
}
