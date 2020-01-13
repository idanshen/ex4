#include "ServerData.h"

ServerData::ServerData(int ServerID, int traffic):ServerID(ServerID),traffic(traffic){}
bool ServerData::operator<(ServerData &s) {
    if(this->traffic==s.traffic){
        return this->ServerID<s.ServerID;
    }
    return this->traffic<s.traffic;
}
bool ServerData::operator==(ServerData &s) {
    return (this->traffic==s.traffic)&(this->ServerID==s.ServerID);
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

void ServerData::set_traffic(int t) {traffic = t;}
