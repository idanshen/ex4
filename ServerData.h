#ifndef EX2_DATACENTER_H
#define EX2_DATACENTER_H

#include "RankTree.h"

class ServerData{
    int ServerID;
    int traffic;
public:
    ServerData(): ServerID(0), traffic(0) {};
    ServerData(int ServerID,int traffic);
    ServerData(const ServerData& s)=default;
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

#endif //EX2_DATACENTER_H
