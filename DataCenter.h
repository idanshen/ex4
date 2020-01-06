//
// Created by User on 1/4/2020.
//

#ifndef EX2_DATACENTER_H
#define EX2_DATACENTER_H

#include "StatusType.h"
#include "RankTree.h"

class ServerNode{
    int ServerID;
    int traffic;
public:
    ServerNode(int ServerID,int traffic);
    ~ServerNode()=default;
    bool operator<(ServerNode& s);
    bool operator==(ServerNode& s);
    int operator*();
    int getID();
    int get_traffic();


};
class DataCenter{
    RankTree<ServerNode>* traffic_tree;
    int ID;
    int NumOfServers;
public:
    DataCenter(int ID);
    ~DataCenter()=default;
    StatusType add_server(int ServerID,int traffic);
    StatusType remove_server(int ServerID);



};
#endif //EX2_DATACENTER_H
