#pragma once
#include<vector>
#include<unordered_map>
#include"guest.h"
#include"room.h"
using namespace std;

class manager{
private:
    vector<class room> hotel_room;
    unordered_map<int,class guest_info> hotel_guest;
    unordered_map<int,class checkin_record> guest_record;

public:
    bool add_room(room class_room);
    bool delete_room(int room_num);

    vector<int> get_empty_room();
    vector<int> get_empty_room(room_type type);

    bool guest_check_in(int ID,int room_num, int days);
    bool guest_reserve(int ID,int room_num, int days);
    bool guest_check_out(int ID,int room_num);
    bool guest_change_room(int ID, int old_room_num, int new_room_num);

    int get_guest_id(int room_num);
    bool get_guest_info(int room_num, guest_info& info);
    int get_guest_days(int room_num, checkin_record& record);
};
