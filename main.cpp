#include <iostream>
#include "DataCenterManager.h"

int main() {
    auto tmp = DataCenterManager(10);
    tmp.AddServer(1,1);
    tmp.AddServer(2,2);
    tmp.AddServer(3,3);
    tmp.AddServer(3,5);
    tmp.AddServer(4,4);

    tmp.SetTraffic(1,8);
    tmp.SetTraffic(2,4);
    tmp.SetTraffic(3,1);
    tmp.SetTraffic(5,7);
    tmp.SetTraffic(4,2);

    tmp.RemoveServer(1);

    tmp.MergeDataCenters(3,4);
    tmp.RemoveServer(4);
    auto sum = new int;
    tmp.SumHighestTrafficServers(3,5,sum);
    std::printf("%d", *sum);
    return 0;
}