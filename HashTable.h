//
// Created by User on 1/2/2020.
//
#ifndef MAIN_CPP_HASHTABLE_H
#define MAIN_CPP_HASHTABLE_H
//#include "StatusType.h"
#include "library2.h"

class Server{
    int ID;
    int DataCenterID;
    int traffic;
    Server* next_s;
    Server* prev_s;
public:
    Server(int ID,int DataCenterID);
    Server(int ID,int DataCenterID,int traffic);
    ~Server()=default;
    int getID();
    int getDataCenterID();
    void SetTraffic(int t);
    int GetTraffic();
    void setNext(Server* s);
    Server* getNext();
    void setPrev(Server* s);
    Server* getPrev();
};

class LinkedList{
    Server* head;
    Server* last_node;
public:
    explicit LinkedList();
    ~LinkedList();
    StatusType add_server(int ServerID,int DataCenterID,int traffic=0);
    StatusType remove_server(int ServerID);
    Server* find_server(int ServerID);
    Server* getHead();

};

class HashTable{
    LinkedList** dynamic_arr;
    int array_size;
    int num_of_servers;
    int HashFunc(int serverID);
    StatusType resize_table(int new_size);
public:
    explicit HashTable(int array_size);
    ~HashTable();
    StatusType Insert(int serverID, int DataCenterID,int traffic=0);
    StatusType Delete(int serverID);
    Server* Search(int serverID);
};


#endif //MAIN_CPP_HASHTABLE_H
