#include <iostream>
#include <assert.h>
#include <cstdlib>
#include "DataCenterManager.h"
using namespace std;

int main() {
    void** DS=new (void*);
    *DS=Init(100);
    Quit(DS);
    delete DS;

    cout<<"*******************************************************"<<"\n";

    return 0;
}