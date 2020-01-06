//
// Created by User on 1/4/2020.
//

#include "DataCenter.h"
ServerNode::ServerNode(int ServerID, int traffic):ServerID(ServerID),traffic(traffic){}

bool ServerNode::operator<(ServerNode &s) {
    if(this->traffic==s.traffic){
        return this->ServerID<s.ServerID;
    }
    return this->traffic<s.traffic;
}
bool ServerNode::operator==(ServerNode &s) {
    return this->traffic==s.traffic;
}


int ServerNode::operator*() {
    return traffic;
}

int ServerNode::getID() {
    return ServerID;
}

int ServerNode::get_traffic() {
    return traffic;
}

DataCenter::DataCenter(int ID): ID(ID),NumOfServers(0) {
    auto *traffic_tree=new RankTree<ServerNode>();
}

StatusType DataCenter::add_server(int ServerID,int traffic) {
    ServerNode* new_s;
    try{
        new_s= new ServerNode(ServerID,traffic);
    }
    catch(bad_alloc& b){
        return ALLOCATION_ERROR;
    }

    StatusType res=traffic_tree->insert(*new_s);
    return res;
}
StatusType DataCenter::remove_server(int ServerID) {
    traffic_tree->find()
    StatusType res=traffic_tree->remove(ServerID);
    return res;
}



