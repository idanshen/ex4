#ifndef EX2_DATACENTERMANAGER_H
#define EX2_DATACENTERMANAGER_H

#include "HashTable.h"
#include "UnionFind.h"
#include "RankTree.h"
#include "StatusType.h"
#include "DataCenter.h"

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

};


#endif //EX2_DATACENTERMANAGER_H
