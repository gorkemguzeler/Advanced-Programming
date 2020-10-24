//
//  Header.h
//  gorkemguzeler_the4
//
//  Created by gorkemg on 10.08.2020.
//  Copyright © 2020 Gorkem Guzeler. All rights reserved.
//

#ifndef queue_h
#define queue_h

#include <iostream>
using namespace std;

//FARKLI BİR STRUCT KULLANARAK INTHERIT ETMEK MÜMKÜN MÜ? nasıl? templated class mı kullanmalıyım????
struct queue_node{
    double Id;
    double MedianHouseAge;
    double AverageRooms;
    double AverageBedrooms;
    double Latitude;
    double Longitude;
    double MedianPrice;
    queue_node* next;
    
    queue_node(double i= 0,double m=0, double r= 0, double b= 0, double l= 0, double o= 0, double p=0, queue_node* n=nullptr): Id(i), MedianHouseAge(m), AverageRooms(r), AverageBedrooms(b), Latitude(l), Longitude(o), MedianPrice(p) ,next(n) {}
};

//template class<Type>
class dynamicQueue{
public:
    dynamicQueue(void);
    ~dynamicQueue(void); //destructor
    bool isEmpty(void) const;
//    void clear(void);
    void operator << (queue_node myPacket);   //enqueue
    void operator >> (queue_node &  newPacket);   //dequeue
    int get_num_of_elements();
    
private:
    queue_node* front;
    queue_node* rear;
    int num_of_elements = 0;
};

dynamicQueue::dynamicQueue(void) {
    front = nullptr;
    rear = nullptr;
//    cout << "Constructor is invoked" << endl;
}

dynamicQueue::~dynamicQueue(void){ //Your class ​must have a destructor, which deallocates all the QueueNode​s in the ​Queue.
//    cout << "Destructor is invoked" << endl;
    queue_node n;
    while(!isEmpty())
    {
        *this >> n;
    }
    rear = nullptr;
    front = nullptr;
}

 int dynamicQueue::get_num_of_elements()
{
    return num_of_elements;
}

bool dynamicQueue::isEmpty(void) const{
    return front == nullptr;
}

//void dynamicQueue::clear(void){
//    queue_node n;
//
//    while(!isEmpty())
//        *this >> n;
//
//    rear = nullptr;
//}

void dynamicQueue::operator << (queue_node myPacket){ // enqueue
    if (isEmpty()){
        front = new queue_node;
        front->Id = myPacket.Id;
        front->MedianHouseAge = myPacket.MedianHouseAge;
        front->AverageRooms = myPacket.AverageRooms;
        front->AverageBedrooms = myPacket.AverageBedrooms;
        front->Latitude = myPacket.Latitude;
        front->Longitude = myPacket.Longitude;
        front->MedianPrice = myPacket.MedianPrice;
        
        
        rear = front;
    }
    else{
        rear->next = new queue_node;
        rear->next->Id = myPacket.Id;
        rear->next->MedianHouseAge = myPacket.MedianHouseAge;
        rear->next->AverageRooms = myPacket.AverageRooms;
        rear->next->AverageBedrooms = myPacket.AverageBedrooms;
        rear->next->Latitude = myPacket.Latitude;
        rear->next->Longitude = myPacket.Longitude;
        rear->next->MedianPrice = myPacket.MedianPrice;
        
        rear= rear->next;
    }
    num_of_elements++;
}

void dynamicQueue::operator >> (queue_node & newPacket){ // dequeue
    if (isEmpty())
    {
//        cout << "Queue is empty" << endl;
    }
    else
    {
        newPacket.Id = front->Id;
        newPacket.MedianHouseAge = front->MedianHouseAge;
        newPacket.AverageRooms = front->AverageRooms;
        newPacket.AverageBedrooms = front->AverageBedrooms;
        newPacket.Latitude = front->Latitude;
        newPacket.Longitude = front->Longitude;
        newPacket.MedianPrice = front->MedianPrice;
        
        queue_node* temp = front;
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


#endif
