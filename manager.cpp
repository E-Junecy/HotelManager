#include <ctime>
#include<iostream>
#include"manager.h"

// 获取当前系统时间，返回字符串：2026-04-05 15:30
string get_now_time() {
    time_t now = time(0);
    tm *ltm = localtime(&now);
    char buf[50];
    sprintf(buf, "%04d-%02d-%02d %02d:%02d",
            ltm->tm_year + 1900,
            ltm->tm_mon + 1,
            ltm->tm_mday,
            ltm->tm_hour,
            ltm->tm_min);
    return string(buf);
}
// 计算两个时间之间的天数
int calculate_days(string time1, string time2) {
    tm t1 = {}, t2 = {};
    sscanf(time1.c_str(), "%d-%d-%d", &t1.tm_year, &t1.tm_mon, &t1.tm_mday);
    sscanf(time2.c_str(), "%d-%d-%d", &t2.tm_year, &t2.tm_mon, &t2.tm_mday);

    t1.tm_year -= 1900;
    t1.tm_mon -= 1;
    t2.tm_year -= 1900;
    t2.tm_mon -= 1;

    time_t a = mktime(&t1);
    time_t b = mktime(&t2);
    double diff = difftime(b, a);
    return (int)(diff / (24 * 60 * 60));
}
// 根据当前时间 + 天数，自动算出退房时间
string get_end_time(string startTime, int days) {
    tm t = {};
    sscanf(startTime.c_str(), "%d-%d-%d %d:%d",
           &t.tm_year, &t.tm_mon, &t.tm_mday,
           &t.tm_hour, &t.tm_min);

    t.tm_year -= 1900;
    t.tm_mon -= 1;

    time_t sec = mktime(&t);
    sec += (time_t)(days - 1) * 24 * 60 * 60;

    tm* end_tm = localtime(&sec);
    char buf[100];
    // 输出格式：年-月-日 12:00
    strftime(buf, sizeof(buf), "%Y-%m-%d 12:00", end_tm);
    return buf;
}

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

//登记入住等相关操作
bool manager::guest_check_in(int ID, int room_num,int days){
    auto it_ID = hotel_guest.find(ID);
    if(it_ID == hotel_guest.end())return false;

    string in_time = get_now_time();
    string out_time = get_end_time(in_time, days);

    for(vector<room>::iterator it_room = hotel_room.begin(); it_room != hotel_room.end(); it_room++){
        if(it_room->get_num() == room_num){
            //根据房间类型确认入住方式
            room_status status = it_room->get_status();
            if(status == stayed)return false;
            else if(status == reserved){
                //预定客户到达，正式登记入住
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
                //普通现场入住
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
bool manager::guest_reserve(int ID, int room_num, int days){
    auto it_ID = hotel_guest.find(ID);
    if(it_ID == hotel_guest.end())return false;

    string in_time = get_now_time();
    string out_time = get_end_time(in_time, days);

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
bool manager::guest_check_out(int ID, int room_num) {
    auto it_ID = hotel_guest.find(ID);
    if (it_ID == hotel_guest.end()) return false;
    for (auto it_room = hotel_room.begin(); it_room != hotel_room.end(); ++it_room) {
        if (it_room->get_num() == room_num) {
            room_status status = it_room->get_status();
            if (status == no_guest) return false;
            vector<int>& guests = it_room->get_guest();
            if (guests[0] != ID) return false;
            auto record_it = guest_record.find(ID);
            if (record_it != guest_record.end()) {
                record_it->second.check_out(get_now_time());
            }
            it_room->clear_guest();
            guest_record.erase(ID);
            return true;
        }
    }
    return false;
}
bool manager::guest_change_room(int ID, int old_room_num, int new_room_num) {
    // 验证用户是否存在
    auto it_ID = hotel_guest.find(ID);
    if (it_ID == hotel_guest.end())return false;
    room* old_room = nullptr;
    room* new_room = nullptr;

    //查找新旧房间
    for (auto& it : hotel_room) {
        if (it.get_num() == old_room_num) {
            old_room = &it;
        }
        if (it.get_num() == new_room_num) {
            new_room = &it;
        }
    }
    if (!old_room || !new_room) {
        return false;
    }
    // 验证旧房间
    vector<int>& guests = old_room->get_guest();
    if (guests.empty() || guests[0] != ID) {
        return false;
    }
    // 验证新房间
    if (new_room->get_status() != no_guest) {
        return false;
    }
    //清空旧房间
    room_status old_status = old_room->get_status();
    old_room->clear_guest();
    //搬入新房间
    if (old_status == stayed) {
        new_room->add_guest(ID);
    } 
    else if (old_status == reserved) {
        new_room->reserve_guest(ID);
    }
    //修改酒店登记入住信息
    auto it_record = guest_record.find(ID);
    if (it_record != guest_record.end()) {
        it_record->second.change_room(new_room_num);
    }
    return true;
}

int manager::get_guest_id(int room_num){
    for (auto& room : hotel_room) {
        if (room.get_num() == room_num) {
            auto& guests = room.get_guest();
            if (!guests.empty()) {
                return guests[0];
            }
        }
    }
    return -1; // 无客人
}
//获取用户信息
bool manager::get_guest_info(int room_num, guest_info& info){
    int ID=get_guest_id(room_num);
    if(ID==-1)return false;
    auto it=hotel_guest.find(ID);
    if(it!=hotel_guest.end()){
        info=it->second;
        return true;
    }
    return false;
}
//获取预定天数
int manager::get_guest_days(int room_num, checkin_record& record) {
    int id = get_guest_id(room_num);
    if (id == -1) return -1;
    auto it = guest_record.find(id);
    if (it == guest_record.end()) return -1;

    record = it->second;
    string in = record.get_checkin_time();
    string out = record.get_checkout_time();
    return calculate_days(in, out); 
}