#pragma once
#include<vector>
#include<unordered_map>
#include"guest.h"
#include"room.h"
using namespace std;

vector<class room> hotel_room;
unordered_map<int,class guest_info> hotel_guest;
unordered_map<int,class checkin_record> guest_record;
