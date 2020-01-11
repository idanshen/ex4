#include "DataCenterManager.h"

DataCenterManager::DataCenterManager(int n) : size(n), dc_hashtable(HashTable(n)), dc_unionfind(UnionFind<RankTree<ServerData>>(n)) {
    main_tree = RankTree<ServerData>();
}

StatusType DataCenterManager::AddServer(int dataCenterID, int serverID) {
    if ((dataCenterID>this->size)||(dataCenterID<=0)||(serverID<=0)) return INVALID_INPUT;
    auto res = dc_hashtable.Search(serverID);
    if (res!=NULL) {
        return FAILURE; //server already exist
    } else {
        dc_hashtable.Insert(serverID,dataCenterID);
        return SUCCESS;
    }
}

