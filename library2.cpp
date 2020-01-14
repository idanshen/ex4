#include "library2.h"
#include"DataCenterManager.h"

void *Init(int n) {
    try{
        auto *DS = new DataCenterManager(n);
        return (void*)DS;
    }
    catch (std::bad_alloc& b) {
        return nullptr;
    }
}

StatusType MergeDataCenters(void *DS, int dataCenter1, int dataCenter2){
    if(DS==NULL){
        return INVALID_INPUT;
    }
    return ((DataCenterManager *) DS)->MergeDataCenters(dataCenter1, dataCenter2);
}

StatusType AddServer(void *DS, int dataCenterID, int serverID){
    if(DS==NULL){
        return INVALID_INPUT;
    }
    return ((DataCenterManager *) DS)->AddServer(dataCenterID, serverID);
}

StatusType RemoveServer(void *DS, int serverID){
    if(DS==NULL){
        return INVALID_INPUT;
    }
    return ((DataCenterManager *) DS)->RemoveServer(serverID);
}

StatusType SetTraffic(void *DS, int serverID,  int traffic){
    if(DS==NULL){
        return INVALID_INPUT;
    }
    return ((DataCenterManager *) DS)->SetTraffic(serverID, traffic);
}

StatusType SumHighestTrafficServers(void *DS, int dataCenterID,  int k, int *traffic){
    if(DS==NULL){
        return INVALID_INPUT;
    }
    return ((DataCenterManager *) DS)->SumHighestTrafficServers(dataCenterID, k, traffic);
}

void Quit(void** DS){
    delete((DataCenterManager *) *DS);
    *DS=NULL;
}