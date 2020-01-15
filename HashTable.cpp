//
// Created by User on 1/2/2020.
//
#include <new>
#include "HashTable.h"
using std::bad_alloc;

Server::Server(int ID, int DataCenterID):ID(ID),DataCenterID(DataCenterID), traffic(0){
    next_s=nullptr;
    prev_s= nullptr;
}
Server::Server(int ID,int DataCenterID,int traffic):ID(ID),DataCenterID(DataCenterID), traffic(traffic){
    next_s= nullptr;
    prev_s= nullptr;
}

int Server::getID() {return ID;}

int Server::getDataCenterID() {return DataCenterID;}

void Server::SetTraffic(int t) {traffic=t;}

int Server::GetTraffic() {return traffic;}

void Server::setNext(Server *s) {next_s=s;}

Server* Server::getNext() {return next_s;}

Server* Server::getPrev() {return prev_s;}

void Server::setPrev(Server *s) {prev_s=s;}


LinkedList::LinkedList():head(nullptr),last_node(nullptr){}

StatusType LinkedList::add_server(int ServerID,int DataCenterID,int traffic) {
    Server* new_s= nullptr;
    Server* current=head;
    while(current){
        if(current->getID()==ServerID){
            return FAILURE;
        }
        current=current->getNext();
    }
    try {
        new_s = new Server(ServerID, DataCenterID,traffic);
    }
    catch(bad_alloc& b){
        return ALLOCATION_ERROR;
    }
    if(!head){
        head=new_s;
    }
    if(!last_node){
        last_node=new_s;
    }
    else {
        last_node->setNext(new_s);
        new_s->setPrev(last_node);
        last_node=new_s;
    }
    return SUCCESS;
}

StatusType LinkedList::remove_server(int ServerID){
    Server* current=head;
    while(current){
        if(current->getID()==ServerID){
            if(!(current->getPrev())){
                if(!current->getNext()){
                    head= nullptr;
                    last_node= nullptr;
                }
                else {
                    head = current->getNext();
                    head->setPrev(nullptr);
                }
                delete current;
            }
            else if(!(current->getNext())){
                last_node=current->getPrev();
                last_node->setNext(nullptr);
                delete current;

            }
            else{
                Server* prev=current->getPrev();
                Server* next=current->getNext();
                prev->setNext(next);
                next->setPrev(prev);
                delete current;
            }
            return SUCCESS;
        }
        current=current->getNext();
    }
    return FAILURE;
}

Server* LinkedList::find_server(int ServerID) {
    Server* current=head;
    while(current){
        if(current->getID()==ServerID){
            return current;
        }
        current=current->getNext();
    }
    return nullptr;
}
Server* LinkedList::getHead() {
    return head;
}

LinkedList::~LinkedList() {
    Server* current=head;
    Server* next=head;
    while(next){
        next=current->getNext();
        delete current;
        current=next;
    }

}

HashTable::HashTable(int array_size):array_size(array_size),num_of_servers(0){
    try {
        dynamic_arr = new LinkedList *[array_size];
        for (int i = 0; i < array_size; i++) {
            dynamic_arr[i] = new LinkedList();
        }
    }
    catch(bad_alloc &b){}
}

int HashTable::HashFunc(int serverID) {
    return serverID%array_size;
}

StatusType HashTable::resize_table(int new_size) {
    LinkedList **new_arr;
    try {
        new_arr = new LinkedList*[new_size];
        for(int i=0;i<new_size;i++){
            new_arr[i]=new LinkedList();
        }
    }
    catch(bad_alloc &b){
        return ALLOCATION_ERROR;
    }
    int old_size=array_size;
    LinkedList** old_arr=dynamic_arr;
    array_size=new_size;
    dynamic_arr=new_arr;
    for(int i=0;i<old_size;i++){

        LinkedList* lst=old_arr[i];
        if(lst){
            Server* current=lst->getHead();
            while(current){
                int serverID=current->getID();
                int DataCenterID=current->getDataCenterID();
                int Traffic=current->GetTraffic();
                StatusType res1=Insert(serverID,DataCenterID,Traffic);
                if(res1==ALLOCATION_ERROR){
                    return ALLOCATION_ERROR;
                }
                current=current->getNext();
            }
        }
        delete lst;

    }
    delete old_arr;
    return SUCCESS;

}
StatusType HashTable::Insert(int serverID, int DataCenterID,int traffic) {
    int index=HashFunc(serverID);
    LinkedList* current=dynamic_arr[index];
    StatusType res;
    if(current){
        res=current->add_server(serverID,DataCenterID,traffic);
    }
    else{
        LinkedList *new_l;
        try {
            new_l = new LinkedList();
        }
        catch(bad_alloc &b){
            return ALLOCATION_ERROR;
        }
        res=new_l->add_server(serverID,DataCenterID,traffic);
        dynamic_arr[index]=new_l;
    }
    if(res!=SUCCESS){
        return res;
    }
    num_of_servers+=1;
    if(num_of_servers>=array_size/2){
        res=resize_table(array_size*2);
        return res;
    }

    return SUCCESS;
}

StatusType HashTable::Delete(int serverID) {
    int index=HashFunc(serverID);
    LinkedList* lst=dynamic_arr[index];
    StatusType res=lst->remove_server(serverID);
    if(res==SUCCESS){
        num_of_servers-=1;
        if(num_of_servers<=array_size/4){
            resize_table(array_size/2);
        }
    }
    return res;
}

Server* HashTable::Search(int serverID) {
    int index=HashFunc(serverID);
    if(!dynamic_arr[index]){
        return nullptr;
    }
    LinkedList* lst=dynamic_arr[index];
    Server* s=lst->find_server(serverID);
    return s;
}