#ifndef EX2_DATACENTERMANAGER_H
#define EX2_DATACENTERMANAGER_H

#include "HashTable.h"
#include "UnionFind.h"
#include "RankTree.h"
#include "StatusType.h"
#include "ServerData.h"

class DataCenterManager {
    UnionFind<RankTree<ServerData>> dc_unionfind;
    HashTable dc_hashtable;
    RankTree<ServerData> main_tree;
    int size;
public:
    explicit DataCenterManager(int n);
    ~DataCenterManager() = default;
    StatusType AddServer(int dataCenterID, int serverID);
    StatusType SetTraffic(int serverID, int traffic);
    StatusType RemoveServer(int serverID);
    StatusType SumHighestTrafficServers(int dataCenterID, int k, int *traffic);
    StatusType MergeDataCenters(int dataCenter1, int dataCenter2);
};


#endif //EX2_DATACENTERMANAGER_H
