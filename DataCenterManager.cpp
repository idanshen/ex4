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

StatusType DataCenterManager::SetTraffic(int serverID, int traffic) {
    if ((traffic<0)||(serverID<=0)) return INVALID_INPUT;
    auto res = dc_hashtable.Search(serverID);
    if ((res->GetTraffic()==0)&&(traffic!=0)) {
        res->SetTraffic(traffic);
        try{
            auto new_s = new ServerData(serverID,traffic);
            RankTree<ServerData> *tree;
            dc_unionfind.Find(res->getDataCenterID(),&tree);
            tree->insert(*new_s);
            main_tree.insert(*new_s);
        }
        catch(bad_alloc& b){
            return ALLOCATION_ERROR;
        }
    }
}
