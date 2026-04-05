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

//重载定义查找空房间函数
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

bool manager::guest_check_in(int ID, int room_num, string in_time, string out_time){
    auto it_ID = hotel_guest.find(ID);
    if(it_ID == hotel_guest.end())return false;
    for(vector<room>::iterator it_room = hotel_room.begin(); it_room != hotel_room.end(); it_room++){
        if(it_room->get_num() == room_num){
            room_status status = it_room->get_status();
            if(status == stayed)return false;
            else if(status == reserved){
                vector<int>& tem = it_room->get_guest();
                if(tem[0] == ID){
                    it_room->clear_guest();
                    it_room->add_guest(ID);
                    checkin_record record;
                    record.check_in(ID, room_num, in_time, out_time);
                    guest_record[ID] = record;
                    return true;
                }
                else return false;
            }
            else if(status == no_guest){
                it_room->add_guest(ID);
                checkin_record record;
                record.check_in(ID, room_num, in_time, out_time);
                guest_record[ID] = record;
                return true;
            }
        }
    }
    return false;
}
bool manager::guest_reserve(int ID, int room_num, string in_time, string out_time){
    auto it_ID = hotel_guest.find(ID);
    if(it_ID == hotel_guest.end())return false;
    for(vector<room>::iterator it_room = hotel_room.begin(); it_room != hotel_room.end(); it_room++){
        if(it_room->get_num() == room_num){
            room_status status = it_room->get_status();
            if(status == stayed||status == reserved)return false;
            else if(status == no_guest){
                it_room->reserve_guest(ID);
                checkin_record record;
                record.reserve(ID, room_num, in_time, out_time);
                guest_record[ID] = record;
                return true;
            }
        }
    }
    return false;
}
bool manager::guest_check_out(int ID,int room_num){
    
}