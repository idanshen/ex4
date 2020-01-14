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
    if (res==NULL) return FAILURE;
    if (res->GetTraffic()==traffic) {
        return SUCCESS;
    }
    else if ((res->GetTraffic()==0)&&(traffic!=0)) {
        try{
            res->SetTraffic(traffic);
            auto new_s = new ServerData(serverID,traffic);
            RankTree<ServerData> *tree;
            dc_unionfind.Find(res->getDataCenterID(),&tree);
            tree->insert(*new_s);
            main_tree.insert(*new_s);
            return SUCCESS;
        }
        catch(bad_alloc& b){
            return ALLOCATION_ERROR;
        }
    } else if  ((res->GetTraffic()!=0)&&(traffic!=0)) {
        try{
            res->SetTraffic(traffic);
            auto for_search = new ServerData(serverID,traffic);
            RankTree<ServerData> *tree;
            generic_node<ServerData> *node;
            dc_unionfind.Find(res->getDataCenterID(),&tree);
            tree->find(*for_search,&node);
            node->data->set_traffic(traffic);
            tree->update_height(node);
            main_tree.find(*for_search,&node);
            node->data->set_traffic(traffic);
            main_tree.update_height(node);
            delete(for_search);
            return SUCCESS;
        }
        catch(bad_alloc& b){
            return ALLOCATION_ERROR;
        }
    }
    else if ((res->GetTraffic()!=0)&&(traffic==0)){
        try{
            res->SetTraffic(traffic);
            auto for_search = new ServerData(serverID,traffic);
            RankTree<ServerData> *tree;
            dc_unionfind.Find(res->getDataCenterID(),&tree);
            tree->remove(*for_search);
            main_tree.remove(*for_search);
            delete(for_search);
            return SUCCESS;
        }
        catch(bad_alloc& b){
            return ALLOCATION_ERROR;
        }
    }
}

StatusType DataCenterManager::RemoveServer(int serverID) {
    if (serverID<=0) return INVALID_INPUT;
    auto res = dc_hashtable.Search(serverID);
    if (res==NULL) return FAILURE;
    else {
        if (res->GetTraffic()!=0){
            try{
                auto for_search = new ServerData(serverID,res->GetTraffic());
                RankTree<ServerData> *tree;
                dc_unionfind.Find(res->getDataCenterID(),&tree);
                tree->remove(*for_search);
                main_tree.remove(*for_search);
                delete(for_search);
            }
            catch(bad_alloc& b){
                return ALLOCATION_ERROR;
            }
        }
        dc_hashtable.Delete(serverID);
        return SUCCESS;
    }
}

StatusType DataCenterManager::MergeDataCenters(int dataCenter1, int dataCenter2){
    if(dataCenter1<=0 || dataCenter1>size || dataCenter2<=0 || dataCenter2>size){
        return INVALID_INPUT;
    }
    StatusType res=this->dc_unionfind.Union(dataCenter1,dataCenter2);
    return res;

}
StatusType DataCenterManager::SumHighestTrafficServers(int dataCenterID, int k, int *traffic) {
    if ((dataCenterID>this->size)||(dataCenterID<0)||(k<0)||(traffic==NULL)) return INVALID_INPUT;
    if (dataCenterID==0) {
        main_tree.SumHighest(k,traffic);
        return SUCCESS;
    } else {
        RankTree<ServerData> *tree;
        dc_unionfind.Find(dataCenterID,&tree);
        tree->SumHighest(k,traffic);
        return SUCCESS;
    }
}