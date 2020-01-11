//
// Created by User on 1/4/2020.
//

#ifndef EX2_DATACENTER_H
#define EX2_DATACENTER_H

#include "StatusType.h"
#include "RankTree.h"

class ServerData{
    int ServerID;
    int traffic;
public:
    ServerData(): ServerID(0), traffic(0) {};
    ServerData(int ServerID,int traffic);
    ~ServerData()=default;
    bool operator<(ServerData& s);
    bool operator==(ServerData& s);
    friend int operator+(const int n, const ServerData &sd);
    bool operator!() { return (ServerID==0);};
    int operator*();
    int getID();
    int get_traffic();
    void set_traffic(int t);
};
/*
class DataCenter{
    RankTree<ServerData>* traffic_tree;
    int ID;
    int NumOfServers;
public:
    explicit DataCenter(int ID);
    ~DataCenter()=default;
    StatusType add_server(int ServerID,int traffic);
    StatusType remove_server(int ServerID);
};
*/
#endif //EX2_DATACENTER_H
