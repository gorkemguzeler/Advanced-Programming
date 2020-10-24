//
//  queue.h
//  gorkemguzeler_the3
//
//  Created by gorkemg on 4.08.2020.
//  Copyright © 2020 Gorkem Guzeler. All rights reserved.
//

#include <iostream>
#include <string>

#ifndef queue_h
#define queue_h

using namespace std;

struct Packet
{
    string id;
    vector<string> routerHistory;
};

struct QueueNode
{
    Packet value;
    QueueNode *next;
};

class dynamicQueue{
    
    friend ostream & operator << (ostream&, const dynamicQueue&);

public:
    
    dynamicQueue(void);  //constructor
    ~dynamicQueue(void); //destructor
    void operator << (Packet myPacket);   //enqueue
    void operator >> (Packet &  newPacket);   //dequeue
    bool isEmpty(void) const;
    int get_num_elements() const;
  
    
private:
    QueueNode* front;
    QueueNode* rear;
    int num_of_elements;
    QueueNode* get_front() const;
};

//free function
ostream & operator << (ostream&, const dynamicQueue&); //SOR??


//member function implementations:
dynamicQueue::dynamicQueue(void){  //Your class ​must have a default constructor, which constructs an empty queue.
    front = nullptr;
    rear = nullptr;
    num_of_elements = 0;
//    cout << "Constructor is invoked" << endl;
}

bool dynamicQueue::isEmpty(void) const{
    return front == nullptr;
}

dynamicQueue::~dynamicQueue(void){ //Your class ​must have a destructor, which deallocates all the QueueNode​s in the ​Queue.
//    cout << "Destructor is invoked" << endl;
    Packet n;
    while(!isEmpty())
    {
        *this >> n;
    }
    rear = nullptr;
    front = nullptr;
}

void dynamicQueue::operator << (Packet myPacket){ // enqueue
    if (isEmpty()){
        front = new QueueNode;
        front->value = myPacket;
        rear = front;
    }
    else{
        rear->next = new QueueNode;
        rear->next->value = myPacket;
        rear= rear->next;
    }
    num_of_elements++;
}

void dynamicQueue::operator >> (Packet & newPacket){ // dequeue
    if (isEmpty())
    {
        cout << "Queue is empty" << endl;
    }
    else
    {
        newPacket.id = (front->value).id;
        newPacket.routerHistory = (front->value).routerHistory;
        
        QueueNode* temp = front;
        front = front->next;
        delete temp;
        num_of_elements--;
        
        if(num_of_elements == 0)
        {
            rear = nullptr;
            front = nullptr;
        }
    }
}

int dynamicQueue::get_num_elements() const
{
    return num_of_elements;
}

QueueNode* dynamicQueue::get_front() const
{
    return front;
}

//free function implementations:
ostream & operator << (ostream& os, const dynamicQueue& d)
{
    QueueNode* temp;
    temp = d.front;

    for(int m = 0 ; m < d.num_of_elements ; m++)
    {
        os << (temp->value).id << ": " ;
        
        for(int i=0; i < (temp->value).routerHistory.size()-1 ; i++)
        {
            os << (temp->value).routerHistory[i] << ", " ;
        }
        
        os << (temp->value).routerHistory[(temp->value).routerHistory.size()-1] << endl;
        
        temp = temp->next;
    }
    
    return os;
}

#endif /* queue_h */
