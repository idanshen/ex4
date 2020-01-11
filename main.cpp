#include <iostream>
#include "DataCenterManager.h"

int main() {
    auto tmp = DataCenterManager(10);
    tmp.AddServer(1,1);
    return 0;
}