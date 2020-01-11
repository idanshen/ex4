//
// Created by User on 1/4/2020.
//

#include "DataCenter.h"
ServerData::ServerData(int ServerID, int traffic):ServerID(ServerID),traffic(traffic){}

bool ServerData::operator<(ServerData &s) {
    if(this->traffic==s.traffic){
        return this->ServerID<s.ServerID;
    }
    return this->traffic<s.traffic;
}
bool ServerData::operator==(ServerData &s) {
    return this->traffic==s.traffic;
}


int ServerData::operator*() {
    return traffic;
}

int ServerData::getID() {
    return ServerID;
}

int ServerData::get_traffic() {
    return traffic;
}

int operator+(const int n, const ServerData &sd){
    return n + sd.traffic;
}
/*
DataCenter::DataCenter(int ID): ID(ID),NumOfServers(0) {
    auto *traffic_tree=new RankTree<ServerData>();
}

StatusType DataCenter::add_server(int ServerID,int traffic) {
    ServerData* new_s;
    try{
        new_s= new ServerData(ServerID,traffic);
    }
    catch(bad_alloc& b){
        return ALLOCATION_ERROR;
    }

    StatusType res=traffic_tree->insert(*new_s);
    return res;
}

StatusType DataCenter::remove_server(int ServerID) {
    StatusType res=traffic_tree->remove(ServerID);
    return res;
}
*/



