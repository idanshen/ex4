#ifndef EX2_DATACENTERMANAGER_H
#define EX2_DATACENTERMANAGER_H

#include "HashTable.h"
#include "UnionFind.h"
#include "RankTree.h"
//#include "StatusType.h"
#include "library2.h"
#include "ServerData.h"

class DataCenterManager {
    int size;
    HashTable dc_hashtable;
    UnionFind<RankTree<ServerData>> dc_unionfind;
    RankTree<ServerData> main_tree;
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
