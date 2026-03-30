#pragma once
#include<vector>
using namespace std;

//定义房间类型枚举类型
enum room_type{
    single,
    standard,
    suite,
    family,
};

//定义房间状态枚举类型
enum room_status{
    no_guest,
    stayed,
    reserved,
};

//客房基本信息
class room{
private:
    double price;
    room_type type;
    room_status status;
    int room_num;
    vector<int> guest_in_house;
public:
    double get_price();
    room_type get_type();
    room_status get_status();
    int get_num();
    vector<int> get_guest();
    void add_guest(int ID);
    void reserve_guest(int ID);
    void clear_guest();
    room::room();
};
